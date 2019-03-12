#include "DeleteAll.h"
#include "moc_DeleteAll.cpp"

#include "../../OpenDrive/Road.h"

DeleteAll::DeleteAll(QWidget *parent)
{
	mOpenDrive=NULL;
	mRoadTree=NULL;
	mOsgMain=NULL;


	QSettings lSettingsFile("Settings.ini", QSettings::IniFormat);
	bool lDeleteConfirmationState = lSettingsFile.value("View/DeleteConfirmation",true).toBool();
	mDeleteConfirmation=lDeleteConfirmationState;

	// Main vertical layout
	QVBoxLayout *mainLayout = new QVBoxLayout;

	//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX
	// Group for settings
	QGroupBox *settingsGroup = new QGroupBox;
	settingsGroup->setSizePolicy(QSizePolicy::Preferred,QSizePolicy::Maximum);
	settingsGroup->setTitle(tr("Delete"));


	mDelete = new QPushButton("Delete item", this);;

	// Form Layout inside group
	QVBoxLayout *buttonsVLayout = new QVBoxLayout;

	buttonsVLayout->addWidget(mDelete);

	settingsGroup->setLayout(buttonsVLayout);
	//XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX

	mainLayout->addWidget(settingsGroup);
	setLayout(mainLayout);


	connect(mDelete, SIGNAL(clicked(bool)), this, SLOT(DeletePressed()));
}

void DeleteAll::Init(OpenDrive *openDrive, RoadTree *roadTree, OSGMain *osgMain)
{
	mOpenDrive=openDrive;
	mRoadTree=roadTree;
	mOsgMain=osgMain;
}

void DeleteAll::ToggleDeleteConfirmation(bool state)
{
	mDeleteConfirmation=state;

	QSettings lSettingsFile("Settings.ini", QSettings::IniFormat);
	lSettingsFile.setValue("View/DeleteConfirmation", state);
	lSettingsFile.sync();
}

