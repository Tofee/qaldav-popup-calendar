// Copyright (C) 2021 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR BSD-3-Clause

#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QCommandLineParser>
#include <QIcon>

#include "CalDAVCalendar/CalendarClient_CalDAV.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    QCoreApplication::setApplicationName("qaldav-popup-calendar");
    QCoreApplication::setApplicationVersion("0.1");

    QCommandLineParser parser;
    parser.setApplicationDescription("CalDAV popup calendar");
    parser.addHelpOption();
    parser.addVersionOption();

    parser.addOptions({
          {"url",
           QCoreApplication::translate("main", "Retrieve CalDAV calendar from <url>."),
           QCoreApplication::translate("main", "url")},
          {"user",
           QCoreApplication::translate("main", "Username for CalDAV server."),
           QCoreApplication::translate("main", "user")},
          {"pass",
           QCoreApplication::translate("main", "Password for CalDAV server."),
           QCoreApplication::translate("main", "pass")},
    });
    parser.process(app);

    QUrl calDALServer = parser.value("url");
    QString username = parser.value("user");
    QString password = parser.value("pass");

    QIcon::setThemeName("qaldav");

    QQmlApplicationEngine engine;
    CalendarClient_CalDAV eventDatabase;
    eventDatabase.setHostURL(calDALServer);
    eventDatabase.setUsername(username);
    eventDatabase.setPassword(password);
    engine.setInitialProperties({{ "eventDatabase", QVariant::fromValue(&eventDatabase) }});

    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
