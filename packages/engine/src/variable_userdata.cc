#include "../include/variable_userdata.hpp"
using namespace litert::engine;
using namespace litert;
variable_userdata::variable_userdata(
    context *ctx, const core::auto_release<core::object> &data)
    : variable(ctx, VT_USERDATA), _data(data) {}
core::auto_release<core::object> &variable_userdata::data() { return _data; }
const core::auto_release<core::object> &variable_userdata::data() const {
  return _data;
}
bool variable_userdata::to_boolean() const { return true; }