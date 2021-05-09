#include <cassert>
#include <sstream>
#include "matrix.hpp"

//  Проверка установки размерности в конструкторе
void DimensionsTest()
{
    Matrix matr(12, 4);
    
    assert (matr.GetRows() == 12 && matr.GetColumns() == 4);
}

//  Проверка двойной индексации
void IndexationTest()
{
    Matrix matr(3, 3);
    matr[2][1] = 5;
    matr[1][0] = 7;
    matr[2][1] = 2;
    
    assert (matr[2][1] == 2 && matr[1][0] == 7);
}

//  Проверка индексации, выходящей за размеры матрицы
void OutOfBoundsTest()
{
    Matrix matr(2, 4);
    int total_errors = 0;
    try 
    {
        matr[2][1] = 3;
    }
    catch(std::out_of_range)
    {
        total_errors++;
    }
    try 
    {
        int32_t bad_index_variable = matr[0][21];
        matr[0][0] = bad_index_variable;
    }
    catch(std::out_of_range)
    {
        total_errors++;
    }
    try 
    {
        matr[0][0] = matr[3][5];
    }
    catch(std::out_of_range)
    {
        total_errors++;
    }
    
    assert (total_errors == 3);
}

//  Проверка работы конструктора копирования
void CopyConstructorTest()
{
    Matrix matr1(3, 5);
    matr1[2][2] = 7;
    Matrix matr2 = matr1;
    
    assert (matr2.GetRows() == 3 && matr2.GetColumns() == 5 &&
            matr2[2][2] == 7);
}

//  Проверка работы оператора присваивания
void AssignmentTest()
{
    Matrix matr1(3, 5);
    Matrix matr2(6, 6);
    matr1[1][1] = 6;
    matr1[2][2] = 7;
    matr2 = matr1;
    matr2[1][1] = 8;
    
    assert (matr2.GetRows() == 3 && matr2.GetColumns() == 5 &&
            matr2[2][2] == 7 && matr2[1][1] == 8 && matr1[1][1] == 6);
}

//  Проверка работы оператора *=
void MultiplicationTest()
{
    Matrix matr1(1, 3);
    matr1[0][0] = 6;
    matr1[0][1] = 5;
    matr1[0][2] = 11;
    Matrix matr2 = (matr1 *= 3);
    
    assert (matr1[0][0] == 18 && matr1[0][1] == 15 && matr1[0][2] == 33 &&
            matr2[0][0] == 18 && matr2[0][1] == 15 && matr2[0][2] == 33);
}

//  Проверка сравнения матриц
void ComparisonTest()
{
    Matrix matr1(4, 4);
    matr1[0][0] = 42;
    Matrix matr2 = matr1;
    bool comparison1 = (matr1 == matr2);
    matr2[1][1] = 24;
    bool comparison2 = (matr1 == matr2);
    Matrix matr3(3, 3);
    Matrix matr4(20, 40);
    bool comparison3 = (matr3 == matr4);
    
    assert (comparison1 && !comparison2 && !comparison3);
}

//  Проверка сложения матриц
void AdditionTest()
{
    Matrix matr1(2, 2);
    Matrix matr2(2, 2);
    
    matr1[0][0] = 3;
    matr1[0][1] = 4;
    matr1[1][0] = 5;
    matr1[1][1] = 6;
    
    matr2[0][0] = -2;
    matr2[0][1] = 4;
    matr2[1][0] = 0;
    matr2[1][1] = 120;
    
    Matrix matr_sum = matr1 + matr2 + matr2;
    
    assert (matr_sum[0][0] == -1 && matr_sum[0][1] == 12 &&
            matr_sum[1][0] == 5 && matr_sum[1][1] == 246);
}

//  Проверка сложения матриц разных размеров
void BadAdditionTest()
{
    Matrix matr1(4, 4);
    Matrix matr2(4, 2);
    int total_errors = 0;
    try 
    {
        matr1 + matr2;
    }
    catch(std::invalid_argument)
    {
        total_errors++;
    }
    try 
    {
        matr2 + matr1;
    }
    catch(std::invalid_argument)
    {
        total_errors++;
    }
    
    assert (total_errors == 2);
}

//  Проверка вывода матрицы 
void OstreamTest()
{
    Matrix matr(2, 3);
    std::ostringstream out;
    matr[0][0] = 1;
    matr[0][1] = 2;
    matr[1][0] = 3;
    matr[1][1] = 4;
    out << matr;
    std::string out_str = out.str();
    
    assert (out_str == "1 2 0 \n3 4 0 \n");
}

//  Тест на матрицу 1х1
void OneByOneTest()
{
    Matrix matr1(1, 1);
    Matrix matr2(1, 1);
    matr1[0][0] = 5;
    matr2[0][0] = 7;
    
    int total_errors = 0;
    try 
    {
        matr1[1][0] = 0;
    }
    catch(std::out_of_range)
    {
        total_errors++;
    }
    try 
    {
        matr1[0][1] = 0;
    }
    catch(std::out_of_range)
    {
        total_errors++;
    }
    assert (total_errors == 2);
    
    std::ostringstream out;
    out << matr1 + (matr2 *= -1);
    std::string out_str = out.str();
    
    assert (out_str == "-2 \n" && matr2[0][0] == -7);
}

//  Тест на матрицы 1хn и nx1
void VectorMatrixTest()
{
    Matrix row1(1, 3);
    Matrix row2(1, 3);
    
    row1[0][0] = 0;
    row1[0][1] = 1;
    row1[0][2] = 2;
    
    row2[0][0] = 0;
    row2[0][1] = 2;
    row2[0][2] = 4;
    
    assert (row1 + row1 == row2);
    
    Matrix column1(4, 1);
    Matrix column2(4, 1);
    
    int total_errors = 0;
    try 
    {
        column1[0][1] = 0;
    }
    catch(std::out_of_range)
    {
        total_errors++;
    }
    try 
    {
        column1[1][2] = 0;
    }
    catch(std::out_of_range)
    {
        total_errors++;
    }
    assert (total_errors == 2);
    
    column1[0][0] = 2;
    column1[1][0] = 0;
    column1[2][0] = 0;
    column1[3][0] = 1;
    column2 = column1;
    assert(column1 == column2);
    
}

int main()
{
    DimensionsTest();
    IndexationTest();
    OutOfBoundsTest();
    CopyConstructorTest();
    AssignmentTest();
    MultiplicationTest();
    ComparisonTest();
    AdditionTest();
    BadAdditionTest();
    OstreamTest();
    OneByOneTest();
    VectorMatrixTest();
    
    std::cout << "All tests passed!" << std::endl;
}