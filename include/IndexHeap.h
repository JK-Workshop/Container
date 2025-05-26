// Copyright (C) JK Workshop - All rights reserved

#pragma once

#include <stdlib.h>
#include <stdint.h>

namespace JK {

    template<class CONTINER, class COMPARE> class IndexHeap {

    private:

        uint32_t data_c;
        CONTAINER data;
        CONTAINER indexHash;

        void update(uint32_t p_index) {
            while (p_index != 1 && heap->cmp(p_value, heap->head[p_index >> 1]) < 0) {
                heap->head[p_index] = heap->head[p_index >> 1];
                heap->hash[heap->head[p_index]] = p_index;
                p_index >>= 1;
            }
            heap->head[p_index] = p_value;
            heap->hash[p_value] = p_index;
        }
        
        void donwdate(uint32_t p_index) {

        }
#if (JK_OPTIMIZATION == JK_ALLIN_SPEED)

        void merge() {

        }

        void split() {

        }
#endif

    public:

        IndexHeap()
            : dataCounter(0) {
            // Allocate and initialize this->data and this->indexHash
        }
        IndexHeap(const IndexHeap& other) -> delete

        ~IndexHeap() {
            // Deallocate this->data and this->indexHash 
        }

        [[nodiscard("Queried field not used")]] constexpr size_t Size() const {
            return this->data.Size();
        }

        [[nodiscard("Queried field not used")]] constexpr size_t Count() const {
            return this->data.Count();
        }

        [[nodiscard("Queried field not used")]] constexpr bool Empty() const {
            return this->Count() == 0;
        }
#if (JK_OPTIMIZATION_LV == JK_NO_OPTIMIZATION)

#elif (JK_OPTIMIZATION_LV == JK_HALF_HALF)

#elif (JK_OPTIMIZATION_LV == JK_ALLIN_SPEED)

#elif (JK_OPTIMIZATION_LV == JK_ALLIN_SIZE)

        void Push(uint32_t p_value) {
            this->update(++heap->cnt);
        }

        uint32_t Pop() {
            uint32_t popped = heap->head[1];    // popped element
            uint32_t last = heap->head[heap->cnt--];
            uint32_t i = 1, j = heap->cnt >> 1;
            while (i <= j) {
                int min = i << 1;
                if ((min | 1) <= heap->cnt && heap->cmp(heap->head[min | 1], heap->head[min]) < 0) {
                    min |= 1;
                }
                if (heap->cmp(heap->head[min], last) < 0) {
                    heap->head[i] = heap->head[min];
                    heap->hash[heap->head[i]] = i;
                }
                else  break;
                i = min;
            }
            heap->head[i] = last;
            heap->hash[last] = i;
            return popped;
        }
#endif

        void operator<<(uint32_t p_value) { this->Push(p_value); }
        
        uint32_t operator>>() { return this->Pop(); }
    };

}