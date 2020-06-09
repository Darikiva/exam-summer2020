#pragma once

#include <optional>
#include <cstring>
#include <string>

namespace exam::types {

/**
 * @brief Representation of physical address.
 */
class Address
{
public:
    void country(std::string country) noexcept
    {
        _country = std::move(country);
    }

    [[nodiscard]]
    auto country() const noexcept -> const std::string
    {
        return _country;
    }

    void state(std::string state) noexcept
    {
        _state = std::move(state);
    }

    [[nodiscard]]
    auto state() const noexcept -> const std::string&
    {
        return _state;
    }

    void city(std::string city) noexcept
    {
        _city = std::move(city);
    }

    [[nodiscard]]
    auto city() const noexcept -> const std::string&
    {
        return _city;
    }

    void street(std::string street) noexcept
    {
        _street = std::move(street);
    }

    [[nodiscard]]
    auto street() const noexcept -> const std::string&
    {
        return _street;
    }

    void building(const uint32_t building) noexcept
    {
        _building = building;
    }

    [[nodiscard]]
    auto building() const noexcept -> uint32_t
    {
        return _building;
    }

    void flat(const uint32_t flat) noexcept
    {
        _flat.emplace(flat);
    }

    [[nodiscard]]
    auto flat() const noexcept -> std::optional<uint32_t>
    {
        return _flat;
    }

    friend bool operator<(const Address& lhs, const Address& rhs) noexcept;
    friend bool operator>(const Address& lhs, const Address& rhs) noexcept;
    friend bool operator==(const Address& lhs, const Address& rhs) noexcept;

private:
    std::string _country;
    std::string _state;
    std::string _city;
    std::string _street;
    uint32_t _building;
    std::optional<uint32_t> _flat;
};

[[nodiscard]]
bool operator<(const Address& lhs, const Address& rhs) noexcept
{
    static const auto tie = [] (const auto& value) {
        return std::tie(
            value._country,
            value._state,
            value._city,
            value._street,
            value._building,
            value._flat
        );
    };

    return tie(lhs) < tie(rhs);
};

[[nodiscard]]
bool operator>(const Address& lhs, const Address& rhs) noexcept
{
    static const auto tie = [] (const auto& value) {
        return std::tie(
            value._country,
            value._state,
            value._city,
            value._street,
            value._building,
            value._flat
        );
    };

    return tie(lhs) > tie(rhs);
}

[[nodiscard]]
bool operator==(const Address& lhs, const Address& rhs) noexcept
{
    return !(lhs < rhs) && !(lhs > rhs);
}

} // namespace exam::types
