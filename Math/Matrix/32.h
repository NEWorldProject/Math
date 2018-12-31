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
        template <class Q, class W, class E>
        constexpr Mat(const Vec2<Q>& m1, const Vec2<W>& m2, const Vec2<E>& m3) noexcept
                : _Stg{RowType(m1), RowType(m2), RowType(m3)} { }
        template <class Q, class W, class A, class S, class Z, class X>
        constexpr Mat(Q&& m11, W&& m12,
                A&& m21, S&& m22,
                Z&& m31, X&& m32) noexcept
                :_Stg{{std::forward<Q>(m11), std::forward<W>(m12)},
                {std::forward<A>(m21), std::forward<S>(m22)},
                {std::forward<Z>(m31), std::forward<X>(m32)}} { }

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
        constexpr Mat operator*(const Mat<T, 2, 2>& r) const noexcept {
            return {
                    _Stg[0][0]*r(0, 0)+_Stg[0][1]*r(1, 0),
                    _Stg[0][0]*r(0, 1)+_Stg[0][1]*r(1, 1),
                    _Stg[1][0]*r(0, 0)+_Stg[1][1]*r(1, 0),
                    _Stg[1][0]*r(0, 1)+_Stg[1][1]*r(1, 1),
                    _Stg[2][0]*r(0, 0)+_Stg[2][1]*r(1, 0),
                    _Stg[2][0]*r(0, 1)+_Stg[2][1]*r(1, 1)
            };
        }
        constexpr auto operator*(const Mat<T, 2, 3>& r) const noexcept {
            return Mat<T, 3, 3>{
                    _Stg[0][0]*r(0, 0)+_Stg[0][1]*r(1, 0),
                    _Stg[0][0]*r(0, 1)+_Stg[0][1]*r(1, 1),
                    _Stg[0][0]*r(0, 2)+_Stg[0][1]*r(1, 2),
                    _Stg[1][0]*r(0, 0)+_Stg[1][1]*r(1, 0),
                    _Stg[1][0]*r(0, 1)+_Stg[1][1]*r(1, 1),
                    _Stg[1][0]*r(0, 2)+_Stg[1][1]*r(1, 2),
                    _Stg[2][0]*r(0, 0)+_Stg[2][1]*r(1, 0),
                    _Stg[2][0]*r(0, 1)+_Stg[2][1]*r(1, 1),
                    _Stg[2][0]*r(0, 2)+_Stg[2][1]*r(1, 2)
            };
        }
        constexpr auto operator*(const Mat<T, 2, 4>& r) const noexcept {
            return Mat<T, 3, 4>{
                    _Stg[0][0]*r(0, 0)+_Stg[0][1]*r(1, 0),
                    _Stg[0][0]*r(0, 1)+_Stg[0][1]*r(1, 1),
                    _Stg[0][0]*r(0, 2)+_Stg[0][1]*r(1, 2),
                    _Stg[0][0]*r(0, 3)+_Stg[0][1]*r(1, 3),
                    _Stg[1][0]*r(0, 0)+_Stg[1][1]*r(1, 0),
                    _Stg[1][0]*r(0, 1)+_Stg[1][1]*r(1, 1),
                    _Stg[1][0]*r(0, 2)+_Stg[1][1]*r(1, 2),
                    _Stg[1][0]*r(0, 3)+_Stg[1][1]*r(1, 3),
                    _Stg[2][0]*r(0, 0)+_Stg[2][1]*r(1, 0),
                    _Stg[2][0]*r(0, 1)+_Stg[2][1]*r(1, 1),
                    _Stg[2][0]*r(0, 2)+_Stg[2][1]*r(1, 2),
                    _Stg[2][0]*r(0, 3)+_Stg[2][1]*r(1, 3)
            };
        }
        template <int Cr, class = std::enable_if_t<(Cr > 4)>>
        constexpr auto operator*(const Mat<T, 2, Cr>& r) const noexcept {
            Mat<T, 3, Cr> ret{};
            for (auto j = 0u; j<Cr; ++j) {
                ret(0, j) += _Stg[0][0]*r(0, j)+_Stg[0][1]*r(1, j);
                ret(1, j) += _Stg[1][0]*r(0, j)+_Stg[1][1]*r(1, j);
                ret(2, j) += _Stg[2][0]*r(0, j)+_Stg[2][1]*r(1, j);
            }
            return ret;
        }
        Mat& operator*=(const Mat<T, 2, 2>& r) noexcept { return (*this = *this*r); }
        constexpr auto operator *(const Vec2<T>& r) const noexcept {
            return Vec3<T>(_Stg[0][0]*r.X+_Stg[0][1]*r.Y, _Stg[1][0]*r.X+_Stg[1][1]*r.Y, _Stg[2][0]*r.X+_Stg[2][1]*r.Y);
        }
    private:
        RowType _Stg[3];
    };

    template <class T>
    constexpr auto operator*(const Vec<3, T>& l, const Mat<T, 3, 2>& r) noexcept {
        return Vec<2, T> {l.X*r(0, 0) + l.Y*r(1, 0) + l.Z*r(2, 0), l.X*r(0, 1) + l.Y*r(1, 1) + l.Z*r(2, 1)};
    }

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
