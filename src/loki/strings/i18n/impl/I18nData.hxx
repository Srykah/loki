/*!
 * \file I18nData.hxx
 * \author Srykah
 * \copyright GNU GPL v3.0
 */
#pragma once

namespace loki::i18n {

template <class... Args>
[[nodiscard]] std::string I18nData::get(const std::string& uri,
                                        Args&&... args) const {
  return get(fmt::format(uri, std::forward<Args>(args)...));
}

}  // namespace loki::i18n
