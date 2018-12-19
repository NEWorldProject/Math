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
        template <class Q, class W, class E>
        constexpr Mat(const Vec4<Q>& m1, const Vec4<W>& m2, const Vec4<E>& m3) noexcept
                : _Stg{RowType(m1), RowType(m2), RowType(m3)} { }
        template <class Q, class W, class E, class R,
                  class A, class S, class D, class F,
                  class Z, class X, class C, class V>
        constexpr Mat(Q&& m11, W&& m12, E&& m13, R&& m14,
                A&& m21, S&& m22, D&& m23, F&& m24,
                Z&& m31, X&& m32, C&& m33, V&& m34) noexcept
                :_Stg{{std::forward<Q>(m11), std::forward<W>(m12), std::forward<E>(m13), std::forward<R>(m14)},
                {std::forward<A>(m21), std::forward<S>(m22), std::forward<D>(m23), std::forward<F>(m24)},
                {std::forward<Z>(m31), std::forward<X>(m32), std::forward<C>(m33), std::forward<V>(m34)}} { }

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
        template <class U, class = EnableIfNotVectorOrMatrix<U>>
        Mat& operator*=(const U& r) noexcept {
            _Stg[0] *= r;
            _Stg[1] *= r;
            _Stg[2] *= r;
            return *this;
        }
        template <class U, class = EnableIfNotVectorOrMatrix<U>>
        Mat& operator/=(const U& r) noexcept {
            _Stg[0] /= r;
            _Stg[1] /= r;
            _Stg[2] /= r;
            return *this;
        }
        constexpr Mat operator-() const noexcept { return {-_Stg[0], -_Stg[1], -_Stg[2]}; }
        constexpr Mat operator+(const Mat& r) const noexcept { return {_Stg[0]+r[0], _Stg[1]+r[1], _Stg[2]+r[2]}; }
        constexpr Mat operator-(const Mat& r) const noexcept { return {_Stg[0]-r[0], _Stg[1]-r[1], _Stg[2]-r[2]}; }
        template <class U, class = EnableIfNotVectorOrMatrix<U>>
        constexpr Mat operator*(const U& r) const noexcept { return {_Stg[0]*r, _Stg[1]*r, _Stg[2]*r}; }
        template <class U, class = EnableIfNotVectorOrMatrix<U>>
        constexpr Mat operator/(const U& r) const noexcept { return {_Stg[0]/r, _Stg[1]/r, _Stg[2]/r}; }
        constexpr auto operator*(const Mat<T, 4, 2>& r) const noexcept {
            return Mat<T, 3, 2> {
                    _Stg[0][0]*r(0, 0)+_Stg[0][1]*r(1, 0)+_Stg[0][2]*r(2, 0)+_Stg[0][2]*r(3, 0),
                    _Stg[0][0]*r(0, 1)+_Stg[0][1]*r(1, 1)+_Stg[0][2]*r(2, 1)+_Stg[0][2]*r(3, 1),
                    _Stg[1][0]*r(0, 0)+_Stg[1][1]*r(1, 0)+_Stg[1][2]*r(2, 0)+_Stg[1][2]*r(3, 0),
                    _Stg[1][0]*r(0, 1)+_Stg[1][1]*r(1, 1)+_Stg[1][2]*r(2, 1)+_Stg[1][2]*r(3, 1),
                    _Stg[2][0]*r(0, 0)+_Stg[2][1]*r(1, 0)+_Stg[2][2]*r(2, 0)+_Stg[2][2]*r(3, 0),
                    _Stg[2][0]*r(0, 1)+_Stg[2][1]*r(1, 1)+_Stg[2][2]*r(2, 1)+_Stg[2][2]*r(3, 1)
            };
        }
        constexpr auto operator*(const Mat<T, 4, 3>& r) const noexcept {
            return Mat<T, 3, 3> {
                    _Stg[0][0]*r(0, 0)+_Stg[0][1]*r(1, 0)+_Stg[0][2]*r(2, 0)+_Stg[0][2]*r(3, 0),
                    _Stg[0][0]*r(0, 1)+_Stg[0][1]*r(1, 1)+_Stg[0][2]*r(2, 1)+_Stg[0][2]*r(3, 1),
                    _Stg[0][0]*r(0, 2)+_Stg[0][1]*r(1, 2)+_Stg[0][2]*r(2, 2)+_Stg[0][2]*r(3, 2),
                    _Stg[1][0]*r(0, 0)+_Stg[1][1]*r(1, 0)+_Stg[1][2]*r(2, 0)+_Stg[1][2]*r(3, 0),
                    _Stg[1][0]*r(0, 1)+_Stg[1][1]*r(1, 1)+_Stg[1][2]*r(2, 1)+_Stg[1][2]*r(3, 1),
                    _Stg[1][0]*r(0, 2)+_Stg[1][1]*r(1, 2)+_Stg[1][2]*r(2, 2)+_Stg[1][2]*r(3, 2),
                    _Stg[2][0]*r(0, 0)+_Stg[2][1]*r(1, 0)+_Stg[2][2]*r(2, 0)+_Stg[2][2]*r(3, 0),
                    _Stg[2][0]*r(0, 1)+_Stg[2][1]*r(1, 1)+_Stg[2][2]*r(2, 1)+_Stg[2][2]*r(3, 1),
                    _Stg[2][0]*r(0, 2)+_Stg[2][1]*r(1, 2)+_Stg[2][2]*r(2, 2)+_Stg[2][2]*r(3, 2)
            };
        }
        constexpr auto operator*(const Mat<T, 4, 4>& r) const noexcept {
            return Mat {
                    _Stg[0][0]*r(0, 0)+_Stg[0][1]*r(1, 0)+_Stg[0][2]*r(2, 0)+_Stg[0][2]*r(3, 0),
                    _Stg[0][0]*r(0, 1)+_Stg[0][1]*r(1, 1)+_Stg[0][2]*r(2, 1)+_Stg[0][2]*r(3, 1),
                    _Stg[0][0]*r(0, 2)+_Stg[0][1]*r(1, 2)+_Stg[0][2]*r(2, 2)+_Stg[0][2]*r(3, 2),
                    _Stg[0][0]*r(0, 3)+_Stg[0][1]*r(1, 3)+_Stg[0][2]*r(2, 3)+_Stg[0][2]*r(3, 3),
                    _Stg[1][0]*r(0, 0)+_Stg[1][1]*r(1, 0)+_Stg[1][2]*r(2, 0)+_Stg[1][2]*r(3, 0),
                    _Stg[1][0]*r(0, 1)+_Stg[1][1]*r(1, 1)+_Stg[1][2]*r(2, 1)+_Stg[1][2]*r(3, 1),
                    _Stg[1][0]*r(0, 2)+_Stg[1][1]*r(1, 2)+_Stg[1][2]*r(2, 2)+_Stg[1][2]*r(3, 2),
                    _Stg[1][0]*r(0, 3)+_Stg[1][1]*r(1, 3)+_Stg[1][2]*r(2, 3)+_Stg[1][2]*r(3, 3),
                    _Stg[2][0]*r(0, 0)+_Stg[2][1]*r(1, 0)+_Stg[2][2]*r(2, 0)+_Stg[2][2]*r(3, 0),
                    _Stg[2][0]*r(0, 1)+_Stg[2][1]*r(1, 1)+_Stg[2][2]*r(2, 1)+_Stg[2][2]*r(3, 1),
                    _Stg[2][0]*r(0, 2)+_Stg[2][1]*r(1, 2)+_Stg[2][2]*r(2, 2)+_Stg[2][2]*r(3, 2),
                    _Stg[2][0]*r(0, 3)+_Stg[2][1]*r(1, 3)+_Stg[2][2]*r(2, 3)+_Stg[2][2]*r(3, 3)
            };
        }
        template <int Cr, class = std::enable_if_t<(Cr > 4)>>
        constexpr auto operator*(const Mat<T, 4, Cr>& r) const noexcept {
            Mat<T, 3, Cr> ret{};
            for (auto j = 0u; j<Cr; ++j) {
                ret(0, j) += _Stg[0][0]*r(0, j)+_Stg[0][1]*r(1, j)+_Stg[0][2]*r(2, j)+_Stg[0][2]*r(3, j);
                ret(1, j) += _Stg[1][0]*r(0, j)+_Stg[1][1]*r(1, j)+_Stg[1][2]*r(2, j)+_Stg[1][2]*r(3, j);
                ret(2, j) += _Stg[2][0]*r(0, j)+_Stg[2][1]*r(1, j)+_Stg[2][2]*r(2, j)+_Stg[2][2]*r(3, j);
            }
            return ret;
        }
        Mat& operator*=(const Mat<T, 4, 4>& r) noexcept { return (*this = *this*r); }
    private:
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
