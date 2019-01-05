#include "LabelingTransformations.h"
#include "MinSizeFilteringCommand.h"

MinSizeFilteringCommand::MinSizeFilteringCommand(Transformer::LabelingTransformations* transformer, int transformationParameter)
	: m_image_transformer(transformer)
	, m_transformation_parameter(transformationParameter)
{
}


MinSizeFilteringCommand::~MinSizeFilteringCommand()
{
}

void MinSizeFilteringCommand::processImage(cv::Mat & image)
{
	image = m_image_transformer->filterRegionsBySize(image, m_transformation_parameter, false);
}
