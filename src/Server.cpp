#include "Server.h"

#include "Calculator.h"

#include <netinet/in.h>
#include <signal.h>
#include <sys/socket.h>
#include <unistd.h>

void my_handler(int s)
{
    printf("Caught signal %d\n", s);
    exit(1);
}

bool Server::isNumber(std::string _str)
{
    for (const auto &ch : _str)
    {
        if (!std::isdigit(ch))
            return false;
    }
    return true;
}

std::string Server::getNextArg(int argc, char **argv)
{
    if (lastArg < argc)
        return std::string(argv[lastArg++]);
    return std::string();
}

bool Server::ParseCmdLine(int argc, char **argv)
{
    lastArg = 0;

    if (argv == 0)
        return false;

    std::string curArg;
    curArg = getNextArg(argc, argv);

    bool isAnyArgValid = false;

    while (!curArg.empty())
    {

        if (curArg == "-p" || curArg == "--port")
        {
            auto nextArg = getNextArg(argc, argv);
            if (isNumber(nextArg) && !nextArg.empty())
                m_targetPort = std::stoi(nextArg);
            else
                return false;

            isAnyArgValid = true;
        }
        else if (curArg == "-f" || curArg == "--file")
        {
            auto nextArg = getNextArg(argc, argv);
            if (nextArg.empty())
                return false;
            m_usersBasePath = nextArg;

            isAnyArgValid = true;
        }
        else if (curArg == "-l" || curArg == "--log")
        {
            auto nextArg = getNextArg(argc, argv);
            if (nextArg.empty())
                return false;
            m_logFilePath = nextArg;

            isAnyArgValid = true;
        }
        else
        {
            if (curArg[0] == '-')
                return false;
        }

        curArg = getNextArg(argc, argv);
    }

    return isAnyArgValid;
}

bool Server::Initialize()
{

    if (m_targetPort == 0)
    {
        std::cout << "target port not seted" << std::endl;
        return false;
    }

    if (m_usersBasePath.empty())
    {
        std::cout << "User base file path not seted" << std::endl;
        return false;
    }

    if (m_logFilePath.empty())
    {
        std::cout << "log file path not seted" << std::endl;
        return false;
    }

    if (!m_logger.Initialize(m_logFilePath))
    {
        return false;
    }

    if (m_targetPort != 33333)
    {
        m_logger.Error("Invalid port");
        return false;
    }

    m_logger.Info("Errors not found");

    try
    {
        m_usersBase.ParseFile(m_usersBasePath);
    }
    catch (const char *message)
    {
        m_logger.Error(message);
        return false;
    }

    return true;
}

int Server::Run()
{

    m_logger.Info("Server->Run");
    int socket = 0;

    try
    {
        socket = m_communicator.CreateSocket(m_targetPort);
    }
    catch (const char *str)
    {
        m_logger.Error(str);
    }

    while (true)
    {
        m_logger.Info("Waiting client connections");
        int clientSocket = m_communicator.WaitClient(socket);

        if (clientSocket == -1)
        {
            m_logger.Wargning("Client conection error");
            continue;
        }
        else
            m_logger.Info("Successfull client connection!");

        try
        {
            m_usersBase.ParseFile(m_usersBasePath);
        }
        catch (const char *message)
        {
            m_logger.Error(message);
            return false;
        }

        if (!m_communicator.isAutorized(clientSocket, m_usersBase))
        {
            m_logger.Wargning("Autorization failure");
            close(clientSocket);
        }

        if (!Calculator::Calculate(clientSocket))
        {
            m_logger.Wargning("Invalid client");
            close(clientSocket);
        }
        else
        {
            m_logger.Info("Calcuation is successful");
            close(clientSocket);
        }
    }

    close(socket);
    return 0;
}