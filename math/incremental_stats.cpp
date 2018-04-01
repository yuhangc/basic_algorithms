//
// Created by yuhang on 4/1/18.
//

#include <vector>
#include <iostream>
#include <random>

// declarations
template <class Tdata>
class SimpleMat;

template <class Tdata>
class SimpleVec {
public:
    SimpleVec() = default;

    explicit SimpleVec(int n) {
        len_ = n;
        vec_ = std::vector<Tdata>(n);
    }

    SimpleVec(const Tdata* data, int len) {
        vec_.assign(data, data+len);
        len_ = len;
    };

    explicit SimpleVec(const std::vector<Tdata>& data) {
        vec_ = data;
        len_ = static_cast<int>(data.size());
    };

    // overload operators
    Tdata& operator[](int i) {
        return vec_[i];
    }

    SimpleVec<Tdata> operator+(const SimpleVec<Tdata>& vec2) const {
        SimpleVec<Tdata> sum(len_);

        for (int i = 0; i < len_; ++i)
            sum.vec_[i]= vec_[i] + vec2.vec_[i];

        return sum;
    }

    SimpleVec<Tdata> operator-(const SimpleVec<Tdata>& vec2) const {
        SimpleVec<Tdata> sub(len_);

        for (int i = 0; i < len_; ++i)
            sub.vec_[i]= vec_[i] - vec2.vec_[i];

        return sub;
    }

    SimpleVec<Tdata>& operator=(const SimpleVec<Tdata>& vec2) {
        len_ = vec2.len_;
        vec_ = vec2.vec_;

        return *this;
    }

    SimpleVec<Tdata>& operator=(const Tdata& val) {
        for (int i = 0; i < len_; ++i)
            vec_[i] = val;

        return *this;
    }

    SimpleMat<Tdata> operator*(const SimpleVec<Tdata>& vec2) const;

    template <class T>
    friend SimpleVec<T> operator*(const T& a, const SimpleVec<T>& vec);
    template <class T>
    friend std::ostream& operator<<(std::ostream& os, const SimpleVec<T>& vec);

    int len() const {
        return len_;
    }

private:
    int len_;
    std::vector<Tdata> vec_;
};


template <class Tdata>
class SimpleMat {
public:
    SimpleMat() = default;

    SimpleMat(int m, int n)
    {
        nrows_ = m;
        ncols_ = n;
        mat_ = std::vector<std::vector<Tdata> >(m, std::vector<Tdata>(n));
    }

    explicit SimpleMat(const std::vector<std::vector<Tdata> >& data) {
        mat_ = data;
        nrows_ = (int)data.size();
        ncols_ = (int)data[0].size();
    }

    // overload operators
    std::vector<Tdata>& operator[](int i ) {
        return mat_[i];
    }

    SimpleMat<Tdata> operator+(const SimpleMat<Tdata>& mat2) const {
        SimpleMat<Tdata> sum(nrows_, ncols_);

        for (int i = 0; i < nrows_; ++i) {
            for (int j = 0; j < ncols_; ++j) {
                sum.mat_[i][j] = mat_[i][j] + mat2.mat_[i][j];
            }
        }

        return sum;
    }

    SimpleMat<Tdata> operator-(const SimpleMat<Tdata>& mat2) const {
        SimpleMat<Tdata> sum(nrows_, ncols_);

        for (int i = 0; i < nrows_; ++i) {
            for (int j = 0; j < ncols_; ++j) {
                sum.mat_[i][j] = mat_[i][j] - mat2.mat_[i][j];
            }
        }

        return sum;
    }

    SimpleMat<Tdata>& operator=(const SimpleMat<Tdata>& mat2) {
        nrows_ = mat2.nrows_;
        ncols_ = mat2.ncols_;
        mat_ = mat2.mat_;

        return *this;
    }

    SimpleMat<Tdata>& operator=(const Tdata& val) {
        for (int i = 0; i < nrows_; ++i) {
            for (int j = 0;  j < ncols_; ++j) {
                mat_[i][j] = val;
            }
        }

        return *this;
    }

    template <class T>
    friend SimpleMat<T> SimpleVec<T>::operator*(const SimpleVec<T>& vec2) const ;

    template <class T>
    friend SimpleMat<T> operator*(const T& a, const SimpleMat<T>& vec);

    template <class T>
    friend std::ostream& operator<<(std::ostream& os, const SimpleMat<T>& vec);


private:
    std::vector<std::vector<Tdata> > mat_;
    int nrows_;
    int ncols_;
};


template <template<class> class Tvec, template<class> class Tmat, class Tdata>
class IncrementalStats {
public:
    explicit IncrementalStats(int dim): dim_(dim), N_(0) {
        mean_ = Tvec<Tdata>(dim);
        cov_ = Tmat<Tdata>(dim, dim);
        cov_square_ = Tmat<Tdata>(dim, dim);
        mean_ = 0;
        cov_ = 0;
    }

