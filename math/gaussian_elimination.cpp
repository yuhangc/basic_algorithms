//
// Created by yuhang on 3/31/18.
//

#include <vector>
#include <iostream>
#include <cmath>
#include <algorithm>

class GaussianElimination {
public:
    // constructor
    explicit GaussianElimination(double tol=1e-6): tol_(tol), n_(0) {};

    bool set_data(const std::vector<std::vector<double> >& A, const std::vector<double>& b) {
        // check if data is valid
        if (A.empty()) {
            std::cout << "Invalid A matrix - empty!" << std::endl;
            return false;
        }

        if (A.size() != A[0].size()) {
            std::cout << "Invalid A matrix - non-square!" << std::endl;
            return false;
        }

        if (A.size() != b.size()) {
            std::cout << "Invalid data - size of A and b do not match!" << std::endl;
            return false;
        }

        A_ = A;
        b_ = b;
        n_ = A.size();
    }

    bool solve(std::vector<double>& sol) {
        if (n_ == 0) {
            std::cout << "no data set!" << std::endl;
            return false;
        }

        // forward elimination
        for (int i = 0; i < n_-1; ++i) {
            // find the best pivot
            double piv_max = std::abs(A_[i][i]);
            int piv_row = i;

            for (int j = i+1; j < n_; ++j) {
                if (std::abs(A_[j][i]) > piv_max) {
                    piv_max = std::abs(A_[j][i]);
                    piv_row = j;
                }
            }

            // check for no solution
            if (piv_max < tol_) {
                std::cout << "No solution! Encountered 0 pivot during elimination." << std::endl;
                return false;
            }

            // swap rows i, piv_row
            if (piv_row != i) {
                swap_row(A_, i, piv_row, i);
                std::swap(b_[i], b_[piv_row]);
            }

            // elimination
            for (int j = i+1; j < n_; ++j) {
                double alpha = A_[j][i] / A_[i][i];
                substract_row(A_, i, j, alpha, i);
                b_[j] -= alpha * b_[i];
            }
        }

        // backward substitution
        sol = std::vector<double>(n_, 0.0);

        for (int i = static_cast<int>(n_)-1; i >= 0; --i) {
            for (int j = i+1; j < n_; ++j)
                b_[i] -= A_[i][j] * sol[j];

            sol[i] = b_[i] / A_[i][i];
        }

        return true;
    }

private:
    std::vector<std::vector<double> > A_;
    std::vector<double> b_;

    unsigned long n_;

    double tol_;

    // helper functions
    void swap_row(std::vector<std::vector<double> >& A, int i, int j, int st=0) {
        for (int k = st; k < A[i].size(); ++k)
            std::swap(A[i][k], A[j][k]);
    }

    void substract_row(std::vector<std::vector<double> >& A, int i, int j, double alpha, int st=0) {
        // row[j] - alpha * row[i]
        for (int k = st; k < A[i].size(); ++k)
            A[j][k] -= alpha * A[i][k];
    }
};


// main test/demo
int main() {
    // create a gaussian elimination object
    GaussianElimination solver;

    // test data
    std::vector<std::vector<double> > A {{3.0, -2.0, 3.0, 5.0, -6.0},
                                         {-1.3, 3.4, 5.2, -6.3, 1.5},
                                         {5.4, 2.6, -8.3, 2.2, 4.3},
                                         {2.4, -6.3, 6.4, -2.9, 8.2},
                                         {-4.3, 5.6, 0.4, 2.8, 1.4}};

    std::vector<double> b {9.4, -8.3, 3.2, 6.4, -4.9};

    // solution should be {0.89583511, -0.72708776,  0.28065052,  0.99378352,  0.09209167}
    std::vector<double> sol;

    solver.set_data(A, b);
    if (!solver.solve(sol)) {
        std::cout << "No solution!" << std::endl;
    }
    else {
        std::cout << "solution is:" << std::endl;
        std::cout << sol[0];
        for (int i = 1; i < sol.size(); ++i)
            std::cout << ", " << sol[i];
        std::cout << std::endl;
    }

    return 0;
}