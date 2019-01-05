#pragma once

#include "ImagePoint.h"

#include <opencv2\core.hpp>

#include <memory>

class StructuringElement
{
public:
	StructuringElement(int width, int height, const int originPointRow = 0 , const int originPointCol = 0 );
	~StructuringElement();

	virtual void initializeStrel(int width, int height);
	int rows() const;
	int cols() const;
	int foregroundPixelNumber() const;
	uchar at(int x, int y) const;
	ImagePoint getOriginPoint() const;


	virtual bool fitsInImageAtPoint(const cv::Mat& image, const ImagePoint& imagePoint) const;

private:
	std::unique_ptr<cv::Mat> m_strel_pixels;
	ImagePoint m_strel_origin_point;
	int m_foreground_pixel_number;
};

