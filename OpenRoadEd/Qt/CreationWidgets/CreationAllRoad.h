#ifndef CREATIONALLROAD_H
#define CREATIONALLROAD_H


#include <QtGui/QWidget>
#include <QtGui/QtGui>

#include "../../OpenDrive/OpenDrive.h"
#include "../../OpenDrive/RoadGeometry.h"
#include "../Tree/RoadTree.h"
#include "../../Osg/OsgMain.h"

/**
 * Class that holds all the buttons used to create road related records
 *
 */
class CreationAllRoad : public QWidget
{
	Q_OBJECT
public:
	/**
	 * Initializes the creation panel
	 */
	CreationAllRoad(QWidget *parent = 0);

	/**
	 * Saves the references to the OpenDrive, road tree and OSG object
	 */
	void Init(OpenDrive *openDrive, RoadTree *roadTree, OSGMain *osgMain);

	/**
	 * Enables or disables groups of buttons when they cannot be used
	 * due to an unrelated item selected in the road tree
	 * 
	 * @param wholeGroup Disable the whole group or just a part
	 * @param roadItems Disable road item buttons
	 * @param laneGroup Disable lane group
	 * @param laneItems Disable lane item buttons
	 */
	void SetEnabled(bool wholeGroup, bool roadItems=false, bool laneGroup=false, bool laneItems=false);
private:
	/**
	 * Pointers to the openDrive, road tree and OSG objects
	 */
	OpenDrive *mOpenDrive;
	RoadTree *mRoadTree;
	OSGMain *mOsgMain;

	/**
	 * Interface widgets
	 */
	QGroupBox *mRoadCreation;
	QPushButton *mCreateRoad;

	QToolButton *mCreateRoadType;
	QToolButton *mCreateGeometryLine;
	QToolButton *mCreateGeometryTurn;
	QToolButton *mCreateElevation;
	QToolButton *mCreateSuperElevation;
	QToolButton *mCreateCrossfall;
	QToolButton *mCreateLaneSection;
	QToolButton *mCreateObject;
	QToolButton *mCreateSignal;

	QGroupBox *mLaneCreation;
	QPushButton *mCreateLaneLeft;
	QPushButton *mCreateLaneRight;

	QToolButton *mCreateLaneWidth;
	QToolButton *mCreateLaneRoadMark;
	QToolButton *mCreateLaneMaterial;
	QToolButton *mCreateLaneVisibility;
	QToolButton *mCreateLaneSpeed;
	QToolButton *mCreateLaneAccess;
	QToolButton *mCreateLaneHeight;

public slots:
	/**
	 * Methods called when one of the creation buttons is pressed
	 */
	void CreateRoadPressed();
	void CreateRoadTypePressed();
	void CreateGeometryLinePressed();
	void CreateGeometryTurnPressed();
	void CreateElevationPressed();
	void CreateSuperElevationPressed();
	void CreateCrossfallPressed();
	void CreateLaneSectionPressed();
	void CreateObjectPressed();
	void CreateSignalPressed();

	void CreateLaneLeftPressed();
	void CreateLaneRightPressed();
	void CreateLaneWidthPressed();
	void CreateLaneRoadMarkPressed();
	void CreateLaneMaterialPressed();
	void CreateLaneVisibilityPressed();
	void CreateLaneSpeedPressed();
	void CreateLaneAccessPressed();
	void CreateLaneHeightPressed();
signals:
	/**
	 * Signal emitted when critical road items are created
	 * that require that the road to be redrawn
	 */
	void RoadChanged(bool recalculateRoad);
};

#endif