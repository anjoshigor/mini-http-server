#ifndef IOACTION_H
#define IOACTION_H

#include <fstream> //ifstream, ofstream
#include <dirent.h> //lib C ler diretorio
#include <cstring> //strcmp, strcpy
#include <string> //strings
#include <vector> //vector

namespace IOAction {

	void copyto(const char *source, const char *destination);
	void getByte(const char *path, unsigned long *bytes);
	void load_folder(const char *path, std::vector<std::string> *list_file);
	void read_file(const char *path, char **destination);
	void write_file(const char *path, const char *data);
}

#endif //IOACTION_H