#include "LabelingTransformations.h"
#include "MaxSizeFilteringCommand.h"

MaxSizeFilteringCommand::MaxSizeFilteringCommand(Transformer::LabelingTransformations* transformer, int transformationParameter)
	: m_image_transformer(transformer)
	, m_transformation_parameter(transformationParameter)
{
}


MaxSizeFilteringCommand::~MaxSizeFilteringCommand()
{
}

void MaxSizeFilteringCommand::processImage(cv::Mat& image)
{
	image = m_image_transformer->filterRegionsBySize(image, m_transformation_parameter, true);
}
