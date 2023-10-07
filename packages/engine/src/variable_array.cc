#include "../include/variable_array.hpp"
#include "engine/include/variable_error.hpp"
using namespace litert::engine;
variable_array::variable_array(context *ctx) : variable(ctx, VT_ARRAY) {}
variable_array::~variable_array() {}
variable_array *variable_array::push(context *ctx, variable *val) {
  add_variable(val);
  _items.push_back(val);
  return (variable_array *)ctx->create(this);
}
variable *variable_array::pop(context *ctx) {
  variable *val = ctx->create(*_items.rbegin());
  _items.pop_back();
  remove_variable(val);
  return val;
}
variable *variable_array::get(context *ctx, const int32_t &index) {
  if (index < _items.size()) {
    if (index >= 0) {
      return ctx->create(_items[index]);
    } else {
      auto real_index = _items.size() + index - 1;
      if (real_index >= 0 && real_index < _items.size()) {
        return ctx->create(real_index);
      } else {
        return ctx->nil();
      }
    }
  }
  return ctx->nil();
}
variable *variable_array::set(context *ctx, const int32_t &index,
                              variable *val) {
  if (index >= _items.size()) {
    for (auto i = _items.size(); i < index; i++) {
      auto nil = ctx->nil();
      add_variable(nil);
      _items.push_back(nil);
    }
    add_variable(val);
    _items.push_back(val);
  } else {
    if (index >= 0) {
      add_variable(val);
      auto &old = _items[index];
      remove_variable(old);
      _items[index] = val;
    } else {
      auto real_index = _items.size() + index - 1;
      if (real_index >= 0 && real_index < _items.size()) {
        add_variable(val);
        auto &old = _items[real_index];
        remove_variable(old);
        _items[real_index] = val;
      } else {
        return ctx->nil();
      }
    }
  }
  return this;
}
variable *variable_array::get(context *ctx, const std::string &name) {
  if (name == "length") {
    return ctx->create(_items.size());
  }
  return variable::get(ctx, name);
}
variable *variable_array::set(context *ctx, const std::string &name,
                              variable *val) {
  if (name == "length") {
    int64_t size;
    if (val->to_integer(&size)) {
      if ((size_t)size >= _items.size()) {
        while (_items.size() < (size_t)size) {
          push(ctx, ctx->nil());
        }
      } else {
        for (auto i = size; (size_t)i < _items.size(); i++) {
          remove_variable(_items[i]);
        }
        _items.resize(size);
      }
    }
    return new variable_error(
        ctx, "cannot set field 'length' with non-integer variable");
  }
  return variable::get(ctx, name);
}
bool variable_array::to_boolean() const { return true; }
variable_array *variable_array::splice(context *ctx, const uint32_t &start,
                                       const uint32_t &delete_count,
                                       variable *insert_data) {
  variable_array *result = new variable_array(ctx);
  if (start <= _items.size()) {
    for (uint32_t index = 0; index < delete_count; index++) {
      if (start >= _items.size()) {
        break;
      }
      auto &old = _items[start];
      result->push(ctx, old);
      remove_variable(old);
      _items.erase(_items.begin() + start);
    }
  }
  if (insert_data->type_of() != VT_NIL) {
    if (insert_data->type_of() == VT_ARRAY) {
      variable_array *arr = (variable_array *)insert_data;
      _items.insert(_items.begin() + start, arr->_items.begin(),
                    arr->_items.end());
    }
  }
  return result;
}
size_t variable_array::length() { return _items.size(); }
const std::string variable_array::to_string() const {
  std::string result = "[";
  for (auto index = 0; index < _items.size(); index++) {
    result += _items[index]->to_string();
    if (index != _items.size() - 1) {
      result += ',';
    }
  }
  result += "]";
  return result;
}