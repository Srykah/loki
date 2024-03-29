#pragma once

#include <functional>
#include <map>
#include <string>

namespace loki::core {

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

}  // namespace loki::core

#include "TemplateEngine.hxx"
