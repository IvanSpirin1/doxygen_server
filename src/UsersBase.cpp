#include "UsersBase.h"

#include <fstream>
#include <Logger.h>
#include <sstream>
#include <limits>


bool UsersBase::ParseFile(const std::string& _pathToFile){
    
    m_users.clear();

    std::ifstream inpt(_pathToFile);
    std::string fileData;

    if(!inpt.is_open())
        throw "Invalid file";

    inpt.seekg(0,std::ios_base::end);
    auto fileSize = inpt.tellg();

    if(fileSize == 0)
        throw "User base is empty";

    fileData.resize(fileSize);
    inpt.seekg(0,std::ios_base::beg);
    inpt.read(&fileData[0],fileData.size());

    for(auto i = 0; i < fileSize;++i){
        auto endOfLine = fileData.find('\n',i);
        if(endOfLine == std::numeric_limits<size_t>::max())
            endOfLine = fileSize;

        auto divPos = fileData.find(':',i);
        if(divPos == std::string::npos)
            throw "Invalid user base format";

        auto login = fileData.substr(i,divPos-i);
        auto password = fileData.substr(divPos+1,endOfLine-divPos-1);

        AddUser(login,password);

        i=endOfLine;
    }

    return true;
}

bool UsersBase::AddUser(const std::string& _login,const std::string& _password){
    
    if(isHasUser(_login))
        return false;
    m_users.insert(std::make_pair(_login,_password));
    return true;
}        

std::string UsersBase::getPassword(const std::string& _login){
    return m_users[_login];
}

const bool UsersBase::isHasUser(const std::string& _login){
    return m_users.find(_login) != m_users.end();
}