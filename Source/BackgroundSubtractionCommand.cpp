#include "BackgroundSubtractionCommand.h"
#include "MorphologicalTransformation.h"

#include <opencv2/highgui.hpp>


BackgroundSubtractionCommand::BackgroundSubtractionCommand(Transformer::MorphologicalTransformation* imageTransformer, int transformationParameter)
	: m_image_transformer(imageTransformer)
	, m_transformation_parameter(transformationParameter)
{
}


BackgroundSubtractionCommand::~BackgroundSubtractionCommand()
{
}

void BackgroundSubtractionCommand::processImage(cv::Mat & image)
{
	m_image_transformer->setStructuringElementDimensions(m_transformation_parameter, m_transformation_parameter);
	m_image_transformer->setTransformationType(Transformer::MorphologicalTransformationType::EROSION);
	cv::Mat image_background = image.clone();
	m_image_transformer->processImage(image_background);

	cv::namedWindow("Background", cv::WINDOW_AUTOSIZE);
	cv::imshow("Background", image_background);

	image = image - image_background;
}
