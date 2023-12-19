#include "Comunicator.h"

#include <netinet/in.h>

#include <iostream>
#include <random>

#define CRYPTOPP_ENABLE_NAMESPACE_WEAK 1

#include <cryptopp/cryptlib.h>
#include <cryptopp/hex.h>
#include <cryptopp/md5.h>

#include "Logger.h"

using namespace CryptoPP;

std::string MD(std::string sah)
{
    Weak::MD5 hash;
    std::string digest;

    auto stringSink  = new StringSink(digest);
    auto hexEncoder = new HexEncoder(stringSink);
    auto hashFilter = new HashFilter(hash,hexEncoder);

    StringSource(sah, true, hashFilter);
    
    return digest;
}

int Comunicator::CreateSocket(const int _port)
{
    int s = socket(AF_INET, SOCK_STREAM, 0);//создается сокет для сервера
    std::unique_ptr<sockaddr_in> self_addr(new sockaddr_in);
    self_addr->sin_family = AF_INET;
    self_addr->sin_port = htons(_port);
    self_addr->sin_addr.s_addr = htonl(INADDR_ANY);
    int b = bind(s,reinterpret_cast <const sockaddr* > (self_addr.get()),sizeof(sockaddr_in));//закрепляет сокет
    if(b == -1)
        throw "Binding error";

    listen(s, SOMAXCONN);
    return s;
}

int Comunicator::WaitClient(const int _socket)
{
    std::unique_ptr<sockaddr_in> client_addr(new sockaddr_in);
    socklen_t len = sizeof (sockaddr_in);
    int clientSocket = accept(_socket, reinterpret_cast <sockaddr* > (client_addr.get()), &len);//создание сокета для клиента
    return clientSocket;
}

bool Comunicator::isAutorized(int work_sock,UsersBase _usersBase)
{

    std::string ok = "OK";
    std::random_device rnd;
    std::mt19937_64 rnd_generator(rnd());
    uint64_t rnd_number = rnd_generator();
    std::string salt;
    StringSource((const byte*)&rnd_number,8,true,new HexEncoder(new StringSink(salt)));
    std::string err = "ERR";
    std::unique_ptr<char[]> msg(new char[256]);

    int size_m = recv(work_sock, msg.get(), 256, 0);
    std::string login(msg.get(), size_m);

    if(!_usersBase.isHasUser(login))
        return false;

    std::string password = _usersBase.getPassword(login);

    msg = std::unique_ptr<char[]> (new char[256]);
    //соль отправленная клиенту
    send(work_sock, salt.c_str(), salt.length(), 0);
    size_m = recv(work_sock, msg.get(), 256, 0);
    std::string sah = salt + password;
    std::string digest;
    digest = MD(sah);
    std::string new_msg(msg.get(),size_m);
    //СВЕРКА ПАРОЛЕЙ
    if(digest != new_msg) {
        send(work_sock, err.c_str(), err.length(), 0);
        return false;
    } else {
        send(work_sock, ok.c_str(), ok.length(), 0);
    }

    return true;
}
