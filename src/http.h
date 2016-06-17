#ifndef HTTP_H
#define HTTP_H

#include <map>
#include <iterator>
#include <chrono>
#include <ctime>
#include <iostream>
#include <sstream>
#include <fstream> //ifstream, ofstream
#include <string> //strings
#include <vector> //vector

namespace http {

    enum TYPES {
        WRONG,
        JPG,
        HTML,
        PNG,
        MP3,
        MP4,
        PDF,
        CSS
    };

    extern const std::map<std::string, TYPES> MAP_TYPES;
    extern const std::string NOT_FOUND;
    extern const std::string NOT_IN_PATTERN;
    extern const std::string OK;
    extern const std::string PATTERN;

    bool check_pattern(const std::vector<std::string>& buffer, const std::vector<std::string>& pattern);
    bool check_file(const std::string& filename, const std::string& filepath);
    std::string get_current_date();
    std::string parse_http(const std::string& buffer);
    std::string return_file(const std::string& filename, const std::string& filepath);
    std::string return_mime(const std::string& filename);
    std::vector<std::string> split_string(const std::string& input);
}

#endif //HTTP_H
