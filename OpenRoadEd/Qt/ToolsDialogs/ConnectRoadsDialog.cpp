
#include <QtGui/QtGui>
#include "ConnectRoadsDialog.h"
#include "moc_ConnectRoadsDialog.cpp"


/**
 * Constructor
 * Initializes the widgets that make up the interface
 *
 * @param openDrive Pointer to openDrive structure
 * @param roadTree Pointer to road tree panel
 */
ConnectRoadsDialog::ConnectRoadsDialog(OpenDrive *openDrive, RoadTree *roadTree) 
{
	// Reference for RoadTree and OpenDrive
	mOpenDrive = openDrive;
	mRoadTree = roadTree;

	// Resets the selection phase to -1
	mSelectionStage=-1;

	// Main group
	QGroupBox *lRoadsGroup = new QGroupBox("Roads");
	//-------------------------------------------------
	// Group for ROAD 1
	QGroupBox *lRoad1Group = new QGroupBox("Road 1");
	//-------------------------------------------------
	QHBoxLayout *lRoad1Layout = new QHBoxLayout;
	mRoad1 = new QLineEdit;

	mBrowseRoad1 = new QToolButton();
	mBrowseRoad1->setFocusPolicy(Qt::StrongFocus);
	mBrowseRoad1->setIcon(QIcon("Resources/Icons/Folder1.png"));
	mBrowseRoad1->setToolTip("Browse for road 1");

	mSelectRoad1 = new QToolButton();
	mSelectRoad1->setFocusPolicy(Qt::StrongFocus);
	mSelectRoad1->setIcon(QIcon("Resources/Icons/Folder2.png"));
	mSelectRoad1->setToolTip("Select road 1");

	lRoad1Layout->addWidget(mRoad1);
	lRoad1Layout->addWidget(mBrowseRoad1);
	lRoad1Layout->addWidget(mSelectRoad1);
	//-------------------------------------------------
	mRoad1ContactPoint = new QComboBox;
	mRoad1ContactPoint->insertItem(0,tr("start"));
	mRoad1ContactPoint->insertItem(1,tr("end"));
	mRoad1ContactPoint->setCurrentIndex(1);

	QFormLayout *lRoad1CfgLayout = new QFormLayout();
	lRoad1CfgLayout->addRow("Road index", lRoad1Layout);
	lRoad1CfgLayout->addRow("Contact point", mRoad1ContactPoint);
	lRoad1Group->setLayout(lRoad1CfgLayout);
	//-------------------------------------------------
	// Group for ROAD 2
	QGroupBox *lRoad2Group = new QGroupBox("Road 2");
	//-------------------------------------------------
	QHBoxLayout *lRoad2Layout = new QHBoxLayout;
	mRoad2 = new QLineEdit;

	mBrowseRoad2 = new QToolButton();
	mBrowseRoad2->setFocusPolicy(Qt::StrongFocus);
	mBrowseRoad2->setIcon(QIcon("Resources/Icons/Folder1.png"));
	mBrowseRoad2->setToolTip("Browse for road 2");

	mSelectRoad2 = new QToolButton();
	mSelectRoad2->setFocusPolicy(Qt::StrongFocus);
	mSelectRoad2->setIcon(QIcon("Resources/Icons/Folder2.png"));
	mSelectRoad2->setToolTip("Select road 2");

	lRoad2Layout->addWidget(mRoad2);
	lRoad2Layout->addWidget(mBrowseRoad2);
	lRoad2Layout->addWidget(mSelectRoad2);
	//-------------------------------------------------
	mRoad2ContactPoint = new QComboBox;
	mRoad2ContactPoint->insertItem(0,tr("start"));
	mRoad2ContactPoint->insertItem(1,tr("end"));

	QFormLayout *lRoad2CfgLayout = new QFormLayout();
	lRoad2CfgLayout->addRow("Road index", lRoad2Layout);
	lRoad2CfgLayout->addRow("Contact point", mRoad2ContactPoint);
	lRoad2Group->setLayout(lRoad2CfgLayout);	
	//-------------------------------------------------

	// Group for movement options
	QGroupBox *mMoveGroup = new QGroupBox("Move");
	QHBoxLayout *mMoveButtons = new QHBoxLayout;
	//-------------------------------------------------
	mMoveRoad1=new QRadioButton("Road 1");
	mMoveRoad2=new QRadioButton("Road 2");
	mMoveRoad2->setChecked(true);
	mMoveButtons->addWidget(mMoveRoad1);
	mMoveButtons->addWidget(mMoveRoad2);
	//-------------------------------------------------
	mMoveGroup->setLayout(mMoveButtons);
	//-------------------------------------------------
	QVBoxLayout *mGroupLayout = new QVBoxLayout;
	mGroupLayout->addWidget(lRoad1Group);
	mGroupLayout->addWidget(lRoad2Group);
	mGroupLayout->addWidget(mMoveGroup);
	lRoadsGroup->setLayout(mGroupLayout);
	//-------------------------------------------------


	// Layout of the settings and Ok Cancel buttons
	QVBoxLayout *lDialogLayout = new QVBoxLayout;

	// Horizontal layout of the Ok Cancel buttons
	QHBoxLayout *lButtonLayout = new QHBoxLayout;
	QPushButton *mOkButton = new QPushButton("Ok");
	QPushButton *mCancelButton = new QPushButton("Cancel");
	lButtonLayout->addWidget(mOkButton);
	lButtonLayout->addWidget(mCancelButton);

	// Adding groupbox and buttons to the main layout
	lDialogLayout->addWidget(lRoadsGroup);
	lDialogLayout->addLayout(lButtonLayout);

	// Dialog window layout
	setLayout(lDialogLayout);

	setWindowTitle("Connect roads");


	// Connections of the interface elements
	connect(mOkButton, SIGNAL(pressed()), this, SLOT(OkPressed()));
	connect(mCancelButton, SIGNAL(pressed()), this, SLOT(CancelPressed()));
	connect(mBrowseRoad1, SIGNAL(pressed()), this, SLOT(BrowseForRoad1()));
	connect(mBrowseRoad2, SIGNAL(pressed()), this, SLOT(BrowseForRoad2()));
	connect(mSelectRoad1, SIGNAL(pressed()), this, SLOT(SelectRoad1()));
	connect(mSelectRoad2, SIGNAL(pressed()), this, SLOT(SelectRoad2()));
}

