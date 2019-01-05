#include "ThresholdingTransformation.h"


#include <opencv2/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>

Transformer::ThresholdingTransformation::ThresholdingTransformation()
{
}


Transformer::ThresholdingTransformation::~ThresholdingTransformation()
{
}

void Transformer::ThresholdingTransformation::processImage(cv::Mat & image)
{
	cv::Mat result_image;
	cv::threshold(image, result_image, m_threshold, 255, cv::THRESH_BINARY);

	image = result_image;
}

void Transformer::ThresholdingTransformation::setThreshold(int threshold)
{
	m_threshold = threshold;
}
