#include "CreationAllJunction.h"
#include "moc_CreationAllJunction.cpp"

#include "../../OpenDrive/Road.h"

/**
 * Initializes the creation panel
 */
CreationAllJunction::CreationAllJunction(QWidget *parent)
{
	// Resets the opendrive and road tree pointers
	mOpenDrive=NULL;
	mRoadTree=NULL;

	//-------------------------------------------------
	// Main vertical layout
	QVBoxLayout *mainLayout = new QVBoxLayout;

	//-------------------------------------------------
	// Group for settings
	QGroupBox *settingsGroup = new QGroupBox;
	settingsGroup->setSizePolicy(QSizePolicy::Maximum,QSizePolicy::Maximum);
	settingsGroup->setTitle(tr("Junction creation"));

	mCreateJunction = new QPushButton("Junction", this);;

	mCreateJunctionConnection = new QToolButton(this);
	mCreateJunctionConnection->setFocusPolicy(Qt::StrongFocus);
	mCreateJunctionConnection->setIcon(QIcon("Resources/Icons/JunctionConnection.png"));
	mCreateJunctionConnection->setToolTip("Junction connection");
	mCreateJunctionLaneLink = new QToolButton(this);
	mCreateJunctionLaneLink->setFocusPolicy(Qt::StrongFocus);
	mCreateJunctionLaneLink->setIcon(QIcon("Resources/Icons/JunctionLaneLink.png"));
	mCreateJunctionLaneLink->setToolTip("Junction lane link");
	mCreateJunctionPriority = new QToolButton(this);
	mCreateJunctionPriority->setFocusPolicy(Qt::StrongFocus);
	mCreateJunctionPriority->setIcon(QIcon("Resources/Icons/JunctionPriority.png"));
	mCreateJunctionPriority->setToolTip("Junction priority");
	mCreateJunctionController = new QToolButton(this);
	mCreateJunctionController->setFocusPolicy(Qt::StrongFocus);
	mCreateJunctionController->setIcon(QIcon("Resources/Icons/JunctionController.png"));
	mCreateJunctionController->setToolTip("Junction controller");

	// Form Layout inside group
	QVBoxLayout *buttonsVLayout = new QVBoxLayout;

	QHBoxLayout *buttonsHLayout1 = new QHBoxLayout;
	buttonsHLayout1->addWidget(mCreateJunction);

	QHBoxLayout *buttonsHLayout2 = new QHBoxLayout;
	buttonsHLayout2->addWidget(mCreateJunctionConnection);
	buttonsHLayout2->addWidget(mCreateJunctionLaneLink);
	buttonsHLayout2->addWidget(mCreateJunctionPriority);
	buttonsHLayout2->addWidget(mCreateJunctionController);

	buttonsVLayout->addLayout(buttonsHLayout1);
	buttonsVLayout->addLayout(buttonsHLayout2);

	settingsGroup->setLayout(buttonsVLayout);
	//-------------------------------------------------

	// Form Layout inside group
	QHBoxLayout *groupHLayout = new QHBoxLayout;

	groupHLayout->addWidget(settingsGroup);

	mainLayout->addLayout(groupHLayout);
	mainLayout->setAlignment(Qt::AlignLeft);
	setLayout(mainLayout);

	// Connections of the interface elements
	connect(mCreateJunction, SIGNAL(clicked(bool)), this, SLOT(CreateJunctionPressed()));
	connect(mCreateJunctionConnection, SIGNAL(clicked(bool)), this, SLOT(CreateJunctionConnectionPressed()));
	connect(mCreateJunctionLaneLink, SIGNAL(clicked(bool)), this, SLOT(CreateJunctionLaneLinkPressed()));
	connect(mCreateJunctionPriority, SIGNAL(clicked(bool)), this, SLOT(CreateJunctionPriorityPressed()));
	connect(mCreateJunctionController, SIGNAL(clicked(bool)), this, SLOT(CreateJunctionControllerPressed()));
}

/**
 * Saves the references to the OpenDrive object and road tree widget
 */
void CreationAllJunction::Init(OpenDrive *openDrive, RoadTree *roadTree)
{
	mOpenDrive=openDrive;
	mRoadTree=roadTree;
}

/**
 * Enables or disables groups of buttons when they cannot be used
 * due to an unrelated item selected in the road tree
 * 
 * @param wholeGroup Disable the whole group or just a part
 * @param junctionItems Disable junction item buttons
 * @param laneLink Disable just the laneLink button
 */
void CreationAllJunction::SetEnabled(bool wholeGroup, bool junctionItems, bool laneLink)
{
	setEnabled(wholeGroup);

	mCreateJunctionConnection->setEnabled(junctionItems);
	mCreateJunctionPriority->setEnabled(junctionItems);
	mCreateJunctionController->setEnabled(junctionItems);

	mCreateJunctionLaneLink->setEnabled(laneLink);
}


/**
 * Methods called when one of the creation buttons is pressed
 */
