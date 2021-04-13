#include "bigint.hpp"

//  Конструктор по умолчанию
BigInt::BigInt()
{
    digits = nullptr;
    num_len = 0;
    sign = '+';
}

//  Конструктор из строки
BigInt::BigInt(const std::string &str_num)
{
    if (str_num[0] == '-')
    {
        num_len = str_num.length() - 1;
        sign = '-';
        digits = new uint16_t[num_len];
        for (size_t i = 0; i < num_len; i++)
            digits[i] = static_cast<uint16_t>(str_num[num_len - i]) - '0';
    }
    else
    {
        num_len = str_num.length();
        sign = '+';
        digits = new uint16_t[num_len];
        for (size_t i = 0; i <  num_len; i++)
            digits[i] = static_cast<uint16_t>(str_num[num_len - i - 1]) - '0';
    }
    //  Меняем знак "-0" на + (для удобства)
    if (str_num == "-0")
        sign = '+';
}

//  Конструктор из числа
BigInt::BigInt(int32_t big_num)
{
    sign = (big_num >= 0) ? '+' : '-';
    size_t big_num_len = 0;
    big_num = abs(big_num);
    int32_t copied_num = big_num;
    //  Смотрим, сколько цифр
    if (copied_num == 0)
        big_num_len = 1;
    else
        while (copied_num > 0)
        {
            copied_num /= 10;
            big_num_len++;
        }
    num_len = big_num_len;
    digits = new uint16_t[num_len];
    for (size_t i = 0; i < num_len; i++)
    {
        digits[i] = (big_num % 10);
        big_num = big_num / 10;
    }
}


//  Конструктор копирования
BigInt::BigInt(const BigInt &other)
{
    num_len = other.num_len;
    sign = other.sign;
    digits = new uint16_t[num_len];
    for (size_t i = 0; i < num_len; i++)
        digits[i] = other.digits[i];
}

//  Конструктор перемещения
BigInt::BigInt(BigInt &&other): digits(other.digits), num_len(other.num_len), sign(other.sign)
{
    other.digits = nullptr;
}

//  Оператор присваивания копированием
BigInt &BigInt::operator=(const BigInt &other)
{
    if (&other == this)
        return *this;
    num_len = other.num_len;
    sign = other.sign;
    delete []digits;
    digits = new uint16_t[num_len];
    for (size_t i = 0; i < num_len; i++)
        digits[i] = other.digits[i];
    return *this;
}

//  Оператор присваивания перемещением
BigInt &BigInt::operator=(BigInt&& other)
{
    if (&other == this)
        return *this;
    if (digits)
        delete []digits;
    digits = other.digits;
    num_len = other.num_len;
    sign = other.sign;
    other.digits = nullptr;
    return *this;
}

//  Оператор сравнения ==
bool BigInt::operator==(const BigInt &other)
{
    if (num_len != other.num_len || sign != other.sign)
        return false;
    for (size_t i = 0; i < num_len; i++)
        if (digits[i] != other.digits[i])
            return false;
    return true;
}

//  Оператор сравнения !=
bool BigInt::operator!=(const BigInt &other)
{
    return !(*this == other);
}

//  Оператор сравнения >
bool BigInt::operator>(const BigInt &other)
{
    //  Разные знаки
    if (sign != other.sign)
        return (sign == '+');
    //  Одинаковые знаки
    else
    {
        //  Разное кол-во цифр
        if (num_len > other.num_len)
            return (sign == '+');
        else if (num_len < other.num_len)
            return (sign == '-');
        //  Одинаковое кол-во цифр
        else
        {
            for (size_t i = 0; i < num_len; i++)
            {
                if (digits[num_len - i - 1] > other.digits[num_len - i - 1])
                    return (sign == '+');
                else if (digits[num_len - i - 1] < other.digits[num_len - i - 1])
                    return (sign == '-');
            }
            return false;
        }
    }
}

//  Оператор сравнения <
bool BigInt::operator<(const BigInt &other)
{
    return !(*this == other || *this > other);
}

//  Оператор сравнения >=
bool BigInt::operator>=(const BigInt &other)
{
    return !(*this < other);
}

//  Оператор сравнения <=
bool BigInt::operator<=(const BigInt &other)
{
    return !(*this > other);
}

//  Унарный минус
BigInt operator-(const BigInt &to_inverse)
{
    BigInt inversed = to_inverse;
    //  Если число 0 - не меняем знак
    if (inversed.num_len != 1 || inversed.digits[0] != 0)
        inversed.sign = (to_inverse.sign == '+') ? '-' : '+';
    return inversed;
}

