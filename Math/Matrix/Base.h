#pragma once

#include "../Vector.h"

namespace Math {
    template <class T, int R, int C> class Mat;

    template <class T> struct IsNotVectorOrMatrix : std::true_type {};
    template <class T, int R, int C> struct IsNotVectorOrMatrix<Mat<T, R, C>> : std::false_type {};
    template <size_t D, class T> struct IsNotVectorOrMatrix<Vec<D, T>> : std::false_type {};
    template <class T>
    using EnableIfNotVectorOrMatrix = std::enable_if_t<IsNotVectorOrMatrix<T>::value>;

}
