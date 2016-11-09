#pragma once

#include <cstddef>
#include <utility>

template<typename T>
class container_wrapper
{
public:
  container_wrapper() = default;

  container_wrapper(T t) :type{std::move(t)} 
  {
  }

  container_wrapper(const container_wrapper&) = default;  
  container_wrapper(container_wrapper&&) = default;
  container_wrapper& operator=(const container_wrapper&) = default;
  container_wrapper& operator=(container_wrapper&&) = default;

  std::size_t size() const {
    return type.size();
  }

private:
  T type;

};

