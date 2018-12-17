#pragma once

#include "Base.h"

namespace Math {
    template <class T>
    class Mat<T, 3, 4> {
    public:
        using DataType = T;
        using RowType = Vec4<T>;
        using ColType = Vec3<T>;

        constexpr Mat() = default;
        template <class Q, class W>
        constexpr Mat(const Vec4<Q>& m1, const Vec4<Q>& m2, const Vec4<W>& m3) noexcept
                : _Stg{RowType(m1), RowType(m2), RowType(m3)} { }
        template <class Q, class W, class E, class R,
                  class A, class S, class D, class F,
                  class Z, class X, class C, class V>
        constexpr Mat(const Q& m11, const W& m12, const E& m13, const R& m14,
                const A& m21, const S& m22, const D& m23, const F& m24,
                const Z& m31, const X& m32, const C& m33, const V& m34) noexcept
                :_Stg{{static_cast<T>(m11), static_cast<T>(m12), static_cast<T>(m13), static_cast<T>(m14)},
                {static_cast<T>(m21), static_cast<T>(m22), static_cast<T>(m23), static_cast<T>(m24)},
                {static_cast<T>(m31), static_cast<T>(m32), static_cast<T>(m33), static_cast<T>(m34)}} { }

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
    using Mat34 = Mat<T, 3, 4>;
    using Mat34I = Mat34<int>;
    using Mat34B = Mat34<int8_t>;
    using Mat34S = Mat34<int16_t>;
    using Mat34L = Mat34<int32_t>;
    using Mat34LL = Mat34<int64_t>;
    using Mat34F = Mat34<float>;
    using Mat34D = Mat34<double>;
    using Mat34ED = Mat34<long double>;
}
