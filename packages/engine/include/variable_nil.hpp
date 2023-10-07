#pragma once
#include "variable.hpp"
namespace litert::engine {
class variable_nil : public variable {
public:
  variable_nil(context *);
};
} // namespace litert::engine