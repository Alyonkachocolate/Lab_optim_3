#ifndef LAB_OPTIM_3_INTEGER_LP_H
#define LAB_OPTIM_3_INTEGER_LP_H

#include "simplex.h"

void integer_LP(std::vector<std::vector<double>> &A,
                const std::vector<double> &c, std::vector<double> &b,
                std::vector<Answer> &int_LP) {
    for (size_t i = 0; i < 60; i++) std::cout << "-";
    std::cout << std::endl;

    std::cout << "CREATE TREE NODE" << std::endl;
    std::cout << "First solution" << std::endl;
    Answer ans = simplex_method(A, c, b);
    ans.print();

    if (ans.terminal_node()) {
        std::cout << "The task initially has an integer solution" << std::endl;
        int_LP.push_back(ans);
        ans.print();
    }

    else {
        double x = ans.is_double;
        Answer answer = ans;
        std::cout << "We have a fractional number: x" << ans.x_is_d << " = " << x << std::endl;
        std::cout << "Branching" << std::endl;
        {
            for (size_t i = 0; i < 60; i++) std::cout << "-";
            std::cout << std::endl;
            std::cout << "1) x<=" << floor(x) << std::endl;
            auto add_in_A = ans.is_vector(true);
            A.push_back(add_in_A);
            b.push_back(floor(x));

            std::cout << "CREATE NEW TREE NODE" << std::endl;
            ans = simplex_method(A, c, b);
            ans.print();

            if (ans.terminal_node()) {
                A.pop_back();
                b.pop_back();
                int_LP.push_back(ans);
                std::cout << "We have an integer solution - terminal node" << std::endl;
                for (size_t i = 0; i < 60; i++) std::cout << "-";
                std::cout << std::endl;
            } else {
                integer_LP(A, c, b, int_LP);
            }
        }

        {
            std::cout << "2) x>=" << ceil(x) << std::endl;
            ans = answer;
            auto add_in_A = ans.is_vector(false);
            A.push_back(add_in_A);
            b.push_back(-ceil(x));

            std::cout << "CREATE NEW TREE NODE" << std::endl;
            ans = simplex_method(A, c, b);
            ans.print();

            if (ans.terminal_node()) {
                A.pop_back();
                b.pop_back();
                int_LP.push_back(ans);
                std::cout << "We have an integer solution - terminal node" << std::endl;
                for (size_t i = 0; i < 60; i++) std::cout << "-";
                std::cout << std::endl;
            } else {
                integer_LP(A, c, b, int_LP);
            }
        }
    }
}

#endif//LAB_OPTIM_3_INTEGER_LP_H
