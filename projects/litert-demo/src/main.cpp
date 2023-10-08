
#include "engine/include/context.hpp"
#include "engine/include/runtime.hpp"
#include "engine/include/scope.hpp"
#include "engine/include/variable_array.hpp"
#include "engine/include/variable_error.hpp"
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
  rt->run_with_context([](engine::context *ctx) {
    auto obj = new engine::variable_object(ctx);
    obj->set(ctx, "print",
             new engine::variable_function(
                 ctx,
                 [](engine::context *ctx, engine::variable *self,
                    const std::vector<engine::variable *> &args)
                     -> std::vector<engine::variable *> {
                   auto data = self->get(ctx, "data");
                   throw new engine::variable_error(ctx, "demo error");
                 }));
    obj->set(ctx, "data", ctx->create("hello world"));
    ctx->with_try_catch(
        [=]() {
          ctx->with_try_catch(
              [=]() {
                auto results = obj->get(ctx, "print")->call(ctx, nullptr, {});
                std::cout << results[0]->to_string() << std::endl;
              },
              [=](engine::variable *error) {
                std::cout << "catch error:" << error->to_string() << std::endl;
                throw new engine::variable_error(ctx, "demo error2", error);
              });
        },
        [](engine::variable *error) {
          std::cout << "catch error again:" << error->to_string() << std::endl;
        });
  });
  delete rt;
  core::object::memory_leak_check();
  return 0;
}