    void add_new_data(const Tvec<Tdata>& x) {
        // update mean
        ++N_;
        Tvec<Tdata> inc = ((1.0 / static_cast<Tdata>(N_)) * (x - mean_));
        mean_ = mean_ + inc;

        // update covariance
        cov_square_ = cov_square_ + (x * x);

        if (N_ > 1) {
            cov_ = (1.0 / static_cast<Tdata>(N_ - 1)) * (cov_square_ - (static_cast<Tdata>(N_) * (mean_ * mean_)));
        }
    }

    const Tvec<Tdata>& mean() const {
        return mean_;
    }

    const Tmat<Tdata>& cov() const {
        return cov_;
    }

private:
    int dim_;
    int N_;
    Tvec<Tdata> mean_;
    Tmat<Tdata> cov_;

    Tmat<Tdata> cov_square_;
};

// definitions
template <class Tdata>
SimpleMat<Tdata> SimpleVec<Tdata>::operator*(const SimpleVec<Tdata>& vec2) const {
    SimpleMat<Tdata> prod(len_, len_);

    for (int i = 0; i < len_; ++i) {
        for (int j = 0; j < len_; ++j) {
            prod.mat_[i][j] = vec_[i] * vec2.vec_[j];
        }
    }

    return prod;
}

template <class Tdata>
SimpleVec<Tdata> operator*(const Tdata& a, const SimpleVec<Tdata>& vec) {
    SimpleVec<Tdata> prod(vec.len_);

    for (int i = 0; i < vec.len_; ++i)
        prod.vec_[i] = a * vec.vec_[i];

    return prod;
}

template <class Tdata>
SimpleMat<Tdata> operator*(const Tdata& a, const SimpleMat<Tdata>& mat) {
    SimpleMat<Tdata> prod(mat.nrows_, mat.ncols_);

    for (int i = 0; i < mat.nrows_; ++i) {
        for (int j = 0; j < mat.ncols_; ++j) {
            prod.mat_[i][j] = a * mat.mat_[i][j];
        }
    }

    return prod;
}

template <class Tdata>
std::ostream& operator<<(std::ostream& os, const SimpleVec<Tdata>& vec) {
    os << vec.vec_[0];
    for (int i = 1; i < vec.len_; ++i)
        os << ", " << vec.vec_[i];
    os << std::endl;
}

template <class Tdata>
std::ostream& operator<<(std::ostream& os, const SimpleMat<Tdata>& mat) {
    for (int i = 0; i < mat.nrows_; ++i) {
        os << mat.mat_[i][0];
        for (int j = 1; j < mat.ncols_; ++j) {
            os << ", " << mat.mat_[i][j];
        }
        os << std::endl;
    }
}

int main() {
    // test the simple vec and mat class
    std::vector<double> vec_data1 {1.0, 2.0, 3.0};
    std::vector<double> vec_data2 {3.0, 2.0, 1.0};
    std::vector<std::vector<double> > mat_data {{1, 2, 3}, {2, 3, 4}, {4, 5, 6}};

    SimpleVec<double> vec1(vec_data1);
    SimpleVec<double> vec2(vec_data2);
    SimpleMat<double> mat1(mat_data);
    SimpleMat<double> mat2(mat_data);

    std::cout << "Vector 1 is: " << vec1;
    std::cout << "Vector 2 is: " << vec2;
    std::cout << "Matrix is: " << std::endl;
    std::cout << mat1;

    std::cout << "vector1 + vector2 is: " << vec1 + vec2;
    std::cout << "outer product of vec1 and vec2 is: " << std::endl;
    std::cout << vec1 * vec2;

    std::cout << "matrix1 + matrix2 is: " << std::endl;
    std::cout << mat1 + mat2;

    // test the incremental statistics
    int dim = 3;
    IncrementalStats<SimpleVec, SimpleMat, double > stats(dim);

    int n_samples = 2500;
    std::vector<double> true_mean_data {5, 5, 5};
    SimpleVec<double> true_mean(true_mean_data);

    double var = 2.0;
    std::default_random_engine generator;
    std::normal_distribution<double> distribution(0.0, var);

    for (int i = 0; i <= n_samples*2; ++i) {
        // generate noise
        SimpleVec<double> noise(dim);
        for (int j = 0; j < dim; ++j)
            noise[j] = distribution(generator);

        SimpleVec<double> meas = true_mean + noise;

        stats.add_new_data(meas);

        if (i % 500 == 0) {
            std::cout << "Mean of first " << i << " samples: " << stats.mean();
            std::cout << "Covariance of first " << i << " samples: " << std::endl;
            std::cout << stats.cov();
        }
    }

    return 0;
}