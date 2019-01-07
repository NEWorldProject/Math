#pragma once

#include "Base.h"

namespace Math {
    template <class T>
    class Mat<T, 2, 3> {
    public:
        using DataType = T;
        using RowType = Vec3<T>;
        using ColType = Vec2<T>;

        constexpr Mat() = default;
        template <class Q, class W>
        constexpr Mat(const Vec3<Q>& m1, const Vec3<W>& m2) noexcept
                : _Stg{RowType(m1), RowType(m2)} { }
        template <class Q, class W, class E, class A, class S, class D>
        constexpr Mat(Q&& m11, W&& m12, E&& m13, A&& m21, S&& m22, D&& m23) noexcept
                :_Stg{RowType{std::forward<Q>(m11), std::forward<W>(m12), std::forward<E>(m13)},
                RowType{std::forward<A>(m21), std::forward<S>(m22), std::forward<D>(m23)}} { }

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
        template <class U, class = EnableIfNotVectorOrMatrix<U>>
        Mat& operator*=(const U& r) noexcept {
            _Stg[0] *= r;
            _Stg[1] *= r;
            return *this;
        }
        template <class U, class = EnableIfNotVectorOrMatrix<U>>
        Mat& operator/=(const U& r) noexcept {
            _Stg[0] /= r;
            _Stg[1] /= r;
            return *this;
        }
        constexpr Mat operator-() const noexcept { return {-_Stg[0], -_Stg[1]}; }
        constexpr Mat operator+(const Mat& r) const noexcept { return {_Stg[0]+r[0], _Stg[1]+r[1]}; }
        constexpr Mat operator-(const Mat& r) const noexcept { return {_Stg[0]-r[0], _Stg[1]-r[1]}; }
        template <class U, class = EnableIfNotVectorOrMatrix<U>>
        constexpr Mat operator*(const U& r) const noexcept { return {_Stg[0]*r, _Stg[1]*r}; }
        template <class U, class = EnableIfNotVectorOrMatrix<U>>
        constexpr Mat operator/(const U& r) const noexcept { return {_Stg[0]/r, _Stg[1]/r}; }
        constexpr auto operator*(const Mat<T, 3, 2>& r) const noexcept {
            return Mat<T, 2, 2> {
                    _Stg[0][0]*r(0, 0)+_Stg[0][1]*r(1, 0)+_Stg[0][2]*r(2, 0),
                    _Stg[0][0]*r(0, 1)+_Stg[0][1]*r(1, 1)+_Stg[0][2]*r(2, 1),
                    _Stg[1][0]*r(0, 0)+_Stg[1][1]*r(1, 0)+_Stg[1][2]*r(2, 0),
                    _Stg[1][0]*r(0, 1)+_Stg[1][1]*r(1, 1)+_Stg[1][2]*r(2, 1)
            };
        }
        constexpr auto operator*(const Mat<T, 3, 3>& r) const noexcept {
            return Mat {
                    _Stg[0][0]*r(0, 0)+_Stg[0][1]*r(1, 0)+_Stg[0][2]*r(2, 0),
                    _Stg[0][0]*r(0, 1)+_Stg[0][1]*r(1, 1)+_Stg[0][2]*r(2, 1),
                    _Stg[0][0]*r(0, 2)+_Stg[0][1]*r(1, 2)+_Stg[0][2]*r(2, 2),
                    _Stg[1][0]*r(0, 0)+_Stg[1][1]*r(1, 0)+_Stg[1][2]*r(2, 0),
                    _Stg[1][0]*r(0, 1)+_Stg[1][1]*r(1, 1)+_Stg[1][2]*r(2, 1),
                    _Stg[1][0]*r(0, 2)+_Stg[1][1]*r(1, 2)+_Stg[1][2]*r(2, 2)
            };
        }
        constexpr auto operator*(const Mat<T, 3, 4>& r) const noexcept {
            return Mat<T, 2, 4> {
                    _Stg[0][0]*r(0, 0)+_Stg[0][1]*r(1, 0)+_Stg[0][2]*r(2, 0),
                    _Stg[0][0]*r(0, 1)+_Stg[0][1]*r(1, 1)+_Stg[0][2]*r(2, 1),
                    _Stg[0][0]*r(0, 2)+_Stg[0][1]*r(1, 2)+_Stg[0][2]*r(2, 2),
                    _Stg[0][0]*r(0, 3)+_Stg[0][1]*r(1, 3)+_Stg[0][2]*r(2, 3),
                    _Stg[1][0]*r(0, 0)+_Stg[1][1]*r(1, 0)+_Stg[1][2]*r(2, 0),
                    _Stg[1][0]*r(0, 1)+_Stg[1][1]*r(1, 1)+_Stg[1][2]*r(2, 1),
                    _Stg[1][0]*r(0, 2)+_Stg[1][1]*r(1, 2)+_Stg[1][2]*r(2, 2),
                    _Stg[1][0]*r(0, 3)+_Stg[1][1]*r(1, 3)+_Stg[1][2]*r(2, 3)
            };
        }
        template <int Cr, class = std::enable_if_t<(Cr > 4)>>
        constexpr auto operator*(const Mat<T, 3, Cr>& r) const noexcept {
            Mat<T, 2, Cr> ret{};
            for (auto j = 0u; j<Cr; ++j) {
                ret(0, j) += _Stg[0][0]*r(0, j)+_Stg[0][1]*r(1, j)+_Stg[0][2]*r(2, j);
                ret(1, j) += _Stg[1][0]*r(0, j)+_Stg[1][1]*r(1, j)+_Stg[1][2]*r(2, j);
            }
            return ret;
        }
        Mat& operator*=(const Mat<T, 3, 3>& r) noexcept { return (*this = *this*r); }
        constexpr auto operator*(const Vec<3, T>& r) noexcept {
            return Vec<2, T>{_Stg[0][0]*r.Data[0]+_Stg[0][1]*r.Data[1]+_Stg[0][2]*r.Data[2],
                    _Stg[1][0]*r.Data[0]+_Stg[1][1]*r.Data[1]+_Stg[1][2]*r.Data[2]};
        }
    private:
        RowType _Stg[2];
    };

    template <class T>
    constexpr auto operator*(const Vec<2, T>& l, const Mat<T, 2, 3>& r) noexcept {
        return Vec<3, T> {l.X*r(0, 0) + l.Y*r(1, 0), l.X*r(0, 1) + l.Y*r(1, 1), l.X*r(0, 2) + l.Y*r(1, 2)};
    }

    template <class T>
    using Mat23 = Mat<T, 2, 3>;
    using Mat23I = Mat23<int>;
    using Mat23B = Mat23<int8_t>;
    using Mat23S = Mat23<int16_t>;
    using Mat23L = Mat23<int32_t>;
    using Mat23LL = Mat23<int64_t>;
    using Mat23F = Mat23<float>;
    using Mat23D = Mat23<double>;
    using Mat23ED = Mat23<long double>;
}
