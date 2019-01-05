#pragma once

#include "ImageTransformationCommand.h"

namespace Transformer
{
	class LabelingTransformations;
}

class MaxSizeFilteringCommand : public ImageTransformationCommand
{
public:
	MaxSizeFilteringCommand(Transformer::LabelingTransformations* transformer, int transformationParameter);
	~MaxSizeFilteringCommand();

	virtual void processImage(cv::Mat& image) override;

private:
	Transformer::LabelingTransformations* m_image_transformer;
	int m_transformation_parameter;
};

