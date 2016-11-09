#include "implementation.h"

#include <algorithm>
#include <numeric>
#include <functional>

type * find_return_type(const std::vector<function> & overload_set, std::vector<type *> argument_types)
{
  auto overload = std::find_if(overload_set.begin(), overload_set.end(), [&](auto && overload) {
    if (argument_types.size() != overload.arguments.size())
    {
      return false;
    }

    return std::inner_product(argument_types.begin(), argument_types.end(), overload.arguments.begin(), true,
           std::logical_and<>(),
           [](auto && type, auto && variable){ return type == variable.type; });
    });

    if (overload == overload_set.end())
    {
      return nullptr;
    }

  return overload->return_type;
}
