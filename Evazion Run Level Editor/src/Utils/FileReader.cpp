#include "FileReader.h"
#include <cstdlib>

namespace GoldSpark {


	bool CheckFile(const std::ifstream& file_in) {
		if (!file_in) {
			std::cout << "Could not open file info.emap" << std::endl;
			return false;
		}

		return true;
	}


	
	
	void ReadFile(const char* text) {
		char t[200 + 1];

		std::ifstream file_in(text);
		if (!CheckFile(file_in))
			return;

		while (!file_in.eof()) {

			file_in.getline(t, 200);
			std::cout << t << std::endl;
		}

		file_in.close();
	
	}


	
	void LoadScene(const char* fileLocation, Scene& scene) {
		char x[10 + 1];
		char y[10 + 1];
		char sizeX[10 + 1];
		char sizeY[10 + 1];
		char* asset = nullptr;
		//variables to convert from char x to GameObject 
		float xPos = 0.0f;
		float yPos = 0.0f;
		float xSize = 0.0f;
		float ySize = 0.0f;


		char t[200 + 1];

		std::ifstream file_in(fileLocation);
		if (!CheckFile(file_in))
			return;

		int id = 0;


		while(!file_in.eof()){

		file_in.getline(t, 200);

		int positionEndIndex = FindWordEnd(t, "Position(");
		for (int i = positionEndIndex + 1; i < strlen(t); i++) {
			//Finding for X
			int lastNumberOfXindex = FindWordBegin(t + i, ", ");
			for (int j = 0; j < lastNumberOfXindex; j++) {
				x[j] = t[i + j];
			}

			if (lastNumberOfXindex > 1)
				xPos = atof(x);



			//Finding for Y
			int lastNumberOfYindex = FindWordBegin(t + i + lastNumberOfXindex + 2, ")Size");
			for (int k = 0; k < lastNumberOfYindex; k++) {
				y[k] = t[i + lastNumberOfXindex + 2 + k];
			}
			if (lastNumberOfXindex > 1)
				yPos = atof(y);

			std::cout << "X: " << xPos << std::endl;
			std::cout << "Y: " << yPos << std::endl;

			//Getting Texture Info
			int positionEndIndex = FindWordEnd(t, "Texture(");
			asset = t + positionEndIndex + 1;
			int length = strlen(asset);
			asset[length - 2] = '\0';
			std::cout << "Asset: " << asset << std::endl;

			
			break;
		}

		//Finding Size
		int sizeEndIndex = FindWordEnd(t, "Size(");
		for (int i = sizeEndIndex + 1; i < strlen(t); i++) {
			//Finding for X
			int lastNumberOfXindex = FindWordBegin(t + i, ", ");
			for (int j = 0; j < lastNumberOfXindex; j++) {
				sizeX[j] = t[i + j];
			}

			if (lastNumberOfXindex > 1)
				xSize = atof(sizeX);



			//Finding for Y
			int lastNumberOfYindex = FindWordBegin(t + i + lastNumberOfXindex + 2, ")Texture");
			for (int k = 0; k < lastNumberOfYindex; k++) {
				sizeY[k] = t[i + lastNumberOfXindex + 2 + k];
			}
			if (lastNumberOfXindex > 1)
				ySize = atof(sizeY);

			std::cout << "X: " << xSize << std::endl;
			std::cout << "Y: " << ySize << std::endl;

		

			//Create Game Object
			if (lastNumberOfXindex > 1 && lastNumberOfYindex > 1 && asset != nullptr) {

				GameObject* go = new GameObject(id, { xPos, yPos }, { xSize, ySize }, *new Texture2D(asset));
				scene.addToScene(go);

			}

		

			id++;
			break;
		}

		}

		file_in.close();

	}





	int FindWordEnd(char* currentText, const char* word) {
		bool found = false;
		int n = strlen(currentText);
		int word_n = strlen(word);

		//Index at which word is ending
		int index = 0;

		for (int i = 0; i < n; i++) {
			if (currentText[i] == word[0])
			{
				index = i;
				for (int j = 1; j < word_n; j++) {
					if (currentText[i + j] == word[j]) {
						found = true;
						index = i + j;
					}
					else {
						found = false;
					}
				}
				if (found)
					break;
			}
		}

		if (found) {
			return index;
		}
		else
			return -1;
	}

	int FindWordBegin(char* currentText, const char* word) {
		bool found = false;
		int n = strlen(currentText);
		int word_n = strlen(word);



		//Index at which word is beginning
		int index = 0;

		for (int i = 0; i < n; i++) {
			if (currentText[i] == word[0])
			{
				index = i;
				for (int j = 1; j < word_n; j++) {
					if (currentText[i + j] == word[j]) {
						found = true;
					}
					else {
						found = false;
					}
				}
				if (found)
					break;
			}
		}

		if (found) {
			return index;
		}
		else
			return -1;
	}

}
