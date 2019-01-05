#pragma once

#include "ConstantElements.h"

#include <opencv2\core.hpp>

#include <map>
#include <memory>
#include <queue>
#include <vector>

namespace Factory
{
	class ImageTransformationCommandFactory;
}

namespace Transformer
{
	class LabelingTransformations;
}

class ForegroundExtractor
{
public:
	
	ForegroundExtractor();
	~ForegroundExtractor();

	void doOperationOnImage(const cv::Mat& inputImage, const std::vector<std::string>& operation_vector, std::string operationType);

private:
	void showLabeledForeground(const cv::Mat& inputImage, const std::vector<std::string>& operation_vector);
	void showProcessedImage(const cv::Mat& inputImage, const std::vector<std::string>& operation_vector);
	std::vector<std::pair<Constants::OperationType, int>> getOperations(const std::vector<std::string>& parsed_input);
	void initializeOperationTypes();
	std::map<std::string, Constants::OperationType> m_operations_map;
	std::unique_ptr<Factory::ImageTransformationCommandFactory> m_command_factory;
	std::unique_ptr<Transformer::LabelingTransformations> m_labeling_element;
};

