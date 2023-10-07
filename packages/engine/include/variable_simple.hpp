#pragma once
#include "variable.hpp"
#include <cstdint>
namespace litert::engine {
template <class T, variable_type t> class variable_simple : public variable {
private:
  T _data;

public:
  variable_simple(context *ctx, const T &data = 0)
      : variable(ctx, t), _data(data) {}
  T &data() { return _data; }
  const T &data() const { return _data; }
  const std::string to_string() const override {
    return fmt::format("{}", _data);
  }
  bool to_integer(int64_t *result) const override {
    *result = (int64_t)_data;
    return true;
  }
  bool to_integer(uint64_t *result) const override {
    *result = (uint64_t)_data;
    return true;
  }
  bool to_float(double_t *result) const override {
    *result = (double_t)_data;
    return true;
  }
  bool to_boolean() const override { return _data != 0; }
};
using variable_int8 = variable_simple<int8_t, VT_INT8>;
using variable_int16 = variable_simple<int16_t, VT_INT16>;
using variable_int32 = variable_simple<int32_t, VT_INT32>;
using variable_int64 = variable_simple<int64_t, VT_INT64>;
using variable_uint8 = variable_simple<uint8_t, VT_UINT8>;
using variable_uint16 = variable_simple<uint16_t, VT_UINT16>;
using variable_uint32 = variable_simple<uint32_t, VT_UINT32>;
using variable_uint64 = variable_simple<uint64_t, VT_UINT64>;
using variable_float32 = variable_simple<float_t, VT_FLOAT32>;
using variable_float64 = variable_simple<double_t, VT_FLOAT64>;
using variable_boolean = variable_simple<bool, VT_BOOLEAN>;
} // namespace litert::engine