#pragma once
#include "variable.hpp"
namespace litert::engine {
class variable_object : public variable {
private:
  std::map<std::string, variable *> _properties;

public:
  variable_object(context *);
  ~variable_object() override;
  variable *get(context *, const std::string &) override;
  variable *set(context *, const std::string &, variable *) override;
  variable *remove(context *, const std::string &) override;
  std::vector<std::string> keys() const;
  bool to_boolean() const override;
  const std::string to_string() const override;
};
} // namespace litert::engine