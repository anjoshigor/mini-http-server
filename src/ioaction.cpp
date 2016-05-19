#include "ioaction.h"

	/**
	*Copies a file from source to destination
	**/
	void IOAction::copyto(const char *source, const char *destination) {

		std::ifstream input(source, std::ios::binary);

		std::ofstream output(destination, std::ios::binary | std::ios::trunc);

		output << input.rdbuf();

		output.close();

		input.close();
	}
	/**
	*Gets number of bytes of a file
	**/
	unsigned long IOAction::getByte(const char *path) {

		unsigned long bytes = 0;

		std::ifstream input(path, std::ios::binary);

		if(input.good()){

			input.seekg(0, std::ios::end);

			bytes = input.tellg();

			input.close();
		}

			return bytes;
	}

//Change to Higor's function
	void IOAction::load_folder(const char *path, std::vector<std::string> *list_file) {

		DIR *directory;

	    struct dirent *entry;

	    if((directory = opendir(path))){

	        while((entry = readdir(directory))){

	        	if(strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0)
	            	list_file->push_back(entry->d_name);
	        }

	        closedir(directory);
	    }
	}
//Change to read the file just once
	void IOAction::read_file(const char *path, char **destination) {

		std::ifstream input;

		std::string buffer, line;

		input.open(path, std::ios::binary);

		if(input.good()) {

			while(getline(input, line)) buffer += line + '\n';

			input.close();

			*destination = new char[buffer.size()];

			strcpy(*destination, buffer.c_str());
		}
  }
/**
*Writes a data to the file erasing if it's not empty and creating
*if it doesn't exist
**/
	void IOAction::write_file(const char *path, const char *data) {

		std::ofstream output;

		output.open(path, std::ios::binary | std::ios::trunc);

		output << data;

		output.close();
	}
