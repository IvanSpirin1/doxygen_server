#include "Calculator.h"

#include <netinet/in.h>
#include <sys/ioctl.h>
#include <stdint.h>
#include <limits>
#include <vector>

#include <unistd.h>

bool Calculator::Calculate(const int _clientSocket)
{
    uint32_t numOfVectors;
    uint32_t vectorLenght;
    std::vector<uint32_t> vector;

    recv(_clientSocket, &numOfVectors, sizeof(numOfVectors), 0);

    for(uint32_t j=0; j< numOfVectors; j++) {

        recv(_clientSocket, &vectorLenght, sizeof(vectorLenght), 0);//прием длинны для первого вектора
        
        vector.resize(vectorLenght);
        while(1){
            int numOfBytes = 0;
            if( ioctl( _clientSocket, TIOCINQ, &numOfBytes ) < 0 )
                return false;

            if(numOfBytes == 0)
                continue;

            if(numOfBytes !=  vector.size() * sizeof(uint32_t))
                return false;
            else
                break;
        }

        recv(_clientSocket, vector.data(), sizeof(vector), 0);

        uint32_t sum = 0;

        for(const auto& vecEl : vector)
            sum+= vecEl*vecEl;
        
        send(_clientSocket, &sum, sizeof(sum), 0);
    }

    return true;
}
