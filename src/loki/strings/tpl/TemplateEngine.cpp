/*!
 * \file TemplateEngine.cpp.c
 * \author Srykah
 * \copyright GNU GPL v3.0
 */
#include "TemplateEngine.hpp"
#include <fmt/args.h>
#include <fmt/format.h>

namespace loki::tpl {
    void TemplateEngine::addRef(const std::string &name, const std::string &t) {
        refs.insert_or_assign(name, [&t]() { return t; });
    }

    void TemplateEngine::addPtr(const std::string &name, const std::string *t) {
        refs.insert_or_assign(name, [t]() { return *t; });
    }

    void TemplateEngine::addLambdaRef(const std::string &name,
                                      const RefGenerator &gen) {
        refs.insert_or_assign(name, gen);
    }

    std::string TemplateEngine::fill(const std::string &tpl) {
        fmt::dynamic_format_arg_store<fmt::format_context> args;
        for (auto&&[name, ref]: refs) {
            args.push_back(fmt::arg(name.c_str(), ref()));
        }
        return fmt::vformat(tpl, args);
    }

}  // namespace loki::tpl
