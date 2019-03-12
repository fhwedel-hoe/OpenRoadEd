#include "CreationPage.h"
#include "moc_CreationPage.cpp"

#include "../../OpenDrive/Road.h"
#include "../../OpenDrive/RoadGeometry.h"

/**
 * Initializes the creation panel
 */
CreationPage::CreationPage(QWidget *parent)
{

	setSizePolicy(QSizePolicy::Preferred,QSizePolicy::Maximum);

	// Creates a new tabbed panel
	mTabWidget = new QTabWidget(this);

	QVBoxLayout *mainLayout = new QVBoxLayout;

	// Creates new road and junction creation groups
	mCreationAllRoad = new CreationAllRoad;
	mCreationAllRoad->SetEnabled(true,false,false,false);
	mCreationAllJunction = new CreationAllJunction;
	mCreationAllJunction->SetEnabled(true,false,false);	
	
	// Adds tabs and respective creation groups
	mTabWidget->addTab(mCreationAllRoad, "Road creation");
	mTabWidget->addTab(mCreationAllJunction, "Junction creation");
	mTabWidget->setBackgroundRole(QPalette::Window);
	setBackgroundRole(QPalette::Window);

	mainLayout->addWidget(mTabWidget);
	setLayout(mainLayout);

	// Connects road changed signal of the creation group panel to appropriate slot
	connect(mCreationAllRoad, SIGNAL(RoadChanged(bool)), this, SLOT(OnRoadGeometryChanged(bool)));
}

/**
 * Saves the references to the OpenDrive, road tree and OSG object
 */
void CreationPage::Init(OpenDrive *openDrive, RoadTree *roadTree, OSGMain *osgMain)
{
	mOpenDrive=openDrive;
	mRoadTree=roadTree;
	mOsgMain=osgMain;

	mCreationAllRoad->Init(mOpenDrive, mRoadTree, mOsgMain);
	mCreationAllJunction->Init(mOpenDrive, mRoadTree);
}

/**
 * Method called when road critical changes are made that require
 * a road redraw
 */
void CreationPage::OnRoadGeometryChanged(bool geometryChanged)
{
	emit CurrentRoadChanged(geometryChanged);
}

/**
 * Method called when something is selected in the road tree
 */
void CreationPage::SomethingSelected()
{
	// Gets the selection type
	RoadTreeItemType lType = mRoadTree->GetSelection()->GetType();

	// Enables and disables button groups depending on the current selection
	switch(lType)
	{
	case ROAD_CONTAINER:
		mCreationAllRoad->SetEnabled(true,false,false,false);
		mCreationAllJunction->SetEnabled(true,false,false);
		break;
	case ROAD:
	case ROAD_TYPE:
	case GEOMETRY_LINE:
	case GEOMETRY_TURN:
	case ELEVATION:
	case SUPERELEVATION:
	case CROSSFALL:
	case OBJECT:
	case SIGNAL:
	case ROAD_TYPE_CONTAINER:
	case GEOMETRY_CONTAINER:
	case ELEVATION_CONTAINER:
	case SUPERELEVATION_CONTAINER:
	case CROSSFALL_CONTAINER:
	case LANE_SECTION_CONTAINER:
	case OBJECT_CONTAINER:
	case SIGNAL_CONTAINER:
		mCreationAllRoad->SetEnabled(true,true,false,false);
		mCreationAllJunction->SetEnabled(true,false,false);
		break;
	case LANE_SECTION:
	case LANE_CONTAINER:
		mCreationAllRoad->SetEnabled(true,true,true,false);
		mCreationAllJunction->SetEnabled(true,false,false);
		break;
	case LANE:
	case LANE_WIDTH:
	case LANE_ROAD_MARK:
	case LANE_MATERIAL:
	case LANE_VISIBILITY:
	case LANE_SPEED:
	case LANE_ACCESS:
	case LANE_HEIGHT:
	case LANE_WIDTH_CONTAINER:
	case LANE_ROAD_MARK_CONTAINER:
	case LANE_MATERIAL_CONTAINER:
	case LANE_VISIBILITY_CONTAINER:
	case LANE_SPEED_CONTAINER:
	case LANE_ACCESS_CONTAINER:
	case LANE_HEIGHT_CONTAINER:
		mCreationAllRoad->SetEnabled(true,true,true,true);
		mCreationAllJunction->SetEnabled(true,false,false);
		break;
	case JUNCTION_CONTAINER:
		mCreationAllRoad->SetEnabled(true,false,false,false);
		mCreationAllJunction->SetEnabled(true,false,false);
		break;
	case JUNCTION:
	case JUNCTION_PRIORITY:
	case JUNCTION_CONTROLLER:
	case JUNCTION_CONNECTION_CONTAINER:
	case JUNCTION_PRIORITY_CONTAINER:
	case JUNCTION_CONTROLLER_CONTAINER:
		mCreationAllRoad->SetEnabled(true,false,false,false);
		mCreationAllJunction->SetEnabled(true,true,false);
		break;
	case JUNCTION_CONNECTION:
	case JUNCTION_LANE_LINK:
	case JUNCTION_LANE_LINK_CONTAINER:
		mCreationAllRoad->SetEnabled(true,false,false,false);
		mCreationAllJunction->SetEnabled(true,true,true);
		break;
	default:
		mCreationAllRoad->SetEnabled(true,false,false,false);
		mCreationAllJunction->SetEnabled(true,false,false);
		break;
	}
}




