#include "../include/variable_error.hpp"
using namespace litert::engine;
variable_error::variable_error(context *ctx, const std::string &msg,
                               const location &loc, variable *caused)
    : variable(ctx, VT_ERROR), _msg(msg), _caused(caused) {
  auto &[filename, line, column] = loc;
  auto stack = ctx->call_stack(filename, line, column);
  for (auto frame = stack.rbegin(); frame != stack.rend(); frame++) {
    if (frame->filename == "") {
      _stack.push_back(fmt::format("at {} (<internel>)", frame->funcname));
    } else {
      _stack.push_back(fmt::format("at {} ({}:{}:{})", frame->funcname,
                                   frame->filename, frame->line,
                                   frame->column));
    }
  }
  if (caused) {
    add_variable(caused);
  }
}
variable_error::variable_error(context *ctx, const std::string &msg,
                               variable *caused,
                               const std::source_location &loc)
    : variable_error(ctx, msg,
                     location{.filename = loc.file_name(),
                              .line = loc.line(),
                              .column = loc.column()},
                     caused) {}
const std::string variable_error::to_string() const {
  std::string result = _msg;
  for (auto &frame : _stack) {
    result += fmt::format("\n\t{}", frame);
  }
  if (_caused) {
    result += "\ncaused by:" + _caused->to_string();
  }
  return result;
}
bool variable_error::to_boolean() const { return true; }