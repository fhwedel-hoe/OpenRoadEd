#include "SettingsPage.h"
#include "moc_SettingsPage.cpp"

#include "../../OpenDrive/Road.h"
#include "../../OpenDrive/RoadGeometry.h"

/**
 * Initializes the settings panel and all the interface elements
 */
SettingsPage::SettingsPage(OpenDrive *openDrive)
{
	// Saves a reference to OpenDrive structure
	mOpenDrive = openDrive;

	//setSizePolicy(QSizePolicy::Preferred,QSizePolicy::Maximum);

	// Creates instances of the settings widgets for the supported record types
	QVBoxLayout *mainLayout = new QVBoxLayout;

	mRoad = new SettingsRoad(mOpenDrive);
	mRoad->hide();
	mRoadType = new SettingsRoadTypeRecord;
	mRoadType->hide();
	mGeometryLine = new SettingsGeometryLine;
	mGeometryLine->hide();
	mGeometryTurn = new SettingsGeometryTurn;
	mGeometryTurn->hide();
	mElevation = new SettingsElevationRecord;
	mElevation->hide();
	mSuperElevation = new SettingsLateralProfileSuper;
	mSuperElevation->hide();
	mCrossfall = new SettingsLateralProfileCrossfall;
	mCrossfall->hide();
	mLaneSection = new SettingsLaneSection;
	mLaneSection->hide();
	mLane = new SettingsLane;
	mLane->hide();
	mLaneWidth = new SettingsLaneWidthRecord;
	mLaneWidth->hide();
	mLaneRoadMark = new SettingsLaneRoadMark;
	mLaneRoadMark->hide();
	mLaneMaterial = new SettingsLaneMaterialRecord;
	mLaneMaterial->hide();
	mLaneVisibility = new SettingsLaneVisibilityRecord;
	mLaneVisibility->hide();
	mLaneSpeed = new SettingsLaneSpeedRecord;
	mLaneSpeed->hide();
	mLaneAccess = new SettingsLaneAccessRecord;
	mLaneAccess->hide();
	mLaneHeight = new SettingsLaneHeightRecord;
	mLaneHeight->hide();

	mJunction = new SettingsJunction;
	mJunction->hide();
	mJunctionConnection = new SettingsJunctionConnection;
	mJunctionConnection->hide();
	mJunctionLaneLink = new SettingsJunctionLaneLink;
	mJunctionLaneLink->hide();
	mJunctionPriority = new SettingsJunctionPriority;
	mJunctionPriority->hide();
	mJunctionController = new SettingsJunctionController;
	mJunctionController->hide();
	// ADD OBJECT HERE
	// ADD SIGNAL HERE
	// ADD CONTROLLER HERE
	// ADD JUNCTION HERE

	// Adds the created widgets to the settings panel in a vertical layout
	mainLayout->addWidget(mRoad);
	mainLayout->addWidget(mRoadType);
	mainLayout->addWidget(mGeometryLine);
	mainLayout->addWidget(mGeometryTurn);
	mainLayout->addWidget(mElevation);
	mainLayout->addWidget(mSuperElevation);
	mainLayout->addWidget(mCrossfall);
	mainLayout->addWidget(mLaneSection);
	mainLayout->addWidget(mLane);
	mainLayout->addWidget(mLaneWidth);
	mainLayout->addWidget(mLaneRoadMark);
	mainLayout->addWidget(mLaneMaterial);
	mainLayout->addWidget(mLaneVisibility);
	mainLayout->addWidget(mLaneSpeed);
	mainLayout->addWidget(mLaneAccess);
	mainLayout->addWidget(mLaneHeight);

	mainLayout->addWidget(mJunction);
	mainLayout->addWidget(mJunctionConnection);
	mainLayout->addWidget(mJunctionLaneLink);
	mainLayout->addWidget(mJunctionPriority);
	mainLayout->addWidget(mJunctionController);
	// ADD OBJECT HERE
	// ADD SIGNAL HERE
	// ADD CONTROLLER HERE
	// ADD JUNCTION HERE

	setLayout(mainLayout);


	// Connects the "item selected" signal of the road tree with the appropriate method
	connect(mRoadType, SIGNAL(RoadRoadTypeChanged(bool)), this, SLOT(OnRoadGeometryChanged(bool)));
	connect(mGeometryLine, SIGNAL(RoadGeometryChanged(bool)), this, SLOT(OnRoadGeometryChanged(bool)));
	connect(mGeometryTurn, SIGNAL(RoadGeometryChanged(bool)), this, SLOT(OnRoadGeometryChanged(bool)));
	connect(mElevation, SIGNAL(RoadElevationChanged(bool)), this, SLOT(OnRoadGeometryChanged(bool)));
	connect(mSuperElevation, SIGNAL(RoadSuperElevationChanged(bool)), this, SLOT(OnRoadGeometryChanged(bool)));
	connect(mCrossfall, SIGNAL(RoadCrossfallChanged(bool)), this, SLOT(OnRoadGeometryChanged(bool)));
	connect(mLaneSection, SIGNAL(RoadLaneSectionChanged(bool)), this, SLOT(OnRoadGeometryChanged(bool)));
	connect(mLane, SIGNAL(RoadLaneChanged(bool)), this, SLOT(OnRoadGeometryChanged(bool)));
	connect(mLaneWidth, SIGNAL(RoadLaneWidthChanged(bool)), this, SLOT(OnRoadGeometryChanged(bool)));
	connect(mLaneRoadMark, SIGNAL(RoadLaneRoadMarkChanged(bool)), this, SLOT(OnRoadGeometryChanged(bool)));
	connect(mLaneMaterial, SIGNAL(RoadLaneMaterialChanged(bool)), this, SLOT(OnRoadGeometryChanged(bool)));
	connect(mLaneVisibility, SIGNAL(RoadLaneVisibilityChanged(bool)), this, SLOT(OnRoadGeometryChanged(bool)));
	connect(mLaneSpeed, SIGNAL(RoadLaneSpeedChanged(bool)), this, SLOT(OnRoadGeometryChanged(bool)));
	connect(mLaneAccess, SIGNAL(RoadLaneAccessChanged(bool)), this, SLOT(OnRoadGeometryChanged(bool)));
	connect(mLaneHeight, SIGNAL(RoadLaneHeightChanged(bool)), this, SLOT(OnRoadGeometryChanged(bool)));
}

