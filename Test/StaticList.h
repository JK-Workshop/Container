#pragma once

#include <print>

#include "../Include/List.h"

struct MyClass {
   MyClass(float p_f, int p_i, double p_d) noexcept : f(p_f), i(p_i), d(p_d) { printf("Constructed, %p\n", this); }
   MyClass(const MyClass& p_other) noexcept : f(p_other.f), i(p_other.i), d(p_other.d) { printf("Copy constructed, %p\n", this); }
   MyClass(MyClass&& p_other) noexcept : f(p_other.f), i(p_other.i), d(p_other.d) { std::printf("Move constructed, %p\n", this); }

   ~MyClass() noexcept { printf("Destructed, %p\n", this); }

   MyClass& operator=(const MyClass& p_other) noexcept {
      this->f = p_other.f;
      this->i = p_other.i;
      this->d = p_other.d;
      printf("Copy assigned, %p\n", this);
      return *this;
   }

   MyClass& operator=(MyClass&& p_other) noexcept {
      this->f = p_other.f;
      this->i = p_other.i;
      this->d = p_other.d;
      printf("Move assigned, %p\n", this);
      return *this;
   }

   float f;
   int i;
   double d;
};

void Test_StaticList() noexcept {
   MyClass myObj0(1.5f, 1, 0.5);
   MyClass myObj1(2.5f, 2, 0.6);
   MyClass myObj2(3.5f, 3, 0.7);
   MyClass myObj3(4.5f, 4, 0.8);
   MyClass myObj4(5.5f, 5, 0.9);
   printf("------------------------------\n");
   JK::List<MyClass, 5u> list;
   list.PushBack(std::move(MyClass(6.0f, 6, 0.6)));
   list.PushBack(myObj1);
   list.PopBack<true>();
   list.PopBack<false>();
   printf("------------------------------\n");

   JK::List<int, 5u> l;
   l.PushBack(1);
   l.PushBack(2);
   l.PushBack(3);
   l.PopBack<true>();
   l.PopBack<true>();
   int i = l.PopBack<false>();
   assert(i == 1);
}