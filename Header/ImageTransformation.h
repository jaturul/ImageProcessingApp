#pragma once

#include <opencv2\core.hpp>

class ImageTransformation
{
public:
	virtual void processImage(cv::Mat& image) = 0;
};

