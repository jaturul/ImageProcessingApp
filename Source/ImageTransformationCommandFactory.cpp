#include "ImageTransformationCommand.h"
#include "ImageTransformationCommandFactory.h"

#include "GammaTransformation.h"
#include "MorphologicalTransformation.h"
#include "LabelingTransformations.h"
#include "ThresholdingTransformation.h"

#include "BackgroundSubtractionCommand.h"
#include "DilationCommand.h"
#include "ErosionCommand.h"
#include "GammaTransformationCommand.h"
#include "MaxSizeFilteringCommand.h"
#include "MinSizeFilteringCommand.h"
#include "ThresholdCommand.h"


Factory::ImageTransformationCommandFactory::ImageTransformationCommandFactory()
	: m_morphological_transformer(new Transformer::MorphologicalTransformation)
	, m_gamma_transformer(new Transformer::GammaTransformation)
	, m_labeling_transformer(new Transformer::LabelingTransformations)
	, m_thresholding_transformation(new Transformer::ThresholdingTransformation)
{
}

Factory::ImageTransformationCommandFactory::~ImageTransformationCommandFactory()
{
}

std::queue<ImageTransformationCommand*> Factory::ImageTransformationCommandFactory::createImageTransformationCommands(std::vector<std::pair<Constants::OperationType, int>> operations)
{
	std::queue<ImageTransformationCommand*> transformation_command_queue;
	for (const auto& operation : operations)
	{
		switch (operation.first)
		{
			case Constants::OperationType::EROSION:
			{
				transformation_command_queue.push(new ErosionCommand(m_morphological_transformer.get(), operation.second));
				break;
			}
			case Constants::OperationType::DILATION:
			{
				transformation_command_queue.push(new DilationCommand(m_morphological_transformer.get(), operation.second));
				break;
			}
			case Constants::OperationType::THRESHOLD:
			{
				transformation_command_queue.push(new ThresholdCommand(m_thresholding_transformation.get(), operation.second));
				break;
			}
			case Constants::OperationType::MIN_SIZE:
			{
				transformation_command_queue.push(new MinSizeFilteringCommand(m_labeling_transformer.get(), operation.second));
				break;
			}
			case Constants::OperationType::MAX_SIZE:
			{
				transformation_command_queue.push(new MaxSizeFilteringCommand(m_labeling_transformer.get(), operation.second));
				break;
			}
			case Constants::OperationType::BACKGROUND_SUB:
			{
				transformation_command_queue.push(new BackgroundSubtractionCommand(m_morphological_transformer.get(), operation.second));
				break;
			}
			case Constants::OperationType::GAMMA_CORRECTION:
			{
				transformation_command_queue.push(new GammaTransformationCommand(m_gamma_transformer.get(), operation.second));
				break;
			}
		}
	}

	return transformation_command_queue;
}
