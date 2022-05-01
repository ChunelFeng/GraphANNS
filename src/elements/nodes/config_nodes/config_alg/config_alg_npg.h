/***************************
@Author: wmz
@Contact: wmengzhao@qq.com
@File: config_alg_npg.h
@Time: 2022/4/14 6:56 PM
@Desc: 'npg' algorithm configuration
***************************/

#ifndef GRAPHANNS_CONFIG_ALG_NPG_H
#define GRAPHANNS_CONFIG_ALG_NPG_H

#include "../config_basic.h"
#include "config_alg_define.h"

class ConfigAlgNPG : public ConfigBasic {
public:
    CStatus init() override {
        CStatus status = CGRAPH_CREATE_GPARAM(ParamNPG, GRAPH_INFO_PARAM_KEY);

        status += CGRAPH_CREATE_GPARAM(ParamNpgTrain, GA_ALG_NPG_TRAIN_PARAM)
        status += CGRAPH_CREATE_GPARAM(ParamNpgSearch, GA_ALG_NPG_SEARCH_PARAM)
        if (!status.isOK()) {
            return CStatus("create param failed");
        }

        auto *npg_param = CGRAPH_GET_GPARAM(ParamNPG, GRAPH_INFO_PARAM_KEY)
        CGRAPH_ASSERT_NOT_NULL(npg_param)

        npg_param->base_path = GA_NPG_BASE_PATH;
        npg_param->query_path = GA_NPG_QUERY_PATH;
        npg_param->groundtruth_path = GA_NPG_GROUNDTRUTH_PATH;
        npg_param->index_path = GA_NPG_INDEX_PATH;

        npg_param->L_candidate = GA_NPG_L_CANDIDATE;
        npg_param->R_neighbor = GA_NPG_R_NEIGHBOR;
        npg_param->C_neighbor = GA_NPG_C_NEIGHBOR;
        npg_param->k_init_graph = GA_NPG_K_INIT_GRAPH;
        return CStatus();
    }

    CStatus run() override {
        return CStatus();
    }
};

#endif //GRAPHANNS_CONFIG_ALG_NPG_H