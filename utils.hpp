//
// Created by Артем Устинов
//

#ifndef MAT_LOG_UTILS_HPP
#define MAT_LOG_UTILS_HPP

#include <cmath>

const int objectNumbers = 9;
const int propertyNumbers = 4;
const int N_SQRT = sqrt(objectNumbers);
const int K = 36;// от 0 до objectNumbers * propertyNumbers
const int LOG_N = std::ceil(std::log2(objectNumbers)); //ceil наим целое .. бит свойства

const int N_VAR = 144; // objectNumbers * propertyNumbers * LOG_N
char var[N_VAR];



#endif //MAT_LOG_UTILS_HPP
