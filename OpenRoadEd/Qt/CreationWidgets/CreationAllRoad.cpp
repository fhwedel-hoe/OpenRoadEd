#include "CreationAllRoad.h"
#include "moc_CreationAllRoad.cpp"

#include "../../OpenDrive/Road.h"

/**
 * Initializes the creation panel
 */
CreationAllRoad::CreationAllRoad(QWidget *parent)
{
	// Resets the opendrive, road tree and OSG object pointers
	mOpenDrive=NULL;
	mRoadTree=NULL;
	mOsgMain=NULL;

	
	// Main vertical layout
	QVBoxLayout *mainLayout = new QVBoxLayout;

	//-------------------------------------------------
	// Group for settings
	mRoadCreation = new QGroupBox;
	mRoadCreation->setSizePolicy(QSizePolicy::Maximum,QSizePolicy::Maximum);
	mRoadCreation->setTitle(tr("Road creation"));

	mCreateRoad = new QPushButton("Road", this);

	mCreateRoadType = new QToolButton(this);
	mCreateRoadType->setFocusPolicy(Qt::StrongFocus);
	mCreateRoadType->setIcon(QIcon("Resources/Icons/RoadType.png"));
	mCreateRoadType->setToolTip("Road type");
	mCreateGeometryLine = new QToolButton(this);
	mCreateGeometryLine->setFocusPolicy(Qt::StrongFocus);
	mCreateGeometryLine->setIcon(QIcon("Resources/Icons/Line.png"));
	mCreateGeometryLine->setToolTip("Line");
	mCreateGeometryTurn = new QToolButton(this);
	mCreateGeometryTurn->setFocusPolicy(Qt::StrongFocus);
	mCreateGeometryTurn->setIcon(QIcon("Resources/Icons/Turn.png"));
	mCreateGeometryTurn->setToolTip("Turn");
	mCreateElevation = new QToolButton(this);
	mCreateElevation->setFocusPolicy(Qt::StrongFocus);
	mCreateElevation->setIcon(QIcon("Resources/Icons/Elevation.png"));
	mCreateElevation->setToolTip("Elevation");
	mCreateSuperElevation = new QToolButton(this);
	mCreateSuperElevation->setFocusPolicy(Qt::StrongFocus);
	mCreateSuperElevation->setIcon(QIcon("Resources/Icons/SuperElevation.png"));
	mCreateSuperElevation->setToolTip("SuperElevation");
	mCreateCrossfall = new QToolButton(this);
	mCreateCrossfall->setFocusPolicy(Qt::StrongFocus);
	mCreateCrossfall->setIcon(QIcon("Resources/Icons/Crossfall.png"));
	mCreateCrossfall->setToolTip("Crossfall");
	mCreateLaneSection = new QToolButton(this);
	mCreateLaneSection->setFocusPolicy(Qt::StrongFocus);
	mCreateLaneSection->setIcon(QIcon("Resources/Icons/LaneSection.png"));
	mCreateLaneSection->setToolTip("Lane section");
	mCreateObject = new QToolButton(this);
	mCreateObject->setFocusPolicy(Qt::StrongFocus);
	mCreateObject->setIcon(QIcon("Resources/Icons/Object.png"));
	mCreateObject->setToolTip("Object");
	mCreateSignal = new QToolButton(this);
	mCreateSignal->setFocusPolicy(Qt::StrongFocus);
	mCreateSignal->setIcon(QIcon("Resources/Icons/Signal.png"));
	mCreateSignal->setToolTip("Signal");

	// Form Layout inside group
	QVBoxLayout *roadButtonsVLayout = new QVBoxLayout;

	QHBoxLayout *roadButtonsHLayout1 = new QHBoxLayout;
	roadButtonsHLayout1->addWidget(mCreateRoad);

	QHBoxLayout *roadButtonsHLayout2 = new QHBoxLayout;
	roadButtonsHLayout2->addWidget(mCreateRoadType);
	roadButtonsHLayout2->addWidget(mCreateGeometryLine);
	roadButtonsHLayout2->addWidget(mCreateGeometryTurn);
	roadButtonsHLayout2->addWidget(mCreateElevation);
	roadButtonsHLayout2->addWidget(mCreateSuperElevation);
	roadButtonsHLayout2->addWidget(mCreateCrossfall);
	roadButtonsHLayout2->addWidget(mCreateLaneSection);
	roadButtonsHLayout2->addWidget(mCreateObject);
	roadButtonsHLayout2->addWidget(mCreateSignal);

	roadButtonsVLayout->addLayout(roadButtonsHLayout1);
	roadButtonsVLayout->addLayout(roadButtonsHLayout2);

	mRoadCreation->setLayout(roadButtonsVLayout);
	//-------------------------------------------------
	// LANE CREATION

	mLaneCreation = new QGroupBox;
	mLaneCreation->setSizePolicy(QSizePolicy::Maximum,QSizePolicy::Maximum);
	mLaneCreation->setTitle(tr("Lane creation"));

	mCreateLaneLeft = new QPushButton("Left lane", this);;
	mCreateLaneRight = new QPushButton("Right lane", this);

	mCreateLaneWidth = new QToolButton(this);
	mCreateLaneWidth->setFocusPolicy(Qt::StrongFocus);
	mCreateLaneWidth->setIcon(QIcon("Resources/Icons/LaneWidth.png"));
	mCreateLaneWidth->setToolTip("Lane width");
	mCreateLaneRoadMark = new QToolButton(this);
	mCreateLaneRoadMark->setFocusPolicy(Qt::StrongFocus);
	mCreateLaneRoadMark->setIcon(QIcon("Resources/Icons/LaneRoadMark.png"));
	mCreateLaneRoadMark->setToolTip("Lane road mark");
	mCreateLaneMaterial = new QToolButton(this);
	mCreateLaneMaterial->setFocusPolicy(Qt::StrongFocus);
	mCreateLaneMaterial->setIcon(QIcon("Resources/Icons/LaneMaterial.png"));
	mCreateLaneMaterial->setToolTip("Lane material");
	mCreateLaneVisibility = new QToolButton(this);
	mCreateLaneVisibility->setFocusPolicy(Qt::StrongFocus);
	mCreateLaneVisibility->setIcon(QIcon("Resources/Icons/LaneVisibility.png"));
	mCreateLaneVisibility->setToolTip("Visibility");
	mCreateLaneSpeed = new QToolButton(this);
	mCreateLaneSpeed->setFocusPolicy(Qt::StrongFocus);
	mCreateLaneSpeed->setIcon(QIcon("Resources/Icons/LaneSpeed.png"));
	mCreateLaneSpeed->setToolTip("Lane speed");
	mCreateLaneAccess = new QToolButton(this);
	mCreateLaneAccess->setFocusPolicy(Qt::StrongFocus);
	mCreateLaneAccess->setIcon(QIcon("Resources/Icons/LaneAccess.png"));
	mCreateLaneAccess->setToolTip("Lane access");
	mCreateLaneHeight = new QToolButton(this);
	mCreateLaneHeight->setFocusPolicy(Qt::StrongFocus);
	mCreateLaneHeight->setIcon(QIcon("Resources/Icons/LaneHeight.png"));
	mCreateLaneHeight->setToolTip("Lane height");

	// Form Layout inside group
	QVBoxLayout *laneButtonsVLayout = new QVBoxLayout;

	QHBoxLayout *laneButtonsHLayout1 = new QHBoxLayout;
	laneButtonsHLayout1->addWidget(mCreateLaneLeft);
	laneButtonsHLayout1->addWidget(mCreateLaneRight);

	QHBoxLayout *laneButtonsHLayout2 = new QHBoxLayout;
	laneButtonsHLayout2->addWidget(mCreateLaneWidth);
	laneButtonsHLayout2->addWidget(mCreateLaneRoadMark);
	laneButtonsHLayout2->addWidget(mCreateLaneMaterial);
	laneButtonsHLayout2->addWidget(mCreateLaneVisibility);
	laneButtonsHLayout2->addWidget(mCreateLaneSpeed);
	laneButtonsHLayout2->addWidget(mCreateLaneAccess);
	laneButtonsHLayout2->addWidget(mCreateLaneHeight);

	laneButtonsVLayout->addLayout(laneButtonsHLayout1);
	laneButtonsVLayout->addLayout(laneButtonsHLayout2);

	mLaneCreation->setLayout(laneButtonsVLayout);
	//-------------------------------------------------


	// Form Layout inside group
	QHBoxLayout *groupHLayout = new QHBoxLayout;

	groupHLayout->addWidget(mRoadCreation);
	groupHLayout->addWidget(mLaneCreation);
	//-------------------------------------------------

	mainLayout->addLayout(groupHLayout);
	mainLayout->setAlignment(Qt::AlignLeft);
	setLayout(mainLayout);

	// Connections of the interface elements
	connect(mCreateRoad, SIGNAL(clicked(bool)), this, SLOT(CreateRoadPressed()));
	connect(mCreateRoadType, SIGNAL(clicked(bool)), this, SLOT(CreateRoadTypePressed()));
	connect(mCreateGeometryLine, SIGNAL(clicked(bool)), this, SLOT(CreateGeometryLinePressed()));
	connect(mCreateGeometryTurn, SIGNAL(clicked(bool)), this, SLOT(CreateGeometryTurnPressed()));
	connect(mCreateElevation, SIGNAL(clicked(bool)), this, SLOT(CreateElevationPressed()));
	connect(mCreateSuperElevation, SIGNAL(clicked(bool)), this, SLOT(CreateSuperElevationPressed()));
	connect(mCreateCrossfall, SIGNAL(clicked(bool)), this, SLOT(CreateCrossfallPressed()));
	connect(mCreateLaneSection, SIGNAL(clicked(bool)), this, SLOT(CreateLaneSectionPressed()));
	connect(mCreateObject, SIGNAL(clicked(bool)), this, SLOT(CreateObjectPressed()));
	connect(mCreateSignal, SIGNAL(clicked(bool)), this, SLOT(CreateSignalPressed()));

	connect(mCreateLaneLeft, SIGNAL(clicked(bool)), this, SLOT(CreateLaneLeftPressed()));
	connect(mCreateLaneRight, SIGNAL(clicked(bool)), this, SLOT(CreateLaneRightPressed()));
	connect(mCreateLaneWidth, SIGNAL(clicked(bool)), this, SLOT(CreateLaneWidthPressed()));
	connect(mCreateLaneRoadMark, SIGNAL(clicked(bool)), this, SLOT(CreateLaneRoadMarkPressed()));
	connect(mCreateLaneMaterial, SIGNAL(clicked(bool)), this, SLOT(CreateLaneMaterialPressed()));
	connect(mCreateLaneVisibility, SIGNAL(clicked(bool)), this, SLOT(CreateLaneVisibilityPressed()));
	connect(mCreateLaneSpeed, SIGNAL(clicked(bool)), this, SLOT(CreateLaneSpeedPressed()));
	connect(mCreateLaneAccess, SIGNAL(clicked(bool)), this, SLOT(CreateLaneAccessPressed()));
	connect(mCreateLaneHeight, SIGNAL(clicked(bool)), this, SLOT(CreateLaneHeightPressed()));
}

