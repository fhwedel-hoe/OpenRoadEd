#include "RoadTree.h"
#include "moc_RoadTree.cpp"

/**
 * Selection object constructor
 */
Selection::Selection()
{
}

/**
 * Selection object copy constructor
 */
Selection::Selection(const Selection& selection)
{
	mType=selection.mType;
	mIndices=selection.mIndices;
}

/**
 * Assignment operator overload
 */
Selection& Selection::operator=(Selection const& rhs)
{
	if(this != &rhs)
	{
		mType=rhs.mType;
		mIndices=rhs.mIndices;
	}
	return *this;
}

/**
 * Operator overload used to access a specific index from the array using the class object name
 */
unsigned int& Selection::operator[](int index)
{
	return mIndices[index];
}

/**
 * Sets the type for the selected object
 *
 * @param type Type for the object, which is being selected
 */
void Selection::SetType(RoadTreeItemType type)
{
	mType=type;
}

/**
 * Adds an index to the back of the index array
 *
 * @param index Index to be added
 */
void  Selection::AddIndex(unsigned int index)
{
	mIndices.push_back(index);
}

/**
 * Adds an index to the front of the index array
 *
 * @param index Index to be added
 */
void  Selection::AddIndexFront(unsigned int index)
{
	mIndices.insert(mIndices.begin(),index);
}

/**
 * Getter for the type
 */
RoadTreeItemType Selection::GetType()
{
	return mType;
}

/**
 * Getter for a single index from the array
 *
 * @param index Index of the index from the array
 */
unsigned int Selection::GetIndex(int index)
{
	return mIndices[index];
}

/**
 * Clears the index array and resets the type
 */
void  Selection::Reset()
{
	mIndices.clear();
	mType=NONE;
}



/**
 * Constructor
 */
RoadTree::RoadTree(QWidget *parent) : QWidget(parent)
{
	// Main vertical layout
	QVBoxLayout *mainLayout = new QVBoxLayout;

	//-------------------------------------------------
	// Creates a group for the tree
	QGroupBox *settingsGroup = new QGroupBox;
	settingsGroup->setTitle(tr("Road tree"));

	// Creates a tree widget
	mTreeWidget=new QTreeWidget;
	mTreeWidget->setColumnCount(1);


	QVBoxLayout *settingsBoxLayout = new QVBoxLayout;
	settingsBoxLayout->addWidget(mTreeWidget);
	settingsGroup->setLayout(settingsBoxLayout);
	//-------------------------------------------------

	// Adds the group to the layout and sets the layout for the widget
	mainLayout->addWidget(settingsGroup);
	setLayout(mainLayout);
}

/**
 * Initializes the road tree and saves the OpenDrive structure reference
 *
 * @param openDrive Pointer to the OpenDrive structure
 */
void RoadTree::Init(OpenDrive *openDrive)
{
	// Saves the reference to the OpenDrive object
	mOpenDrive=openDrive;

	// Creates and adds the top-level items for the road container and junction container
	mRoadContainer = new RoadTreeItemBase(NULL, ROAD_CONTAINER, "Roads");
	mJunctionContainer = new RoadTreeItemBase(NULL, JUNCTION_CONTAINER, "Junctions");
	mTreeWidget->addTopLevelItem(mRoadContainer);
	mTreeWidget->addTopLevelItem(mJunctionContainer);

	// Reads the last used settings for the tree color coding
	QSettings lSettingsFile("Settings.ini", QSettings::IniFormat);
	bool lTreeColorCodingState = lSettingsFile.value("View/TreeColorCoding",true).toBool();
	mRoadContainer->ColorCode(lTreeColorCodingState);
	mJunctionContainer->ColorCode(lTreeColorCodingState);
}

/**
 * Method called when the tree item color coding is toggled
 */
void RoadTree::ColorCode(bool enable)
{
	// Sets the color coding for the top level items (and thus - for their children)
	mRoadContainer->ColorCode(enable);
	mJunctionContainer->ColorCode(enable);

	// Saves the color coding state to the settings file
	QSettings lSettingsFile("Settings.ini", QSettings::IniFormat);
	lSettingsFile.setValue("View/TreeColorCoding", enable);
	lSettingsFile.sync();
}

/**
 * Gets the current selection object
 *
 * @return Returns the selection object, which holds the type and indices of the selected item
 */
Selection *RoadTree::GetSelection()
{
	return &mSelection;
}

/**
 * Fiils in the selection object given an item from the tree
 *
 * @return item Item used to fill in the selection object
 */
void RoadTree::FillInSelectionObject(RoadTreeItemBase *item)
{
	// Clears the selection
	mSelection.Reset();

	// Gets the road type
	RoadTreeItemBase *curItem = item;
	RoadTreeItemType lType = curItem->GetType();
	mSelection.SetType(lType);

	// Goes up the tree hierarchy, filling in the indices
	while(lType!=ROAD_CONTAINER && lType!=JUNCTION_CONTAINER)
	{
		switch(lType)
		{
		case ROAD:
		case ROAD_TYPE:
		case GEOMETRY_LINE:
		case GEOMETRY_TURN:
		case ELEVATION:
		case SUPERELEVATION:
		case CROSSFALL:
		case LANE_SECTION:
		case LANE:
		case LANE_WIDTH:
		case LANE_ROAD_MARK:
		case LANE_MATERIAL:
		case LANE_VISIBILITY:
		case LANE_SPEED:
		case LANE_ACCESS:
		case LANE_HEIGHT:
		case OBJECT:
		case SIGNAL:
		case CONTROLLER:
		case JUNCTION:
		case JUNCTION_CONNECTION:
		case JUNCTION_LANE_LINK:
		case JUNCTION_PRIORITY:
		case JUNCTION_CONTROLLER:
			mSelection.AddIndexFront(static_cast<RoadTreeItem*>(curItem)->GetIndex());
			break;
		}

		curItem = static_cast<RoadTreeItemBase*>(curItem->parent());
		lType=curItem->GetType();
	}
}

/**
 * Shifts the indices stored in the item when a new item is inserted or deleted from the tree
 *
 * @param container Container that holds the item that is to be deleted
 * @param startingIndex Index of the item where the shift starts
 * @param delta Shifting step (can be negative)
 */
void RoadTree::ShiftIndexes(QTreeWidgetItem *container, int index, int delta)
{
	int size=container->childCount();
	if(index<size)
	{
		// For each item - shift it's index and reset the item name to reflect the changes
		for(int i=index+1; i<size; i++)
		{
			RoadTreeItem *lItem = static_cast<RoadTreeItem*>(container->child(i));
			lItem->ShiftIndex(delta);
			lItem->SetTextByType();
		}
	}
}

/**
 * Clears the tree, removing all the items
 */
void RoadTree::ClearTree()
{
	// Removes all the items from the tree
	mTreeWidget->clear();

	// Creates and adds the top-level items for the road container and junction container
	mRoadContainer = new RoadTreeItemBase(NULL, ROAD_CONTAINER, "Roads");
	mJunctionContainer = new RoadTreeItemBase(NULL, JUNCTION_CONTAINER, "Junctions");
	mTreeWidget->addTopLevelItem(mRoadContainer);
	mTreeWidget->addTopLevelItem(mJunctionContainer);

	// Reads the last used settings for the tree color coding
	QSettings lSettingsFile("Settings.ini", QSettings::IniFormat);
	bool lTreeColorCodingState = lSettingsFile.value("View/TreeColorCoding",true).toBool();
	mRoadContainer->ColorCode(lTreeColorCodingState);
	mJunctionContainer->ColorCode(lTreeColorCodingState);
}

/**
 * Two methods for each record type used to add a new record to the road tree. Second method also returns the created item
 *
 * @param indexXXX Index or sequence of indices of the corresponding object in OpenDrive structure
 * @param YYY Reference to the pointer that will hold the created road tree item
 * @param select Flag that determines if the newly created object will be automatically selected
 */
void RoadTree::AddRoad(int index, bool select=false)
{
	RTIRoad *lRoad = NULL;
	AddRoad(index, lRoad, select);
}

