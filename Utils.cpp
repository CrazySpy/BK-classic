//
// Created by 蒋希文 on 2021/12/29.
//

#include <vector>
#include "Types.h"

template<typename T>
void orderedInsert(std::vector<T> &set, const T &element) {
    auto it = std::lower_bound(set.begin(), set.end(), element);
    set.insert(it, element);
}

template void orderedInsert(std::vector<VertexType> &set, const VertexType &element);