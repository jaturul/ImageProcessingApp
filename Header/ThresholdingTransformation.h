#pragma once

#include "ImageTransformation.h"

namespace Transformer
{
	class ThresholdingTransformation : public ImageTransformation
	{
	public:
		ThresholdingTransformation();
		~ThresholdingTransformation();

		virtual void processImage(cv::Mat& image) override;
		void setThreshold(int threshold);

	private:
		int m_threshold;
	};

}

