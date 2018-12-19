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
        template <class Q, class W, class E, class R>
        constexpr Mat(const Vec3<Q>& m1, const Vec3<W>& m2, const Vec3<E>& m3, const Vec3<R>& m4) noexcept
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
        constexpr auto operator*(const Mat<T, 3, 2>& r) const noexcept {
            return Mat<T, 4, 2> {
                    _Stg[0][0]*r(0, 0)+_Stg[0][1]*r(1, 0)+_Stg[0][2]*r(2, 0),
                    _Stg[0][0]*r(0, 1)+_Stg[0][1]*r(1, 1)+_Stg[0][2]*r(2, 1),
                    _Stg[1][0]*r(0, 0)+_Stg[1][1]*r(1, 0)+_Stg[1][2]*r(2, 0),
                    _Stg[1][0]*r(0, 1)+_Stg[1][1]*r(1, 1)+_Stg[1][2]*r(2, 1),
                    _Stg[2][0]*r(0, 0)+_Stg[2][1]*r(1, 0)+_Stg[2][2]*r(2, 0),
                    _Stg[2][0]*r(0, 1)+_Stg[2][1]*r(1, 1)+_Stg[2][2]*r(2, 1),
                    _Stg[3][0]*r(0, 0)+_Stg[3][1]*r(1, 0)+_Stg[3][2]*r(2, 0),
                    _Stg[3][0]*r(0, 1)+_Stg[3][1]*r(1, 1)+_Stg[3][2]*r(2, 1)
            };
        }
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
                    _Stg[2][0]*r(0, 2)+_Stg[2][1]*r(1, 2)+_Stg[2][2]*r(2, 2),
                    _Stg[3][0]*r(0, 0)+_Stg[3][1]*r(1, 0)+_Stg[3][2]*r(2, 0),
                    _Stg[3][0]*r(0, 1)+_Stg[3][1]*r(1, 1)+_Stg[3][2]*r(2, 1),
                    _Stg[3][0]*r(0, 2)+_Stg[3][1]*r(1, 2)+_Stg[3][2]*r(2, 2)
            };
        }
        constexpr auto operator*(const Mat<T, 3, 4>& r) const noexcept {
            return Mat<T, 4, 4> {
                    _Stg[0][0]*r(0, 0)+_Stg[0][1]*r(1, 0)+_Stg[0][2]*r(2, 0),
                    _Stg[0][0]*r(0, 1)+_Stg[0][1]*r(1, 1)+_Stg[0][2]*r(2, 1),
                    _Stg[0][0]*r(0, 2)+_Stg[0][1]*r(1, 2)+_Stg[0][2]*r(2, 2),
                    _Stg[0][0]*r(0, 3)+_Stg[0][1]*r(1, 3)+_Stg[0][2]*r(2, 3),
                    _Stg[1][0]*r(0, 0)+_Stg[1][1]*r(1, 0)+_Stg[1][2]*r(2, 0),
                    _Stg[1][0]*r(0, 1)+_Stg[1][1]*r(1, 1)+_Stg[1][2]*r(2, 1),
                    _Stg[1][0]*r(0, 2)+_Stg[1][1]*r(1, 2)+_Stg[1][2]*r(2, 2),
                    _Stg[1][0]*r(0, 3)+_Stg[1][1]*r(1, 3)+_Stg[1][2]*r(2, 3),
                    _Stg[2][0]*r(0, 0)+_Stg[2][1]*r(1, 0)+_Stg[2][2]*r(2, 0),
                    _Stg[2][0]*r(0, 1)+_Stg[2][1]*r(1, 1)+_Stg[2][2]*r(2, 1),
                    _Stg[2][0]*r(0, 2)+_Stg[2][1]*r(1, 2)+_Stg[2][2]*r(2, 2),
                    _Stg[2][0]*r(0, 3)+_Stg[2][1]*r(1, 3)+_Stg[2][2]*r(2, 3),
                    _Stg[3][0]*r(0, 0)+_Stg[3][1]*r(1, 0)+_Stg[3][2]*r(2, 0),
                    _Stg[3][0]*r(0, 1)+_Stg[3][1]*r(1, 1)+_Stg[3][2]*r(2, 1),
                    _Stg[3][0]*r(0, 2)+_Stg[3][1]*r(1, 2)+_Stg[3][2]*r(2, 2),
                    _Stg[3][0]*r(0, 3)+_Stg[3][1]*r(1, 3)+_Stg[3][2]*r(2, 3)
            };
        }
        template <int Cr, class = std::enable_if_t<(Cr > 4)>>
        constexpr auto operator*(const Mat<T, 3, Cr>& r) const noexcept {
            Mat<T, 4, Cr> ret{};
            for (auto j = 0u; j<Cr; ++j) {
                ret(0, j) += _Stg[0][0]*r(0, j)+_Stg[0][1]*r(1, j)+_Stg[0][2]*r(2, j);
                ret(1, j) += _Stg[1][0]*r(0, j)+_Stg[1][1]*r(1, j)+_Stg[1][2]*r(2, j);
                ret(2, j) += _Stg[2][0]*r(0, j)+_Stg[2][1]*r(1, j)+_Stg[2][2]*r(2, j);
                ret(3, j) += _Stg[3][0]*r(0, j)+_Stg[3][1]*r(1, j)+_Stg[3][2]*r(2, j);
            }
            return ret;
        }
        Mat& operator*=(const Mat& r) noexcept { return (*this = *this * r); }
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
