cmake_minimum_required(VERSION 3.1) # this version is a guess

project(OpenRoadEd)
 
if(COMMAND cmake_policy)
  cmake_policy(SET CMP0003 NEW) # explicitly request new style for passing relative and absolute paths to linker
  cmake_policy(SET CMP0106 NEW) # Disable VTK specific cmake feature "Documentation"
endif(COMMAND cmake_policy)

set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

find_package(Qt5Widgets REQUIRED)
find_package(Qt5OpenGL REQUIRED)
find_package(Qt5Gui REQUIRED)
find_package(Qt5Core REQUIRED)
find_package(OpenSceneGraph REQUIRED osgDB osgViewer osgUtil osgGA)

add_subdirectory(osgQt)

set(TARGET_H "${CMAKE_SOURCE_DIR}/OpenDrive/OpenDriveXmlParser.h"
    "${CMAKE_SOURCE_DIR}/OpenDrive/RoadGeometry.h"
    "${CMAKE_SOURCE_DIR}/OpenDrive/Road.h"
    "${CMAKE_SOURCE_DIR}/OpenDrive/Junction.h"
    "${CMAKE_SOURCE_DIR}/OpenDrive/OpenDriveXmlWriter.h"
    "${CMAKE_SOURCE_DIR}/OpenDrive/Lane.h"
    "${CMAKE_SOURCE_DIR}/OpenDrive/OtherStructures.h"
    "${CMAKE_SOURCE_DIR}/OpenDrive/OpenDrive.h"
    "${CMAKE_SOURCE_DIR}/OpenDrive/ObjectSignal.h"
    "${CMAKE_SOURCE_DIR}/TinyXML/tinyxml.h"
    "${CMAKE_SOURCE_DIR}/TinyXML/tinystr.h"
    "${CMAKE_SOURCE_DIR}/Osg/OSGJunction.h"
    "${CMAKE_SOURCE_DIR}/Osg/OSGRoad.h"
    "${CMAKE_SOURCE_DIR}/Osg/OSGCameraControls2.h"
    "${CMAKE_SOURCE_DIR}/Osg/OSGMain.h"
    "${CMAKE_SOURCE_DIR}/Osg/OSGObjectNode.h"
    "${CMAKE_SOURCE_DIR}/Osg/OSGCameraControls.h"
    "${CMAKE_SOURCE_DIR}/Osg/OSGRecordsHelpers.h"
    "${CMAKE_SOURCE_DIR}/Osg/OSGConstants.h"
    "${CMAKE_SOURCE_DIR}/Osg/OSGScenery.h"
    "${CMAKE_SOURCE_DIR}/Qt/ConfigDialogs/SceneryDialog.h"
    "${CMAKE_SOURCE_DIR}/Qt/ConfigDialogs/ReferencePlaneDialog.h"
    "${CMAKE_SOURCE_DIR}/Qt/CreationWidgets/DeleteAll.h"
    "${CMAKE_SOURCE_DIR}/Qt/CreationWidgets/CreationAllRoad.h"
    "${CMAKE_SOURCE_DIR}/Qt/CreationWidgets/CreationAllJunction.h"
    "${CMAKE_SOURCE_DIR}/Qt/CreationWidgets/CreationPage.h"
    "${CMAKE_SOURCE_DIR}/Qt/QOSGWidget.h"
    "${CMAKE_SOURCE_DIR}/Qt/MainWindow.h"
    "${CMAKE_SOURCE_DIR}/Qt/SettingsWidgets/SettingsJunctionLaneLink.h"
    "${CMAKE_SOURCE_DIR}/Qt/SettingsWidgets/SettingsLaneSpeedRecord.h"
    "${CMAKE_SOURCE_DIR}/Qt/SettingsWidgets/SettingsJunction.h"
    "${CMAKE_SOURCE_DIR}/Qt/SettingsWidgets/SettingsGeometryLine.h"
    "${CMAKE_SOURCE_DIR}/Qt/SettingsWidgets/SettingsLaneRoadMark.h"
    "${CMAKE_SOURCE_DIR}/Qt/SettingsWidgets/SettingsLaneHeightRecord.h"
    "${CMAKE_SOURCE_DIR}/Qt/SettingsWidgets/SettingsJunctionConnection.h"
    "${CMAKE_SOURCE_DIR}/Qt/SettingsWidgets/SettingsPage.h"
    "${CMAKE_SOURCE_DIR}/Qt/SettingsWidgets/SettingsLaneSection.h"
    "${CMAKE_SOURCE_DIR}/Qt/SettingsWidgets/SettingsGeometryTurn.h"
    "${CMAKE_SOURCE_DIR}/Qt/SettingsWidgets/SettingsLaneAccessRecord.h"
    "${CMAKE_SOURCE_DIR}/Qt/SettingsWidgets/SettingsRoadTypeRecord.h"
    "${CMAKE_SOURCE_DIR}/Qt/SettingsWidgets/SettingsLaneMaterialRecord.h"
    "${CMAKE_SOURCE_DIR}/Qt/SettingsWidgets/SettingsElevationRecord.h"
    "${CMAKE_SOURCE_DIR}/Qt/SettingsWidgets/SettingsLaneVisibilityRecord.h"
    "${CMAKE_SOURCE_DIR}/Qt/SettingsWidgets/SettingsJunctionController.h"
    "${CMAKE_SOURCE_DIR}/Qt/SettingsWidgets/SettingsLateralProfileSuper.h"
    "${CMAKE_SOURCE_DIR}/Qt/SettingsWidgets/SettingsJunctionPriority.h"
    "${CMAKE_SOURCE_DIR}/Qt/SettingsWidgets/SettingsLane.h"
    "${CMAKE_SOURCE_DIR}/Qt/SettingsWidgets/SettingsRoad.h"
    "${CMAKE_SOURCE_DIR}/Qt/SettingsWidgets/SettingsLaneWidthRecord.h"
    "${CMAKE_SOURCE_DIR}/Qt/SettingsWidgets/SettingsLateralProfileCrossfall.h"
    "${CMAKE_SOURCE_DIR}/Qt/ToolsDialogs/GetRoadDialog.h"
    "${CMAKE_SOURCE_DIR}/Qt/ToolsDialogs/ConnectRoadsDialog.h"
    "${CMAKE_SOURCE_DIR}/Qt/ToolsDialogs/LoadingDialog.h"
    "${CMAKE_SOURCE_DIR}/Qt/Tree/RoadTreeItems.h"
    "${CMAKE_SOURCE_DIR}/Qt/Tree/RoadTree.h"
    "${CMAKE_SOURCE_DIR}/Cephes/mconf.h")

