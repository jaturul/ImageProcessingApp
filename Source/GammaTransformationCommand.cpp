#include "GammaTransformation.h"
#include "GammaTransformationCommand.h"

GammaTransformationCommand::GammaTransformationCommand(Transformer::GammaTransformation* transformer, int transformationParameter)
	: m_image_transformer(transformer)
	, m_transformation_parameter(transformationParameter)
{
}

GammaTransformationCommand::~GammaTransformationCommand()
{
}

void GammaTransformationCommand::processImage(cv::Mat & image)
{
	m_image_transformer->setGammaCorrectionPower(m_transformation_parameter);
	m_image_transformer->processImage(image);
}
