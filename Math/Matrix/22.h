#pragma once

#include "Base.h"

namespace Math {
    template <class T>
    class Mat<T, 2, 2> {
    public:
        using DataType = T;
        using RowType = Vec2<T>;
        using ColType = Vec2<T>;

        constexpr Mat() = default;
        template <class Q, class W>
        constexpr Mat(const Vec2<Q>& m1, const Vec2<W>& m2) noexcept
                : _Stg{RowType(m1), RowType(m2)} { }
        template <class Q, class W, class E, class R>
        constexpr Mat(Q&& m11, W&& m12, E&& m21, R&& m22) noexcept
                :_Stg{RowType{std::forward<Q>(m11), std::forward<W>(m12)},
                RowType{std::forward<E>(m21), std::forward<R>(m22)}} { }

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
        constexpr Mat operator*(const Mat& r) const noexcept {
            return {
                    _Stg[0][0]*r(0, 0)+_Stg[0][1]*r(1, 0),
                    _Stg[0][0]*r(0, 1)+_Stg[0][1]*r(1, 1),
                    _Stg[1][0]*r(0, 0)+_Stg[1][1]*r(1, 0),
                    _Stg[1][0]*r(0, 1)+_Stg[1][1]*r(1, 1)
            };
        }
        constexpr auto operator*(const Mat<T, 2, 3>& r) const noexcept {
            return Mat<T, 2, 3>{
                    _Stg[0][0]*r(0, 0)+_Stg[0][1]*r(1, 0),
                    _Stg[0][0]*r(0, 1)+_Stg[0][1]*r(1, 1),
                    _Stg[0][0]*r(0, 2)+_Stg[0][1]*r(1, 2),
                    _Stg[1][0]*r(0, 0)+_Stg[1][1]*r(1, 0),
                    _Stg[1][0]*r(0, 1)+_Stg[1][1]*r(1, 1),
                    _Stg[1][0]*r(0, 2)+_Stg[1][1]*r(1, 2)
            };
        }
        constexpr auto operator*(const Mat<T, 2, 4>& r) const noexcept {
            return Mat<T, 2, 4>{
                    _Stg[0][0]*r(0, 0)+_Stg[0][1]*r(1, 0),
                    _Stg[0][0]*r(0, 1)+_Stg[0][1]*r(1, 1),
                    _Stg[0][0]*r(0, 2)+_Stg[0][1]*r(1, 2),
                    _Stg[0][0]*r(0, 3)+_Stg[0][1]*r(1, 3),
                    _Stg[1][0]*r(0, 0)+_Stg[1][1]*r(1, 0),
                    _Stg[1][0]*r(0, 1)+_Stg[1][1]*r(1, 1),
                    _Stg[1][0]*r(0, 2)+_Stg[1][1]*r(1, 2),
                    _Stg[1][0]*r(0, 3)+_Stg[1][1]*r(1, 3)
            };
        }
        template <int Cr, class = std::enable_if_t<(Cr>4)>>
        constexpr auto operator*(const Mat<T, 2, Cr>& r) const noexcept {
            Mat<T, 2, Cr> ret{};
            for (auto j = 0u; j<Cr; ++j) {
                ret(0, j) += _Stg[0][0]*r(0, j)+_Stg[0][1]*r(1, j);
                ret(1, j) += _Stg[1][0]*r(0, j)+_Stg[1][1]*r(1, j);
            }
            return ret;
        }
        constexpr auto operator*(const Vec2<T>& r) const noexcept {
            return Vec2<T>(_Stg[0][0]*r.X+_Stg[0][1]*r.Y, _Stg[1][0]*r.X+_Stg[1][1]*r.Y);
        }
        Mat& operator*=(const Mat& r) noexcept { return (*this = *this*r); }
        constexpr static Mat Identity() noexcept {
            return {
                    1.0, 0.0,
                    0.0, 1.0
            };
        }
    private:
        RowType _Stg[2];
    };

    template <class T>
    constexpr auto operator*(const Vec<2, T>& l, const Mat<T, 2, 2>& r) noexcept {
        return Vec<2, T>{l.X*r(0, 0)+l.Y*r(1, 0), l.X*r(0, 1)+l.Y*r(1, 1)};
    }

    template <class T>
    using Mat2 = Mat<T, 2, 2>;
    using Mat2I = Mat2<int>;
    using Mat2B = Mat2<int8_t>;
    using Mat2S = Mat2<int16_t>;
    using Mat2L = Mat2<int32_t>;
    using Mat2LL = Mat2<int64_t>;
    using Mat2F = Mat2<float>;
    using Mat2D = Mat2<double>;
    using Mat2ED = Mat2<long double>;
    using Mat22I = Mat2I;
    using Mat22B = Mat2B;
    using Mat22S = Mat2S;
    using Mat22L = Mat2L;
    using Mat22LL = Mat2LL;
    using Mat22F = Mat2F;
    using Mat22D = Mat2D;
    using Mat22ED = Mat2ED;
}
