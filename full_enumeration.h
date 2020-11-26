#ifndef LAB_OPTIM_3_FULL_ENUMERATION_H
#define LAB_OPTIM_3_FULL_ENUMERATION_H

#include "simplex.h"

// проверка вхождения данных переменных в ограничения
bool limitation(const std::vector<std::vector<double>> &A, const std::vector<double> &b, double x1, double x2, double x3) {
    for (size_t i = 0; i < A.size(); i++)
        if ((A.at(i).at(0) * x1 + A.at(i).at(1) * x2 + A.at(i).at(2) * x3) > b.at(i)) return false;// в случае нарушения условий выходим из функции
    return true;
}

// функция подсчёта при полном переборе
void full_enumeration(std::vector<std::vector<double>> &A,
                      const std::vector<double> &c, std::vector<double> &b,
                      std::vector<Answer> &full_enum) {
    double x1 = 0, x2 = 0, x3 = 0;
    while (limitation(A, b, x1, x2, x3)) {
        while (limitation(A, b, x1, x2, x3)) {
            while (limitation(A, b, x1, x2, x3)) {
                double F = c.at(0) * x1 + c.at(1) * x2 + c.at(2) * x3;
                if (F - ceil(F) == 0) {
                    Answer ans(x1, x2, x3);
                    ans.print();
                    full_enum.emplace_back(ans);
                }
                x3 += 1;
            }
            x3 = 0;
            x2 += 1;
        }
        x2 = 0;
        x3 = 0;
        x1 += 1;
    }
}

#endif//LAB_OPTIM_3_FULL_ENUMERATION_H
