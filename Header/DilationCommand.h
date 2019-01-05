#pragma once

#include "ImageTransformationCommand.h"

namespace Transformer
{
	class MorphologicalTransformation;
}

class DilationCommand : public ImageTransformationCommand
{
public:
	DilationCommand(Transformer::MorphologicalTransformation* transformer, int transformationParameter);
	~DilationCommand();

	virtual void processImage(cv::Mat& image) override;

private:
	Transformer::MorphologicalTransformation* m_image_transformer;
	int m_transformation_parameter;
};