void RoadTree::AddRoad(int index, RTIRoad *&road, bool select=false)
{
	// Disconnect the "Item selected" signal so it is not issued when new object is created
	disconnect(mTreeWidget, SIGNAL(itemSelectionChanged()), this, SLOT(OnItemSelected())); 
	// If the new created item is to be selected - clear the current selection
	if(select) mTreeWidget->clearSelection();
	
	// Create a new item
	if(index>=mRoadContainer->childCount())
	{
		road = new RTIRoad(index, mRoadContainer, ROAD);	
	}
	else
	{
		QTreeWidgetItem *prev = NULL;
		if(index>0)	prev = mRoadContainer->child(index-1);
		road = new RTIRoad(index, mRoadContainer, prev, ROAD);
		ShiftIndexes(mRoadContainer, index, 1);
	}

	// Connect the "Item selected" siganl back
	connect(mTreeWidget, SIGNAL(itemSelectionChanged()), this, SLOT(OnItemSelected())); 

	// Select the item if required
	if(select) 
	{
		road->setSelected(true);
		mTreeWidget->expandItem(road);
		mTreeWidget->scrollToItem(road);
	}
}
void RoadTree::AddRoadType(int indexRoad, int indexRoadType, bool select)
{
	RoadTreeItem *lRoadType=NULL;
	AddRoadType(indexRoad, indexRoadType, lRoadType, select);

}
void RoadTree::AddRoadType(int indexRoad, int indexRoadType, RoadTreeItem *&roadType, bool select)
{
	RTIRoad *lRoad = NULL;
	lRoad = static_cast<RTIRoad*>(GetRoad(indexRoad));
	if(lRoad==NULL) return;
	disconnect(mTreeWidget, SIGNAL(itemSelectionChanged()), this, SLOT(OnItemSelected())); 
	if(select) mTreeWidget->clearSelection();
	lRoad->AddRoadType(indexRoadType,roadType);
	connect(mTreeWidget, SIGNAL(itemSelectionChanged()), this, SLOT(OnItemSelected())); 
	if(select) 
	{
		roadType->setSelected(true);
		mTreeWidget->expandItem(roadType);
		mTreeWidget->scrollToItem(roadType);
	}
}
void RoadTree::AddGeometry(int indexRoad, int indexGeometry, bool select)
{
	RoadTreeItem *lGeometry=NULL;
	AddGeometry(indexRoad, indexGeometry,lGeometry,select);
}
void RoadTree::AddGeometry(int indexRoad, int indexGeometry, RoadTreeItem *&geometry, bool select)
{
	RTIRoad *lRoad = NULL;
	lRoad = static_cast<RTIRoad*>(GetRoad(indexRoad));
	if(lRoad==NULL) return;
	disconnect(mTreeWidget, SIGNAL(itemSelectionChanged()), this, SLOT(OnItemSelected())); 
	if(select) mTreeWidget->clearSelection();
	int lType = GetRealGeometry(indexRoad, indexGeometry)->CheckIfLine();
	lRoad->AddGeometryBlock(indexGeometry,geometry,lType);
	connect(mTreeWidget, SIGNAL(itemSelectionChanged()), this, SLOT(OnItemSelected())); 
	if(select) 
	{
		geometry->setSelected(true);
		mTreeWidget->expandItem(geometry);
		mTreeWidget->scrollToItem(geometry);
	}
}
void RoadTree::AddElevation(int indexRoad, int indexElevation, bool select)
{
	RoadTreeItem *lElevation=NULL;
	AddElevation(indexRoad, indexElevation, lElevation, select);
}
void RoadTree::AddElevation(int indexRoad, int indexElevation, RoadTreeItem *&elevation, bool select)
{
	RTIRoad *lRoad = NULL;
	lRoad = static_cast<RTIRoad*>(GetRoad(indexRoad));
	if(lRoad==NULL) return;
	disconnect(mTreeWidget, SIGNAL(itemSelectionChanged()), this, SLOT(OnItemSelected())); 
	if(select) mTreeWidget->clearSelection();
	lRoad->AddElevation(indexElevation,elevation);
	connect(mTreeWidget, SIGNAL(itemSelectionChanged()), this, SLOT(OnItemSelected())); 
	if(select) 
	{
		elevation->setSelected(true);
		mTreeWidget->expandItem(elevation);
		mTreeWidget->scrollToItem(elevation);
	}
}
void RoadTree::AddSuperElevation(int indexRoad, int indexSuperElevation, bool select)
{
	RoadTreeItem *lSuperElevation=NULL;
	AddSuperElevation(indexRoad, indexSuperElevation, lSuperElevation, select);
}
void RoadTree::AddSuperElevation(int indexRoad, int indexSuperElevation, RoadTreeItem *&superElevation, bool select)
{
	RTIRoad *lRoad = NULL;
	lRoad = static_cast<RTIRoad*>(GetRoad(indexRoad));
	if(lRoad==NULL) return;
	disconnect(mTreeWidget, SIGNAL(itemSelectionChanged()), this, SLOT(OnItemSelected())); 
	if(select) mTreeWidget->clearSelection();
	lRoad->AddSuperElevation(indexSuperElevation,superElevation);
	connect(mTreeWidget, SIGNAL(itemSelectionChanged()), this, SLOT(OnItemSelected())); 
	if(select) 
	{
		superElevation->setSelected(true);
		mTreeWidget->expandItem(superElevation);
		mTreeWidget->scrollToItem(superElevation);
	}
}
void RoadTree::AddCrossfall(int indexRoad, int indexCrossfall, bool select)
{
	RoadTreeItem *lCrossfall=NULL;
	AddCrossfall(indexRoad, indexCrossfall, lCrossfall, select);
}
void RoadTree::AddCrossfall(int indexRoad, int indexCrossfall, RoadTreeItem *&crossfall, bool select)
{
	RTIRoad *lRoad = NULL;
	lRoad = static_cast<RTIRoad*>(GetRoad(indexRoad));
	if(lRoad==NULL) return;
	disconnect(mTreeWidget, SIGNAL(itemSelectionChanged()), this, SLOT(OnItemSelected())); 
	if(select) mTreeWidget->clearSelection();
	lRoad->AddCrossfall(indexCrossfall,crossfall);
	connect(mTreeWidget, SIGNAL(itemSelectionChanged()), this, SLOT(OnItemSelected())); 
	if(select) 
	{
		crossfall->setSelected(true);
		mTreeWidget->expandItem(crossfall);
		mTreeWidget->scrollToItem(crossfall);
	}
}
void RoadTree::AddLaneSection(int indexRoad, int indexLaneSection, bool select)
{
	RTILaneSection *lLaneSection=NULL;
	AddLaneSection(indexRoad, indexLaneSection, lLaneSection, select);
}
void RoadTree::AddLaneSection(int indexRoad, int indexLaneSection, RTILaneSection *&laneSection, bool select)
{
	RTIRoad *lRoad = NULL;
	lRoad = static_cast<RTIRoad*>(GetRoad(indexRoad));
	if(lRoad==NULL) return;
	disconnect(mTreeWidget, SIGNAL(itemSelectionChanged()), this, SLOT(OnItemSelected())); 
	if(select) mTreeWidget->clearSelection();
	lRoad->AddLaneSection(indexLaneSection,laneSection);
	connect(mTreeWidget, SIGNAL(itemSelectionChanged()), this, SLOT(OnItemSelected())); 
	if(select) 
	{
		laneSection->setSelected(true);
		mTreeWidget->expandItem(laneSection);
		mTreeWidget->scrollToItem(laneSection);
	}
}
void RoadTree::AddLaneLeft(int indexRoad, int indexLaneSection, int indexLane, bool select)
{
	RTILane *lLane=NULL;
	AddLaneLeft(indexRoad, indexLaneSection, indexLane, lLane, select);
}
void RoadTree::AddLaneLeft(int indexRoad, int indexLaneSection, int indexLane, RTILane *&lane, bool select)
{
	RTILaneSection *lLaneSection = NULL;
	lLaneSection = static_cast<RTILaneSection*>(GetLaneSection(indexRoad, indexLaneSection));
	if(lLaneSection==NULL) return;
	disconnect(mTreeWidget, SIGNAL(itemSelectionChanged()), this, SLOT(OnItemSelected())); 
	if(select) mTreeWidget->clearSelection();
	lLaneSection->AddLaneLeft(indexLane,lane);
	connect(mTreeWidget, SIGNAL(itemSelectionChanged()), this, SLOT(OnItemSelected())); 
	if(select) 
	{
		lane->setSelected(true);
		mTreeWidget->expandItem(lane);
		mTreeWidget->scrollToItem(lane);
	}
}
void RoadTree::AddLaneCenter(int indexRoad, int indexLaneSection, int indexLane, bool select)
{
	RTILane *lLane=NULL;
	AddLaneCenter(indexRoad, indexLaneSection, indexLane, lLane, select);
}
void RoadTree::AddLaneCenter(int indexRoad, int indexLaneSection, int indexLane, RTILane *&lane, bool select)
{
	RTILaneSection *lLaneSection = NULL;
	lLaneSection = static_cast<RTILaneSection*>(GetLaneSection(indexRoad, indexLaneSection));
	if(lLaneSection==NULL) return;
	disconnect(mTreeWidget, SIGNAL(itemSelectionChanged()), this, SLOT(OnItemSelected())); 
	if(select) mTreeWidget->clearSelection();
	lLaneSection->AddLaneCenter(indexLane,lane);
	connect(mTreeWidget, SIGNAL(itemSelectionChanged()), this, SLOT(OnItemSelected())); 
	if(select) 
	{
		lane->setSelected(true);
		mTreeWidget->expandItem(lane);
		mTreeWidget->scrollToItem(lane);
	}
}
void RoadTree::AddLaneRight(int indexRoad, int indexLaneSection, int indexLane, bool select)
{
	RTILane *lLane=NULL;
	AddLaneRight(indexRoad, indexLaneSection, indexLane, lLane, select);
}
void RoadTree::AddLaneRight(int indexRoad, int indexLaneSection, int indexLane, RTILane *&lane, bool select)
{
	RTILaneSection *lLaneSection = NULL;
	lLaneSection = static_cast<RTILaneSection*>(GetLaneSection(indexRoad, indexLaneSection));
	if(lLaneSection==NULL) return;
	disconnect(mTreeWidget, SIGNAL(itemSelectionChanged()), this, SLOT(OnItemSelected())); 
	if(select) mTreeWidget->clearSelection();
	lLaneSection->AddLaneRight(indexLane,lane);
	connect(mTreeWidget, SIGNAL(itemSelectionChanged()), this, SLOT(OnItemSelected())); 
	if(select) 
	{
		lane->setSelected(true);
		mTreeWidget->expandItem(lane);
		mTreeWidget->scrollToItem(lane);
	}
}
void RoadTree::AddLaneWidth(int indexRoad, int indexLaneSection, int indexLane, int indexLaneWidth, bool select)
{
	RoadTreeItem *lLaneWidth=NULL;
	AddLaneWidth(indexRoad, indexLaneSection, indexLane, indexLaneWidth, lLaneWidth, select);
}
void RoadTree::AddLaneWidth(int indexRoad, int indexLaneSection, int indexLane, int indexLaneWidth, RoadTreeItem *&laneWidth, bool select)
{
	RTILane *lLane = NULL;
	lLane = static_cast<RTILane*>(GetLane(indexRoad, indexLaneSection, indexLane));
	if(lLane==NULL) return;
	disconnect(mTreeWidget, SIGNAL(itemSelectionChanged()), this, SLOT(OnItemSelected())); 
	if(select) mTreeWidget->clearSelection();
	lLane->AddLaneWidth(indexLaneWidth,laneWidth);
	connect(mTreeWidget, SIGNAL(itemSelectionChanged()), this, SLOT(OnItemSelected())); 
	if(select) 
	{
		laneWidth->setSelected(true);
		mTreeWidget->expandItem(laneWidth);
		mTreeWidget->scrollToItem(laneWidth);
	}
}
void RoadTree::AddLaneRoadMark(int indexRoad, int indexLaneSection, int indexLane, int indexLaneRoadMark, bool select)
{
	RoadTreeItem *lLaneRoadMark=NULL;
	AddLaneRoadMark(indexRoad, indexLaneSection, indexLane, indexLaneRoadMark, lLaneRoadMark, select);
}
void RoadTree::AddLaneRoadMark(int indexRoad, int indexLaneSection, int indexLane, int indexLaneRoadMark, RoadTreeItem *&laneRoadMark, bool select)
{
	RTILane *lLane = NULL;
	lLane = static_cast<RTILane*>(GetLane(indexRoad, indexLaneSection, indexLane));
	if(lLane==NULL) return;
	disconnect(mTreeWidget, SIGNAL(itemSelectionChanged()), this, SLOT(OnItemSelected())); 
	if(select) mTreeWidget->clearSelection();
	lLane->AddLaneRoadMark(indexLaneRoadMark,laneRoadMark);
	connect(mTreeWidget, SIGNAL(itemSelectionChanged()), this, SLOT(OnItemSelected())); 
	if(select) 
	{
		laneRoadMark->setSelected(true);
		mTreeWidget->expandItem(laneRoadMark);
		mTreeWidget->scrollToItem(laneRoadMark);
	}
}
void RoadTree::AddLaneMaterial(int indexRoad, int indexLaneSection, int indexLane, int indexLaneMaterial, bool select)
{
	RoadTreeItem *lLaneMaterial=NULL;
	AddLaneMaterial(indexRoad, indexLaneSection, indexLane, indexLaneMaterial, lLaneMaterial, select);
}
void RoadTree::AddLaneMaterial(int indexRoad, int indexLaneSection, int indexLane, int indexLaneMaterial, RoadTreeItem *&laneMaterial, bool select)
{
	RTILane *lLane = NULL;
	lLane = static_cast<RTILane*>(GetLane(indexRoad, indexLaneSection, indexLane));
	if(lLane==NULL) return;
	disconnect(mTreeWidget, SIGNAL(itemSelectionChanged()), this, SLOT(OnItemSelected())); 
	if(select) mTreeWidget->clearSelection();
	lLane->AddLaneMaterial(indexLaneMaterial,laneMaterial);
	connect(mTreeWidget, SIGNAL(itemSelectionChanged()), this, SLOT(OnItemSelected())); 
	if(select) 
	{
		laneMaterial->setSelected(true);
		mTreeWidget->expandItem(laneMaterial);
		mTreeWidget->scrollToItem(laneMaterial);
	}
}
void RoadTree::AddLaneVisibility(int indexRoad, int indexLaneSection, int indexLane, int indexLaneVisibility, bool select)
{
	RoadTreeItem *lLaneVisibility=NULL;
	AddLaneVisibility(indexRoad, indexLaneSection, indexLane, indexLaneVisibility, lLaneVisibility, select);
}
void RoadTree::AddLaneVisibility(int indexRoad, int indexLaneSection, int indexLane, int indexLaneVisibility, RoadTreeItem *&laneVisibility, bool select)
{
	RTILane *lLane = NULL;
	lLane = static_cast<RTILane*>(GetLane(indexRoad, indexLaneSection, indexLane));
	if(lLane==NULL) return;
	disconnect(mTreeWidget, SIGNAL(itemSelectionChanged()), this, SLOT(OnItemSelected())); 
	if(select) mTreeWidget->clearSelection();
	lLane->AddLaneVisibility(indexLaneVisibility,laneVisibility);
	connect(mTreeWidget, SIGNAL(itemSelectionChanged()), this, SLOT(OnItemSelected())); 
	if(select) 
	{
		laneVisibility->setSelected(true);
		mTreeWidget->expandItem(laneVisibility);
		mTreeWidget->scrollToItem(laneVisibility);
	}
}
void RoadTree::AddLaneSpeed(int indexRoad, int indexLaneSection, int indexLane, int indexLaneSpeed, bool select)
{
	RoadTreeItem *lLaneSpeed=NULL;
	AddLaneSpeed(indexRoad, indexLaneSection, indexLane, indexLaneSpeed, lLaneSpeed, select);
}
void RoadTree::AddLaneSpeed(int indexRoad, int indexLaneSection, int indexLane, int indexLaneSpeed, RoadTreeItem *&laneSpeed, bool select)
{
	RTILane *lLane = NULL;
	lLane = static_cast<RTILane*>(GetLane(indexRoad, indexLaneSection, indexLane));
	if(lLane==NULL) return;
	disconnect(mTreeWidget, SIGNAL(itemSelectionChanged()), this, SLOT(OnItemSelected())); 
	if(select) mTreeWidget->clearSelection();
	lLane->AddLaneSpeed(indexLaneSpeed,laneSpeed);
	connect(mTreeWidget, SIGNAL(itemSelectionChanged()), this, SLOT(OnItemSelected())); 
	if(select) 
	{
		laneSpeed->setSelected(true);
		mTreeWidget->expandItem(laneSpeed);
		mTreeWidget->scrollToItem(laneSpeed);
	}
}
void RoadTree::AddLaneAccess(int indexRoad, int indexLaneSection, int indexLane, int indexLaneAccess, bool select)
{
	RoadTreeItem *lLaneAccess=NULL;
	AddLaneAccess(indexRoad, indexLaneSection, indexLane, indexLaneAccess, lLaneAccess, select);
}
void RoadTree::AddLaneAccess(int indexRoad, int indexLaneSection, int indexLane, int indexLaneAccess, RoadTreeItem *&laneAccess, bool select)
{
	RTILane *lLane = NULL;
	lLane = static_cast<RTILane*>(GetLane(indexRoad, indexLaneSection, indexLane));
	if(lLane==NULL) return;
	disconnect(mTreeWidget, SIGNAL(itemSelectionChanged()), this, SLOT(OnItemSelected())); 
	if(select) mTreeWidget->clearSelection();
	lLane->AddLaneAccess(indexLaneAccess,laneAccess);
	connect(mTreeWidget, SIGNAL(itemSelectionChanged()), this, SLOT(OnItemSelected())); 
	if(select) 
	{
		laneAccess->setSelected(true);
		mTreeWidget->expandItem(laneAccess);
		mTreeWidget->scrollToItem(laneAccess);
	}
}
void RoadTree::AddLaneHeight(int indexRoad, int indexLaneSection, int indexLane, int indexLaneHeight, bool select)
{
	RoadTreeItem *lLaneHeight=NULL;
	AddLaneHeight(indexRoad, indexLaneSection, indexLane, indexLaneHeight, lLaneHeight, select);
}
void RoadTree::AddLaneHeight(int indexRoad, int indexLaneSection, int indexLane, int indexLaneHeight, RoadTreeItem *&laneHeight, bool select)
{
	RTILane *lLane = NULL;
	lLane = static_cast<RTILane*>(GetLane(indexRoad, indexLaneSection, indexLane));
	if(lLane==NULL) return;
	disconnect(mTreeWidget, SIGNAL(itemSelectionChanged()), this, SLOT(OnItemSelected())); 
	if(select) mTreeWidget->clearSelection();
	lLane->AddLaneHeight(indexLaneHeight,laneHeight);
	connect(mTreeWidget, SIGNAL(itemSelectionChanged()), this, SLOT(OnItemSelected())); 
	if(select) 
	{
		laneHeight->setSelected(true);
		mTreeWidget->expandItem(laneHeight);
		mTreeWidget->scrollToItem(laneHeight);
	}
}
void RoadTree::AddObject(int indexRoad, int indexObject, bool select)
{
	RoadTreeItem *lObject=NULL;
	AddObject(indexRoad, indexObject, lObject, select);
}
void RoadTree::AddObject(int indexRoad, int indexObject, RoadTreeItem *&object, bool select)
{
	RTIRoad *lRoad = NULL;
	lRoad = static_cast<RTIRoad*>(GetRoad(indexRoad));
	if(lRoad==NULL) return;
	disconnect(mTreeWidget, SIGNAL(itemSelectionChanged()), this, SLOT(OnItemSelected())); 
	if(select) mTreeWidget->clearSelection();
	lRoad->AddObject(indexObject,object);
	connect(mTreeWidget, SIGNAL(itemSelectionChanged()), this, SLOT(OnItemSelected())); 
	if(select) 
	{
		object->setSelected(true);
		mTreeWidget->expandItem(object);
		mTreeWidget->scrollToItem(object);
	}
}
void RoadTree::AddSignal(int indexRoad, int indexSignal, bool select)
{
	RoadTreeItem *lSignal=NULL;
	AddSignal(indexRoad, indexSignal, lSignal, select);
}
void RoadTree::AddSignal(int indexRoad, int indexSignal, RoadTreeItem *&signal, bool select)
{
	RTIRoad *lRoad = NULL;
	lRoad = static_cast<RTIRoad*>(GetRoad(indexRoad));
	if(lRoad==NULL) return;
	disconnect(mTreeWidget, SIGNAL(itemSelectionChanged()), this, SLOT(OnItemSelected())); 
	if(select) mTreeWidget->clearSelection();
	lRoad->AddSignal(indexSignal,signal);
	connect(mTreeWidget, SIGNAL(itemSelectionChanged()), this, SLOT(OnItemSelected())); 
	if(select) 
	{
		signal->setSelected(true);
		mTreeWidget->expandItem(signal);
		mTreeWidget->scrollToItem(signal);
	}
}
void RoadTree::AddJunction(int index, bool select=false)
{
	RTIJunction *lJunction = NULL;
	AddJunction(index, lJunction, select);
}
void RoadTree::AddJunction(int index, RTIJunction *&junction, bool select=false)
{
	disconnect(mTreeWidget, SIGNAL(itemSelectionChanged()), this, SLOT(OnItemSelected())); 
	if(select) mTreeWidget->clearSelection();
	junction = new RTIJunction(index, mJunctionContainer, JUNCTION);
	connect(mTreeWidget, SIGNAL(itemSelectionChanged()), this, SLOT(OnItemSelected())); 
	if(select) 
	{
		junction->setSelected(true);
		mTreeWidget->expandItem(junction);
		mTreeWidget->scrollToItem(junction);
	}
}
void RoadTree::AddJunctionConnection(int indexJunction, int indexConnection, bool select=false)
{
	RTIJunctionConnection *lJunctionConnection=NULL;
	AddJunctionConnection(indexJunction, indexConnection, lJunctionConnection, select);
}
void RoadTree::AddJunctionConnection(int indexJunction, int indexConnection, RTIJunctionConnection *&junctionConnection, bool select=false)
{
	RTIJunction *lJunction = NULL;
	lJunction = static_cast<RTIJunction*>(GetJunction(indexJunction));
	if(lJunction==NULL) return;
	disconnect(mTreeWidget, SIGNAL(itemSelectionChanged()), this, SLOT(OnItemSelected())); 
	if(select) mTreeWidget->clearSelection();
	lJunction->AddConnection(indexConnection,junctionConnection);
	connect(mTreeWidget, SIGNAL(itemSelectionChanged()), this, SLOT(OnItemSelected())); 
	if(select) 
	{
		junctionConnection->setSelected(true);
		mTreeWidget->expandItem(junctionConnection);
		mTreeWidget->scrollToItem(junctionConnection);
	}
}
void RoadTree::AddJunctionLaneLink(int indexJunction, int indexConnection, int indexLaneLink, bool select=false)
{
	RoadTreeItem *lJunctionLaneLink=NULL;
	AddJunctionLaneLink(indexJunction, indexConnection, indexLaneLink, lJunctionLaneLink, select);
}
void RoadTree::AddJunctionLaneLink(int indexJunction, int indexConnection, int indexLaneLink, RoadTreeItem *&junctionLaneLink, bool select=false)
{
	RTIJunctionConnection *lJunctionConnection = NULL;
	lJunctionConnection = static_cast<RTIJunctionConnection*>(GetJunctionConnection(indexJunction,indexConnection));
	if(lJunctionConnection==NULL) return;
	disconnect(mTreeWidget, SIGNAL(itemSelectionChanged()), this, SLOT(OnItemSelected())); 
	if(select) mTreeWidget->clearSelection();
	lJunctionConnection->AddLaneLink(indexLaneLink,junctionLaneLink);
	connect(mTreeWidget, SIGNAL(itemSelectionChanged()), this, SLOT(OnItemSelected())); 
	if(select) 
	{
		junctionLaneLink->setSelected(true);
		mTreeWidget->expandItem(junctionLaneLink);
		mTreeWidget->scrollToItem(junctionLaneLink);
	}
}
void RoadTree::AddJunctionPriority(int indexJunction, int indexPriority, bool select=false)
{
	RoadTreeItem *lJunctionPriority=NULL;
	AddJunctionPriority(indexJunction, indexPriority, lJunctionPriority, select);
}
void RoadTree::AddJunctionPriority(int indexJunction, int indexPriority, RoadTreeItem *&junctionPriority, bool select=false)
{
	RTIJunction *lJunction = NULL;
	lJunction = static_cast<RTIJunction*>(GetJunction(indexJunction));
	if(lJunction==NULL) return;
	disconnect(mTreeWidget, SIGNAL(itemSelectionChanged()), this, SLOT(OnItemSelected())); 
	if(select) mTreeWidget->clearSelection();
	lJunction->AddPriority(indexPriority,junctionPriority);
	connect(mTreeWidget, SIGNAL(itemSelectionChanged()), this, SLOT(OnItemSelected())); 
	if(select) 
	{
		junctionPriority->setSelected(true);
		mTreeWidget->expandItem(junctionPriority);
		mTreeWidget->scrollToItem(junctionPriority);
	}
}
void RoadTree::AddJunctionController(int indexJunction, int indexController, bool select=false)
{
	RoadTreeItem *lJunctionController=NULL;
	AddJunctionController(indexJunction, indexController, lJunctionController, select);
}
void RoadTree::AddJunctionController(int indexJunction, int indexController, RoadTreeItem *&junctionController, bool select=false)
{
	RTIJunction *lJunction = NULL;
	lJunction = static_cast<RTIJunction*>(GetJunction(indexJunction));
	if(lJunction==NULL) return;
	disconnect(mTreeWidget, SIGNAL(itemSelectionChanged()), this, SLOT(OnItemSelected())); 
	if(select) mTreeWidget->clearSelection();
	lJunction->AddController(indexController,junctionController);
	connect(mTreeWidget, SIGNAL(itemSelectionChanged()), this, SLOT(OnItemSelected())); 
	if(select) 
	{
		junctionController->setSelected(true);
		mTreeWidget->expandItem(junctionController);
		mTreeWidget->scrollToItem(junctionController);
	}
}
//===========================================================================================

