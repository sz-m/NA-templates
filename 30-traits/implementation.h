#pragma once
#include <type_traits>

template<typename T, typename T1, typename T2, typename T3>
struct is_any_of : std::disjunction<std::is_same<T, T1>, std::is_same<T, T2>, std::is_same<T, T3>>
{

};
