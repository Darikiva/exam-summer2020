#pragma once
#include <string>
using std::string;

namespace exam::types {

class Official {
public:
    Official() = default;
    Official(const string& m, const string& o, const string& d, const string& n);

    void setMinistry(const string& m);
    void setOrganization(const string& o);
    void setDepartment(const string& d);
    void setName(const string& n);

    string getMinistry() const noexcept;
    string getOrganization() const noexcept;
    string getDepartment() const noexcept;
    string getName() const noexcept;

    friend bool operator>(const Official& left, const Official& right);
    friend bool operator>=(const Official& left, const Official& right);
    friend bool operator<(const Official& left, const Official& right);
    friend bool operator<=(const Official& left, const Official& right);
    friend bool operator==(const Official& left, const Official& right);
    friend bool operator!=(const Official& left, const Official& right);
private:
    string _ministry;
    string _organization;
    string _department;
    string _name;
};

} //namespace exam::types