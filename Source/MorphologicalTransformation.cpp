#include "MorphologicalTransformation.h"

#include "ImagePoint.h"
#include "StructuringElement.h"

#include <iostream>

Transformer::MorphologicalTransformation::MorphologicalTransformation()
{

}

Transformer::MorphologicalTransformation::MorphologicalTransformation(int width, int height, MorphologicalTransformationType type )
	: m_type(type)
	, m_strel(new StructuringElement(width, height))
{
	
}


Transformer::MorphologicalTransformation::~MorphologicalTransformation()
{
}

void Transformer::MorphologicalTransformation::processImage(cv::Mat & image)
{
	image = transformGrayscaleImage(image, *m_strel);
}

void Transformer::MorphologicalTransformation::setTransformationType(const MorphologicalTransformationType & type)
{
	m_type = type;
}

void Transformer::MorphologicalTransformation::setStructuringElementDimensions(int width, int height)
{
	m_strel.reset(new StructuringElement(width, height));
}

cv::Mat Transformer::MorphologicalTransformation::transformGrayscaleImage(const cv::Mat& grayscaleImage, const StructuringElement& structuringElement)
{
	cv::Mat erosion_result = grayscaleImage.clone();

	if (grayscaleImage.channels() != 1)
	{
		std::cerr << "The image is not grayscale!!! Erosion won't be performed.";
		return cv::Mat();
	}

	for (int row_index = 0; row_index < grayscaleImage.rows; ++row_index)
	{
		for (int col_index = 0; col_index < grayscaleImage.cols; ++col_index)
		{
			ImagePoint current_point(row_index, col_index);

			int min_val = getTransformationValueAtPoint(grayscaleImage, structuringElement, current_point);

			transformImageAtPoint(erosion_result, current_point, min_val);
		}
	}

	return erosion_result;
}

void Transformer::MorphologicalTransformation::transformImageAtPoint(cv::Mat& erodedImage, const ImagePoint& point, const int& transformationValue)
{
	erodedImage.at<uchar>(point.row(), point.col()) = transformationValue;
}

int Transformer::MorphologicalTransformation::getTransformationValueAtPoint(const cv::Mat& binaryImage, const StructuringElement& structuringElement, const ImagePoint& point)
{
	int extreme_value = 0;

	if (transformationIsErosion())
	{
		extreme_value = 255;
	}
	else if (transformationIsDilation())
	{
		extreme_value = 0;
	}

	// Working only for strel origin point in (0,0)!
	for (int strel_row_index = 0; strel_row_index < structuringElement.rows(); ++strel_row_index)
	{
		for (int strel_col_index = 0; strel_col_index < structuringElement.cols(); ++strel_col_index)
		{
			int current_image_row = point.row() + strel_row_index;
			int current_image_col = point.col() + strel_col_index;

			if ((current_image_row > binaryImage.rows - 1) || (current_image_col > binaryImage.cols - 1))
			{
				continue;
			}

			if (transformationIsErosion())
			{
				if (binaryImage.at<uchar>(current_image_row, current_image_col) < extreme_value)
				{
					extreme_value = binaryImage.at<uchar>(current_image_row, current_image_col);
				}
			}
			else if (transformationIsDilation())
			{
				if (binaryImage.at<uchar>(current_image_row, current_image_col) > extreme_value)
				{
					extreme_value = binaryImage.at<uchar>(current_image_row, current_image_col);
				}
			}
			
		}
	}

	return extreme_value;
}

bool Transformer::MorphologicalTransformation::transformationIsDilation()
{
	return (m_type == MorphologicalTransformationType::DILATION);
}

bool Transformer::MorphologicalTransformation::transformationIsErosion()
{
	return (m_type == MorphologicalTransformationType::EROSION);
}