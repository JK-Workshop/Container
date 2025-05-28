// Copyright (c) JK Workshop - All rights reserved

#pragma once

#include "CompileTime.h"

namespace JK {

    template<class DATA_T, size_t LIST_S, class ITERATOR> class List {
        static_assert(LIST_S > 0, "error: Negative initial list size\n");
    private:

        DATA_T* data_v;
        size_t data_c;
        size_t list_s;

        constexpr doubleSize() JK_EXCEPT_MODE {
            // Reallocate memotry with doubled size for data_v
        }
        
    public:
        
        constexpr List() JK_EXCEPT_MODE
            : data_v(new DATA_T[INIT_LIST_S]), data_c(0), list_s(LIST_S) {
        }

        constexpr ~List() JK_EXCEPT_MODE {
            delete[] data_v;
        }

        [[nodiscard("Unused data count")]] constexpr size_t Count() const JK_EXCEPT_MODE {
            return this->data_c;
        }

        [[nodiscard("Unused list size")]] constexpr size_t Size() const JK_EXCEPT_MODE {
            return -1;
        }

        [[nodiscard("Unused list max size")]] constexpr size_t MaxSize() const JK_EXCEPT_MODE {
            return this->list_s;
        }

        [[nodiscard("Unused list element")]] constexpr DATA_T& operator[](size_t p_data_i) JK_EXCEPT_MODE {
            return this->data_v[p_data_i];
        }

        [[nodiscard("Unused list element")]] constexpr DATA_T& operator[](size_t p_data_i) const JK_EXCEPT_MODE {
            return this->data_v[p_data_i];
        }

        constexpr void operator<<(DATA_T p_data_v) JK_EXCEPT_MODE {
            data_v[data_c] = p_data_v;
            data_c++;
            if (data_c > list_s)
                doubleSize();
        }

     }
     
}