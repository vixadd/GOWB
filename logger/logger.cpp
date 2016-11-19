#include "..\includes\logger.h"
using namespace std;

Logger::Logger(std::string filename) {
	//No critical section here since this is only called once
	this->filename = filename;
}

Logger::~Logger() {
}

//open close and clear the log file
void Logger::clearlogfile() {
	//lock the whole clearlogfile function to prevent 
	//multiple changes to the same file at the same time.
	//if an exception is thrown, the mutex will automatically unlock
	lock_guard<mutex> lock(m);
	myFile.open(filename, std::fstream::trunc);

	//close file
	if (myFile.is_open())
		myFile.close();
}

void Logger::log(std::string data) {
	//lock the whole log function to prevent
	//multiple changes to the same file at the same time.
	//if an exception is thrown, the mutex will automatically unlock
	lock_guard<mutex> lock(m);
	myFile.open(filename, std::fstream::app);
	if (!myFile.is_open())
		return;

	std::string myline;

	myFile << data;

	//close file
	if (myFile.is_open())
		myFile.close();
}
