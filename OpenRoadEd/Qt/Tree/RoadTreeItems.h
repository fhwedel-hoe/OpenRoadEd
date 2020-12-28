#ifndef ROADTREEITEMS_H
#define ROADTREEITEMS_H


#include <QtWidgets>
#include <QtGui/QtGui>

#include "../../OpenDrive/OpenDrive.h"
#include "../../OpenDrive/Road.h"
#include "../../OpenDrive/Lane.h"
#include "../../OpenDrive/RoadGeometry.h"
#include "../../OpenDrive/Junction.h"
#include "../../OpenDrive/OtherStructures.h"

//====== CLASS PROTOTYPES ====//
class RTIRoadContainer;
class RTIJunctionContainer;
class RTIRoadTypeContainer;
class RTIGeometryBlockContainer;
class RTIElevationContainer;
class RTISuperElevationContainer;
class RTICrossfallContainer;
class RTILaneSectionContainer;
class RTILaneContainer;
class RTILaneWidthContainer;
class RTILaneRoadMarkContainer;
class RTILaneMaterialContainer;
class RTILaneVisibilityContainer;
class RTILaneSpeedContainer;
class RTILaneAccessContainer;
class RTILaneHeightContainer;
class RTIObjectContainer;
class RTISignalContainer;

class RTIRoad;
class RTILaneSection;
class RTILane;
class RTIJunction;
class RTIJunctionConnection;

/**
 * Types of items that can be created in the road tree
 * Add here a new one when you want to add support for a new record type
 */
enum RoadTreeItemType 
{
	CONTAINER,
	ROAD_CONTAINER,
	ROAD,
	ROAD_TYPE_CONTAINER,
	ROAD_TYPE,
	GEOMETRY_CONTAINER,
	GEOMETRY_LINE,
	GEOMETRY_TURN,
	ELEVATION_CONTAINER,
	ELEVATION,
	SUPERELEVATION_CONTAINER,
	SUPERELEVATION,
	CROSSFALL_CONTAINER,
	CROSSFALL,
	LANE_SECTION_CONTAINER,
	LANE_SECTION,
	LANE_CONTAINER,
	LANE,
	LANE_WIDTH_CONTAINER,
	LANE_WIDTH,
	LANE_ROAD_MARK_CONTAINER,
	LANE_ROAD_MARK,
	LANE_MATERIAL_CONTAINER,
	LANE_MATERIAL,
	LANE_VISIBILITY_CONTAINER,
	LANE_VISIBILITY,
	LANE_SPEED_CONTAINER,
	LANE_SPEED,
	LANE_ACCESS_CONTAINER,
	LANE_ACCESS,
	LANE_HEIGHT_CONTAINER,
	LANE_HEIGHT,
	OBJECT_CONTAINER,
	OBJECT,
	SIGNAL_CONTAINER,
	SIGNAL,
	CONTROLLER_CONTAINER,
	CONTROLLER,
	JUNCTION_CONTAINER,
	JUNCTION,
	JUNCTION_CONNECTION_CONTAINER,
	JUNCTION_CONNECTION,
	JUNCTION_LANE_LINK_CONTAINER,
	JUNCTION_LANE_LINK,
	JUNCTION_PRIORITY_CONTAINER,
	JUNCTION_PRIORITY,
	JUNCTION_CONTROLLER_CONTAINER,
	JUNCTION_CONTROLLER,
	NONE
};

/**
 * Colors used in the road tree to color code the items
 * By default has colors for all the item types and their containers ordered in the hierarchy depth order
 * Add new record here if you want to add support for a new record type
 */
struct RoadTreeItemConfig
{
public:

	// ROADS GROUP
	// LEVEL 1
	static QBrush RoadContainerColor() {return QBrush(QColor(0x6b94b3));};

	// LEVEL 2
	static QBrush RoadColor() {return QBrush(QColor(0x7ba1b5));};

