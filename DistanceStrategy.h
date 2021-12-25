//
// Created by 蒋希文 on 2021/6/24.
//

#ifndef BK_CLASSIC_DISTANCESTRATEGY_H
#define BK_CLASSIC_DISTANCESTRATEGY_H

#include "Types.h"

class DistanceStrategy {
public:
    virtual double calculate(const LocationType &location1, const LocationType &location2) = 0;
};

#endif //BK_CLASSIC_DISTANCESTRATEGY_H
