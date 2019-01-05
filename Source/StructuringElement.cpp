#include "StructuringElement.h"


StructuringElement::StructuringElement(int width, int height, const int originPointRow /* = 0 */, const int originPointColumn /* = 0 */)
	: m_strel_origin_point(originPointRow, originPointColumn)
	, m_foreground_pixel_number(width * height)
{
	initializeStrel(width, height);
}

StructuringElement::~StructuringElement()
{
}

void StructuringElement::initializeStrel(int width, int height)
{
	m_strel_pixels = std::make_unique<cv::Mat>(height, width, CV_8U, 255);
}

int StructuringElement::rows() const
{
	return m_strel_pixels->rows;
}

int StructuringElement::cols() const
{
	return m_strel_pixels->cols;
}

int StructuringElement::foregroundPixelNumber() const
{
	return m_foreground_pixel_number;
}

uchar StructuringElement::at(int x, int y) const
{
	return m_strel_pixels->at<uchar>(x,y);
}

ImagePoint StructuringElement::getOriginPoint() const
{
	return m_strel_origin_point;
}

bool StructuringElement::fitsInImageAtPoint(const cv::Mat& image, const ImagePoint& imagePoint ) const
{
	
	int origin_to_row_min = m_strel_origin_point.row();
	int origin_to_row_max = m_strel_pixels->rows - 1 - m_strel_origin_point.row();

	int origin_to_col_min = m_strel_origin_point.col();
	int origin_to_col_max = m_strel_pixels->cols - 1 - m_strel_origin_point.col();


	return ( (imagePoint.row() - origin_to_row_min >= 0) && (imagePoint.row() + origin_to_row_max < image.rows) &&
			 (imagePoint.col() - origin_to_col_min >= 0) && (imagePoint.col() + origin_to_col_max < image.cols) );

}
