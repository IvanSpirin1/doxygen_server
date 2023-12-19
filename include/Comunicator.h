#pragma once

/** @file
* @author Спирин И.А.
* @version 1.0
* @date 18.12.2023
* @copyright ИБСТ ПГУ
* @warning Курсовая работа студента
* @brief Заголовочный файл для модуля Comunicator
*/

#include "UsersBase.h"

/** @brief Класс Comunicator
* @details Для создания сокета сервера и слушания запросов предназначен метод CreateSocket \n
* Для создания сокета клиента и подключения его к серверу метод WaitClient \n
* Для авторизации клиента предназначен метод isAutorized \n
*/
class Comunicator
{
public:
    /**
    * @brief Создание сокета сервера
    * @param [in] _port порт 
    * @return Сокет
    */
    int CreateSocket(const int _port);
    /**
    * @brief Создание сокета клиента
    * @param [in] _socket сокет сервера 
    * @return Сокет клиента
    */
    int WaitClient(const int _socket);
    /**
    * @brief Авторизация
    * @param [in] work_sock сокет клиента 
    * @param [in] UsersBase база данных пользователя
    * @return Сокет клиента
    */
    bool isAutorized(int work_sock,UsersBase _usersBase);
};
