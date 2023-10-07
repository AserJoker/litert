#include "../include/variable.hpp"
#include "../include/variable_string.hpp"
#include "core/include/auto_release.hpp"
#include <fmt/format.h>
#include <set>
using namespace litert::engine;
using namespace litert;
variable::variable(context *ctx, const int &type)
    : _type(type), _gc_time(0), _check_time(0) {
  ctx->get_scope()->add_variable(this);
  variable::variables.push_back(this);
}
variable::~variable() { std::erase(variable::variables, this); }
void variable::add_variable(variable *n) {
  _children.push_back(n);
  n->_parents.push_back(this);
}
void variable::remove_variable(variable *n) {
  for (auto it = n->_parents.begin(); it != n->_parents.end(); it++) {
    if (*it == this) {
      n->_parents.erase(it);
      break;
    }
  }
  for (auto it = _children.begin(); it != _children.end(); it++) {
    if (*it == n) {
      _children.erase(it);
      break;
    }
  }
  n->auto_release();
}
std::list<scope *> &variable::get_groups() { return _scopes; }
void variable::auto_release() {
  if (!_scopes.empty()) {
    return;
  }
  static uint64_t gc_time = 0;
  static uint64_t check_time = 0;
  std::set<core::auto_release<variable>> release_list;
  std::list<variable *> worker_queue = {this};
  _gc_time = ++gc_time;
  while (!worker_queue.empty()) {
    auto n = *worker_queue.begin();
    worker_queue.erase(worker_queue.begin());
    if (n->check_alone(++check_time)) {
      for (auto c : n->_children) {
        std::erase(c->_parents, n);
        if (c->_gc_time != gc_time) {
          c->_gc_time = gc_time;
          worker_queue.push_back(c);
        }
      }
      release_list.insert(n);
    }
  }
  while (!release_list.empty()) {
    release_list.erase(release_list.begin());
  }
}
bool variable::check_alone(uint64_t check_time) {
  std::list<variable *> worker_queue = {this};
  this->_check_time = check_time;
  while (!worker_queue.empty()) {
    auto n = *worker_queue.begin();
    worker_queue.erase(worker_queue.begin());
    if (!n->_scopes.empty()) {
      return false;
    }
    for (auto &p : n->_parents) {
      if (p->_check_time != check_time) {
        p->_check_time = check_time;
        worker_queue.push_back(p);
      }
    }
  }
  return true;
}
variable *variable::get(context *ctx, const std::string &) {
  return ctx->nil();
}
variable *variable::set(context *ctx, const std::string &, variable *) {
  return ctx->nil();
}
variable *variable::remove(context *ctx, const std::string &) {
  return ctx->nil();
}
variable *variable::get(context *ctx, const int32_t &) { return ctx->nil(); }
variable *variable::set(context *ctx, const int32_t &, variable *) {
  return ctx->nil();
}

variable *variable::remove(context *ctx, const int32_t &) { return ctx->nil(); }
variable *variable::to_string(context *ctx) {
  return new variable_string(ctx, to_string());
}
bool variable::to_integer(int64_t *) const { return false; }
bool variable::to_integer(uint64_t *) const { return false; }
bool variable::to_float(double_t *) const { return false; }
bool variable::to_boolean() const { return false; }

std::vector<variable *> variable::call(context *ctx, variable *self,
                                       const std::vector<variable *> &args,
                                       const std::string &filename,
                                       const uint32_t &line,
                                       const uint32_t &column) {
  return {};
}