/**
 * Deletes the currently selected item
 */
void RoadTree::DeleteRoad()
{
	// Disconnect the "Item selected" signal so it is not issued when an item is deleted
	disconnect(mTreeWidget, SIGNAL(itemSelectionChanged()), this, SLOT(OnItemSelected())); 

	// Removes the item from the tree
	RTIRoad *lItem = static_cast<RTIRoad*>(mRoadContainer->takeChild(mSelection[0]));

	// Frees the memeory and shifts the indices
	unsigned int lIndex=mSelection[0];
	if(lItem!=NULL) 
	{
		delete lItem;
		ShiftIndexes(mRoadContainer, lIndex-1, -1);
	}

	// Connects the "Item selected" signal back
	connect(mTreeWidget, SIGNAL(itemSelectionChanged()), this, SLOT(OnItemSelected())); 
}
void RoadTree::DeleteRoadType()
{
	disconnect(mTreeWidget, SIGNAL(itemSelectionChanged()), this, SLOT(OnItemSelected())); 
	RTIRoad *lRoad = static_cast<RTIRoad*>(GetRoad(mSelection[0]));

	if(lRoad!=NULL)
	{
		unsigned int lIndex=mSelection[1];
		RoadTreeItem *lItem = static_cast<RoadTreeItem*>(lRoad->GetRoadTypeContainer()->takeChild(mSelection[1]));
		if(lItem!=NULL) 
		{
			delete lItem;
			ShiftIndexes(lRoad->GetRoadTypeContainer(), lIndex-1, -1);
		}
	}
	connect(mTreeWidget, SIGNAL(itemSelectionChanged()), this, SLOT(OnItemSelected())); 
}
void RoadTree::DeleteGeometry()
{
	disconnect(mTreeWidget, SIGNAL(itemSelectionChanged()), this, SLOT(OnItemSelected())); 
	RTIRoad *lRoad = static_cast<RTIRoad*>(GetRoad(mSelection[0]));

	if(lRoad!=NULL)
	{
		unsigned int lIndex=mSelection[1];
		RoadTreeItem *lItem = static_cast<RoadTreeItem*>(lRoad->GetGeometryBlockContainer()->takeChild(mSelection[1]));
		if(lItem!=NULL)	
		{
			delete lItem;
			ShiftIndexes(lRoad->GetGeometryBlockContainer(), lIndex-1, -1);
		}
	}
	connect(mTreeWidget, SIGNAL(itemSelectionChanged()), this, SLOT(OnItemSelected())); 
}
void RoadTree::DeleteLastGeometry()
{
	disconnect(mTreeWidget, SIGNAL(itemSelectionChanged()), this, SLOT(OnItemSelected())); 
	RTIRoad *lRoad = static_cast<RTIRoad*>(GetRoad(mSelection[0]));

	if(lRoad!=NULL)
	{
		RoadTreeItem *lItem = static_cast<RoadTreeItem*>(lRoad->GetGeometryBlockContainer()->takeChild(lRoad->GetGeometryBlockContainer()->childCount()-1));
		if(lItem!=NULL)	
		{
			delete lItem;
		}
	}
	connect(mTreeWidget, SIGNAL(itemSelectionChanged()), this, SLOT(OnItemSelected())); 
}
void RoadTree::DeleteElevation()
{
	disconnect(mTreeWidget, SIGNAL(itemSelectionChanged()), this, SLOT(OnItemSelected())); 
	RTIRoad *lRoad = static_cast<RTIRoad*>(GetRoad(mSelection[0]));

	if(lRoad!=NULL)
	{
		unsigned int lIndex=mSelection[1];
		RoadTreeItem *lItem = static_cast<RoadTreeItem*>(lRoad->GetElevationContainer()->takeChild(mSelection[1]));
		if(lItem!=NULL) 
		{
			delete lItem;
			ShiftIndexes(lRoad->GetElevationContainer(), lIndex-1, -1);
		}
	}
	connect(mTreeWidget, SIGNAL(itemSelectionChanged()), this, SLOT(OnItemSelected())); 
}
void RoadTree::DeleteSuperElevation()
{
	disconnect(mTreeWidget, SIGNAL(itemSelectionChanged()), this, SLOT(OnItemSelected())); 
	RTIRoad *lRoad = static_cast<RTIRoad*>(GetRoad(mSelection[0]));

	if(lRoad!=NULL)
	{
		unsigned int lIndex=mSelection[1];
		RoadTreeItem *lItem = static_cast<RoadTreeItem*>(lRoad->GetSuperElevationContainer()->takeChild(mSelection[1]));
		if(lItem!=NULL) 
		{
			delete lItem;
			ShiftIndexes(lRoad->GetSuperElevationContainer(), lIndex-1, -1);
		}
	}
	connect(mTreeWidget, SIGNAL(itemSelectionChanged()), this, SLOT(OnItemSelected())); 
}
void RoadTree::DeleteCrossfall()
{
	disconnect(mTreeWidget, SIGNAL(itemSelectionChanged()), this, SLOT(OnItemSelected())); 
	RTIRoad *lRoad = static_cast<RTIRoad*>(GetRoad(mSelection[0]));

	if(lRoad!=NULL)
	{
		unsigned int lIndex=mSelection[1];
		RoadTreeItem *lItem = static_cast<RoadTreeItem*>(lRoad->GetCrossfallContainer()->takeChild(mSelection[1]));
		if(lItem!=NULL) 
		{
			delete lItem;
			ShiftIndexes(lRoad->GetCrossfallContainer(), lIndex-1, -1);
		}
	}
	connect(mTreeWidget, SIGNAL(itemSelectionChanged()), this, SLOT(OnItemSelected())); 
}
void RoadTree::DeleteLaneSection()
{
	disconnect(mTreeWidget, SIGNAL(itemSelectionChanged()), this, SLOT(OnItemSelected())); 
	RTIRoad *lRoad = static_cast<RTIRoad*>(GetRoad(mSelection[0]));

	if(lRoad!=NULL)
	{
		unsigned int lIndex=mSelection[1];
		RTILaneSection *lItem = static_cast<RTILaneSection*>(lRoad->GetLaneSectionContainer()->takeChild(mSelection[1]));
		if(lItem!=NULL) 
		{
			delete lItem;
			ShiftIndexes(lRoad->GetLaneSectionContainer(), lIndex-1, -1);
		}
	}
	connect(mTreeWidget, SIGNAL(itemSelectionChanged()), this, SLOT(OnItemSelected())); 
}
void RoadTree::DeleteLaneLeft()
{
	disconnect(mTreeWidget, SIGNAL(itemSelectionChanged()), this, SLOT(OnItemSelected())); 
	RTILaneSection *lLaneSection = static_cast<RTILaneSection*>(GetLaneSection(mSelection[0],mSelection[1]));
	if(lLaneSection!=NULL)
	{
		RTILane *lItem = static_cast<RTILane*>(lLaneSection->GetLaneContainerLeft()->takeChild(0));
		if(lItem!=NULL) 
		{
			delete lItem;
			ShiftIndexes(lLaneSection->GetLaneContainerLeft(), -1, -1);
			ShiftIndexes(lLaneSection->GetLaneContainerCenter(), -1, -1);
			ShiftIndexes(lLaneSection->GetLaneContainerRight(), -1, -1);
		}
	}
	connect(mTreeWidget, SIGNAL(itemSelectionChanged()), this, SLOT(OnItemSelected())); 
}
void RoadTree::DeleteLaneCenter()
{
	disconnect(mTreeWidget, SIGNAL(itemSelectionChanged()), this, SLOT(OnItemSelected())); 
	RTILaneSection *lLaneSection = static_cast<RTILaneSection*>(GetLaneSection(mSelection[0],mSelection[1]));
	if(lLaneSection!=NULL)
	{
		RTILane *lItem = static_cast<RTILane*>(lLaneSection->GetLaneContainerCenter()->takeChild(0));
		if(lItem!=NULL) 
		{
			delete lItem;
			ShiftIndexes(lLaneSection->GetLaneContainerCenter(), -1, -1);
			ShiftIndexes(lLaneSection->GetLaneContainerRight(), -1, -1);
		}
	}
	connect(mTreeWidget, SIGNAL(itemSelectionChanged()), this, SLOT(OnItemSelected())); 
}
void RoadTree::DeleteLaneRight()
{
	disconnect(mTreeWidget, SIGNAL(itemSelectionChanged()), this, SLOT(OnItemSelected())); 
	RTILaneSection *lLaneSection = static_cast<RTILaneSection*>(GetLaneSection(mSelection[0],mSelection[1]));
	if(lLaneSection!=NULL)
	{
		RTILane *lItem = static_cast<RTILane*>(lLaneSection->GetLaneContainerRight()->takeChild(lLaneSection->GetLaneContainerRight()->childCount()-1));
		if(lItem!=NULL) 
		{
			delete lItem;
		}
	}
	connect(mTreeWidget, SIGNAL(itemSelectionChanged()), this, SLOT(OnItemSelected())); 
}
void RoadTree::DeleteLaneWidth()
{
	disconnect(mTreeWidget, SIGNAL(itemSelectionChanged()), this, SLOT(OnItemSelected())); 
	RTILane *lLane = static_cast<RTILane*>(GetLane(mSelection[0],mSelection[1],mSelection[2]));
	if(lLane!=NULL)
	{
		unsigned int lIndex=mSelection[3];
		RoadTreeItem *lItem = static_cast<RoadTreeItem*>(lLane->GetLaneWidthContainer()->takeChild(mSelection[3]));
		if(lItem!=NULL) 
		{
			delete lItem;
			ShiftIndexes(lLane->GetLaneWidthContainer(), lIndex-1, -1);
		}
	}
	connect(mTreeWidget, SIGNAL(itemSelectionChanged()), this, SLOT(OnItemSelected())); 
}
void RoadTree::DeleteLaneRoadMark()
{
	disconnect(mTreeWidget, SIGNAL(itemSelectionChanged()), this, SLOT(OnItemSelected())); 
	RTILane *lLane = static_cast<RTILane*>(GetLane(mSelection[0],mSelection[1],mSelection[2]));
	if(lLane!=NULL)
	{
		unsigned int lIndex=mSelection[3];
		RoadTreeItem *lItem = static_cast<RoadTreeItem*>(lLane->GetLaneRoadMarkContainer()->takeChild(mSelection[3]));
		if(lItem!=NULL) 
		{
			delete lItem;
			ShiftIndexes(lLane->GetLaneRoadMarkContainer(), lIndex-1, -1);
		}
	}
	connect(mTreeWidget, SIGNAL(itemSelectionChanged()), this, SLOT(OnItemSelected())); 
}
void RoadTree::DeleteLaneMaterial()
{
	disconnect(mTreeWidget, SIGNAL(itemSelectionChanged()), this, SLOT(OnItemSelected())); 
	RTILane *lLane = static_cast<RTILane*>(GetLane(mSelection[0],mSelection[1],mSelection[2]));
	if(lLane!=NULL)
	{
		unsigned int lIndex=mSelection[3];
		RoadTreeItem *lItem = static_cast<RoadTreeItem*>(lLane->GetLaneMaterialContainer()->takeChild(mSelection[3]));
		if(lItem!=NULL) 
		{
			delete lItem;
			ShiftIndexes(lLane->GetLaneMaterialContainer(), lIndex-1, -1);
		}
	}
	connect(mTreeWidget, SIGNAL(itemSelectionChanged()), this, SLOT(OnItemSelected())); 
}
void RoadTree::DeleteLaneVisibility()
{
	disconnect(mTreeWidget, SIGNAL(itemSelectionChanged()), this, SLOT(OnItemSelected())); 
	RTILane *lLane = static_cast<RTILane*>(GetLane(mSelection[0],mSelection[1],mSelection[2]));
	if(lLane!=NULL)
	{
		unsigned int lIndex=mSelection[3];
		RoadTreeItem *lItem = static_cast<RoadTreeItem*>(lLane->GetLaneVisibilityContainer()->takeChild(mSelection[3]));
		if(lItem!=NULL) 
		{
			delete lItem;
			ShiftIndexes(lLane->GetLaneVisibilityContainer(), lIndex-1, -1);
		}
	}
	connect(mTreeWidget, SIGNAL(itemSelectionChanged()), this, SLOT(OnItemSelected())); 
}
void RoadTree::DeleteLaneSpeed()
{
	disconnect(mTreeWidget, SIGNAL(itemSelectionChanged()), this, SLOT(OnItemSelected())); 
	RTILane *lLane = static_cast<RTILane*>(GetLane(mSelection[0],mSelection[1],mSelection[2]));
	if(lLane!=NULL)
	{
		unsigned int lIndex=mSelection[3];
		RoadTreeItem *lItem = static_cast<RoadTreeItem*>(lLane->GetLaneSpeedContainer()->takeChild(mSelection[3]));
		if(lItem!=NULL) 
		{
			delete lItem;
			ShiftIndexes(lLane->GetLaneSpeedContainer(), lIndex-1, -1);
		}
	}
	connect(mTreeWidget, SIGNAL(itemSelectionChanged()), this, SLOT(OnItemSelected())); 
}
void RoadTree::DeleteLaneAccess()
{
	disconnect(mTreeWidget, SIGNAL(itemSelectionChanged()), this, SLOT(OnItemSelected())); 
	RTILane *lLane = static_cast<RTILane*>(GetLane(mSelection[0],mSelection[1],mSelection[2]));
	if(lLane!=NULL)
	{
		unsigned int lIndex=mSelection[3];
		RoadTreeItem *lItem = static_cast<RoadTreeItem*>(lLane->GetLaneAccessContainer()->takeChild(mSelection[3]));
		if(lItem!=NULL) 
		{
			delete lItem;
			ShiftIndexes(lLane->GetLaneAccessContainer(), lIndex-1, -1);
		}
	}
	connect(mTreeWidget, SIGNAL(itemSelectionChanged()), this, SLOT(OnItemSelected())); 
}
void RoadTree::DeleteLaneHeight()
{
	disconnect(mTreeWidget, SIGNAL(itemSelectionChanged()), this, SLOT(OnItemSelected())); 
	RTILane *lLane = static_cast<RTILane*>(GetLane(mSelection[0],mSelection[1],mSelection[2]));
	if(lLane!=NULL)
	{
		unsigned int lIndex=mSelection[3];
		RoadTreeItem *lItem = static_cast<RoadTreeItem*>(lLane->GetLaneHeightContainer()->takeChild(mSelection[3]));
		if(lItem!=NULL) 
		{
			delete lItem;
			ShiftIndexes(lLane->GetLaneHeightContainer(), lIndex-1, -1);
		}
	}
	connect(mTreeWidget, SIGNAL(itemSelectionChanged()), this, SLOT(OnItemSelected())); 
}
void RoadTree::DeleteObject()
{
	disconnect(mTreeWidget, SIGNAL(itemSelectionChanged()), this, SLOT(OnItemSelected())); 
	RTIRoad *lRoad = static_cast<RTIRoad*>(GetRoad(mSelection[0]));

	if(lRoad!=NULL)
	{
		unsigned int lIndex=mSelection[1];
		RoadTreeItem *lItem = static_cast<RoadTreeItem*>(lRoad->GetObjectContainer()->takeChild(mSelection[1]));
		if(lItem!=NULL) 
		{
			delete lItem;
			ShiftIndexes(lRoad->GetObjectContainer(), lIndex-1, -1);
		}
	}
	connect(mTreeWidget, SIGNAL(itemSelectionChanged()), this, SLOT(OnItemSelected())); 
}
void RoadTree::DeleteSignal()
{
	disconnect(mTreeWidget, SIGNAL(itemSelectionChanged()), this, SLOT(OnItemSelected())); 
	RTIRoad *lRoad = static_cast<RTIRoad*>(GetRoad(mSelection[0]));

	if(lRoad!=NULL)
	{
		unsigned int lIndex=mSelection[1];
		RoadTreeItem *lItem = static_cast<RoadTreeItem*>(lRoad->GetSignalContainer()->takeChild(mSelection[1]));
		if(lItem!=NULL) 
		{
			delete lItem;
			ShiftIndexes(lRoad->GetSignalContainer(), lIndex-1, -1);
		}
	}
	connect(mTreeWidget, SIGNAL(itemSelectionChanged()), this, SLOT(OnItemSelected())); 
}
void RoadTree::DeleteJunction()
{
	disconnect(mTreeWidget, SIGNAL(itemSelectionChanged()), this, SLOT(OnItemSelected())); 
	RTIJunction *lItem = static_cast<RTIJunction*>(mJunctionContainer->takeChild(mSelection[0]));

	unsigned int lIndex=mSelection[0];
	if(lItem!=NULL) 
	{
		delete lItem;
		ShiftIndexes(mJunctionContainer, lIndex-1, -1);
	}
	connect(mTreeWidget, SIGNAL(itemSelectionChanged()), this, SLOT(OnItemSelected())); 
}
void RoadTree::DeleteJunctionConnection()
{
	disconnect(mTreeWidget, SIGNAL(itemSelectionChanged()), this, SLOT(OnItemSelected())); 
	RTIJunction *lJunction = static_cast<RTIJunction*>(GetJunction(mSelection[0]));

	if(lJunction!=NULL)
	{
		unsigned int lIndex=mSelection[1];
		RTIJunctionConnection *lItem = static_cast<RTIJunctionConnection*>(lJunction->GetConnectionContainer()->takeChild(mSelection[1]));
		if(lItem!=NULL) 
		{
			delete lItem;
			ShiftIndexes(lJunction->GetConnectionContainer(), lIndex-1, -1);
		}
	}
	connect(mTreeWidget, SIGNAL(itemSelectionChanged()), this, SLOT(OnItemSelected())); 
}
void RoadTree::DeleteJunctionLaneLink()
{
	disconnect(mTreeWidget, SIGNAL(itemSelectionChanged()), this, SLOT(OnItemSelected())); 
	RTIJunctionConnection *lJunctionConnection = static_cast<RTIJunctionConnection*>(GetJunctionConnection(mSelection[0],mSelection[1]));

	if(lJunctionConnection!=NULL)
	{
		unsigned int lIndex=mSelection[2];
		RoadTreeItem *lItem = static_cast<RoadTreeItem*>(lJunctionConnection->GetLaneLinkContainer()->takeChild(mSelection[2]));
		if(lItem!=NULL) 
		{
			delete lItem;
			ShiftIndexes(lJunctionConnection->GetLaneLinkContainer(), lIndex-1, -1);
		}
	}
	connect(mTreeWidget, SIGNAL(itemSelectionChanged()), this, SLOT(OnItemSelected())); 
}
void RoadTree::DeleteJunctionPriority()
{
	disconnect(mTreeWidget, SIGNAL(itemSelectionChanged()), this, SLOT(OnItemSelected())); 
	RTIJunction *lJunction = static_cast<RTIJunction*>(GetJunction(mSelection[0]));

	if(lJunction!=NULL)
	{
		unsigned int lIndex=mSelection[1];
		RoadTreeItem *lItem = static_cast<RoadTreeItem*>(lJunction->GetPriorityContainer()->takeChild(mSelection[1]));
		if(lItem!=NULL) 
		{
			delete lItem;
			ShiftIndexes(lJunction->GetPriorityContainer(), lIndex-1, -1);
		}
	}
	connect(mTreeWidget, SIGNAL(itemSelectionChanged()), this, SLOT(OnItemSelected())); 
}
void RoadTree::DeleteJunctionController()
{
	disconnect(mTreeWidget, SIGNAL(itemSelectionChanged()), this, SLOT(OnItemSelected())); 
	RTIJunction *lJunction = static_cast<RTIJunction*>(GetJunction(mSelection[0]));

	if(lJunction!=NULL)
	{
		unsigned int lIndex=mSelection[1];
		RoadTreeItem *lItem = static_cast<RoadTreeItem*>(lJunction->GetControllerContainer()->takeChild(mSelection[1]));
		if(lItem!=NULL) 
		{
			delete lItem;
			ShiftIndexes(lJunction->GetControllerContainer(), lIndex-1, -1);
		}
	}
	connect(mTreeWidget, SIGNAL(itemSelectionChanged()), this, SLOT(OnItemSelected())); 
}
//===========================================================================================

