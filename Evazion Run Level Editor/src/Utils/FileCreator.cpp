#include "FileCreator.h"



namespace GoldSpark {


	void createFile(const char* name, const char* info) {
		std::ofstream outfile(name);
		outfile << info << std::endl;
		outfile.close();
	}


}