#include "ErosionCommand.h"
#include "MorphologicalTransformation.h"

ErosionCommand::ErosionCommand(Transformer::MorphologicalTransformation * transformer, int transformationParameter)
	: m_image_transformer(transformer)
	, m_transformation_parameter(transformationParameter)
{
}

ErosionCommand::~ErosionCommand()
{
}

void ErosionCommand::processImage(cv::Mat & image)
{
	m_image_transformer->setTransformationType(Transformer::MorphologicalTransformationType::EROSION);
	m_image_transformer->setStructuringElementDimensions(m_transformation_parameter, m_transformation_parameter);
	m_image_transformer->processImage(image);
}
