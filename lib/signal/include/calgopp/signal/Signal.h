#pragma once

#include "calgopp/types/Peak.h"
#include "calgopp/types/Point.h"

#include <etl/vector.h>

#include <cstdint>
#include <utility>

namespace calgopp::signal {

/**
 * Signal representation.
 */
class Signal
{
public:
    /**
     * Default constructor.
     */
    Signal() = default;

    /**
     * Copying constructor
     * @param other                 Other signal to be copied
     */
    Signal(const Signal& other) = default;

    /**
     * Moving constructor
     * @param other                 Other signal to be moved
     */
    Signal(Signal&& other) noexcept = default;

    Signal(etl::vector<types::Point, MAX_SIGNAL_SIZE>::iterator begin,
           etl::vector<types::Point, MAX_SIGNAL_SIZE>::iterator end)
        : m_points(begin, end)
    {
    }

    /**
     * Copying assignment operator
     * @param other                 Other signal to be copied
     * @return Copied signal
     */
    Signal& operator=(const Signal& other) = default;

    /**
     * Moving assignment operator
     * @param other                 Other signal to be moved
     * @return Moved signal
     */
    Signal& operator=(Signal&& other) noexcept = default;

    /**
     * Template constructor that accepts STL containers
     * @tparam InputContainer       Type of container
     * @param values                Values to populate signal
     */
    template <typename InputContainer>
    Signal(const InputContainer& values)
        : Signal(values.data(), values.size())
    {
    }

    /**
     * Template constructor that accepts C-style arrays
     * @tparam Type                 Type of array elements
     * @param values                Values to populate signal
     * @param size                  Size of array
     */
    template <typename Type>
    Signal(const Type* values, std::uint32_t size)
    {
        for (std::uint32_t i = 0; i < size; i++)
        {
            m_points.push_back(types::Point{i, values[i]});
        }
    }

    template <typename Type>
    Signal(const Type* reals, const Type* imags, std::uint32_t size)
    {
        for (std::uint32_t i = 0; i < size; i++)
        {
            m_points.push_back(types::Point{i, {reals[i], imags[i]}});
        }
    }

    /**
     * Creates signal from container of points
     * @param points                Signal points
     */
    Signal(etl::vector<types::Point, MAX_SIGNAL_SIZE> points)
        : m_points(points)
    {
    }

    /**
     * Creates signal from C-style array of Points objects
     * @param points
     * @param size
     */
    Signal(const types::Point* points, std::uint32_t size);

    /**
     * Creates signal from C-style array of Points objects
     * @param points
     * @param size
     */
    Signal(const types::Peak* peaks, std::uint32_t size);

    /**
     * Default destructor
     */
    ~Signal() = default;

    /**
     * Check if signal is empty (doesn't have any points)
     * @return True if signal is empty, false otherwise
     */
    bool empty() const { return m_points.empty(); }

    /**
     * Bool operator. Checks if signal is not empty.
     * @return True if signal is not empty, false otherwise.
     */
    operator bool() const { return !empty(); }

    /**
     * Appending operator. Allows quick addition of new points.
     * @param point                     Point to be added.
     */
    void operator+=(const types::Point& point);

    /**
     * Appending operator. Allows to append another signal.
     * @param signal                    Signal to append.
     */
    void operator+=(Signal& signal);

    /**
     * Decrement operator. Removes last point from signal. Throws const char* in case of empty signal.
     */
    void operator--();

    /**
     * Append method. Appends new point to end of the signal.
     * @param point                     Point to append.
     */
    void append(const types::Point& point);

    /**
     * Remove method. Removes point with provided index. Throws const char* on invalid index.
     * @param index                     Index of point to remove.
     */
    void remove(std::uint32_t index);

    types::Point get(std::uint32_t index) const;

    /**
     * Index operator. Accesses reference to item at index. Throws const char* on invalid index.
     * @param index                     Index of point to access.
     * @return Returns reference to target point.
     */
    types::Point& operator[](std::uint32_t index);

    /**
     * Returns size of the signal.
     * @return Size of the signal.
     */
    std::uint32_t size() const { return m_points.size(); }

    /**
     * Finds peaks in signal.
     * @param type                      Type of peaks to find
     * @param height                    Height threshold. Peaks lower than threshold are skipped.
     * @param distance                  Distance threshold between two neighbour peaks.
     *                                  Smaller (for highs) / greater (for lows) peaks are being dropped until
     *                                  the distance requirement is met.
     * @return Container with peaks.
     */
    etl::vector<types::Peak, MAX_SIGNAL_SIZE>
    peaks(types::PeakType type = types::PeakType::eHigh, long double height = 0, std::uint32_t distance = 1) const;

    /**
     * Begin iterator.
     * @return Iterator to the first element of signal.
     */
    etl::vector<types::Point, MAX_SIGNAL_SIZE>::iterator begin() { return m_points.begin(); }

    /**
     * End iterator.
     * @return Iterator to 1 place after last element.
     */
    etl::vector<types::Point, MAX_SIGNAL_SIZE>::iterator end() { return m_points.end(); }

    /**
     * Begin iterator.
     * @return Iterator to the first element of signal.
     */
    etl::vector<types::Point, MAX_SIGNAL_SIZE>::const_iterator begin() const { return m_points.begin(); }

    /**
     * End iterator.
     * @return Iterator to 1 place after last element.
     */
    etl::vector<types::Point, MAX_SIGNAL_SIZE>::const_iterator end() const { return m_points.end(); }

    std::uint32_t index(const types::Point& point) const;

private:
    etl::vector<types::Point, MAX_SIGNAL_SIZE> m_points;
};

} // namespace calgopp::signal
