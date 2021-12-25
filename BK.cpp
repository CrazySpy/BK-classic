//
// Created by 蒋希文 on 2021/12/21.
//

#include <algorithm>
#include "BK.h"
#include "Utils.h"

BK::BK(const std::vector<InstanceType> &instances, double distanceThreshold)
:_distanceThreshold(distanceThreshold) {
    for(auto &instance: instances) {
        auto instanceName = toInstanceName(instance);
        _instances.push_back(instanceName);
        _locations[instanceName] = instance.location;
    }
    _generateRelations();
}

void BK::_generateRelations() {
    for(int i = 0; i < _instances.size(); ++i) {
        auto &instanceName1 = _instances[i];
        auto &location1 = _locations[instanceName1];
        for(int j = 0; j < _instances.size(); ++j) {
            auto &instanceName2 = _instances[j];
            if(instanceName1 == instanceName2) continue;

            auto &location2 = _locations[instanceName2];
            double distance = _distance->calculate(location1, location2);

            if(distance <= _distanceThreshold) {
                _relations[instanceName1].push_back(instanceName2);
            }
        }
    }
}

InstanceNameType BK::_selectPivot(const std::vector<InstanceNameType> &P,
                                  const std::vector<InstanceNameType> &X) {
    std::vector<InstanceNameType> unionSet;
    std::set_union(P.begin(), P.end(), X.begin(), X.end(), std::back_inserter(unionSet));

    InstanceNameType bestInstance = unionSet[0];
    unsigned int instanceNeighbourNum = 0;
    for(auto &instanceName : unionSet) {
        if(instanceNeighbourNum <= _relations[instanceName].size()) {
            bestInstance = instanceName;
            instanceNeighbourNum = _relations[instanceName].size();
        }
    }

    return bestInstance;
}

void BK::_executeBK() {
    auto R = std::vector<InstanceNameType>();
    auto P = _instances;
    auto X = std::vector<InstanceNameType>();
    _executeBKRecursive(R,P,X);
}

void BK::_executeBKRecursive(std::vector<InstanceNameType> &R,
                      std::vector<InstanceNameType> &P,
                      std::vector<InstanceNameType> &X) {
    if(P.empty()) {
        if(X.empty()) {
            _cliques.push_back(R);
        }
        return;
    }

    auto pivot = _selectPivot(P, X);
    auto &pivotNeighbour = _relations[pivot];
    std::vector<InstanceNameType> nonPivotNeighbourP;
    // The candidate should select from the pivot's non-neighbour.
    std::set_difference(P.begin(), P.end(),
                        pivotNeighbour.begin(), pivotNeighbour.end(),
                        std::back_inserter(nonPivotNeighbourP));

    for(auto &candidateInstance : nonPivotNeighbourP) {
        auto &candidateNeighbours = _relations[candidateInstance];

        std::vector<InstanceNameType> tmpR = R, tmpP, tmpX;
        // R = R ∪ candidate
        tmpR.push_back(candidateInstance);
        // P = P ∩ candidate
        std::set_intersection(P.begin(), P.end(), candidateNeighbours.begin(), candidateNeighbours.end(),
                              std::back_inserter(tmpP));
        // X = X ∩ candidate
        std::set_intersection(X.begin(), X.end(), candidateNeighbours.begin(), candidateNeighbours.end(),
                              std::back_inserter(tmpX));

        _executeBKRecursive(tmpR, tmpP, tmpX);

        P.erase(std::find(P.begin(), P.end(), candidateInstance));

        X.push_back(candidateInstance);
    }
}

std::vector<CliqueType> BK::execute() {
    _executeBK();
    return _cliques;
}

