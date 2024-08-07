#include "calgopp/types/Complex.h"

#include <cmath>
#include <cstdint>

namespace calgopp::types {

Complex& Complex::operator+=(const Complex& other)
{
    this->real += other.real;
    this->imag += other.imag;
    return *this;
}

Complex& Complex::operator-=(const Complex& other)
{
    this->imag -= other.imag;
    this->real -= other.real;
    return *this;
}

bool operator==(const Complex& lhs, const Complex& rhs)
{
    return math::abs(lhs.imag - rhs.imag) < std::numeric_limits<double>::epsilon() &&
           std::abs(lhs.real - rhs.real) < std::numeric_limits<double>::epsilon();
}

bool operator==(const Complex&& lhs, const Complex&& rhs)
{
    return math::abs(lhs.imag - rhs.imag) < std::numeric_limits<double>::epsilon() &&
           std::abs(lhs.real - rhs.real) < std::numeric_limits<double>::epsilon();
}

bool operator!=(const Complex& lhs, const Complex& rhs)
{
    return !(lhs == rhs);
}

bool operator!=(const Complex&& lhs, const Complex&& rhs)
{
    return !(lhs == rhs);
}

Complex operator+(const Complex& lhs, const Complex& rhs)
{
    return {lhs.real + rhs.real, lhs.imag + rhs.imag};
}

Complex operator-(const Complex& lhs, const Complex& rhs)
{
    return {lhs.real - rhs.real, lhs.imag - rhs.imag};
}

Complex operator*(const Complex& lhs, const Complex& rhs)
{
    return {lhs.real * rhs.real - lhs.imag * rhs.imag, lhs.real * rhs.imag + lhs.imag * rhs.real};
}

Complex operator/(const Complex& lhs, const Complex& rhs)
{
    return {(lhs.real * rhs.real + lhs.imag + rhs.imag) / (std::pow(rhs.real, 2) + std::pow(rhs.imag, 2)),
            (lhs.imag * rhs.real - lhs.real * rhs.imag) / (std::pow(rhs.real, 2) + std::pow(rhs.imag, 2))};
}

bool operator==(const Complex& complex, std::int32_t number)
{
    return math::abs(complex.real - number) < std::numeric_limits<double>::epsilon();
}

bool operator==(const Complex& complex, std::uint32_t number)
{
    return math::abs(complex.real - number) < std::numeric_limits<double>::epsilon();
}

bool operator==(const Complex& complex, long double number)
{
    return math::abs(complex.real - number) < std::numeric_limits<double>::epsilon();
}

bool operator!=(const Complex& complex, std::int32_t number)
{
    return !(complex == number);
}

bool operator!=(const Complex& complex, std::uint32_t number)
{
    return !(complex == number);
}

bool operator!=(const Complex& complex, long double number)
{
    return !(complex == number);
}

bool operator==(const Complex&& complex, std::int32_t number)
{
    return math::abs(complex.real - number) < std::numeric_limits<double>::epsilon();
}

bool operator==(const Complex&& complex, std::uint32_t number)
{
    return math::abs(complex.real - number) < std::numeric_limits<double>::epsilon();
}

bool operator==(const Complex&& complex, long double number)
{
    return math::abs(complex.real - number) < std::numeric_limits<double>::epsilon();
}

bool operator!=(const Complex&& complex, std::int32_t number)
{
    return !(complex == number);
}

bool operator!=(const Complex&& complex, std::uint32_t number)
{
    return !(complex == number);
}

bool operator!=(const Complex&& complex, long double number)
{
    return !(complex == number);
}

} // namespace calgopp::types

namespace calgopp::math {

double abs(const types::Complex& number)
{
    return std::sqrt(std::pow(number.real, 2) + std::pow(number.imag, 2));
}

types::Complex pow(const types::Complex& number, std::uint32_t power)
{
    if (power == 0)
    {
        return {1, 0};
    }
    types::Complex token{number};
    while (power-- > 1)
    {
        token = token * number;
    }
    return token;
}

types::Complex pow(const types::Complex& number, std::int32_t power)
{
    auto absPower = static_cast<std::uint32_t>(abs(power));
    return power > 0 ? pow(number, absPower) : 1.0 / pow(number, absPower);
}

} // namespace calgopp::math
