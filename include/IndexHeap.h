// Copyright (c) JK Workshop - All rights reserved

#pragma once

#include <stdlib.h>
#include <stdint.h>

#include "StaticArray.h"

namespace JK {

    enum class Heap_t {
        BINARY_HEAP,
        FIBONACCI_HEAP
    };

    template<class CONTINER, class COMPARE> class IndexHeap {

    private:

        constexpr size_t data_c;
        constexpr CONTAINER data_v;
        constexpr CONTAINER index_h;

        constexpr void update(size_t p_data_i) requires () {
            size_t target_v = this->data_v[p_data_i];
            while (p_data_i != 1 && COMPARE(target_v, this->data_v[p_data_i >> 1])) {
                this->data_v[p_data_i] = this->data_v[p_data_i >> 1];
                this->index_h[this->data_v[p_data_i]] = p_data_i;
                p_data_i >>= 1;
            }
            this->index_h[p_data_i] = target_v;
            this->index_h[target_v] = p_data_i;
        }
        
        constexpr void downdate(size_t p_data_i) {

        }

        constexpr void merge() {

        }

        constexpr void split() {

        }

    public:

        IndexHeap()
            : data_c(1), data_v(), index_h() {
        }

        ~IndexHeap() {
        }

        [[nodiscard("Unused index heap size")]] constexpr size_t Size() const {
            return this->data_v.Size();
        }

        [[nodiscard("Unsed index heap empty evaluation")]] constexpr bool Empty() const {
            return this->data_c == 0;
        }

        [[nodiscard("Unused index heap top")]] constexpr size_t Top() const {
            return this->data_v[1];
        }

        constexpr void Push(size_t p_data_v) {
            this->data_v[++this->data_c] = p_data_v;
            this->update(this->data_c);
        }

        constexpr void Pop(size_t& p_popped_v) requires () {
            p_popped_v = this->Top();
            this->data_v[1] = this->data_v[this->data_c];
            this->data_c--;
            this->downdata(1);
        }

        /*
        constexpr void operator<<(size_t p_data_v) {
            this->Push(p_data_v);
        }
        
        constexpr size_t operator>>() {
            return this->Pop();
        }

        constexpr size_t& operator[](size_t p_data_i) {

        }
        */
    };

}