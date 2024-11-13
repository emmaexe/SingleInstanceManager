#pragma once

#include <QObject>
#include <QString>
#include <functional>
#include <optional>
#include <string>

class SingleInstanceManager: public QObject {
    Q_OBJECT
    Q_CLASSINFO("D-Bus Interface", "com.example.application.SingleInstanceManager")
    public:
        SingleInstanceManager(std::function<void(std::optional<std::string> data)> onNewInstanceStarted, std::optional<std::string> data, QObject* parent = nullptr);
        std::function<void(const std::optional<std::string> data)> onNewInstanceStarted;
    public slots:
        void newInstanceStarted(const QString& data);
};