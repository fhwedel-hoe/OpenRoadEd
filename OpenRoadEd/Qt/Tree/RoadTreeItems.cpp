#include "RoadTreeItems.h"

/**
 * Constructor
 *
 * @param parent Parent of the item, can be a tree widget or another tree item
 * @param type Type of the item (ROAD, JUNCTION, LANE...)
 * @param text Custom name of the item that could be seen in the road tree
 */
RoadTreeItemBase::RoadTreeItemBase(QTreeWidgetItem *parent, RoadTreeItemType type, const QString &text):QTreeWidgetItem(parent, QTreeWidgetItem::UserType+1)
{
	mType=type;
	setText(0,text);
	if(parent!=NULL) ColorCode(static_cast<RoadTreeItemBase*>(parent)->GetColorCodedFlag());
	else ColorCode(true);
}
RoadTreeItemBase::RoadTreeItemBase(QTreeWidgetItem *parent, RoadTreeItemType type):QTreeWidgetItem(parent, QTreeWidgetItem::UserType+1)
{
	mType=type;
	if(parent!=NULL) ColorCode(static_cast<RoadTreeItemBase*>(parent)->GetColorCodedFlag());
	else ColorCode(true);
}

/**
 * Constructor used to insert the item after an existing item in the tree
 *
 * @param parent Parent of the item, can be a tree widget or another tree item
 * @param previous Existing item after which the new one should be inserted
 * @param type Type of the item (ROAD, JUNCTION, LANE...)
 * @param text Custom name of the item that could be seen in the road tree
 */
RoadTreeItemBase::RoadTreeItemBase(QTreeWidgetItem *parent, QTreeWidgetItem *previous, RoadTreeItemType type, const QString &text):QTreeWidgetItem(parent, previous, QTreeWidgetItem::UserType+1)
{
	mType=type;
	setText(0,text);
	if(parent!=NULL) ColorCode(static_cast<RoadTreeItemBase*>(parent)->GetColorCodedFlag());
	else ColorCode(true);
}
RoadTreeItemBase::RoadTreeItemBase(QTreeWidgetItem *parent, QTreeWidgetItem *previous, RoadTreeItemType type):QTreeWidgetItem(parent, previous, QTreeWidgetItem::UserType+1)
{
	mType=type;
	if(parent!=NULL) ColorCode(static_cast<RoadTreeItemBase*>(parent)->GetColorCodedFlag());
	else ColorCode(true);
}

/**
 * Getter for the type
 *
 * @return Returns the type of the object it represents
 */
RoadTreeItemType RoadTreeItemBase::GetType()
{
	return mType;
}

/**
 * Returns the flag that shows if the item is color coded or not
 */
bool RoadTreeItemBase::GetColorCodedFlag()
{
	return mColorCoded;
}

/**
 * Method used to color code the item and it's children
 *
 * @param enable Set to true to enable
 */
