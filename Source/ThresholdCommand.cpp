#include "ThresholdCommand.h"
#include "ThresholdingTransformation.h"

ThresholdCommand::ThresholdCommand(Transformer::ThresholdingTransformation* imageTransformer, int transformationParameter)
	: m_image_transformer(imageTransformer)
	, m_transformation_parameter(transformationParameter)
{
}

ThresholdCommand::~ThresholdCommand()
{
}

void ThresholdCommand::processImage(cv::Mat & image)
{
	m_image_transformer->setThreshold(m_transformation_parameter);
	m_image_transformer->processImage(image);
}
