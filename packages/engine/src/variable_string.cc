#include "../include/variable_string.hpp"
#include "../include/variable_simple.hpp"
#include <sstream>
using namespace litert::engine;
variable_string::variable_string(context *ctx, const std::string &data)
    : variable(ctx, VT_STRING), _data(data) {}
variable *variable_string::get(context *ctx, const std::string &name) {
  if (name == "length") {
    return new variable_uint64(ctx, _data.length());
  }
  return variable::get(ctx, name);
}
const std::string variable_string::to_string() const { return _data; }
bool variable_string::to_boolean() const { return _data.empty(); }

bool variable_string::to_integer(int64_t *result) const {
  if (_data[0] >= '0' && _data[0] <= '9') {
    std::stringstream ss;
    ss << _data;
    ss >> *result;
    return true;
  }
  return false;
}
bool variable_string::to_integer(uint64_t *result) const {
  if (_data[0] >= '0' && _data[0] <= '9') {
    std::stringstream ss;
    ss << _data;
    ss >> *result;
    return true;
  }
  return false;
}
bool variable_string::to_float(double_t *result) const {
  if (_data[0] >= '0' && _data[0] <= '9' || _data[0] == '.') {
    std::stringstream ss;
    ss << _data;
    ss >> *result;
    return true;
  }
  return false;
}