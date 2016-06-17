#include "logger.hpp"

//initialize static data-member

Logger *Logger::instance = nullptr;

Logger::Cleanup::~Cleanup() {
	delete Logger::instance;
	Logger::instance = nullptr;
}

Logger::Logger(){
	static Cleanup cleanup;
	output.open("../log.txt", std::ios::out);

	if(!output.good())
		throw std::runtime_error("Unable to generate log file!");

	std::clog << "Created log file" << std::endl;
}

Logger::~Logger() {
	output.close();
}

Logger& Logger::get_instance(void) {

	if(instance == nullptr)
		instance = new Logger();
	return *instance;
}

std::string Logger::sys_time(void) const {
   time_t now = time(0);
   return std::string(ctime(&now));
}

void Logger::sys_register(const std::string& message, Flags level) {
	mutex.lock();

	std::string type;

	switch(level){
		case DEBUG:   type = "DEBUG"; 	break;
		case ERROR:	  type = "ERROR"; 	break;
		case INFO:	  type = "INFO"; 	break;
		case WARNING: type = "WARNING"; break;
	}

	std::string text {"[#] TYPE: " + type + "\t\tDATE: " + sys_time() +
					   "\n" + message + "\n"};

	output << "========" << std::endl;
	output << text <<std::endl;
	output << "========" << std::endl;

	mutex.unlock();
}
