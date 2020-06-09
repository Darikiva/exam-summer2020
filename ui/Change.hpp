#pragma once

#include <QMetaType>
#include <QObject>
#include <cstdint>

namespace exam::ui::change
{

class Swap
{
    Q_GADGET
    Q_PROPERTY(unsigned int first READ first)
    Q_PROPERTY(unsigned int second READ second)
    Q_PROPERTY(QString type READ type)
public:
    Swap(const std::size_t first, const std::size_t second) noexcept :
        _first{first},
        _second{second}
    { }

    Swap() = default;
    Swap(const Swap&) = default;
    Swap& operator=(const Swap&) = default;

    std::size_t first() const noexcept
    {
        return _first;
    }

    std::size_t second() const noexcept
    {
        return _second;
    }


    QString type() const
    {
        return "Swap";
    }

private:
    std::size_t _first{0};
    std::size_t _second{0};
};

class SelectPivot
{
    Q_GADGET
    Q_PROPERTY(unsigned int value READ value)
    Q_PROPERTY(QString type READ type)
public:
    explicit SelectPivot(const std::size_t value) noexcept :
        _value{value}
    { }

    SelectPivot() = default;
    SelectPivot(const SelectPivot&) = default;
    SelectPivot& operator=(const SelectPivot&) = default;

    std::size_t value() const noexcept
    {
        return _value;
    }

    QString type() const
    {
        return "SelectPivot";
    }

private:
    std::size_t _value{0};
};

class SelectSubrange
{
    Q_GADGET
    Q_PROPERTY(unsigned int first READ first)
    Q_PROPERTY(unsigned int last READ last)
    Q_PROPERTY(QString type READ type)
public:
    SelectSubrange(const std::size_t first, const std::size_t last) noexcept :
        _first{first},
        _last{last}
    { }

    SelectSubrange() = default;
    SelectSubrange(const SelectSubrange&) = default;
    SelectSubrange& operator=(const SelectSubrange&) = default;

    std::size_t first() const noexcept
    {
        return _first;
    }

    std::size_t last() const noexcept
    {
        return _last;
    }


    QString type() const
    {
        return "SelectSubrange";
    }

private:
    std::size_t _first{0};
    std::size_t _last{0};
};

class MergeSubranges
{
    Q_GADGET
    Q_PROPERTY(unsigned int first READ first)
    Q_PROPERTY(unsigned int last READ last)
    Q_PROPERTY(QString type READ type)
public:
    MergeSubranges(const std::size_t first, const std::size_t last) noexcept :
        _first{first},
        _last{last}
    { }

    MergeSubranges() = default;
    MergeSubranges(const MergeSubranges&) = default;
    MergeSubranges& operator=(const MergeSubranges&) = default;

    std::size_t first() const noexcept
    {
        return _first;
    }

    std::size_t last() const noexcept
    {
        return _last;
    }


    QString type() const
    {
        return "MergeSubranges";
    }

private:
    std::size_t _first{0};
    std::size_t _last{0};
};

} // namespace exam::ui::change

Q_DECLARE_METATYPE(exam::ui::change::Swap);
Q_DECLARE_METATYPE(exam::ui::change::SelectPivot);
Q_DECLARE_METATYPE(exam::ui::change::SelectSubrange);
Q_DECLARE_METATYPE(exam::ui::change::MergeSubranges);
