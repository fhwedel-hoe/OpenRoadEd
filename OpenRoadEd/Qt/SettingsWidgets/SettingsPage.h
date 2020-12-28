#ifndef SETTINGSPAGE_H
#define SETTINGSPAGE_H


#include <QtWidgets>
#include <QtGui/QtGui>

#include "../../OpenDrive/OpenDrive.h"

#include "SettingsRoad.h"
#include "SettingsRoadTypeRecord.h"
#include "SettingsGeometryLine.h"
#include "SettingsGeometryTurn.h"
#include "SettingsElevationRecord.h"
#include "SettingsLateralProfileSuper.h"
#include "SettingsLateralProfileCrossfall.h"
#include "SettingsLaneSection.h"
#include "SettingsLane.h"
#include "SettingsLaneWidthRecord.h"
#include "SettingsLaneRoadMark.h"
#include "SettingsLaneMaterialRecord.h"
#include "SettingsLaneVisibilityRecord.h"
#include "SettingsLaneSpeedRecord.h"
#include "SettingsLaneAccessRecord.h"
#include "SettingsLaneHeightRecord.h"

#include "SettingsJunction.h"
#include "SettingsJunctionConnection.h"
#include "SettingsJunctionLaneLink.h"
#include "SettingsJunctionPriority.h"
#include "SettingsJunctionController.h"
// ADD OBJECT HERE
// ADD SIGNAL HERE
// ADD CONTROLLER HERE
// ADD JUNCTION HERE

/**
 * Class that holds the panels, which contains settings widgets for every record type
 * All settings widgets are added in a vertical layout. When there is a need to display
 * settings for a specific records, all settings widgets are hidden and only the required 
 * widgets is displayed
 */
class SettingsPage : public QWidget
{
	Q_OBJECT
public:
	/**
	 * Initializes the settings panel and all the interface elements
	 */
	SettingsPage(OpenDrive *openDrive);
private:
	/**
	 * Pointer to the OpenDrive structure
	 */
	OpenDrive *mOpenDrive;

	/**
	 * All the settings widgets for all teh record types
	 */
	SettingsRoad *mRoad;
	SettingsRoadTypeRecord *mRoadType;
	SettingsGeometryLine *mGeometryLine;
	SettingsGeometryTurn *mGeometryTurn;
	SettingsElevationRecord *mElevation;
	SettingsLateralProfileSuper *mSuperElevation;
	SettingsLateralProfileCrossfall *mCrossfall;
	SettingsLaneSection *mLaneSection;
	SettingsLane *mLane;
	SettingsLaneWidthRecord *mLaneWidth;
	SettingsLaneRoadMark *mLaneRoadMark;
	SettingsLaneMaterialRecord *mLaneMaterial;
	SettingsLaneVisibilityRecord *mLaneVisibility;
	SettingsLaneSpeedRecord *mLaneSpeed;
	SettingsLaneAccessRecord *mLaneAccess;
	SettingsLaneHeightRecord *mLaneHeight;

	SettingsJunction *mJunction;
	SettingsJunctionConnection *mJunctionConnection;
	SettingsJunctionLaneLink *mJunctionLaneLink;
	SettingsJunctionPriority *mJunctionPriority;
	SettingsJunctionController *mJunctionController;
	// ADD OBJECT HERE
	// ADD SIGNAL HERE
	// ADD CONTROLLER HERE
	// ADD JUNCTION HERE

	/**
	 * Hides all the widgets
	 */
	void HideAll();

public slots:
	/**
	 * Methods called when an item is selected in the road tree
	 * Every method hides every single settings widget, displays
	 * a specific one and load the property data from the supplied record object
	 */
	void OnNothingSelected();
	void OnRoadSelected(Road *node);
	void OnRoadTypeSelected(RoadType *node, double minS, double maxS);
	void OnGeometryLineSelected(GeometryBlock *node, bool first);
	void OnGeometryTurnSelected(GeometryBlock *node, bool first);
	void OnElevationSelected(Elevation *node, double minS, double maxS);
	void OnSuperElevationSelected(SuperElevation *node, double minS, double maxS);
	void OnCrossfallSelected(Crossfall *node, double minS, double maxS);
	void OnLaneSectionSelected(LaneSection *node, double minS, double maxS,bool first);
	void OnLaneSelected(Lane *node);
	void OnLaneWidthSelected(LaneWidth *node, double minS, double maxS);
	void OnLaneRoadMarkSelected(LaneRoadMark *node, double minS, double maxS);
	void OnLaneMaterialSelected(LaneMaterial *node, double minS, double maxS);
	void OnLaneVisibilitySelected(LaneVisibility *node, double minS, double maxS);
	void OnLaneSpeedSelected(LaneSpeed *node, double minS, double maxS);
	void OnLaneAccessSelected(LaneAccess *node, double minS, double maxS);
	void OnLaneHeightSelected(LaneHeight *node, double minS, double maxS);
	void OnObjectSelected(Object *node);
	void OnSignalSelected(Signal *node);

	void OnJunctionSelected(Junction *node);
	void OnJunctionConnectionSelected(JunctionConnection *node);
	void OnJunctionLaneLinkSelected(JunctionLaneLink *node);
	void OnJunctionPrioritySelected(JunctionPriorityRoad *node);
	void OnJunctionControllerSelected(JunctionController *node);

	/**
	 * Methods called when an a critical record property is modified
	 * which requires the road to be redrawn
	 */
	void OnRoadGeometryChanged(bool geometryChanged=false);


signals:
	/**
	 * Signal emitted when the road has to be redrawn
	 */
	void CurrentRoadChanged(bool geometryChanged);
};

#endif
