#pragma once

#include "Base.h"

namespace Math {
    template <class T>
    class Mat<T, 4, 4> {
    public:
        using DataType = T;
        using RowType = Vec4<T>;
        using ColType = Vec4<T>;

        constexpr Mat() = default;
        template <class Q, class W>
        constexpr Mat(const Vec4<Q>& m1, const Vec4<W>& m2, const Vec4<Q>& m3, const Vec4<W>& m4) noexcept
                : _Stg{RowType(m1), RowType(m2), RowType(m3), RowType(m4)} { }
        template <class Q, class W, class E, class R,
                  class A, class S, class D, class F,
                  class Z, class X, class C, class V,
                  class Y, class U, class I, class O>
        constexpr Mat(const Q& m11, const W& m12, const E& m13, const R& m14,
                const A& m21, const S& m22, const D& m23, const F& m24,
                const Z& m31, const X& m32, const C& m33, const V& m34,
                const T& m41, const Y& m42, const I& m43, const O& m44) noexcept
                :_Stg{{static_cast<T>(m11), static_cast<T>(m12), static_cast<T>(m13), static_cast<T>(m14)},
                {static_cast<T>(m21), static_cast<T>(m22), static_cast<T>(m23), static_cast<T>(m24)},
                {static_cast<T>(m31), static_cast<T>(m32), static_cast<T>(m33), static_cast<T>(m34)},
                {static_cast<T>(m41), static_cast<T>(m42), static_cast<T>(m43), static_cast<T>(m44)}} { }

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
            return {_Stg[0]-r[0], _Stg[1]-r[1], _Stg[2]-r[2], _Stg[3]-r[3]};
        }
        template <class U>
        constexpr Mat operator*(const U& r) const noexcept { return {_Stg[0]*r, _Stg[1]*r, _Stg[2]*r, _Stg[3]*r}; }
        template <class U>
        constexpr Mat operator/(const U& r) const noexcept { return {_Stg[0]/r, _Stg[1]/r, _Stg[2]/r, _Stg[3]/r}; }
        constexpr Mat operator*(const Mat& r) const noexcept {
            return {
                    _Stg[0][0]*r(0, 0)+_Stg[0][1]*r(1, 0)+_Stg[0][2]*r(2, 0)+_Stg[0][3]*r(3, 0),
                    _Stg[0][0]*r(0, 1)+_Stg[0][1]*r(1, 1)+_Stg[0][2]*r(2, 1)+_Stg[0][3]*r(3, 1),
                    _Stg[0][0]*r(0, 2)+_Stg[0][1]*r(1, 2)+_Stg[0][2]*r(2, 2)+_Stg[0][3]*r(3, 2),
                    _Stg[0][0]*r(0, 3)+_Stg[0][1]*r(1, 3)+_Stg[0][2]*r(2, 3)+_Stg[0][3]*r(3, 3),
                    _Stg[1][0]*r(0, 0)+_Stg[1][1]*r(1, 0)+_Stg[1][2]*r(2, 0)+_Stg[1][3]*r(3, 0),
                    _Stg[1][0]*r(0, 1)+_Stg[1][1]*r(1, 1)+_Stg[1][2]*r(2, 1)+_Stg[1][3]*r(3, 1),
                    _Stg[1][0]*r(0, 2)+_Stg[1][1]*r(1, 2)+_Stg[1][2]*r(2, 2)+_Stg[1][3]*r(3, 2),
                    _Stg[1][0]*r(0, 3)+_Stg[1][1]*r(1, 3)+_Stg[1][2]*r(2, 3)+_Stg[1][3]*r(3, 3),
                    _Stg[2][0]*r(0, 0)+_Stg[2][1]*r(1, 0)+_Stg[2][2]*r(2, 0)+_Stg[2][3]*r(3, 0),
                    _Stg[2][0]*r(0, 1)+_Stg[2][1]*r(1, 1)+_Stg[2][2]*r(2, 1)+_Stg[2][3]*r(3, 1),
                    _Stg[2][0]*r(0, 2)+_Stg[2][1]*r(1, 2)+_Stg[2][2]*r(2, 2)+_Stg[2][3]*r(3, 2),
                    _Stg[2][0]*r(0, 3)+_Stg[2][1]*r(1, 3)+_Stg[2][2]*r(2, 3)+_Stg[2][3]*r(3, 3),
                    _Stg[3][0]*r(0, 0)+_Stg[3][1]*r(1, 0)+_Stg[3][2]*r(2, 0)+_Stg[3][3]*r(3, 0),
                    _Stg[3][0]*r(0, 1)+_Stg[3][1]*r(1, 1)+_Stg[3][2]*r(2, 1)+_Stg[3][3]*r(3, 1),
                    _Stg[3][0]*r(0, 2)+_Stg[3][1]*r(1, 2)+_Stg[3][2]*r(2, 2)+_Stg[3][3]*r(3, 2),
                    _Stg[3][0]*r(0, 3)+_Stg[3][1]*r(1, 3)+_Stg[3][2]*r(2, 3)+_Stg[3][3]*r(3, 3)
            };
        }
        Mat& operator*=(const Mat& r) noexcept { return (*this = *this * r); }
    private:
        RowType _Stg[4];
    };

    template <class T>
    using Mat4 = Mat<T, 4, 4>;
    using Mat4I = Mat4<int>;
    using Mat4B = Mat4<int8_t>;
    using Mat4S = Mat4<int16_t>;
    using Mat4L = Mat4<int32_t>;
    using Mat4LL = Mat4<int64_t>;
    using Mat4F = Mat4<float>;
    using Mat4D = Mat4<double>;
    using Mat4ED = Mat4<long double>;
    using Mat44I = Mat4I;
    using Mat44B = Mat4B;
    using Mat44S = Mat4S;
    using Mat44L = Mat4L;
    using Mat44LL = Mat4LL;
    using Mat44F = Mat4F;
    using Mat44D = Mat4D;
    using Mat44ED = Mat4ED;
}
