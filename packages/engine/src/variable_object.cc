#include "../include/variable_object.hpp"
#include "../include/variable_field.hpp"
using namespace litert::engine;
variable_object::variable_object(context *ctx) : variable(ctx, VT_OBJECT) {}
variable_object::~variable_object() {}
variable *variable_object::get(context *ctx, const std::string &name) {
  if (_properties.contains(name)) {
    return new variable_field(ctx, this, _properties.at(name));
  }
  return ctx->nil();
}
variable *variable_object::set(context *ctx, const std::string &name,
                               variable *val) {
  add_variable(val);
  if (_properties.contains(name)) {
    auto &old = _properties.at(name);
    remove_variable(old);
  }
  _properties[name] = val;
  return ctx->create(this);
}
variable *variable_object::remove(context *ctx, const std::string &name) {
  if (_properties.contains(name)) {
    auto &val = _properties.at(name);
    remove_variable(val);
    return ctx->create(this);
  }
  return ctx->nil();
}
std::vector<std::string> variable_object::keys() const {
  std::vector<std::string> keys;
  for (auto &[key, _] : _properties) {
    keys.push_back(key);
  }
  return keys;
}
bool variable_object::to_boolean() const { return true; }
const std::string variable_object::to_string() const {
  std::string result = "{";
  auto it = _properties.begin();
  for (size_t index = 0; index < _properties.size(); index++) {
    auto &[key, value] = *it;
    it++;
    result += key;
    result += ":";
    result += value->to_string();
    if (index != _properties.size() - 1) {
      result += ",";
    }
  }
  result += "}";
  return result;
}