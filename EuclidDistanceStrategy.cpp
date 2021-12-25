//
// Created by 蒋希文 on 2021/6/24.
//

#include <cmath>
#include "EuclidDistanceStrategy.h"

double EuclidDistanceStrategy::calculate(const LocationType &location1, const LocationType &location2) {
    return std::sqrt(std::pow(location1.first - location2.first, 2) +
                         std::pow(location1.second - location2.second, 2)
                         );
}
