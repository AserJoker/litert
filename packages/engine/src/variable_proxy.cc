#include "../include/variable_proxy.hpp"
using namespace litert::engine;
variable_proxy::variable_proxy(context *ctx, variable *source)
    : variable(ctx, source->type_of()), _source(source) {
  add_variable(source);
}
variable *variable_proxy::get(context *ctx, const std::string &name) {
  return _source->get(ctx, name);
};
variable *variable_proxy::set(context *ctx, const std::string &name,
                              variable *val) {
  return _source->set(ctx, name, val);
};
variable *variable_proxy::get(context *ctx, const int32_t &index) {
  return _source->get(ctx, index);
};
variable *variable_proxy::set(context *ctx, const int32_t &index,
                              variable *val) {
  return _source->set(ctx, index, val);
};
variable *variable_proxy::remove(context *ctx, const int32_t &index) {
  return _source->remove(ctx, index);
};
variable *variable_proxy::remove(context *ctx, const std::string &name) {
  return _source->remove(ctx, name);
};
std::vector<variable *> variable_proxy::call(
    context *ctx, variable *self, const std::vector<variable *> &args,
    const std::string &filename, const uint32_t &line, const uint32_t &column) {
  return _source->call(ctx, self, args, filename, line, column);
};

const std::string variable_proxy::to_string() const {
  return _source->to_string();
};
bool variable_proxy::to_integer(int64_t *res) const {
  return _source->to_integer(res);
};
bool variable_proxy::to_integer(uint64_t *res) const {
  return _source->to_integer(res);
};
bool variable_proxy::to_float(double_t *res) const {
  return _source->to_float(res);
};
bool variable_proxy::to_boolean() const { return _source->to_boolean(); };
variable *variable_proxy::value_of() const { return _source; };
variable *variable_proxy::value_of() { return _source; };