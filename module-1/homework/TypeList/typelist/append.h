#pragma once

#include "typelist.h"

template<typename TList, typename NewType>
struct Append;

template<typename H, typename T, typename NewType>
struct Append<TypeList<H, T>, NewType> {
    typedef TypeList<H, typename Append<T, NewType>::NewTypeList> NewTypeList;
};

template<>
struct Append<NullType, NullType> {
    typedef NullType NewTypeList;
};

template<typename NewType>
struct Append<NullType, NewType> {
    typedef TypeList<NewType, NullType> NewTypeList;
};



