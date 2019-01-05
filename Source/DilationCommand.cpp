#include "DilationCommand.h"
#include "MorphologicalTransformation.h"

DilationCommand::DilationCommand(Transformer::MorphologicalTransformation* transformer, int transformationParameter)
	: m_image_transformer(transformer)
	, m_transformation_parameter(transformationParameter)
{
}


DilationCommand::~DilationCommand()
{
}

void DilationCommand::processImage(cv::Mat & image)
{
	m_image_transformer->setTransformationType(Transformer::MorphologicalTransformationType::DILATION);
	m_image_transformer->setStructuringElementDimensions(m_transformation_parameter, m_transformation_parameter);
	m_image_transformer->processImage(image);
}

