#include "Manager.hpp"

#include <QQmlApplicationEngine>
#include <QGuiApplication>
#include <QQmlContext>

int main(int argc, char* argv[])
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);

    QGuiApplication app{argc, argv};
    QQmlApplicationEngine engine;
    exam::ui::Manager manager;

    engine.rootContext()->setContextProperty("manager", &manager);
    engine.load(QUrl{QStringLiteral("qrc:/main.qml")});

    return QGuiApplication::exec();
}
