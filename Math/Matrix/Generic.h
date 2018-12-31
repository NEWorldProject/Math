#pragma once

#include "Base.h"

namespace Math {
    template <class T, int R, int C>
    class Mat {
    public:
        using DataType = T;
        using RowType = Vec<C, T>;
        using ColType = Vec<R, T>;

        constexpr Mat() noexcept = default;
        template <class ...U>
        constexpr explicit Mat(U&&... args) noexcept : _Stg{std::forward<U>(args)...} {}

        RowType& operator[](int idx) noexcept { return _Stg[idx]; }
        const RowType& operator[](int idx) const noexcept { return _Stg[idx]; }
        DataType& operator()(int row, int col) noexcept { return _Stg[row][col]; }
        const DataType& operator()(int row, int col) const noexcept { return _Stg[row][col]; }

        constexpr Mat operator-() const noexcept {
            Mat ret{};
            for (auto i = 0; i<R; ++i) ret[i] = -(*this)[i];
            return ret;
        }

        constexpr Mat operator+(const Mat& r) const noexcept {
            Mat ret = r;
            for (auto i = 0; i<R; ++i) ret[i] += (*this)[i];
            return ret;
        }

        constexpr Mat operator-(const Mat& r) const noexcept {
            Mat ret = r;
            for (auto i = 0; i<R; ++i) ret[i] -= (*this)[i];
            return ret;
        }

        template <class U, class = EnableIfNotVectorOrMatrix<U>>
        constexpr Mat operator*(const U& r) const noexcept {
            Mat ret = r;
            for (auto i = 0; i<R; ++i) ret[i] *= r;
            return ret;
        }

        template <class U, class = EnableIfNotVectorOrMatrix<U>>
        constexpr Mat operator/(const U& r) const noexcept {
            Mat ret = r;
            for (auto i = 0; i<R; ++i) ret[i] /= r;
            return ret;
        }

        Mat& operator+=(const Mat& r) noexcept {
            for (auto i = 0; i<R; ++i) (*this)[i] += r[i];
            return *this;
        }

        Mat& operator-=(const Mat& r) noexcept {
            for (auto i = 0; i<R; ++i) (*this)[i] -= r[i];
            return *this;
        }

        template <class U, class = EnableIfNotVectorOrMatrix<U>>
        Mat& operator*=(const U& r) noexcept {
            for (auto i = 0; i<R; ++i) (*this)[i] *= r;
            return *this;
        }

        template <class U, class = EnableIfNotVectorOrMatrix<U>>
        Mat& operator/=(const U& r) noexcept {
            for (auto i = 0; i<R; ++i) (*this)[i] /= r;
            return *this;
        }

        template <int Cr>
        constexpr auto operator*(const Mat<T, C, Cr>& op) const noexcept {
            Mat<T, R, Cr> ret{};
            for (auto i = 0u; i<R; ++i)
                for (auto j = 0u; j<Cr; ++j)
                    for (auto k = 0u; k<C; ++k)
                        ret(i, j) += (*this)(i, k)*op(k, j);
            return ret;
        }

        constexpr auto operator*(const Vec<C, T>& op) const noexcept {
            Vec<R, T> ret{};
            for (auto i = 0u; i<R; ++i)
                for (auto k = 0u; k<C; ++k)
                    ret.Data[i] += (*this)(i, k)*op.Data[k];
            return ret;
        }

        Mat& operator*=(const Mat<T, C, C>& r) noexcept { return (*this = *this*r); }
    private:
        RowType _Stg[R];
    };
}
