#pragma once

#include <type_traits>

template<typename... Ts>
struct voider
{
    using type = void;
};

template<typename... Ts>
using void_t = typename voider<Ts...>::type;

template<typename T, typename = void>
struct has_type_typedef : std::false_type {};

template<typename T>
struct has_type_typedef<T, void_t<typename T::type>> : std::true_type {};

template<typename T, typename = void>
struct has_member_variable : std::false_type {};

template<typename T>
struct has_member_variable<T,
  void_t<
    typename std::enable_if<
      std::is_same<
        int,
        decltype(std::declval<T>().member)
      >::value
    >::type
  >> : std::true_type {};