/**
 * Saves the references to the OpenDrive, road tree and OSG object
 */
void CreationAllRoad::Init(OpenDrive *openDrive, RoadTree *roadTree, OSGMain *osgMain)
{
	mOpenDrive=openDrive;
	mRoadTree=roadTree;
	mOsgMain=osgMain;
}

/**
 * Enables or disables groups of buttons when they cannot be used
 * due to an unrelated item selected in the road tree
 * 
 * @param wholeGroup Disable the whole group or just a part
 * @param roadItems Disable road item buttons
 * @param laneGroup Disable lane group
 * @param laneItems Disable lane item buttons
 */
void CreationAllRoad::SetEnabled(bool wholeGroup, bool roadItems, bool laneGroup, bool laneItems)
{
	mRoadCreation->setEnabled(wholeGroup);

	mCreateRoadType->setEnabled(roadItems);
	mCreateGeometryLine->setEnabled(roadItems);
	mCreateGeometryTurn->setEnabled(roadItems);
	mCreateElevation->setEnabled(roadItems);
	mCreateSuperElevation->setEnabled(roadItems);
	mCreateCrossfall->setEnabled(roadItems);
	mCreateLaneSection->setEnabled(roadItems);
	mCreateObject->setEnabled(roadItems);
	mCreateSignal->setEnabled(roadItems);

	mLaneCreation->setEnabled(laneGroup);

	mCreateLaneWidth->setEnabled(laneItems);
	mCreateLaneRoadMark->setEnabled(laneItems);
	mCreateLaneMaterial->setEnabled(laneItems);
	mCreateLaneVisibility->setEnabled(laneItems);
	mCreateLaneSpeed->setEnabled(laneItems);
	mCreateLaneAccess->setEnabled(laneItems);
	mCreateLaneHeight->setEnabled(laneItems);
}

