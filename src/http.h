#ifndef HTTP_H
#define HTTP_H

#include <fstream> //ifstream, ofstream
#include <dirent.h> //lib C read directory
#include <cstring> //strcmp, strcpy
#include <string> //strings
#include <vector> //vector

namespace http {

  extern std::string NOT_FOUND;
  extern std::string NOT_IN_PATTERN;
  extern std::string OK;

  std::string parse_http(std::string buffer, std::string pattern);
  bool check_pattern(std::vector<std::string> buffer, std::vector<std::string> pattern);
  bool check_file(std::string filename, std::string filepath);
  std::string return_file(std::string filename, std::string filepath);
  std::vector<std::string> split_string(std::string input);
  std::string return_mime(std::string filename);
  std::string get_current_date();
}

#endif //HTTP_H
