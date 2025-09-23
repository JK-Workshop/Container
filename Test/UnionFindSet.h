// Test for JK::UnionFindSet. Each testcase starts with integer n, m, meaning
// there are n elements and m operations, followed by m lines, each line be
// either 0, a, b meaning unite a and b or 1, a, b meaning check whether or
// not a and b are in the same set. The result consists multiple lines,, each
// line corresponds to a check, which has an number 0 or1 where 0 means the
// check returns false and 1 means it retures true.

#include "../Include/UnionFindSet.h"

#include <array>
#include <filesystem>
#include <fstream>
#include <print>
#include <vector>

auto Test_UnionFindSet() noexcept -> void
{
   namespace fs = std::filesystem;

   const auto dir = "Test/UnionFindSetCases";

   for (const auto e : fs::directory_iterator(dir,)) {
      // Open in and out files
      auto in = std::fopen(InName.data(), "r");
      auto out = std::fopen(OutName.data(), "r");
      if (in == 0 || out == 0)
         __debugbreak();

      size_t n, m;
      std::fscanf(in, "%llu%llu", &n, &m);
      auto ufs = JK::UnionFindSet<std::dynamic_extent>(n);

      size_t op, a, b;
      for (auto i = size_t(0); i < m; ++i) {

         std::fscanf(in, "%llu%llu%llu", &op, &a, &b);
         if (op == 0)
            ufs.Unite(a, b);
         else {
            size_t res;
            std::fscanf(out, "%llu", &res);
            if (ufs.Find(a) == ufs.Find(b)) {
               if (res != 1)
                  __debugbreak();
            } else if (res != 0) {
               __debugbreak();
            }
         }
      }
      std::fclose(in);
      std::fclose(out);

      std::print("UnionFindSet: Testcase {} passed!\n", f);
   }
}