/**
 * Selects the item in the road tree, given the indices
 *
 * @param indexXXX Index or sequence of indices, used to select an object
 */
void RoadTree::SelectNone()
{
	mTreeWidget->clearSelection();
	mSelection.Reset();
	emit NothingSelected();
}

void RoadTree::SelectRoad(int index)
{
	mTreeWidget->clearSelection();

	QTreeWidgetItem *lItem = GetRoad(index);

	if(lItem!=NULL) 
	{
		lItem->setSelected(true);
		mTreeWidget->expandItem(lItem);
		mTreeWidget->scrollToItem(lItem);
	}
}
void RoadTree::SelectRoadType(int indexRoad, int indexRoadType)
{
	mTreeWidget->clearSelection();

	QTreeWidgetItem *lItem = GetRoadType(indexRoad, indexRoadType);

	if(lItem!=NULL) 
	{
		lItem->setSelected(true);
		mTreeWidget->expandItem(lItem);
		mTreeWidget->scrollToItem(lItem);
	}
}
void RoadTree::SelectGeometry(int indexRoad, int indexGeometry)
{
	mTreeWidget->clearSelection();

	QTreeWidgetItem *lItem = GetGeometry(indexRoad, indexGeometry);

	if(lItem!=NULL) 
	{
		lItem->setSelected(true);
		mTreeWidget->expandItem(lItem);
		mTreeWidget->scrollToItem(lItem);
	}
}
void RoadTree::SelectElevation(int indexRoad, int indexElevation)
{
	mTreeWidget->clearSelection();

	QTreeWidgetItem *lItem = GetElevation(indexRoad, indexElevation);

	if(lItem!=NULL) 
	{
		lItem->setSelected(true);
		mTreeWidget->expandItem(lItem);
		mTreeWidget->scrollToItem(lItem);
	}
}
void RoadTree::SelectSuperElevation(int indexRoad, int indexSuperElevation)
{
	mTreeWidget->clearSelection();

	QTreeWidgetItem *lItem = GetSuperElevation(indexRoad, indexSuperElevation);

	if(lItem!=NULL) 
	{
		lItem->setSelected(true);
		mTreeWidget->expandItem(lItem);
		mTreeWidget->scrollToItem(lItem);
	}
}
void RoadTree::SelectCrossfall(int indexRoad, int indexCrossfall)
{
	mTreeWidget->clearSelection();

	QTreeWidgetItem *lItem = GetCrossfall(indexRoad, indexCrossfall);

	if(lItem!=NULL) 
	{
		lItem->setSelected(true);
		mTreeWidget->expandItem(lItem);
		mTreeWidget->scrollToItem(lItem);
	}
}
void RoadTree::SelectLaneSection(int indexRoad, int indexLaneSection)
{
	mTreeWidget->clearSelection();

	QTreeWidgetItem *lItem = GetLaneSection(indexRoad, indexLaneSection);

	if(lItem!=NULL) 
	{
		lItem->setSelected(true);
		mTreeWidget->expandItem(lItem);
		mTreeWidget->scrollToItem(lItem);
	}
}
void RoadTree::SelectLane(int indexRoad, int indexLaneSection, int indexLane)
{
	mTreeWidget->clearSelection();

	QTreeWidgetItem *lItem = GetLane(indexRoad, indexLaneSection, indexLane);

	if(lItem!=NULL) 
	{
		lItem->setSelected(true);
		mTreeWidget->expandItem(lItem);
		mTreeWidget->scrollToItem(lItem);
	}
}
void RoadTree::SelectLaneWidth(int indexRoad, int indexLaneSection, int indexLane, int indexLaneWidth)
{
	mTreeWidget->clearSelection();

	QTreeWidgetItem *lItem = GetLaneWidth(indexRoad, indexLaneSection, indexLane, indexLaneWidth);

	if(lItem!=NULL) 
	{
		lItem->setSelected(true);
		mTreeWidget->expandItem(lItem);
		mTreeWidget->scrollToItem(lItem);
	}
}
void RoadTree::SelectLaneRoadMark(int indexRoad, int indexLaneSection, int indexLane, int indexLaneRoadMark)
{
	mTreeWidget->clearSelection();

	QTreeWidgetItem *lItem = GetLaneRoadMark(indexRoad, indexLaneSection, indexLane, indexLaneRoadMark);

	if(lItem!=NULL) 
	{
		lItem->setSelected(true);
		mTreeWidget->expandItem(lItem);
		mTreeWidget->scrollToItem(lItem);
	}
}
void RoadTree::SelectLaneMaterial(int indexRoad, int indexLaneSection, int indexLane, int indexLaneMaterial)
{
	mTreeWidget->clearSelection();

	QTreeWidgetItem *lItem = GetLaneMaterial(indexRoad, indexLaneSection, indexLane, indexLaneMaterial);

	if(lItem!=NULL) 
	{
		lItem->setSelected(true);
		mTreeWidget->expandItem(lItem);
		mTreeWidget->scrollToItem(lItem);
	}
}
void RoadTree::SelectLaneVisibility(int indexRoad, int indexLaneSection, int indexLane, int indexLaneVisibility)
{
	mTreeWidget->clearSelection();

	QTreeWidgetItem *lItem = GetLaneVisibility(indexRoad, indexLaneSection, indexLane, indexLaneVisibility);

	if(lItem!=NULL) 
	{
		lItem->setSelected(true);
		mTreeWidget->expandItem(lItem);
		mTreeWidget->scrollToItem(lItem);
	}
}
void RoadTree::SelectLaneSpeed(int indexRoad, int indexLaneSection, int indexLane, int indexLaneSpeed)
{
	mTreeWidget->clearSelection();

	QTreeWidgetItem *lItem = GetLaneSpeed(indexRoad, indexLaneSection, indexLane, indexLaneSpeed);

	if(lItem!=NULL) 
	{
		lItem->setSelected(true);
		mTreeWidget->expandItem(lItem);
		mTreeWidget->scrollToItem(lItem);
	}
}
void RoadTree::SelectLaneAccess(int indexRoad, int indexLaneSection, int indexLane, int indexLaneAccess)
{
	mTreeWidget->clearSelection();

	QTreeWidgetItem *lItem = GetLaneAccess(indexRoad, indexLaneSection, indexLane, indexLaneAccess);

	if(lItem!=NULL) 
	{
		lItem->setSelected(true);
		mTreeWidget->expandItem(lItem);
		mTreeWidget->scrollToItem(lItem);
	}
}
void RoadTree::SelectLaneHeight(int indexRoad, int indexLaneSection, int indexLane, int indexLaneHeight)
{
	mTreeWidget->clearSelection();

	QTreeWidgetItem *lItem = GetLaneHeight(indexRoad, indexLaneSection, indexLane, indexLaneHeight);

	if(lItem!=NULL) 
	{
		lItem->setSelected(true);
		mTreeWidget->expandItem(lItem);
		mTreeWidget->scrollToItem(lItem);
	}
}
void RoadTree::SelectObject(int indexRoad, int indexObject)
{
	mTreeWidget->clearSelection();

	QTreeWidgetItem *lItem = GetObject(indexRoad, indexObject);

	if(lItem!=NULL) 
	{
		lItem->setSelected(true);
		mTreeWidget->expandItem(lItem);
		mTreeWidget->scrollToItem(lItem);
	}
}
void RoadTree::SelectSignal(int indexRoad, int indexSignal)
{
	mTreeWidget->clearSelection();

	QTreeWidgetItem *lItem = GetSignal(indexRoad, indexSignal);

	if(lItem!=NULL) 
	{
		lItem->setSelected(true);
		mTreeWidget->expandItem(lItem);
		mTreeWidget->scrollToItem(lItem);
	}
}
void RoadTree::SelectJunction(int index)
{
	mTreeWidget->clearSelection();

	QTreeWidgetItem *lItem = GetJunction(index);

	if(lItem!=NULL) 
	{
		lItem->setSelected(true);
		mTreeWidget->expandItem(lItem);
		mTreeWidget->scrollToItem(lItem);
	}
}
void RoadTree::SelectJunctionConnection(int indexJunction, int indexConnection)
{
	mTreeWidget->clearSelection();

	QTreeWidgetItem *lItem = GetJunctionConnection(indexJunction, indexConnection);

	if(lItem!=NULL) 
	{
		lItem->setSelected(true);
		mTreeWidget->expandItem(lItem);
		mTreeWidget->scrollToItem(lItem);
	}
}
void RoadTree::SelectJunctionLaneLink(int indexJunction, int indexConnection, int indexLaneLink)
{
	mTreeWidget->clearSelection();

	QTreeWidgetItem *lItem = GetJunctionLaneLink(indexJunction, indexConnection, indexLaneLink);

	if(lItem!=NULL) 
	{
		lItem->setSelected(true);
		mTreeWidget->expandItem(lItem);
		mTreeWidget->scrollToItem(lItem);
	}
}
void RoadTree::SelectJunctionPriority(int indexJunction, int indexPriority)
{
	mTreeWidget->clearSelection();

	QTreeWidgetItem *lItem = GetJunctionPriority(indexJunction, indexPriority);

	if(lItem!=NULL) 
	{
		lItem->setSelected(true);
		mTreeWidget->expandItem(lItem);
		mTreeWidget->scrollToItem(lItem);
	}
}
void RoadTree::SelectJunctionController(int indexJunction, int indexController)
{
	mTreeWidget->clearSelection();

	QTreeWidgetItem *lItem = GetJunctionController(indexJunction, indexController);

	if(lItem!=NULL) 
	{
		lItem->setSelected(true);
		mTreeWidget->expandItem(lItem);
		mTreeWidget->scrollToItem(lItem);
	}
}
//===========================================================================================

