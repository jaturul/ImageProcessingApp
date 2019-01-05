#include "ConstantElements.h"
#include "ForegroundExtractor.h"
#include "ImageTransformationCommand.h"
#include "ImageTransformationCommandFactory.h"
#include "LabelingTransformations.h"

#include <opencv2/highgui/highgui.hpp>

#include <iostream>


ForegroundExtractor::ForegroundExtractor()
	: m_command_factory(new Factory::ImageTransformationCommandFactory)
	, m_labeling_element(new Transformer::LabelingTransformations)
{
	initializeOperationTypes();
}


ForegroundExtractor::~ForegroundExtractor()
{
}

void ForegroundExtractor::doOperationOnImage(const cv::Mat & inputImage, const std::vector<std::string>& operationVector, std::string operationType)
{
	if (operationType == "label")
	{
		showLabeledForeground(inputImage, operationVector);
	}
	else if (operationType == "show")
	{
		showProcessedImage(inputImage, operationVector);
	}
}

void ForegroundExtractor::showLabeledForeground(const cv::Mat& inputImage, const std::vector<std::string>& operation_vector)
{
	cv::Mat input_image_copy = inputImage.clone();
	std::vector<std::pair<Constants::OperationType, int>> image_operations = getOperations(operation_vector);
	std::queue<ImageTransformationCommand*> image_transformation_commands = m_command_factory->createImageTransformationCommands(image_operations);

	while (!image_transformation_commands.empty())
	{
		ImageTransformationCommand* current_command = image_transformation_commands.front();
		current_command->processImage(input_image_copy);

		image_transformation_commands.pop();
	}
	
	cv::namedWindow("Result image(BEFORE)", cv::WINDOW_AUTOSIZE);
	cv::imshow("Result image(BEFORE)", input_image_copy);

	cv::Mat labeled_image;
	int  number_of_foreground_areas = m_labeling_element->labelImage(input_image_copy, labeled_image);
	labeled_image = m_labeling_element->colorLabeledImage(labeled_image, number_of_foreground_areas);

	std::cout << "Number of detected regions: " << number_of_foreground_areas << std::endl;

	cv::namedWindow("Result image", cv::WINDOW_AUTOSIZE);
	cv::imshow("Result image", labeled_image);
	cv::waitKey(0);
}

void ForegroundExtractor::showProcessedImage(const cv::Mat & inputImage, const std::vector<std::string>& operation_vector)
{
	cv::Mat input_image_copy = inputImage.clone();
	std::vector<std::pair<Constants::OperationType, int>> image_operations = getOperations(operation_vector);
	std::queue<ImageTransformationCommand*> image_transformation_commands = m_command_factory->createImageTransformationCommands(image_operations);

	while (!image_transformation_commands.empty())
	{
		ImageTransformationCommand* current_command = image_transformation_commands.front();
		current_command->processImage(input_image_copy);

		image_transformation_commands.pop();
	}

	cv::namedWindow("Result image", cv::WINDOW_AUTOSIZE);
	cv::imshow("Result image", input_image_copy);
	cv::waitKey(0);
}

std::vector<std::pair<Constants::OperationType, int>> ForegroundExtractor::getOperations(const std::vector<std::string>& parsedInput)
{
	std::vector<std::pair<Constants::OperationType, int>> operations;

	for (int index = 0; index < parsedInput.size(); index+=2)
	{
		Constants::OperationType current_operation_type = m_operations_map[parsedInput[index]];
		int current_operation_parameter = std::stoi(parsedInput[index+1]);
		operations.push_back(std::pair<Constants::OperationType, int>(current_operation_type, current_operation_parameter));
	}

	return operations;
}

void ForegroundExtractor::initializeOperationTypes()
{
	std::vector<std::string> available_transformation_labels = Constants::ConstantElements::getTransformationLabels();
	for (int index = 0; index < available_transformation_labels.size(); ++index)
	{
		m_operations_map.insert
		(std::pair<std::string, Constants::OperationType>(available_transformation_labels[index], static_cast<Constants::OperationType>(index + 1)));
	}
}
