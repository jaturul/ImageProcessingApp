#pragma once

#include "ImageTransformation.h"

#include <map>

struct ColorHSV;
struct ImagePoint;

namespace Transformer
{
	class LabelingTransformations : public ImageTransformation
	{
	public:
		LabelingTransformations();
		~LabelingTransformations();

		void processImage(cv::Mat& image) override;

		int labelImage(const cv::Mat& image, cv::Mat& labeledImage);
		cv::Mat filterRegionsBySize(const cv::Mat& image, const int& sizeThreshold, bool maxSize);
		cv::Mat colorLabeledImage(const cv::Mat binaryImage, int numberOfAreas);

	private:
		std::vector<ColorHSV> getDistinctColors(int numberOfColors);
		std::map<int, int> getRegionSizes(const cv::Mat& labeledImage);
		std::vector<ImagePoint> get8connectedUnlabeledForegroundNeighboursAtPoint(const cv::Mat& image, const cv::Mat& labeledImage, const ImagePoint& point);
	};
}