void RoadTreeItemBase::ColorCode(bool enable)
{
	mColorCoded=enable;
	if(enable)
	{
		switch(mType)
		{
		// ITEMS
		case ROAD:
			setBackground(0,RoadTreeItemConfig::RoadColor());
			setIcon(0,QIcon("Resources/Icons/Road.png"));
			break;
		case ROAD_TYPE:
			setBackground(0,RoadTreeItemConfig::RoadTypeColor());
			setIcon(0,QIcon("Resources/Icons/RoadType.png"));
			break;
		case GEOMETRY_LINE:
			setBackground(0,RoadTreeItemConfig::GeometryColor());
			setIcon(0,QIcon("Resources/Icons/Line.png"));
			break;
		case GEOMETRY_TURN:
			setBackground(0,RoadTreeItemConfig::GeometryColor());
			setIcon(0,QIcon("Resources/Icons/Turn.png"));
			break;
		case ELEVATION:
			setBackground(0,RoadTreeItemConfig::ElevationColor());
			setIcon(0,QIcon("Resources/Icons/Elevation.png"));
			break;
		case SUPERELEVATION:
			setBackground(0,RoadTreeItemConfig::SuperElevationColor());
			setIcon(0,QIcon("Resources/Icons/SuperElevation.png"));
			break;
		case CROSSFALL:
			setBackground(0,RoadTreeItemConfig::CrossfallColor());
			setIcon(0,QIcon("Resources/Icons/Crossfall.png"));
			break;
		case LANE_SECTION:
			setBackground(0,RoadTreeItemConfig::LaneSectionColor());
			setIcon(0,QIcon("Resources/Icons/LaneSection.png"));
			break;
		case LANE:
			setBackground(0,RoadTreeItemConfig::LaneColor());
			setIcon(0,QIcon("Resources/Icons/Lane.png"));
			break;
		case LANE_WIDTH:
			setBackground(0,RoadTreeItemConfig::LaneWidthColor());
			setIcon(0,QIcon("Resources/Icons/LaneWidth.png"));
			break;
		case LANE_ROAD_MARK:
			setBackground(0,RoadTreeItemConfig::LaneRoadMarkColor());
			setIcon(0,QIcon("Resources/Icons/LaneRoadMark.png"));
			break;
		case LANE_MATERIAL:
			setBackground(0,RoadTreeItemConfig::LaneMaterialColor());
			setIcon(0,QIcon("Resources/Icons/LaneMaterial.png"));
			break;
		case LANE_VISIBILITY:
			setBackground(0,RoadTreeItemConfig::LaneVisibilityColor());
			setIcon(0,QIcon("Resources/Icons/LaneVisibility.png"));
			break;
		case LANE_SPEED:
			setBackground(0,RoadTreeItemConfig::LaneSpeedColor());
			setIcon(0,QIcon("Resources/Icons/LaneSpeed.png"));
			break;
		case LANE_ACCESS:
			setBackground(0,RoadTreeItemConfig::LaneAccessColor());
			setIcon(0,QIcon("Resources/Icons/LaneAccess.png"));
			break;
		case LANE_HEIGHT:
			setBackground(0,RoadTreeItemConfig::LaneHeightColor());
			setIcon(0,QIcon("Resources/Icons/LaneHeight.png"));
			break;
		case OBJECT:
			setBackground(0,RoadTreeItemConfig::ObjectColor());
			setIcon(0,QIcon("Resources/Icons/Object.png"));
			break;
		case SIGNAL:
			setBackground(0,RoadTreeItemConfig::SignalColor());
			setIcon(0,QIcon("Resources/Icons/Signal.png"));
			break;
		case CONTROLLER:
			break;
		case JUNCTION:
			setBackground(0,RoadTreeItemConfig::JunctionColor());
			setIcon(0,QIcon("Resources/Icons/Junction.png"));
			break;
		case JUNCTION_CONNECTION:
			setBackground(0,RoadTreeItemConfig::JunctionConnectionColor());
			setIcon(0,QIcon("Resources/Icons/JunctionConnection.png"));
			break;
		case JUNCTION_LANE_LINK:
			setBackground(0,RoadTreeItemConfig::JunctionLaneLinkColor());
			setIcon(0,QIcon("Resources/Icons/JunctionLaneLink.png"));
			break;
		case JUNCTION_PRIORITY:
			setBackground(0,RoadTreeItemConfig::JunctionPriorityColor());
			setIcon(0,QIcon("Resources/Icons/JunctionPriority.png"));
			break;
		case JUNCTION_CONTROLLER:
			setBackground(0,RoadTreeItemConfig::JunctionControllerColor());
			setIcon(0,QIcon("Resources/Icons/JunctionController.png"));
			break;

		// CONTAINERS
		case ROAD_CONTAINER:
			setBackground(0,RoadTreeItemConfig::RoadContainerColor());
			//setIcon(0,QIcon("Resources/Icons/Folder.png"));
			break;
		case ROAD_TYPE_CONTAINER:
			setBackground(0,RoadTreeItemConfig::RoadTypeContainerColor());
			//setIcon(0,QIcon("Resources/Icons/Folder.png"));
			break;
		case GEOMETRY_CONTAINER:
			setBackground(0,RoadTreeItemConfig::GeometryContainerColor());
			//setIcon(0,QIcon("Resources/Icons/Folder.png"));
			break;
		case ELEVATION_CONTAINER:
			setBackground(0,RoadTreeItemConfig::ElevationContainerColor());
			//setIcon(0,QIcon("Resources/Icons/Folder.png"));
			break;
		case SUPERELEVATION_CONTAINER:
			setBackground(0,RoadTreeItemConfig::SuperElevationContainerColor());
			//setIcon(0,QIcon("Resources/Icons/Folder.png"));
			break;
		case CROSSFALL_CONTAINER:
			setBackground(0,RoadTreeItemConfig::CrossfallContainerColor());
			//setIcon(0,QIcon("Resources/Icons/Folder.png"));
			break;
		case LANE_SECTION_CONTAINER:
			setBackground(0,RoadTreeItemConfig::LaneSectionContainerColor());
			//setIcon(0,QIcon("Resources/Icons/Folder.png"));
			break;
		case LANE_CONTAINER:
			setBackground(0,RoadTreeItemConfig::LaneContainerColor());
			//setIcon(0,QIcon("Resources/Icons/Folder.png"));
			break;
		case LANE_WIDTH_CONTAINER:
			setBackground(0,RoadTreeItemConfig::LaneWidthContainerColor());
			//setIcon(0,QIcon("Resources/Icons/Folder.png"));
			break;
		case LANE_ROAD_MARK_CONTAINER:
			setBackground(0,RoadTreeItemConfig::LaneRoadMarkContainerColor());
			//setIcon(0,QIcon("Resources/Icons/Folder.png"));
			break;
		case LANE_MATERIAL_CONTAINER:
			setBackground(0,RoadTreeItemConfig::LaneMaterialContainerColor());
			//setIcon(0,QIcon("Resources/Icons/Folder.png"));
			break;
		case LANE_VISIBILITY_CONTAINER:
			setBackground(0,RoadTreeItemConfig::LaneVisibilityContainerColor());
			//setIcon(0,QIcon("Resources/Icons/Folder.png"));
			break;
		case LANE_SPEED_CONTAINER:
			setBackground(0,RoadTreeItemConfig::LaneSpeedContainerColor());
			//setIcon(0,QIcon("Resources/Icons/Folder.png"));
			break;
		case LANE_ACCESS_CONTAINER:
			setBackground(0,RoadTreeItemConfig::LaneAccessContainerColor());
			//setIcon(0,QIcon("Resources/Icons/Folder.png"));
			break;
		case LANE_HEIGHT_CONTAINER:
			setBackground(0,RoadTreeItemConfig::LaneHeightContainerColor());
			//setIcon(0,QIcon("Resources/Icons/Folder.png"));
			break;
		case OBJECT_CONTAINER:
			setBackground(0,RoadTreeItemConfig::ObjectContainerColor());
			//setIcon(0,QIcon("Resources/Icons/Folder.png"));
			break;
		case SIGNAL_CONTAINER:
			setBackground(0,RoadTreeItemConfig::SignalContainerColor());
			//setIcon(0,QIcon("Resources/Icons/Folder.png"));
			break;
		case CONTROLLER_CONTAINER:
			break;
		case JUNCTION_CONTAINER:
			setBackground(0,RoadTreeItemConfig::JunctionContainerColor());
			//setIcon(0,QIcon("Resources/Icons/Folder.png"));
			break;
		case JUNCTION_CONNECTION_CONTAINER:
			setBackground(0,RoadTreeItemConfig::JunctionConnectionContainerColor());
			//setIcon(0,QIcon("Resources/Icons/Folder.png"));
			break;
		case JUNCTION_LANE_LINK_CONTAINER:
			setBackground(0,RoadTreeItemConfig::JunctionLaneLinkContainerColor());
			//setIcon(0,QIcon("Resources/Icons/Folder.png"));
			break;
		case JUNCTION_PRIORITY_CONTAINER:
			setBackground(0,RoadTreeItemConfig::JunctionPriorityContainerColor());
			//setIcon(0,QIcon("Resources/Icons/Folder.png"));
			break;
		case JUNCTION_CONTROLLER_CONTAINER:
			setBackground(0,RoadTreeItemConfig::JunctionControllerContainerColor());
			//setIcon(0,QIcon("Resources/Icons/Folder.png"));
			break;
		}
	}
	else
	{
		setBackground(0,QBrush());
	}

	// Color code the children
	int count=childCount();
	for(int i=0; i<count; i++)
	{
		static_cast<RoadTreeItemBase*>(child(i))->ColorCode(enable);
	}
}
//===================================================================================================

