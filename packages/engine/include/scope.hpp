#pragma once
#include "core/include/object.hpp"
#include <list>
namespace litert::engine {
class variable;
class scope : public core::object {
private:
  std::list<scope *> _children;
  std::list<variable *> _variables;
  scope *_parent;

public:
  scope(scope * = nullptr);
  ~scope();
  void add_variable(variable *);
  void remove_variable(variable *);
};
} // namespace litert::engine
