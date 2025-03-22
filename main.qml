// Copyright (C) 2021 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR BSD-3-Clause

import QtCore
import QtQuick
import QtQuick.Controls
import QtQuick.Controls.Material
import QtQuick.Layouts

import App

ApplicationWindow {
    id: window
    width: 800
    height: 600
    title: qsTr("Event Calendar")
    visible: true

    required property CalendarClient eventDatabase

    readonly property date currentDate: new Date()
    property date shownDate: new Date()
    property int monthOffset: -wheelHandler.rotation/15
    onMonthOffsetChanged: {
        shownDate.setMonth(currentDate.getMonth()+monthOffset);
        eventDatabase.setMonth(shownDate.getMonth()+1);
        eventDatabase.setYear(shownDate.getFullYear());
    }

    header: ToolBar {
        Label {
            text: window.shownDate.toLocaleString(locale, "MMMM yyyy")
            font.pixelSize: Qt.application.font.pixelSize * 1.25
            anchors.centerIn: parent
        }
    }

    GridLayout {
        anchors.fill: parent
        columns: 2

        DayOfWeekRow {
            id: dayOfWeekRow
            locale: grid.locale
            font.bold: false
            delegate: Label {
                text: model.shortName
                font: dayOfWeekRow.font
                horizontalAlignment: Text.AlignHCenter
                verticalAlignment: Text.AlignVCenter
            }

            Layout.column: 1
            Layout.fillWidth: true
        }

        WeekNumberColumn {
            month: grid.month
            year: grid.year
            locale: grid.locale
            font.bold: false

            Layout.fillHeight: true
        }

        MonthGrid {
            id: grid
            month: window.shownDate.getMonth()
            year: window.shownDate.getFullYear()
            spacing: 0

            readonly property int gridLineThickness: 1

            Layout.fillWidth: true
            Layout.fillHeight: true

            delegate: MonthGridDelegate {
                id: gridDelegate
                visibleMonth: grid.month
                eventDatabase: window.eventDatabase
            }

            background: Item {
                x: grid.leftPadding
                y: grid.topPadding
                width: grid.availableWidth
                height: grid.availableHeight

                // Vertical lines
                Row {
                    spacing: (parent.width - (grid.gridLineThickness * rowRepeater.model)) / rowRepeater.model

                    Repeater {
                        id: rowRepeater
                        model: 7
                        delegate: Rectangle {
                            width: 1
                            height: grid.height
                            color: "#ccc"
                        }
                    }
                }

                // Horizontal lines
                Column {
                    spacing: (parent.height - (grid.gridLineThickness * columnRepeater.model)) / columnRepeater.model

                    Repeater {
                        id: columnRepeater
                        model: 6
                        delegate: Rectangle {
                            width: grid.width
                            height: 1
                            color: "#ccc"
                        }
                    }
                }
            }
        }
    }

    WheelHandler {
        id: wheelHandler
    }

    Settings {
        category: "Window"
        property alias x: window.x
        property alias y: window.y
        property alias width: window.width
        property alias height: window.height
    }
}
