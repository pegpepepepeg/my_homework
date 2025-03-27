#include "LongNumber.hpp"
#define REQUIRE return
#define CHECK(x) if(!(x)) return false;
#define CHECK_FALSE(x) if(x) return false;

bool cmp(LongNumber a, LongNumber b) {
    LongNumber r = a - b;
    r.sign = false;
    return r < LongNumber(1e-6);
}

bool test1() {
    LongNumber num1(10.0);
    LongNumber num2(10.0);

    // when
    LongNumber result = num1 + num2;

    // then
    LongNumber expected(20.0);
    REQUIRE(cmp(result,expected));
}

bool test2() {
    LongNumber num1(0.1);
    LongNumber num2(0.1);

    // when
    LongNumber result = num1 + num2;

    // then
    LongNumber expected(0.2);
    REQUIRE(cmp(result, expected));
}

bool test3() {
    // given
    LongNumber num1(10.5);
    LongNumber num2(10.75);

    // when
    LongNumber result = num1 + num2;

    // then
    LongNumber expected(21.25);
    REQUIRE(cmp(result, expected));
}

bool test4() {
    // given
    LongNumber num1(-10.15);
    LongNumber num2(10.75);

    // when
    LongNumber result = num1 + num2;

    // then
    LongNumber expected(0.6);
    REQUIRE(cmp(result, expected));
}
bool test5() {
    // given
    LongNumber num1(-10000000000000000000000000000000000000000000000000000000000000000000001.5);
    LongNumber num2(10000000000000000000000000000000000000000000000000000000000000000000000.5);

    // when
    LongNumber result = num1 + num2;

    // then
    LongNumber expected(-1.0);
    REQUIRE(cmp(result,expected));
}

bool test6() {
    // given
    LongNumber num1(
        15.84375
    );
    LongNumber num2(
        11.8125
    );

    // when
    LongNumber result_positive = num1 - num2;

    // then
    LongNumber expected_positive(4.03125);
    CHECK(cmp(result_positive, expected_positive));

    // when
    LongNumber result_negative = num2 - num1;

    // then
    LongNumber expected_negative(-4.03125);
    REQUIRE(cmp(result_negative, expected_negative));
}

bool test7() {
    // given
    LongNumber num1(
        15.84375
    );
    LongNumber num2(
        11.8125
    );

    // when
    LongNumber result = num1 * num2;

    // then
    LongNumber expected(187.154296875);
    REQUIRE(cmp(result, expected));
}

bool test8() {
    // given
    LongNumber num1(
        -15.84375
    );
    LongNumber num2(
        11.8125
    );

    // when
    LongNumber result = num1 * num2;

    // then
    LongNumber expected(-187.154296875);
    REQUIRE(cmp(result, expected));
}

bool test9() {
    // given
    LongNumber num1(
        -15.84375
    );
    LongNumber num2(
        -11.8125
    );

    // when
    LongNumber result = num1 * num2;

    // then
    LongNumber expected(187.154296875);
    REQUIRE(cmp(result, expected));
}

bool test10() {
    // given
    LongNumber num1(
        2.25
    );
    LongNumber num2(
        2.25
    );

    // when
    LongNumber result = num1 / num2;

    // then
    LongNumber expected(1.0);
    REQUIRE(cmp(result, expected));
}

bool test11() {
    // given
    LongNumber num1(
        -2.25
    );
    LongNumber num2(
        2.25
    );

    // when
    LongNumber result = num1 / num2;

    // then
    LongNumber expected(-1.0);
    REQUIRE(cmp(result, expected));
}

bool test12() {
    // given
    LongNumber num1(
        -2.25
    );
    LongNumber num2(
        -2.25
    );

    // when
    LongNumber result = num1 / num2;

    // then
    LongNumber expected(1.0);
    REQUIRE(cmp(result, expected));
}

bool test13() {
    // given
    LongNumber num1(
        10.01
    );
    LongNumber num2(
        11.02
    );

    // when
    bool result_false = num1 > num2;

    // then
    CHECK_FALSE(result_false);

    // when
    bool result_true = num1 < num2;

    // then
    REQUIRE(result_true);
}

bool test14() {
    // given
    LongNumber num1(
        -10.01
    );
    LongNumber num2(
        11.02
    );

    // when
    bool result_false = num1 > num2;

    // then
    CHECK_FALSE(result_false);

    // when
    bool result_true = num1 < num2;

    // then
    REQUIRE(result_true);
}

bool test15() {
    // given
    LongNumber num1(
        -11.01
    );
    LongNumber num2(
        -10.02
    );

    // when
    bool result_false = num1 > num2;

    // then
    CHECK_FALSE(result_false);

    // when
    bool result_true = num1 < num2;

    // then
    REQUIRE(result_true);
}
/*
LongNumber calculate_pi(int precision) {
    LongNumber pi("3.0");
    LongNumber epsilon = LongNumber("0.1");
    for (int i = 0; i < precision; ++i) {
        epsilon = epsilon * LongNumber("0.1"); // epsilon = 10^{-precision}
    }

    LongNumber sign("1.0");
    LongNumber denominator("2.0"); // Начинаем с 2*3*4
    int step = 0;
    LongNumber term;

    do {
        term = LongNumber("4.0") / (denominator * (denominator + LongNumber("1.0")) * (denominator + LongNumber("2.0")));
        term = term * sign;

        pi = pi + term;

        sign = sign * LongNumber("-1.0");
        denominator = denominator + LongNumber("2.0");
        step++;
    } while (term > epsilon || term < epsilon * LongNumber("-1.0"));

    return pi;
}

TEST_CASE("Calculate pi", "[benchmark]") {
    BENCHMARK("Fibonacci 25") {
        return calculate_pi(100);
    };
}
*/

int main() {
    std::cout << "Test 1 " << (test1() ? "OK" : "FAIL") << '\n';
    std::cout << "Test 2 " << (test2() ? "OK" : "FAIL") << '\n';
    std::cout << "Test 3 " << (test3() ? "OK" : "FAIL") << '\n';
    std::cout << "Test 4 " << (test4() ? "OK" : "FAIL") << '\n';
    std::cout << "Test 5 " << (test5() ? "OK" : "FAIL") << '\n';
    std::cout << "Test 6 " << (test6() ? "OK" : "FAIL") << '\n';
    std::cout << "Test 7 " << (test7() ? "OK" : "FAIL") << '\n';
    std::cout << "Test 8 " << (test8() ? "OK" : "FAIL") << '\n';
    std::cout << "Test 9 " << (test9() ? "OK" : "FAIL") << '\n';
    std::cout << "Test 10 " << (test10() ? "OK" : "FAIL") << '\n';
    std::cout << "Test 11 " << (test11() ? "OK" : "FAIL") << '\n';
    std::cout << "Test 12 " << (test12() ? "OK" : "FAIL") << '\n';
    std::cout << "Test 13 " << (test13() ? "OK" : "FAIL") << '\n';
    std::cout << "Test 14 " << (test14() ? "OK" : "FAIL") << '\n';
    std::cout << "Test 15 " << (test15() ? "OK" : "FAIL") << '\n';

}