/**
 * Returns the item in the road tree, given the indices
 *
 * @param indexXXX Index or sequence of indices, used to select an object
 * @return Road tree item that is to be returned
 */
QTreeWidgetItem* RoadTree::GetRoad(int index)
{
	return mRoadContainer->child(index);
}
QTreeWidgetItem* RoadTree::GetRoadType(int indexRoad, int indexRoadType)
{
	RTIRoad *lRoad = static_cast<RTIRoad*>(GetRoad(indexRoad));
	if(lRoad==NULL) return NULL;
	RoadTreeItemBase *lContainer = lRoad->GetRoadTypeContainer();
	return lContainer->child(indexRoadType);
}
QTreeWidgetItem* RoadTree::GetGeometry(int indexRoad, int indexGeometry)
{
	RTIRoad *lRoad = static_cast<RTIRoad*>(GetRoad(indexRoad));
	if(lRoad==NULL) return NULL;
	RoadTreeItemBase *lContainer = lRoad->GetGeometryBlockContainer();
	return lContainer->child(indexGeometry);
}
QTreeWidgetItem* RoadTree::GetElevation(int indexRoad, int indexElevation)
{
	RTIRoad *lRoad = static_cast<RTIRoad*>(GetRoad(indexRoad));
	if(lRoad==NULL) return NULL;
	RoadTreeItemBase *lContainer = lRoad->GetElevationContainer();
	return lContainer->child(indexElevation);
}
QTreeWidgetItem* RoadTree::GetSuperElevation(int indexRoad, int indexSuperElevation)
{
	RTIRoad *lRoad = static_cast<RTIRoad*>(GetRoad(indexRoad));
	if(lRoad==NULL) return NULL;
	RoadTreeItemBase *lContainer = lRoad->GetSuperElevationContainer();
	return lContainer->child(indexSuperElevation);
}
QTreeWidgetItem* RoadTree::GetCrossfall(int indexRoad, int indexCrossfall)
{
	RTIRoad *lRoad = static_cast<RTIRoad*>(GetRoad(indexRoad));
	if(lRoad==NULL) return NULL;
	RoadTreeItemBase *lContainer = lRoad->GetCrossfallContainer();
	return lContainer->child(indexCrossfall);
}
QTreeWidgetItem* RoadTree::GetLaneSection(int indexRoad, int indexLaneSection)
{
	RTIRoad *lRoad = static_cast<RTIRoad*>(GetRoad(indexRoad));
	if(lRoad==NULL) return NULL;
	RoadTreeItemBase *lContainer = lRoad->GetLaneSectionContainer();
	return lContainer->child(indexLaneSection);
}
QTreeWidgetItem* RoadTree::GetLane(int indexRoad, int indexLaneSection, int indexLane)
{
	RTILaneSection *lLaneSection = static_cast<RTILaneSection*>(GetLaneSection(indexRoad, indexLaneSection));
	if(lLaneSection==NULL) return NULL;
	RoadTreeItemBase *lContainer = lLaneSection->GetLaneContainerLeft();
	RoadTreeItem *lItem;
	for(int i=0; i<lContainer->childCount(); i++)
	{
		lItem = static_cast<RoadTreeItem*>(lContainer->child(i));
		if(lItem->GetIndex() == indexLane)
		{
			return lContainer->child(i);
		}
	}

	lContainer = lLaneSection->GetLaneContainerCenter();
	for(int i=0; i<lContainer->childCount(); i++)
	{
		lItem = static_cast<RoadTreeItem*>(lContainer->child(i));
		if(lItem->GetIndex() == indexLane)
		{
			return lContainer->child(i);
		}
	}

	lContainer = lLaneSection->GetLaneContainerRight();
	for(int i=0; i<lContainer->childCount(); i++)
	{
		lItem = static_cast<RoadTreeItem*>(lContainer->child(i));
		if(lItem->GetIndex() == indexLane)
		{
			return lContainer->child(i);
		}
	}
	return NULL;
}
QTreeWidgetItem* RoadTree::GetLaneWidth(int indexRoad, int indexLaneSection, int indexLane, int indexLaneWidth)
{
	RTILane *lLane = static_cast<RTILane*>(GetLane(indexRoad, indexLaneSection, indexLane));
	if(lLane==NULL) return NULL;
	RoadTreeItemBase *lContainer = lLane->GetLaneWidthContainer();
	return lContainer->child(indexLaneWidth);
}
QTreeWidgetItem* RoadTree::GetLaneRoadMark(int indexRoad, int indexLaneSection, int indexLane, int indexLaneRoadMark)
{
	RTILane *lLane = static_cast<RTILane*>(GetLane(indexRoad, indexLaneSection, indexLane));
	if(lLane==NULL) return NULL;
	RoadTreeItemBase *lContainer = lLane->GetLaneRoadMarkContainer();
	return lContainer->child(indexLaneRoadMark);
}
QTreeWidgetItem* RoadTree::GetLaneMaterial(int indexRoad, int indexLaneSection, int indexLane, int indexLaneMaterial)
{
	RTILane *lLane = static_cast<RTILane*>(GetLane(indexRoad, indexLaneSection, indexLane));
	if(lLane==NULL) return NULL;
	RoadTreeItemBase *lContainer = lLane->GetLaneMaterialContainer();
	return lContainer->child(indexLaneMaterial);
}
QTreeWidgetItem* RoadTree::GetLaneVisibility(int indexRoad, int indexLaneSection, int indexLane, int indexLaneVisibility)
{
	RTILane *lLane = static_cast<RTILane*>(GetLane(indexRoad, indexLaneSection, indexLane));
	if(lLane==NULL) return NULL;
	RoadTreeItemBase *lContainer = lLane->GetLaneVisibilityContainer();
	return lContainer->child(indexLaneVisibility);
}
QTreeWidgetItem* RoadTree::GetLaneSpeed(int indexRoad, int indexLaneSection, int indexLane, int indexLaneSpeed)
{
	RTILane *lLane = static_cast<RTILane*>(GetLane(indexRoad, indexLaneSection, indexLane));
	if(lLane==NULL) return NULL;
	RoadTreeItemBase *lContainer = lLane->GetLaneSpeedContainer();
	return lContainer->child(indexLaneSpeed);
}
QTreeWidgetItem* RoadTree::GetLaneAccess(int indexRoad, int indexLaneSection, int indexLane, int indexLaneAccess)
{
	RTILane *lLane = static_cast<RTILane*>(GetLane(indexRoad, indexLaneSection, indexLane));
	if(lLane==NULL) return NULL;
	RoadTreeItemBase *lContainer = lLane->GetLaneAccessContainer();
	return lContainer->child(indexLaneAccess);
}
QTreeWidgetItem* RoadTree::GetLaneHeight(int indexRoad, int indexLaneSection, int indexLane, int indexLaneHeight)
{
	RTILane *lLane = static_cast<RTILane*>(GetLane(indexRoad, indexLaneSection, indexLane));
	if(lLane==NULL) return NULL;
	RoadTreeItemBase *lContainer = lLane->GetLaneHeightContainer();
	return lContainer->child(indexLaneHeight);
}
QTreeWidgetItem* RoadTree::GetObject(int indexRoad, int indexObject)
{
	RTIRoad *lRoad = static_cast<RTIRoad*>(GetRoad(indexRoad));
	if(lRoad==NULL) return NULL;
	RoadTreeItemBase *lContainer = lRoad->GetObjectContainer();
	return lContainer->child(indexObject);
}
QTreeWidgetItem* RoadTree::GetSignal(int indexRoad, int indexSignal)
{
	RTIRoad *lRoad = static_cast<RTIRoad*>(GetRoad(indexRoad));
	if(lRoad==NULL) return NULL;
	RoadTreeItemBase *lContainer = lRoad->GetSignalContainer();
	return lContainer->child(indexSignal);
}
QTreeWidgetItem* RoadTree::GetJunction(int index)
{
	return mJunctionContainer->child(index);
}
QTreeWidgetItem* RoadTree::GetJunctionConnection(int indexJunction, int indexConnection)
{
	RTIJunction *lJunction = static_cast<RTIJunction*>(GetJunction(indexJunction));
	if(lJunction==NULL) return NULL;
	RoadTreeItemBase *lContainer = lJunction->GetConnectionContainer();
	return lContainer->child(indexConnection);
}
QTreeWidgetItem* RoadTree::GetJunctionLaneLink(int indexJunction, int indexConnection, int indexLaneLink)
{
	RTIJunctionConnection *lJunctionConnection = static_cast<RTIJunctionConnection*>(GetJunctionConnection(indexJunction, indexConnection));
	if(lJunctionConnection==NULL) return NULL;
	RoadTreeItemBase *lContainer = lJunctionConnection->GetLaneLinkContainer();
	return lContainer->child(indexLaneLink);
}
QTreeWidgetItem* RoadTree::GetJunctionPriority(int indexJunction, int indexPriority)
{
	RTIJunction *lJunction = static_cast<RTIJunction*>(GetJunction(indexJunction));
	if(lJunction==NULL) return NULL;
	RoadTreeItemBase *lContainer = lJunction->GetPriorityContainer();
	return lContainer->child(indexPriority);
}
QTreeWidgetItem* RoadTree::GetJunctionController(int indexJunction, int indexController)
{
	RTIJunction *lJunction = static_cast<RTIJunction*>(GetJunction(indexJunction));
	if(lJunction==NULL) return NULL;
	RoadTreeItemBase *lContainer = lJunction->GetControllerContainer();
	return lContainer->child(indexController);
}
//===========================================================================================


