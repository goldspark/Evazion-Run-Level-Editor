#pragma once

#include <iostream>
#include <fstream>
#include "../Scenes/Scene.h"

namespace GoldSpark {
	int FindWordEnd(char* currentText, const char* word);
	int FindWordBegin(char* currentText, const char* word);
	bool CheckFile(const std::ifstream& file_in);
	void ReadFile(const char* text);
	void LoadScene(const char* fileLocation, Scene& scene);

}
