#include <iostream>
#include <string>
#include "calculator.h"

int main() {
    std::string input;
    while (true) {
        std::cout << "Введите выражение: ";
        std::getline(std::cin, input);

        try {
            double result = evaluateExpression(input);
            std::cout << "Результат: " << result << "\n";
        } catch (const std::exception& e) {

            std::cout << "Попробуй заново (ЭТО КАЛЬКУЛЯТОР).\n";
        }
    }
    return 0;
}