/**
 * Returns the Open Drive structure object that is currently selected in the road tree
 *
 * @return OpenDrive related object from the OpenDrive structure
 */
Road* RoadTree::GetRealRoad()
{
	return mOpenDrive->GetRoad(mSelection[0]);
}
RoadType* RoadTree::GetRealRoadType()
{
	return mOpenDrive->GetRoad(mSelection[0])->GetRoadType(mSelection[1]);
}
GeometryBlock* RoadTree::GetRealGeometry()
{
	return mOpenDrive->GetRoad(mSelection[0])->GetGeometryBlock(mSelection[1]);
}
Elevation* RoadTree::GetRealElevation()
{
	return mOpenDrive->GetRoad(mSelection[0])->GetElevation(mSelection[1]);
}
SuperElevation* RoadTree::GetRealSuperElevation()
{
	return mOpenDrive->GetRoad(mSelection[0])->GetSuperElevation(mSelection[1]);
}
Crossfall* RoadTree::GetRealCrossfall()
{
	return mOpenDrive->GetRoad(mSelection[0])->GetCrossfall(mSelection[1]);
}
LaneSection* RoadTree::GetRealLaneSection()
{
	return mOpenDrive->GetRoad(mSelection[0])->GetLaneSection(mSelection[1]);
}
Lane* RoadTree::GetRealLane()
{
	return mOpenDrive->GetRoad(mSelection[0])->GetLaneSection(mSelection[1])->GetLane(mSelection[2]);
}
LaneWidth* RoadTree::GetRealLaneWidth()
{
	return mOpenDrive->GetRoad(mSelection[0])->GetLaneSection(mSelection[1])->GetLane(mSelection[2])->GetLaneWidth(mSelection[3]);
}
LaneRoadMark* RoadTree::GetRealLaneRoadMark()
{
	return mOpenDrive->GetRoad(mSelection[0])->GetLaneSection(mSelection[1])->GetLane(mSelection[2])->GetLaneRoadMark(mSelection[3]);
}
LaneMaterial* RoadTree::GetRealLaneMaterial()
{
	return mOpenDrive->GetRoad(mSelection[0])->GetLaneSection(mSelection[1])->GetLane(mSelection[2])->GetLaneMaterial(mSelection[3]);
}
LaneVisibility* RoadTree::GetRealLaneVisibility()
{
	return mOpenDrive->GetRoad(mSelection[0])->GetLaneSection(mSelection[1])->GetLane(mSelection[2])->GetLaneVisibility(mSelection[3]);
}
LaneSpeed* RoadTree::GetRealLaneSpeed()
{
	return mOpenDrive->GetRoad(mSelection[0])->GetLaneSection(mSelection[1])->GetLane(mSelection[2])->GetLaneSpeed(mSelection[3]);
}
LaneAccess* RoadTree::GetRealLaneAccess()
{
	return mOpenDrive->GetRoad(mSelection[0])->GetLaneSection(mSelection[1])->GetLane(mSelection[2])->GetLaneAccess(mSelection[3]);
}
LaneHeight* RoadTree::GetRealLaneHeight()
{
	return mOpenDrive->GetRoad(mSelection[0])->GetLaneSection(mSelection[1])->GetLane(mSelection[2])->GetLaneHeight(mSelection[3]);
}
Object* RoadTree::GetRealObject()
{
	return mOpenDrive->GetRoad(mSelection[0])->GetObject(mSelection[1]);
}
Signal* RoadTree::GetRealSignal()
{
	return mOpenDrive->GetRoad(mSelection[0])->GetSignal(mSelection[1]);
}
Junction* RoadTree::GetRealJunction()
{
	return mOpenDrive->GetJunction(mSelection[0]);
}
JunctionConnection* RoadTree::GetRealJunctionConnection()
{
	return mOpenDrive->GetJunction(mSelection[0])->GetJunctionConnection(mSelection[1]);
}
JunctionLaneLink* RoadTree::GetRealJunctionLaneLink()
{
	return mOpenDrive->GetJunction(mSelection[0])->GetJunctionConnection(mSelection[1])->GetJunctionLaneLink(mSelection[2]);
}
JunctionPriorityRoad* RoadTree::GetRealJunctionPriority()
{
	return mOpenDrive->GetJunction(mSelection[0])->GetJunctionPriority(mSelection[1]);
}
JunctionController* RoadTree::GetRealJunctionController()
{
	return mOpenDrive->GetJunction(mSelection[0])->GetJunctionController(mSelection[1]);
}
//===========================================================================================


/**
 * Returns the OpenDrive structure object, given the indices
 *
 * @param indexXXX Index or sequence of indices, used to select an object
 * @return OpenDrive related object from the OpenDrive structure
 */
Road* RoadTree::GetRealRoad(int indexRoad)
{
	return mOpenDrive->GetRoad(indexRoad);
}
RoadType* RoadTree::GetRealRoadType(int indexRoad, int indexRoadType)
{
	return mOpenDrive->GetRoad(indexRoad)->GetRoadType(indexRoadType);
}
GeometryBlock* RoadTree::GetRealGeometry(int indexRoad, int indexGeometry)
{
	return mOpenDrive->GetRoad(indexRoad)->GetGeometryBlock(indexGeometry);
}
Elevation* RoadTree::GetRealElevation(int indexRoad, int indexElevation)
{
	return mOpenDrive->GetRoad(indexRoad)->GetElevation(indexElevation);
}
SuperElevation* RoadTree::GetRealSuperElevation(int indexRoad, int indexSuperElevation)
{
	return mOpenDrive->GetRoad(indexRoad)->GetSuperElevation(indexSuperElevation);
}
Crossfall* RoadTree::GetRealCrossfall(int indexRoad, int indexCrossfall)
{
	return mOpenDrive->GetRoad(indexRoad)->GetCrossfall(indexCrossfall);
}
LaneSection* RoadTree::GetRealLaneSection(int indexRoad, int indexLaneSection)
{
	return mOpenDrive->GetRoad(indexRoad)->GetLaneSection(indexLaneSection);
}
Lane* RoadTree::GetRealLane(int indexRoad, int indexLaneSection, int indexLane)
{
	return mOpenDrive->GetRoad(indexRoad)->GetLaneSection(indexLaneSection)->GetLane(indexLane);
}
LaneWidth* RoadTree::GetRealLaneWidth(int indexRoad, int indexLaneSection, int indexLane, int indexLaneWidth)
{
	return mOpenDrive->GetRoad(indexRoad)->GetLaneSection(indexLaneSection)->GetLane(indexLane)->GetLaneWidth(indexLaneWidth);
}
LaneRoadMark* RoadTree::GetRealLaneRoadMark(int indexRoad, int indexLaneSection, int indexLane, int indexLaneRoadMark)
{
	return mOpenDrive->GetRoad(indexRoad)->GetLaneSection(indexLaneSection)->GetLane(indexLane)->GetLaneRoadMark(indexLaneRoadMark);
}
LaneMaterial* RoadTree::GetRealLaneMaterial(int indexRoad, int indexLaneSection, int indexLane, int indexLaneMaterial)
{
	return mOpenDrive->GetRoad(indexRoad)->GetLaneSection(indexLaneSection)->GetLane(indexLane)->GetLaneMaterial(indexLaneMaterial);
}
LaneVisibility* RoadTree::GetRealLaneVisibility(int indexRoad, int indexLaneSection, int indexLane, int indexLaneVisibility)
{
	return mOpenDrive->GetRoad(indexRoad)->GetLaneSection(indexLaneSection)->GetLane(indexLane)->GetLaneVisibility(indexLaneVisibility);
}
LaneSpeed* RoadTree::GetRealLaneSpeed(int indexRoad, int indexLaneSection, int indexLane, int indexLaneSpeed)
{
	return mOpenDrive->GetRoad(indexRoad)->GetLaneSection(indexLaneSection)->GetLane(indexLane)->GetLaneSpeed(indexLaneSpeed);
}
LaneAccess* RoadTree::GetRealLaneAccess(int indexRoad, int indexLaneSection, int indexLane, int indexLaneAccess)
{
	return mOpenDrive->GetRoad(indexRoad)->GetLaneSection(indexLaneSection)->GetLane(indexLane)->GetLaneAccess(indexLaneAccess);
}
LaneHeight* RoadTree::GetRealLaneHeight(int indexRoad, int indexLaneSection, int indexLane, int indexLaneHeight)
{
	return mOpenDrive->GetRoad(indexRoad)->GetLaneSection(indexLaneSection)->GetLane(indexLane)->GetLaneHeight(indexLaneHeight);
}
Object* RoadTree::GetRealObject(int indexRoad, int indexObject)
{
	return mOpenDrive->GetRoad(indexRoad)->GetObject(indexObject);
}
Signal* RoadTree::GetRealSignal(int indexRoad, int indexSignal)
{
	return mOpenDrive->GetRoad(indexRoad)->GetSignal(indexSignal);
}
Junction* RoadTree::GetRealJunction(int indexJunction)
{
	return mOpenDrive->GetJunction(indexJunction);
}
JunctionConnection* RoadTree::GetRealJunctionConnection(int indexJunction, int indexConnection)
{
	return mOpenDrive->GetJunction(indexJunction)->GetJunctionConnection(indexConnection);
}
JunctionLaneLink* RoadTree::GetRealJunctionLaneLink(int indexJunction, int indexConnection, int indexLaneLink)
{
	return mOpenDrive->GetJunction(indexJunction)->GetJunctionConnection(indexConnection)->GetJunctionLaneLink(indexLaneLink);
}
JunctionPriorityRoad* RoadTree::GetRealJunctionPriority(int indexJunction, int indexPriority)
{
	return mOpenDrive->GetJunction(indexJunction)->GetJunctionPriority(indexPriority);
}
JunctionController* RoadTree::GetRealJunctionController(int indexJunction, int indexController)
{
	return mOpenDrive->GetJunction(indexJunction)->GetJunctionController(indexController);
}
//===========================================================================================