/**
 * Constructor
 *
 * @param index Index of the corresponding record in OpenDrive structure
 * @param parent Parent of the item, can be a tree widget or another tree item
 * @param type Type of the item (ROAD, JUNCTION, LANE...)
 * @param text Custom name of the item that could be seen in the road tree
 */
RoadTreeItem::RoadTreeItem(int index, QTreeWidgetItem *parent, RoadTreeItemType type, const QString &text) : RoadTreeItemBase(parent,type,text)
{
	mIndex=index;
	SetTextByType();
}
RoadTreeItem::RoadTreeItem(int index, QTreeWidgetItem *parent, RoadTreeItemType type):RoadTreeItemBase(parent,type)
{
	mIndex=index;
	SetTextByType();
}

/**
 * Constructor used to insert the item after an existing item in the tree
 *
 * @param index Index of the corresponding record in OpenDrive structure
 * @param parent Parent of the item, can be a tree widget or another tree item
 * @param previous Existing item after which the new one should be inserted
 * @param type Type of the item (ROAD, JUNCTION, LANE...)
 * @param text Custom name of the item that could be seen in the road tree
 */
RoadTreeItem::RoadTreeItem(int index, QTreeWidgetItem *parent, QTreeWidgetItem *previous, RoadTreeItemType type, const QString &text) : RoadTreeItemBase(parent,previous,type,text)
{
	mIndex=index;
	SetTextByType();
}
RoadTreeItem::RoadTreeItem(int index, QTreeWidgetItem *parent, QTreeWidgetItem *previous, RoadTreeItemType type):RoadTreeItemBase(parent,previous,type)
{
	mIndex=index;
	SetTextByType();
}

/**
 * Getter for the item index
 */
int RoadTreeItem::GetIndex()
{
	return mIndex;
}

/**
 * Shifts the current index or the indices in a container
 * Used when a previous item is deleted or added
 *
 * @param delta Delta value to be added to the index
 */
void RoadTreeItem::ShiftIndex(int delta)
{
	mIndex+=delta;
}

/**
 * Shifts the indices in a child container
 * Used when a previous item is deleted or added
 *
 * @param container Container where an index shift is required
 * @param index The index from which the shift should start
 * @param delta Delta value to be added to the index
 */
void RoadTreeItem::ShiftIndexes(QTreeWidgetItem *container, int index, int delta)
{
	int size=container->childCount();
	if(index<size)
	{
		for(int i=index+1; i<size; i++)
		{
			RoadTreeItem *lItem = static_cast<RoadTreeItem*>(container->child(i));
			lItem->ShiftIndex(delta);
			lItem->SetTextByType();
		}
	}
}

/**
 * Sets the title of the item depending on it's type and index
 * Add a record here if you want to add support for new record types
 */
void RoadTreeItem::SetTextByType()
{
	switch(mType)
	{
	case ROAD:
		setText(0,QString("Road %1").arg(mIndex));
		break;
	case ROAD_TYPE:
		setText(0,QString("Road type %1").arg(mIndex));
		break;
	case GEOMETRY_LINE:
		setText(0,QString("Geometry %1: Line").arg(mIndex));
		break;
	case GEOMETRY_TURN:
		setText(0,QString("Geometry %1: Turn").arg(mIndex));
		break;
	case ELEVATION:
		setText(0,QString("Elevation %1").arg(mIndex));
		break;
	case SUPERELEVATION:
		setText(0,QString("Superelevation %1").arg(mIndex));
		break;
	case CROSSFALL:
		setText(0,QString("Crossfall %1").arg(mIndex));
		break;
	case LANE_SECTION:
		setText(0,QString("Lane section %1").arg(mIndex));
		break;
	case LANE:
		setText(0,QString("Lane %1").arg(mIndex));
		break;
	case LANE_WIDTH:
		setText(0,QString("Lane width %1").arg(mIndex));
		break;
	case LANE_ROAD_MARK:
		setText(0,QString("Lane road mark %1").arg(mIndex));
		break;
	case LANE_MATERIAL:
		setText(0,QString("Lane material %1").arg(mIndex));
		break;
	case LANE_VISIBILITY:
		setText(0,QString("Lane visibility %1").arg(mIndex));
		break;
	case LANE_SPEED:
		setText(0,QString("Lane speed %1").arg(mIndex));
		break;
	case LANE_ACCESS:
		setText(0,QString("Lane access %1").arg(mIndex));
		break;
	case LANE_HEIGHT:
		setText(0,QString("Lane height %1").arg(mIndex));
		break;
	case OBJECT:
		setText(0,QString("Object %1").arg(mIndex));
		break;
	case SIGNAL:
		setText(0,QString("Signal %1").arg(mIndex));
		break;
	case CONTROLLER:
		setText(0,QString("Controller %1").arg(mIndex));
		break;
	case JUNCTION:
		setText(0,QString("Junction %1").arg(mIndex));
		break;
	case JUNCTION_CONNECTION:
		setText(0,QString("Connection %1").arg(mIndex));
		break;
	case JUNCTION_LANE_LINK:
		setText(0,QString("Lane link %1").arg(mIndex));
		break;
	case JUNCTION_PRIORITY:
		setText(0,QString("Priority %1").arg(mIndex));
		break;
	case JUNCTION_CONTROLLER:
		setText(0,QString("Controller %1").arg(mIndex));
		break;
	}
}
//===================================================================================================

/**
 * Constructor
 *
 * @param index Index of the corresponding record in OpenDrive structure
 * @param parent Parent of the item, can be a tree widget or another tree item
 * @param type Type of the item (ROAD, JUNCTION, LANE...)
 * @param text Custom name of the item that could be seen in the road tree
 */
