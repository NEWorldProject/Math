#pragma once

#include "../Vector.h"

namespace Math {

    template <class T, int C, int Cr, class = std::enable_if_t<(C > 4)>>
    constexpr auto operator*(const Vec<C, T>& l, const Mat<T, C, Cr>& r) noexcept {
        Vec<Cr, T> ret{};
        for (auto j = 0u; j<Cr; ++j)
            for (auto k = 0u; k<C; ++k)
                ret.Data[j] += l.Data[k]*r(k, j);
        return ret;
    }

    template <class T, int C>
    constexpr auto& operator*=(Vec<C, T>& l, const Mat<T, C, C>& r) noexcept { return (l = l * r); }

    template <class T, int Cr, class = std::enable_if_t<(Cr > 4)>>
    constexpr auto operator*(const Vec<2, T>& l, const Mat<T, 2, Cr>& r) noexcept {
        Vec<Cr, T> ret{VectorUninitialized};
        for (auto j = 0u; j<Cr; ++j)
            ret.Data[j] = l.X*r(0, j) + l.Y*r(1, j);
        return ret;
    }

    template <class T, int Cr, class = std::enable_if_t<(Cr > 4)>>
    constexpr auto operator*(const Vec<3, T>& l, const Mat<T, 3, Cr>& r) noexcept {
        Vec<Cr, T> ret{VectorUninitialized};
        for (auto j = 0u; j<Cr; ++j)
            ret.Data[j] = l.X*r(0, j) + l.Y*r(1, j) + l.Z*r(2, j);
        return ret;
    }

    template <class T, int Cr, class = std::enable_if_t<(Cr > 4)>>
    constexpr auto operator*(const Vec<4, T>& l, const Mat<T, 4, Cr>& r) noexcept {
        Vec<Cr, T> ret{VectorUninitialized};
        for (auto j = 0u; j<Cr; ++j)
            ret.Data[j] = l.X*r(0, j) + l.Y*r(1, j) + l.Z*r(2, j) + l.T*r(3, j);
        return ret;
    }

    template <class T, int R, int C>
    constexpr auto operator*(const Mat<T, R, C>& l, const Vec<C, T>& r) noexcept {
        Vec<R, T> ret{};
        for (auto i = 0u; i<R; ++i)
            for (auto k = 0u; k<C; ++k)
                ret.Data[i] += l(i, k)*r.Data[k];
        return ret;
    }

    template <class T, int R>
    constexpr auto operator*(const Mat<T, R, 2>& l, const Vec<2, T>& r) noexcept {
        Vec<R, T> ret{VectorUninitialized};
        for (auto i = 0u; i<R; ++i)
            ret.Data[i] = l(i, 0)*r.Data[0] + l(i, 1)*r.Data[1];
        return ret;
    }

    template <class T, int R>
    constexpr auto operator*(const Mat<T, R, 3>& l, const Vec<3, T>& r) noexcept {
        Vec<R, T> ret{VectorUninitialized};
        for (auto i = 0u; i<R; ++i)
            ret.Data[i] = l(i, 0)*r.Data[0] + l(i, 1)*r.Data[1] + l(i, 2)*r.Data[2];
        return ret;
    }

    template <class T, int R>
    constexpr auto operator*(const Mat<T, R, 4>& l, const Vec<4, T>& r) noexcept {
        Vec<R, T> ret{VectorUninitialized};
        for (auto i = 0u; i<R; ++i)
            ret.Data[i] = l(i, 0)*r.Data[0] + l(i, 1)*r.Data[1] + l(i, 2)*r.Data[2] + l(i, 3)*r.Data[3];
        return ret;
    }

}
