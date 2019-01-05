#pragma once

#include "ConstantElements.h"

#include <memory>
#include <queue>
#include <vector>

class ImageTransformationCommand;

namespace Transformer
{
	class GammaTransformation;
	class MorphologicalTransformation;
	class LabelingTransformations;
	class ThresholdingTransformation;
}

namespace Factory
{
	class ImageTransformationCommandFactory
	{
	public:
		ImageTransformationCommandFactory();
		~ImageTransformationCommandFactory();

		std::queue<ImageTransformationCommand*> createImageTransformationCommands(std::vector<std::pair<Constants::OperationType, int>> operations);

	private:
		std::unique_ptr<Transformer::GammaTransformation> m_gamma_transformer;
		std::unique_ptr<Transformer::MorphologicalTransformation> m_morphological_transformer;
		std::unique_ptr<Transformer::LabelingTransformations> m_labeling_transformer;
		std::unique_ptr<Transformer::ThresholdingTransformation> m_thresholding_transformation;
	};
}