void DeleteAll::DeletePressed()
{
	unsigned int index=0;

	Selection *lCurSelection = mRoadTree->GetSelection();
	RoadTreeItemType lType = lCurSelection->GetType();
	
	switch (lType)
	{

	case CONTAINER:
	case ROAD_CONTAINER:
	case ROAD_TYPE_CONTAINER:
	case GEOMETRY_CONTAINER:
	case ELEVATION_CONTAINER:
	case SUPERELEVATION_CONTAINER:
	case CROSSFALL_CONTAINER:
	case LANE_SECTION_CONTAINER:
	case LANE_CONTAINER:
	case LANE_WIDTH_CONTAINER:
	case LANE_ROAD_MARK_CONTAINER:
	case LANE_MATERIAL_CONTAINER:
	case LANE_VISIBILITY_CONTAINER:
	case LANE_SPEED_CONTAINER:
	case LANE_ACCESS_CONTAINER:
	case LANE_HEIGHT_CONTAINER:
	case OBJECT_CONTAINER:
	case SIGNAL_CONTAINER:
	case CONTROLLER_CONTAINER:
	case JUNCTION_CONTAINER:
	case JUNCTION_CONNECTION_CONTAINER:
	case JUNCTION_LANE_LINK_CONTAINER:
	case JUNCTION_PRIORITY_CONTAINER:
	case JUNCTION_CONTROLLER_CONTAINER:
		return;
		break;
	}


	if(mDeleteConfirmation)
	{
		int ret = QMessageBox::warning(this, tr("Warning"),
										tr("This will delete the selected item.\n"),
										QMessageBox::Ok | QMessageBox::Cancel,
										QMessageBox::Cancel);

		if(ret==QMessageBox::Cancel) return;
	}



	switch (lType)
	{
	case ROAD:
		{
			unsigned int lIndex=(*lCurSelection)[0];
			mOsgMain->ClearSelection(true);
			mOpenDrive->DeleteRoad(lIndex);
			mRoadTree->DeleteRoad();
			if((lIndex-1)<mOpenDrive->GetRoadCount() && (lIndex-1)>=0) mRoadTree->SelectRoad(lIndex-1);
			else mRoadTree->SelectNone();

			mOsgMain->DeleteRoad(lIndex);
			break;
		}
	case ROAD_TYPE:
		{
			Road *lRoad = mRoadTree->GetRealRoad();
			if(lRoad)
			{
				unsigned int lIndex=(*lCurSelection)[1];
				mOsgMain->ClearSelection(true);
				lRoad->DeleteRoadType(lIndex);
				mRoadTree->DeleteRoadType(); 
				if((lIndex-1)<lRoad->GetRoadTypeCount() && (lIndex-1)>=0) mRoadTree->SelectRoadType((*lCurSelection)[0],lIndex-1);
				else mRoadTree->SelectRoad((*lCurSelection)[0]);
				emit RoadChanged(false);
			}
			break;
		}
	case GEOMETRY_LINE:
		{
			Road *lRoad = mRoadTree->GetRealRoad();
			if(lRoad)
			{
				unsigned int lIndex=lRoad->GetGeometryBlockCount()-1;
				mOsgMain->ClearSelection(true);
				lRoad->DeleteGeometryBlock(lIndex);
				mRoadTree->DeleteLastGeometry(); 
				if((lIndex-1)<lRoad->GetGeometryBlockCount() && (lIndex-1)>=0) mRoadTree->SelectGeometry((*lCurSelection)[0],lIndex-1);
				else mRoadTree->SelectRoad((*lCurSelection)[0]);
				emit RoadChanged(true);
			}
			break;
		}
	case GEOMETRY_TURN:
		{
			Road *lRoad = mRoadTree->GetRealRoad();
			if(lRoad)
			{
				unsigned int lIndex=lRoad->GetGeometryBlockCount()-1;
				mOsgMain->ClearSelection(true);
				lRoad->DeleteGeometryBlock(lIndex);
				mRoadTree->DeleteLastGeometry(); 
				if((lIndex-1)<lRoad->GetGeometryBlockCount() && (lIndex-1)>=0) mRoadTree->SelectGeometry((*lCurSelection)[0],lIndex-1);
				else mRoadTree->SelectRoad((*lCurSelection)[0]);
				emit RoadChanged(true);
			}
			break;
		}
	case ELEVATION:
		{
			Road *lRoad = mRoadTree->GetRealRoad();
			if(lRoad)
			{
				unsigned int lIndex=(*lCurSelection)[1];
				mOsgMain->ClearSelection(true);
				lRoad->DeleteElevation(lIndex);
				mRoadTree->DeleteElevation(); 
				if((lIndex-1)<lRoad->GetElevationCount() && (lIndex-1)>=0) mRoadTree->SelectElevation((*lCurSelection)[0],lIndex-1);
				else mRoadTree->SelectRoad((*lCurSelection)[0]);
				emit RoadChanged(false);
			}
			break;
		}
	case SUPERELEVATION:
		{
			Road *lRoad = mRoadTree->GetRealRoad();
			if(lRoad)
			{
				unsigned int lIndex=(*lCurSelection)[1];
				mOsgMain->ClearSelection(true);
				lRoad->DeleteSuperElevation(lIndex);
				mRoadTree->DeleteSuperElevation(); 
				if((lIndex-1)<lRoad->GetSuperElevationCount() && (lIndex-1)>=0) mRoadTree->SelectSuperElevation((*lCurSelection)[0],lIndex-1);
				else mRoadTree->SelectRoad((*lCurSelection)[0]);
				emit RoadChanged(false);
			}
			break;
		}
	case CROSSFALL:
		{
			Road *lRoad = mRoadTree->GetRealRoad();
			if(lRoad)
			{
				unsigned int lIndex=(*lCurSelection)[1];
				mOsgMain->ClearSelection(true);
				lRoad->DeleteCrossfall(lIndex);
				mRoadTree->DeleteCrossfall();
				if((lIndex-1)<lRoad->GetCrossfallCount() && (lIndex-1)>=0) mRoadTree->SelectCrossfall((*lCurSelection)[0],lIndex-1);
				else mRoadTree->SelectRoad((*lCurSelection)[0]);
				emit RoadChanged(false);
			}
			break;
		}
	case LANE_SECTION:
		{
			Road *lRoad = mRoadTree->GetRealRoad();
			if(lRoad)
			{
				unsigned int lIndex=(*lCurSelection)[1];
				mOsgMain->ClearSelection(true);
				lRoad->DeleteLaneSection(lIndex);
				mRoadTree->DeleteLaneSection();
				if((lIndex-1)<lRoad->GetLaneSectionCount() && (lIndex-1)>=0) mRoadTree->SelectLaneSection((*lCurSelection)[0],lIndex-1);
				else mRoadTree->SelectRoad((*lCurSelection)[0]);
				emit RoadChanged(false);
			}
			break;
		}
	case LANE:
		{
			LaneSection *lLaneSection=mRoadTree->GetRealLaneSection();
			Lane *lLane=mRoadTree->GetRealLane();
			if(lLaneSection && lLane)
			{
				if(lLane->GetSide()>0)
				{
					mOsgMain->ClearSelection(true);
					lLaneSection->DeleteLeftLane();
					mRoadTree->DeleteLaneLeft();
					mRoadTree->SelectLaneSection((*lCurSelection)[0],(*lCurSelection)[1]);
					emit RoadChanged(false);
				}
				else if(lLane->GetSide()==0)
				{
					//lLaneSection->DeleteCenterLane();
					//mRoadTree->DeleteLaneCenter();
				}
				else if(lLane->GetSide()<0)
				{
					mOsgMain->ClearSelection(true);
					lLaneSection->DeleteRigthLane();
					mRoadTree->DeleteLaneRight();
					mRoadTree->SelectLaneSection((*lCurSelection)[0],(*lCurSelection)[1]);
					emit RoadChanged(false);
				}
			}
			break;
			
		}
	case LANE_WIDTH:
		{
			Lane *lLane = mRoadTree->GetRealLane();
			if(lLane)
			{
				unsigned int lIndex=(*lCurSelection)[3];
				mOsgMain->ClearSelection(true);
				lLane->DeleteLaneWidth(lIndex);
				mRoadTree->DeleteLaneWidth();
				if((lIndex-1)<lLane->GetLaneWidthCount() && (lIndex-1)>=0) mRoadTree->SelectLaneWidth((*lCurSelection)[0],(*lCurSelection)[1],(*lCurSelection)[2],lIndex-1);
				else mRoadTree->SelectLane((*lCurSelection)[0],(*lCurSelection)[1],(*lCurSelection)[2]);
				emit RoadChanged(false);
			}
			break;
		}
	case LANE_ROAD_MARK:
		{
			Lane *lLane = mRoadTree->GetRealLane();
			if(lLane)
			{
				unsigned int lIndex=(*lCurSelection)[3];
				mOsgMain->ClearSelection(true);
				lLane->DeleteLaneRoadMark(lIndex);
				mRoadTree->DeleteLaneRoadMark();
				if((lIndex-1)<lLane->GetLaneRoadMarkCount() && (lIndex-1)>=0) mRoadTree->SelectLaneRoadMark((*lCurSelection)[0],(*lCurSelection)[1],(*lCurSelection)[2],lIndex-1);
				else mRoadTree->SelectLane((*lCurSelection)[0],(*lCurSelection)[1],(*lCurSelection)[2]);
				emit RoadChanged(false);
			}
			break;
		}
	case LANE_MATERIAL:
		{
			Lane *lLane = mRoadTree->GetRealLane();
			if(lLane)
			{
				unsigned int lIndex=(*lCurSelection)[3];
				mOsgMain->ClearSelection(true);
				lLane->DeleteLaneMaterial(lIndex);
				mRoadTree->DeleteLaneMaterial();
				if((lIndex-1)<lLane->GetLaneMaterialCount() && (lIndex-1)>=0) mRoadTree->SelectLaneMaterial((*lCurSelection)[0],(*lCurSelection)[1],(*lCurSelection)[2],lIndex-1);
				else mRoadTree->SelectLane((*lCurSelection)[0],(*lCurSelection)[1],(*lCurSelection)[2]);
				emit RoadChanged(false);
			}
			break;
		}
	case LANE_VISIBILITY:
		{
			Lane *lLane = mRoadTree->GetRealLane();
			if(lLane)
			{
				unsigned int lIndex=(*lCurSelection)[3];
				mOsgMain->ClearSelection(true);
				lLane->DeleteLaneVisibility(lIndex);
				mRoadTree->DeleteLaneVisibility();
				if((lIndex-1)<lLane->GetLaneVisibilityCount() && (lIndex-1)>=0) mRoadTree->SelectLaneVisibility((*lCurSelection)[0],(*lCurSelection)[1],(*lCurSelection)[2],lIndex-1);
				else mRoadTree->SelectLane((*lCurSelection)[0],(*lCurSelection)[1],(*lCurSelection)[2]);
				emit RoadChanged(false);
			}
			break;
		}
	case LANE_SPEED:
		{
			Lane *lLane = mRoadTree->GetRealLane();
			if(lLane)
			{
				unsigned int lIndex=(*lCurSelection)[3];
				mOsgMain->ClearSelection(true);
				lLane->DeleteLaneSpeed(lIndex);
				mRoadTree->DeleteLaneSpeed();
				if((lIndex-1)<lLane->GetLaneSpeedCount() && (lIndex-1)>=0) mRoadTree->SelectLaneSpeed((*lCurSelection)[0],(*lCurSelection)[1],(*lCurSelection)[2],lIndex-1);
				else mRoadTree->SelectLane((*lCurSelection)[0],(*lCurSelection)[1],(*lCurSelection)[2]);
				emit RoadChanged(false);
			}
			break;
		}
	case LANE_ACCESS:
		{
			Lane *lLane = mRoadTree->GetRealLane();
			if(lLane)
			{
				unsigned int lIndex=(*lCurSelection)[3];
				mOsgMain->ClearSelection(true);
				lLane->DeleteLaneAccess(lIndex);
				mRoadTree->DeleteLaneAccess();
				if((lIndex-1)<lLane->GetLaneAccessCount() && (lIndex-1)>=0) mRoadTree->SelectLaneAccess((*lCurSelection)[0],(*lCurSelection)[1],(*lCurSelection)[2],lIndex-1);
				else mRoadTree->SelectLane((*lCurSelection)[0],(*lCurSelection)[1],(*lCurSelection)[2]);
				emit RoadChanged(false);
			}
			break;
		}
	case LANE_HEIGHT:
		{
			Lane *lLane = mRoadTree->GetRealLane();
			if(lLane)
			{
				unsigned int lIndex=(*lCurSelection)[3];
				mOsgMain->ClearSelection(true);
				lLane->DeleteLaneHeight(lIndex);
				mRoadTree->DeleteLaneHeight();
				if((lIndex-1)<lLane->GetLaneHeightCount() && (lIndex-1)>=0) mRoadTree->SelectLaneHeight((*lCurSelection)[0],(*lCurSelection)[1],(*lCurSelection)[2],lIndex-1);
				else mRoadTree->SelectLane((*lCurSelection)[0],(*lCurSelection)[1],(*lCurSelection)[2]);
				emit RoadChanged(false);
			}
			break;
		}
	case OBJECT:
		{
			Road *lRoad = mRoadTree->GetRealRoad();
			if(lRoad)
			{
				unsigned int lIndex=(*lCurSelection)[1];
				mOsgMain->ClearSelection(true);
				lRoad->DeleteObject(lIndex);
				mRoadTree->DeleteObject(); 
				if((lIndex-1)<lRoad->GetObjectCount() && (lIndex-1)>=0) mRoadTree->SelectObject((*lCurSelection)[0],lIndex-1);
				else mRoadTree->SelectRoad((*lCurSelection)[0]);
				emit RoadChanged(false);
			}
			break;
		}
	case SIGNAL:
		{
			Road *lRoad = mRoadTree->GetRealRoad();
			if(lRoad)
			{
				unsigned int lIndex=(*lCurSelection)[1];
				mOsgMain->ClearSelection(true);
				lRoad->DeleteSignal(lIndex);
				mRoadTree->DeleteSignal(); 
				if((lIndex-1)<lRoad->GetSignalCount() && (lIndex-1)>=0) mRoadTree->SelectSignal((*lCurSelection)[0],lIndex-1);
				else mRoadTree->SelectRoad((*lCurSelection)[0]);
				emit RoadChanged(false);
			}
			break;
		}
	case CONTROLLER:
		//ADD CONTROLLER CODE HERE
		break;
	case JUNCTION:
		{
			unsigned int lIndex=(*lCurSelection)[0];
			mOsgMain->ClearSelection(true);
			mOpenDrive->DeleteJunction(lIndex);
			mRoadTree->DeleteJunction();
			if((lIndex-1)<mOpenDrive->GetJunctionCount() && (lIndex-1)>=0) mRoadTree->SelectJunction(lIndex-1);
			else mRoadTree->SelectNone();

			mOsgMain->DeleteJunction(lIndex);
			break;
		}
	case JUNCTION_CONNECTION:
		{
			Junction *lJunction = mRoadTree->GetRealJunction();
			if(lJunction)
			{
				unsigned int lIndex=(*lCurSelection)[1];
				mOsgMain->ClearSelection(true);
				lJunction->DeleteJunctionConnection(lIndex);
				mRoadTree->DeleteJunctionConnection(); 
				if((lIndex-1)<lJunction->GetJunctionConnectionCount() && (lIndex-1)>=0) mRoadTree->SelectJunctionConnection((*lCurSelection)[0],lIndex-1);
				else mRoadTree->SelectJunction((*lCurSelection)[0]);
			}
			break;
		}
	case JUNCTION_LANE_LINK:
		{
			JunctionConnection *lJunctionConnection = mRoadTree->GetRealJunctionConnection();
			if(lJunctionConnection)
			{
				unsigned int lIndex=(*lCurSelection)[2];
				mOsgMain->ClearSelection(true);
				lJunctionConnection->DeleteJunctionLaneLink(lIndex);
				mRoadTree->DeleteJunctionLaneLink(); 
				if((lIndex-1)<lJunctionConnection->GetJunctionLaneLinkCount() && (lIndex-1)>=0) mRoadTree->SelectJunctionLaneLink((*lCurSelection)[0],(*lCurSelection)[1],lIndex-1);
				else mRoadTree->SelectJunctionConnection((*lCurSelection)[0],(*lCurSelection)[1]);
			}
			break;
		}
	case JUNCTION_PRIORITY:
		{
			Junction *lJunction = mRoadTree->GetRealJunction();
			if(lJunction)
			{
				unsigned int lIndex=(*lCurSelection)[1];
				mOsgMain->ClearSelection(true);
				lJunction->DeleteJunctionPriority(lIndex);
				mRoadTree->DeleteJunctionPriority(); 
				if((lIndex-1)<lJunction->GetJunctionPriorityCount() && (lIndex-1)>=0) mRoadTree->SelectJunctionPriority((*lCurSelection)[0],lIndex-1);
				else mRoadTree->SelectJunction((*lCurSelection)[0]);
			}
			break;
		}
	case JUNCTION_CONTROLLER:
		{
			Junction *lJunction = mRoadTree->GetRealJunction();
			if(lJunction)
			{
				unsigned int lIndex=(*lCurSelection)[1];
				mOsgMain->ClearSelection(true);
				lJunction->DeleteJunctionController(lIndex);
				mRoadTree->DeleteJunctionController(); 
				if((lIndex-1)<lJunction->GetJunctionControllerCount() && (lIndex-1)>=0) mRoadTree->SelectJunctionController((*lCurSelection)[0],lIndex-1);
				else mRoadTree->SelectJunction((*lCurSelection)[0]);
			}
			break;
		}
	default:
		{
			mRoadTree->SelectNone();
			break;
		}
	}

	
	
}





