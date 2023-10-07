#pragma once
#include "variable.hpp"
namespace litert::engine {
class variable_string : public variable {
private:
  std::string _data;

public:
  variable_string(context *, const std::string & = "");
  inline std::string &data() { return _data; };
  inline const std::string &data() const { return _data; }
  variable *get(context *, const std::string &) override;
  const std::string to_string() const override;
  bool to_boolean() const override;
  bool to_integer(int64_t *) const override;
  bool to_integer(uint64_t *) const override;
  bool to_float(double_t *) const override;
};
} // namespace litert::engine