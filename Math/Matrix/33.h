#pragma once

#include "Base.h"

namespace Math {
    template <class T>
    class Mat<T, 3, 3> {
    public:
        using DataType = T;
        using RowType = Vec3<T>;
        using ColType = Vec3<T>;

        constexpr Mat() = default;
        template <class Q, class W>
        constexpr Mat(const Vec3<Q>& m1, const Vec3<W>& m2, const Vec3<W>& m3) noexcept
                : _Stg{RowType(m1), RowType(m2), RowType(m3)} { }
        template <class Q, class W, class E, class A, class S, class D, class Z, class X, class C>
        constexpr Mat(const Q& m11, const W& m12, const E& m13,
                const A& m21, const S& m22, const D& m23,
                const Z& m31, const X& m32, const C& m33) noexcept
                :_Stg{{static_cast<T>(m11), static_cast<T>(m12), static_cast<T>(m13)},
                {static_cast<T>(m21), static_cast<T>(m22), static_cast<T>(m23)},
                {static_cast<T>(m31), static_cast<T>(m32), static_cast<T>(m33)}} { }

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
        constexpr Mat operator*(const Mat& r) const noexcept {
            return {
                    _Stg[0][0]*r(0, 0)+_Stg[0][1]*r(1, 0)+_Stg[0][2]*r(2, 0),
                    _Stg[0][0]*r(0, 1)+_Stg[0][1]*r(1, 1)+_Stg[0][2]*r(2, 1),
                    _Stg[0][0]*r(0, 2)+_Stg[0][1]*r(1, 2)+_Stg[0][2]*r(2, 2),
                    _Stg[1][0]*r(0, 0)+_Stg[1][1]*r(1, 0)+_Stg[1][2]*r(2, 0),
                    _Stg[1][0]*r(0, 1)+_Stg[1][1]*r(1, 1)+_Stg[1][2]*r(2, 1),
                    _Stg[1][0]*r(0, 2)+_Stg[1][1]*r(1, 2)+_Stg[1][2]*r(2, 2),
                    _Stg[2][0]*r(0, 0)+_Stg[2][1]*r(1, 0)+_Stg[2][2]*r(2, 0),
                    _Stg[2][0]*r(0, 1)+_Stg[2][1]*r(1, 1)+_Stg[2][2]*r(2, 1),
                    _Stg[2][0]*r(0, 2)+_Stg[2][1]*r(1, 2)+_Stg[2][2]*r(2, 2)
            };
        }
        Mat& operator*=(const Mat& r) noexcept { return (*this = *this * r); }
    private:
        RowType _Stg[3];
    };

    template <class T>
    using Mat3 = Mat<T, 3, 3>;
    using Mat3I = Mat3<int>;
    using Mat3B = Mat3<int8_t>;
    using Mat3S = Mat3<int16_t>;
    using Mat3L = Mat3<int32_t>;
    using Mat3LL = Mat3<int64_t>;
    using Mat3F = Mat3<float>;
    using Mat3D = Mat3<double>;
    using Mat3ED = Mat3<long double>;
    using Mat33I = Mat3I;
    using Mat33B = Mat3B;
    using Mat33S = Mat3S;
    using Mat33L = Mat3L;
    using Mat33LL = Mat3LL;
    using Mat33F = Mat3F;
    using Mat33D = Mat3D;
    using Mat33ED = Mat3ED;
}
