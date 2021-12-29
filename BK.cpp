//
// Created by 蒋希文 on 2021/12/21.
//

#include <algorithm>
#include <numeric>
#include "BK.h"
#include "Types.h"
#include "Utils.h"

BK::BK(unsigned int vertexNum, const std::vector<EdgeType> &edges)
        :_vertexNum(vertexNum) {
    for(auto &edge : edges) {
        auto &u = edge.first, &v = edge.second;
        _edges[u].push_back(v);
        _edges[v].push_back(u);
    }
}

VertexType BK::_selectPivot(const std::vector<VertexType> &P,
                            const std::vector<VertexType> &X) {
    std::vector<VertexType> unionSet;
    std::set_union(P.begin(), P.end(), X.begin(), X.end(), std::back_inserter(unionSet));

    VertexType bestInstance = unionSet[0];
    unsigned int instanceNeighbourNum = 0;
    for(auto &instanceName : unionSet) {
        if(instanceNeighbourNum <= _edges[instanceName].size()) {
            bestInstance = instanceName;
            instanceNeighbourNum = _edges[instanceName].size();
        }
    }

    return bestInstance;
}

void BK::_executeBK() {
    auto R = std::vector<VertexType>();
    auto P = std::vector<VertexType>(_vertexNum, 1);
    std::partial_sum(P.begin(), P.end(), P.begin());
    auto X = std::vector<VertexType>();
    _executeBKRecursive(R, P, X);
}

void BK::_executeBKRecursive(std::vector<VertexType> &R,
                             std::vector<VertexType> &P,
                             std::vector<VertexType> &X) {
    if(P.empty()) {
        if(X.empty()) {
            _cliques.push_back(R);
        }
        return;
    }

    auto pivot = _selectPivot(P, X);
    auto &pivotNeighbour = _edges[pivot];
    std::vector<VertexType> nonPivotNeighbourP;
    // The candidate should select from the pivot's non-neighbour.
    std::set_difference(P.begin(), P.end(),
                        pivotNeighbour.begin(), pivotNeighbour.end(),
                        std::back_inserter(nonPivotNeighbourP));

    for(auto &candidateInstance : nonPivotNeighbourP) {
        /*
        if (candidateInstance == 36 && X == std::vector<VertexType>{34, 35}) {
            std::cout << "abc" << std::endl;
        }
         */
        auto &candidateNeighbours = _edges[candidateInstance];

        std::vector<VertexType> tmpR = R, tmpP, tmpX;
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

        orderedInsert(X, candidateInstance);
    }
}

std::vector<CliqueType> BK::execute() {
    _executeBK();
    return _cliques;
}
