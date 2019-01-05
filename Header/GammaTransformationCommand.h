#pragma once

#include "ImageTransformationCommand.h"

namespace Transformer
{
	class GammaTransformation;
}

class GammaTransformationCommand : public ImageTransformationCommand
{
public:
	GammaTransformationCommand(Transformer::GammaTransformation* transformer, int transformationParameter);
	~GammaTransformationCommand();

	virtual void processImage(cv::Mat& image) override;

private:
	int m_transformation_parameter;
	Transformer::GammaTransformation* m_image_transformer;
};

