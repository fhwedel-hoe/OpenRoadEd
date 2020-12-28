#-------------------------------------------------
#
# Project created by QtCreator 2019-03-12T12:51:06
#
#-------------------------------------------------

QT       += core gui

QT += opengl
QT += widgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = OpenRoadEd
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += link_pkgconfig
PKGCONFIG += openscenegraph

SOURCES += \
main.cpp \
OpenDrive/OpenDriveXmlWriter.cpp \
OpenDrive/OtherStructures.cpp \
OpenDrive/OpenDrive.cpp \
OpenDrive/Road.cpp \
OpenDrive/Junction.cpp \
OpenDrive/Lane.cpp \
OpenDrive/OpenDriveXmlParser.cpp \
OpenDrive/ObjectSignal.cpp \
OpenDrive/RoadGeometry.cpp \
TinyXML/tinyxml.cpp \
TinyXML/tinyxmlparser.cpp \
TinyXML/tinystr.cpp \
TinyXML/tinyxmlerror.cpp \
Osg/OSGObjectNode.cpp \
Osg/OSGCameraControls.cpp \
Osg/OSGRecordsHelpers.cpp \
Osg/OSGRoad.cpp \
Osg/OSGScenery.cpp \
Osg/OSGCameraControls2.cpp \
Osg/OSGJunction.cpp \
Osg/OSGMain.cpp \
Qt/ConfigDialogs/SceneryDialog.cpp \
Qt/ConfigDialogs/ReferencePlaneDialog.cpp \
Qt/CreationWidgets/DeleteAll.cpp \
Qt/CreationWidgets/CreationAllJunction.cpp \
Qt/CreationWidgets/CreationPage.cpp \
Qt/CreationWidgets/CreationAllRoad.cpp \
Qt/QOSGWidget.cpp \
Qt/SettingsWidgets/SettingsRoad.cpp \
Qt/SettingsWidgets/SettingsPage.cpp \
Qt/SettingsWidgets/SettingsLateralProfileSuper.cpp \
Qt/SettingsWidgets/SettingsElevationRecord.cpp \
Qt/SettingsWidgets/SettingsJunctionConnection.cpp \
Qt/SettingsWidgets/SettingsLaneHeightRecord.cpp \
Qt/SettingsWidgets/SettingsLaneAccessRecord.cpp \
Qt/SettingsWidgets/SettingsLane.cpp \
Qt/SettingsWidgets/SettingsLaneSection.cpp \
Qt/SettingsWidgets/SettingsGeometryLine.cpp \
Qt/SettingsWidgets/SettingsLaneVisibilityRecord.cpp \
Qt/SettingsWidgets/SettingsJunction.cpp \
Qt/SettingsWidgets/SettingsLateralProfileCrossfall.cpp \
Qt/SettingsWidgets/SettingsLaneWidthRecord.cpp \
Qt/SettingsWidgets/SettingsJunctionPriority.cpp \
Qt/SettingsWidgets/SettingsLaneMaterialRecord.cpp \
Qt/SettingsWidgets/SettingsJunctionLaneLink.cpp \
Qt/SettingsWidgets/SettingsLaneRoadMark.cpp \
Qt/SettingsWidgets/SettingsGeometryTurn.cpp \
Qt/SettingsWidgets/SettingsRoadTypeRecord.cpp \
Qt/SettingsWidgets/SettingsLaneSpeedRecord.cpp \
Qt/SettingsWidgets/SettingsJunctionController.cpp \
Qt/ToolsDialogs/GetRoadDialog.cpp \
Qt/ToolsDialogs/ConnectRoadsDialog.cpp \
Qt/ToolsDialogs/LoadingDialog.cpp \
Qt/MainWindow.cpp \
Qt/Tree/RoadTreeItems.cpp \
Qt/Tree/RoadTree.cpp \
Cephes/const.cpp \
Cephes/fresnl.cpp \
Cephes/polevl.c

HEADERS += \
OpenDrive/OpenDriveXmlParser.h \
OpenDrive/RoadGeometry.h \
OpenDrive/Road.h \
OpenDrive/Junction.h \
OpenDrive/OpenDriveXmlWriter.h \
OpenDrive/Lane.h \
OpenDrive/OtherStructures.h \
OpenDrive/OpenDrive.h \
OpenDrive/ObjectSignal.h \
TinyXML/tinyxml.h \
TinyXML/tinystr.h \
Osg/OSGJunction.h \
Osg/OSGRoad.h \
Osg/OSGCameraControls2.h \
Osg/OSGMain.h \
Osg/OSGObjectNode.h \
Osg/OSGCameraControls.h \
Osg/OSGRecordsHelpers.h \
Osg/OSGConstants.h \
Osg/OSGScenery.h \
Debug/BuildLog.htm \
Qt/ConfigDialogs/SceneryDialog.h \
Qt/ConfigDialogs/ReferencePlaneDialog.h \
Qt/CreationWidgets/DeleteAll.h \
Qt/CreationWidgets/CreationAllRoad.h \
Qt/CreationWidgets/CreationAllJunction.h \
Qt/CreationWidgets/CreationPage.h \
Qt/QOSGWidget.h \
Qt/MainWindow.h \
Qt/SettingsWidgets/SettingsJunctionLaneLink.h \
Qt/SettingsWidgets/SettingsLaneSpeedRecord.h \
Qt/SettingsWidgets/SettingsJunction.h \
Qt/SettingsWidgets/SettingsGeometryLine.h \
Qt/SettingsWidgets/SettingsLaneRoadMark.h \
Qt/SettingsWidgets/SettingsLaneHeightRecord.h \
Qt/SettingsWidgets/SettingsJunctionConnection.h \
Qt/SettingsWidgets/SettingsPage.h \
Qt/SettingsWidgets/SettingsLaneSection.h \
Qt/SettingsWidgets/SettingsGeometryTurn.h \
Qt/SettingsWidgets/SettingsLaneAccessRecord.h \
Qt/SettingsWidgets/SettingsRoadTypeRecord.h \
Qt/SettingsWidgets/SettingsLaneMaterialRecord.h \
Qt/SettingsWidgets/SettingsElevationRecord.h \
Qt/SettingsWidgets/SettingsLaneVisibilityRecord.h \
Qt/SettingsWidgets/SettingsJunctionController.h \
Qt/SettingsWidgets/SettingsLateralProfileSuper.h \
Qt/SettingsWidgets/SettingsJunctionPriority.h \
Qt/SettingsWidgets/SettingsLane.h \
Qt/SettingsWidgets/SettingsRoad.h \
Qt/SettingsWidgets/SettingsLaneWidthRecord.h \
Qt/SettingsWidgets/SettingsLateralProfileCrossfall.h \
Qt/ToolsDialogs/GetRoadDialog.h \
Qt/ToolsDialogs/ConnectRoadsDialog.h \
Qt/ToolsDialogs/LoadingDialog.h \
Qt/Tree/RoadTreeItems.h \
Qt/Tree/RoadTree.h \
Cephes/mconf.h
