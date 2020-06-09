#include "Manager.hpp"
#include "Change.hpp"
#include "Meta/Map.hpp"
#include "Meta/Overload.hpp"
#include "Sort/Type.hpp"
#include "Sort/Change.hpp"
#include "Sort/Sort.hpp"
#include "../src/types/Adress.hpp"

#include <variant>

namespace exam::ui {
namespace {

struct Value {
    struct Int {};
    struct Address {};

    using Variant = std::variant<
        Int,
        Address
    >;

    using Map = meta::map::Map<
        meta::map::Plain<Int, int>,
        meta::map::Plain<Address, int>
    >;
};

struct Container {
    struct Vector {};
    struct List {};

    using Variant = std::variant<
        Vector,
        List
    >;

    using Map = meta::map::Map<
        meta::map::Generic<Vector, std::vector>,
        meta::map::Generic<List, std::list>
    >;

    static constexpr auto from_string(const std::string_view str) noexcept -> std::optional<Variant>
    {
        if (str == "Vector") {
            return Vector{};
        }

        if (str == "List") {
            return List{};
        }

        return {};
    }
};

struct Order {
    struct Asc {};
    struct Desc {};

    using Variant = std::variant<
        Asc,
        Desc
    >;

    using Map = meta::map::Map<
        meta::map::Plain<Asc, std::less<>>,
        meta::map::Plain<Desc, std::greater<>>
    >;

    static constexpr auto from_string(const std::string_view str) noexcept -> std::optional<Variant>
    {
        if (str == "Asc") {
            return Asc{};
        }

        if (str == "Desc") {
            return Desc{};
        }

        return {};
    }
};

} // namespace

struct Manager::Impl
{
    /// Data to be sorted
    Value::Variant value;
    /// Vector of data to be sorted
    std::vector<int> data;
    /// Container to be sorted
    Container::Variant container;
    /// Possible order type
    Order::Variant order;
    /// Algorithm type
    sort::type::Type algorithm;
};

Manager::Manager()
    : QObject{},
      _pimpl{new Impl{}}
{ }

Manager::~Manager() noexcept = default;

void Manager::selectContainerType(const QString type)
{
    const auto container = Container::from_string(type.toStdString());
    if (!container) {
        /// TODO: notify about inconsistency
        return;
    }

    _pimpl->container = std::move(*container);
}

void Manager::selectOrderType(const QString type)
{
    const auto order = Order::from_string(type.toStdString());
    if (!order) {
        /// TODO: notify about inconsistency
        return;
    }

    _pimpl->order = std::move(*order);
}

void Manager::selectSortType(const QString type)
{
    const auto algorithm = sort::type::from_string(type.toStdString());
    if (!algorithm) {
        /// TODO: notify about inconsistency
        return;
    }

    _pimpl->algorithm = std::move(*algorithm);
}

QVariantList Manager::execute(QVariantList data)
{
    QVariantList result;

    std::visit(
        [&] (auto value) mutable {
            using Value = Value::Map::template Get<decltype(value)>;

            std::visit(
                [&] (auto value) mutable {
                    using Container = Container::Map::template Get<decltype(value), Value>;

                    Container container;

                    std::transform(
                        _pimpl->data.begin(),
                        _pimpl->data.end(),
                        std::back_inserter(container),
                        [] (const auto& value) {
                            /// TODO: improve with proper serialization
                            return value;
                        }
                    );

                    const auto order = [&] (const auto& lhs, const auto& rhs) {
                        return std::visit(
                            [&] (auto value) {
                                using Order = Order::Map::template Get<decltype(value)>;

                                return Order{}(lhs, rhs);
                            },
                            _pimpl->order 
                        );
                    };

                    const auto changes = std::visit(
                        [&] (auto value) {
                            return sort::Sort<decltype(value)>{}(
                                container.begin(),
                                container.end(),
                                order
                            );
                        },
                        _pimpl->algorithm
                    );

                    std::transform(
                        changes.begin(),
                        changes.end(),
                        std::back_inserter(result),
                        [&] (const auto& value) {
                            using It = typename Container::iterator;

                            const auto index = [&] (const auto iterator) {
                                return static_cast<std::size_t>(std::distance(container.begin(), iterator));
                            };

                            QVariant variant;

                            std::visit(meta::Overload{
                                [&] (const sort::change::Swap<It>& change) mutable {
                                    variant.setValue(
                                        change::Swap{
                                            index(change.first),
                                            index(change.second)
                                        }
                                    );
                                },
                                [&] (const sort::change::SelectPivot<It>& change) mutable {
                                    variant.setValue(
                                        change::SelectPivot{
                                            index(change.value)
                                        }
                                    );
                                },
                                [&] (const sort::change::SelectSubrange<It>& change) mutable {
                                    variant.setValue(
                                        change::SelectSubrange{
                                            index(change.first),
                                            index(change.last)
                                        }
                                    );
                                },
                                [&] (const sort::change::MergeSubranges<It>& change) mutable {
                                    variant.setValue(
                                        change::MergeSubranges{
                                            index(change.first),
                                            index(change.last)
                                        }
                                    );
                                }},
                                value
                            );

                            return variant;
                        }
                    );
                },
                _pimpl->container
            );        
        },
        _pimpl->value
    );

    return result;
}

} // namespace exam::ui