RTIRoad::RTIRoad(int index, QTreeWidgetItem *parent, RoadTreeItemType type, const QString &text):RoadTreeItem(index,parent,type,text)
{
	Init();
}
RTIRoad::RTIRoad(int index, QTreeWidgetItem *parent, RoadTreeItemType type):RoadTreeItem(index,parent,type)
{
	Init();
}

/**
 * Constructor used to insert the item after an existing item in the tree
 *
 * @param index Index of the corresponding record in OpenDrive structure
 * @param parent Parent of the item, can be a tree widget or another tree item
 * @param prev Existing item after which the new one should be inserted
 * @param type Type of the item (ROAD, JUNCTION, LANE...)
 * @param text Custom name of the item that could be seen in the road tree
 */
RTIRoad::RTIRoad(int index, QTreeWidgetItem *parent, QTreeWidgetItem *prev, RoadTreeItemType type, const QString &text):RoadTreeItem(index,parent,prev,type,text)
{
	Init();
}
RTIRoad::RTIRoad(int index, QTreeWidgetItem *parent, QTreeWidgetItem *prev, RoadTreeItemType type):RoadTreeItem(index,parent,prev,type)
{
	Init();
}

/**
 * Initializes the containers
 */
void RTIRoad::Init()
{
	mRoadTypeContainer = new RoadTreeItemBase(this, ROAD_TYPE_CONTAINER, "Road type");
	mGeometryBlockContainer = new RoadTreeItemBase(this, GEOMETRY_CONTAINER, "Road geometry");
	mElevationContainer = new RoadTreeItemBase(this, ELEVATION_CONTAINER, "Road elevation");

	mSuperElevationContainer = new RoadTreeItemBase(this, SUPERELEVATION_CONTAINER, "Road superelevation");
	mCrossfallContainer = new RoadTreeItemBase(this, CROSSFALL_CONTAINER, "Road crossfall");

	mLaneSectionContainer = new RoadTreeItemBase(this, LANE_SECTION_CONTAINER, "Road lane sections");
	mObjectContainer = new RoadTreeItemBase(this, OBJECT_CONTAINER, "Road objects");
	mSignalContainer = new RoadTreeItemBase(this, SIGNAL_CONTAINER, "Road signals");
}


/**
 * Returns the child item containers
 */
RoadTreeItemBase *RTIRoad::GetRoadTypeContainer()
{
	return mRoadTypeContainer;
}
RoadTreeItemBase *RTIRoad::GetGeometryBlockContainer()
{
	return mGeometryBlockContainer;
}
RoadTreeItemBase *RTIRoad::GetElevationContainer()
{
	return mElevationContainer;
}
RoadTreeItemBase *RTIRoad::GetSuperElevationContainer()
{
	return mSuperElevationContainer;
}
RoadTreeItemBase *RTIRoad::GetCrossfallContainer()
{
	return mCrossfallContainer;
}
RoadTreeItemBase *RTIRoad::GetLaneSectionContainer()
{
	return mLaneSectionContainer;
}
RoadTreeItemBase *RTIRoad::GetObjectContainer()
{
	return mObjectContainer;
}
RoadTreeItemBase *RTIRoad::GetSignalContainer()
{
	return mSignalContainer;
}


/**
 * Two methods used to add a new record to the child containers. Second method also returns the created item
 *
 * @param indexXXX Index or sequence of indices of the corresponding object in OpenDrive structure
 * @param YYY Reference to the pointer that will hold the created road tree item
 */
