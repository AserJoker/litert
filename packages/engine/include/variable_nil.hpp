#pragma once
#include "variable.hpp"
namespace litert::engine {
class variable_nil : public variable {
public:
  variable_nil(context *);
  const std::string to_string() const override;
};
} // namespace litert::engine