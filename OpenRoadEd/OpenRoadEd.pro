#-------------------------------------------------
#
# Project created by QtCreator 2019-03-12T12:51:06
#
#-------------------------------------------------

QT       += core gui

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
OpenRoadEd/main.cpp \
OpenRoadEd/OpenDrive/OpenDriveXmlWriter.cpp \
OpenRoadEd/OpenDrive/OtherStructures.cpp \
OpenRoadEd/OpenDrive/OpenDrive.cpp \
OpenRoadEd/OpenDrive/Road.cpp \
OpenRoadEd/OpenDrive/Junction.cpp \
OpenRoadEd/OpenDrive/Lane.cpp \
OpenRoadEd/OpenDrive/OpenDriveXmlParser.cpp \
OpenRoadEd/OpenDrive/ObjectSignal.cpp \
OpenRoadEd/OpenDrive/RoadGeometry.cpp \
OpenRoadEd/TinyXML/tinyxml.cpp \
OpenRoadEd/TinyXML/tinyxmlparser.cpp \
OpenRoadEd/TinyXML/tinystr.cpp \
OpenRoadEd/TinyXML/tinyxmlerror.cpp \
OpenRoadEd/Osg/OSGObjectNode.cpp \
OpenRoadEd/Osg/OSGCameraControls.cpp \
OpenRoadEd/Osg/OSGRecordsHelpers.cpp \
OpenRoadEd/Osg/OSGRoad.cpp \
OpenRoadEd/Osg/OSGScenery.cpp \
OpenRoadEd/Osg/OSGCameraControls2.cpp \
OpenRoadEd/Osg/OSGJunction.cpp \
OpenRoadEd/Osg/OSGMain.cpp \
OpenRoadEd/Qt/ConfigDialogs/SceneryDialog.cpp \
OpenRoadEd/Qt/ConfigDialogs/ReferencePlaneDialog.cpp \
OpenRoadEd/Qt/CreationWidgets/DeleteAll.cpp \
OpenRoadEd/Qt/CreationWidgets/CreationAllJunction.cpp \
OpenRoadEd/Qt/CreationWidgets/CreationPage.cpp \
OpenRoadEd/Qt/CreationWidgets/CreationAllRoad.cpp \
OpenRoadEd/Qt/QOSGWidget.cpp \
OpenRoadEd/Qt/SettingsWidgets/SettingsRoad.cpp \
OpenRoadEd/Qt/SettingsWidgets/SettingsPage.cpp \
OpenRoadEd/Qt/SettingsWidgets/SettingsLateralProfileSuper.cpp \
OpenRoadEd/Qt/SettingsWidgets/SettingsElevationRecord.cpp \
OpenRoadEd/Qt/SettingsWidgets/SettingsJunctionConnection.cpp \
OpenRoadEd/Qt/SettingsWidgets/SettingsLaneHeightRecord.cpp \
OpenRoadEd/Qt/SettingsWidgets/SettingsLaneAccessRecord.cpp \
OpenRoadEd/Qt/SettingsWidgets/SettingsLane.cpp \
OpenRoadEd/Qt/SettingsWidgets/SettingsLaneSection.cpp \
OpenRoadEd/Qt/SettingsWidgets/SettingsGeometryLine.cpp \
OpenRoadEd/Qt/SettingsWidgets/SettingsLaneVisibilityRecord.cpp \
OpenRoadEd/Qt/SettingsWidgets/SettingsJunction.cpp \
OpenRoadEd/Qt/SettingsWidgets/SettingsLateralProfileCrossfall.cpp \
OpenRoadEd/Qt/SettingsWidgets/SettingsLaneWidthRecord.cpp \
OpenRoadEd/Qt/SettingsWidgets/SettingsJunctionPriority.cpp \
OpenRoadEd/Qt/SettingsWidgets/SettingsLaneMaterialRecord.cpp \
OpenRoadEd/Qt/SettingsWidgets/SettingsJunctionLaneLink.cpp \
OpenRoadEd/Qt/SettingsWidgets/SettingsLaneRoadMark.cpp \
OpenRoadEd/Qt/SettingsWidgets/SettingsGeometryTurn.cpp \
OpenRoadEd/Qt/SettingsWidgets/SettingsRoadTypeRecord.cpp \
OpenRoadEd/Qt/SettingsWidgets/SettingsLaneSpeedRecord.cpp \
OpenRoadEd/Qt/SettingsWidgets/SettingsJunctionController.cpp \
OpenRoadEd/Qt/ToolsDialogs/GetRoadDialog.cpp \
OpenRoadEd/Qt/ToolsDialogs/ConnectRoadsDialog.cpp \
OpenRoadEd/Qt/ToolsDialogs/LoadingDialog.cpp \
OpenRoadEd/Qt/MainWindow.cpp \
OpenRoadEd/Qt/Tree/RoadTreeItems.cpp \
OpenRoadEd/Qt/Tree/RoadTree.cpp \
OpenRoadEd/Cephes/const.cpp \
OpenRoadEd/Cephes/fresnl.cpp \
OpenRoadEd/Cephes/polevl.c

