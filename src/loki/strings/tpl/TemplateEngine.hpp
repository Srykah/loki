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
  template <class T>
  void addRef(const std::string& name, const T& t);
  template <class T>
  void addPtr(const std::string& name, const T* t);
  void addLambdaRef(const std::string& name,
                    const std::function<std::string()>& gen);

  std::string fill(const std::string& tpl);

 private:
  std::map<std::string, std::function<std::string()>> refs;
};

}  // namespace loki::tpl

#include "impl/TemplateEngine.hxx"
