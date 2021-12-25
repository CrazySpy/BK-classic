//
// Created by 蒋希文 on 2021/12/21.
//

#include <algorithm>
#include <vector>
#include "Types.h"

InstanceNameType toInstanceName(const InstanceType &instance) {
    return {instance.feature, instance.id};
}

LocationType getLocation(const InstanceType &instance) {
    return instance.location;
}