/**
 * Launches the dialog
 */
void ConnectRoadsDialog::Run()
{
	mRoadTree->SelectNone();
	exec();
}

/**
 * Shows a list of roads for the user to select
 */
void ConnectRoadsDialog::BrowseForRoad1()
{
	// Shows a dialog that has a list of roads
	GetRoadDialog lGetRoadDialog(mOpenDrive);
	unsigned int index = lGetRoadDialog.ReturnRoadIndex();
	mRoad1->setText(QString("%1").arg(index));
}

/**
 * Shows a list of roads for the user to select
 */
void ConnectRoadsDialog::BrowseForRoad2()
{
	// Shows a dialog that has a list of roads
	GetRoadDialog lGetRoadDialog(mOpenDrive);
	unsigned int index = lGetRoadDialog.ReturnRoadIndex();
	mRoad2->setText(QString("%1").arg(index));
}

/**
 * Hides the dialog and waits for the user to select the road
 * in the road tree or 3D viewport
 */
void ConnectRoadsDialog::SelectRoad1()
{
	mSelectionStage=3;
	hide();
	mRoadTree->SelectNone();
}

/**
 * Hides the dialog and waits for the user to select the road
 * in the road tree or 3D viewport
 */
void ConnectRoadsDialog::SelectRoad2()
{
	mSelectionStage=4;
	hide();
	mRoadTree->SelectNone();
}

/**
 * Closes the dialog
 */
void ConnectRoadsDialog::OkPressed()
{
	ConnectRoads();

	accept();
}
void ConnectRoadsDialog::CancelPressed()
{
	reject();
}

/**
 * Executed when the user selects a road
 */
void ConnectRoadsDialog::RoadSelected()
{
	// When the dialog is hidden, selecting a road would set it as the first road in the dialog
	// This is useful when the user selects a road and launches the dialog afterwards - the currently
	// selected road would be already chosen
	if(mSelectionStage<0)
	{
		mRoad1Index = mRoadTree->GetSelection()->GetIndex(0);
		mRoad1->setText(QString("%1").arg(mRoad1Index));
	}


	if(mSelectionStage==0)
	{
		mRoad1Index = mRoadTree->GetSelection()->GetIndex(0);
		mRoad1->setText(QString("%1").arg(mRoad1Index));
		mSelectionStage = 1;
	}
	else if(mSelectionStage==1)
	{
		mRoad2Index = mRoadTree->GetSelection()->GetIndex(0);
		mRoad2->setText(QString("%1").arg(mRoad2Index));
		mSelectionStage=-1;
		exec();
	}

	// When the dialog is hidden (waiting for the user to select a road)
	// and a road is selected - the dialog is shown again, showing the selected road
	else if(mSelectionStage==3)
	{
		mRoad1Index = mRoadTree->GetSelection()->GetIndex(0);
		mRoad1->setText(QString("%1").arg(mRoad1Index));
		mSelectionStage=-1;
		exec();
	}
	else if(mSelectionStage==4)
	{
		mRoad2Index = mRoadTree->GetSelection()->GetIndex(0);
		mRoad2->setText(QString("%1").arg(mRoad2Index));
		mSelectionStage=-1;
		exec();
	}
}

