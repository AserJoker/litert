#include "../include/variable_nil.hpp"
using namespace litert::engine;
variable_nil::variable_nil(context *ctx) : variable(ctx, VT_NIL) {}
const std::string variable_nil::to_string() const { return "nil"; }