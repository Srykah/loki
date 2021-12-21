/*!
 * \file TemplateEngine.hxx
 * \author Srykah
 * \copyright GNU GPL v3.0
 */
#pragma once

namespace loki::tpl {

template <class T>
void TemplateEngine::addRef(const std::string& name, const T& t) {
  refs.insert_or_assign(name, [&t]() { return std::to_string(t); });
}

template <class T>
void TemplateEngine::addPtr(const std::string& name, const T* t) {
  refs.insert_or_assign(name, [t]() { return std::to_string(*t); });
}

}  // namespace loki::tpl
