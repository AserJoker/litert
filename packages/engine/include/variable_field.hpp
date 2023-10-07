#pragma once
#include "variable.hpp"
namespace litert::engine {
class variable_field : public variable {
private:
  variable *_self;
  variable *_field;

public:
  variable_field(context *, variable *, variable *);
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
  virtual const std::string to_string() const override;
  virtual bool to_integer(int64_t *) const override;
  virtual bool to_integer(uint64_t *) const override;
  virtual bool to_float(double_t *) const override;
  virtual bool to_boolean() const override;
  virtual variable *value_of() const override;
  virtual variable *value_of() override;
};
} // namespace litert::engine