	// LEVEL 3
	static QBrush RoadTypeContainerColor() {return QBrush(QColor(0x8caeba));};
	static QBrush GeometryContainerColor() {return QBrush(QColor(0x8caeba));};
	static QBrush ElevationContainerColor() {return QBrush(QColor(0x8caeba));};
	static QBrush SuperElevationContainerColor() {return QBrush(QColor(0x8caeba));};
	static QBrush CrossfallContainerColor() {return QBrush(QColor(0x8caeba));};
	static QBrush LaneSectionContainerColor() {return QBrush(QColor(0x8caeba));};
	static QBrush ObjectContainerColor() {return QBrush(QColor(0x8caeba));};
	static QBrush SignalContainerColor() {return QBrush(QColor(0x8caeba));};

	// LEVEL 4
	static QBrush RoadTypeColor() {return QBrush(QColor(0x9dbac0));};
	static QBrush GeometryColor() {return QBrush(QColor(0x9dbac0));};
	static QBrush ElevationColor() {return QBrush(QColor(0x9dbac0));};
	static QBrush SuperElevationColor() {return QBrush(QColor(0x9dbac0));};
	static QBrush CrossfallColor() {return QBrush(QColor(0x9dbac0));};
	static QBrush LaneSectionColor() {return QBrush(QColor(0x9dbac0));};
	static QBrush ObjectColor() {return QBrush(QColor(0x9dbac0));};
	static QBrush SignalColor() {return QBrush(QColor(0x9dbac0));};

	// LEVEL 5
	static QBrush LaneContainerColor() {return QBrush(QColor(0xb0c8c9));};

	// LEVEL 6
	static QBrush LaneColor() {return QBrush(QColor(0xc1d5d3));};

	// LEVEL 7
	static QBrush LaneWidthContainerColor() {return QBrush(QColor(0xd6e3e0));};
	static QBrush LaneRoadMarkContainerColor() {return QBrush(QColor(0xd6e3e0));};
	static QBrush LaneMaterialContainerColor() {return QBrush(QColor(0xd6e3e0));};
	static QBrush LaneVisibilityContainerColor() {return QBrush(QColor(0xd6e3e0));};
	static QBrush LaneSpeedContainerColor() {return QBrush(QColor(0xd6e3e0));};
	static QBrush LaneAccessContainerColor() {return QBrush(QColor(0xd6e3e0));};
	static QBrush LaneHeightContainerColor() {return QBrush(QColor(0xd6e3e0));};

	// LEVEL 8
	static QBrush LaneWidthColor() {return QBrush(QColor(0xe9f0ed));};
	static QBrush LaneRoadMarkColor() {return QBrush(QColor(0xe9f0ed));};
	static QBrush LaneMaterialColor() {return QBrush(QColor(0xe9f0ed));};
	static QBrush LaneVisibilityColor() {return QBrush(QColor(0xe9f0ed));};
	static QBrush LaneSpeedColor() {return QBrush(QColor(0xe9f0ed));};
	static QBrush LaneAccessColor() {return QBrush(QColor(0xe9f0ed));};
	static QBrush LaneHeightColor() {return QBrush(QColor(0xe9f0ed));};


	// JUNCTIONS GROUP
	// LEVEL 1
	static QBrush JunctionContainerColor() {return QBrush(QColor(0xde8140));};

	// LEVEL 2
	static QBrush JunctionColor() {return QBrush(QColor(0xe09051));};

	// LEVEL 3
	static QBrush JunctionConnectionContainerColor() {return QBrush(QColor(0xe29f64));};
	static QBrush JunctionPriorityContainerColor() {return QBrush(QColor(0xe29f64));};
	static QBrush JunctionControllerContainerColor() {return QBrush(QColor(0xe29f64));};