/**
 * Methods called when one of the creation buttons is pressed
 */
void CreationAllRoad::CreateRoadPressed()
{
	// Creates a new record in openDrive structure and returns it's index
	unsigned int index=mOpenDrive->AddRoad("", 0, "", "-1");
	// Add the road to the road tree
	mRoadTree->AddRoad(index, true);

	// Cleares the keyboard focus, so pressing space to switch to camera mode won't create a record
	mCreateRoad->clearFocus();
}

void CreationAllRoad::CreateRoadTypePressed()
{
	Road *lRoad=NULL;
	RoadType *lRoadType=NULL;
	unsigned int index=0;

	// Get the current selection
	Selection *lCurSelection = mRoadTree->GetSelection();
	RoadTreeItemType lType = lCurSelection->GetType();
	// If another road type is selected - duplicate it
	if(lType == ROAD_TYPE)
	{
		// Clone the selected road type
		lRoad = mRoadTree->GetRealRoad();
		index = lRoad->CloneRoadType((*lCurSelection)[1]);
		// Redraws the road to reflect the changes
		mOsgMain->RedrawRoad(lCurSelection->GetIndex(0));
		// Add new road type to the road tree
		mRoadTree->AddRoadType((*lCurSelection)[0], index, true);
		//emit RoadChanged(false);
	}
	// If something else is selected - duplicate the last road type or create a new one if
	// no road types exist
	else if(lType == ROAD || lType == ROAD_TYPE_CONTAINER || (lType>ROAD && lType<CONTROLLER_CONTAINER))
	{
		// Get last road type
		lRoad = mRoadTree->GetRealRoad();
		lRoadType = lRoad->GetLastRoadType();
		// Duplicate it if it exists
		if(lRoadType) index = lRoad->CloneRoadType(lRoad->GetRoadTypeCount()-1);
		// else create a blank one
		else index = lRoad->AddRoadType(0,"Default");
		// Redraws the road to reflect the changes
		mOsgMain->RedrawRoad(lCurSelection->GetIndex(0));
		// Add new road type to the road tree
		mRoadTree->AddRoadType((*lCurSelection)[0], index, true);
		//emit RoadChanged(false);
	}

	// Cleares the keyboard focus, so pressing space to switch to camera mode won't create a record
	mCreateRoadType->clearFocus();
}
void CreationAllRoad::CreateGeometryLinePressed()
{
	// Read the first record creation method to see how it works

	Road *lRoad=NULL;
	GeometryBlock *lGeometryLast=NULL;
	GeometryBlock *lGeometryNew=NULL;
	unsigned int index=0;

	Selection *lCurSelection = mRoadTree->GetSelection();
	RoadTreeItemType lType = lCurSelection->GetType();
	if(lType == GEOMETRY_LINE || lType == GEOMETRY_TURN || lType == ROAD || lType == GEOMETRY_CONTAINER || (lType>ROAD && lType<CONTROLLER_CONTAINER))
	{
		double lNewS=0;
		double lNewX=0;
		double lNewY=0;
		double lNewHdg=0;

		lRoad = mRoadTree->GetRealRoad();
		lGeometryLast = lRoad->GetLastGeometryBlock();
		if(lGeometryLast!=NULL) 
		{	
			lGeometryLast->GetLastCoords(lNewS, lNewX, lNewY, lNewHdg);
		}

		index = lRoad->AddGeometryBlock();
		lGeometryNew = lRoad->GetGeometryBlock(index);

		lGeometryNew->AddGeometryLine(lNewS, lNewX, lNewY, lNewHdg, 50.0);
		lRoad->SetRoadLength(lRoad->GetRoadLength()+lGeometryNew->GetBlockLength());

		mOsgMain->RedrawRoad(lCurSelection->GetIndex(0));

		mRoadTree->AddGeometry((*lCurSelection)[0], index, true);

		//emit RoadChanged(true);
	}

	mCreateGeometryLine->clearFocus();
}
void CreationAllRoad::CreateGeometryTurnPressed()
{
	// Read the first record creation method to see how it works

	Road *lRoad=NULL;
	GeometryBlock *lGeometryLast=NULL;
	GeometryBlock *lGeometryNew=NULL;
	unsigned int index=0;

	Selection *lCurSelection = mRoadTree->GetSelection();
	RoadTreeItemType lType = lCurSelection->GetType();
	if(lType == GEOMETRY_LINE || lType == GEOMETRY_TURN || lType == ROAD || lType == GEOMETRY_CONTAINER || (lType>ROAD && lType<CONTROLLER_CONTAINER))
	{
		double lNewS=0;
		double lNewX=0;
		double lNewY=0;
		double lNewHdg=0;

		lRoad = mRoadTree->GetRealRoad();
		lGeometryLast = lRoad->GetLastGeometryBlock();
		if(lGeometryLast) 
		{	
			lGeometryLast->GetLastCoords(lNewS, lNewX, lNewY, lNewHdg);
		}

		index = lRoad->AddGeometryBlock();
		lGeometryNew = lRoad->GetGeometryBlock(index);


		lGeometryNew->AddGeometrySpiral(lNewS, lNewX, lNewY, lNewHdg, 20.0, 0,0.003);

		lGeometryNew->GetLastCoords(lNewS, lNewX, lNewY, lNewHdg);
		lGeometryNew->AddGeometryArc(lNewS, lNewX, lNewY, lNewHdg, 30.0, 0.003);

		lGeometryNew->GetLastCoords(lNewS, lNewX, lNewY, lNewHdg);
		lGeometryNew->AddGeometrySpiral(lNewS, lNewX, lNewY, lNewHdg, 20.0, 0.003,0);
		lRoad->SetRoadLength(lRoad->GetRoadLength()+lGeometryNew->GetBlockLength());

		mOsgMain->RedrawRoad(lCurSelection->GetIndex(0));

		mRoadTree->AddGeometry((*lCurSelection)[0], index, true);
		

		//emit RoadChanged(true);
	}

	mCreateGeometryTurn->clearFocus();
}
void CreationAllRoad::CreateElevationPressed()
{
	// Read the first record creation method to see how it works

	Road *lRoad=NULL;
	Elevation *lElevation=NULL;
	unsigned int index=0;

	Selection *lCurSelection = mRoadTree->GetSelection();
	RoadTreeItemType lType = lCurSelection->GetType();
	if(lType == ELEVATION)
	{
		lRoad = mRoadTree->GetRealRoad();
		index = lRoad->CloneElevation((*lCurSelection)[1]);
		mOsgMain->RedrawRoad(lCurSelection->GetIndex(0));
		mRoadTree->AddElevation((*lCurSelection)[0], index, true);
		//emit RoadChanged(false);
	}
	else if(lType == ROAD  || lType == ELEVATION_CONTAINER || (lType>ROAD && lType<CONTROLLER_CONTAINER))
	{
		lRoad = mRoadTree->GetRealRoad();
		lElevation = lRoad->GetLastElevation();
		if(lElevation) index = lRoad->CloneElevation(lRoad->GetElevationCount()-1);
		else index = lRoad->AddElevation(0.0,0.0,0.0,0.0,0.0);
		mOsgMain->RedrawRoad(lCurSelection->GetIndex(0));
		mRoadTree->AddElevation((*lCurSelection)[0], index, true);
		//emit RoadChanged(false);
	}

	mCreateElevation->clearFocus();
}
void CreationAllRoad::CreateSuperElevationPressed()
{
	// Read the first record creation method to see how it works

	Road *lRoad=NULL;
	SuperElevation *lSuperElevation=NULL;
	unsigned int index=0;

	Selection *lCurSelection = mRoadTree->GetSelection();
	RoadTreeItemType lType = lCurSelection->GetType();
	if(lType == SUPERELEVATION)
	{
		lRoad = mRoadTree->GetRealRoad();
		index = lRoad->CloneSuperElevation((*lCurSelection)[1]);
		mOsgMain->RedrawRoad(lCurSelection->GetIndex(0));
		mRoadTree->AddSuperElevation((*lCurSelection)[0], index, true);
		//emit RoadChanged(false);
	}
	else if(lType == ROAD  || lType == SUPERELEVATION_CONTAINER || (lType>ROAD && lType<CONTROLLER_CONTAINER))
	{
		lRoad = mRoadTree->GetRealRoad();
		lSuperElevation = lRoad->GetLastSuperElevation();
		if(lSuperElevation) index = lRoad->CloneSuperElevation(lRoad->GetSuperElevationCount()-1);
		else index = lRoad->AddSuperElevation(0.0,0.0,0.0,0.0,0.0);
		mOsgMain->RedrawRoad(lCurSelection->GetIndex(0));
		mRoadTree->AddSuperElevation((*lCurSelection)[0], index, true);
		//emit RoadChanged(false);
	}

	mCreateSuperElevation->clearFocus();
}
void CreationAllRoad::CreateCrossfallPressed()
{
	// Read the first record creation method to see how it works

	Road *lRoad=NULL;
	Crossfall *lCrossfall=NULL;
	unsigned int index=0;

	Selection *lCurSelection = mRoadTree->GetSelection();
	RoadTreeItemType lType = lCurSelection->GetType();
	if(lType == CROSSFALL)
	{
		lRoad = mRoadTree->GetRealRoad();
		index = lRoad->CloneCrossfall((*lCurSelection)[1]);
		mOsgMain->RedrawRoad(lCurSelection->GetIndex(0));
		mRoadTree->AddCrossfall((*lCurSelection)[0], index, true);
		//emit RoadChanged(false);
	}
	else if(lType == ROAD || lType == CROSSFALL_CONTAINER || (lType>ROAD && lType<CONTROLLER_CONTAINER))
	{
		lRoad = mRoadTree->GetRealRoad();
		lCrossfall = lRoad->GetLastCrossfall();
		if(lCrossfall) index = lRoad->CloneCrossfall(lRoad->GetCrossfallCount()-1);
		else index = lRoad->AddCrossfall("both", 0.0,0.0,0.0,0.0,0.0);
		mOsgMain->RedrawRoad(lCurSelection->GetIndex(0));
		mRoadTree->AddCrossfall((*lCurSelection)[0], index, true);
		//emit RoadChanged(false);
	}
	mCreateCrossfall->clearFocus();
}
void CreationAllRoad::CreateLaneSectionPressed()
{
	// Read the first record creation method to see how it works
	// This record also clones the last of all the children record types 
	// It has to go through all the child records per type, finding the last one

	Road *lRoad=NULL;
	LaneSection *lLaneSection=NULL;
	unsigned int index=0;

	Selection *lCurSelection = mRoadTree->GetSelection();
	RoadTreeItemType lType = lCurSelection->GetType();
	if(lType == LANE_SECTION || (lType>LANE_SECTION && lType<OBJECT_CONTAINER))
	{
		lRoad = mRoadTree->GetRealRoad();
		index = lRoad->CloneLaneSectionEnd((*lCurSelection)[1]);
		lLaneSection=lRoad->GetLastAddedLaneSection();

		mOsgMain->RedrawRoad(lCurSelection->GetIndex(0));

		RTILaneSection *lTreeLaneSection=NULL;
		mRoadTree->AddLaneSection((*lCurSelection)[0], index, lTreeLaneSection, true);

		//========== LANES ==========//
		for(unsigned int iLanes=0; iLanes<lLaneSection->GetLaneCount(); iLanes++)
		{
			RTILane *lTreeLane=NULL;

			int lLaneSide = lLaneSection->GetLane(iLanes)->GetSide();
			lTreeLaneSection->AddLane(iLanes, lTreeLane, lLaneSide);

			//--- LANE WIDTHS ---//
			for(unsigned int iLaneWidth=0; iLaneWidth<lLaneSection->GetLane(iLanes)->GetLaneWidthCount(); iLaneWidth++)
			{
				lTreeLane->AddLaneWidth(iLaneWidth);
			}
			//--- LANE ROAD MARKS ---//
			for(unsigned int iLaneRoadMark=0; iLaneRoadMark<lLaneSection->GetLane(iLanes)->GetLaneRoadMarkCount(); iLaneRoadMark++)
			{
				lTreeLane->AddLaneRoadMark(iLaneRoadMark);
			}
			//--- LANE MATERIAL ---//
			for(unsigned int iLaneMaterial=0; iLaneMaterial<lLaneSection->GetLane(iLanes)->GetLaneMaterialCount(); iLaneMaterial++)
			{
				lTreeLane->AddLaneMaterial(iLaneMaterial);
			}
			//--- LANE VISIBILITY ---//
			for(unsigned int iLaneVisibility=0; iLaneVisibility<lLaneSection->GetLane(iLanes)->GetLaneVisibilityCount(); iLaneVisibility++)
			{
				lTreeLane->AddLaneVisibility(iLaneVisibility);
			}
			//--- LANE SPEED ---//
			for(unsigned int iLaneSpeed=0; iLaneSpeed<lLaneSection->GetLane(iLanes)->GetLaneSpeedCount(); iLaneSpeed++)
			{
				lTreeLane->AddLaneSpeed(iLaneSpeed);
			}
			//--- LANE ACCESS ---//
			for(unsigned int iLaneAccess=0; iLaneAccess<lLaneSection->GetLane(iLanes)->GetLaneAccessCount(); iLaneAccess++)
			{
				lTreeLane->AddLaneAccess(iLaneAccess);
			}
			//--- LANE HEIGHT ---//
			for(unsigned int iLaneHeight=0; iLaneHeight<lLaneSection->GetLane(iLanes)->GetLaneHeightCount(); iLaneHeight++)
			{
				lTreeLane->AddLaneHeight(iLaneHeight);
			}
		}

		//emit RoadChanged(false);
	}
	else if(lType == ROAD  || lType == LANE_SECTION_CONTAINER || (lType>ROAD && lType<LANE_SECTION_CONTAINER) || (lType>LANE_HEIGHT && lType<CONTROLLER_CONTAINER))
	{
		lRoad = mRoadTree->GetRealRoad();
		lLaneSection = lRoad->GetLastLaneSection();
		if(lLaneSection) 
		{
			index = lRoad->CloneLaneSectionEnd(lRoad->GetLaneSectionCount()-1);
			lLaneSection=lRoad->GetLastAddedLaneSection();

			mOsgMain->RedrawRoad(lCurSelection->GetIndex(0));

			RTILaneSection *lTreeLaneSection=NULL;
			mRoadTree->AddLaneSection((*lCurSelection)[0], index, lTreeLaneSection, true);

			//========== LANES ==========//
			for(unsigned int iLanes=0; iLanes<lLaneSection->GetLaneCount(); iLanes++)
			{
				RTILane *lTreeLane=NULL;

				int lLaneSide = lLaneSection->GetLane(iLanes)->GetSide();
				lTreeLaneSection->AddLane(iLanes, lTreeLane, lLaneSide);

				//--- LANE WIDTHS ---//
				for(unsigned int iLaneWidth=0; iLaneWidth<lLaneSection->GetLane(iLanes)->GetLaneWidthCount(); iLaneWidth++)
				{
					lTreeLane->AddLaneWidth(iLaneWidth);
				}
				//--- LANE ROAD MARKS ---//
				for(unsigned int iLaneRoadMark=0; iLaneRoadMark<lLaneSection->GetLane(iLanes)->GetLaneRoadMarkCount(); iLaneRoadMark++)
				{
					lTreeLane->AddLaneRoadMark(iLaneRoadMark);
				}
				//--- LANE MATERIAL ---//
				for(unsigned int iLaneMaterial=0; iLaneMaterial<lLaneSection->GetLane(iLanes)->GetLaneMaterialCount(); iLaneMaterial++)
				{
					lTreeLane->AddLaneMaterial(iLaneMaterial);
				}
				//--- LANE VISIBILITY ---//
				for(unsigned int iLaneVisibility=0; iLaneVisibility<lLaneSection->GetLane(iLanes)->GetLaneVisibilityCount(); iLaneVisibility++)
				{
					lTreeLane->AddLaneVisibility(iLaneVisibility);
				}
				//--- LANE SPEED ---//
				for(unsigned int iLaneSpeed=0; iLaneSpeed<lLaneSection->GetLane(iLanes)->GetLaneSpeedCount(); iLaneSpeed++)
				{
					lTreeLane->AddLaneSpeed(iLaneSpeed);
				}
				//--- LANE ACCESS ---//
				for(unsigned int iLaneAccess=0; iLaneAccess<lLaneSection->GetLane(iLanes)->GetLaneAccessCount(); iLaneAccess++)
				{
					lTreeLane->AddLaneAccess(iLaneAccess);
				}
				//--- LANE HEIGHT ---//
				for(unsigned int iLaneHeight=0; iLaneHeight<lLaneSection->GetLane(iLanes)->GetLaneHeightCount(); iLaneHeight++)
				{
					lTreeLane->AddLaneHeight(iLaneHeight);
				}
			}

			//emit RoadChanged(false);

		}
		else 
		{
			index = lRoad->AddLaneSection(0.0);

			// CENTER
			lLaneSection = lRoad->GetLastAddedLaneSection();
			unsigned int centerLaneIndex = lLaneSection->AddLane(0,0,"driving", false);
			Lane *lLane=lLaneSection->GetLastAddedLane();
			unsigned int widthIndex = lLane->AddWidthRecord(0.0,0.0,0.0,0.0,0.0);
			// LEFT
			unsigned int leftLaneIndex = lLaneSection->AddLane(1,1,"driving", false);
			lLane=lLaneSection->GetLastAddedLane();
			unsigned int widthIndexL = lLane->AddWidthRecord(0.0,3.0,0.0,0.0,0.0);
			// RIGHT
			unsigned int rightLaneIndex = lLaneSection->AddLane(-1,-1,"driving", false);
			lLane=lLaneSection->GetLastAddedLane();
			unsigned int widthIndexR = lLane->AddWidthRecord(0.0,3.0,0.0,0.0,0.0);
			
			
			mOsgMain->RedrawRoad(lCurSelection->GetIndex(0));


			mRoadTree->AddLaneSection((*lCurSelection)[0], index, true);

			mRoadTree->AddLaneCenter((*lCurSelection)[0], index, centerLaneIndex, false);
			mRoadTree->AddLaneWidth((*lCurSelection)[0],index, centerLaneIndex, widthIndex, false);

			
			mRoadTree->AddLaneLeft((*lCurSelection)[0], index, leftLaneIndex, false);
			mRoadTree->AddLaneWidth((*lCurSelection)[0],index, leftLaneIndex, widthIndexL, false);

			mRoadTree->AddLaneRight((*lCurSelection)[0], index, rightLaneIndex, false);
			mRoadTree->AddLaneWidth((*lCurSelection)[0],index, rightLaneIndex, widthIndexR, false);

			//emit RoadChanged(false);
		}
	}

	mCreateLaneSection->clearFocus();
}
void CreationAllRoad::CreateObjectPressed()
{
	// Not implemented yet
}
void CreationAllRoad::CreateSignalPressed()
{
	// Not implemented yet
}



