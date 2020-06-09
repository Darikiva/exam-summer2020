#pragma once

#include <QVariantList>
#include <QObject>
#include <QString>
#include <memory>

namespace exam::ui {

/**
 * @brief Main class mapped into QML to interact with
 *  actual implementation of sorting.
 */
class Manager final: public QObject
{
    Q_OBJECT
public:
    Manager();
    ~Manager() noexcept;

public slots:
    void selectContainerType(QString type);
    void selectOrderType(QString type);
    void selectSortType(QString type);
    QVariantList execute(QVariantList data);

private:
    struct Impl;
    std::unique_ptr<Impl> _pimpl;
};
    
} // namespace exam::ui
