#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <string>
#include <vector>

// Функция для выполнения арифметической операции
double applyOperation(double a, double b, char op);

// Функция для проверки корректности выражения
bool isValidExpression(const std::string& expr);

// Функция для вычисления результата выражения
double evaluateExpression(const std::string& expression);

#endif // CALCULATOR_H
