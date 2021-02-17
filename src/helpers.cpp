#include "helpers.hpp"
#include <random>

std::random_device rd;
std::mt19937 rng(rd());

std::function<double()> probability_generator = default_probability_generator;


double default_probability_generator() {
    return std::generate_canonical<double, 10>(rng);
}
