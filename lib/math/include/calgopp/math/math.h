#pragma once

namespace calgopp::math {

inline double toRadians(double degrees)
{
    return degrees / 57.29577951;
}

inline double toDegrees(double radians)
{
    return radians * 57.29577951;
}

/**
 * Epsilon number approximation.
 * @return Epsilon number.
 */
inline double epsilon()
{
    return 0.0000000000000000000001;
}

/**
 * Euler number approximation.
 * @return Euler number.
 */
inline double euler()
{
    return 2.7182818284590452353602874713526624977572;
}

/**
 * PI number approximation.
 * @return PI number.
 */
inline double pi()
{
    return 3.14159265358979323846;
}

/**
 * Absolute operator.
 * @tparam Type                         Number type.
 * @param number                        Argument.
 * @return Absolute value of argument.
 */
template <typename Type>
Type abs(Type number)
{
    return number < 0 ? -number : number;
}

/**
 * Returns integral part of the number.
 * @tparam Type                         Number type.
 * @param number                        Argument.
 * @return Integral part of the number.
 */
template <typename Type>
Type floor(Type number)
{
    return number < 0 ? -floor(abs(number - 1)) : int(number);
}

/**
 * Returns next integer to number.
 * @tparam Type                         Number type.
 * @param number                        Argument.
 * @return Next integer after number.
 */
template <typename Type>
Type ceil(Type number)
{
    if (int(number) == number)
    {
        return number;
    }
    return number < 0 ? -ceil(abs(number + 1)) : int(number + 1);
}

/**
 * Rounds number to either ceil or floor if floating point part is <0.5.
 * @tparam Type                         Number type.
 * @param number                        Argument.
 * @return Nearest integer.
 */
template <typename Type>
Type round(Type number)
{
    auto flr = floor(number);
    return number - flr < 0.5 ? flr : ceil(number);
}

/**
 * Calculates greatest common divisor of provided numbers.
 * @param a                             First number.
 * @param b                             Second number.
 * @return Greates common divisor.
 */
int gcd(int a, int b);

/**
 * Fraction.
 * Stores fraction of the number as numerator and denominator.
 */
class Fraction
{
public:
    /**
     * Template constructor. Allows to store fraction of any floating type number.
     * @tparam Floating                 Floating number type.
     * @param num                       Number to get fraction.
     */

    Fraction(long double num);

    bool operator()() const { return m_denominator != 0 || m_numerator != 0; }

    bool operator!() const { return m_numerator == 0 && m_denominator == 0; }

    /**
     * Numerator getter.
     * @return Fraction numerator.
     */
    int numerator() const { return m_numerator; }

    /**
     * Denominator getter.
     * @return Fraction denominator.
     */
    int denominator() const { return m_denominator; }

private:
    int m_numerator{};
    int m_denominator{};
};

double root(int number, unsigned int base);

double root(long int number, unsigned int base); // NOLINT

double root(double number, unsigned int base);

double root(int number, int base);

double root(long int number, int base); // NOLINT

double root(double number, int base);

template <typename Number>
double sqrt(Number num)
{
    return root(num, 2);
}

double pow(int number, unsigned int power);

double pow(long int number, unsigned int power); // NOLINT

double pow(double number, unsigned int power);

double pow(int number, int power);

double pow(long int number, int power); // NOLINT

double pow(double number, int power);

double pow(int number, double power);

double pow(long int number, double power); // NOLINT

double pow(double number, double power);

/**
 * Exponential function.
 * @tparam PowerType                            Power type.
 * @param power                                 Euler number power.
 * @return Calculated exponential.
 */
template <typename PowerType>
double exp(PowerType power)
{
    return pow(euler(), power);
}

/**
 * Sine function. Calculates sine for argument.
 * @tparam Number
 * @param num
 * @return
 */
template <typename Number>
double sin(Number num)
{
    double t = num;
    double sine = t;
    for (int a = 1; a < 20; ++a)
    {
        double mult = -num * num / ((2.0 * double(a) + 1.0) * (2.0 * double(a)));
        t *= mult;
        sine += t;
    }
    return sine;
}

/**
 * Cosine function.
 * @tparam Number
 * @param num
 * @return
 */
template <typename Number>
double cos(Number num)
{
    auto shouldBePositive = [num]() -> bool {
        auto degrees = abs(toDegrees(num));
        while (degrees > 360)
        {
            degrees -= 360;
        }
        return (degrees >= 0 && degrees <= 90) || (degrees >= 270 && degrees <= 360);
    };
    auto result = root(1 - pow(sin(num), 2), 2);
    return shouldBePositive() ? result : -result;
}

/**
 * Tangent function.
 * @tparam Number
 * @param num
 * @return
 */
template <typename Number>
double tan(Number num)
{
    auto shouldBePositive = [num]() -> bool {
        auto degrees = abs(toDegrees(num));
        while (degrees > 360)
        {
            degrees -= 360;
        }
        return (degrees >= 0 && degrees <= 90) || (degrees > 180 && degrees <= 270);
    };
    auto result = abs(sin(num) / cos(num));
    return shouldBePositive() ? result : -result;
}

template <typename T>
long double log(const T& argument)
{
    long double token{};
    auto base = double(argument - 1) / double(argument + 1);
    for (unsigned int i = 1; i < 200; i += 2)
    {
        token += (1.0 / double(i)) * pow(base, i);
    }
    return 2 * token;
}

template <typename Number>
double asin(Number num)
{
    bool negate = num < 0;
    auto absNum = abs(num);
    auto a0 = 1.5707288;
    auto a1 = -0.2121144;
    auto a2 = 0.0742610;
    auto a3 = -0.0187293;
    auto ret = ((pi() / 2) - root((1 - absNum), 2) * (a0 + a1 * absNum + a2 * pow(absNum, 2) + a3 * pow(absNum, 3)));
    return negate ? -ret : ret;
}

template <typename Number>
double acos(Number num)
{
    auto absNum = abs(num);
    float negate = float(num < 0);
    double ret = -0.0187293;
    ret = ret * absNum;
    ret = ret + 0.0742610;
    ret = ret * absNum;
    ret = ret - 0.2121144;
    ret = ret * absNum;
    ret = ret + 1.5707288;
    ret = ret * root(1.0 - absNum, 2);
    ret = ret - 2 * negate * ret;
    return negate * 3.14159265358979 + ret;
}

template <typename Number>
double atan(Number num)
{
    if (abs(num) <= 1)
    {
        return asin(2 * num / (1 + pow(num, 2))) / 2;
    }
    bool negate = num < -1;
    auto numPowered = pow(num, 2);
    auto ret = acos((1 - numPowered) / (1 + numPowered)) / 2;
    return negate ? -ret : ret;
}

} // namespace calgopp::math