void RTIRoad::AddRoadType(int index)
{
	RoadTreeItem *lRoadType = NULL;
	AddRoadType(index, lRoadType);
}
void RTIRoad::AddRoadType(int index, RoadTreeItem *&roadType)
{
	if(index>=mRoadTypeContainer->childCount())
	{
		roadType = new RoadTreeItem(index, mRoadTypeContainer, ROAD_TYPE);	
	}
	else
	{
		QTreeWidgetItem *prev = NULL;
		if(index>0)	prev = mRoadTypeContainer->child(index-1);
		roadType = new RoadTreeItem(index, mRoadTypeContainer, prev, ROAD_TYPE);
		ShiftIndexes(mRoadTypeContainer, index, 1);
	}
}
void RTIRoad::AddGeometryBlock(int index, int type)
{
	RoadTreeItem *lRoadGeometry = NULL;
	AddGeometryBlock(index, lRoadGeometry, type);
}
void RTIRoad::AddGeometryBlock(int index, RoadTreeItem *&roadGeometry, int type)
{
	RoadTreeItemType lGType;
	if(type) lGType=GEOMETRY_LINE;
	else lGType=GEOMETRY_TURN;
	
	if(index>=mGeometryBlockContainer->childCount())
	{
		roadGeometry = new RoadTreeItem(index, mGeometryBlockContainer, lGType);	
	}
	else
	{
		QTreeWidgetItem *prev = NULL;
		if(index>0)	prev = mGeometryBlockContainer->child(index-1);
		roadGeometry = new RoadTreeItem(index, mGeometryBlockContainer, prev, lGType);
		ShiftIndexes(mGeometryBlockContainer, index, 1);
	}
}
void RTIRoad::AddElevation(int index)
{
	RoadTreeItem *lRoadElevation = NULL;
	AddElevation(index, lRoadElevation);
}
void RTIRoad::AddElevation(int index, RoadTreeItem *&roadElevation)
{
	if(index>=mElevationContainer->childCount())
	{
		roadElevation = new RoadTreeItem(index, mElevationContainer, ELEVATION);
	}
	else
	{
		QTreeWidgetItem *prev = NULL;
		if(index>0)	prev = mElevationContainer->child(index-1);
		roadElevation = new RoadTreeItem(index, mElevationContainer, prev, ELEVATION);
		ShiftIndexes(mElevationContainer, index, 1);
	}
}
void RTIRoad::AddSuperElevation(int index)
{
	RoadTreeItem *lRoadSuperelevation = NULL;
	AddSuperElevation(index, lRoadSuperelevation);
}
void RTIRoad::AddSuperElevation(int index, RoadTreeItem *&roadSuperelevation)
{
	if(index>=mSuperElevationContainer->childCount())
	{
		roadSuperelevation = new RoadTreeItem(index, mSuperElevationContainer, SUPERELEVATION);
	}
	else
	{
		QTreeWidgetItem *prev = NULL;
		if(index>0)	prev = mSuperElevationContainer->child(index-1);
		roadSuperelevation = new RoadTreeItem(index, mSuperElevationContainer, prev, SUPERELEVATION);
		ShiftIndexes(mSuperElevationContainer, index, 1);
	}
}
void RTIRoad::AddCrossfall(int index)
{
	RoadTreeItem *lRoadCrossfall = NULL;
	AddCrossfall(index, lRoadCrossfall);
}
void RTIRoad::AddCrossfall(int index, RoadTreeItem *&roadCrossfall)
{
	if(index>=mCrossfallContainer->childCount())
	{
		roadCrossfall = new RoadTreeItem(index, mCrossfallContainer, CROSSFALL);
	}
	else
	{
		QTreeWidgetItem *prev = NULL;
		if(index>0)	prev = mCrossfallContainer->child(index-1);
		roadCrossfall = new RoadTreeItem(index, mCrossfallContainer, prev, CROSSFALL);
		ShiftIndexes(mCrossfallContainer, index, 1);
	}
}
void RTIRoad::AddLaneSection(int index)
{
	RTILaneSection *lRoadLaneSection = NULL;
	AddLaneSection(index, lRoadLaneSection);
}
void RTIRoad::AddLaneSection(int index, RTILaneSection *&roadLaneSection)
{
	if(index>=mLaneSectionContainer->childCount())
	{
		roadLaneSection = new RTILaneSection(index, mLaneSectionContainer, LANE_SECTION);
	}
	else
	{
		QTreeWidgetItem *prev = NULL;
		if(index>0)	prev = mLaneSectionContainer->child(index-1);
		roadLaneSection = new RTILaneSection(index, mLaneSectionContainer, prev, LANE_SECTION);
		ShiftIndexes(mLaneSectionContainer, index, 1);
	}
}
void RTIRoad::AddObject(int index)
{
	RoadTreeItem *lRoadObject = NULL;
	AddObject(index, lRoadObject);
}
void RTIRoad::AddObject(int index, RoadTreeItem *&roadObject)
{
	if(index>=mObjectContainer->childCount())
	{
		roadObject = new RoadTreeItem(index, mObjectContainer, OBJECT);
	}
	else
	{
		QTreeWidgetItem *prev = NULL;
		if(index>0)	prev = mObjectContainer->child(index-1);
		roadObject = new RoadTreeItem(index, mObjectContainer, prev, OBJECT);
		ShiftIndexes(mObjectContainer, index, 1);
	}
}
void RTIRoad::AddSignal(int index)
{
	RoadTreeItem *lRoadSignal = NULL;
	AddSignal(index, lRoadSignal);
}
void RTIRoad::AddSignal(int index, RoadTreeItem *&radSignal)
{
	if(index>=mSignalContainer->childCount())
	{
		radSignal = new RoadTreeItem(index, mSignalContainer, SIGNAL);
	}
	else
	{
		QTreeWidgetItem *prev = NULL;
		if(index>0)	prev = mSignalContainer->child(index-1);
		radSignal = new RoadTreeItem(index, mSignalContainer, prev, SIGNAL);
		ShiftIndexes(mSignalContainer, index, 1);
	}
}
//===================================================================================================


/**
 * Constructor
 *
 * @param index Index of the corresponding record in OpenDrive structure
 * @param parent Parent of the item, can be a tree widget or another tree item
 * @param type Type of the item (ROAD, JUNCTION, LANE...)
 * @param text Custom name of the item that could be seen in the road tree
 */
RTILaneSection::RTILaneSection(int index, QTreeWidgetItem *parent, RoadTreeItemType type, const QString &text):RoadTreeItem(index,parent,type,text)
{
	Init();
}
RTILaneSection::RTILaneSection(int index, QTreeWidgetItem *parent, RoadTreeItemType type):RoadTreeItem(index,parent,type)
{
	Init();
}

/**
 * Constructor used to insert the item after an existing item in the tree
 *
 * @param index Index of the corresponding record in OpenDrive structure
 * @param parent Parent of the item, can be a tree widget or another tree item
 * @param prev Existing item after which the new one should be inserted
 * @param type Type of the item (ROAD, JUNCTION, LANE...)
 * @param text Custom name of the item that could be seen in the road tree
 */
RTILaneSection::RTILaneSection(int index, QTreeWidgetItem *parent, QTreeWidgetItem *prev, RoadTreeItemType type, const QString &text):RoadTreeItem(index,parent,prev,type,text)
{
	Init();
}
RTILaneSection::RTILaneSection(int index, QTreeWidgetItem *parent, QTreeWidgetItem *prev, RoadTreeItemType type):RoadTreeItem(index,parent,prev,type)
{
	Init();
}

/**
 * Initializes the containers
 */
void RTILaneSection::Init()
{
	mLaneContainerLeft = new RoadTreeItemBase(this,LANE_CONTAINER, "Left lanes");
	mLaneContainerCenter = new RoadTreeItemBase(this,LANE_CONTAINER, "Center lanes");
	mLaneContainerRight = new RoadTreeItemBase(this,LANE_CONTAINER, "Right lanes");
}

/**
 * Returns the child item containers
 */
RoadTreeItemBase *RTILaneSection::GetLaneContainerLeft()
{
	return mLaneContainerLeft;
}
RoadTreeItemBase *RTILaneSection::GetLaneContainerCenter()
{
	return mLaneContainerCenter;
}
RoadTreeItemBase *RTILaneSection::GetLaneContainerRight()
{
	return mLaneContainerRight;
}

/**
 * Two methods used to add a new record to the child containers. Second method also returns the created item
 *
 * @param indexXXX Index or sequence of indices of the corresponding object in OpenDrive structure
 * @param YYY Reference to the pointer that will hold the created road tree item
 */
