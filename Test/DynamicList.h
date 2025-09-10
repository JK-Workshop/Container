#pragma once

#include "StaticList.h"

void Test_DynamicList() noexcept {
   MyClass myObj0(1.5f, 1, 0.5);
   MyClass myObj1(2.5f, 2, 0.6);
   MyClass myObj2(3.5f, 3, 0.7);
   MyClass myObj3(4.5f, 4, 0.8);
   MyClass myObj4(5.5f, 5, 0.9);

   JK::List<MyClass, 0u> list(1);
   list.PushBack(myObj0);
   list.PushBack(myObj1);
   list.PushBack(myObj2);
   list.PushBack(myObj3);
   list.PushBack(myObj4);

   list.Truncate(2);

   int a = 1;
}