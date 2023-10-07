#include "../include/variable_field.hpp"
using namespace litert::engine;
variable_field::variable_field(context *ctx, variable *self, variable *field)
    : variable(ctx, field->type_of()), _self(self), _field(field) {
  add_variable(self);
  add_variable(field);
}
variable *variable_field::get(context *ctx, const std::string &name) {
  return _field->get(ctx, name);
};
variable *variable_field::set(context *ctx, const std::string &name,
                              variable *val) {
  return _field->set(ctx, name, val);
};
variable *variable_field::get(context *ctx, const int32_t &index) {
  return _field->get(ctx, index);
};
variable *variable_field::set(context *ctx, const int32_t &index,
                              variable *val) {
  return _field->set(ctx, index, val);
};
variable *variable_field::remove(context *ctx, const int32_t &index) {
  return _field->remove(ctx, index);
};
variable *variable_field::remove(context *ctx, const std::string &name) {
  return _field->remove(ctx, name);
};
std::vector<variable *> variable_field::call(
    context *ctx, variable *self, const std::vector<variable *> &args,
    const std::string &filename, const uint32_t &line, const uint32_t &column) {
  return _field->call(ctx, _self, args, filename, line, column);
};

const std::string variable_field::to_string() const {
  return _field->to_string();
};
bool variable_field::to_integer(int64_t *res) const {
  return _field->to_integer(res);
};
bool variable_field::to_integer(uint64_t *res) const {
  return _field->to_integer(res);
};
bool variable_field::to_float(double_t *res) const {
  return _field->to_float(res);
};
bool variable_field::to_boolean() const { return _field->to_boolean(); };
variable *variable_field::value_of() const { return _field; };
variable *variable_field::value_of() { return _field; };