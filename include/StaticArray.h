// Copyright

#pragma once

#include <CompileTime.h>

namespace JK::Continers {

    template<class TYPE, size_t SIZE, bool COUNT_CHECK, class ALLOCATOR, class ITERATOR> class StaticArray {
        static_assert(std::is_object_v<TYPE>, "Please provide a basic type or class");
    private:

        TYPE* data;
        constexpr size_t count; 
        constexpr ALLOCATOR allocator;
        constexpr ITERATOR iterator;

        constexpr TYPE& begin() const {
            return this->data[0];
        }

        constexpr TYPE& end() const {
            return this->data[this->Size()];
        }
        
    public:

        StaticArray()
            : data(new TYPE[SIZE]), count(0) {

        }

        StaticArray((TYPE*)&& p_existingArray)
            : data(std::move(p_existingArray)) {

        }

        ~StaticArray() {
            delete[] this->data;
        }

        [[nodiscard("Queried field not used")]] constexpr size_t Size() const {
            return SIZE;
        }

        [[nodiscard("Queried field not used")]] constexpr size_t Count() const {
            return this->count;
        }

        [[nodiscard("Not used data")]] constexpr TYPE& operator[](size_t p_index) {
            assert(p_index >= this->Size(), "Index out of bound\n");
            return this->data[p_index];
        }

        [[nodiscard]] constexpr void operator=(StaticArray& other) {
            
        }

    };

    template<class TYPE, size_t SIZE> using StaticArray<TYPE, SIZE> = StaticArray<TYPE, SIZE, JK_DIASABLE_COUNT, /* Specify default allocator*/, /* Specify default iterator */>;
}