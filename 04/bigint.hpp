#pragma once
#include <iostream>
#include <string>

class BigInt
{
    uint16_t *digits = nullptr;
    size_t num_len = 0;
    char sign = '+';
public:
    BigInt();
    BigInt(const std::string&);
    BigInt(int32_t);
    BigInt(const BigInt&);
    BigInt(BigInt&&);
    BigInt &operator=(const BigInt&);
    BigInt &operator=(BigInt&&);

    bool operator==(const BigInt&);
    bool operator!=(const BigInt&);
    bool operator>(const BigInt&);
    bool operator<(const BigInt&);
    bool operator>=(const BigInt&);
    bool operator<=(const BigInt&);

    friend BigInt operator-(const BigInt&);
    BigInt operator+(const BigInt&);
    BigInt operator+(int32_t);
    BigInt operator-(const BigInt&);
    BigInt operator-(int32_t);
    BigInt operator*(const BigInt&);
    BigInt operator*(int32_t);

    friend std::ostream &operator<<(std::ostream&, const BigInt&);

    ~BigInt();

    void ShiftLeft(size_t);
    void CutLeadingZeros();

    std::string GetStringView();
    bool IsEmpty();
    size_t GetLength();
    char GetSign();

};