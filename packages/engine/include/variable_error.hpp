#pragma once
#include "variable.hpp"
#include <source_location>
namespace litert::engine {
class variable_error : public variable {
public:
  struct location {
    std::string filename;
    uint32_t line;
    uint32_t column;
  };

private:
  std::string _msg;
  std::vector<std::string> _stack;
  variable *_caused;

public:
  variable_error(context *, const std::string &, const location &,
                 variable * = nullptr);
  variable_error(
      context *, const std::string &, variable * = nullptr,
      const std::source_location & = std::source_location::current());
  const std::string to_string() const override;
  bool to_boolean() const override;
};
} // namespace litert::engine