set(TARGET_CPP "${CMAKE_SOURCE_DIR}/OpenDrive/OpenDriveXmlWriter.cpp"
    "${CMAKE_SOURCE_DIR}/OpenDrive/OtherStructures.cpp"
    "${CMAKE_SOURCE_DIR}/OpenDrive/OpenDrive.cpp"
    "${CMAKE_SOURCE_DIR}/OpenDrive/Road.cpp"
    "${CMAKE_SOURCE_DIR}/OpenDrive/Junction.cpp"
    "${CMAKE_SOURCE_DIR}/OpenDrive/Lane.cpp"
    "${CMAKE_SOURCE_DIR}/OpenDrive/OpenDriveXmlParser.cpp"
    "${CMAKE_SOURCE_DIR}/OpenDrive/ObjectSignal.cpp"
    "${CMAKE_SOURCE_DIR}/OpenDrive/RoadGeometry.cpp"
    "${CMAKE_SOURCE_DIR}/TinyXML/tinyxml.cpp"
    "${CMAKE_SOURCE_DIR}/TinyXML/tinyxmlparser.cpp"
    "${CMAKE_SOURCE_DIR}/TinyXML/tinystr.cpp"
    "${CMAKE_SOURCE_DIR}/TinyXML/tinyxmlerror.cpp"
    "${CMAKE_SOURCE_DIR}/Osg/OSGObjectNode.cpp"
    "${CMAKE_SOURCE_DIR}/Osg/OSGCameraControls.cpp"
    "${CMAKE_SOURCE_DIR}/Osg/OSGRecordsHelpers.cpp"
    "${CMAKE_SOURCE_DIR}/Osg/OSGRoad.cpp"
    "${CMAKE_SOURCE_DIR}/Osg/OSGScenery.cpp"
    "${CMAKE_SOURCE_DIR}/Osg/OSGCameraControls2.cpp"
    "${CMAKE_SOURCE_DIR}/Osg/OSGJunction.cpp"
    "${CMAKE_SOURCE_DIR}/Osg/OSGMain.cpp"
    "${CMAKE_SOURCE_DIR}/Qt/ConfigDialogs/SceneryDialog.cpp"
    "${CMAKE_SOURCE_DIR}/Qt/ConfigDialogs/ReferencePlaneDialog.cpp"
    "${CMAKE_SOURCE_DIR}/Qt/CreationWidgets/DeleteAll.cpp"
    "${CMAKE_SOURCE_DIR}/Qt/CreationWidgets/CreationAllJunction.cpp"
    "${CMAKE_SOURCE_DIR}/Qt/CreationWidgets/CreationPage.cpp"
    "${CMAKE_SOURCE_DIR}/Qt/CreationWidgets/CreationAllRoad.cpp"
    "${CMAKE_SOURCE_DIR}/Qt/QOSGWidget.cpp"
    "${CMAKE_SOURCE_DIR}/Qt/SettingsWidgets/SettingsRoad.cpp"
    "${CMAKE_SOURCE_DIR}/Qt/SettingsWidgets/SettingsPage.cpp"
    "${CMAKE_SOURCE_DIR}/Qt/SettingsWidgets/SettingsLateralProfileSuper.cpp"
    "${CMAKE_SOURCE_DIR}/Qt/SettingsWidgets/SettingsElevationRecord.cpp"
    "${CMAKE_SOURCE_DIR}/Qt/SettingsWidgets/SettingsJunctionConnection.cpp"
    "${CMAKE_SOURCE_DIR}/Qt/SettingsWidgets/SettingsLaneHeightRecord.cpp"
    "${CMAKE_SOURCE_DIR}/Qt/SettingsWidgets/SettingsLaneAccessRecord.cpp"
    "${CMAKE_SOURCE_DIR}/Qt/SettingsWidgets/SettingsLane.cpp"
    "${CMAKE_SOURCE_DIR}/Qt/SettingsWidgets/SettingsLaneSection.cpp"
    "${CMAKE_SOURCE_DIR}/Qt/SettingsWidgets/SettingsGeometryLine.cpp"
    "${CMAKE_SOURCE_DIR}/Qt/SettingsWidgets/SettingsLaneVisibilityRecord.cpp"
    "${CMAKE_SOURCE_DIR}/Qt/SettingsWidgets/SettingsJunction.cpp"
    "${CMAKE_SOURCE_DIR}/Qt/SettingsWidgets/SettingsLateralProfileCrossfall.cpp"
    "${CMAKE_SOURCE_DIR}/Qt/SettingsWidgets/SettingsLaneWidthRecord.cpp"
    "${CMAKE_SOURCE_DIR}/Qt/SettingsWidgets/SettingsJunctionPriority.cpp"
    "${CMAKE_SOURCE_DIR}/Qt/SettingsWidgets/SettingsLaneMaterialRecord.cpp"
    "${CMAKE_SOURCE_DIR}/Qt/SettingsWidgets/SettingsJunctionLaneLink.cpp"
    "${CMAKE_SOURCE_DIR}/Qt/SettingsWidgets/SettingsLaneRoadMark.cpp"
    "${CMAKE_SOURCE_DIR}/Qt/SettingsWidgets/SettingsGeometryTurn.cpp"
    "${CMAKE_SOURCE_DIR}/Qt/SettingsWidgets/SettingsRoadTypeRecord.cpp"
    "${CMAKE_SOURCE_DIR}/Qt/SettingsWidgets/SettingsLaneSpeedRecord.cpp"
    "${CMAKE_SOURCE_DIR}/Qt/SettingsWidgets/SettingsJunctionController.cpp"
    "${CMAKE_SOURCE_DIR}/Qt/ToolsDialogs/GetRoadDialog.cpp"
    "${CMAKE_SOURCE_DIR}/Qt/ToolsDialogs/ConnectRoadsDialog.cpp"
    "${CMAKE_SOURCE_DIR}/Qt/ToolsDialogs/LoadingDialog.cpp"
    "${CMAKE_SOURCE_DIR}/Qt/MainWindow.cpp"
    "${CMAKE_SOURCE_DIR}/Qt/Tree/RoadTreeItems.cpp"
    "${CMAKE_SOURCE_DIR}/Qt/Tree/RoadTree.cpp"
    "${CMAKE_SOURCE_DIR}/Cephes/const.cpp"
    "${CMAKE_SOURCE_DIR}/Cephes/fresnl.cpp"
    "${CMAKE_SOURCE_DIR}/Cephes/polevl.c")

add_executable(OpenRoadEd main.cpp ${TARGET_H} ${TARGET_CPP})
set_property(TARGET OpenRoadEd PROPERTY CXX_STANDARD 14)
target_compile_definitions(OpenRoadEd PRIVATE NOGDI)
target_link_libraries(OpenRoadEd ${OPENSCENEGRAPH_LIBRARIES} Qt5::Widgets Qt5::Gui Qt5::OpenGL Qt5::Core )

target_include_directories(OpenRoadEd PRIVATE 
osgQt/include
${CMAKE_BINARY_DIR}/osgQt/src/
)
