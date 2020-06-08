#pragma once

#include <variant>

namespace exam::sort::change {
namespace detail {

template<typename It, template<typename> typename... Changes>
using parametrize = std::variant<Changes<It>...>;

} // namespace detail


template<typename It>
struct Swap
{
    It first;
    It second;
};

template<typename It>
Swap(It, It) -> Swap<It>;


template<typename It>
struct SelectPivot
{
    It value;
};

template<typename It>
SelectPivot(It) -> SelectPivot<It>;


template<typename It>
struct SelectSubrange
{
    It first;
    It last;
};

template<typename It>
SelectSubrange(It, It) -> SelectSubrange<It>;


template<typename It>
struct MergeSubranges
{
    It first;
    It last;
};

template<typename It>
MergeSubranges(It, It) -> MergeSubranges<It>;


template<typename It>
struct Compare
{
    It first;
    It second;
};

template<typename It>
Compare(It, It) -> Compare<It>;


template<typename It>
using Change = detail::parametrize<It,
    Swap,
    SelectPivot,
    SelectSubrange,
    MergeSubranges,
    Compare
>;

} // namespace exam::sort::change
