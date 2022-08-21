namespace loki::core {

template <class... Args>
[[nodiscard]] std::string I18nData::get(const std::string& uri,
                                        Args&&... args) const {
  return get(Ptr{fmt::format(fmt::runtime(uri), std::forward<Args>(args)...)});
}

}  // namespace loki::core
