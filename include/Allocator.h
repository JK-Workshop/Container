// Copyright (C) JK Workshop - All rights reserved

#pragma once

namespace JK::Containers {

    template<class TYPE, size_t SIZE> class Allocator {

    private:

    public:

        Allocator(TYPE* p_dataPtr) : dataPtr(p_dataPtr) {
            
        }

        Allocator(TYPE* p_dataRef) : dataRef(p_dataRef) {

        }

        ~Allocator() {

        }

        } Allocator<int, 5> allocator(data)

    };
}