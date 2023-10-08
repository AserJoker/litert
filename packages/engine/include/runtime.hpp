#pragma once
#include "core/include/object.hpp"
#include <functional>
namespace litert::engine {
class context;
class runtime : public core::object {
public:
  void run_with_context(const std::function<void(context *)>&);
};
} // namespace litert::engine