/**
 * Clears the parameters
 */
void ConnectRoadsDialog::Clear()
{
	mRoad1->setText("");
	mRoad2->setText("");
	mRoad1ContactPoint->setCurrentIndex(1);
	mRoad2ContactPoint->setCurrentIndex(0);
	mMoveRoad1->setChecked(true);
}

/**
 * Connects the roads
 */
void ConnectRoadsDialog::ConnectRoads()
{
	unsigned int iRoad1 = mRoad1->text().toUInt();
	unsigned int iRoad2 = mRoad2->text().toUInt();

	if(iRoad1>=0 && iRoad1<mOpenDrive->GetRoadCount() && iRoad2>=0 && iRoad2<mOpenDrive->GetRoadCount())
	{
		Road *lRoad1=NULL;
		Road *lRoad2=NULL;

		short lConnectToStart1;
		short lConnectToStart2;

		unsigned int lRoadToUpdate;

		if(mMoveRoad1->isChecked())
		{
			lRoad1 = mOpenDrive->GetRoad(iRoad2);
			lRoad2 = mOpenDrive->GetRoad(iRoad1);

			lConnectToStart1 = mRoad2ContactPoint->currentIndex();
			lConnectToStart2 = mRoad1ContactPoint->currentIndex();

			lRoadToUpdate=iRoad1;
		}
		else if(mMoveRoad2->isChecked())
		{
			lRoad1 = mOpenDrive->GetRoad(iRoad1);
			lRoad2 = mOpenDrive->GetRoad(iRoad2);

			lConnectToStart1 = mRoad1ContactPoint->currentIndex();
			lConnectToStart2 = mRoad2ContactPoint->currentIndex();

			lRoadToUpdate=iRoad2;
		}

		// connect road 2 start to road 1 end
		if(lConnectToStart1==1 && lConnectToStart2==0)
		{
			double lRoad1EndX, lRoad1EndY, lRoad1EndHdg;
			double lRoad2StartX, lRoad2StartY, lRoad2StartHdg;

			// Get the first road end coords
			lRoad1->GetGeometryCoords(lRoad1->GetRoadLength(), lRoad1EndX, lRoad1EndY, lRoad1EndHdg);

			// Get the second road start coords
			lRoad2->GetGeometryCoords(0, lRoad2StartX, lRoad2StartY, lRoad2StartHdg);

			// Move the second road to the start of the first road
			GeometryBlock *lFirstGeometry = lRoad2->GetGeometryBlock(0);
			if(lFirstGeometry!=NULL)
			{
				// move the road
				lFirstGeometry->Recalculate(0, lRoad1EndX, lRoad1EndY, lRoad1EndHdg);
				lRoad2->RecalculateGeometry();
				
				emit RoadChanged(lRoadToUpdate);

				//lRoad1->SetSuccessor("",lRoad2->GetRoadId(), "start");
				//lRoad2->SetPredecessor("",lRoad1->GetRoadId(), "end");
			}
		}
		// connect road 2 end to road 1 end
		if(lConnectToStart1==1 && lConnectToStart2==1)
		{
			double lRoad1EndX, lRoad1EndY, lRoad1EndHdg;
			double lRoad2EndX, lRoad2EndY, lRoad2EndHdg;
			double lRoad2StartX, lRoad2StartY, lRoad2StartHdg;
			double lDeltaX, lDeltaY, lDeltaHdg;
			
			// Get the destination coords
			lRoad1->GetGeometryCoords(lRoad1->GetRoadLength(), lRoad1EndX, lRoad1EndY, lRoad1EndHdg);

			// Get the second road end coords
			lRoad2->GetGeometryCoords(lRoad2->GetRoadLength(), lRoad2EndX, lRoad2EndY, lRoad2EndHdg);

			// Get the new angle
			lDeltaHdg=(lRoad1EndHdg-M_PI)-lRoad2EndHdg;

			// Get the start coords of the second road
			lRoad2->GetGeometryCoords(0, lRoad2StartX, lRoad2StartY, lRoad2StartHdg);

			// move the second road end to the end of the first road
			GeometryBlock *lFirstGeometry = lRoad2->GetGeometryBlock(0);
			if(lFirstGeometry!=NULL)
			{
				// Rotate to the right angle
				lFirstGeometry->Recalculate(0, lRoad2StartX, lRoad2StartY, lRoad2StartHdg+lDeltaHdg);
				lRoad2->RecalculateGeometry();

				// Get the new end coords
				lRoad2->GetGeometryCoords(lRoad2->GetRoadLength(), lRoad2EndX, lRoad2EndY, lRoad2EndHdg);

				// Calculate the delta
				lDeltaX=lRoad1EndX-lRoad2EndX;
				lDeltaY=lRoad1EndY-lRoad2EndY;

				// Move to the new coords
				lFirstGeometry->Recalculate(0, lRoad2StartX + lDeltaX, lRoad2StartY + lDeltaY, lRoad2StartHdg+lDeltaHdg);
				lRoad2->RecalculateGeometry();
				
				emit RoadChanged(lRoadToUpdate);

				//lRoad1->SetSuccessor("",lRoad2->GetRoadId(), "end");
				//lRoad2->SetSuccessor("",lRoad1->GetRoadId(), "end");
			}
		}
		// connect road 2 end to road 1 start
		if(lConnectToStart1==0 && lConnectToStart2==1)
		{
			double lRoad1StartX, lRoad1StartY, lRoad1StartHdg;
			double lRoad2EndX, lRoad2EndY, lRoad2EndHdg;
			double lRoad2StartX, lRoad2StartY, lRoad2StartHdg;
			double lDeltaX, lDeltaY, lDeltaHdg;
			
			// Get the destination coords
			lRoad1->GetGeometryCoords(0, lRoad1StartX, lRoad1StartY, lRoad1StartHdg);

			// Get the second road end coords
			lRoad2->GetGeometryCoords(lRoad2->GetRoadLength(), lRoad2EndX, lRoad2EndY, lRoad2EndHdg);

			// Get the new angle
			lDeltaHdg=(lRoad1StartHdg)-lRoad2EndHdg;

			// Get the start coords of the second road
			lRoad2->GetGeometryCoords(0, lRoad2StartX, lRoad2StartY, lRoad2StartHdg);

			// move the second road end to the end of the first road
			GeometryBlock *lFirstGeometry = lRoad2->GetGeometryBlock(0);
			if(lFirstGeometry!=NULL)
			{
				// Rotate to the right angle
				lFirstGeometry->Recalculate(0, lRoad2StartX, lRoad2StartY, lRoad2StartHdg+lDeltaHdg);
				lRoad2->RecalculateGeometry();

				// Get the new end coords
				lRoad2->GetGeometryCoords(lRoad2->GetRoadLength(), lRoad2EndX, lRoad2EndY, lRoad2EndHdg);

				// Calculate the delta
				lDeltaX=lRoad1StartX-lRoad2EndX;
				lDeltaY=lRoad1StartY-lRoad2EndY;

				// Move to the new coords
				lFirstGeometry->Recalculate(0, lRoad2StartX + lDeltaX, lRoad2StartY + lDeltaY, lRoad2StartHdg+lDeltaHdg);
				lRoad2->RecalculateGeometry();
				
				emit RoadChanged(lRoadToUpdate);

				//lRoad1->SetPredecessor("",lRoad2->GetRoadId(), "end");
				//lRoad2->SetSuccessor("",lRoad1->GetRoadId(), "start");
			}
		}
		// connect road 2 start to road 1 start
		if(lConnectToStart1==0 && lConnectToStart2==0)
		{
			double lRoad1StartX, lRoad1StartY, lRoad1StartHdg;
			double lRoad2StartX, lRoad2StartY, lRoad2StartHdg;
			double lDeltaHdg;
			
			// Get the destination coords
			lRoad1->GetGeometryCoords(0, lRoad1StartX, lRoad1StartY, lRoad1StartHdg);

			// Get the second road end coords
			lRoad2->GetGeometryCoords(0, lRoad2StartX, lRoad2StartY, lRoad2StartHdg);

			// Get the new angle
			lDeltaHdg=(lRoad1StartHdg-M_PI)-lRoad2StartHdg;

			// move the second road end to the end of the first road
			GeometryBlock *lFirstGeometry = lRoad2->GetGeometryBlock(0);
			if(lFirstGeometry!=NULL)
			{
				// Rotate to the right angle
				lFirstGeometry->Recalculate(0, lRoad1StartX, lRoad1StartY, lRoad1StartHdg+M_PI);
				lRoad2->RecalculateGeometry();
				
				emit RoadChanged(lRoadToUpdate);

				//lRoad1->SetPredecessor("",lRoad2->GetRoadId(), "start");
				//lRoad2->SetPredecessor("",lRoad1->GetRoadId(), "start");
			}
		}
	}
}