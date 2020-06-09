#pragma once

#include <string_view>
#include <optional>
#include <variant>

namespace exam::ui::sort::type {

struct Insertion {};
struct Selection {};
struct Bubble {};
struct Quick {};
struct Merge {};
struct Heap {};

using Type = std::variant<
    Insertion,
    Selection,
    Bubble,
    Quick,
    Merge,
    Heap
>;

constexpr auto from_string(const std::string_view str) noexcept -> std::optional<Type>
{
    if (str == "Insertion") {
        return Insertion{};
    }

    if (str == "Selection") {
        return Selection{};
    }

    if (str == "Bubble") {
        return Bubble{};
    }

    if (str == "Quick") {
        return Quick{};
    }

    if (str == "Merge") {
        return Merge{};
    }

    if (str == "Heap") {
        return Heap{};
    }

    return {};
}

} // namespace exam::ui::sort::type
