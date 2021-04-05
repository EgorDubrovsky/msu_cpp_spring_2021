#pragma once
#include <iostream>

class Matrix
{
	size_t rows;
	size_t columns;
	int32_t *data = nullptr;
	
	class ProxyRow
    {
        int32_t *data = nullptr;
		size_t size;
    public:
        ProxyRow(int32_t*, size_t);
		~ProxyRow();
        int32_t& operator[](size_t);
    };

public:
	Matrix(size_t, size_t);
	Matrix(const Matrix&);
	~Matrix();
	Matrix &operator=(const Matrix&);
	Matrix &operator*=(const int32_t);
	ProxyRow operator[](size_t);
	bool operator==(const Matrix&);
	bool operator!=(const Matrix&);
	Matrix operator+(const Matrix&);
	friend std::ostream &operator<<(std::ostream&, const Matrix&);
	size_t GetRows() const;
	size_t GetColumns() const;
};