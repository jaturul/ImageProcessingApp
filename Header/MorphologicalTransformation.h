#pragma once

#include "ImageTransformation.h"

#include <opencv2\core.hpp>

#include <memory>

struct ImagePoint;
class StructuringElement;

namespace Transformer
{
	enum class MorphologicalTransformationType { DILATION = 1, EROSION = 2 };

	class MorphologicalTransformation : public ImageTransformation
	{
	public:
		MorphologicalTransformation();
		MorphologicalTransformation(int width, int height, MorphologicalTransformationType type);
		~MorphologicalTransformation();

		void processImage(cv::Mat& image) override;
		void setTransformationType(const MorphologicalTransformationType& type);
		void setStructuringElementDimensions(int width, int height);

	private:
		cv::Mat transformGrayscaleImage(const cv::Mat& binaryImage, const StructuringElement& structuringElement);
		void transformImageAtPoint(cv::Mat& erodedImage, const ImagePoint& point, const int& erodingValue);
		int getTransformationValueAtPoint(const cv::Mat& binaryImage, const StructuringElement& structuringElement, const ImagePoint& point);

		bool transformationIsDilation();
		bool transformationIsErosion();

		std::unique_ptr<StructuringElement> m_strel;
		MorphologicalTransformationType m_type;
	};
}