//  Оператор сложения
BigInt BigInt::operator+(const BigInt &other)
{

    BigInt to_return = 0;
    BigInt to_add = 0;
    uint16_t carry_over = 0;
    //  Складываем однознаковые числа
    if (this->sign == other.sign)
    {
        to_return = (num_len > other.num_len) ? *this : other;
        to_add = (num_len > other.num_len) ? other : *this;
        for (size_t i = 0; i < to_return.num_len; i++)
        {
            if (i < to_add.num_len)
                to_return.digits[i] = to_return.digits[i] + to_add.digits[i];
            to_return.digits[i] += carry_over;
            carry_over = to_return.digits[i] / 10;
            to_return.digits[i] %= 10;
        }
        //  Если переполнили наши разряды - добавляем новый
        if (carry_over > 0)
        {
            uint16_t *extend = new uint16_t[to_return.num_len + 1];
            for (size_t i = 0; i < to_return.num_len; i++)
                extend[i] = to_return.digits[i];
            extend[to_return.num_len] = carry_over;
            delete []to_return.digits;
            to_return.digits = extend;
            to_return.num_len += 1;
        }
    }
    //  Складываем числа с разными знаками
    else
    {
        //  Выделяем наибольшее по модулю число - из него вычитаем
        to_return = *this;
        to_return.sign = '+';
        to_add = other;
        to_add.sign = '+';
        if (to_return > to_add)
        {
            to_return = *this;
            to_add = other;
        }
        else
        {
            to_return = other;
            to_add = *this;
        }
        //  Вычитаем
        for (size_t i = 0; i < to_return.num_len; i++)
        {
            int16_t subtract;
            if (i < to_add.num_len)
                subtract = to_return.digits[i] - to_add.digits[i];
            else
                subtract = to_return.digits[i];
            subtract += carry_over;
            carry_over = (subtract < 0) ? -1 : 0;
            to_return.digits[i] = (subtract < 0) ? subtract + 10 : subtract;
        }
        //  Удаляем ведущие нули
        to_return.CutLeadingZeros();
    }
    return to_return;
}

BigInt BigInt::operator+(int32_t add)
{
    BigInt tmp = add;
    return *this + tmp;
}

//  Оператор вычитания
BigInt BigInt::operator-(const BigInt &other)
{
    return *this + (-other);
}

BigInt BigInt::operator-(int32_t subtr)
{
    BigInt tmp = subtr;
    return *this + (-subtr);
}

//  Оператор умножения
BigInt BigInt::operator*(const BigInt &other)
{
    BigInt to_return = 0;
    uint16_t carry_over = 0;
    //  Цикл по цифрам второго множителя
    for (size_t j = 0; j < other.num_len; j++)
    {
        BigInt accumulate = *this;
        accumulate.sign = '+';
        //  Цикл по цифрам первого множителя
        for (size_t i = 0; i < this->num_len; i++)
        {
            accumulate.digits[i] = this->digits[i] * other.digits[j];
            accumulate.digits[i] += carry_over;
            carry_over = accumulate.digits[i] / 10;
            accumulate.digits[i] %= 10;
        }
        //  Если переполнили наши разряды - добавляем новый
        if (carry_over > 0)
        {
            uint16_t *extend = new uint16_t[accumulate.num_len + 1];
            for (size_t i = 0; i < accumulate.num_len; i++)
                extend[i] = accumulate.digits[i];
            extend[accumulate.num_len] = carry_over;
            delete []accumulate.digits;
            accumulate.digits = extend;
            accumulate.num_len += 1;
            carry_over = 0;
        }
        accumulate.ShiftLeft(j);
        to_return = to_return + accumulate;
        delete []accumulate.digits;
        accumulate.digits = nullptr;
    }
    to_return.CutLeadingZeros();
    if (this->sign == other.sign)
        return to_return;
    else
        return (-to_return);
}

BigInt BigInt::operator*(int32_t factor)
{
    BigInt tmp = factor;
    return (*this) * tmp;
}

//  Оператор вывода
std::ostream &operator<<(std::ostream &stream, const BigInt &to_output)
{
    if (to_output.sign == '-')
        stream << '-';
    for (size_t i = 0; i < to_output.num_len; i++)
    {
        stream << to_output.digits[to_output.num_len - i - 1];
    }
    return stream;
}

//  Деструктор
BigInt::~BigInt()
{
    if (digits)
        delete []digits;
}

//  Добавление нулей в конец числа
void BigInt::ShiftLeft(size_t k)
{
    uint16_t *reserve = digits;
    num_len += k;
    digits = new uint16_t[num_len];
    for (size_t i = 0; i < k; i++)
        digits[i] = 0;
    for (size_t i = k; i < num_len; i++)
        digits[i] = reserve[i - k];
    delete []reserve;

}

//  Удаление ведущих нулей
void BigInt::CutLeadingZeros()
{
    size_t leading_zeros = 0;
    for (size_t i = 0; i < num_len; i++)
    {
        if (digits[num_len - i - 1] == 0)
            leading_zeros++;
        else
            break;
    }
    if (leading_zeros > 0 && leading_zeros != num_len)
    {
        size_t new_len = num_len - leading_zeros;
        uint16_t *shrink = new uint16_t[new_len];
        for (size_t i = 0; i < new_len; i++)
            shrink[i] = digits[i];
        delete []digits;
        digits = shrink;
        num_len = new_len;
    }
    else if (leading_zeros > 0)
    {
        *this = 0;
        sign = '+';
    }
}


//  Геттеры и другие функции для тестов
std::string BigInt::GetStringView()
{
    std::string to_return = "";
    if (sign == '-')
        to_return += '-';
    for (size_t i = 0; i < num_len; i++)
        to_return += digits[num_len - i - 1] + '0';
    return to_return;
}

bool BigInt::IsEmpty()
{
    return (digits == nullptr);
}

size_t BigInt::GetLength()
{
    return num_len;
}

char BigInt::GetSign()
{
    return sign;
}