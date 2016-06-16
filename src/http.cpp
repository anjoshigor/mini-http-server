#include "http.h"
#include <unistd.h>
#include <netdb.h>
#include <sstream>
#include <fstream>
#include <vector>
#include <iostream>
#include <iterator>
#include <map>
#include <chrono>
#include <ctime>



namespace http{

  std::string NOT_FOUND = "HTTP/1.1 404 Not Found\n";
  std::string NOT_IN_PATTERN = "HTTP/1.1 400 Bad Command\n";
  std::string OK = "\n\nHTTP/1.1 200 OK \n";

  std::string parse_http(std::string buffer, std::string pattern){
      std::clog<<"Parsing request..."<<std::endl;

      std::vector<std::string> incoming_vec = split_string(buffer);//converts to
      std::vector<std::string> pattern_vec = split_string(pattern);//vec of strings

      std::string DATE = get_current_date();

      std::clog<<"Checking pattern..."<<std::endl;
      if(!check_pattern(incoming_vec, pattern_vec)){
        return  NOT_IN_PATTERN+DATE+"Server: FulaninhoServidor\nContent-Length: \nContent-Type: utf8\nConnection: Closed\n\n"+return_file("/badrequest.html","../files");
      }
      std::clog<<"Pattern [OK]"<<std::endl;

      std::clog<<"Checking requested file: "<<incoming_vec[1]<<"..."<<std::endl;
      if(!check_file(incoming_vec[1], "../files")){

        std::string MIME = return_mime(incoming_vec[1]);

        return  NOT_FOUND+DATE+"Server: FulaninhoServidor\nContent-Length: \nContent-Type: "+MIME+"Connection: Closed\n\n"+return_file("/notfound.html", "../files");
      }

      std::clog<<"File [OK]"<<std::endl;
      std::string MIME = return_mime(incoming_vec[1]);
      std::string ANSWER = return_file(incoming_vec[1], "../files");
      std::string SIZE = std::to_string(ANSWER.size());
      return OK+DATE+"Server: FulaninhoServidor\nContent-Length: "+SIZE+"\nContent-Type: "+MIME+"Connection: Closed\n\n"+ANSWER;
  }

  std::string return_file(std::string filename, std::string filepath){
    std::ifstream source((filepath+filename).c_str());
    std::string outcoming( (std::istreambuf_iterator<char>(source)),
                           (std::istreambuf_iterator<char>()) );
    return outcoming;
  }

  std::string get_current_date(){
    std::chrono::time_point<std::chrono::system_clock> end = std::chrono::system_clock::now();
    std::time_t end_time = std::chrono::system_clock::to_time_t(end);
    std::string TIME(std::ctime(&end_time));
    std::string DATE = "Date: "+TIME;
    return DATE;
  }

  std:: string return_mime(std::string filename){
    std::size_t found = filename.find_last_of(".");
    std::string MIME = "utf8\n";

    enum StringValue {wrong, jpg, png, css, pdf, html, mp3, mp4};
    std::map<std::string, StringValue> mapStringValues;
    mapStringValues["mp3"] = mp3;
    mapStringValues["mp4"] = mp4;
    mapStringValues["html"] = html;
    mapStringValues["css"] = css;
    mapStringValues["jpg"] = jpg;
    mapStringValues["jpeg"] = jpg;
    mapStringValues["png"] = png;
    mapStringValues["pdf"] = pdf;


      if(found){
      std::string TYPE = filename.substr(found+1);

        switch (mapStringValues[TYPE]) {
          case html:
          MIME = "text/html; charset=iso-8859-1\n";
          break;

          case pdf:
          MIME = "application/pdf\n";
          break;

          case css:
          MIME = "text/css\n";
          break;

          case png:
          MIME = "image/png\n";
          break;

          case jpg:
          MIME = "image/jpeg\n";
          break;

          case mp3:
          MIME = "audio/mp3\n";
          break;

          case mp4:
          MIME = "video/mp4\n";
          break;

          default:
          break;
        }

      }

    return MIME;
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
