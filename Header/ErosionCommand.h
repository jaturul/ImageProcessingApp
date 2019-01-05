#pragma once

#include "ImageTransformationCommand.h"

namespace Transformer
{
	class MorphologicalTransformation;
}

class ErosionCommand :public ImageTransformationCommand
{
public:
	ErosionCommand(Transformer::MorphologicalTransformation* transformer, int transformationParameter);
	~ErosionCommand();

	virtual void processImage(cv::Mat& image) override;

private:
	Transformer::MorphologicalTransformation* m_image_transformer;
	int m_transformation_parameter;
};

