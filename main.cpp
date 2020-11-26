#include "full_enumeration.h"
#include "integer_LP.h"
#include "max_F.h"
#include "simplex.h"

int main() {
    std::vector<std::vector<double>> A = {{2, 1, 1}, {1, 4, 0}, {0, 0.5, 1}};
    std::vector<double> c = {3, 1, 4};
    std::vector<double> b = {6, 4, 1};

    // целочиленное программирование
    std::cout << "INTEGER PROGRAMMING" << std::endl;
    std::vector<Answer> int_LP;// вектор терминальных узлов
    bool ok = true;

    integer_LP(A, c, b, int_LP);
    std::cout << std::endl;

    Answer ans_alg = max_F(int_LP);


    std::cout << "_______________\nANSWER of integer programming (algorithm)->" << std::endl;
    ans_alg.print();

    // полный перебор
    for (size_t i = 0; i < 60; i++) std::cout << "-";
    std::cout << std::endl;
    std::cout << "FULL ENUMERATION" << std::endl;
    std::vector<Answer> full_enum;
    full_enumeration(A, c, b, full_enum);

    Answer ans_full = max_F(full_enum);

    std::cout << "_______________\nANSWER of integer programming (full enumeration)->" << std::endl;
    ans_full.print();
    for (size_t i = 0; i < 60; i++) std::cout << "-";
    std::cout << std::endl;

    std::cout << "_______________\nANSWER of integer programming (algorithm)->" << std::endl;
    ans_alg.print();
    std::cout << "_______________\nANSWER of integer programming (full enumeration)->" << std::endl;
    ans_full.print();

    // сравнение ответов
    if (ans_alg == ans_full) std::cout << "_ANSWER in full enumeration is equal to the algorithm ANSWER_" << std::endl;
    else
        std::cout << "_ERROR!!!\n_ANSWER in full enumeration is not equal to the algorithm ANSWER_\n";


    std::cout << "\nОптимальное решение нельзя получить округлением компонент "
                 "исходного решения задачи ЛП "
                 "до близжайших целых. В нашем случае можно:\n"
                 "Имеем исходное решение:"
              << std::endl;
    Answer ans = simplex_method(A, c, b);
    ans.print();
    if (ans.terminal_node()) std::cout << "Дробная переменная - x" << ans.x_is_d << " = " << ans.is_double << std::endl;

    std::cout << "При округлении вниз получаем решение:" << std::endl;
    Answer ans_2(floor(ans.get_x1()), floor(ans.get_x2()), floor(ans.get_x3()));
    ans_2.print();
    if (!limitation(A, b, floor(ans.get_x1()), floor(ans.get_x2()), floor(ans.get_x3())))
        std::cout << "Решения не имеет" << std::endl;
    else {
        if (ans_2.func() < ans_alg.func()) std::cout << "Неоптимальное решение - F = " << ans_2.func() << std::endl;
        else
            std::cout << "Оптимальное решение - F = " << ans_2.func() << std::endl;
    }

    std::cout << "\nПри округлении вверх получаем решение:" << std::endl;
    Answer ans_1(ceil(ans.get_x1()), ceil(ans.get_x2()), ceil(ans.get_x3()));
    ans_1.print();
    if (!limitation(A, b, ceil(ans.get_x1()), ceil(ans.get_x2()), ceil(ans.get_x3())))
        std::cout << "Решения не имеет (недопустимое решение)" << std::endl;
    else {
        if (ans_1.func() < ans_alg.func()) std::cout << "Неоптимальное решение - F = " << ans_1.func() << std::endl;
        else
            std::cout << "Оптимальное решение - F = " << ans_1.func() << std::endl;
    }


    return 0;
}
