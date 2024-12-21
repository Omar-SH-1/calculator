
#include <iostream>
#include <vector>
#include <string>

double applyOperation(double a, double b, char op) {
    if (op == '+') return a + b;
    if (op == '-') return a - b;
    if (op == '*') return a * b;
    if (op == '/') {
        if (b == 0) throw "Error: Division by zero!";
        return a / b;
    }
    return 0;
}

bool isValidExpression(const std::string& expr) {
    for (char c : expr) {
        if (!((c >= '0' && c <= '9') || c == '+' || c == '-' || c == '*' || c == '/' || c == '.' || c == ' '))
            return false;
    }
    return true;
}

int main() {
while (true) {
    try {
        std::string expression;
        std::cout << "Enter an expression: ";
        std::getline(std::cin, expression);
        if (expression[0] == '-') {
            expression =  "0" + expression;
        }
        if (!isValidExpression(expression)) throw "В академ захотел?";

        std::vector<double> numbers;
        std::vector<char> operators;

        // Разбор выражения
        for (size_t i = 0; i < expression.size(); ++i) {
            if ((expression[i] >= '0' && expression[i] <= '9') || expression[i] == '.') {
                size_t j = i;
                while (j < expression.size() &&
                      ((expression[j] >= '0' && expression[j] <= '9') || expression[j] == '.')) ++j;
                numbers.push_back(std::stod(expression.substr(i, j - i)));
                i = j - 1;
            } else if (expression[i] == '+' || expression[i] == '-' ||
                       expression[i] == '*' || expression[i] == '/') {
                operators.push_back(expression[i]);
            }
        }

        // Обработка операций с высоким приоритетом (* и /)
        for (size_t i = 0; i < operators.size(); ++i) {
            if (operators[i] == '*' || operators[i] == '/') {
                numbers[i + 1] = applyOperation(numbers[i], numbers[i + 1], operators[i]);
                numbers[i] = 0; // Не используемое значение
                if(operators[i-1] == '-') {
                    operators[i] = '-';
                }
                else {
                    operators[i] = '+';
                }// Замена оператора
            }
        }

        // Обработка оставшихся операций (+ и -)
        double result = numbers[0];
        for (size_t i = 0; i < operators.size(); ++i) {
            result = applyOperation(result, numbers[i + 1], operators[i]);
        }

        std::cout << "Final result: " << result << std::endl;
        break;
    } catch (const char* err) {
        std::cout << err << "\nPlease enter a new expression.\n";
    }
}
return 0;
}


