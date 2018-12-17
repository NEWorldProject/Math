#pragma once

#include "Base.h"

namespace Math {
    template <class T>
    class Mat<T, 2, 4> {
    public:
        using DataType = T;
        using RowType = Vec4<T>;
        using ColType = Vec2<T>;

        constexpr Mat() = default;
        template <class Q, class W>
        constexpr Mat(const Vec4<Q>& m1, const Vec4<W>& m2) noexcept
                : _Stg{RowType(m1), RowType(m2)} { }
        template <class Q, class W, class E, class R, class A, class S, class D, class F>
        constexpr Mat(const Q& m11, const W& m12, const E& m13, const R& m14,
                const A& m21, const S& m22, const D& m23, const F& m24) noexcept
                :_Stg{{static_cast<T>(m11), static_cast<T>(m12), static_cast<T>(m13), static_cast<T>(m14)},
                        {static_cast<T>(m21), static_cast<T>(m22), static_cast<T>(m23), static_cast<T>(m24)}} { }

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
    private:
        RowType _Stg[2];
    };

    template <class T>
    using Mat24 = Mat<T, 2, 4>;
    using Mat24I = Mat24<int>;
    using Mat24B = Mat24<int8_t>;
    using Mat24S = Mat24<int16_t>;
    using Mat24L = Mat24<int32_t>;
    using Mat24LL = Mat24<int64_t>;
    using Mat24F = Mat24<float>;
    using Mat24D = Mat24<double>;
    using Mat2ED = Mat24<long double>;
}
