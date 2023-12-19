#pragma once

/** @file
* @author Спирин И.А.
* @version 1.0
* @date 18.12.2023
* @copyright ИБСТ ПГУ
* @warning Курсовая работа студента
* @brief Заголовочный файл для модуля Server
*/

#include "Logger.h"
#include "Comunicator.h"
#include "UsersBase.h"


/** @brief Класс Server
* @details Для управления сервером предназначены 
* методы: ParseCmdLine для парсинга командной строки 
* и Initialize для инициализации
* и Run для запуска сервера
*/
class Server
{
public:
    /**
    * @brief Метод ParseCmdLine для парсинга
	* @param Параметры командной строки
	* @return Метод возвращает false, если нарушена правильность написания аргументов
    * @warning Вызов до инициализации
	*/
    bool ParseCmdLine(int argc, char **argv);
    /**
    * @brief Метод Initialize для инициализации
	* @return Метод возвращает false, если указан неверный параметр
	*/
    bool Initialize();
    /**
    * @brief Метод Run для запуска и прослушки сообщений
	* @return Метод ничего не возвращает
	*/
    int Run();

private:
    std::string m_usersBasePath;

    int m_targetPort;

    std::string m_logFilePath;

    UsersBase m_usersBase;
    Comunicator m_communicator;
    Logger m_logger;

    std::string getNextArg(int argc,char** argv);

    bool isNumber(std::string _str);

    int lastArg;
};
