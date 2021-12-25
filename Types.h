#ifndef BK_CLASSIC_TYPES_H
#define BK_CLASSIC_TYPES_H

#include <iostream>
#include <vector>

using FeatureType = std::string;
using InstanceIdType = std::string;
using LocationType = std::pair<double, double>;
struct InstanceType {
    FeatureType feature;
    InstanceIdType id;
    LocationType location;
};

using InstanceNameType = std::pair<FeatureType, InstanceIdType>;

using InstanceNameType = std::pair<FeatureType, InstanceIdType>;

using PatternType = std::vector<FeatureType>;
using CliqueType = std::vector<InstanceNameType>;

#endif //BK_CLASSIC_TYPES_H
