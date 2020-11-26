// Created by Alyona Dorodnyaya, Nyanyoka@yandex.ru

#include "simplex.h"

#include <utility>

// Вывод двумерного массива
void print_2(const std::vector<std::vector<double>> &A) {
    for (size_t i = 0; i < 50; i++) std::cout << "-";
    std::cout << std::endl;
    for (const auto &i : A) {
        for (double j : i)
            std::cout << std::right << std::setw(8) << std::setprecision(4) << j << " ";
        std::cout << std::endl;
    }
    for (size_t i = 0; i < 50; i++) std::cout << "-";
    std::cout << '\n'
              << '\n';
}

void print_simplex(const std::vector<std::vector<double>> &A,
                   const std::vector<std::string> &sv,
                   const std::vector<std::string> &basis) {
    for (size_t i = 0; i < 50; i++) std::cout << "-";
    std::cout << std::endl;
    for (const auto &i : sv)
        std::cout << std::right << std::setw(8) << i << " ";
    std::cout << std::endl;
    size_t k = 1;
    for (const auto &i : A) {
        std::cout << std::right << std::setw(8) << basis[k];
        for (double j : i)
            std::cout << std::right << std::setw(8) << std::setprecision(4) << j << " ";
        std::cout << std::endl;
        k++;
    }
    for (size_t i = 0; i < 50; i++) std::cout << "-";
    std::cout << '\n'
              << '\n';
}

// Вывод одномерного массива
void print_1(const std::vector<double> &A) {
    for (size_t i = 0; i < 50; i++) std::cout << "-";
    std::cout << std::endl;
    for (const auto &i : A)
        std::cout << std::setw(8) << i << " ";
    std::cout << std::endl;
    for (size_t i = 0; i < 50; i++) std::cout << "-";
    std::cout << '\n'
              << '\n';
}

// Изначальное заполнение симплекс-таблицы
void first_table(const std::vector<std::vector<double>> &A,
                 const std::vector<double> &c, const std::vector<double> &b,
                 std::vector<std::vector<double>> &simplex,
                 const std::vector<std::string> &sv,
                 const std::vector<std::string> &basis) {
    simplex.reserve(A.size() + 1);
    size_t k = 0;
    for (auto &i : A) {
        auto j = i;
        j.insert(j.begin(), b[k]);
        simplex.push_back(j);
        k++;
    }
    auto c1 = c;
    for (double &i : c1) i = -i;
    c1.insert(c1.begin(), 0);
    simplex.push_back(c1);
    std::cout << std::setw(20) << "Simplex - initial table" << std::endl;
    print_simplex(simplex, sv, basis);
}

// Разрешающий столбец
size_t column(const std::vector<double> &c) {
    size_t column = 10;// в случае оптимального решения функция возвращает 10
    double s = c.at(1);
    for (size_t i = 1; i < 4; i++) {
        if (c.at(i) < 0 && c.at(i) <= s) {
            s = c.at(i);
            column = i;
        }
    }
    return column;
}

// Разрешающая строка
size_t string(size_t column_, const std::vector<std::vector<double>> &simplex) {
    // в случае, когда функция не ограничена
    // (то есть ни одного положительного отношения) на множестве решений вернет -1
    size_t string_ = 0;
    double C = -1;
    for (size_t i = 0; i < simplex.size(); i++) {
        if (simplex.at(i).at(0) > 0 && simplex.at(i).at(column_) > 0) {
            if (C == -1) string_ = i;
            if (simplex.at(i).at(0) / simplex.at(i).at(column_) < C)
                string_ = i;
            C = simplex.at(i).at(0) / simplex.at(i).at(column_);
        }
    }
    if (C == -1) return (simplex.size() + 1);
    return string_;
}

bool problem(std::vector<std::vector<double>> &simplex,
             std::vector<std::string> &sv,
             std::vector<std::string> &basis) {
    size_t column_, string_;
    size_t size_column = simplex.at(0).size();
    size_t size_string = simplex.size();

    bool ok = false;
    while (!ok) {
        size_t u = -1;
        double min = 0;
        for (size_t i = 0; i < simplex.size() - 1; ++i) {
            if (simplex.at(i).at(0) < min) {
                min = simplex.at(i).at(0);
                u = i;
            }
        }
        if (u == -1) ok = true;// если отрицательных не найдено - выходим из цикла
                               // (можно было бы выйти и из функции, но лучше,
                               // чтобы функция всегда что-то возвращала)
        else {
            string_ = u;
            u = 1;
            while (u < size_column && simplex.at(string_).at(u) >= 0) u++;
            if (u == size_column) return false;
            column_ = u;

            double element = simplex.at(string_).at(column_);
            // Меняем переменные
            std::swap(sv.at(column_ + 1), basis.at(string_ + 1));

            // Изменяем таблицу:
            // - элементы разрешающий строки / разрешающий элемент
            // - элементы разрешающего столбца / противоположный разрешающиму элементу
            // - разрешающий элемент заменяется противоположным самому себе (1/element)
            for (size_t i = 0; i < size_string; i++)
                for (size_t j = 0; j < size_column; j++)
                    if (i != string_ && j != column_)
                        simplex.at(i).at(j) -= simplex.at(string_).at(j) * simplex.at(i).at(column_) / simplex.at(string_).at(column_);

            for (size_t i = 0; i < size_string; i++)
                for (size_t j = 0; j < size_column; j++) {
                    if (i == string_ && j != column_) simplex.at(i).at(j) /= element;
                    if (i == string_ && j == column_) simplex.at(i).at(j) = 1 / element;
                    if (i != string_ && j == column_) simplex.at(i).at(j) /= (-1) * element;
                }
        }
    }
    // в случае выхода из цикла, то есть симплекс таблица преобразовалась
    // и решение имеется, возращается true
    return true;
}


