#include "Percolation.h"

Percolation::Percolation(size_t dimension)
    : m_is_open_is_full(dimension, std::vector<std::pair<bool, bool>>(dimension, std::make_pair(false, false)))
    , m_size(dimension)
    , m_count_open(0)
    , m_is_percolation(false)
{
}

void Percolation::check_and_fill(size_t row, size_t column)
{
    if (column < m_size && row < m_size && is_open(row, column) && !is_full(row, column)) {
        full(row, column);
    }
}

bool Percolation::check_full(size_t row, size_t column) const
{
    return column < m_size && row < m_size && is_full(row, column);
}

void Percolation::open(size_t row, size_t column)
{
    if (!m_is_open_is_full[row][column].first) {
        m_is_open_is_full[row][column].first = true;
        if (row == 0 || check_full(row + 1, column) || check_full(row - 1, column) ||
            check_full(row, column + 1) || check_full(row, column - 1)) {
            full(row, column);
        }
        m_count_open++;
    }
}

bool Percolation::is_open(size_t row, size_t column) const
{
    return m_is_open_is_full[row][column].first;
}

void Percolation::full(size_t row, size_t column)
{
    m_is_open_is_full[row][column].second = true;
    if (row == m_size - 1) {
        m_is_percolation = true;
    }
    check_and_fill(row + 1, column);
    check_and_fill(row - 1, column);
    check_and_fill(row, column + 1);
    check_and_fill(row, column - 1);
}

bool Percolation::is_full(size_t row, size_t column) const
{
    return m_is_open_is_full[row][column].second;
}

size_t Percolation::get_numbet_of_open_cells() const
{
    return m_count_open;
}

bool Percolation::has_percolation() const
{
    return m_is_percolation;
}
