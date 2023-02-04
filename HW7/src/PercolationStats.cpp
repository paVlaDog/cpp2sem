#include "PercolationStats.h"

#include "Percolation.h"

#include <random> // для std::random_device и std::mt19937

PercolationStats::PercolationStats(size_t dimension, size_t trials)
    : m_dimension(dimension)
    , m_trials(trials)
{
    execute();
}

double PercolationStats::get_mean() const
{
    return m_mean;
}

double PercolationStats::get_standard_deviation() const
{
    return m_standard_deviation;
}

double PercolationStats::get_confidence_low() const
{
    return m_mean - 1.96 * m_standard_deviation / sqrt(m_trials);
}

double PercolationStats::get_confidence_high() const
{
    return m_mean + 1.96 * m_standard_deviation / sqrt(m_trials);
}

void PercolationStats::execute()
{
    std::random_device rd;
    std::mt19937 mersenne(rd());
    std::uniform_int_distribution<> random_gen(0, m_dimension - 1);
    for (size_t i = 0; i < m_trials; i++) {
        Percolation per = Percolation(m_dimension);
        while (!per.has_percolation()) {
            per.open(random_gen(mersenne), random_gen(mersenne));
        }
        m_result.push_back(static_cast<double>(per.get_numbet_of_open_cells()) / (m_dimension * m_dimension));
        m_mean += m_result[i] / m_trials;
    }
    for (const auto element : m_result) {
        m_standard_deviation += (m_mean - element) * (m_mean - element);
    }
    m_standard_deviation = sqrt(m_standard_deviation / (m_trials - 1));
}
