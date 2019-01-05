#pragma once

#include "ImageTransformationCommand.h"

namespace Transformer
{
	class ThresholdingTransformation;
}

class ThresholdCommand : public ImageTransformationCommand
{
public:
	ThresholdCommand(Transformer::ThresholdingTransformation* imageTransformer, int transformationParameter);
	~ThresholdCommand();

	virtual void processImage(cv::Mat& image) override;

private:
	Transformer::ThresholdingTransformation* m_image_transformer;
	int m_transformation_parameter;
};

