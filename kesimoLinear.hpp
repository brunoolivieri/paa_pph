#ifndef KESIMOLINEAR_HPP_INCLUDED
#define KESIMOLINEAR_HPP_INCLUDED

#include <vector>
#include "PPH.hpp"

std::vector<parOrdenado> partition(std::vector<parOrdenado> &val, float chave);

float selectionByMedianOfMedians(const vector<parOrdenado> values,unsigned pos);

#endif // KESIMOLINEAR_HPP_INCLUDED
