#pragma once

#include <fstream>  
#include <iostream>
#include <vector>
#include <fstream>
#include <string>

namespace worldtravel
{
	namespace file
	{
		bool doesFileExist(const std::string& filePath);
		void readFileToVector(const std::string& filePath, std::vector<std::string>& targetVector);
	}
}