#pragma once

#include "Base.h"

namespace Math {
    template <class T>
    class Mat<T, 4, 2> {
    public:
        using DataType = T;
        using RowType = Vec2<T>;
        using ColType = Vec4<T>;

        constexpr Mat() = default;
        template <class Q, class W>
        constexpr Mat(const Vec2<Q>& m1, const Vec2<W>& m2, const Vec2<Q>& m3, const Vec2<W>& m4) noexcept
                : _Stg{RowType(m1), RowType(m2), RowType(m3), RowType(m4)} { }
        template <class Q, class W, class A, class S, class Z, class X, class Y, class U>
        constexpr Mat(const Q& m11, const W& m12,
                const A& m21, const S& m22,
                const Z& m31, const X& m32,
                const Y& m41, const U& m42) noexcept
                :_Stg{{static_cast<T>(m11), static_cast<T>(m12)},
                {static_cast<T>(m21), static_cast<T>(m22)},
                {static_cast<T>(m31), static_cast<T>(m32)},
                {static_cast<T>(m41), static_cast<T>(m42)}} { }

        RowType& operator[](int idx) noexcept { return _Stg[idx]; }
        const RowType& operator[](int idx) const noexcept { return _Stg[idx]; }
        DataType& operator()(int row, int col) noexcept { return _Stg[row][col]; }
        const DataType& operator()(int row, int col) const noexcept { return _Stg[row][col]; }

        Mat& operator+=(const Mat& r) noexcept {
            _Stg[0] += r[0];
            _Stg[1] += r[1];
            _Stg[2] += r[2];
            _Stg[3] += r[3];
            return *this;
        }
        Mat& operator-=(const Mat& r) noexcept {
            _Stg[0] -= r[0];
            _Stg[1] -= r[1];
            _Stg[2] -= r[2];
            _Stg[3] -= r[3];
            return *this;
        }
        template <class U>
        Mat& operator*=(const U& r) noexcept {
            _Stg[0] *= r;
            _Stg[1] *= r;
            _Stg[2] *= r;
            _Stg[3] *= r;
            return *this;
        }
        template <class U>
        Mat& operator/=(const U& r) noexcept {
            _Stg[0] /= r;
            _Stg[1] /= r;
            _Stg[2] /= r;
            _Stg[3] /= r;
            return *this;
        }
        constexpr Mat operator-() const noexcept { return {-_Stg[0], -_Stg[1], -_Stg[2], -_Stg[3]}; }
        constexpr Mat operator+(const Mat& r) const noexcept {
            return {_Stg[0]+r[0], _Stg[1]+r[1], _Stg[2]+r[2], _Stg[3]+r[3]};
        }
        constexpr Mat operator-(const Mat& r) const noexcept {
            return {_Stg[0]-r[0], _Stg[1]-r[1], _Stg[2]-r[2], _Stg[3]-r[3]}; }
        template <class U>
        constexpr Mat operator*(const U& r) const noexcept { return {_Stg[0]*r, _Stg[1]*r, _Stg[2]*r, _Stg[3]*r}; }
        template <class U>
        constexpr Mat operator/(const U& r) const noexcept { return {_Stg[0]/r, _Stg[1]/r, _Stg[2]/r, _Stg[3]/r}; }
    private:
        RowType _Stg[4];
    };

    template <class T>
    using Mat42 = Mat<T, 4, 2>;
    using Mat42I = Mat42<int>;
    using Mat42B = Mat42<int8_t>;
    using Mat42S = Mat42<int16_t>;
    using Mat42L = Mat42<int32_t>;
    using Mat42LL = Mat42<int64_t>;
    using Mat42F = Mat42<float>;
    using Mat42D = Mat42<double>;
    using Mat42ED = Mat42<long double>;
}