Answer simplex_method(const std::vector<std::vector<double>> &A,
                      const std::vector<double> &c,
                      const std::vector<double> &b) {
    Answer answer;

    // Вывод матриц из условия
    std::cout << std::setw(20) << "A" << std::endl;
    print_2(A);
    std::cout << std::setw(20) << "c" << std::endl;
    print_1(c);
    std::cout << std::setw(20) << "b" << std::endl;
    print_1(b);

    // Векторa для хранения базисных и свободных переменных:
    // изначально свободные переменные - x1, x2, x3
    // изначально базисные переменные - x4, ..., x(A.size()+3)
    std::vector<std::string> sv, basis;
    basis.reserve(A.size());
    sv = {" ", "b", "x1", "x2", "x3"};
    basis.emplace_back(" ");
    for (size_t i = 0; i < A.size(); i++)
        basis.emplace_back("x" + std::to_string(i + 4));
    basis.emplace_back("F");

    // Создание и заполенение симплекс таблицы
    std::vector<std::vector<double>> simplex;
    first_table(A, c, b, simplex, sv, basis);
    size_t column_, string_;
    size_t size_column = simplex.at(0).size();
    size_t size_string = simplex.size();

    // если не удаётся избавится от отрицательных b, решения нет, возвращается пустой ответ
    if (!problem(simplex, sv, basis)) return answer;

    while (column(simplex.at(size_string - 1)) != 10) {

        // Находим разрешающий столбец, строку и элемент
        column_ = column(simplex.at(size_string - 1));
        string_ = string(column_, simplex);
        // проверка на то, имеет ли пример вообще оптимальное решение на данном множестве
        if (string_ == simplex.size() + 1) { answer.no_ans(); }
        double element = simplex.at(string_).at(column_);
        // Меняем переменные
        std::swap(sv.at(column_ + 1), basis.at(string_ + 1));

        //         Изменяем таблицу:
        //         - элементы разрешающий строки / разрешающий элемент
        //         - элементы разрешающего столбца / противоположный разрешающиму элементу
        //         - разрешающий элемент заменяется противоположным самому себе (1/element)
        for (size_t i = 0; i < size_string; i++)
            for (size_t j = 0; j < size_column; j++)
                if (i != string_ && j != column_)
                    simplex.at(i).at(j) -= simplex.at(string_).at(j) * simplex.at(i).at(column_) / simplex.at(string_).at(column_);

        for (size_t i = 0; i < size_string; i++)
            for (size_t j = 0; j < size_column; j++) {
                if (i == string_ && j != column_) simplex.at(i).at(j) /= element;
                if (i == string_ && j == column_) simplex.at(i).at(j) = 1 / element;
                if (i != string_ && j == column_) simplex.at(i).at(j) /= (-1) * element;
            }

        // Подведение итога оптимизации. Если итоговый ответ - оптимальный, выписывается ответ и итоговая симплекс таблица
        // если не удаётся избавится от отрицательных b, решения нет
        if (!problem(simplex, sv, basis)) answer.no_ans();
        if (column(simplex.at(size_string - 1)) == 10) {
            // Вывод полученной симплекс-таблицы
            std::cout << std::setw(20) << "Simplex - end table" << std::endl;
            print_simplex(simplex, sv, basis);

            double x1, x2, x3;
            for (const auto &s : sv) {
                if (s == "x1") answer.set_x1(0);
                if (s == "x2") answer.set_x2(0);
                if (s == "x3") answer.set_x3(0);
            }
            for (size_t i = 1; i < basis.size(); i++) {
                if (basis.at(i) == "x1") answer.set_x1(simplex.at(i - 1).at(0));
                if (basis.at(i) == "x2") answer.set_x2(simplex.at(i - 1).at(0));
                if (basis.at(i) == "x3") answer.set_x3(simplex.at(i - 1).at(0));
            }
        }
    }
    return answer;// если симплекс-метод завершился, решение есть и оно найдено
}
