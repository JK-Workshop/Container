// Test for JK::UnionFindSet. Each testcase starts with integer n, m, meaning
// there are n elements and m operations, followed by m lines, each line be
// either 0, a, b meaning unite a and b or 1, a, b meaning check whether or
// not a and b are in the same set. The result consists multiple lines,, each
// line corresponds to a check, which has an number 0 or1 where 0 means the
// check returns false and 1 means it retures true.

#include "../Include/UnionFindSet.h"
#include "Timer.h"

#include <array>
#include <cstdio>
#include <filesystem>
#include <print>
#include <string>
#include <vector>

static constexpr auto TESTCASE_COUNT = size_t(18);
static const auto DIR = std::filesystem::path("Test/UnionFindSetCases");

auto Test_UnionFindSet() noexcept -> void
{
   for (auto fileIdx = size_t(1); fileIdx <= TESTCASE_COUNT; ++fileIdx) {
      // paths of input and output files
      const auto inPath = DIR / ("in" + std::to_string(fileIdx) + ".txt");
      const auto outPath = DIR / ("out" + std::to_string(fileIdx) + ".txt");
      // FILE* handle of input and ouput files
      const auto inHandle = _wfopen(inPath.c_str(), L"r");
      const auto outHandle = _wfopen(outPath.c_str(), L"r");
      // Read in data count and operation count
      size_t data_c, op_c;
      fscanf(inHandle, "%zu%zu", &data_c, &op_c);
      // Define the data list
      auto data_l = std::make_unique<size_t[]>(data_c);
      for (auto i = size_t(0); i < data_c; ++i)
         data_l[i] = i;

      struct inCache_t {
         size_t op_v, a, b;
      };
      struct inCacheP_t {
         size_t op_v;
         size_t *p, *q;
      };
      // Cache into list from input file, avoiding future reading file stall
      auto inCache_l = std::make_unique<inCache_t[]>(op_c);
      for (auto i = size_t(0); i < op_c; ++i)
         fscanf(inHandle, "%zu%zu%zu", &inCache_l[i].op_v, &inCache_l[i].a, &inCache_l[i].b);
      // Cache into list from output file, avoiding future reading file stall
      auto outCache_i = size_t(0);
      auto outCache_l = std::make_unique<size_t[]>(op_c);
      while (fscanf(outHandle, "%zu", &outCache_l[outCache_i]) != EOF)
         ++outCache_i;
      outCache_i = 0;

      auto iUfs = JK::IdxUnionFindSet<std::dynamic_extent>(data_c);

      // Test index union find set
      const auto timerName = std::format("Index union find set testcase {} passed", fileIdx);
      auto timer = ScopedTimer(timerName);
      for (auto i = size_t(0); i < op_c; ++i) {
         const auto [op_v, a, b] = inCache_l[i];
         if (op_v == 0) iUfs.Unite(a, b);
         else if (outCache_l[outCache_i++] != iUfs.IsSame(a, b)) {
            std::print("Testcase {} failed\n", fileIdx);
            JK_RUNTIME_BREAK();
         }
      }
      timer.~ScopedTimer();

      fclose(inHandle);
      fclose(outHandle);
   }
}
