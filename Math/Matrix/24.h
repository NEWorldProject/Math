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
        constexpr Mat(Q&& m11, W&& m12, E&& m13, R&& m14,
                A&& m21, S&& m22, D&& m23, F&& m24) noexcept
                :_Stg{{std::forward<Q>(m11), std::forward<W>(m12), std::forward<E>(m13), std::forward<R>(m14)},
                        {std::forward<A>(m21), std::forward<S>(m22), std::forward<D>(m23), std::forward<F>(m24)}} { }

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
