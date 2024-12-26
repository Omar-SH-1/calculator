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

// Проверяет, является ли символ допустимым в выражении
bool isValidCharacter(char c) {
    return std::isdigit(c) || c == '+' || c == '-' || c == '*' || c == '/' || c == '.' || std::isspace(c);
}

// Проверяет корректность формата числа
bool isValidNumber(const std::string& num) {
    bool hasDot = false;
    for (size_t i = 0; i < num.size(); ++i) {
        if (num[i] == '.') {
            if (hasDot) return false; // Две точки в числе
            hasDot = true;
        } else if (!std::isdigit(num[i]) && !(i == 0 && num[i] == '-')) {
            return false; // Недопустимый символ в числе
        }
    }
    return !num.empty();
}

// Функция для вычисления результата выражения
double evaluateExpression(const std::string& expression) {
    std::string expr = expression;

    // Проверяем, содержит ли выражение недопустимые символы
    for (char c : expr) {
        if (!isValidCharacter(c)) {
            throw std::runtime_error("Error: Invalid character in expression!");
        }
    }

    std::vector<double> numbers;
    std::vector<char> operators;

    // Разбор выражения
    for (size_t i = 0; i < expr.size(); ++i) {
        if (std::isdigit(expr[i]) || expr[i] == '.' ||
            (expr[i] == '-' && (i == 0 || expr[i - 1] == '+' || expr[i - 1] == '-' || expr[i - 1] == '*' || expr[i - 1] == '/'))) {
            size_t j = i;
            while (j < expr.size() && (std::isdigit(expr[j]) || expr[j] == '.')) ++j;
            std::string number = expr.substr(i, j - i);
            if (!isValidNumber(number)) {
                throw std::runtime_error("Error: Invalid number format!");
            }
            try {
                numbers.push_back(std::stod(number));
            } catch (const std::exception&) {
                throw std::runtime_error("Error: Number conversion failed!");
            }
            i = j - 1;
        } else if (expr[i] == '+' || expr[i] == '-' || expr[i] == '*' || expr[i] == '/') {
            if (i == 0 || i == expr.size() - 1 || !std::isdigit(expr[i - 1]) && expr[i - 1] != '.') {
                throw std::runtime_error("Error: Operator position is invalid!");
            }
            operators.push_back(expr[i]);
        }
    }

    if (numbers.size() - 1 != operators.size()) {
        throw std::runtime_error("Error: Mismatch between numbers and operators!");
    }

    // Обработка операций с высоким приоритетом (* и /)
    for (size_t i = 0; i < operators.size(); ++i) {
        if (operators[i] == '*' || operators[i] == '/') {
            numbers[i + 1] = applyOperation(numbers[i], numbers[i + 1], operators[i]);
            numbers.erase(numbers.begin() + i);
            operators.erase(operators.begin() + i);
            --i;
        }
    }

    // Обработка оставшихся операций (+ и -)
    double result = numbers[0];
    for (size_t i = 0; i < operators.size(); ++i) {
        result = applyOperation(result, numbers[i + 1], operators[i]);
    }

    return result;
}