void CreationAllJunction::CreateJunctionPressed()
{
	// Creates a new record in openDrive structure and returns it's index
	unsigned int index=mOpenDrive->AddJunction("", "");
	// Add the junction to the road tree
	mRoadTree->AddJunction(index, true);
}
void CreationAllJunction::CreateJunctionConnectionPressed()
{
	Junction *lJunction=NULL;
	JunctionConnection *lJunctionConnection=NULL;
	unsigned int index=0;

	// Get the current selection
	Selection *lCurSelection = mRoadTree->GetSelection();
	RoadTreeItemType lType = lCurSelection->GetType();
	// If another junction connection is selected - duplicate it
	if(lType == JUNCTION_CONNECTION)
	{
		// Clone the selected junction connection
		lJunction = mRoadTree->GetRealJunction();
		index = lJunction->CloneJunctionConnection((*lCurSelection)[1]);
		// Add junction connection to the road tree
		mRoadTree->AddJunctionConnection((*lCurSelection)[0], index, true);
		//emit RoadChanged(false);
	}
	// If something else is selected - duplicate the last junction connection or create a new one if
	// no junction connections exist
	else if(lType == JUNCTION|| lType == JUNCTION_CONNECTION_CONTAINER || (lType>JUNCTION && lType<NONE))
	{
		// Get the last junction connection
		lJunction = mRoadTree->GetRealJunction();
		lJunctionConnection = lJunction->GetLastJunctionConnection();
		// Duplicate it if it exists
		if(lJunctionConnection) index = lJunction->CloneJunctionConnection(lJunction->GetJunctionConnectionCount()-1);
		// Else - create a blank one
		else index = lJunction->AddJunctionConnection("","","","start");
		// Add junction connection to the road tree
		mRoadTree->AddJunctionConnection((*lCurSelection)[0], index, true);
		//emit RoadChanged(false);
	}
}
void CreationAllJunction::CreateJunctionLaneLinkPressed()
{
	// Read the first record creation method to see how it works

	JunctionConnection *lJunctionConnection=NULL;
	JunctionLaneLink *lJunctionLaneLink=NULL;
	unsigned int index=0;

	Selection *lCurSelection = mRoadTree->GetSelection();
	RoadTreeItemType lType = lCurSelection->GetType();
	if(lType == JUNCTION_LANE_LINK)
	{
		lJunctionConnection = mRoadTree->GetRealJunctionConnection();
		index = lJunctionConnection->CloneJunctionLaneLink((*lCurSelection)[2]);
		mRoadTree->AddJunctionLaneLink((*lCurSelection)[0],(*lCurSelection)[1], index, true);
		//emit RoadChanged(false);
	}
	else if(lType == JUNCTION_CONNECTION || lType == JUNCTION_LANE_LINK_CONTAINER)
	{
		lJunctionConnection = mRoadTree->GetRealJunctionConnection();
		lJunctionLaneLink = lJunctionConnection->GetLastJunctionLaneLink();
		if(lJunctionLaneLink) index = lJunctionConnection->CloneJunctionLaneLink(lJunctionConnection->GetJunctionLaneLinkCount()-1);
		else index = lJunctionConnection->AddJunctionLaneLink(0,0);
		mRoadTree->AddJunctionLaneLink((*lCurSelection)[0],(*lCurSelection)[1], index, true);
		//emit RoadChanged(false);
	}
}
void CreationAllJunction::CreateJunctionPriorityPressed()
{
	// Read the first record creation method to see how it works

	Junction *lJunction=NULL;
	JunctionPriorityRoad *lJunctionPriority=NULL;
	unsigned int index=0;

	Selection *lCurSelection = mRoadTree->GetSelection();
	RoadTreeItemType lType = lCurSelection->GetType();
	if(lType == JUNCTION_PRIORITY)
	{
		lJunction = mRoadTree->GetRealJunction();
		index = lJunction->CloneJunctionPriority((*lCurSelection)[1]);
		mRoadTree->AddJunctionPriority((*lCurSelection)[0], index, true);
		//emit RoadChanged(false);
	}
	else if(lType == JUNCTION|| lType == JUNCTION_PRIORITY_CONTAINER || (lType>JUNCTION && lType<NONE))
	{
		lJunction = mRoadTree->GetRealJunction();
		lJunctionPriority = lJunction->GetLastJunctionPriority();
		if(lJunctionPriority) index = lJunction->CloneJunctionPriority(lJunction->GetJunctionPriorityCount()-1);
		else index = lJunction->AddJunctionPriority("","");
		mRoadTree->AddJunctionPriority((*lCurSelection)[0], index, true);
		//emit RoadChanged(false);
	}
}
void CreationAllJunction::CreateJunctionControllerPressed()
{
	// Read the first record creation method to see how it works

	Junction *lJunction=NULL;
	JunctionController *lJunctionController=NULL;
	unsigned int index=0;

	Selection *lCurSelection = mRoadTree->GetSelection();
	RoadTreeItemType lType = lCurSelection->GetType();
	if(lType == JUNCTION_CONTROLLER)
	{
		lJunction = mRoadTree->GetRealJunction();
		index = lJunction->CloneJunctionController((*lCurSelection)[1]);
		mRoadTree->AddJunctionController((*lCurSelection)[0], index, true);
		//emit RoadChanged(false);
	}
	else if(lType == JUNCTION|| lType == JUNCTION_CONTROLLER_CONTAINER || (lType>JUNCTION && lType<NONE))
	{
		lJunction = mRoadTree->GetRealJunction();
		lJunctionController = lJunction->GetLastJunctionController();
		if(lJunctionController) index = lJunction->CloneJunctionController(lJunction->GetJunctionControllerCount()-1);
		else index = lJunction->AddJunctionController("","");
		mRoadTree->AddJunctionController((*lCurSelection)[0], index, true);
		//emit RoadChanged(false);
	}
}




