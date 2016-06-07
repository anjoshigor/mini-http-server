#include "LogClass.hpp"

//Definition of the static variable (Singleton)
LogClass * LogClass::instance_ = nullptr;

LogClass::LogClass(const std::string path){
	log_output_.open(path, std::ios::out);

	if (!log_output_)
	{
		std::cerr<<"Cannot open output file"<<std::endl;
		exit(1);
	}

	std::cerr<<"Everything is OK, the instance was created"<<std::endl;
}

LogClass::~LogClass(){
	std::cerr<<"Call Destructor"<<std::endl;
	log_output_.close();
}

LogClass& LogClass::makeInstance(const std::string path){
	if (!instance_)
		instance_ = new LogClass(path);
	else if(instance_)
		std::cerr<<"The instance has already been created"<<std::endl;

	return *instance_;
}

void LogClass::WriterLog(const std::string content){
	log_mutex_.lock(); //input protocol
	log_output_ << content << std::endl;
	log_mutex_.unlock();
}