/**
 * Loads the OpenDrive structure and fills in the road tree
 *
 * @param openDrive Pointer to the OpenDrive structure
 */
void RoadTree::LoadStructure(OpenDrive *openDrive)
{
	// If openDrive object is not set yet
	if(openDrive!=NULL)
	{
		// Set it
		mOpenDrive=openDrive;

		// Reset the road tree
		ClearTree();

		// Go through the roads in OpenDrive structure and create appropriate records in the road tree
		for(unsigned int iRoad=0; iRoad<openDrive->GetRoadCount(); iRoad++)
		{
			RTIRoad *lRoad = NULL;
			AddRoad(iRoad, lRoad);

			//========= ROAD TYPE ==========//
			for(unsigned int iRoadType=0; iRoadType<openDrive->GetRoad(iRoad)->GetRoadTypeCount(); iRoadType++)
			{
				lRoad->AddRoadType(iRoadType);
			}

			//========= GEOMETRY ==========//
			for(unsigned int iRoadGeometry=0; iRoadGeometry<openDrive->GetRoad(iRoad)->GetGeometryBlockCount(); iRoadGeometry++)
			{
				int lType = GetRealGeometry(iRoad, iRoadGeometry)->CheckIfLine();
				lRoad->AddGeometryBlock(iRoadGeometry, lType);
			}

			//========= ELEVATION ==========//
			for(unsigned int iRoadElevation=0; iRoadElevation<openDrive->GetRoad(iRoad)->GetElevationCount(); iRoadElevation++)
			{
				lRoad->AddElevation(iRoadElevation);
			}

			//========= SUPERELEVATION ==========//
			for(unsigned int iRoadSuperelevation=0; iRoadSuperelevation<openDrive->GetRoad(iRoad)->GetSuperElevationCount(); iRoadSuperelevation++)
			{
				lRoad->AddSuperElevation(iRoadSuperelevation);
			}

			//========= CROSSFALL ==========//
			for(unsigned int iRoadCrossfall=0; iRoadCrossfall<openDrive->GetRoad(iRoad)->GetCrossfallCount(); iRoadCrossfall++)
			{
				lRoad->AddCrossfall(iRoadCrossfall);
			}

			//========= LANE SECTION ==========//
			for(unsigned int iRoadLaneSection=0; iRoadLaneSection<openDrive->GetRoad(iRoad)->GetLaneSectionCount(); iRoadLaneSection++)
			{
				RTILaneSection *lLaneSection=NULL;
				lRoad->AddLaneSection(iRoadLaneSection, lLaneSection);

				//========== LANES ==========//
				for(unsigned int iLanes=0; iLanes<openDrive->GetRoad(iRoad)->GetLaneSection(iRoadLaneSection)->GetLaneCount(); iLanes++)
				{
					RTILane *lLane=NULL;

					int lLaneSide = GetRealLane(iRoad,iRoadLaneSection,iLanes)->GetSide();
					lLaneSection->AddLane(iLanes, lLane, lLaneSide);

					//--- LANE WIDTHS ---//
					for(unsigned int iLaneWidth=0; iLaneWidth<openDrive->GetRoad(iRoad)->GetLaneSection(iRoadLaneSection)->GetLane(iLanes)->GetLaneWidthCount(); iLaneWidth++)
					{
						lLane->AddLaneWidth(iLaneWidth);
					}
					//--- LANE ROAD MARKS ---//
					for(unsigned int iLaneRoadMark=0; iLaneRoadMark<openDrive->GetRoad(iRoad)->GetLaneSection(iRoadLaneSection)->GetLane(iLanes)->GetLaneRoadMarkCount(); iLaneRoadMark++)
					{
						lLane->AddLaneRoadMark(iLaneRoadMark);
					}
					//--- LANE MATERIAL ---//
					for(unsigned int iLaneMaterial=0; iLaneMaterial<openDrive->GetRoad(iRoad)->GetLaneSection(iRoadLaneSection)->GetLane(iLanes)->GetLaneMaterialCount(); iLaneMaterial++)
					{
						lLane->AddLaneMaterial(iLaneMaterial);
					}
					//--- LANE VISIBILITY ---//
					for(unsigned int iLaneVisibility=0; iLaneVisibility<openDrive->GetRoad(iRoad)->GetLaneSection(iRoadLaneSection)->GetLane(iLanes)->GetLaneVisibilityCount(); iLaneVisibility++)
					{
						lLane->AddLaneVisibility(iLaneVisibility);
					}
					//--- LANE SPEED ---//
					for(unsigned int iLaneSpeed=0; iLaneSpeed<openDrive->GetRoad(iRoad)->GetLaneSection(iRoadLaneSection)->GetLane(iLanes)->GetLaneSpeedCount(); iLaneSpeed++)
					{
						lLane->AddLaneSpeed(iLaneSpeed);
					}
					//--- LANE ACCESS ---//
					for(unsigned int iLaneAccess=0; iLaneAccess<openDrive->GetRoad(iRoad)->GetLaneSection(iRoadLaneSection)->GetLane(iLanes)->GetLaneAccessCount(); iLaneAccess++)
					{
						lLane->AddLaneAccess(iLaneAccess);
					}
					//--- LANE HEIGHT ---//
					for(unsigned int iLaneHeight=0; iLaneHeight<openDrive->GetRoad(iRoad)->GetLaneSection(iRoadLaneSection)->GetLane(iLanes)->GetLaneHeightCount(); iLaneHeight++)
					{
						lLane->AddLaneHeight(iLaneHeight);
					}
				}
			}

			//========= OBJECTS ==========//
			for(unsigned int iRoadObject=0; iRoadObject<openDrive->GetRoad(iRoad)->GetObjectCount(); iRoadObject++)
			{
				lRoad->AddObject(iRoadObject);
			}

			//========= SIGNALS ==========//
			for(unsigned int iRoadSignal=0; iRoadSignal<openDrive->GetRoad(iRoad)->GetSignalCount(); iRoadSignal++)
			{
				lRoad->AddSignal(iRoadSignal);
			}
		}

		//========= JUNCTIONS ==========//
		for(unsigned int iJunction=0; iJunction<openDrive->GetJunctionCount(); iJunction++)
		{
			RTIJunction *lJunction = NULL;
			AddJunction(iJunction, lJunction);

			//========= CONNECTIONS ==========//
			for(unsigned int iJunctionConnection=0; iJunctionConnection<openDrive->GetJunction(iJunction)->GetJunctionConnectionCount(); iJunctionConnection++)
			{
				RTIJunctionConnection *lJunctionConnection = NULL;
				lJunction->AddConnection(iJunctionConnection, lJunctionConnection);

				//========= LANE LINKS ==========//
				for(unsigned int iJunctionLaneLink=0; iJunctionLaneLink<openDrive->GetJunction(iJunction)->GetJunctionConnection(iJunctionConnection)->GetJunctionLaneLinkCount(); iJunctionLaneLink++)
				{
					lJunctionConnection->AddLaneLink(iJunctionLaneLink);
				}
			}

			//========= PRIORITIES ==========//
			for(unsigned int iJunctionPriority=0; iJunctionPriority<openDrive->GetJunction(iJunction)->GetJunctionPriorityCount(); iJunctionPriority++)
			{
				lJunction->AddPriority(iJunctionPriority);
			}

			//========= CONTROLLERS ==========//
			for(unsigned int iJunctionController=0; iJunctionController<openDrive->GetJunction(iJunction)->GetJunctionControllerCount(); iJunctionController++)
			{
				lJunction->AddController(iJunctionController);
			}
		}

	}

	// Disconnect any previous "Item selected" signals and connect again, using the new built tree
	disconnect(mTreeWidget, SIGNAL(itemSelectionChanged()), this, SLOT(OnItemSelected())); 
	connect(mTreeWidget, SIGNAL(itemSelectionChanged()), this, SLOT(OnItemSelected())); 
}

/**
 * Method called when an item in the road tree is clicked
 */
void RoadTree::OnItemSelected()
{
	// Get the list of selected items
	QList<QTreeWidgetItem *> list = mTreeWidget->selectedItems();

	// If more than one item is selected - select none, else call the method bellow
	if(list.size()==1)
	{
		OnItemActivation(list[0],0);
	}
	else 
	{
		SelectNone();
		//emit NothingSelected();
	}
}

/**
 * Method called when an item in the road tree is clicked
 */
