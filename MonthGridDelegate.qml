// Copyright (C) 2021 The Qt Company Ltd.
// SPDX-License-Identifier: LicenseRef-Qt-Commercial OR BSD-3-Clause

import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Controls.Material

import App

ColumnLayout {
    id: root

    required property CalendarClient eventDatabase

    required property bool today
    required property int year
    required property int month
    required property int day

    required property int visibleMonth

    readonly property bool isCurrentMonth: month === root.visibleMonth

    Material.theme: today ? Material.Dark : undefined

    Label {
        id: dayText
        horizontalAlignment: Text.AlignHCenter
        topPadding: 4
        text: day
        color: isCurrentMonth ? Material.primaryTextColor : Material.secondaryTextColor
        font.italic: !isCurrentMonth;

        Layout.fillWidth: true

        Rectangle {
            width: height
            height: Math.max(dayText.implicitWidth, dayText.implicitHeight)
            radius: width / 2
            color: Material.accentColor
            anchors.centerIn: dayText
            anchors.verticalCenterOffset: dayText.height - dayText.baselineOffset
            z: -1
            visible: root.today
        }
    }

    ListView {
        spacing: 1
        clip: true

        Layout.fillWidth: true
        Layout.fillHeight: true
        Layout.topMargin: 4

        delegate: ItemDelegate {
            id: itemDelegate
            //width: root.width
            text: name
            font.pixelSize: Qt.application.font.pixelSize * 0.8
            leftPadding: 4
            rightPadding: 4
            topPadding: 4
            bottomPadding: 4

            ToolTip.text: description
            ToolTip.visible: hovered && description !== ""

            required property string name
            required property string description

            Material.theme: Material.Dark

            background: Rectangle {
                color: isCurrentMonth ? itemDelegate.Material.primary : itemDelegate.Material.backgroundDimColor;
                radius: 3
            }
        }
        model: EventModel {
            eventDatabase: root.eventDatabase
            date: new Date(root.year, root.month, root.day)
        }
    }
}
