#include "bigint.hpp"
#include <cassert>
#include <sstream>

//  Проверка конструктора по умолчанию
void DefaultConstructorTest()
{
    BigInt a;
    assert(a.GetLength() == 0 && a.IsEmpty());
}

//  Проверка конструктора из строки
void ConstructorFromStringTest()
{
    BigInt a("1024");
    BigInt b("-31");
    BigInt c("-123456789876543212345678987654321");

    assert(a.GetStringView() == "1024" && b.GetStringView() == "-31" &&
           c.GetStringView() == "-123456789876543212345678987654321");
}

//  Проверка конструктора из числа
void ConstructorFromIntTest()
{
    BigInt a(1024);
    BigInt b(-31);

    assert(a.GetStringView() == "1024" && b.GetStringView() == "-31");
}

//  Проверка конструктора копирования
void CopyConstructorTest()
{
    BigInt a(1024);
    BigInt b = a;

    assert(b.GetStringView() == "1024");
}

//  Проверка оператора копирования
void CopyAssignmentTest()
{
    BigInt a(1024);
    BigInt b;
    b = a;

    assert(b.GetStringView() == "1024");
}

//  Проверка сложения
void AdditionTest()
{
    BigInt a(99);
    BigInt b(-31);
    BigInt c(-100);
    BigInt d(100);
    BigInt big1("77777777777777777777777777777");
    BigInt big2("12121212121212121212121212121");
    BigInt big3("33333333333333333333333333333");
    BigInt big4("-10000000000000000000000000000");

    BigInt sum = a + b;
    assert(sum.GetStringView() == "68");

    sum = a + c;
    assert(sum.GetStringView() == "-1");

    sum = a + d;
    assert(sum.GetStringView() == "199");

    sum = b + c;
    assert(sum.GetStringView() == "-131");

    sum = b + d;
    assert(sum.GetStringView() == "69");

    sum = c + d;
    assert(sum.GetStringView() == "0");

    sum = c + d;
    assert(sum.GetStringView() == "0");

    sum = a + 1010;
    assert(sum.GetStringView() == "1109");

    sum = big1 + big2;
    assert(sum.GetStringView() == "89898989898989898989898989898");

    sum = big1 + big3;
    assert(sum.GetStringView() == "111111111111111111111111111110");

    sum = big1 + big4;
    assert(sum.GetStringView() == "67777777777777777777777777777");

    sum = big2 + big4;
    assert(sum.GetStringView() == "2121212121212121212121212121");

    sum = big3 + c;
    assert(sum.GetStringView() == "33333333333333333333333333233");
}

//  Проверка вычитания
void SubtractionTest()
{
    BigInt a(99);
    BigInt b(-31);
    BigInt c(-100);
    BigInt d(100);
    BigInt big1("12121212121212121212121212121");
    BigInt big2("33333333333333333333333333333");
    BigInt big3("10000000000000000000000000000");
    BigInt big4("33333333333333333333333333666");

    BigInt diff = a - b;
    assert(diff.GetStringView() == "130");

    diff = a - c;
    assert(diff.GetStringView() == "199");

    diff = a - d;
    assert(diff.GetStringView() == "-1");

    diff = b - c;
    assert(diff.GetStringView() == "69");

    diff = b - d;
    assert(diff.GetStringView() == "-131");

    diff = c - d;
    assert(diff.GetStringView() == "-200");

    diff = big1 - big2;
    assert(diff.GetStringView() == "-21212121212121212121212121212");

    diff = big3 - 1;
    assert(diff.GetStringView() == "9999999999999999999999999999");

    diff = big2 - big4;
    assert(diff.GetStringView() == "-333");
}

//  Проверка умножения
void MultiplicationTest()
{
    BigInt a(0);
    BigInt b(-2000);
    BigInt c(12345);
    BigInt d(-10000);
    BigInt big1("666666666666666666666666666666666666666");
    BigInt big2("123123123123123123123123123123123123123");
    BigInt big3("-30000000000000000000000000");

    BigInt product = a * b;
    assert(product.GetStringView() == "0");

    product = b * c;
    assert(product.GetStringView() == "-24690000");

    product = b * d;
    assert(product.GetStringView() == "20000000");

    product = big1 * 2;
    assert(product.GetStringView() == "1333333333333333333333333333333333333332");

    product = big2 * big3;
    assert(product.GetStringView() == "-3693693693693693693693693693693693693690000000000000000000000000");

    product = a * big3;
    assert(product.GetStringView() == "0");
}

//  Проверка унарного минуса
void UnaryMinusTest()
{
    BigInt a(0);
    BigInt b(-2000);
    BigInt c(12345);

    assert((-a).GetStringView() == "0" && (-b).GetStringView() == "2000" && (-c).GetStringView() == "-12345");
}

//  Проверка оператора вывода
void OstreamTest()
{
    BigInt a("-123456789876543212345678987654321");
    std::ostringstream out;
    out << a;
    std::string out_str = out.str();
    assert (out_str == "-123456789876543212345678987654321");

    a = 99999;
    out << a;
    out_str = out.str();
    assert (out_str == "-12345678987654321234567898765432199999");
}

//  Проверка логических операций сравнения
void ComparisonTest()
{
    BigInt a("10000000000000000000000");
    BigInt b("10000000000000000000010");
    BigInt c("-10000000000000000000000");
    BigInt d("-10000000000000000000010");

    bool compare = (a == a);
    assert (compare);
    compare = (a == b);
    assert (!compare);
    compare = (a != c);
    assert (compare);
    compare = (c != c);
    assert (!compare);
    compare = (b > a);
    assert (compare);
    compare = (d > d);
    assert (!compare);
    compare = (b >= c);
    assert (compare);
    compare = (d >= a);
    assert (!compare);
    compare = (d < c);
    assert (compare);
    compare = (a < c);
    assert (!compare);
    compare = (d <= d);
    assert (compare);
    compare = (b <= a);
    assert (!compare);
}

int main()
{
    DefaultConstructorTest();
    ConstructorFromStringTest();
    ConstructorFromIntTest();
    CopyConstructorTest();
    CopyAssignmentTest();
    AdditionTest();
    SubtractionTest();
    MultiplicationTest();
    UnaryMinusTest();
    OstreamTest();
    ComparisonTest();

    std::cout << "All tests passed!\n";
}