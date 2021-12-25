//
// Created by 蒋希文 on 2021/6/24.
//

#ifndef BK_CLASSIC_EUCLIDDISTANCESTRATEGY_H
#define BK_CLASSIC_EUCLIDDISTANCESTRATEGY_H

#include "DistanceStrategy.h"

class EuclidDistanceStrategy : public DistanceStrategy {
public:
    double calculate(const LocationType &location1, const LocationType &location2) override;
};


#endif //BK_CLASSIC_EUCLIDDISTANCESTRATEGY_H
