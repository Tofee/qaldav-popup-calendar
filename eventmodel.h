// Copyright (C) 2021 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR BSD-3-Clause

#ifndef CONTACTMODEL_H
#define CONTACTMODEL_H

#include <QAbstractListModel>
#include <QDate>
#include <QtQml>

#include "CalDAVCalendar/CalendarClient.h"
#include "CalDAVCalendar/CalendarEvent.h"

class SqlEventDatabase;

class EventModel : public QAbstractListModel
{
    Q_OBJECT
    Q_PROPERTY(CalendarClient *eventDatabase READ eventDatabase WRITE setEventDatabase NOTIFY eventDatabaseChanged)
    Q_PROPERTY(QDate date READ date WRITE setDate NOTIFY dateChanged)
    QML_ELEMENT
    Q_MOC_INCLUDE("CalDAVCalendar/CalendarClient.h")

public:
    EventModel(QObject *parent = nullptr);

    enum ContactRole {
        NameRole = Qt::UserRole,
        DescriptionRole,
        StartDateRole,
        EndDateRole
    };
    Q_ENUM(ContactRole)

    CalendarClient *eventDatabase();
    void setEventDatabase(CalendarClient *eventDatabase);

    QDate date() const;
    void setDate(QDate date);

    int rowCount(const QModelIndex & = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;
    QHash<int, QByteArray> roleNames() const;

signals:
    void eventDatabaseChanged();
    void dateChanged();

private:
    bool isValid() const;
    void repopulate();

    CalendarClient *m_eventDatabase = nullptr;
    QDate m_date;
    QList<CalendarEvent*> m_events;
};

#endif // CONTACTMODEL_H
