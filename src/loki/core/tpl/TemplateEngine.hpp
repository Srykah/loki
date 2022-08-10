/*!
 * \file TemplateEngine.hpp.h
 * \author Srykah
 * \copyright GNU GPL v3.0
 */
#pragma once

#include <functional>
#include <map>
#include <string>

namespace loki::tpl {

class TemplateEngine {
 public:
  using RefGenerator = std::function<const std::string&()>;

 public:
  template <class T>
  void addRef(const std::string& name, const T& t);

  void addRef(const std::string& name, const std::string& t);

  template <class T>
  void addPtr(const std::string& name, const T* t);

  void addPtr(const std::string& name, const std::string* t);

  void addLambdaRef(const std::string& name, const RefGenerator& gen);

  std::string fill(const std::string& tpl);

 private:
  std::map<std::string, RefGenerator> refs;
};

}  // namespace loki::tpl

#include "TemplateEngine.hxx"
