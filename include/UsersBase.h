#pragma once

/** @file
* @author Спирин И.А.
* @version 1.0
* @date 18.12.2023
* @copyright ИБСТ ПГУ
* @warning Курсовая работа студента
* @brief Заголовочный файл для модуля UsersBase
*/

#include <iostream>
#include <unordered_map>

/** @brief Класс UsersBase
* @details Для чтения базы данных предназначен метод ParseFile
* Для проверки наличия клиента в базе данных предназначен метод isHasUser
*/
class UsersBase{

    public:

        /**
        * @brief Метод ParseFile для обратки базы данных пользователей
        * @param [in] _pathToUser base - путь до базы данных пользователей
        * @return Метод возращает false, если файл недоступен для чтения и если содержиться ошибка в базе данных
        */
        bool ParseFile(const std::string& _pathToFile);
        /**
        * @brief Метод AddUser для добавления пользователя в базу данных
        * @param [in] login - логин
        * @param [in] password - пароль
        * @return Метод возращает false, если пользователь уже существует
        */
        bool AddUser(const std::string& _login,const std::string& _password);
        /**
        * @brief Метод getPassword возвращает пароль для логина
        * @param [in] login - логин
        * @return Метод возращает пустую строку, если пользователь отсутствует
        */        
        std::string getPassword(const std::string& _login);
        /**
        * @brief Метод isHasUser для проверки наличия пользователя
        * @param [in] login - логин
        * @return Метод возращает false, если пользователь отсутствует
        */        
        const bool isHasUser(const std::string& _login);
        
    private:
        std::unordered_map<std::string,std::string> m_users;
};