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
        template <class Q, class W, class E, class R>
        constexpr Mat(const Vec4<Q>& m1, const Vec4<W>& m2, const Vec4<E>& m3, const Vec4<R>& m4) noexcept
                : _Stg{RowType(m1), RowType(m2), RowType(m3), RowType(m4)} { }
        template <class Q, class W, class E, class R,
                  class A, class S, class D, class F,
                  class Z, class X, class C, class V,
                  class Y, class U, class I, class O>
        constexpr Mat(Q&& m11, W&& m12, E&& m13, R&& m14,
                A&& m21, S&& m22, D&& m23, F&& m24,
                Z&& m31, X&& m32, C&& m33, V&& m34,
                T&& m41, Y&& m42, I&& m43, O&& m44) noexcept
                :_Stg{{std::forward<Q>(m11), std::forward<W>(m12), std::forward<E>(m13), std::forward<R>(m14)},
                {std::forward<A>(m21), std::forward<S>(m22), std::forward<D>(m23), std::forward<F>(m24)},
                {std::forward<Z>(m31), std::forward<X>(m32), std::forward<C>(m33), std::forward<V>(m34)},
                {std::forward<Y>(m41), std::forward<U>(m42), std::forward<I>(m43), std::forward<O>(m44)}} { }

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
        template <class U, class = EnableIfNotVectorOrMatrix<U>>
        Mat& operator*=(const U& r) noexcept {
            _Stg[0] *= r;
            _Stg[1] *= r;
            _Stg[2] *= r;
            _Stg[3] *= r;
            return *this;
        }
        template <class U, class = EnableIfNotVectorOrMatrix<U>>
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
        template <class U, class = EnableIfNotVectorOrMatrix<U>>
        constexpr Mat operator*(const U& r) const noexcept { return {_Stg[0]*r, _Stg[1]*r, _Stg[2]*r, _Stg[3]*r}; }
        template <class U, class = EnableIfNotVectorOrMatrix<U>>
        constexpr Mat operator/(const U& r) const noexcept { return {_Stg[0]/r, _Stg[1]/r, _Stg[2]/r, _Stg[3]/r}; }
        constexpr auto operator*(const Mat<T, 4, 2>& r) const noexcept {
            return Mat<T, 4, 2> {
                    _Stg[0][0]*r(0, 0)+_Stg[0][1]*r(1, 0)+_Stg[0][2]*r(2, 0)+_Stg[0][2]*r(3, 0),
                    _Stg[0][0]*r(0, 1)+_Stg[0][1]*r(1, 1)+_Stg[0][2]*r(2, 1)+_Stg[0][2]*r(3, 1),
                    _Stg[1][0]*r(0, 0)+_Stg[1][1]*r(1, 0)+_Stg[1][2]*r(2, 0)+_Stg[1][2]*r(3, 0),
                    _Stg[1][0]*r(0, 1)+_Stg[1][1]*r(1, 1)+_Stg[1][2]*r(2, 1)+_Stg[1][2]*r(3, 1),
                    _Stg[2][0]*r(0, 0)+_Stg[2][1]*r(1, 0)+_Stg[2][2]*r(2, 0)+_Stg[2][2]*r(3, 0),
                    _Stg[2][0]*r(0, 1)+_Stg[2][1]*r(1, 1)+_Stg[2][2]*r(2, 1)+_Stg[2][2]*r(3, 1),
                    _Stg[3][0]*r(0, 0)+_Stg[3][1]*r(1, 0)+_Stg[3][2]*r(2, 0)+_Stg[3][2]*r(3, 0),
                    _Stg[3][0]*r(0, 1)+_Stg[3][1]*r(1, 1)+_Stg[3][2]*r(2, 1)+_Stg[3][2]*r(3, 1)
            };
        }
        constexpr auto operator*(const Mat<T, 4, 3>& r) const noexcept {
            return Mat<T, 4, 3> {
                    _Stg[0][0]*r(0, 0)+_Stg[0][1]*r(1, 0)+_Stg[0][2]*r(2, 0)+_Stg[0][2]*r(3, 0),
                    _Stg[0][0]*r(0, 1)+_Stg[0][1]*r(1, 1)+_Stg[0][2]*r(2, 1)+_Stg[0][2]*r(3, 1),
                    _Stg[0][0]*r(0, 2)+_Stg[0][1]*r(1, 2)+_Stg[0][2]*r(2, 2)+_Stg[0][2]*r(3, 2),
                    _Stg[1][0]*r(0, 0)+_Stg[1][1]*r(1, 0)+_Stg[1][2]*r(2, 0)+_Stg[1][2]*r(3, 0),
                    _Stg[1][0]*r(0, 1)+_Stg[1][1]*r(1, 1)+_Stg[1][2]*r(2, 1)+_Stg[1][2]*r(3, 1),
                    _Stg[1][0]*r(0, 2)+_Stg[1][1]*r(1, 2)+_Stg[1][2]*r(2, 2)+_Stg[1][2]*r(3, 2),
                    _Stg[2][0]*r(0, 0)+_Stg[2][1]*r(1, 0)+_Stg[2][2]*r(2, 0)+_Stg[2][2]*r(3, 0),
                    _Stg[2][0]*r(0, 1)+_Stg[2][1]*r(1, 1)+_Stg[2][2]*r(2, 1)+_Stg[2][2]*r(3, 1),
                    _Stg[2][0]*r(0, 2)+_Stg[2][1]*r(1, 2)+_Stg[2][2]*r(2, 2)+_Stg[2][2]*r(3, 2),
                    _Stg[3][0]*r(0, 0)+_Stg[3][1]*r(1, 0)+_Stg[3][2]*r(2, 0)+_Stg[3][2]*r(3, 0),
                    _Stg[3][0]*r(0, 1)+_Stg[3][1]*r(1, 1)+_Stg[3][2]*r(2, 1)+_Stg[3][2]*r(3, 1),
                    _Stg[3][0]*r(0, 2)+_Stg[3][1]*r(1, 2)+_Stg[3][2]*r(2, 2)+_Stg[3][2]*r(3, 2)
            };
        }
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
        template <int Cr, class = std::enable_if_t<(Cr > 4)>>
        constexpr auto operator*(const Mat<T, 4, Cr>& r) const noexcept {
            Mat<T, 3, Cr> ret{};
            for (auto j = 0u; j<Cr; ++j) {
                ret(0, j) += _Stg[0][0]*r(0, j)+_Stg[0][1]*r(1, j)+_Stg[0][2]*r(2, j)+_Stg[0][2]*r(3, j);
                ret(1, j) += _Stg[1][0]*r(0, j)+_Stg[1][1]*r(1, j)+_Stg[1][2]*r(2, j)+_Stg[1][2]*r(3, j);
                ret(2, j) += _Stg[2][0]*r(0, j)+_Stg[2][1]*r(1, j)+_Stg[2][2]*r(2, j)+_Stg[2][2]*r(3, j);
                ret(3, j) += _Stg[3][0]*r(0, j)+_Stg[3][1]*r(1, j)+_Stg[3][2]*r(2, j)+_Stg[3][2]*r(3, j);
            }
            return ret;
        }
        Mat& operator*=(const Mat& r) noexcept { return (*this = *this*r); }
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
