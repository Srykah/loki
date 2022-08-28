namespace loki::core {

template <class T>
void TemplateEngine::addRef(const std::string& name, const T& t) {
  refs.insert_or_assign(name, [&t]() { return std::to_string(t); });
}

template <class T>
void TemplateEngine::addPtr(const std::string& name, const T* t) {
  refs.insert_or_assign(name, [t]() { return std::to_string(*t); });
}

}  // namespace loki::core
