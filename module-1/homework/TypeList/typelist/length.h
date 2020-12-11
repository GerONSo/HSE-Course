#pragma once

#include "typelist.h"

template<typename TList> 
struct Length;

template<>
struct Length<NullType> {
    enum {
        length = 0
    };
};

template<typename H, typename T> 
struct Length<TypeList<H, T>> {
    enum {
        length = Length<T>::length + 1
    };
};