#pragma once
#include "variable.hpp"
namespace litert::engine {
class variable_proxy : public variable {
private:
  variable *_source;

public:
  variable_proxy(context *, variable *);
  variable *get(context *, const std::string &) override;
  variable *set(context *, const std::string &, variable *) override;
  variable *get(context *, const int32_t &) override;
  variable *set(context *, const int32_t &, variable *) override;
  variable *remove(context *, const int32_t &) override;
  variable *remove(context *, const std::string &) override;
  std::vector<variable *> call(context *, variable *,
                               const std::vector<variable *> &,
                               const std::string & = "<internel>",
                               const uint32_t & = 0,
                               const uint32_t & = 0) override;
  const std::string to_string() const override;
  bool to_integer(int64_t *) const override;
  bool to_integer(uint64_t *) const override;
  bool to_float(double_t *) const override;
  bool to_boolean() const override;
  variable *value_of() const override;
  variable *value_of() override;
};
} // namespace litert::engine