HEADERS += \
OpenRoadEd/OpenDrive/OpenDriveXmlParser.h \
OpenRoadEd/OpenDrive/RoadGeometry.h \
OpenRoadEd/OpenDrive/Road.h \
OpenRoadEd/OpenDrive/Junction.h \
OpenRoadEd/OpenDrive/OpenDriveXmlWriter.h \
OpenRoadEd/OpenDrive/Lane.h \
OpenRoadEd/OpenDrive/OtherStructures.h \
OpenRoadEd/OpenDrive/OpenDrive.h \
OpenRoadEd/OpenDrive/ObjectSignal.h \
OpenRoadEd/TinyXML/tinyxml.h \
OpenRoadEd/TinyXML/tinystr.h \
OpenRoadEd/Osg/OSGJunction.h \
OpenRoadEd/Osg/OSGRoad.h \
OpenRoadEd/Osg/OSGCameraControls2.h \
OpenRoadEd/Osg/OSGMain.h \
OpenRoadEd/Osg/OSGObjectNode.h \
OpenRoadEd/Osg/OSGCameraControls.h \
OpenRoadEd/Osg/OSGRecordsHelpers.h \
OpenRoadEd/Osg/OSGConstants.h \
OpenRoadEd/Osg/OSGScenery.h \
OpenRoadEd/Debug/BuildLog.htm \
OpenRoadEd/Qt/ConfigDialogs/SceneryDialog.h \
OpenRoadEd/Qt/ConfigDialogs/ReferencePlaneDialog.h \
OpenRoadEd/Qt/CreationWidgets/DeleteAll.h \
OpenRoadEd/Qt/CreationWidgets/CreationAllRoad.h \
OpenRoadEd/Qt/CreationWidgets/CreationAllJunction.h \
OpenRoadEd/Qt/CreationWidgets/CreationPage.h \
OpenRoadEd/Qt/QOSGWidget.h \
OpenRoadEd/Qt/MainWindow.h \
OpenRoadEd/Qt/SettingsWidgets/SettingsJunctionLaneLink.h \
OpenRoadEd/Qt/SettingsWidgets/SettingsLaneSpeedRecord.h \
OpenRoadEd/Qt/SettingsWidgets/SettingsJunction.h \
OpenRoadEd/Qt/SettingsWidgets/SettingsGeometryLine.h \
OpenRoadEd/Qt/SettingsWidgets/SettingsLaneRoadMark.h \
OpenRoadEd/Qt/SettingsWidgets/SettingsLaneHeightRecord.h \
OpenRoadEd/Qt/SettingsWidgets/SettingsJunctionConnection.h \
OpenRoadEd/Qt/SettingsWidgets/SettingsPage.h \
OpenRoadEd/Qt/SettingsWidgets/SettingsLaneSection.h \
OpenRoadEd/Qt/SettingsWidgets/SettingsGeometryTurn.h \
OpenRoadEd/Qt/SettingsWidgets/SettingsLaneAccessRecord.h \
OpenRoadEd/Qt/SettingsWidgets/SettingsRoadTypeRecord.h \
OpenRoadEd/Qt/SettingsWidgets/SettingsLaneMaterialRecord.h \
OpenRoadEd/Qt/SettingsWidgets/SettingsElevationRecord.h \
OpenRoadEd/Qt/SettingsWidgets/SettingsLaneVisibilityRecord.h \
OpenRoadEd/Qt/SettingsWidgets/SettingsJunctionController.h \
OpenRoadEd/Qt/SettingsWidgets/SettingsLateralProfileSuper.h \
OpenRoadEd/Qt/SettingsWidgets/SettingsJunctionPriority.h \
OpenRoadEd/Qt/SettingsWidgets/SettingsLane.h \
OpenRoadEd/Qt/SettingsWidgets/SettingsRoad.h \
OpenRoadEd/Qt/SettingsWidgets/SettingsLaneWidthRecord.h \
OpenRoadEd/Qt/SettingsWidgets/SettingsLateralProfileCrossfall.h \
OpenRoadEd/Qt/ToolsDialogs/GetRoadDialog.h \
OpenRoadEd/Qt/ToolsDialogs/ConnectRoadsDialog.h \
OpenRoadEd/Qt/ToolsDialogs/LoadingDialog.h \
OpenRoadEd/Qt/Tree/RoadTreeItems.h \
OpenRoadEd/Qt/Tree/RoadTree.h \
OpenRoadEd/Cephes/mconf.h
