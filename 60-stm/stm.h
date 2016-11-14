#pragma once

#include <type_traits>
#include <boost/variant.hpp>

struct swallow
{
    template<typename... Ts>
    swallow(Ts &&...)
    {
    }
};

template<std::size_t N, typename T, typename... Ts>
struct index_of_impl;

template<std::size_t N, typename T, typename... Ts>
struct index_of_impl<N, T, T, Ts...> : std::integral_constant<std::size_t, N>
{
};

template<std::size_t N, typename T, typename Tail, typename... Ts>
struct index_of_impl<N, T, Tail, Ts...> : index_of_impl<N + 1, T, Ts...>
{
};

template<typename... Ts>
constexpr std::size_t index_of = index_of_impl<0, Ts...>::value;

template<typename T, typename... Ts>
struct overload_set : public T, public overload_set<Ts...>
{
    overload_set(T && t, Ts &&... ts) : T{ std::forward<T>(t) }, overload_set<Ts...>{ std::forward<Ts>(ts)... }
    {
    }

    using T::operator();
    using overload_set<Ts...>::operator();
};

template<typename T>
struct overload_set<T> : public T
{
    overload_set(T && t) : T{ std::forward<T>(t) }
    {
    }

    using T::operator();
};

template<typename... Ts>
auto make_overload_set(Ts &&... ts)
{
    return overload_set<Ts...>{ std::forward<Ts>(ts)... };
}

struct invalid_transition : public std::exception
{
};

template<typename T>
using remove_cvref_t = std::remove_cv_t<std::remove_reference_t<T>>;

template<typename... States>
class state_machine
{
public:
  template<typename InitState, typename = typename std::enable_if<
      std::disjunction<
        std::is_same<remove_cvref_t<InitState>, States>...
      >::value
    >::type>
  state_machine(InitState && state) : _state{std::forward<InitState>(state)}
  {
  }

  template<typename State>
  bool is_active() const
  {
    return _state.which() == index_of<State, States...>;
  }

  template<typename Event>
  void raise(Event && event = Event{})
  {
    boost::apply_visitor(
      make_overload_set(
        [&](auto && state) -> decltype(state.handle(event), void()) {
          _state = state.handle(event);
        },

        [](auto &&... state) {
          swallow{state...};
          throw invalid_transition{};
        }
      ),
      _state
    );
  }

private:
  boost::variant<States...> _state;
};
