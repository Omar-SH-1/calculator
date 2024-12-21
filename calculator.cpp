#include "calculator.h"
#include <stdexcept>
#include <cctype>
#include <cstdlib>

// Выполняет операцию (+, -, *, /)
double applyOperation(double a, double b, char op) {
    if (op == '+') return a + b;
    if (op == '-') return a - b;
    if (op == '*') return a * b;
    if (op == '/') {
        if (b == 0) throw std::runtime_error("Error: Division by zero!");
        return a / b;
    }
    throw std::runtime_error("Error: Unknown operator!");
}

// Проверяет, является ли выражение корректным
bool isValidExpression(const std::string& expr) {
    for (char c : expr) {
        if (!std::isdigit(c) && c != '+' && c != '-' && c != '*' &&
            c != '/' && c != '.' && !std::isspace(c)) {
            return false;
        }
    }
    return true;
}

// Функция для вычисления результата выражения
double evaluateExpression(const std::string& expression) {
    std::string expr = expression;
    if (expr[0] == '-') {
        expr = "0" + expr;
    }

    if (!isValidExpression(expr)) {
        throw std::runtime_error("Error: Invalid expression!");
    }

    std::vector<double> numbers;
    std::vector<char> operators;

    // Разбор выражения
    for (size_t i = 0; i < expr.size(); ++i) {
        if (std::isdigit(expr[i]) || expr[i] == '.') {
            size_t j = i;
            while (j < expr.size() && (std::isdigit(expr[j]) || expr[j] == '.')) ++j;
            numbers.push_back(std::stod(expr.substr(i, j - i)));
            i = j - 1;
        } else if (expr[i] == '+' || expr[i] == '-' || expr[i] == '*' || expr[i] == '/') {
            operators.push_back(expr[i]);
        }
    }

    // Обработка операций с высоким приоритетом (* и /)
    for (size_t i = 0; i < operators.size(); ++i) {
        if (operators[i] == '*' || operators[i] == '/') {
            numbers[i + 1] = applyOperation(numbers[i], numbers[i + 1], operators[i]);
            numbers[i] = 0; // Значение больше не используется
            operators[i] = '+'; // Замена на нейтральный оператор
        }
    }

    // Обработка оставшихся операций (+ и -)
    double result = numbers[0];
    for (size_t i = 0; i < operators.size(); ++i) {
        result = applyOperation(result, numbers[i + 1], operators[i]);
    }

    return result;
}