	// LEVEL 4
	static QBrush JunctionConnectionColor() {return QBrush(QColor(0xe5ae77));};
	static QBrush JunctionPriorityColor() {return QBrush(QColor(0xe5ae77));};
	static QBrush JunctionControllerColor() {return QBrush(QColor(0xe5ae77));};

	// LEVEL 5
	static QBrush JunctionLaneLinkContainerColor() {return QBrush(QColor(0xe9bf8f));};

	// LEVEL 6
	static QBrush JunctionLaneLinkColor() {return QBrush(QColor(0xedcda7));};
};

/**
 * Base tree item class, keeps a "type" identifier and color-coding functionality
 * Can be used both for the items as well as item containers
 */
class RoadTreeItemBase : public QTreeWidgetItem
{
public:
	/**
	 * Constructor
	 *
	 * @param parent Parent of the item, can be a tree widget or another tree item
	 * @param type Type of the item (ROAD, JUNCTION, LANE...)
	 * @param text Custom name of the item that could be seen in the road tree
	 */
	RoadTreeItemBase(QTreeWidgetItem *parent, RoadTreeItemType type, const QString &text);
	RoadTreeItemBase(QTreeWidgetItem *parent, RoadTreeItemType type);

	/**
	 * Constructor used to insert the item after an existing item in the tree
	 *
	 * @param parent Parent of the item, can be a tree widget or another tree item
	 * @param previous Existing item after which the new one should be inserted
	 * @param type Type of the item (ROAD, JUNCTION, LANE...)
	 * @param text Custom name of the item that could be seen in the road tree
	 */
	RoadTreeItemBase(QTreeWidgetItem *parent, QTreeWidgetItem *previous, RoadTreeItemType type, const QString &text);
	RoadTreeItemBase(QTreeWidgetItem *parent, QTreeWidgetItem *previous, RoadTreeItemType type);

	/**
	 * Getter for the type
	 *
	 * @return Returns the type of the object it represents
	 */
	RoadTreeItemType GetType();

	/**
	 * Returns the flag that shows if the item is color coded or not
	 */
	bool GetColorCodedFlag();

	/**
	 * Method used to color code the item and it's children
	 *
	 * @param enable Set to true to enable
	 */
	void ColorCode(bool enable);
private:

	/**
	 * Flag that shows if the item is color coded
	 */
	bool mColorCoded;
protected:

	/**
	 * Type of the record this item represents
	 */
	RoadTreeItemType mType;

};


/**
 * Tree item that inherits the base class
 * Used for generic items that can't have children (ELEVATION, CROSSFALL, ...)
 * Adds an index of the record it represents in the OpenDrive structure
 * Adds an index shifting method used to increase or decrease the index when a previous item
 * is added or removed
 * Adds a name setting method that sets the name of the item depending on it's type and index
 */
class RoadTreeItem : public RoadTreeItemBase
{
public:
	/**
	 * Constructor
	 *
	 * @param index Index of the corresponding record in OpenDrive structure
	 * @param parent Parent of the item, can be a tree widget or another tree item
	 * @param type Type of the item (ROAD, JUNCTION, LANE...)
	 * @param text Custom name of the item that could be seen in the road tree
	 */
	RoadTreeItem(int index, QTreeWidgetItem *parent, RoadTreeItemType type, const QString &text);
	RoadTreeItem(int index, QTreeWidgetItem *parent, RoadTreeItemType type);

	/**
	 * Constructor used to insert the item after an existing item in the tree
	 *
	 * @param index Index of the corresponding record in OpenDrive structure
	 * @param parent Parent of the item, can be a tree widget or another tree item
	 * @param previous Existing item after which the new one should be inserted
	 * @param type Type of the item (ROAD, JUNCTION, LANE...)
	 * @param text Custom name of the item that could be seen in the road tree
	 */
	RoadTreeItem(int index, QTreeWidgetItem *parent, QTreeWidgetItem *previous, RoadTreeItemType type, const QString &text);
	RoadTreeItem(int index, QTreeWidgetItem *parent, QTreeWidgetItem *previous, RoadTreeItemType type);
	
