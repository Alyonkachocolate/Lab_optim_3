// Created by Alyona Dorodnyaya, Nyanyoka@yandex.ru

#ifndef LAB_OPTIM_3_SIMPLEX_H
#define LAB_OPTIM_3_SIMPLEX_H

#include <cmath>
#include <iomanip>
#include <iostream>
#include <string>
#include <vector>

class Answer {
private:
    bool ans_;
    double x1_;
    double x2_;
    double x3_;


public:
    Answer() : x1_(0), x2_(0), x3_(0), ans_(false) {}
    double is_double = 0;

    Answer(double x1, double x2, double x3) : x1_(x1), x2_(x2), x3_(x3), ans_(true) {}

    size_t x_is_d = 0;

    double func() const {
        if (ans_) return (3.0 * x1_ + 1.0 * x2_ + 4.0 * x3_);
        return 0;
    }

    bool ans() const { return ans_; }

    double get_x1() const{
        return x1_;
    }

    double get_x2() const{
        return x2_;
    }

    double get_x3() const{
        return x3_;
    }

    void set_x1(double x1) {
        x1_ = x1;
        ans_ = true;
    }
    void set_x2(double x2) {
        x2_ = x2;
        ans_ = true;
    }
    void set_x3(double x3) {
        x3_ = x3;
        ans_ = true;
    }

    bool terminal_node() {
        // если не имеет решения или решение целочисленное - терминальный узел
        if (!ans_) return true;
        if ((x1_ - ceil(x1_)) != 0) {
            is_double = x1_;
            x_is_d = 1;
            return false;
        }
        if ((x2_ - ceil(x2_)) != 0) {
            is_double = x2_;
            x_is_d = 2;
            return false;
        }
        if ((x3_ - ceil(x3_)) != 0) {
            is_double = x3_;
            x_is_d = 3;
            return false;
        }
        return true;
    }

    std::vector<double> is_vector(bool t) const {
        if (x_is_d == 1) {
            if (t) return {1, 0, 0};
            else
                return {-1, 0, 0};
        }
        if (x_is_d == 2) {
            if (t) return {0, 1, 0};
            else
                return {0, -1, 0};
        }
        if (t) return {0, 0, 1};
        else
            return {0, 0, -1};
    }

    void no_ans() { ans_ = false; }
    void print() const {
        if (ans_) {
            std::cout << "ANSWER of linear programming: "
                         "\nmax F = max("
                      << "x1 + x2 + x3) = "
                      << "3*" << x1_ << " + " << x2_ << " + 4*" << x3_ << " = " << func() << '\n'
                      << "x1 = " << x1_ << "\nx2 = " << x2_
                      << "\nx3 = " << x3_ << std::endl;
        } else
            std::cout << "There is no optimal solution" << std::endl;
        std::cout << std::endl;
    }

    bool operator==(const Answer &rhs) const {
        return (x1_ == rhs.x1_ && x2_ == rhs.x2_, x3_ == rhs.x3_);
    }
};

// Избавляемся от отрицательных коэффициентов в векторе b
bool problem(std::vector<std::vector<double>> &simplex,
             std::vector<std::string> &sv,
             std::vector<std::string> &basis);

// Cимплекс метод - 1 - имеет решение, 0 - не имеет решения
Answer simplex_method(const std::vector<std::vector<double>> &A,
                      const std::vector<double> &c,
                      const std::vector<double> &b);

// Вывод двумерного массива
void print_2(const std::vector<std::vector<double>> &A);

// Вывод симплекс таблицы
void print_simplex(const std::vector<std::vector<double>> &A,
                   const std::vector<std::string> &sv,
                   const std::vector<std::string> &basis);

// Вывод одномерного массива
void print_1(const std::vector<double> &A);

// Изначальное заполнение симплекс-таблицы
void first_table(const std::vector<std::vector<double>> &A,
                 const std::vector<double> &c, const std::vector<double> &b,
                 std::vector<std::vector<double>> &simplex,
                 const std::vector<std::string> &sv,
                 const std::vector<std::string> &basis);

// Нахождение разрешающего столбца
size_t column(const std::vector<double> &c);

// Нахождение разрешающей строки по разрешающему столбцу
size_t string(size_t column_, const std::vector<std::vector<double>> &simplex);

#endif//LAB_OPTIM_3_SIMPLEX_H
