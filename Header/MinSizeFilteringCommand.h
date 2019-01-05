#pragma once

#include "ImageTransformationCommand.h"

namespace Transformer
{
	class LabelingTransformations;
}

class MinSizeFilteringCommand : public ImageTransformationCommand
{
public:
	MinSizeFilteringCommand(Transformer::LabelingTransformations* transformer, int transformationParameter);
	~MinSizeFilteringCommand();

	virtual void processImage(cv::Mat& image) override;

private:
	Transformer::LabelingTransformations* m_image_transformer;
	int m_transformation_parameter;
};

