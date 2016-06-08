#include "http.h"
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <netdb.h>
#include <sstream>
#include <fstream>
#include <vector>
#include <iostream>
#include <iterator>
#include <dirent.h>


namespace http{

  std::string NOT_FOUND = "HTTP/1.1 404 Not Found\nDate: "+static_cast<const std::string>(__DATE__)+" "+static_cast<const std::string>(__TIME__)+" GMT"+"\nServer: Apache/2.2.14 (Win32)\nContent-Length: 0\nContent-Type: UNDEFINED\nConnection: Closed\n";
  std::string NOT_IN_PATTERN = "HTTP/1.1 400 Bad Command\nDate: "+static_cast<const std::string>(__DATE__)+" "+static_cast<const std::string>(__TIME__)+" GMT"+"\nServer: Apache/2.2.14 (Win32)\nContent-Length: 0\nContent-Type: UNDEFINED\nConnection: Closed\n";
  std::string OK = "\n\nHTTP/1.1 200 OK \nDate: " + static_cast<const std::string>(__DATE__)+ " " +static_cast<const std::string>(__TIME__)+" GMT \nServer : Custom/server \nContent-Length: \nContent-Type: utf8\n\n";

  std::string parse_http(std::string buffer, std::string pattern){
      std::clog<<"Parsing request..."<<std::endl;

      std::vector<std::string> incoming_vec = split_string(buffer);//converts to
      std::vector<std::string> pattern_vec = split_string(pattern);//vec of strings

      std::clog<<"Checking pattern..."<<std::endl;
      if(!check_pattern(incoming_vec, pattern_vec))
        return  NOT_IN_PATTERN;

      std::clog<<"Pattern [OK]"<<std::endl;



      std::clog<<"Checking requested file: "<<incoming_vec[1]<<"..."<<std::endl;
      if(!check_file(incoming_vec[1], "../files"))
        return  NOT_FOUND;

      std::clog<<"File [OK]"<<std::endl;

      return return_file(incoming_vec[1], "../files");
  }

  std::string return_file(std::string filename, std::string filepath){
    std::ifstream source((filepath+filename).c_str());
    std::string outcoming( (std::istreambuf_iterator<char>(source)),
                           (std::istreambuf_iterator<char>()) );
    return OK+outcoming;
  }

  bool check_file(std::string filename, std::string filepath){
    std::string fullpath = filepath+filename;
    std::clog<<"-Looking at "<<fullpath<<std::endl;

    if(fullpath.compare("../files/")==0){
        std::cerr << "--Cannot request entire folder [X]"<<std::endl;
        return false;
    }

    std::ifstream afile((fullpath).c_str(),std::ios::in);

    if(!afile.is_open()){
      std::cerr << "--File Not Found " << filepath+filename <<" [X]"<<std::endl;
      return false;
    }

    return true;
  }

  bool check_pattern(std::vector<std::string> buffer, std::vector<std::string> pattern){

    int j = 0;
    int size = pattern.size();

    for (size_t i = 0; i < buffer.size(); i++) {

      if (buffer[i]==pattern[j])
        j++;

      if (j == size)
        return true;

    }
    std::cerr << "-Not in Pattern [X]"<<std::endl;
    return false;
  }

  std::vector<std::string> split_string(std::string input){

      std::istringstream string_stream(input); //stream
      std::istream_iterator<std::string> begin(string_stream), end;//iterator
      std::vector<std::string> output(begin, end); // vector of strings

      return output;
  }


}