	/**
	 * Getter for the item index
	 */
	int GetIndex();

	/**
	 * Shifts the current index or the indices in a container
	 * Used when a previous item is deleted or added
	 *
	 * @param delta Delta value to be added to the index
	 */
	void ShiftIndex(int delta);

	/**
	 * Shifts the indices in a child container
	 * Used when a previous item is deleted or added
	 *
	 * @param container Container where an index shift is required
	 * @param index The index from which the shift should start
	 * @param delta Delta value to be added to the index
	 */
	void ShiftIndexes(QTreeWidgetItem *container, int index, int delta);

	/**
	 * Sets the title of the item depending on it's type and index
	 * Add a record here if you want to add support for new record types
	 */
	void SetTextByType();
private:

	/**
	 * Index of the corresponding item in OpenDrive structure
	 */
	int mIndex;
};


/**
 * ROAD item that inherits the RoadTreeItem class and adds child containers for child items
 * Adds methods used to add child items to the respective containers
 * Adds methods used to get child item containers
 */
class RTIRoad : public RoadTreeItem
{
public:
	/**
	 * Constructor
	 *
	 * @param index Index of the corresponding record in OpenDrive structure
	 * @param parent Parent of the item, can be a tree widget or another tree item
	 * @param type Type of the item (ROAD, JUNCTION, LANE...)
	 * @param text Custom name of the item that could be seen in the road tree
	 */
	RTIRoad(int index, QTreeWidgetItem *parent, RoadTreeItemType type, const QString &text);
	RTIRoad(int index, QTreeWidgetItem *parent, RoadTreeItemType type);

	/**
	 * Constructor used to insert the item after an existing item in the tree
	 *
	 * @param index Index of the corresponding record in OpenDrive structure
	 * @param parent Parent of the item, can be a tree widget or another tree item
	 * @param prev Existing item after which the new one should be inserted
	 * @param type Type of the item (ROAD, JUNCTION, LANE...)
	 * @param text Custom name of the item that could be seen in the road tree
	 */
	RTIRoad(int index, QTreeWidgetItem *parent, QTreeWidgetItem *prev, RoadTreeItemType type, const QString &text);
	RTIRoad(int index, QTreeWidgetItem *parent, QTreeWidgetItem *prev, RoadTreeItemType type);

	/**
	 * Returns the child item containers
	 */
	RoadTreeItemBase *GetRoadTypeContainer();
	RoadTreeItemBase *GetGeometryBlockContainer();
	RoadTreeItemBase *GetElevationContainer();
	RoadTreeItemBase *GetSuperElevationContainer();
	RoadTreeItemBase *GetCrossfallContainer();
	RoadTreeItemBase *GetLaneSectionContainer();
	RoadTreeItemBase *GetObjectContainer();
	RoadTreeItemBase *GetSignalContainer();

	/**
	 * Two methods used to add a new record to the child containers. Second method also returns the created item
	 *
	 * @param indexXXX Index or sequence of indices of the corresponding object in OpenDrive structure
	 * @param YYY Reference to the pointer that will hold the created road tree item
	 */
	void AddRoadType(int index);
	void AddRoadType(int index, RoadTreeItem*& roadType);
	void AddGeometryBlock(int index, int type);
	void AddGeometryBlock(int index, RoadTreeItem*& roadGeometry, int type);
	void AddElevation(int index);
	void AddElevation(int index, RoadTreeItem*& roadElevation);
	void AddSuperElevation(int index);
	void AddSuperElevation(int index, RoadTreeItem*& roadSuperelevation);
	void AddCrossfall(int index);
	void AddCrossfall(int index, RoadTreeItem*& crossfall);
	void AddLaneSection(int index);
	void AddLaneSection(int index, RTILaneSection*& roadLaneSection);
	void AddObject(int index);
	void AddObject(int index, RoadTreeItem*& roadObject);
	void AddSignal(int index);
	void AddSignal(int index, RoadTreeItem*& roadSignal);

private:
	/**
	 * Child item containers
	 */
	RoadTreeItemBase *mRoadTypeContainer;
	RoadTreeItemBase *mGeometryBlockContainer;
	RoadTreeItemBase *mElevationContainer;
	RoadTreeItemBase *mSuperElevationContainer;
	RoadTreeItemBase *mCrossfallContainer;
	RoadTreeItemBase *mLaneSectionContainer;
	RoadTreeItemBase *mObjectContainer;
	RoadTreeItemBase *mSignalContainer;

