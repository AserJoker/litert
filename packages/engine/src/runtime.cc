#include "../include/runtime.hpp"
#include "../include/context.hpp"
#include "../include/variable.hpp"
#include <thread>
using namespace litert::engine;
void runtime::run_with_context(const std::function<void(context *)> &handle) {
  context *ctx = new context(this);
  try {
    handle(ctx);
    while (ctx->_tasks.size()) {
      auto task = *ctx->_tasks.rbegin();
      ctx->_tasks.pop_back();
      if (!task()) {
        ctx->_tasks.push_back(task);
      }
      std::this_thread::sleep_for(std::chrono::milliseconds(4));
    }
  } catch (variable *err) {
    fmt::print("uncatched error:{}", err->to_string());
  } catch (std::exception &e) {
    fmt::print("uncatched native error:{}", e.what());
  }
  delete ctx;
}