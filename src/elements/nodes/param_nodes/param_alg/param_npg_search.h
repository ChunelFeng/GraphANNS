/***************************
@Author: Chunel
@Contact: chunel@foxmail.com
@File: param_npg_search.h
@Time: 2022/5/1 15:25
@Desc: 
***************************/

#ifndef GRAPHANNS_PARAM_NPG_SEARCH_H
#define GRAPHANNS_PARAM_NPG_SEARCH_H

#include "../param_basic_v2.h"

struct ParamNpgSearch : public ParamBasicV2<> {
    VecValType *query = nullptr;
    unsigned top_k = 20;
    unsigned search_L = top_k + 500;    // todo 这个确定是成员变量么？
    unsigned query_id = 0;

    std::vector<NeighborFlag> sp;
    std::vector<std::vector<unsigned> > results;

    CVoid reset() override {
        sp.clear();
    }
};

#endif //GRAPHANNS_PARAM_NPG_SEARCH_H