	/**
	 * Initializes the containers
	 */
	void Init();
};

/**
 * LANE_SECTION item that inherits the RoadTreeItem class and adds child containers for child items
 * Adds methods used to add child items to the respective containers
 * Adds methods used to get child item containers
 */
class RTILaneSection : public RoadTreeItem
{
public:
	/**
	 * Constructor
	 *
	 * @param index Index of the corresponding record in OpenDrive structure
	 * @param parent Parent of the item, can be a tree widget or another tree item
	 * @param type Type of the item (ROAD, JUNCTION, LANE...)
	 * @param text Custom name of the item that could be seen in the road tree
	 */
	RTILaneSection(int index, QTreeWidgetItem *parent, RoadTreeItemType type, const QString &text);
	RTILaneSection(int index, QTreeWidgetItem *parent, RoadTreeItemType type);

	/**
	 * Constructor used to insert the item after an existing item in the tree
	 *
	 * @param index Index of the corresponding record in OpenDrive structure
	 * @param parent Parent of the item, can be a tree widget or another tree item
	 * @param prev Existing item after which the new one should be inserted
	 * @param type Type of the item (ROAD, JUNCTION, LANE...)
	 * @param text Custom name of the item that could be seen in the road tree
	 */
	RTILaneSection(int index, QTreeWidgetItem *parent, QTreeWidgetItem *prev, RoadTreeItemType type, const QString &text);
	RTILaneSection(int index, QTreeWidgetItem *parent, QTreeWidgetItem *prev, RoadTreeItemType type);

	/**
	 * Returns the child item containers
	 */
	RoadTreeItemBase *GetLaneContainerLeft();
	RoadTreeItemBase *GetLaneContainerCenter();
	RoadTreeItemBase *GetLaneContainerRight();

	/**
	 * Two methods used to add a new record to the child containers. Second method also returns the created item
	 *
	 * @param indexXXX Index or sequence of indices of the corresponding object in OpenDrive structure
	 * @param YYY Reference to the pointer that will hold the created road tree item
	 */
	void AddLane(int index, int side);
	void AddLane(int index, RTILane *&lane, int side);
	void AddLaneLeft(int index);
	void AddLaneLeft(int index, RTILane *&lane);
	void AddLaneCenter(int index);
	void AddLaneCenter(int index, RTILane *&lane);
	void AddLaneRight(int index);
	void AddLaneRight(int index, RTILane *&lane);
private:
	/**
	 * Child item containers
	 */
	RoadTreeItemBase *mLaneContainerLeft;
	RoadTreeItemBase *mLaneContainerCenter;
	RoadTreeItemBase *mLaneContainerRight;

	/**
	 * Initializes the containers
	 */
	void Init();
};

/**
 * LANE item that inherits the RoadTreeItem class and adds child containers for child items
 * Adds methods used to add child items to the respective containers
 * Adds methods used to get child item containers
 */
class RTILane : public RoadTreeItem
{
public:
	/**
	 * Constructor
	 *
	 * @param index Index of the corresponding record in OpenDrive structure
	 * @param parent Parent of the item, can be a tree widget or another tree item
	 * @param type Type of the item (ROAD, JUNCTION, LANE...)
	 * @param text Custom name of the item that could be seen in the road tree
	 */
	RTILane(int index, QTreeWidgetItem *parent, RoadTreeItemType type, const QString &text);
	RTILane(int index, QTreeWidgetItem *parent, RoadTreeItemType type);

