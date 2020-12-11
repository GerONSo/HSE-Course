#pragma once

#include "typelist.h"

template<typename TList, typename TargetType>
struct IndexOf;

template<typename H, typename T, typename TargetType>
struct IndexOf<TypeList<H, T>, TargetType> {
    private:
        enum {
            temp = IndexOf<T, TargetType>::pos
        };
    public:
        enum {
            pos = (temp == -1) ? -1 : 1 + temp
        };
};

template<typename TargetType>
struct IndexOf<NullType, TargetType> {
    enum {
        pos = -1
    };
};

template<typename H, typename T>
struct IndexOf<TypeList<H, T>, H> {
    enum {
        pos = 0
    };
};

