#pragma once
#include "ImageTransformation.h"

#include <opencv2\core.hpp>

namespace Transformer
{
	class GammaTransformation : public ImageTransformation
	{
	public:
		GammaTransformation();
		~GammaTransformation();

		void processImage(cv::Mat& image) override;
		void setGammaCorrectionPower(const int& power);

	private:
		void increaseContrast(cv::Mat& image);

		int m_gamma_correction_power;
	};
}
