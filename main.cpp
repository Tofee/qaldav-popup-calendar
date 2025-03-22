// Copyright (C) 2021 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR BSD-3-Clause

#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QSettings>
#include <QIcon>

#include "CalDAVCalendar/CalendarClient_CalDAV.h"

int main(int argc, char *argv[])
{
    QGuiApplication app(argc, argv);
    QCoreApplication::setOrganizationName("QalDAV");
    QCoreApplication::setApplicationName("qaldav-popup-calendar");
    QCoreApplication::setApplicationVersion("0.1");

    QIcon::setThemeName("qaldav");

    QSettings appSettings;
    QList<CalendarClient_CalDAV*> listCalendars;

    appSettings.beginGroup("Accounts");
    auto keys = appSettings.allKeys();
    appSettings.endGroup();
    for(auto keyAccount: keys) {
        QString calDALSection = appSettings.value("Accounts/" + keyAccount).value<QString>();
        QString calDALServer = appSettings.value(calDALSection + "/Url").value<QString>();
        QString username = appSettings.value(calDALSection + "/Login").value<QString>();
        QString password = appSettings.value(calDALSection + "/Password").value<QString>();

        CalendarClient_CalDAV *accountCalendar = new CalendarClient_CalDAV();
        accountCalendar->setHostURL(calDALServer);
        accountCalendar->setUsername(username);
        accountCalendar->setPassword(password);

        listCalendars.append(accountCalendar);
    }

    QQmlApplicationEngine engine;
    engine.setInitialProperties({{ "eventDatabase", QVariant::fromValue(listCalendars.first()) }});

    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    return app.exec();
}
