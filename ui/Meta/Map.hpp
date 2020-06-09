#pragma once

#include <type_traits>
#include <tuple>

namespace exam::ui::meta::map {

/**
 * @brief Key/value pair, where value is plain type.
 */
template<typename K, typename V>
struct Plain
{
    using Key = K;
    using Value = V;
};

/**
 * @brief Key/value pair, where value is generic type.
 */
template<typename K, template<typename...> typename V>
struct Generic
{
    using Key = K;

    template<typename... Ts>
    using Value = V<Ts...>;
};

namespace detail {

template<typename T>
struct is_plain_impl : std::false_type
{ };

template<typename K, typename V>
struct is_plain_impl<Plain<K, V>> : std::true_type
{ };

template<typename T>
constexpr bool is_plain = is_plain_impl<T>::value;

template<typename T>
struct is_generic_impl : std::false_type
{ };

template<typename K, template<typename...> typename V>
struct is_generic_impl<Generic<K, V>> : std::true_type
{ };

template<typename T>
inline constexpr bool is_generic = is_generic_impl<T>::value;

template<typename T>
inline constexpr bool is_pair = is_plain<T> || is_generic<T>;

template<typename Pair, typename... Args, typename = std::enable_if_t<detail::is_plain<Pair> && (sizeof...(Args) == 0)>>
constexpr auto value_impl() -> typename Pair::Value;

template<typename Pair, typename... Args, typename = std::enable_if_t<detail::is_generic<Pair>>>
constexpr auto value_impl() -> typename Pair::template Value<Args...>;

template<typename Pair, typename... Args>
using value = decltype(value_impl<Pair, Args...>());

template<typename T, typename... Ts>
constexpr auto count_impl() noexcept -> std::size_t
{
    std::size_t count = 0;
    return ((std::is_same_v<T, Ts> ?: ++count) && ...) ?: count;
}

template<typename T, typename... Ts>
inline constexpr auto count = count_impl<T, Ts...>();

template<typename... Is, typename... Js>
constexpr bool unique_impl() noexcept
{
    return (count<Is, Js...> + ...) == sizeof...(Is);
}

template<typename... Ts>
inline constexpr bool unique = unique_impl<Ts..., Ts...>();

template<typename T, typename... Ts>
constexpr auto index_of_impl() noexcept -> std::size_t
{
    constexpr auto index = [idx = 0] () mutable {
        return ((std::is_same_v<T, Ts> ? false : ++idx) && ...) ? std::size_t(-1) : idx;
    }();

    static_assert(index != std::size_t(-1), "Type not found");
    return index;
}

template<typename T, typename... Ts>
inline constexpr auto index_of = index_of_impl<T, Ts...>();

template<std::size_t I, typename... Ts>
using nth_element_of = std::tuple_element_t<I, std::tuple<Ts...>>;

} // namespace detail


template<typename... Pairs>
struct Map
{
    static_assert(detail::unique<typename Pairs::Key...>);
    static_assert((detail::is_pair<Pairs> && ...));

    template<typename Key, typename... Args>
    using Get = detail::value<
        detail::nth_element_of<
            detail::index_of<Key, typename Pairs::Key...>,
            Pairs...
        >,
        Args...
    >;
};

} // namespace exam::ui::meta::map
