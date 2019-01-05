#include "GammaTransformation.h"


Transformer::GammaTransformation::GammaTransformation()
{
}


Transformer::GammaTransformation::~GammaTransformation()
{
}

void Transformer::GammaTransformation::processImage(cv::Mat & image)
{
	increaseContrast(image);
}

void Transformer::GammaTransformation::setGammaCorrectionPower(const int & power)
{
	m_gamma_correction_power = power;
}


void Transformer::GammaTransformation::increaseContrast(cv::Mat& image)
{
	for (int ii = 0; ii < image.rows; ++ii)
	{
		for (int jj = 0; jj < image.cols; ++jj)
		{
			image.at<uchar>(ii, jj) = static_cast<uchar>(std::pow(image.at<uchar>(ii, jj) / 255.0f, m_gamma_correction_power) * 255.0f);
		}
	}
}