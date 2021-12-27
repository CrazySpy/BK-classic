//
// Created by 蒋希文 on 2021/12/21.
//

#ifndef BK_CLASSIC_BK_H
#define BK_CLASSIC_BK_H

#include <vector>
#include <map>
#include <set>
#include "Types.h"

class BK {
private:
    unsigned int _vertexNum;

    std::map<unsigned int, std::vector<VertexType>> _edges;

    std::vector<std::vector<VertexType>> _cliques;

public:
    BK(unsigned int vertexNum, const std::vector<EdgeType> &edges);
    std::vector<CliqueType> execute();
private:
    VertexType _selectPivot(const std::vector<VertexType> &P,
                            const std::vector<VertexType> &X);
    void _executeBK();
    void _executeBKRecursive(std::vector<VertexType> &R,
                             std::vector<VertexType> &P,
                             std::vector<VertexType> &X);
};

#endif //BK_CLASSIC_BK_H
