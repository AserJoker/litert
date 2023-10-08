#include "../include/variable_field.hpp"
using namespace litert::engine;
variable_field::variable_field(context *ctx, variable *self, variable *field)
    : variable_proxy(ctx, field), _self(self) {
  add_variable(self);
}
std::vector<variable *> variable_field::call(
    context *ctx, variable *self, const std::vector<variable *> &args,
    const std::string &filename, const uint32_t &line, const uint32_t &column) {
  return value_of()->call(ctx, _self, args, filename, line, column);
};