void CreationAllRoad::CreateLaneLeftPressed()
{
	// Read the first record creation method to see how it works

	LaneSection *lLaneSection=NULL;
	Lane *lLane=NULL;
	unsigned int index=0;

	Selection *lCurSelection = mRoadTree->GetSelection();
	RoadTreeItemType lType = lCurSelection->GetType();
	if(lType == LANE || lType == LANE_SECTION || (lType>LANE_SECTION && lType<OBJECT_CONTAINER))
	{
		lLaneSection = mRoadTree->GetRealLaneSection();
		lLane = lLaneSection->GetLastLeftLane();
		if(lLane) index = lLaneSection->AddLane(1,(lLaneSection->GetLeftLaneCount()+1),lLane->GetType(), false);
		else index = lLaneSection->AddLane(1,1,"driving", false);

		lLane=lLaneSection->GetLastAddedLane();
		unsigned int widthIndex = lLane->AddWidthRecord(0.0,3.0,0.0,0.0,0.0);

		mOsgMain->RedrawRoad(lCurSelection->GetIndex(0));

		mRoadTree->AddLaneLeft((*lCurSelection)[0], (*lCurSelection)[1], index, true);
		mRoadTree->AddLaneWidth((*lCurSelection)[0],(*lCurSelection)[1], index, widthIndex, false);

		//emit RoadChanged(false);
	}

	mCreateLaneLeft->clearFocus();
}

