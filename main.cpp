#include <iostream>
#include <string>
#include "calculator.h"

int main() {
    while (true) {
        try {
            std::string expression;
            std::cout << "Enter an expression: ";
            std::getline(std::cin, expression);

            double result = evaluateExpression(expression);
            std::cout << "Final result: " << result << std::endl;
            break;
        } catch (const std::exception& err) {
            std::cout << err.what() << "\nPlease enter a new expression.\n";
        }
    }
    return 0;
}