	/**
	 * Constructor used to insert the item after an existing item in the tree
	 *
	 * @param index Index of the corresponding record in OpenDrive structure
	 * @param parent Parent of the item, can be a tree widget or another tree item
	 * @param prev Existing item after which the new one should be inserted
	 * @param type Type of the item (ROAD, JUNCTION, LANE...)
	 * @param text Custom name of the item that could be seen in the road tree
	 */
	RTILane(int index, QTreeWidgetItem *parent, QTreeWidgetItem *prev, RoadTreeItemType type, const QString &text);
	RTILane(int index, QTreeWidgetItem *parent, QTreeWidgetItem *prev, RoadTreeItemType type);

	/**
	 * Returns the child item containers
	 */
	RoadTreeItemBase *GetLaneWidthContainer();
	RoadTreeItemBase *GetLaneRoadMarkContainer();
	RoadTreeItemBase *GetLaneMaterialContainer();
	RoadTreeItemBase *GetLaneVisibilityContainer();
	RoadTreeItemBase *GetLaneSpeedContainer();
	RoadTreeItemBase *GetLaneAccessContainer();
	RoadTreeItemBase *GetLaneHeightContainer();

	/**
	 * Two methods used to add a new record to the child containers. Second method also returns the created item
	 *
	 * @param indexXXX Index or sequence of indices of the corresponding object in OpenDrive structure
	 * @param YYY Reference to the pointer that will hold the created road tree item
	 */
	void AddLaneWidth(int index);
	void AddLaneWidth(int index, RoadTreeItem *&laneWidth);
	void AddLaneRoadMark(int index);
	void AddLaneRoadMark(int index, RoadTreeItem *&laneRoadMark);
	void AddLaneMaterial(int index);
	void AddLaneMaterial(int index, RoadTreeItem *&laneMaterial);
	void AddLaneVisibility(int index);
	void AddLaneVisibility(int index, RoadTreeItem *&laneVisibility);
	void AddLaneSpeed(int index);
	void AddLaneSpeed(int index, RoadTreeItem *&laneSpeed);
	void AddLaneAccess(int index);
	void AddLaneAccess(int index, RoadTreeItem *&laneAccess);
	void AddLaneHeight(int index);
	void AddLaneHeight(int index, RoadTreeItem *&laneHeight);
private:
	/**
	 * Child item containers
	 */
	RoadTreeItemBase *mLaneWidthContainer;
	RoadTreeItemBase *mLaneRoadMarkContainer;
	RoadTreeItemBase *mLaneMaterialContainer;
	RoadTreeItemBase *mLaneVisibilityContainer;
	RoadTreeItemBase *mLaneSpeedContainer;
	RoadTreeItemBase *mLaneAccessContainer;
	RoadTreeItemBase *mLaneHeightContainer;

	/**
	 * Initializes the containers
	 */
	void Init();
};

/**
 * JUNCTION item that inherits the RoadTreeItem class and adds child containers for child items
 * Adds methods used to add child items to the respective containers
 * Adds methods used to get child item containers
 */
class RTIJunction : public RoadTreeItem
{
public:
	/**
	 * Constructor
	 *
	 * @param index Index of the corresponding record in OpenDrive structure
	 * @param parent Parent of the item, can be a tree widget or another tree item
	 * @param type Type of the item (ROAD, JUNCTION, LANE...)
	 * @param text Custom name of the item that could be seen in the road tree
	 */
	RTIJunction(int index, QTreeWidgetItem *parent, RoadTreeItemType type, const QString &text);
	RTIJunction(int index, QTreeWidgetItem *parent, RoadTreeItemType type);

