#pragma once

/** @file
* @author Спирин И.А.
* @version 1.0
* @date 18.12.2023
* @copyright ИБСТ ПГУ
* @warning Курсовая работа студента
* @brief Заголовочный файл для модуля Logger
*/

#include <iostream>

/** @brief Класс Logger
* @details Для записи ошибок предназначен методы Info, Error, Warning
*/
class Logger{

    public:

        Logger() = default;

        /**
        * @brief Проверка доступности файла
        * @param [in] _pathToLogFile путь до файла
        * @return Метод возращает false, если файл недоступен для записи
        */
        bool Initialize(const std::string _pathToLogFile);

        /**
        * @brief Выводы в логи информации
        * @param [in] _log запись в файл
        * @return Метод ничего не возвращает
        */
        void Info(std::string _log);
        /**
        * @brief Выводы в логи ошибки
        * @param [in] _log запись в файл
        * @return Метод ничего не возвращает
        */
        void Error(std::string _log);
        /**
        * @brief Выводы в логи предупреждения
        * @param [in] _log запись в файл
        * @return Метод ничего не возвращает
        */
        void Wargning(std::string _log);
    private:

        std::string m_pathToFile;
};