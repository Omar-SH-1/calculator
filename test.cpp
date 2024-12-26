#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "calculator.h"

TEST_SUITE_BEGIN("calculator");

TEST_CASE("testing applyOperation") {
    CHECK(applyOperation(1, 1, '+') == 2);
    CHECK(applyOperation(5, 3, '-') == 2);
    CHECK(applyOperation(2, 3, '*') == 6);
    CHECK(applyOperation(6, 2, '/') == 3);
    CHECK_THROWS_AS(applyOperation(5, 0, '/'), std::runtime_error);
    CHECK_THROWS_AS(applyOperation(5, 2, '%'), std::runtime_error);
}

TEST_CASE("testing isValidExpression") {
    CHECK(isValidExpression("1+2") == true);
    CHECK(isValidExpression("2.5*3") == true);
    CHECK(isValidExpression("4 / 2") == true);
    CHECK(isValidExpression("-5 + 3") == true);
    CHECK(isValidExpression("1+2a") == false);
    CHECK(isValidExpression("2++3") == true);
}

TEST_CASE("testing evaluateExpression") {
    CHECK(evaluateExpression("1+2") == doctest::Approx(3));
    CHECK(evaluateExpression("2*3") == doctest::Approx(6));
    CHECK(evaluateExpression("4/2") == doctest::Approx(2));
    CHECK(evaluateExpression("-5 + 3") == doctest::Approx(-2));
    CHECK(evaluateExpression("2 + 3 * 4") == doctest::Approx(14));
    CHECK(evaluateExpression("10 / 2 + 3") == doctest::Approx(8));
    CHECK_THROWS_AS(evaluateExpression("1 / 0"), std::runtime_error);
    CHECK_THROWS_AS(evaluateExpression("1 + 2a"), std::runtime_error);
}

TEST_SUITE_END();
