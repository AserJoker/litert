#pragma once
#include "core/include/object.hpp"
#include "runtime.hpp"
#include "scope.hpp"
#include <functional>
#include <stack>
#include <stdint.h>
#include <string>

namespace litert::engine {
class variable;
class context : public core::object {
public:
  struct call_frame {
    std::string filename;
    std::string funcname;
    uint32_t line;
    uint32_t column;
  };

private:
  scope *_current_scope;
  runtime *_rt;

  variable *_nil;
  std::list<call_frame> _call_stack;

public:
  scope *push_scope();
  void pop_scope(scope *);
  scope *get_scope();
  void with_scope(const std::function<void(scope *)> &);
  context(runtime *);
  ~context() override;
  variable *nil();
  void push_call_stack(const std::string &, const std::string &,
                       const uint32_t &, const uint32_t &);
  void pop_call_stack();
  const std::list<call_frame> call_stack(const std::string &, const uint32_t &,
                                         const uint32_t &) const;
  variable *create(const std::string &);
  variable *create(const int8_t &);
  variable *create(const int16_t &);
  variable *create(const int32_t &);
  variable *create(const int64_t &);
  variable *create(const uint8_t &);
  variable *create(const uint16_t &);
  variable *create(const uint32_t &);
  variable *create(const uint64_t &);
  variable *create(const float &);
  variable *create(const double &);
  variable *create(const bool &);
  variable *create(variable *);
  variable *create(const std::vector<variable *> &);
  template <class T> variable *create(const std::vector<T> &items) {
    std::vector<variable *> vitems;
    for (auto &item : items) {
      vitems.push_back(create(item));
    }
    return create(vitems);
  }
};
} // namespace litert::engine