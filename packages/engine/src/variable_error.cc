#include "../include/variable_error.hpp"
using namespace litert::engine;
variable_error::variable_error(context *ctx, const std::string &msg,
                               const std::string &filename,
                               const uint32_t &line, const uint32_t &column)
    : variable(ctx, VT_ERROR), _msg(msg) {
  auto stack = ctx->call_stack(filename, line, column);
  for (auto frame = stack.rbegin(); frame != stack.rend(); frame++) {
    if (frame->filename == "<internel>") {
      _stack.push_back(
          fmt::format("at {} ({})", frame->funcname, frame->filename));
    } else {
      _stack.push_back(fmt::format("at {} ({}:{}:{})", frame->funcname,
                                   frame->filename, frame->line,
                                   frame->column));
    }
  }
}
const std::string variable_error::to_string() const {
  std::string result = _msg;
  for (auto &frame : _stack) {
    result += fmt::format("\n\t{}", frame);
  }
  return result;
}
bool variable_error::to_boolean() const { return true; }