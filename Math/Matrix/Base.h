#pragma once

#include "../Vector.h"

namespace Math {
    template <class T, int R, int C> class Mat;

    template <class T> struct IsNotVectorOrMatrix : std::true_type {};
    template <class T, int R, int C> struct IsNotVectorOrMatrix<Mat<T, R, C>> : std::false_type {};
    template <size_t D, class T> struct IsNotVectorOrMatrix<Vec<D, T>> : std::false_type {};
    template <class T>
    using EnableIfNotVectorOrMatrix = std::enable_if_t<IsNotVectorOrMatrix<T>::value>;

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

}