/**
 * Hides all the widgets
 */
void SettingsPage::HideAll()
{
	mRoad->hide();
	mRoadType->hide();
	mGeometryLine->hide();
	mGeometryTurn->hide();
	mElevation->hide();
	mSuperElevation->hide();
	mCrossfall->hide();
	mLaneSection->hide();
	mLane->hide();
	mLaneWidth->hide();
	mLaneRoadMark->hide();
	mLaneMaterial->hide();
	mLaneVisibility->hide();
	mLaneSpeed->hide();
	mLaneAccess->hide();
	mLaneHeight->hide();

	mJunction->hide();
	mJunctionConnection->hide();
	mJunctionLaneLink->hide();
	mJunctionPriority->hide();
	mJunctionController->hide();
	// ADD OBJECT HERE
	// ADD SIGNAL HERE
	// ADD CONTROLLER HERE
	// ADD JUNCTION HERE
}

/**
 * Methods called when an item is selected in the road tree
 * Every method hides every single settings widget, displays
 * a specific one and load the property data from the supplied record object
 */
void SettingsPage::OnNothingSelected()
{
	HideAll();
}

void SettingsPage::OnRoadSelected(Road *node)
{
	// Hides everything
	HideAll();
	// Shows only the appropriate settings widget
	mRoad->show();
	// Loads the data into the input properties
	mRoad->LoadData(node);
}
void SettingsPage::OnRoadTypeSelected(RoadType *node, double minS, double maxS)
{
	// See the first few methods in this group for details

	HideAll();
	mRoadType->show();
	mRoadType->LoadData(node, minS, maxS);
}
void SettingsPage::OnGeometryLineSelected(GeometryBlock *node, bool first)
{
	// See the first few methods in this group for details

	HideAll();
	mGeometryLine->show();
	mGeometryLine->LoadData(node);
	mGeometryLine->SetFirst(first);
}
void SettingsPage::OnGeometryTurnSelected(GeometryBlock *node, bool first)
{
	// See the first few methods in this group for details

	HideAll();
	mGeometryTurn->show();
	mGeometryTurn->LoadData(node);
	mGeometryTurn->SetFirst(first);
}
void SettingsPage::OnElevationSelected(Elevation *node, double minS, double maxS)
{
	// See the first few methods in this group for details

	HideAll();
	mElevation->show();
	mElevation->LoadData(node, minS, maxS);
}
void SettingsPage::OnSuperElevationSelected(SuperElevation *node, double minS, double maxS)
{
	// See the first few methods in this group for details

	HideAll();
	mSuperElevation->show();
	mSuperElevation->LoadData(node, minS, maxS);
}
void SettingsPage::OnCrossfallSelected(Crossfall *node, double minS, double maxS)
{
	// See the first few methods in this group for details

	HideAll();
	mCrossfall->show();
	mCrossfall->LoadData(node, minS, maxS);
}
void SettingsPage::OnLaneSectionSelected(LaneSection *node, double minS, double maxS, bool first)
{
	// See the first few methods in this group for details

	HideAll();
	mLaneSection->show();
	mLaneSection->LoadData(node, minS, maxS, first);
}
void SettingsPage::OnLaneSelected(Lane *node)
{
	// See the first few methods in this group for details

	HideAll();
	mLane->show();
	mLane->LoadData(node);
}
void SettingsPage::OnLaneWidthSelected(LaneWidth *node, double minS, double maxS)
{
	// See the first few methods in this group for details

	HideAll();
	mLaneWidth->show();
	mLaneWidth->LoadData(node, minS, maxS);
}
void SettingsPage::OnLaneRoadMarkSelected(LaneRoadMark *node, double minS, double maxS)
{
	// See the first few methods in this group for details

	HideAll();
	mLaneRoadMark->show();
	mLaneRoadMark->LoadData(node, minS, maxS);
}
void SettingsPage::OnLaneMaterialSelected(LaneMaterial *node, double minS, double maxS)
{
	// See the first few methods in this group for details

	HideAll();
	mLaneMaterial->show();
	mLaneMaterial->LoadData(node, minS, maxS);
}
void SettingsPage::OnLaneVisibilitySelected(LaneVisibility *node, double minS, double maxS)
{
	// See the first few methods in this group for details

	HideAll();
	mLaneVisibility->show();
	mLaneVisibility->LoadData(node, minS, maxS);
}
void SettingsPage::OnLaneSpeedSelected(LaneSpeed *node, double minS, double maxS)
{
	// See the first few methods in this group for details

	HideAll();
	mLaneSpeed->show();
	mLaneSpeed->LoadData(node, minS, maxS);
}
void SettingsPage::OnLaneAccessSelected(LaneAccess *node, double minS, double maxS)
{
	// See the first few methods in this group for details

	HideAll();
	mLaneAccess->show();
	mLaneAccess->LoadData(node, minS, maxS);
}
void SettingsPage::OnLaneHeightSelected(LaneHeight *node, double minS, double maxS)
{
	// See the first few methods in this group for details

	HideAll();
	mLaneHeight->show();
	mLaneHeight->LoadData(node, minS, maxS);
}
void SettingsPage::OnObjectSelected(Object *node)
{
	// See the first few methods in this group for details

	HideAll();
	//mObject->show();
	//mObject->LoadData(node);
}
void SettingsPage::OnSignalSelected(Signal *node)
{
	// See the first few methods in this group for details

	HideAll();
	//mSignal->show();
	//mSignal->LoadData(node);
}
void SettingsPage::OnJunctionSelected(Junction *node)
{
	// See the first few methods in this group for details

	HideAll();
	mJunction->show();
	mJunction->LoadData(node);
}
void SettingsPage::OnJunctionConnectionSelected(JunctionConnection *node)
{
	// See the first few methods in this group for details

	HideAll();
	mJunctionConnection->show();
	mJunctionConnection->LoadData(node);
}
void SettingsPage::OnJunctionLaneLinkSelected(JunctionLaneLink *node)
{
	// See the first few methods in this group for details

	HideAll();
	mJunctionLaneLink->show();
	mJunctionLaneLink->LoadData(node);
}
void SettingsPage::OnJunctionPrioritySelected(JunctionPriorityRoad *node)
{
	// See the first few methods in this group for details

	HideAll();
	mJunctionPriority->show();
	mJunctionPriority->LoadData(node);
}
void SettingsPage::OnJunctionControllerSelected(JunctionController *node)
{
	// See the first few methods in this group for details

	HideAll();
	mJunctionController->show();
	mJunctionController->LoadData(node);
}


/**
 * Methods called when an a critical record property is modified
 * which requires the road to be redrawn
 */
void SettingsPage::OnRoadGeometryChanged(bool geometryChanged)
{
	// Emit the "road changed" signal so the 3D viewport could redraw the road
	emit CurrentRoadChanged(geometryChanged);
}