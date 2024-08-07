#pragma once

#include "calgopp/types/Peak.h"
#include "calgopp/types/Point.h"

#include <etl/vector.h>

#include <array>
#include <chrono>
#include <cmath>
#include <cstdint>
#include <deque>
#include <filesystem>
#include <functional>
#include <iomanip>
#include <iostream>
#include <optional>
#include <queue>
#include <string>
#include <tuple>
#include <variant>
#include <vector>

using namespace calgopp;

namespace test {

enum class Transform
{
    eFastFourier
};

using ContainerVariant = std::variant<std::vector<double>,
                                      std::vector<int>,
                                      std::vector<float>,
                                      std::array<double, 1000>,
                                      std::array<int, 1000>,
                                      std::array<float, 1000>>;

template <typename InputType>
class CStyleArrayVariant // NOLINT
{
public:
    CStyleArrayVariant(std::uint32_t size)
        : m_size(size)
        , m_array(new InputType[m_size])
    {
        for (std::uint32_t i = 0; i < m_size; i++)
        {
            m_array[i] = 2 * i;
        }
    }

    operator InputType*() const { return m_array; }

    ~CStyleArrayVariant() { delete[] m_array; }

private:
    std::uint32_t m_size{};
    InputType* m_array{nullptr};
};

template <typename T>
std::vector<T> vectorInput()
{
    std::vector<T> token(1000);
    for (std::uint32_t i = 0; i < 1000; i++)
    {
        token[i] = 2 * i;
    }
    return token;
}

template <typename T>
std::array<T, 1000> arrayInput()
{
    std::array<T, 1000> token{};
    for (std::uint32_t i = 0; i < 1000; i++)
    {
        token[i] = 2 * i;
    }
    return token;
}

template <typename T>
void addData(etl::vector<T, 100000>& container, std::uint32_t amount)
{
    for (std::uint32_t i = 0; i < amount; i++)
    {
        container.append(2 * i);
    }
}

int testDataset(const std::filesystem::path& scriptPath,
                const std::filesystem::path& outputPath,
                std::uint32_t size,
                double height = 0,
                double distance = 1,
                types::PeakType type = types::PeakType::eHigh);

std::vector<calgopp::types::Point> getRawDataset(const std::filesystem::path& datasetPath);

std::vector<calgopp::types::Peak> getPeaks(const std::filesystem::path& datasetPath);

std::vector<calgopp::types::Complex> getTransformedDataset(const std::filesystem::path& datasetPath,
                                                           Transform transform = Transform::eFastFourier);

inline std::uint64_t benchmark(const std::function<void()>& function)
{
    auto start =
        std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::system_clock::now().time_since_epoch());
    function();
    return (std::chrono::duration_cast<std::chrono::nanoseconds>(std::chrono::system_clock::now().time_since_epoch()) -
            start)
        .count();
}

template <typename T>
bool almostEqual(const T& var1, const T& var2, double threshold = 0.0000001)
{
    double dif = std::abs(var1 - var2);
    if (dif == 0)
    {
        return true;
    }
    bool diffGreaterThanThreshold = dif >= threshold;
    if (diffGreaterThanThreshold)
    {
        std::cout << std::setprecision(20) << "Variables don't equal. Var1: " << var1 << ", var2: " << var2
                  << ", difference: " << dif << std::endl;
    }
    return !diffGreaterThanThreshold;
}

bool almostEqual(const types::Complex& var1, const types::Complex& var2, double threshold = 0.0000001);

} // namespace test