void RTILaneSection::AddLane(int index, int side)
{
	RTILane *lLane = NULL;
	AddLane(index, lLane, side);
}
void RTILaneSection::AddLane(int index, RTILane*& lane, int side)
{
	if(side>0) lane = new RTILane(index, mLaneContainerLeft, LANE);
	else if(side==0) lane = new RTILane(index, mLaneContainerCenter, LANE);
	else lane = new RTILane(index, mLaneContainerRight, LANE);
}
void RTILaneSection::AddLaneLeft(int index)
{
	RTILane *lLane = NULL;
	AddLaneLeft(index, lLane);
}
void RTILaneSection::AddLaneLeft(int index, RTILane *&lane)
{
	QTreeWidgetItem *prev = NULL;
	lane = new RTILane(index, mLaneContainerLeft, prev, LANE);
	ShiftIndexes(mLaneContainerLeft, index, 1);
	ShiftIndexes(mLaneContainerCenter, -1, 1);
	ShiftIndexes(mLaneContainerRight, -1, 1);
}
void RTILaneSection::AddLaneCenter(int index)
{
	RTILane *lLane = NULL; 
	AddLaneCenter(index, lLane);
}
void RTILaneSection::AddLaneCenter(int index, RTILane *&lane)
{
	lane = new RTILane(index, mLaneContainerCenter, LANE);
	ShiftIndexes(mLaneContainerCenter, index, 1);
	ShiftIndexes(mLaneContainerRight, index, 1);
}
void RTILaneSection::AddLaneRight(int index)
{
	RTILane *lLane = NULL;
	AddLaneRight(index, lLane);
}
void RTILaneSection::AddLaneRight(int index, RTILane *&lane)
{
	lane = new RTILane(index, mLaneContainerRight, LANE);
}
//===================================================================================================

/**
 * Constructor
 *
 * @param index Index of the corresponding record in OpenDrive structure
 * @param parent Parent of the item, can be a tree widget or another tree item
 * @param type Type of the item (ROAD, JUNCTION, LANE...)
 * @param text Custom name of the item that could be seen in the road tree
 */
RTILane::RTILane(int index, QTreeWidgetItem *parent, RoadTreeItemType type, const QString &text):RoadTreeItem(index,parent,type,text)
{
	Init();
}
RTILane::RTILane(int index, QTreeWidgetItem *parent, RoadTreeItemType type):RoadTreeItem(index,parent,type)
{
	Init();
}

/**
 * Constructor used to insert the item after an existing item in the tree
 *
 * @param index Index of the corresponding record in OpenDrive structure
 * @param parent Parent of the item, can be a tree widget or another tree item
 * @param prev Existing item after which the new one should be inserted
 * @param type Type of the item (ROAD, JUNCTION, LANE...)
 * @param text Custom name of the item that could be seen in the road tree
 */
RTILane::RTILane(int index, QTreeWidgetItem *parent, QTreeWidgetItem *prev, RoadTreeItemType type, const QString &text):RoadTreeItem(index,parent,prev,type,text)
{
	Init();
}
RTILane::RTILane(int index, QTreeWidgetItem *parent, QTreeWidgetItem *prev, RoadTreeItemType type):RoadTreeItem(index,parent,prev,type)
{
	Init();
}

/**
 * Initializes the containers
 */
void RTILane::Init()
{
	mLaneWidthContainer = new RoadTreeItemBase(this, LANE_WIDTH_CONTAINER, "Lane width");
	mLaneRoadMarkContainer = new RoadTreeItemBase(this, LANE_ROAD_MARK_CONTAINER, "Lane road mark");
	mLaneMaterialContainer = new RoadTreeItemBase(this, LANE_MATERIAL_CONTAINER, "Lane material");
	mLaneVisibilityContainer = new RoadTreeItemBase(this, LANE_VISIBILITY_CONTAINER, "Lane visibility");
	mLaneSpeedContainer = new RoadTreeItemBase(this, LANE_SPEED_CONTAINER, "Lane speed");
	mLaneAccessContainer = new RoadTreeItemBase(this, LANE_ACCESS_CONTAINER, "Lane access");
	mLaneHeightContainer = new RoadTreeItemBase(this, LANE_HEIGHT_CONTAINER, "Lane height");
}

/**
 * Returns the child item containers
 */
RoadTreeItemBase *RTILane::GetLaneWidthContainer()
{
	return mLaneWidthContainer;
}
RoadTreeItemBase *RTILane::GetLaneRoadMarkContainer()
{
	return mLaneRoadMarkContainer;
}
RoadTreeItemBase *RTILane::GetLaneMaterialContainer()
{
	return mLaneMaterialContainer;
}
RoadTreeItemBase *RTILane::GetLaneVisibilityContainer()
{
	return mLaneVisibilityContainer;
}
RoadTreeItemBase *RTILane::GetLaneSpeedContainer()
{
	return mLaneSpeedContainer;
}
RoadTreeItemBase *RTILane::GetLaneAccessContainer()
{
	return mLaneAccessContainer;
}
RoadTreeItemBase *RTILane::GetLaneHeightContainer()
{
	return mLaneHeightContainer;
}

/**
 * Two methods used to add a new record to the child containers. Second method also returns the created item
 *
 * @param indexXXX Index or sequence of indices of the corresponding object in OpenDrive structure
 * @param YYY Reference to the pointer that will hold the created road tree item
 */
