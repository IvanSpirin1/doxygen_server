#include "Server.h"

int main(int argc, char *argv[])
{
    Server server;

    if(!server.ParseCmdLine(argc,argv))
    {
        std::cout << "Usage:"<<std::endl;
        std::cout << "-p(--port)\t<target port>"<<std::endl;
        std::cout << "-l(--log)\t<log file path>"<<std::endl;
        std::cout << "-f(--file)\t<user base file>" <<std::endl;

        return 0;
    };

    if(!server.Initialize()){
        return 1;
    }
    
    return server.Run();
}
