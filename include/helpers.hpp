#ifndef UNTITLED3_HELPERS_HPP
#define UNTITLED3_HELPERS_HPP

#include <random>
#include <cstdlib>
#include <functional>
#include <memory>
#include "types.hpp"
#include "storage_types.hpp"

extern std::random_device rd;
extern std::mt19937 rng;

extern double default_probability_generator();

extern ProbabilityGenerator probability_generator;


#endif //UNTITLED3_HELPERS_HPP