void CreationAllRoad::CreateLaneRightPressed()
{
	// Read the first record creation method to see how it works

	LaneSection *lLaneSection=NULL;
	Lane *lLane=NULL;
	unsigned int index=0;

	Selection *lCurSelection = mRoadTree->GetSelection();
	RoadTreeItemType lType = lCurSelection->GetType();
	if(lType == LANE || lType == LANE_SECTION || (lType>LANE_SECTION && lType<OBJECT_CONTAINER))
	{
		lLaneSection = mRoadTree->GetRealLaneSection();
		lLane = lLaneSection->GetLastRightLane();
		if(lLane) index = lLaneSection->AddLane(-1,-(int)(lLaneSection->GetRightLaneCount()+1),lLane->GetType(), false);
		else index = lLaneSection->AddLane(-1,-1,"driving", false);

		lLane=lLaneSection->GetLastAddedLane();
		unsigned int widthIndex = lLane->AddWidthRecord(0.0,3.0,0.0,0.0,0.0);

		mOsgMain->RedrawRoad(lCurSelection->GetIndex(0));

		mRoadTree->AddLaneRight((*lCurSelection)[0], (*lCurSelection)[1], index, true);
		mRoadTree->AddLaneWidth((*lCurSelection)[0],(*lCurSelection)[1], index, widthIndex, false);

		//emit RoadChanged(false);
	}

	mCreateLaneRight->clearFocus();
}
void CreationAllRoad::CreateLaneWidthPressed()
{
	// Read the first record creation method to see how it works

	Lane *lLane=NULL;
	LaneWidth *lLaneWidth=NULL;
	unsigned int index=0;

	Selection *lCurSelection = mRoadTree->GetSelection();
	RoadTreeItemType lType = lCurSelection->GetType();
	if(lType == LANE_WIDTH)
	{
		lLane = mRoadTree->GetRealLane();
		index = lLane->CloneLaneWidth((*lCurSelection)[3]);
		mOsgMain->RedrawRoad(lCurSelection->GetIndex(0));
		mRoadTree->AddLaneWidth((*lCurSelection)[0], (*lCurSelection)[1], (*lCurSelection)[2], index, true);
		//emit RoadChanged(false);
	}
	else if(lType == LANE || lType == LANE_WIDTH_CONTAINER || (lType>LANE && lType<OBJECT_CONTAINER))
	{
		lLane = mRoadTree->GetRealLane();
		lLaneWidth = lLane->GetLastLaneWidth();
		if(lLaneWidth) index = lLane->CloneLaneWidth(lLane->GetLaneWidthCount()-1);
		else index = lLane->AddWidthRecord(0.0,3.0,0.0,0.0,0.0);
		mOsgMain->RedrawRoad(lCurSelection->GetIndex(0));
		mRoadTree->AddLaneWidth((*lCurSelection)[0],(*lCurSelection)[1],(*lCurSelection)[2], index, true);
		//emit RoadChanged(false);
	}

	mCreateLaneWidth->clearFocus();
}
void CreationAllRoad::CreateLaneRoadMarkPressed()
{
	// Read the first record creation method to see how it works

	Lane *lLane=NULL;
	LaneRoadMark *lLaneRoadMark=NULL;
	unsigned int index=0;

	Selection *lCurSelection = mRoadTree->GetSelection();
	RoadTreeItemType lType = lCurSelection->GetType();
	if(lType == LANE_ROAD_MARK)
	{
		lLane = mRoadTree->GetRealLane();
		index = lLane->CloneLaneRoadMark((*lCurSelection)[3]);
		mOsgMain->RedrawRoad(lCurSelection->GetIndex(0));
		mRoadTree->AddLaneRoadMark((*lCurSelection)[0], (*lCurSelection)[1], (*lCurSelection)[2], index, true);
		//emit RoadChanged(false);
	}
	else if(lType == LANE || lType == LANE_ROAD_MARK_CONTAINER || (lType>LANE && lType<OBJECT_CONTAINER))
	{
		lLane = mRoadTree->GetRealLane();
		lLaneRoadMark = lLane->GetLastLaneRoadMark();
		if(lLaneRoadMark) index = lLane->CloneLaneRoadMark(lLane->GetLaneRoadMarkCount()-1);
		else index = lLane->AddRoadMarkRecord(0.0, "broken", "standard", "standard", 0.0, "both");
		mOsgMain->RedrawRoad(lCurSelection->GetIndex(0));
		mRoadTree->AddLaneRoadMark((*lCurSelection)[0],(*lCurSelection)[1],(*lCurSelection)[2], index, true);
		//emit RoadChanged(false);
	}

	mCreateLaneRoadMark->clearFocus();
}
void CreationAllRoad::CreateLaneMaterialPressed()
{
	// Read the first record creation method to see how it works

	Lane *lLane=NULL;
	LaneMaterial *lLaneMaterial=NULL;
	unsigned int index=0;

	Selection *lCurSelection = mRoadTree->GetSelection();
	RoadTreeItemType lType = lCurSelection->GetType();
	if(lType == LANE_MATERIAL)
	{
		lLane = mRoadTree->GetRealLane();
		index = lLane->CloneLaneMaterial((*lCurSelection)[3]);
		mOsgMain->RedrawRoad(lCurSelection->GetIndex(0));
		mRoadTree->AddLaneMaterial((*lCurSelection)[0], (*lCurSelection)[1], (*lCurSelection)[2], index, true);
		//emit RoadChanged(false);
	}
	else if(lType == LANE || lType == LANE_MATERIAL_CONTAINER || (lType>LANE && lType<OBJECT_CONTAINER))
	{
		lLane = mRoadTree->GetRealLane();
		lLaneMaterial = lLane->GetLastLaneMaterial();
		if(lLaneMaterial) index = lLane->CloneLaneMaterial(lLane->GetLaneMaterialCount()-1);
		else index = lLane->AddMaterialRecord(0.0,"",0.0,0.0);
		mOsgMain->RedrawRoad(lCurSelection->GetIndex(0));
		mRoadTree->AddLaneMaterial((*lCurSelection)[0],(*lCurSelection)[1],(*lCurSelection)[2], index, true);
		//emit RoadChanged(false);
	}

	mCreateLaneMaterial->clearFocus();
}
void CreationAllRoad::CreateLaneVisibilityPressed()
{
	// Read the first record creation method to see how it works

	Lane *lLane=NULL;
	LaneVisibility *lLaneVisibility=NULL;
	unsigned int index=0;

	Selection *lCurSelection = mRoadTree->GetSelection();
	RoadTreeItemType lType = lCurSelection->GetType();
	if(lType == LANE_VISIBILITY)
	{
		lLane = mRoadTree->GetRealLane();
		index = lLane->CloneLaneVisibility((*lCurSelection)[3]);
		mOsgMain->RedrawRoad(lCurSelection->GetIndex(0));
		mRoadTree->AddLaneVisibility((*lCurSelection)[0], (*lCurSelection)[1], (*lCurSelection)[2], index, true);
		//emit RoadChanged(false);
	}
	else if(lType == LANE || lType == LANE_VISIBILITY_CONTAINER  || (lType>LANE && lType<OBJECT_CONTAINER))
	{
		lLane = mRoadTree->GetRealLane();
		lLaneVisibility = lLane->GetLastLaneVisibility();
		if(lLaneVisibility) index = lLane->CloneLaneVisibility(lLane->GetLaneVisibilityCount()-1);
		else index = lLane->AddVisibilityRecord(0.0,0.0,0.0,0.0,0.0);
		mOsgMain->RedrawRoad(lCurSelection->GetIndex(0));
		mRoadTree->AddLaneVisibility((*lCurSelection)[0],(*lCurSelection)[1],(*lCurSelection)[2], index, true);
		//emit RoadChanged(false);
	}

	mCreateLaneVisibility->clearFocus();
}
void CreationAllRoad::CreateLaneSpeedPressed()
{
	// Read the first record creation method to see how it works

	Lane *lLane=NULL;
	LaneSpeed *lLaneSpeed=NULL;
	unsigned int index=0;

	Selection *lCurSelection = mRoadTree->GetSelection();
	RoadTreeItemType lType = lCurSelection->GetType();
	if(lType == LANE_SPEED)
	{
		lLane = mRoadTree->GetRealLane();
		index = lLane->CloneLaneSpeed((*lCurSelection)[3]);
		mOsgMain->RedrawRoad(lCurSelection->GetIndex(0));
		mRoadTree->AddLaneSpeed((*lCurSelection)[0], (*lCurSelection)[1], (*lCurSelection)[2], index, true);
		//emit RoadChanged(false);
	}
	else if(lType == LANE || lType == LANE_SPEED_CONTAINER  || (lType>LANE && lType<OBJECT_CONTAINER))
	{
		lLane = mRoadTree->GetRealLane();
		lLaneSpeed = lLane->GetLastLaneSpeed();
		if(lLaneSpeed) index = lLane->CloneLaneSpeed(lLane->GetLaneSpeedCount()-1);
		else index = lLane->AddSpeedRecord(0.0,60.0);
		mOsgMain->RedrawRoad(lCurSelection->GetIndex(0));
		mRoadTree->AddLaneSpeed((*lCurSelection)[0],(*lCurSelection)[1],(*lCurSelection)[2], index, true);
		//emit RoadChanged(false);
	}

	mCreateLaneSpeed->clearFocus();
}
void CreationAllRoad::CreateLaneAccessPressed()
{
	// Read the first record creation method to see how it works

	Lane *lLane=NULL;
	LaneAccess *lLaneAccess=NULL;
	unsigned int index=0;

	Selection *lCurSelection = mRoadTree->GetSelection();
	RoadTreeItemType lType = lCurSelection->GetType();
	if(lType == LANE_ACCESS)
	{
		lLane = mRoadTree->GetRealLane();
		index = lLane->CloneLaneAccess((*lCurSelection)[3]);
		mOsgMain->RedrawRoad(lCurSelection->GetIndex(0));
		mRoadTree->AddLaneAccess((*lCurSelection)[0], (*lCurSelection)[1], (*lCurSelection)[2], index, true);
		//emit RoadChanged(false);
	}
	else if(lType == LANE || lType == LANE_ACCESS_CONTAINER || (lType>LANE && lType<OBJECT_CONTAINER))
	{
		lLane = mRoadTree->GetRealLane();
		lLaneAccess = lLane->GetLastLaneAccess();
		if(lLaneAccess) index = lLane->CloneLaneAccess(lLane->GetLaneAccessCount()-1);
		else index = lLane->AddAccessRecord(0,"simulator");
		mOsgMain->RedrawRoad(lCurSelection->GetIndex(0));
		mRoadTree->AddLaneAccess((*lCurSelection)[0],(*lCurSelection)[1],(*lCurSelection)[2], index, true);
		//emit RoadChanged(false);
	}

	mCreateLaneAccess->clearFocus();
}
void CreationAllRoad::CreateLaneHeightPressed()
{
	// Read the first record creation method to see how it works

	Lane *lLane=NULL;
	LaneHeight *lLaneHeight=NULL;
	unsigned int index=0;

	Selection *lCurSelection = mRoadTree->GetSelection();
	RoadTreeItemType lType = lCurSelection->GetType();
	if(lType == LANE_HEIGHT)
	{
		lLane = mRoadTree->GetRealLane();
		index = lLane->CloneLaneHeight((*lCurSelection)[3]);
		mOsgMain->RedrawRoad(lCurSelection->GetIndex(0));
		mRoadTree->AddLaneHeight((*lCurSelection)[0], (*lCurSelection)[1], (*lCurSelection)[2], index, true);
		//emit RoadChanged(false);
	}
	else if(lType == LANE || lType == LANE_HEIGHT_CONTAINER || (lType>LANE && lType<OBJECT_CONTAINER))
	{
		lLane = mRoadTree->GetRealLane();
		lLaneHeight = lLane->GetLastLaneHeight();
		if(lLaneHeight) index = lLane->CloneLaneHeight(lLane->GetLaneHeightCount()-1);
		else index = lLane->AddHeightRecord(0.0,0.0,0.0);
		mOsgMain->RedrawRoad(lCurSelection->GetIndex(0));
		mRoadTree->AddLaneHeight((*lCurSelection)[0],(*lCurSelection)[1],(*lCurSelection)[2], index, true);
		//emit RoadChanged(false);
	}
	
	mCreateLaneHeight->clearFocus();
}
