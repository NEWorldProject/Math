#pragma once

#include "Base.h"

namespace Math {
    template <class T>
    class Mat<T, 2, 2> {
    public:
        using DataType = T;
        using RowType = Vec2<T>;
        using ColType = Vec2<T>;

        constexpr Mat() = default;
        template <class Q, class W>
        constexpr Mat(const Vec2<Q>& m1, const Vec2<W>& m2) noexcept
                : _Stg{RowType(m1), RowType(m2)} { }
        template <class Q, class W, class E, class R>
        constexpr Mat(Q&& m11, W&& m12, E&& m21, R&& m22) noexcept
                :_Stg{{std::forward<Q>(m11), std::forward<W>(m12)}, {std::forward<E>(m21), std::forward<R>(m22)}} { }

        RowType& operator[](int idx) noexcept { return _Stg[idx]; }
        const RowType& operator[](int idx) const noexcept { return _Stg[idx]; }
        DataType& operator()(int row, int col) noexcept { return _Stg[row][col]; }
        const DataType& operator()(int row, int col) const noexcept { return _Stg[row][col]; }

        Mat& operator+=(const Mat& r) noexcept {
            _Stg[0] += r[0];
            _Stg[1] += r[1];
            return *this;
        }
        Mat& operator-=(const Mat& r) noexcept {
            _Stg[0] -= r[0];
            _Stg[1] -= r[1];
            return *this;
        }
        template <class U>
        Mat& operator*=(const U& r) noexcept {
            _Stg[0] *= r;
            _Stg[1] *= r;
            return *this;
        }
        template <class U>
        Mat& operator/=(const U& r) noexcept {
            _Stg[0] /= r;
            _Stg[1] /= r;
            return *this;
        }
        constexpr Mat operator-() const noexcept { return {-_Stg[0], -_Stg[1]}; }
        constexpr Mat operator+(const Mat& r) const noexcept { return {_Stg[0]+r[0], _Stg[1]+r[1]}; }
        constexpr Mat operator-(const Mat& r) const noexcept { return {_Stg[0]-r[0], _Stg[1]-r[1]}; }
        template <class U>
        constexpr Mat operator*(const U& r) const noexcept { return {_Stg[0]*r, _Stg[1]*r}; }
        template <class U>
        constexpr Mat operator/(const U& r) const noexcept { return {_Stg[0]/r, _Stg[1]/r}; }
        constexpr Mat operator*(const Mat& r) const noexcept {
            return {
                    _Stg[0][0]*r(0, 0)+_Stg[0][1]*r(1, 0),
                    _Stg[0][0]*r(0, 1)+_Stg[0][1]*r(1, 1),
                    _Stg[1][0]*r(0, 0)+_Stg[1][1]*r(1, 0),
                    _Stg[1][0]*r(0, 1)+_Stg[1][1]*r(1, 1)
            };
        }
        Mat& operator*=(const Mat& r) noexcept { return (*this = *this * r); }
    private:
        RowType _Stg[2];
    };

    template <class T>
    using Mat2 = Mat<T, 2, 2>;
    using Mat2I = Mat2<int>;
    using Mat2B = Mat2<int8_t>;
    using Mat2S = Mat2<int16_t>;
    using Mat2L = Mat2<int32_t>;
    using Mat2LL = Mat2<int64_t>;
    using Mat2F = Mat2<float>;
    using Mat2D = Mat2<double>;
    using Mat2ED = Mat2<long double>;
    using Mat22I = Mat2I;
    using Mat22B = Mat2B;
    using Mat22S = Mat2S;
    using Mat22L = Mat2L;
    using Mat22LL = Mat2LL;
    using Mat22F = Mat2F;
    using Mat22D = Mat2D;
    using Mat22ED = Mat2ED;
}
