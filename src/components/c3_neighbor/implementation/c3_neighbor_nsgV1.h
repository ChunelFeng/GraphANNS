/***************************
@Author: wmz
@Contact: wmengzhao@qq.com
@File: c3_neighbor_nsgv1.h
@Time: 2022/4/7 5:20 PM
@Desc: edge selection by RNG (a strategy that considers neighbor distribution and is applied to 'NSG', 'HNSW', etc.)
***************************/

#ifndef GRAPHANNS_C3_NEIGHBOR_NSGV1_H
#define GRAPHANNS_C3_NEIGHBOR_NSGV1_H

#include "../c3_neighbor_basic.h"

class C3NeighborNSGV1 : public C3NeighborBasic {
public:
    DAnnFuncType prepareParam() override {
        /**
         * todo 这个问题跟c2 中的那个问题，是同样的。为啥会写两份同样的代码捏，对吧
         * 是所有算法，通用，还是针对nsg通用？
         */
        auto *t_param = CGRAPH_GET_GPARAM(NPGTrainParam, GA_ALG_NPG_TRAIN_PARAM_KEY)
        model_ = CGRAPH_GET_GPARAM(AnnsModelParam, GA_ALG_MODEL_PARAM_KEY);
        if (nullptr == model_ || nullptr == t_param) {
            return DAnnFuncType::ANN_PREPARE_ERROR;
        }

        num_ = model_->train_data.num;
        dim_ = model_->train_data.dim;
        data_ = model_->train_data.data;

        C_ = t_param->C_neighbor;
        R_ = t_param->R_neighbor;

        return DAnnFuncType::ANN_TRAIN;
    }

    CStatus train() override {
        auto t_param = CGRAPH_GET_GPARAM(NPGTrainParam, GA_ALG_NPG_TRAIN_PARAM_KEY)
        CGRAPH_ASSERT_NOT_NULL(t_param)

        for (unsigned i = 0; i < num_; i++) {
            unsigned start = 0;
            std::sort(model_->pool_m[i].begin(), model_->pool_m[i].end());
            std::vector<Neighbor> result;
            if (model_->pool_m[i][start].id_ == i) start++;
            result.push_back(model_->pool_m[i][start]);

            while (result.size() < R_
                   && (++start) < model_->pool_m[i].size() && start < C_) {
                auto &p = model_->pool_m[i][start];
                bool occlude = false;
                for (const auto &res: result) {
                    if (p.id_ == res.id_) {
                        occlude = true;
                        break;
                    }
                    DistResType djk = 0;
                    dist_op_.calculate(data_ + (res.id_ * dim_),
                                      data_ + p.id_ * dim_,
                                      dim_, dim_, djk);
                    if (djk < p.distance_) {
                        occlude = true;
                        break;
                    }
                }
                if (!occlude) result.push_back(p);
            }

            {
                CGRAPH_PARAM_WRITE_CODE_BLOCK(t_param)
                model_->cut_graph.push_back(result);
            }
        }
        return CStatus();
    }
};

#endif //GRAPHANNS_C3_NEIGHBOR_NSGV1_H
