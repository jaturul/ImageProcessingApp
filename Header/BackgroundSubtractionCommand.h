#pragma once

#include "ImageTransformationCommand.h"

namespace Transformer
{
	class MorphologicalTransformation;
}

class BackgroundSubtractionCommand : public ImageTransformationCommand
{
public:
	BackgroundSubtractionCommand(Transformer::MorphologicalTransformation* imageTransformer, int transformationParameter);
	~BackgroundSubtractionCommand();

	virtual void processImage(cv::Mat& image) override;

private:
	Transformer::MorphologicalTransformation* m_image_transformer;
	int m_transformation_parameter;
};

