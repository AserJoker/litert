#include "../include/variable_function.hpp"
#include "../include/variable_error.hpp"
using namespace litert::engine;
variable_function::variable_function(context *ctx,
                                     const native_function &callee,
                                     const std::string &name,
                                     const uint32_t &length)
    : variable(ctx, VT_FUNCTION), _callee(callee), _name(name), _length(length),
      _bind(nullptr) {}
variable_function::~variable_function() {}
std::vector<variable *> variable_function::call(
    context *ctx, variable *self, const std::vector<variable *> &args,
    const std::string &filename, const uint32_t &line, const uint32_t &column) {
  if (args.size() < _length) {
    return {new variable_error(ctx, fmt::format("too few param: need {} get {}",
                                                _length, args.size()))};
  }
  auto sc = ctx->push_scope();
  ctx->push_call_stack(filename, _name, line, column);
  for (auto &arg : args) {
    ctx->get_scope()->add_variable(arg);
  }
  auto result = _callee(ctx, _bind ? _bind : self, args);
  ctx->pop_call_stack();
  for (auto &res : result) {
    sc->add_variable(res);
  }
  ctx->pop_scope(sc);
  return result;
}
variable_function *variable_function::bind(context *ctx, variable *self) {
  auto bind_fn = new variable_function(ctx, _callee, _name, _length);
  bind_fn->_bind = self;
  return bind_fn;
}
const std::string variable_function::to_string() const {
  return fmt::format("[func {}]", _name);
}
bool variable_function::to_boolean() const { return true; }
const std::string variable_function::name() const { return _name; }
const uint32_t variable_function::length() const { return _length; }