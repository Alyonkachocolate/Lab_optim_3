#ifndef LAB_OPTIM_3_MAX_F_H
#define LAB_OPTIM_3_MAX_F_H

#include "simplex.h"

Answer max_F(const std::vector<Answer> &vec) {
    double max_F = 0;
    Answer ans;
    for (const auto &a : vec)
        if (a.ans() && a.func() > max_F) {
            max_F = a.func();
            ans = a;
        }
    return ans;
}

#endif//LAB_OPTIM_3_MAX_F_H
