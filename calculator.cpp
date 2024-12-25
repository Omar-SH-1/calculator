#include <stdexcept>
#include <cctype>
#include <cstdlib>
#include <vector>
#include <iostream>

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

    if (!isValidExpression(expr)) {
        throw std::runtime_error("Скоро АКАДЕМ нормально введи!!");
    }

    std::vector<double> numbers;
    std::vector<char> operators;

    // Разбор выражения
    for (size_t i = 0; i < expr.size(); ++i) {
        // Проверка на число (включая отрицательное)
        if (std::isdigit(expr[i]) || expr[i] == '.' ||
            (expr[i] == '-' && (i == 0 || expr[i - 1] == '+' || expr[i - 1] == '-' || expr[i - 1] == '*' || expr[i - 1] == '/'))) {
            size_t j = i;
            while (j < expr.size() && (std::isdigit(expr[j]) || expr[j] == '.' || (j == i && expr[j] == '-'))) ++j;
            try {
                numbers.push_back(std::stod(expr.substr(i, j - i)));
            } catch (const std::exception&) {
                throw std::runtime_error("Error: Invalid number format!");
            }
            i = j - 1;
        } else if (expr[i] == '+' || expr[i] == '-' || expr[i] == '*' || expr[i] == '/') {
            operators.push_back(expr[i]);
        }
    }

    // Обработка операций с высоким приоритетом (* и /)
    for (size_t i = 0; i < operators.size(); ++i) {
        if (operators[i] == '*' || operators[i] == '/') {
            numbers[i + 1] = applyOperation(numbers[i], numbers[i + 1], operators[i]);
            numbers.erase(numbers.begin() + i);  // Удаляем обработанный элемент
            operators.erase(operators.begin() + i);  // Удаляем обработанный оператор
            --i;  // Возврат к предыдущему индексу
        }
    }

    // Обработка оставшихся операций (+ и -)
    double result = numbers[0];
    for (size_t i = 0; i < operators.size(); ++i) {
        result = applyOperation(result, numbers[i + 1], operators[i]);
    }

    return result;
}
