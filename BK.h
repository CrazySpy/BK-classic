//
// Created by 蒋希文 on 2021/12/21.
//

#ifndef BK_CLASSIC_BK_H
#define BK_CLASSIC_BK_H

#include <vector>
#include <map>
#include <set>
#include "Types.h"
#include "DistanceStrategy.h"
#include "EuclidDistanceStrategy.h"

class BK {
private:
    std::vector<InstanceNameType> _instances;
    std::map<InstanceNameType, LocationType> _locations;

    double _distanceThreshold;

    std::map<InstanceNameType, std::vector<InstanceNameType>> _relations;

    DistanceStrategy *_distance = new EuclidDistanceStrategy();

    std::vector<std::vector<InstanceNameType>> _cliques;

public:
    BK(const std::vector<InstanceType> &instances, double distanceThreshold);
    std::vector<CliqueType> execute();
private:
    void _generateRelations();
    InstanceNameType _selectPivot(const std::vector<InstanceNameType> &P,
                                  const std::vector<InstanceNameType> &X);
    void _executeBK();
    void _executeBKRecursive(std::vector<InstanceNameType> &R,
                      std::vector<InstanceNameType> &P,
                      std::vector<InstanceNameType> &X);
};


#endif //BK_CLASSIC_BK_H
