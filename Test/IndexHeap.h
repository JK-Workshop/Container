// Test for JK::IndexHeap, in each testcase, the first line is an unsigned integer n, indicating there are n heao operations,
// followed by n lines, each line consists of two integers, the first integer is among 0, 1, 2 where 0 means the operation is
// a heap push operation, 1 means the operation is a heap pop operation, 3 means the operation is an update operation of a
// heap element. If it's a push operation, then followed by an integer indicating push that interger into the heap, if the
// operation is a pop operation, then followed by nothing, if the operation is a upate operation of an heap element, then it's
// followed by two integers a, b indicating update a to b, you should always guarantee that b<a.

#include "../Include/IndexHeap.h"

#include <filesystem>
#include <fstream>
#include <print>
#include <span>
#include <vector>

#define TEMPALTE template <SIZE_T HEAP_S, class COMPARATOR_T, JK::IndexHeapImpl_e IMPL_E>

TEMPALTE void PrintHeap(const JK::IndexHeap<HEAP_S, COMPARATOR_T, IMPL_E>& p_indexHeap, const SIZE_T* p_heapData_l) noexcept {
   for (SIZE_T i = 0; i < p_indexHeap.Count(); ++i)
      std::print("{}, ", p_heapData_l[i]);
   std::print("\n");
}

void Test_IndexHeap() noexcept {
   // Generate test cases
   SIZE_T arr[10] = {4, 6, 3, 5, 8, 2, 7, 9, 10, 1};
   SIZE_T IHeapData[10];
   auto cmp = [&arr](const SIZE_T i, const SIZE_T j) -> bool { return arr[i] < arr[j]; };
   JK::IndexHeap<10, decltype(cmp), JK::IndexHeapImpl_e::BINARY> IHeap(IHeapData, cmp);
   IHeap.Push(0);
   IHeap.Push(1);
   IHeap.Push(2);
   IHeap.Pop();
   IHeap.Push(3);
   IHeap.Push(4);
   arr[4] = 3;
   IHeap.Update(4);
   // const std::filesystem::path TestcasePath("Test/IndexHeapCases/In/");
   // 
   // if (!std::filesystem::exists(TestcasePath)) {
   //    std::print(stderr, "Directory does not exist\n");
   //    JK_RT_BREAK();
   // }
   // if (!std::filesystem::is_directory(TestcasePath)) {
   //    std::print(stderr, "Path is not a directory\n");
   //    JK_RT_BREAK();
   // }
   // 
   // for (const auto& _v : std::filesystem::directory_iterator(TestcasePath)) {
   //    std::ifstream in(_v.path().native());
   //    size_t n, opType, operant0, operant1;
   //    in >> n;
   //    std::vector<size_t> data(n);
   //    auto comparator = [&data](const size_t i, const size_t j) -> bool { return data[i] < data[j]; };
   //    JK::IndexHeap<std::dynamic_extent, decltype(comparator), JK::IndexHeapImpl_e::BINARY> IHeap(data.data(), n, comparator);
   //    while (n--) {
   //       in >> opType;
   //       switch (opType) {
   //       case 0:
   //          in >> operant0;
   //          data.push_back(operant0);
   //          IHeap.Push(data.size() - 1);
   //          break;
   //       case 1:
   //          IHeap.Pop();
   //          break;
   //       case 2:
   //          in >> operant0 >> operant1;
   //          data[operant0] = operant1;
   //          IHeap.Update(operant0);
   //          break;
   //       }
   //    }
   //    in.close();
   // }
}

#undef TEMPLATE
