
#include "Logger.h"

#include <iostream>
#include <fstream>
#include <ctime>

bool Logger::Initialize(const std::string _pathToLogFile){
    m_pathToFile = _pathToLogFile;

    std::ofstream log_file(m_pathToFile, std::ios_base::app);

    if(!log_file.is_open())
        return false;

    return true;
}

void Logger::Info(std::string _log){
    std::ofstream log_file(m_pathToFile, std::ios_base::app);
    std::time_t cur_time = std::time(nullptr);
    char buf[sizeof("dd/mmm/yyyy:HH:MM:SS")];
    std::strftime(buf, sizeof(buf), "%d/%b/%Y:%H:%M:%S", std::localtime(&cur_time));

    log_file << std::string(buf, sizeof(buf)) + '\t';
    log_file <<"[INFO]"<< _log << std::endl << std::flush;
    log_file.close();

    std::cout<<"[INFO]"<< _log << std::endl << std::flush;

}

void Logger::Error(std::string _log){
    std::ofstream log_file(m_pathToFile, std::ios_base::app);
    std::time_t cur_time = std::time(nullptr);
    char buf[sizeof("dd/mmm/yyyy:HH:MM:SS")];
    std::strftime(buf, sizeof(buf), "%d/%b/%Y:%H:%M:%S", std::localtime(&cur_time));

    log_file << std::string(buf, sizeof(buf)) + '\t';
    log_file <<"[ERROR]"<< _log << std::endl << std::flush;
    log_file.close();

    std::cout<<"[ERROR]"<< _log << std::endl << std::flush;

}

void Logger::Wargning(std::string _log){

    std::ofstream log_file(m_pathToFile, std::ios_base::app);
    std::time_t cur_time = std::time(nullptr);
    char buf[sizeof("dd/mmm/yyyy:HH:MM:SS")];
    std::strftime(buf, sizeof(buf), "%d/%b/%Y:%H:%M:%S", std::localtime(&cur_time));

    log_file << std::string(buf, sizeof(buf));
    log_file <<"[WARGNING]"<< _log << std::endl << std::flush;
    log_file.close();

    std::cout<<"[WARGNING]"<< _log << std::endl << std::flush;

}