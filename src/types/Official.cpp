#include "Official.hpp"
#include <tuple>

namespace exam::types {

Official::Official(const string& m, const string& o, const string& d, const string& n):
    _ministry(m), _organization(o), _department(d), _name(n){}

void Official::setMinistry(const string& m)  { _ministry = m; }
void Official::setOrganization(const string& o) { _organization = o; }
void Official::setDepartment(const string& d) { _department = d; }
void Official::setName(const string& n) { _name = n; }

string Official::getMinistry() const noexcept { return _ministry; }
string Official::getOrganization() const noexcept { return _organization; }
string Official::getDepartment() const noexcept { return _department; }
string Official::getName() const noexcept { return _name; }

bool operator>(const Official& left, const Official& right) {
    static const auto tie = [](const auto& value) {
        return std::tie(value._ministry, value._organization, value._department, value._name);
    };

    return tie(left) < tie(right);
}
bool operator<(const Official& left, const Official& right) {
    static const auto tie = [](const auto& value) {
        return std::tie(value._ministry, value._organization, value._department, value._name);
    };

    return tie(left) < tie(right);
}
bool operator>=(const Official& left, const Official& right) {
    return !(left < right);
}
bool operator<=(const Official& left, const Official& right) {
    return !(left > right);
}
bool operator==(const Official& left, const Official& right) {
    static const auto tie = [](const auto& value) {
        return std::tie(value._ministry, value._organization, value._department, value._name);
    };

    return tie(left) == tie(right);
}
bool operator!=(const Official& left, const Official& right) {
    return !(left == right);
}

} //namespace exam::types