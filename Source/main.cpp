#include "ForegroundExtractor.h"
#include "GammaTransformation.h"
#include "LabelingTransformations.h"
#include "MorphologicalTransformation.h"

#include "InputParser.h"

#include <opencv2/core.hpp>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/imgproc.hpp>

#include <cassert>
#include <iostream>
#include <string>
#include <map>

using namespace cv;
using namespace std;

int main(int argc, char** argv)
{
	std::vector<std::string> parsed_input;
	try
	{
		parsed_input = InputParser::parseInput(argc, argv);
	}
	catch (const std::exception e)
	{
		std::cout << e.what() << std::endl;
	}
	std::string image_path = parsed_input[0];
	
	std::cout << image_path;
	parsed_input.erase(parsed_input.begin());
	
	cv::Mat input_image = imread(image_path, CV_LOAD_IMAGE_GRAYSCALE);
	
	cv::namedWindow("Input image", CV_WINDOW_AUTOSIZE);
	cv::imshow("Input image", input_image);

	if (input_image.data == nullptr)
	{
		std::cerr << "The provided image name doesn't exist!" << std::endl;

		return -1;
	}

	ForegroundExtractor foreground_extractor;
	std::string foreground_extractor_operation = parsed_input[0];
	parsed_input.erase(parsed_input.begin());

	assert(parsed_input.size() % 2 == 0);

	foreground_extractor.doOperationOnImage(input_image, parsed_input, foreground_extractor_operation);
	
	system("pause");
	return 0;
}