void RTILane::AddLaneWidth(int index)
{
	RoadTreeItem *lLaneWidth = NULL;
	AddLaneWidth(index, lLaneWidth);
}
void RTILane::AddLaneWidth(int index, RoadTreeItem *&laneWidth)
{
	if(index>=mLaneWidthContainer->childCount())
	{
		laneWidth = new RoadTreeItem(index, mLaneWidthContainer, LANE_WIDTH);
	}
	else
	{
		QTreeWidgetItem *prev = NULL;
		if(index>0)	prev = mLaneWidthContainer->child(index-1);
		laneWidth = new RoadTreeItem(index, mLaneWidthContainer, prev, LANE_WIDTH);
		ShiftIndexes(mLaneWidthContainer, index, 1);
	}
}
void RTILane::AddLaneRoadMark(int index)
{
	RoadTreeItem *lLaneRoadMark = NULL;
	AddLaneRoadMark(index, lLaneRoadMark);
}
void RTILane::AddLaneRoadMark(int index, RoadTreeItem *&laneRoadMark)
{
	if(index>=mLaneRoadMarkContainer->childCount())
	{
		laneRoadMark = new RoadTreeItem(index, mLaneRoadMarkContainer, LANE_ROAD_MARK);
	}
	else
	{
		QTreeWidgetItem *prev = NULL;
		if(index>0)	prev = mLaneRoadMarkContainer->child(index-1);
		laneRoadMark = new RoadTreeItem(index, mLaneRoadMarkContainer, LANE_ROAD_MARK);
		ShiftIndexes(mLaneRoadMarkContainer, index, 1);
	}
}
void RTILane::AddLaneMaterial(int index)
{
	RoadTreeItem *lLaneMaterial = NULL;
	AddLaneMaterial(index, lLaneMaterial);
}
void RTILane::AddLaneMaterial(int index, RoadTreeItem *&laneMaterial)
{
	if(index>=mLaneMaterialContainer->childCount())
	{
		laneMaterial = new RoadTreeItem(index, mLaneMaterialContainer, LANE_MATERIAL);
	}
	else
	{
		QTreeWidgetItem *prev = NULL;
		if(index>0)	prev = mLaneMaterialContainer->child(index-1);
		laneMaterial = new RoadTreeItem(index, mLaneMaterialContainer, LANE_MATERIAL);
		ShiftIndexes(mLaneMaterialContainer, index, 1);
	}
}
void RTILane::AddLaneVisibility(int index)
{
	RoadTreeItem *lLaneVisibility = NULL;
	AddLaneVisibility(index, lLaneVisibility);
}
void RTILane::AddLaneVisibility(int index, RoadTreeItem *&laneVisibility)
{
	if(index>=mLaneVisibilityContainer->childCount())
	{
		laneVisibility = new RoadTreeItem(index, mLaneVisibilityContainer, LANE_VISIBILITY);
	}
	else
	{
		QTreeWidgetItem *prev = NULL;
		if(index>0)	prev = mLaneVisibilityContainer->child(index-1);
		laneVisibility = new RoadTreeItem(index, mLaneVisibilityContainer, LANE_VISIBILITY);
		ShiftIndexes(mLaneVisibilityContainer, index, 1);
	}
}
void RTILane::AddLaneSpeed(int index)
{
	RoadTreeItem *lLaneSpeed = NULL;
	AddLaneSpeed(index, lLaneSpeed);
}
void RTILane::AddLaneSpeed(int index, RoadTreeItem *&laneSpeed)
{
	if(index>=mLaneSpeedContainer->childCount())
	{
		laneSpeed = new RoadTreeItem(index, mLaneSpeedContainer, LANE_SPEED);
	}
	else
	{
		QTreeWidgetItem *prev = NULL;
		if(index>0)	prev = mLaneSpeedContainer->child(index-1);
		laneSpeed = new RoadTreeItem(index, mLaneSpeedContainer, LANE_SPEED);
		ShiftIndexes(mLaneSpeedContainer, index, 1);
	}
}
void RTILane::AddLaneAccess(int index)
{
	RoadTreeItem *lLaneAccess = NULL;
	AddLaneAccess(index, lLaneAccess);
}
void RTILane::AddLaneAccess(int index, RoadTreeItem *&laneAccess)
{
	if(index>=mLaneAccessContainer->childCount())
	{
		laneAccess = new RoadTreeItem(index, mLaneAccessContainer, LANE_ACCESS);
	}
	else
	{
		QTreeWidgetItem *prev = NULL;
		if(index>0)	prev = mLaneAccessContainer->child(index-1);
		laneAccess = new RoadTreeItem(index, mLaneAccessContainer, LANE_ACCESS);
		ShiftIndexes(mLaneAccessContainer, index, 1);
	}
}
void RTILane::AddLaneHeight(int index)
{
	RoadTreeItem *lLaneHeight = NULL;
	AddLaneHeight(index, lLaneHeight);
}
void RTILane::AddLaneHeight(int index, RoadTreeItem *&laneHeight)
{
	if(index>=mLaneHeightContainer->childCount())
	{
		laneHeight = new RoadTreeItem(index, mLaneHeightContainer, LANE_HEIGHT);
	}
	else
	{
		QTreeWidgetItem *prev = NULL;
		if(index>0)	prev = mLaneHeightContainer->child(index-1);
		laneHeight = new RoadTreeItem(index, mLaneHeightContainer, LANE_HEIGHT);
		ShiftIndexes(mLaneHeightContainer, index, 1);
	}
}

//===================================================================================================


/**
 * Constructor
 *
 * @param index Index of the corresponding record in OpenDrive structure
 * @param parent Parent of the item, can be a tree widget or another tree item
 * @param type Type of the item (ROAD, JUNCTION, LANE...)
 * @param text Custom name of the item that could be seen in the road tree
 */
RTIJunction::RTIJunction(int index, QTreeWidgetItem *parent, RoadTreeItemType type, const QString &text):RoadTreeItem(index,parent,type,text)
{
	Init();
}
RTIJunction::RTIJunction(int index, QTreeWidgetItem *parent, RoadTreeItemType type):RoadTreeItem(index,parent,type)
{
	Init();
}

/**
 * Constructor used to insert the item after an existing item in the tree
 *
 * @param index Index of the corresponding record in OpenDrive structure
 * @param parent Parent of the item, can be a tree widget or another tree item
 * @param prev Existing item after which the new one should be inserted
 * @param type Type of the item (ROAD, JUNCTION, LANE...)
 * @param text Custom name of the item that could be seen in the road tree
 */
RTIJunction::RTIJunction(int index, QTreeWidgetItem *parent, QTreeWidgetItem *prev, RoadTreeItemType type, const QString &text):RoadTreeItem(index,parent,prev,type,text)
{
	Init();
}
RTIJunction::RTIJunction(int index, QTreeWidgetItem *parent, QTreeWidgetItem *prev, RoadTreeItemType type):RoadTreeItem(index,parent,prev,type)
{
	Init();
}

/**
 * Initializes the containers
 */
