#pragma once
#include "core/include/auto_release.hpp"
#include "variable.hpp"
namespace litert::engine {
class variable_userdata : public variable {
private:
  core::auto_release<core::object> _data;

public:
  variable_userdata(context *, const core::auto_release<core::object> &);
  core::auto_release<core::object> &data();
  const core::auto_release<core::object> &data() const;
  bool to_boolean() const override;
};
} // namespace litert::engine