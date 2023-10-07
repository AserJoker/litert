#pragma once
#include "variable.hpp"
namespace litert::engine {
class variable_error : public variable {
private:
  std::string _msg;
  std::vector<std::string> _stack;

public:
  variable_error(context *, const std::string &,
                 const std::string & = "<internel>", const uint32_t & = 0,
                 const uint32_t & = 0);
  const std::string to_string() const override;
  bool to_boolean() const override;
};
} // namespace litert::engine