void RTIJunction::Init()
{
	mConnectionContainer = new RoadTreeItemBase(this, JUNCTION_CONNECTION_CONTAINER, "Connections");;
	mPriorityContainer = new RoadTreeItemBase(this, JUNCTION_PRIORITY_CONTAINER, "Priority");;
	mControllerContainer = new RoadTreeItemBase(this, JUNCTION_CONTROLLER_CONTAINER, "Controller");;
}

/**
 * Returns the child item containers
 */
RoadTreeItemBase* RTIJunction::GetConnectionContainer()
{
	return mConnectionContainer;
}
RoadTreeItemBase* RTIJunction::GetPriorityContainer()
{
	return mPriorityContainer;
}
RoadTreeItemBase* RTIJunction::GetControllerContainer()
{
	return mControllerContainer;
}


/**
 * Two methods used to add a new record to the child containers. Second method also returns the created item
 *
 * @param indexXXX Index or sequence of indices of the corresponding object in OpenDrive structure
 * @param YYY Reference to the pointer that will hold the created road tree item
 */
void RTIJunction::AddConnection(int index)
{
	RTIJunctionConnection *lConnection = NULL;
	AddConnection(index, lConnection);
}
void RTIJunction::AddConnection(int index, RTIJunctionConnection *&connection)
{
	if(index>=mConnectionContainer->childCount())
	{
		connection = new RTIJunctionConnection(index, mConnectionContainer, JUNCTION_CONNECTION);
	}
	else
	{
		QTreeWidgetItem *prev = NULL;
		if(index>0)	prev = mConnectionContainer->child(index-1);
		connection = new RTIJunctionConnection(index, mConnectionContainer, prev, JUNCTION_CONNECTION);
		ShiftIndexes(mConnectionContainer, index, 1);
	}
}
void RTIJunction::AddPriority(int index)
{
	RoadTreeItem *lPriority = NULL;
	AddPriority(index, lPriority);
}
void RTIJunction::AddPriority(int index, RoadTreeItem *&priority)
{
	if(index>=mPriorityContainer->childCount())
	{
		priority = new RoadTreeItem(index, mPriorityContainer, JUNCTION_PRIORITY);
	}
	else
	{
		QTreeWidgetItem *prev = NULL;
		if(index>0)	prev = mPriorityContainer->child(index-1);
		priority = new RoadTreeItem(index, mPriorityContainer, prev, JUNCTION_PRIORITY);
		ShiftIndexes(mPriorityContainer, index, 1);
	}
}
void RTIJunction::AddController(int index)
{
	RoadTreeItem *lController = NULL;
	AddController(index, lController);
}
void RTIJunction::AddController(int index, RoadTreeItem *&controller)
{
	if(index>=mControllerContainer->childCount())
	{
		controller = new RoadTreeItem(index, mControllerContainer, JUNCTION_CONTROLLER);
	}
	else
	{
		QTreeWidgetItem *prev = NULL;
		if(index>0)	prev = mControllerContainer->child(index-1);
		controller = new RoadTreeItem(index, mControllerContainer, prev, JUNCTION_CONTROLLER);
		ShiftIndexes(mControllerContainer, index, 1);
	}
}
//===================================================================================================

/**
 * Constructor
 *
 * @param index Index of the corresponding record in OpenDrive structure
 * @param parent Parent of the item, can be a tree widget or another tree item
 * @param type Type of the item (ROAD, JUNCTION, LANE...)
 * @param text Custom name of the item that could be seen in the road tree
 */
RTIJunctionConnection::RTIJunctionConnection(int index, QTreeWidgetItem *parent, RoadTreeItemType type, const QString &text):RoadTreeItem(index,parent,type,text)
{
	Init();
}
RTIJunctionConnection::RTIJunctionConnection(int index, QTreeWidgetItem *parent, RoadTreeItemType type):RoadTreeItem(index,parent,type)
{
	Init();
}

/**
 * Constructor used to insert the item after an existing item in the tree
 *
 * @param index Index of the corresponding record in OpenDrive structure
 * @param parent Parent of the item, can be a tree widget or another tree item
 * @param prev Existing item after which the new one should be inserted
 * @param type Type of the item (ROAD, JUNCTION, LANE...)
 * @param text Custom name of the item that could be seen in the road tree
 */
RTIJunctionConnection::RTIJunctionConnection(int index, QTreeWidgetItem *parent, QTreeWidgetItem *prev, RoadTreeItemType type, const QString &text):RoadTreeItem(index,parent,prev,type,text)
{
	Init();
}
RTIJunctionConnection::RTIJunctionConnection(int index, QTreeWidgetItem *parent, QTreeWidgetItem *prev, RoadTreeItemType type):RoadTreeItem(index,parent,prev,type)
{
	Init();
}

/**
 * Initializes the containers
 */
void RTIJunctionConnection::Init()
{
	mLaneLinkContainer = new RoadTreeItemBase(this, JUNCTION_LANE_LINK_CONTAINER, "Lane link");;
}

/**
 * Returns the child item containers
 */
RoadTreeItemBase* RTIJunctionConnection::GetLaneLinkContainer()
{
	return mLaneLinkContainer;
}

/**
 * Two methods used to add a new record to the child containers. Second method also returns the created item
 *
 * @param indexXXX Index or sequence of indices of the corresponding object in OpenDrive structure
 * @param YYY Reference to the pointer that will hold the created road tree item
 */
void RTIJunctionConnection::AddLaneLink(int index)
{
	RoadTreeItem *lLaneLink = NULL;
	AddLaneLink(index, lLaneLink);
}
void RTIJunctionConnection::AddLaneLink(int index, RoadTreeItem *&laneLink)
{
	if(index>=mLaneLinkContainer->childCount())
	{
		laneLink = new RoadTreeItem(index, mLaneLinkContainer, JUNCTION_LANE_LINK);
	}
	else
	{
		QTreeWidgetItem *prev = NULL;
		if(index>0)	prev = mLaneLinkContainer->child(index-1);
		laneLink = new RoadTreeItem(index, mLaneLinkContainer, prev, JUNCTION_LANE_LINK);
		ShiftIndexes(mLaneLinkContainer, index, 1);
	}
}