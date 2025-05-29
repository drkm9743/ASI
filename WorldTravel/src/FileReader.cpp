#include "FileReader.h"

namespace worldtravel
{
	namespace file
	{
		bool doesFileExist(const std::string& filePath)
		{
			std::ifstream file(filePath);
			return !file.fail();
		}

		void readFileToVector(const std::string& filePath, std::vector<std::string>& targetVector)
		{
			std::ifstream file(filePath);
			std::string line;

			if (file.is_open()) {
				while (std::getline(file, line)) {
					if (!line.empty()) {
						targetVector.push_back(line);
					}
				}
				file.close();
			}
		}
	}
}