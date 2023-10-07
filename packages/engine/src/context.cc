#include "../include/context.hpp"
#include "../include/variable_array.hpp"
#include "../include/variable_nil.hpp"
#include "../include/variable_simple.hpp"
#include "../include/variable_string.hpp"
#include <stdint.h>
using namespace litert::engine;
context::context(runtime *rt) : _rt(rt) {
  _current_scope = new scope();
  _nil = new variable_nil(this);
  _call_stack.push_back({
      .funcname = "<litert:start>",
  });
}
context::~context() { delete _current_scope; }
scope *context::get_scope() { return _current_scope; }
void context::with_scope(const std::function<void(scope *)> &process) {
  auto sc = push_scope();
  process(sc);
  pop_scope(sc);
}
scope *context::push_scope() {
  scope *current = _current_scope;
  _current_scope = new scope(current);
  return current;
}
void context::pop_scope(scope *sc) {
  delete _current_scope;
  _current_scope = sc;
}
variable *context::nil() { return create(_nil); }

void context::push_call_stack(const std::string &filename,
                              const std::string &funcname, const uint32_t &line,
                              const uint32_t &column) {
  auto &tail = *_call_stack.rbegin();
  tail.filename = filename;
  tail.line = line;
  tail.column = column;
  _call_stack.push_back(
      call_frame{.funcname = funcname, .line = 0, .column = 0});
};
void context::pop_call_stack() { _call_stack.pop_back(); };
const std::list<context::call_frame>
context::call_stack(const std::string &filename, const uint32_t &line,
                    const uint32_t &column) const {
  auto res = _call_stack;
  auto &tail = *res.rbegin();
  tail.filename = filename;
  tail.line = line;
  tail.column = column;
  return res;
};

variable *context::create(const std::string &data) {
  return new variable_string(this, data);
};
variable *context::create(const int8_t &data) {
  return new variable_int8(this, data);
};
variable *context::create(const int16_t &data) {
  return new variable_int16(this, data);
};
variable *context::create(const int32_t &data) {
  return new variable_int32(this, data);
};
variable *context::create(const int64_t &data) {
  return new variable_int64(this, data);
};
variable *context::create(const uint8_t &data) {
  return new variable_uint8(this, data);
};
variable *context::create(const uint16_t &data) {
  return new variable_uint16(this, data);
};
variable *context::create(const uint32_t &data) {
  return new variable_uint32(this, data);
};
variable *context::create(const uint64_t &data) {
  return new variable_uint64(this, data);
};
variable *context::create(const float_t &data) {
  return new variable_float32(this, data);
};
variable *context::create(const double_t &data) {
  return new variable_float64(this, data);
};
variable *context::create(const bool &data) {
  return new variable_boolean(this, data);
};
variable *context::create(const std::vector<variable *> &items) {
  variable_array *arr = new variable_array(this);
  for (auto &item : items) {
    arr->push(this, item);
  }
  return arr;
}
variable *context::create(variable *val) {
  auto &type = val->type_of();
  switch (type) {
  case VT_STRING:
    return create(dynamic_cast<variable_string *>(val)->data());
  case VT_INT8:
    return create(dynamic_cast<variable_int8 *>(val)->data());
  case VT_INT16:
    return create(dynamic_cast<variable_int16 *>(val)->data());
  case VT_INT32:
    return create(dynamic_cast<variable_int32 *>(val)->data());
  case VT_INT64:
    return create(dynamic_cast<variable_int64 *>(val)->data());
  case VT_UINT8:
    return create(dynamic_cast<variable_uint8 *>(val)->data());
  case VT_UINT16:
    return create(dynamic_cast<variable_uint16 *>(val)->data());
  case VT_UINT32:
    return create(dynamic_cast<variable_uint32 *>(val)->data());
  case VT_UINT64:
    return create(dynamic_cast<variable_uint64 *>(val)->data());
  case VT_FLOAT32:
    return create(dynamic_cast<variable_float32 *>(val)->data());
  case VT_FLOAT64:
    return create(dynamic_cast<variable_float64 *>(val)->data());
  case VT_BOOLEAN:
    return create(dynamic_cast<variable_boolean *>(val)->data());
  }
  auto res = val->value_of();
  _current_scope->add_variable(res);
  return res;
};
