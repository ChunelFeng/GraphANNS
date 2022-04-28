/***************************
@Author: wmz
@Contact: wmengzhao@qq.com
@File: search_pool.h
@Time: 2022/4/14 10:04 PM
@Desc: candidate results when searching
***************************/

#ifndef GRAPHANNS_NEIGHBOR_FLAG_H
#define GRAPHANNS_NEIGHBOR_FLAG_H

#include "neighbor_basic.h"

struct NeighborFlag : public Neighbor {
public:
    NeighborFlag(unsigned id, DistResType distance, bool f) : Neighbor(id, distance), flag_(f) {}

    inline bool operator<(const NeighborFlag &other) const {
        return distance_ < other.distance_;
    }

    inline bool operator>(const NeighborFlag &other) const {
        return distance_ > other.distance_;
    }

public:
    bool flag_;
};

#endif //GRAPHANNS_NEIGHBOR_FLAG_H
