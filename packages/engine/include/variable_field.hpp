#pragma once
#include "variable.hpp"
#include "variable_proxy.hpp"
namespace litert::engine {
class variable_field : public variable_proxy {
private:
  variable *_self;

public:
  variable_field(context *, variable *, variable *);
  std::vector<variable *> call(context *, variable *,
                               const std::vector<variable *> &,
                               const std::string & = "<internel>",
                               const uint32_t & = 0,
                               const uint32_t & = 0) override;
};
} // namespace litert::engine