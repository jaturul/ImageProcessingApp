#pragma once

#include <algorithm>
#include <queue>
#include <string>
#include <vector>

class InputParser
{
public:
	InputParser();
	~InputParser();

	static std::vector<std::string> parseInput(int argc, char** argv);

private:
	static std::vector<std::string> getRawInput(int argc, char** argv);
	static std::string getFilenameFromPath(const std::string& path);

	static bool isImageName(const std::string& path);
	static bool isAlphanumerical(const std::string& name);
	static bool isImageExtension(const std::string& extension);
	static bool isImageTransformationLabel(const std::string& label);
	static bool isNumber(const std::string& number);
	static bool isForegroundExtractorOperation(const std::string& operation);
	static bool hasSlashes(const std::string& name);
};

