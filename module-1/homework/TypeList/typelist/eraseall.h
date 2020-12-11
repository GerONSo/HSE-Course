#pragma once

#include "typelist.h"

template<typename TList, typename TargetType>
struct EraseAll;

template<typename H, typename T, typename TargetType>
struct EraseAll<TypeList<H, T>, TargetType> {
    typedef TypeList<H, typename EraseAll<T, TargetType>::NewTypeList> NewTypeList;
};

template<typename TargetType, typename T>
struct EraseAll<TypeList<TargetType, T>, TargetType> {
    typedef typename EraseAll<T, TargetType>::NewTypeList NewTypeList;
};

template<typename TargetType>
struct EraseAll<NullType, TargetType> {
    typedef NullType NewTypeList;
};