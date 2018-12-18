#pragma once

#include "Base.h"

namespace Math {
    template <class T, int R, int C>
    class Mat {
    public:
        using DataType = T;
        using RowType = Vec<C, T>;
        using ColType = Vec<R, T>;

        RowType& operator[](int idx) noexcept { return _Stg[idx]; }
        const RowType& operator[](int idx) const noexcept { return _Stg[idx]; }
        DataType& operator()(int row, int col) noexcept { return _Stg[row][col]; }
        const DataType& operator()(int row, int col) const noexcept { return _Stg[row][col]; }

        constexpr Mat operator - () const noexcept {
            Mat ret {};
            for (auto i = 0; i < R; ++i) ret[i] = -(*this)[i];
            return ret;
        }

        constexpr Mat operator + (const Mat& r) const noexcept {
            Mat ret = r;
            for (auto i = 0; i < R; ++i) ret[i] += (*this)[i];
            return ret;
        }

        constexpr Mat operator - (const Mat& r) const noexcept {
            Mat ret = r;
            for (auto i = 0; i < R; ++i) ret[i] -= (*this)[i];
            return ret;
        }

        template <int Cr>
        constexpr auto operator*(const Mat<T, C, Cr>& op) const noexcept {
            Mat<T, R, Cr> ret {};
            for (auto i = 0u; i<R; ++i)
                for (auto j = 0u; j<Cr; ++j)
                    for (auto k = 0u; k<C; ++k)
                        ret(i, j) += (*this)(i, k)*op(k, j);
            return ret;
        }

        Mat& operator*=(const Mat<T, C, C>& r) noexcept { return (*this = *this * r); }
    private:
        RowType _Stg[R];
    };
}
