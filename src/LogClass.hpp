#ifndef LOG_CLASS_H
#define LOG_CLASS_H

#include <iostream>
#include <mutex>
#include <fstream>
#include <string>
#include <thread>

class LogClass
{
private:
	/*
		Private Constructors 
	 */
	LogClass(const std::string path);
	LogClass(LogClass& copy) = delete;
	
	/*
		Private Data Members
	 */
	static LogClass *instance_;
	std::ofstream log_output_ ;	
	std::mutex log_mutex_;
	
public:
	static LogClass& makeInstance(const std::string path);
	void WriterLog(const std::string content);
	~LogClass();
	
};

#endif // LOG_CLASS_H
