#include "matrix.hpp"

Matrix::Matrix(size_t rows, size_t columns)
{
    this->rows = rows;
    this->columns = columns;
    data = new int32_t[rows * columns];
    for (size_t i = 0; i < rows * columns; i++)
        data[i] = 0;
}

Matrix::Matrix(const Matrix &other)
{
    this->rows = other.rows;
    this->columns = other.columns;
    this->data = new int32_t[rows * columns];
    if (other.data)
        for (size_t i = 0; i < rows * columns; i++)
            this->data[i] = other.data[i];
}

Matrix::~Matrix()
{
    if (data)
        delete []data;
}

Matrix &Matrix::operator=(const Matrix &other)
{
    this->rows = other.rows;
    this->columns = other.columns;
    if (data)
        delete []data;
    data = new int32_t[rows * columns];
    if (other.data)
        for (size_t i = 0; i < rows * columns; i++)
            this->data[i] = other.data[i];
    return *this;
}

Matrix &Matrix::operator*=(const int32_t multiplier)
{
    if (data)
        for (size_t i = 0; i < rows * columns; i++)
            this->data[i] *= multiplier;
    return *this;
}

Matrix::ProxyRow Matrix::operator[](size_t i)
{
    if (i < rows)
    {
        ProxyRow proxy(data + i * columns, columns);
        return proxy;
    }
    else
    {
        throw std::out_of_range("");
    }
}

bool Matrix::operator==(const Matrix &other)
{
    if (rows != other.rows || columns != other.columns)
        return false;
    else
        for (size_t i = 0; i < rows * columns; i++)
            if (data[i] != other.data[i])
                return false;
    return true;
}

Matrix Matrix::operator+(const Matrix &other)
{
    if (rows == other.rows && columns == other.columns)
    {
        Matrix help(rows, columns);
        for (size_t i = 0; i < rows * columns; i++)
            help.data[i] = data[i] + other.data[i];
        return help;
    }
    else
        throw std::invalid_argument("");
}

std::ostream &operator<<(std::ostream &stream, const Matrix &to_output)
{
    for (size_t i = 0; i < to_output.rows; i++)
    {
        for (size_t j = 0; j < to_output.columns; j++)
            stream << to_output.data[i * to_output.columns + j] << " ";
        stream << "\n";
    }
    return stream;
}

size_t Matrix::GetRows() const
{
    return rows;
}

size_t Matrix::GetColumns() const
{
    return columns;
}


//  Методы ProxyRow
Matrix::ProxyRow::ProxyRow(int32_t *row_data, size_t row_size)
{
    this->data = row_data;
    this->size = row_size;
}

Matrix::ProxyRow::~ProxyRow()
{
    
}

int32_t &Matrix::ProxyRow::operator[](size_t j)
{
    if (j < size)
        return data[j];
    else
        throw std::out_of_range("");
}