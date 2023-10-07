
#include "engine/include/context.hpp"
#include "engine/include/runtime.hpp"
#include "engine/include/scope.hpp"
#include "engine/include/variable_array.hpp"
#include "engine/include/variable_function.hpp"
#include "engine/include/variable_object.hpp"
#include "engine/include/variable_simple.hpp"
#include "engine/include/variable_string.hpp"
#include <codecvt>
#include <fstream>
#include <iostream>
#include <windows.h>

using namespace litert;
int main(int argc, char *argv[]) {
#if defined(_WIN32)
  SetConsoleOutputCP(CP_UTF8);
  setvbuf(stdout, nullptr, _IOFBF, 1000);
#endif
  engine::runtime *rt = new engine::runtime();
  engine::context *ctx = new engine::context(rt);
  auto obj = new engine::variable_object(ctx);
  obj->set(ctx, "print",
           new engine::variable_function(
               ctx,
               [](engine::context *ctx, engine::variable *self,
                  const std::vector<engine::variable *> &args)
                   -> std::vector<engine::variable *> { return {}; }));
  auto print = obj->get(ctx, "print");
  std::cout << print->to_string() << std::endl;
  delete ctx;
  delete rt;
  core::object::memory_leak_check();
  return 0;
}
