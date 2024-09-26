#pragma once

#include <iostream>

namespace ql
{
  void print(auto... items)
  {
    ((std::cout << items), ...);
  }

  void println(auto... items)
  {
    print(items..., '\n');
  }
}