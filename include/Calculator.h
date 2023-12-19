#pragma once

/** @file
* @author Спирин И.А.
* @version 1.0
* @date 18.12.2023
* @copyright ИБСТ ПГУ
* @warning Курсовая работа студента
* @brief Заголовочный файл для модуля Calculator
*/


/** @brief Класс Calculator
* @details Для выполнения операции над данными и их отправки предназначен метод Calculate
* @warning Реализация только для типа данных uint32_t
*/
class Calculator
{
public:
    /**
	* @brief Метод Calculate для выполнения операции над данными и их отправки
	* @param [in] _clientSocket сокет 
	* @return Метод ничего не возвращает
	*/
    static bool Calculate(const int _clientSocket);
};