void RoadTree::OnItemActivation( QTreeWidgetItem * item, int column)
{
	// Get the selected item from the road tree
	RoadTreeItemBase *lItem = static_cast<RoadTreeItemBase*>(item);
	
	// Fill in the selection object
	FillInSelectionObject(lItem);

	// Get the selected object type
	RoadTreeItemType lType = mSelection.GetType();

	// Depending on the type - emit one of the signals
	switch (lType)
	{
	case ROAD:
		{
			Road *lRoad=GetRealRoad();
			if(lRoad!=NULL) emit RoadSelected(GetRealRoad());
			break;
		}
	case ROAD_TYPE:
		{
			RoadType *lRoadType=GetRealRoadType();

			// Calculates the limitation range for the "S" parameter
			double lMinS=0;
			double lMaxS=GetRealRoad(mSelection[0])->GetRoadLength();
			RoadType *lRoadTypePrev = GetRealRoadType(mSelection[0],mSelection[1]-1);
			RoadType *lRoadTypeNext = GetRealRoadType(mSelection[0],mSelection[1]+1);
			if(lRoadTypePrev!=NULL) lMinS=lRoadTypePrev->GetS();
			if(lRoadTypeNext!=NULL) lMaxS=lRoadTypeNext->GetS();
			
			if(lRoadType!=NULL) emit RoadTypeSelected(lRoadType, lMinS, lMaxS);
			break;
		}
	case GEOMETRY_LINE:
		{
			GeometryBlock *lRoadGeometry = GetRealGeometry();

			bool lFirst=false;
			if(mSelection[1]==0) lFirst=true;

			if(lRoadGeometry!=NULL) emit GeometryLineSelected(lRoadGeometry, lFirst);
			break;
		}
	case GEOMETRY_TURN:
		{
			GeometryBlock *lRoadGeometry = GetRealGeometry();

			bool lFirst=false;
			if(mSelection[1]==0) lFirst=true;

			if(lRoadGeometry!=NULL) emit GeometryTurnSelected(lRoadGeometry, lFirst);
			break;
		}
	case ELEVATION:
		{
			Elevation *lElevation=GetRealElevation();
			
			double lMinS=0;
			double lMaxS=GetRealRoad(mSelection[0])->GetRoadLength();
			Elevation *lElevationPrev = GetRealElevation(mSelection[0],mSelection[1]-1);
			Elevation *lElevationNext = GetRealElevation(mSelection[0],mSelection[1]+1);
			if(lElevationPrev!=NULL) lMinS=lElevationPrev->GetS();
			if(lElevationNext!=NULL) lMaxS=lElevationNext->GetS();
			
			if(lElevation!=NULL) emit ElevationSelected(lElevation, lMinS, lMaxS);
			break;
		}
	case SUPERELEVATION:
		{
			SuperElevation *lSuperElevation=GetRealSuperElevation();
			
			double lMinS=0;
			double lMaxS=GetRealRoad(mSelection[0])->GetRoadLength();
			SuperElevation *lSuperElevationPrev = GetRealSuperElevation(mSelection[0],mSelection[1]-1);
			SuperElevation *lSuperElevationNext = GetRealSuperElevation(mSelection[0],mSelection[1]+1);
			if(lSuperElevationPrev!=NULL) lMinS=lSuperElevationPrev->GetS();
			if(lSuperElevationNext!=NULL) lMaxS=lSuperElevationNext->GetS();
			
			if(lSuperElevation!=NULL) emit SuperElevationSelected(lSuperElevation, lMinS, lMaxS);
			break;
		}
	case CROSSFALL:
		{
			Crossfall *lCrossfall=GetRealCrossfall();
			
			double lMinS=0;
			double lMaxS=GetRealRoad(mSelection[0])->GetRoadLength();
			Crossfall *lCrossfallPrev = GetRealCrossfall(mSelection[0],mSelection[1]-1);
			Crossfall *lCrossfallNext = GetRealCrossfall(mSelection[0],mSelection[1]+1);
			if(lCrossfallPrev!=NULL) lMinS=lCrossfallPrev->GetS();
			if(lCrossfallNext!=NULL) lMaxS=lCrossfallNext->GetS();
			
			if(lCrossfall!=NULL) emit CrossfallSelected(lCrossfall, lMinS, lMaxS);
			break;
		}
	case LANE_SECTION:
		{
			LaneSection *lLaneSection=GetRealLaneSection();
			
			double lMinS=0;
			double lMaxS=GetRealRoad(mSelection[0])->GetRoadLength()- (lLaneSection->GetS2() - lLaneSection->GetS());
			LaneSection *lLaneSectionPrev = GetRealLaneSection(mSelection[0],mSelection[1]-1);
			LaneSection *lLaneSectionNext = GetRealLaneSection(mSelection[0],mSelection[1]+1);
			if(lLaneSectionPrev!=NULL) lMinS=lLaneSectionPrev->GetS2();
			if(lLaneSectionNext!=NULL) lMaxS=lLaneSectionNext->GetS() - (lLaneSection->GetS2() - lLaneSection->GetS());
			
			bool lFirst=false;
			if(mSelection[1]==0) lFirst=true;
			if(lLaneSection!=NULL) emit LaneSectionSelected(lLaneSection, lMinS, lMaxS, lFirst);
			break;
		}
	case LANE:
		{
			Lane *lLane=GetRealLane();
			if(lLane!=NULL) emit LaneSelected(lLane);
			break;
		}
	case LANE_WIDTH:
		{
			LaneWidth *lLaneWidth = GetRealLaneWidth();
			
			double lMinS=0;
			double lMaxS=GetRealRoad(mSelection[0])->GetRoadLength();
			LaneSection *lLaneSectionCur = GetRealLaneSection(mSelection[0],mSelection[1]);
			LaneSection *lLaneSectionNext = GetRealLaneSection(mSelection[0],mSelection[1]+1);
			if(lLaneSectionNext!=NULL && lLaneSectionCur!=NULL)  lMaxS=lLaneSectionNext->GetS()-lLaneSectionCur->GetS();
			LaneWidth *lLaneWidthPrev = GetRealLaneWidth(mSelection[0],mSelection[1],mSelection[2],mSelection[3]-1);
			LaneWidth *lLaneWidthNext = GetRealLaneWidth(mSelection[0],mSelection[1],mSelection[2],mSelection[3]+1);
			if(lLaneWidthPrev!=NULL) lMinS=lLaneWidthPrev->GetS();
			if(lLaneWidthNext!=NULL) lMaxS=lLaneWidthNext->GetS();
			
			if(lLaneWidth!=NULL) emit LaneWidthSelected(lLaneWidth, lMinS, lMaxS);
			break;
		}
	case LANE_ROAD_MARK:
		{
			LaneRoadMark *lLaneRoadMark = GetRealLaneRoadMark();
			
			double lMinS=0;
			double lMaxS=GetRealRoad(mSelection[0])->GetRoadLength();
			LaneSection *lLaneSectionCur = GetRealLaneSection(mSelection[0],mSelection[1]);
			LaneSection *lLaneSectionNext = GetRealLaneSection(mSelection[0],mSelection[1]+1);
			if(lLaneSectionNext!=NULL && lLaneSectionCur!=NULL)  lMaxS=lLaneSectionNext->GetS()-lLaneSectionCur->GetS();
			LaneRoadMark *lLaneRoadMarkPrev = GetRealLaneRoadMark(mSelection[0],mSelection[1],mSelection[2],mSelection[3]-1);
			LaneRoadMark *lLaneRoadMarkNext = GetRealLaneRoadMark(mSelection[0],mSelection[1],mSelection[2],mSelection[3]+1);
			if(lLaneRoadMarkPrev!=NULL) lMinS=lLaneRoadMarkPrev->GetS();
			if(lLaneRoadMarkNext!=NULL) lMaxS=lLaneRoadMarkNext->GetS();
			
			if(lLaneRoadMark!=NULL) emit LaneRoadMarkSelected(lLaneRoadMark, lMinS, lMaxS);
			break;
		}
	case LANE_MATERIAL:
		{
			LaneMaterial *lLaneMaterial = GetRealLaneMaterial();
			
			double lMinS=0;
			double lMaxS=GetRealRoad(mSelection[0])->GetRoadLength();
			LaneSection *lLaneSectionCur = GetRealLaneSection(mSelection[0],mSelection[1]);
			LaneSection *lLaneSectionNext = GetRealLaneSection(mSelection[0],mSelection[1]+1);
			if(lLaneSectionNext!=NULL && lLaneSectionCur!=NULL)  lMaxS=lLaneSectionNext->GetS()-lLaneSectionCur->GetS();
			LaneMaterial *lLaneMaterialPrev = GetRealLaneMaterial(mSelection[0],mSelection[1],mSelection[2],mSelection[3]-1);
			LaneMaterial *lLaneMaterialNext = GetRealLaneMaterial(mSelection[0],mSelection[1],mSelection[2],mSelection[3]+1);
			if(lLaneMaterialPrev!=NULL) lMinS=lLaneMaterialPrev->GetS();
			if(lLaneMaterialNext!=NULL) lMaxS=lLaneMaterialNext->GetS();
			
			if(lLaneMaterial!=NULL) emit LaneMaterialSelected(lLaneMaterial, lMinS, lMaxS);
			break;
		}
	case LANE_VISIBILITY:
		{
			LaneVisibility *lLaneVisibility = GetRealLaneVisibility();
			
			double lMinS=0;
			double lMaxS=GetRealRoad(mSelection[0])->GetRoadLength();
			LaneSection *lLaneSectionCur = GetRealLaneSection(mSelection[0],mSelection[1]);
			LaneSection *lLaneSectionNext = GetRealLaneSection(mSelection[0],mSelection[1]+1);
			if(lLaneSectionNext!=NULL && lLaneSectionCur!=NULL)  lMaxS=lLaneSectionNext->GetS()-lLaneSectionCur->GetS();
			LaneVisibility *lLaneVisibilityPrev = GetRealLaneVisibility(mSelection[0],mSelection[1],mSelection[2],mSelection[3]-1);
			LaneVisibility *lLaneVisibilityNext = GetRealLaneVisibility(mSelection[0],mSelection[1],mSelection[2],mSelection[3]+1);
			if(lLaneVisibilityPrev!=NULL) lMinS=lLaneVisibilityPrev->GetS();
			if(lLaneVisibilityNext!=NULL) lMaxS=lLaneVisibilityNext->GetS();
			
			if(lLaneVisibility!=NULL) emit LaneVisibilitySelected(lLaneVisibility, lMinS, lMaxS);
			break;
		}
	case LANE_SPEED:
		{
			LaneSpeed *lLaneSpeed = GetRealLaneSpeed();
			
			double lMinS=0;
			double lMaxS=GetRealRoad(mSelection[0])->GetRoadLength();
			LaneSection *lLaneSectionCur = GetRealLaneSection(mSelection[0],mSelection[1]);
			LaneSection *lLaneSectionNext = GetRealLaneSection(mSelection[0],mSelection[1]+1);
			if(lLaneSectionNext!=NULL && lLaneSectionCur!=NULL)  lMaxS=lLaneSectionNext->GetS()-lLaneSectionCur->GetS();
			LaneSpeed *lLaneSpeedPrev = GetRealLaneSpeed(mSelection[0],mSelection[1],mSelection[2],mSelection[3]-1);
			LaneSpeed *lLaneSpeedNext = GetRealLaneSpeed(mSelection[0],mSelection[1],mSelection[2],mSelection[3]+1);
			if(lLaneSpeedPrev!=NULL) lMinS=lLaneSpeedPrev->GetS();
			if(lLaneSpeedNext!=NULL) lMaxS=lLaneSpeedNext->GetS();
			
			if(lLaneSpeed!=NULL) emit LaneSpeedSelected(lLaneSpeed, lMinS, lMaxS);
			break;
		}
	case LANE_ACCESS:
		{
			LaneAccess *lLaneAccess = GetRealLaneAccess();
			
			double lMinS=0;
			double lMaxS=GetRealRoad(mSelection[0])->GetRoadLength();
			LaneSection *lLaneSectionCur = GetRealLaneSection(mSelection[0],mSelection[1]);
			LaneSection *lLaneSectionNext = GetRealLaneSection(mSelection[0],mSelection[1]+1);
			if(lLaneSectionNext!=NULL && lLaneSectionCur!=NULL)  lMaxS=lLaneSectionNext->GetS()-lLaneSectionCur->GetS();
			LaneAccess *lLaneAccessPrev = GetRealLaneAccess(mSelection[0],mSelection[1],mSelection[2],mSelection[3]-1);
			LaneAccess *lLaneAccessNext = GetRealLaneAccess(mSelection[0],mSelection[1],mSelection[2],mSelection[3]+1);
			if(lLaneAccessPrev!=NULL) lMinS=lLaneAccessPrev->GetS();
			if(lLaneAccessNext!=NULL) lMaxS=lLaneAccessNext->GetS();
			
			if(lLaneAccess!=NULL) emit LaneAccessSelected(lLaneAccess, lMinS, lMaxS);
			break;
		}
	case LANE_HEIGHT:
		{
			LaneHeight *lLaneHeight = GetRealLaneHeight();
			
			double lMinS=0;
			double lMaxS=GetRealRoad(mSelection[0])->GetRoadLength();
			LaneSection *lLaneSectionCur = GetRealLaneSection(mSelection[0],mSelection[1]);
			LaneSection *lLaneSectionNext = GetRealLaneSection(mSelection[0],mSelection[1]+1);
			if(lLaneSectionNext!=NULL && lLaneSectionCur!=NULL)  lMaxS=lLaneSectionNext->GetS()-lLaneSectionCur->GetS();
			LaneHeight *lLaneHeightPrev = GetRealLaneHeight(mSelection[0],mSelection[1],mSelection[2],mSelection[3]-1);
			LaneHeight *lLaneHeightNext = GetRealLaneHeight(mSelection[0],mSelection[1],mSelection[2],mSelection[3]+1);
			if(lLaneHeightPrev!=NULL) lMinS=lLaneHeightPrev->GetS();
			if(lLaneHeightNext!=NULL) lMaxS=lLaneHeightNext->GetS();
			
			if(lLaneHeight!=NULL) emit LaneHeightSelected(lLaneHeight, lMinS, lMaxS);
			break;
		}
	case OBJECT:
		{
			Object *lObject = GetRealObject();
			if(lObject!=NULL) emit ObjectSelected(lObject);
			break;
		}
	case SIGNAL:
		{
			Signal *lSignal = GetRealSignal();
			if(lSignal!=NULL) emit SignalSelected(lSignal);
			break;
		}
	case CONTROLLER:
		//ADD CONTROLLER CODE HERE
		break;
	case JUNCTION:
		{
			Junction *lJunction = GetRealJunction();
			if(lJunction!=NULL) emit JunctionSelected(lJunction);
			break;
		}
	case JUNCTION_CONNECTION:
		{
			JunctionConnection *lJunctionConnection = GetRealJunctionConnection();
			if(lJunctionConnection!=NULL) emit JunctionConnectionSelected(lJunctionConnection);
			break;
		}
	case JUNCTION_LANE_LINK:
		{
			JunctionLaneLink *lJunctionLaneLink = GetRealJunctionLaneLink();
			if(lJunctionLaneLink!=NULL) emit JunctionLaneLinkSelected(lJunctionLaneLink);
			break;
		}
	case JUNCTION_PRIORITY:
		{
			JunctionPriorityRoad *lJunctionPriority = GetRealJunctionPriority();
			if(lJunctionPriority!=NULL) emit JunctionPrioritySelected(lJunctionPriority);
			break;
		}
	case JUNCTION_CONTROLLER:
		{
			JunctionController *lJunctionController = GetRealJunctionController();
			if(lJunctionController!=NULL) emit JunctionControllerSelected(lJunctionController);
			break;
		}
	default:
		{
			emit NothingSelected();
			break;
		}
	}
}

/**
 * Method called when one of the rods is wiether changed in the settings panel or a new tree item is added
 */
void RoadTree::OnCurrentRoadChanged(bool geometryChanged)
{
	// Recaluclate the geometry records of the road
	if(geometryChanged) 
		GetRealRoad()->RecalculateGeometry();

	// Emit a road changed signal, so the 3D viewport could redraw the new road
	emit RoadRecalculated(mSelection[0]);
}

