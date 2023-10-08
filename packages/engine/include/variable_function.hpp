#pragma once
#include "variable.hpp"
#include <functional>
namespace litert::engine {
using native_function = std::function<std::vector<variable *>(
    context *, variable *, const std::vector<variable *> &)>;
class variable_function : public variable {
private:
  native_function _callee;
  std::string _name;
  uint32_t _length;
  variable *_bind;

public:
  variable_function(context *, const native_function &,
                    const std::string & = "[[anonymous]]",
                    const uint32_t & = 0);
  ~variable_function() override;
  std::vector<variable *> call(context *, variable *,
                               const std::vector<variable *> &,
                               const std::string & = "<internel>",
                               const uint32_t & = 0,
                               const uint32_t & = 0) override;
  variable_function *bind(context *, variable *);
  const std::string to_string() const override;
  const std::string name() const;
  const uint32_t length() const;
  bool to_boolean() const override;
};
} // namespace litert::engine