#pragma once

#include "ImageTransformation.h"

#include <opencv2\core.hpp>

class ImageTransformationCommand
{
public:
	virtual void processImage(cv::Mat& image) = 0;
};