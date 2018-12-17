#pragma once

#include "Base.h"

namespace Math {
    template <class T>
    class Mat<T, 3, 2> {
    public:
        using DataType = T;
        using RowType = Vec2<T>;
        using ColType = Vec3<T>;

        constexpr Mat() = default;
        template <class Q, class W>
        constexpr Mat(const Vec2<Q>& m1, const Vec2<W>& m2, const Vec2<W>& m3) noexcept
                : _Stg{RowType(m1), RowType(m2), RowType(m3)} { }
        template <class Q, class W, class A, class S, class Z, class X>
        constexpr Mat(const Q& m11, const W& m12,
                const A& m21, const S& m22,
                const Z& m31, const X& m32) noexcept
                :_Stg{{static_cast<T>(m11), static_cast<T>(m12)},
                {static_cast<T>(m21), static_cast<T>(m22)},
                {static_cast<T>(m31), static_cast<T>(m32)}} { }

        RowType& operator[](int idx) noexcept { return _Stg[idx]; }
        const RowType& operator[](int idx) const noexcept { return _Stg[idx]; }
        DataType& operator()(int row, int col) noexcept { return _Stg[row][col]; }
        const DataType& operator()(int row, int col) const noexcept { return _Stg[row][col]; }

        Mat& operator+=(const Mat& r) noexcept {
            _Stg[0] += r[0];
            _Stg[1] += r[1];
            _Stg[2] += r[2];
            return *this;
        }
        Mat& operator-=(const Mat& r) noexcept {
            _Stg[0] -= r[0];
            _Stg[1] -= r[1];
            _Stg[2] -= r[2];
            return *this;
        }
        template <class U>
        Mat& operator*=(const U& r) noexcept {
            _Stg[0] *= r;
            _Stg[1] *= r;
            _Stg[2] *= r;
            return *this;
        }
        template <class U>
        Mat& operator/=(const U& r) noexcept {
            _Stg[0] /= r;
            _Stg[1] /= r;
            _Stg[2] /= r;
            return *this;
        }
        constexpr Mat operator-() const noexcept { return {-_Stg[0], -_Stg[1], -_Stg[2]}; }
        constexpr Mat operator+(const Mat& r) const noexcept { return {_Stg[0]+r[0], _Stg[1]+r[1], _Stg[2]+r[2]}; }
        constexpr Mat operator-(const Mat& r) const noexcept { return {_Stg[0]-r[0], _Stg[1]-r[1], _Stg[2]-r[2]}; }
        template <class U>
        constexpr Mat operator*(const U& r) const noexcept { return {_Stg[0]*r, _Stg[1]*r, _Stg[2]*r}; }
        template <class U>
        constexpr Mat operator/(const U& r) const noexcept { return {_Stg[0]/r, _Stg[1]/r, _Stg[2]/r}; }
    private:
        RowType _Stg[3];
    };

    template <class T>
    using Mat32 = Mat<T, 3, 2>;
    using Mat32I = Mat32<int>;
    using Mat32B = Mat32<int8_t>;
    using Mat32S = Mat32<int16_t>;
    using Mat32L = Mat32<int32_t>;
    using Mat32LL = Mat32<int64_t>;
    using Mat32F = Mat32<float>;
    using Mat32D = Mat32<double>;
    using Mat32ED = Mat32<long double>;
}