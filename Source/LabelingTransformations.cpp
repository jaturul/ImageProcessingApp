// based on 1-pass algorithm found here https://en.wikipedia.org/wiki/Connected-component_labeling

#include "ColorHSV.h"
#include "ImagePoint.h"
#include "LabelingTransformations.h"

#include <opencv2\core.hpp>
#include <opencv2\imgproc.hpp>

#include <queue>
#include <map>


Transformer::LabelingTransformations::LabelingTransformations()
{
}


Transformer::LabelingTransformations::~LabelingTransformations()
{
}

void Transformer::LabelingTransformations::processImage(cv::Mat & image)
{
	cv::Mat labeled_image;
	labelImage(image, labeled_image);

	image = labeled_image;
}

// returns the number of labeled regions
int Transformer::LabelingTransformations::labelImage(const cv::Mat& image, cv::Mat& labeledImage)
{
	labeledImage = cv::Mat::zeros(image.rows, image.cols, CV_8UC1);
	int current_label = 0;
	std::queue<ImagePoint> neighbour_queue;

	for (int row_index = 0; row_index < image.rows; ++row_index)
	{
		for (int col_index = 0; col_index < image.cols; ++col_index)
		{
			if ((image.at<uchar>(row_index, col_index) == 255) && (labeledImage.at<uchar>(row_index, col_index) == 0))
			{
				++current_label;
				labeledImage.at<uchar>(row_index, col_index) = current_label;
				neighbour_queue.push(ImagePoint(row_index, col_index));

				while (!neighbour_queue.empty())
				{
					ImagePoint current_point = neighbour_queue.front();

					if ((image.at<uchar>(current_point.row(), current_point.col()) == 255) &&
						(labeledImage.at<uchar>(current_point.row(), current_point.col()) == 0))
					{
						labeledImage.at<uchar>(current_point.row(), current_point.col()) = (uchar)current_label;
					}
					std::vector<ImagePoint> current_queue_element_neighbours = get8connectedUnlabeledForegroundNeighboursAtPoint(image, labeledImage, current_point);
					for (const auto& neighbour : current_queue_element_neighbours)
					{
						labeledImage.at<uchar>(neighbour.row(), neighbour.col()) = (uchar)current_label;
						neighbour_queue.push(neighbour);
					}

					neighbour_queue.pop();
				}
			}

		}
	}

	return current_label;
}

std::vector<ImagePoint> Transformer::LabelingTransformations::get8connectedUnlabeledForegroundNeighboursAtPoint(const cv::Mat& image, const cv::Mat& labeledImage, const ImagePoint& point)
{
	std::vector<ImagePoint> forground_neighbours;
	for (int row_index = -1; row_index < 2; ++row_index)
	{
		for (int col_index = -1; col_index < 2; ++col_index)
		{
			ImagePoint current_neighbour(point.row() + row_index, point.col() + col_index);
			if (((row_index == 0) && (col_index == 0)) || (current_neighbour.row() < 0) || (current_neighbour.col() < 0) ||
				(current_neighbour.col() >= image.cols) || (current_neighbour.row() >= image.rows))
			{
				continue;
			}

			if ((image.at<uchar>(current_neighbour.row(), current_neighbour.col()) != 0) &&
				(labeledImage.at<uchar>(current_neighbour.row(), current_neighbour.col()) == 0))
			{
				forground_neighbours.push_back(current_neighbour);
			}
		}
	}

	return forground_neighbours;
}

std::vector<ColorHSV> Transformer::LabelingTransformations::getDistinctColors(int numberOfColors)
{
	std::vector<ColorHSV> colors;
	const int GOOD_SATURATION = 175;
	const int GOOD_VALUE = 175;
	const int HUE_MAX_VALUE = 180;

	for (int index = 0; index < numberOfColors; ++index)
	{
		int current_hue = (index + 1) * HUE_MAX_VALUE / numberOfColors;
		colors.push_back(ColorHSV(current_hue, GOOD_SATURATION, GOOD_VALUE));
	}

	return colors;
}

std::map<int, int> Transformer::LabelingTransformations::getRegionSizes(const cv::Mat& labeledImage)
{
	std::map<int, int> region_sizes;

	for (int row_index = 0; row_index < labeledImage.rows; ++row_index)
	{
		for (int col_index = 0; col_index < labeledImage.cols; ++col_index)
		{
			int region_label = labeledImage.at<uchar>(row_index, col_index);
			if (region_label != 0)
			{
				if (region_sizes.find(region_label) == region_sizes.end())
				{
					region_sizes.insert(std::pair<int, int>(region_label, 1));
				}
				else
				{
					region_sizes[region_label] += 1;
				}
			}
		}
	}

	return region_sizes;
}

cv::Mat Transformer::LabelingTransformations::filterRegionsBySize(const cv::Mat& image, const int& sizeThreshold, bool isThresholdMaxSize)
{
	cv::Mat result = cv::Mat::zeros(image.rows, image.cols, CV_8UC1);
	cv::Mat labeled_image;
	labelImage(image, labeled_image);
	std::map<int, int> region_sizes = getRegionSizes(labeled_image);

	for (int row_index = 0; row_index < image.rows; ++row_index)
	{
		for (int col_index = 0; col_index < image.cols; ++col_index)
		{
			int region_label = labeled_image.at<uchar>(row_index, col_index);
			if (region_label != 0)
			{
				if (isThresholdMaxSize ? (region_sizes[region_label] <= sizeThreshold) : (region_sizes[region_label] >= sizeThreshold))
				{
					result.at<uchar>(row_index, col_index) = 255;
				}
			}
		}
	}

	return result;
}


cv::Mat Transformer::LabelingTransformations::colorLabeledImage(const cv::Mat binaryImage, int numberOfAreas)
{
	cv::Mat colored_image = cv::Mat::zeros(binaryImage.rows, binaryImage.cols, CV_8UC3);
	std::vector<ColorHSV> label_colors = getDistinctColors(numberOfAreas);

	for (int row_index = 0; row_index < binaryImage.rows; ++row_index)
	{
		for (int col_index = 0; col_index < binaryImage.cols; ++col_index)
		{
			int current_label = (int)binaryImage.at<uchar>(row_index, col_index);
			if (current_label != 0)
			{
				ColorHSV current_color = label_colors.at(current_label - 1);
				cv::Vec3b current_color_vector = cv::Vec3b(current_color.hue(), current_color.saturation(), current_color.value());
				colored_image.at<cv::Vec3b>(row_index, col_index) = current_color_vector;
			}
		}
	}

	cv::cvtColor(colored_image, colored_image, CV_HSV2BGR);

	return colored_image;
}