	/**
	 * Constructor used to insert the item after an existing item in the tree
	 *
	 * @param index Index of the corresponding record in OpenDrive structure
	 * @param parent Parent of the item, can be a tree widget or another tree item
	 * @param prev Existing item after which the new one should be inserted
	 * @param type Type of the item (ROAD, JUNCTION, LANE...)
	 * @param text Custom name of the item that could be seen in the road tree
	 */
	RTIJunction(int index, QTreeWidgetItem *parent, QTreeWidgetItem *prev, RoadTreeItemType type, const QString &text);
	RTIJunction(int index, QTreeWidgetItem *parent, QTreeWidgetItem *prev, RoadTreeItemType type);

	/**
	 * Returns the child item containers
	 */
	RoadTreeItemBase *GetConnectionContainer();
	RoadTreeItemBase *GetPriorityContainer();
	RoadTreeItemBase *GetControllerContainer();

	/**
	 * Two methods used to add a new record to the child containers. Second method also returns the created item
	 *
	 * @param indexXXX Index or sequence of indices of the corresponding object in OpenDrive structure
	 * @param YYY Reference to the pointer that will hold the created road tree item
	 */
	void AddConnection(int index);
	void AddConnection(int index, RTIJunctionConnection *&connection);
	void AddPriority(int index);
	void AddPriority(int index, RoadTreeItem *&priority);
	void AddController(int index);
	void AddController(int index, RoadTreeItem *&controller);
private:
	/**
	 * Child item containers
	 */
	RoadTreeItemBase *mConnectionContainer;
	RoadTreeItemBase *mPriorityContainer;
	RoadTreeItemBase *mControllerContainer;

	/**
	 * Initializes the containers
	 */
	void Init();
};

/**
 * JUNCTION_CONNECTION item that inherits the RoadTreeItem class and adds child containers for child items
 * Adds methods used to add child items to the respective containers
 * Adds methods used to get child item containers
 */
class RTIJunctionConnection : public RoadTreeItem
{
public:
	/**
	 * Constructor
	 *
	 * @param index Index of the corresponding record in OpenDrive structure
	 * @param parent Parent of the item, can be a tree widget or another tree item
	 * @param type Type of the item (ROAD, JUNCTION, LANE...)
	 * @param text Custom name of the item that could be seen in the road tree
	 */
	RTIJunctionConnection(int index, QTreeWidgetItem *parent, RoadTreeItemType type, const QString &text);
	RTIJunctionConnection(int index, QTreeWidgetItem *parent, RoadTreeItemType type);

	/**
	 * Constructor used to insert the item after an existing item in the tree
	 *
	 * @param index Index of the corresponding record in OpenDrive structure
	 * @param parent Parent of the item, can be a tree widget or another tree item
	 * @param prev Existing item after which the new one should be inserted
	 * @param type Type of the item (ROAD, JUNCTION, LANE...)
	 * @param text Custom name of the item that could be seen in the road tree
	 */
	RTIJunctionConnection(int index, QTreeWidgetItem *parent, QTreeWidgetItem *prev, RoadTreeItemType type, const QString &text);
	RTIJunctionConnection(int index, QTreeWidgetItem *parent, QTreeWidgetItem *prev, RoadTreeItemType type);


	/**
	 * Returns the child item containers
	 */
	RoadTreeItemBase *GetLaneLinkContainer();

	/**
	 * Two methods used to add a new record to the child containers. Second method also returns the created item
	 *
	 * @param indexXXX Index or sequence of indices of the corresponding object in OpenDrive structure
	 * @param YYY Reference to the pointer that will hold the created road tree item
	 */
	void AddLaneLink(int index);
	void AddLaneLink(int index, RoadTreeItem *&laneLink);
private:
	/**
	 * Child item containers
	 */
	RoadTreeItemBase *mLaneLinkContainer;

	/**
	 * Initializes the containers
	 */
	void Init();
};

#endif
