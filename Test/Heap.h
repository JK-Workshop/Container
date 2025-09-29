#include "../Include/Heap.h"

#include <filesystem>
#include <format>
#include <fstream>
#include <print>
#include <string>

#include "Timer.h"

auto Test_Heap() noexcept -> void
{
   namespace fs = std::filesystem;

   const auto dir = fs::path("Test/HeapCases/");
   size_t DataCount, OpCount, OpType;
   int a;

   // Test poiner heap
   for (auto fi = size_t(0); fi < 13; ++fi) {
      auto in = std::ifstream(dir / ("in" + std::to_string(fi) + ".txt"), std::ios::in);
      auto out = std::ifstream(dir / ("out" + std::to_string(fi) + ".txt"), std::ios::in);

      in >> DataCount >> OpCount;                     // data[] has n elements and there are m operations
      auto data = std::make_unique<int[]>(DataCount); // Data array

      // Fill in data[]
      for (auto i = size_t(0); i < DataCount; ++i)
         in >> data[i];

      auto pData = std::make_unique<int*[]>(OpCount);                         // PtrHeap data (array of pointers)
      auto cmp = [](const int* p, const int* q) -> bool { return *p <= *q; }; // Comparason routine
      auto pheap = JK::PtrHeap<int, std::dynamic_extent, decltype(cmp), JK::HeapImpl_e::BINARY>(pData.get(), OpCount, cmp);

      auto timer = ScopedTimer("Pointer heap");

      for (auto i = size_t(0); i < OpCount; ++i) {
         in >> OpType;
         switch (OpType) {
         case 0:
            in >> a;
            pheap.Push(&data[a]);
            break;
         case 1:
            out >> a;
            if (*pheap.Top() != a) {
               std::print("Testcase {} failed!", fi);
               return;
            }
            break;
         case 2:
            pheap.Pop();
            break;
         }

         // Test index heap
      }

      std::print("Testcase {} passed!", fi);
   }

   // Test index heap
   for (auto fi = size_t(0); fi < 13; ++fi) {
      auto in = std::ifstream(dir / ("in" + std::to_string(fi) + ".txt"), std::ios::in);
      auto out = std::ifstream(dir / ("out" + std::to_string(fi) + ".txt"), std::ios::in);

      in >> DataCount >> OpCount;                     // data[] has n elements and there are m operations
      auto data = std::make_unique<int[]>(DataCount); // Data array

      // Fill in data[]
      for (auto i = size_t(0); i < DataCount; ++i)
         in >> data[i];

      auto pData = std::make_unique<size_t[]>(OpCount);                                          // PtrHeap data (array of pointers)
      auto cmp = [&data](const size_t i, const size_t j) -> bool { return data[i] <= data[j]; }; // Comparason routine
      auto iheap = JK::IdxHeap<std::dynamic_extent, decltype(cmp), JK::HeapImpl_e::BINARY>(pData.get(), OpCount, cmp);

      auto timer = ScopedTimer("Index heap");

      for (auto i = size_t(0); i < OpCount; ++i) {
         in >> OpType;
         // Test pointer heap
         switch (OpType) {
         case 0:
            in >> a;
            iheap.Push(a);
            break;
         case 1:
            out >> a;
            if (data[iheap.Top()] != a) {
               std::print("Testcase {} failed!", fi);
               return;
            }
            break;
         case 2:
            iheap.Pop();
            break;
         }

         // Test index heap
      }

      std::print("Testcase {} passed!", fi);
   }
}
