#pragma once

#include "typelist.h"

template<typename TList, typename OldType, typename NewType> 
struct Replace;

template<typename H, typename T, typename OldType, typename NewType>
struct Replace<TypeList<H, T>, OldType, NewType> {
    typedef TypeList<H, typename Replace<T, OldType, NewType>::NewTypeList> NewTypeList;
};

template<typename OldType, typename T, typename NewType>
struct Replace<TypeList<OldType, T>, OldType, NewType> {
    typedef TypeList<NewType, typename Replace<T, OldType, NewType>::NewTypeList> NewTypeList;
};

template<typename OldType, typename NewType>
struct Replace<NullType, OldType, NewType> {
    typedef NullType NewTypeList;
};