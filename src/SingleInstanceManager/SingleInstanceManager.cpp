#include "SingleInstanceManager.hpp"

#include <QDBusConnection>
#include <QDBusMessage>
#include <iostream>

SingleInstanceManager::SingleInstanceManager(std::function<void(std::optional<std::string> data)> onNewInstanceStarted, std::optional<std::string> data, QObject* parent): QObject(parent), onNewInstanceStarted(onNewInstanceStarted) {
    QDBusConnection sessionBus = QDBusConnection::sessionBus();
    
    if (!sessionBus.registerService("com.example.application")) {
        QDBusMessage message = QDBusMessage::createMethodCall("com.example.application", "/SingleInstanceManager", "com.example.application.SingleInstanceManager", "newInstanceStarted");
        if (data.has_value()) {
            message << QString(data.value().c_str());
        } else {
            message << "";
        }

        QDBusMessage reply = sessionBus.call(message);
        if (reply.type() == QDBusMessage::ErrorMessage) {
            std::cerr << "DBus error: " << reply.errorMessage().toStdString() << std::endl;
        }

        exit(0);
    }

    if (!sessionBus.registerObject("/SingleInstanceManager", this, QDBusConnection::ExportAllSlots | QDBusConnection::ExportAllSignals)) {
        std::cerr << "Failed to register DBus object: " << sessionBus.lastError().message().toStdString() << std::endl;
        exit(1);
    }
}

void SingleInstanceManager::newInstanceStarted(const QString& data) {
    if (this->onNewInstanceStarted) {
        this->onNewInstanceStarted( data.isEmpty() ? std::nullopt : std::make_optional(data.toStdString()) );
    }
}