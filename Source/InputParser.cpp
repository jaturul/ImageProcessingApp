#include "ConstantElements.h"
#include "InputParser.h"

#include <algorithm>
#include <locale>
#include <string>


InputParser::InputParser()
{
}


InputParser::~InputParser()
{
}

std::vector<std::string> InputParser::parseInput(int argc, char ** argv)
{
	/////// We are assuming Input in format: processed_image_name show_or_label operation_label_1 operation_parameter_1 ... operation_label_N operation_parameter_N

	std::vector<std::string> raw_input = getRawInput(argc, argv);
	std::vector<std::string> parsed_input;

	for (int argument_index = 0; argument_index < raw_input.size(); ++argument_index)
	{
		switch (argument_index)
		{
			case (0):
			{
				if (!isImageName(raw_input[argument_index]))
				{
					throw std::invalid_argument("Argument " + std::to_string(argument_index + 1) + " is not an image name!");
				}
			

				if (!hasSlashes(raw_input[argument_index]))
				{
					raw_input[argument_index] = "./" + raw_input[argument_index];
				}

				parsed_input.push_back(raw_input[argument_index]);
				break;
			}
			case(1):
			{
				if (!isForegroundExtractorOperation(raw_input[argument_index]))
				{
					throw std::invalid_argument("Argument " + std::to_string(argument_index + 1) + " is not a ForegroundExtractor operation!");
				}

				parsed_input.push_back(raw_input[argument_index]);

				break;
			}
			default:
			{
				if (argument_index % 2 == 0)
				{
					if (!isImageTransformationLabel(raw_input[argument_index]))
					{
						throw std::invalid_argument("Argument " + std::to_string(argument_index + 1) + " is not a transformation label!");
					}

					parsed_input.push_back(raw_input[argument_index]);
					break;
				}
				else
				{
					if (!isNumber(raw_input[argument_index]))
					{
						throw std::invalid_argument("Argument " + std::to_string(argument_index + 1) + " is not a numerical value!");
					}

					parsed_input.push_back(raw_input[argument_index]);
					break;
				}
			}
		}
	}

	if (parsed_input.size() % 2 == 1)
	{
		throw std::invalid_argument("Wrong number of arguments provided!");
	}

	return parsed_input;
}

std::vector<std::string> InputParser::getRawInput(int argc, char ** argv)
{
	std::vector<std::string> raw_input;

	// argument at index 0 is omitted as it's file name which isn't needed
	for (int argument_index = 1; argument_index < argc; ++argument_index)
	{
		std::string current_argument = std::string(argv[argument_index]);
		current_argument.erase(std::remove(current_argument.begin(), current_argument.end(), '\r'), current_argument.end());
		current_argument.erase(std::remove(current_argument.begin(), current_argument.end(), '\n'), current_argument.end());
 		raw_input.push_back(current_argument);
	}

	return raw_input;
}

std::string InputParser::getFilenameFromPath(const std::string & path)
{
	std::string local_path = path;
	int last_slash_index = static_cast<int>(path.find_last_of("\\"));
	if (last_slash_index == -1)
	{
		last_slash_index = static_cast<int>(path.find_last_of("/"));
	}
	std::string result = std::string(local_path.begin() + (last_slash_index + 1), local_path.end());
	return result;
}

bool InputParser::isImageName(const std::string & path)
{
	std::string file_name = getFilenameFromPath(path);
	int dot_index = static_cast<int>(file_name.find("."));

	std::string name(file_name.begin(), file_name.begin() + dot_index);
	std::string extension(file_name.begin() + dot_index + 1, file_name.end());

	if (!isAlphanumerical(name))
	{
		return false;
	}

	if (!isImageExtension(extension))
	{
		return false;
	}

	return true;
}

bool InputParser::isAlphanumerical(const std::string & name)
{
	for (const auto& character : name)
	{
		if (!isalnum(character))
		{
			return false;
		}
	}

	return true;
}

bool InputParser::isImageExtension(const std::string & extension)
{
	std::string local_extension = extension;
	std::transform(local_extension.begin(), local_extension.end(), local_extension.begin(), ::tolower);

	std::vector<std::string> acceptable_image_extensions = Constants::ConstantElements::getAcceptableImageExtensions();
	for (const auto& acceptable_extension: acceptable_image_extensions)
	{
		if (local_extension == acceptable_extension)
		{
			return true;
		}
	}

	return false;
}

bool InputParser::isImageTransformationLabel(const std::string & label)
{
	std::vector<std::string> available_transformation_labels = Constants::ConstantElements::getTransformationLabels();
	for (const auto& transformation_label : available_transformation_labels)
	{
		if (label == transformation_label)
		{
			return true;
		}
	}

	return false;
}

bool InputParser::isNumber(const std::string & number)
{
	for (const auto& digit : number)
	{
		if (!isdigit(digit))
		{
			return false;
		}
	}

	return true;
}

bool InputParser::isForegroundExtractorOperation(const std::string & operation)
{
	std::vector<std::string> available_operation_labels = Constants::ConstantElements::getForegroundExtractorOperations();
	for (const auto& operation_label : available_operation_labels)
	{
		if (operation == operation_label)
		{
			return true;
		}
	}

	return false;
}

bool InputParser::hasSlashes(const std::string & name)
{
	int last_slash_index = static_cast<int>(name.find_last_of("\\"));
	if (last_slash_index == -1)
	{
		last_slash_index = static_cast<int>(name.find_last_of("/"));
	}

	return last_slash_index != -1;
}
