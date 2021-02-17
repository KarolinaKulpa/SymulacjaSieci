#ifndef SIEC_TYPES_HPP
#define SIEC_TYPES_HPP

#include <cstdlib>
#include <functional>
#include<iostream>

using ElementID = int;
using Time = int;
using TimeOffset = int;
using ProbabilityGenerator = std::function<double()>;

#endif //SIEC_TYPES_HPP
