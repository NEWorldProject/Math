#pragma once

#include <cmath>
#include <cstddef>
#include <utility>
#include <type_traits>

namespace Math {
    template <size_t D, class T>
    union Vec;

    template <class T, int R, int C> class Mat;

    template <class T> struct IsNotVectorOrMatrix : std::true_type {};
    template <class T, int R, int C> struct IsNotVectorOrMatrix<Mat<T, R, C>> : std::false_type {};
    template <size_t D, class T> struct IsNotVectorOrMatrix<Vec<D, T>> : std::false_type {};
    template <class T>
    using EnableIfNotVectorOrMatrix = std::enable_if_t<IsNotVectorOrMatrix<T>::value>;

    struct VectorUninitializedT{} VectorUninitialized;

    template <size_t D, class T>
    constexpr bool operator<(const Vec<D, T>& l, const Vec<D, T>& r) noexcept { return r.LengthSqr()<r.LengthSqr(); }
    template <size_t D, class T>
    constexpr bool operator>(const Vec<D, T>& l, const Vec<D, T>& r) noexcept { return r.LengthSqr()>r.LengthSqr(); }
    template <size_t D, class T>
    constexpr bool operator<=(const Vec<D, T>& l, const Vec<D, T>& r) noexcept { return r.LengthSqr()<=r.LengthSqr(); }
    template <size_t D, class T>
    constexpr bool operator>=(const Vec<D, T>& l, const Vec<D, T>& r) noexcept { return r.LengthSqr()>=r.LengthSqr(); }
    template <size_t D, class T, class U>
    constexpr auto operator*(const U& l, const Vec<D, T>& r) noexcept { return r*l; } // vec * n == n * vec
    template <size_t D, class T>
    constexpr auto Dot(const Vec<D, T>& l, const Vec<D, T>& r) noexcept { return l.Dot(r); }
}