#pragma once
#include "variable.hpp"
namespace litert::engine {
class variable_array : public variable {
private:
  std::vector<variable *> _items;

public:
  variable_array(context *);
  ~variable_array() override;
  variable *get(context *, const int32_t &) override;
  variable *set(context *, const int32_t &, variable *) override;
  variable_array *push(context *, variable *);
  variable *pop(context *);
  variable *get(context *, const std::string &) override;
  variable *set(context *, const std::string &, variable *) override;
  size_t length();
  bool to_boolean() const override;
  variable_array *splice(context *, const uint32_t &, const uint32_t &,
                         variable *);
  const std::string to_string() const override;
};
} // namespace litert::engine