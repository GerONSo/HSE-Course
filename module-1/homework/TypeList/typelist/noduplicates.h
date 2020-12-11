#pragma once

#include "erase.h"
#include "typelist.h"

template<typename TList>
struct NoDuplicates;

template<typename H, typename T>
struct NoDuplicates<TypeList<H, T>> {
    private:
        typedef typename NoDuplicates<T>::NewTypeList TailNoDuplicates;
        typedef typename Erase<TailNoDuplicates, H>::NewTypeList TailNoHead;
    public:
        typedef TypeList<H, TailNoHead> NewTypeList;
};

template<>
struct NoDuplicates<NullType> {
    typedef NullType NewTypeList;
};