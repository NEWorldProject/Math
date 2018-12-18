#pragma once

#include "Base.h"

namespace Math {
    template <class T>
    class Mat<T, 4, 3> {
    public:
        using DataType = T;
        using RowType = Vec3<T>;
        using ColType = Vec4<T>;

        constexpr Mat() = default;
        template <class Q, class W>
        constexpr Mat(const Vec3<Q>& m1, const Vec3<W>& m2, const Vec3<Q>& m3, const Vec3<W>& m4) noexcept
                : _Stg{RowType(m1), RowType(m2), RowType(m3), RowType(m4)} { }
        template <class Q, class W, class E,
                  class A, class S, class D,
                  class Z, class X, class C,
                  class Y, class U, class I>
        constexpr Mat(Q&& m11, W&& m12, E&& m13,
                A&& m21, S&& m22, D&& m23,
                Z&& m31, X&& m32, C&& m33,
                T&& m41, Y&& m42, I&& m43) noexcept
                :_Stg{{std::forward<Q>(m11), std::forward<W>(m12), std::forward<E>(m13)},
                {std::forward<A>(m21), std::forward<S>(m22), std::forward<D>(m23)},
                {std::forward<Z>(m31), std::forward<X>(m32), std::forward<C>(m33)},
                {std::forward<Y>(m41), std::forward<U>(m42), std::forward<I>(m43)}} { }

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
    private:
        RowType _Stg[4];
    };

    template <class T>
    using Mat43 = Mat<T, 4, 3>;
    using Mat43I = Mat43<int>;
    using Mat43B = Mat43<int8_t>;
    using Mat43S = Mat43<int16_t>;
    using Mat43L = Mat43<int32_t>;
    using Mat43LL = Mat43<int64_t>;
    using Mat43F = Mat43<float>;
    using Mat43D = Mat43<double>;
    using Mat43ED = Mat43<long double>;
}
