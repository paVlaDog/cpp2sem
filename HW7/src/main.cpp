#include "Percolation.h"
#include "PercolationStats.h"

#include <iostream>

int main()
{
    const size_t dimension = 10;
    const size_t trials = 100;
    PercolationStats percolation_stats(dimension, trials);
    std::cout << "mean = " << percolation_stats.get_mean() << std::endl;
    std::cout << "deviation = " << percolation_stats.get_standard_deviation() << std::endl;
    std::cout << "confidence_low = " << percolation_stats.get_confidence_low() << std::endl;
    std::cout << "confidence_high = " << percolation_stats.get_confidence_high() << std::endl;
    return 0;
}
