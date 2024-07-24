#include "math_utils.h"
#include <cmath>

double MathUtils::normalCDF(double value) {
    return 0.5 * std::erfc(-value * M_SQRT1_2);
}