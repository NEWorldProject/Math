#pragma once

#include <cmath>
#include <cstddef>
#include <utility>
#include <type_traits>

namespace Math {
    template <size_t D, class T>
    union Vec;

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