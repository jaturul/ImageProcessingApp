#include "ConstantElements.h"

std::vector<std::string> Constants::ConstantElements::getAcceptableImageExtensions()
{
	return std::vector<std::string>{ "jpg", "png", "bmp" };
}

std::vector<std::string> Constants::ConstantElements::getForegroundExtractorOperations()
{
	return std::vector<std::string>{"label", "show"};
}

std::vector<std::string> Constants::ConstantElements::getTransformationLabels()
{
	return std::vector<std::string>{ "erosion", "dilation", "threshold", "max_size", "min_size", "background_sub", "gamma_correction" };
}
