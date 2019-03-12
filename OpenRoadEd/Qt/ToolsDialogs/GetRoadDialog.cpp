
#include <QtGui/QtGui>
#include "GetRoadDialog.h"
#include "moc_GetRoadDialog.cpp"


/**
 * Constructor
 * Initializes the widgets that make up the interface
 *
 * @param openDrive Pointer to openDrive structure
 */
GetRoadDialog::GetRoadDialog(OpenDrive *openDrive) 
{
	// Reference for RoadTree and OpenDrive
	mOpenDrive = openDrive;

	//-------------------------------------------------
	mRoadsGroup = new QGroupBox("Roads");
	QVBoxLayout *lGroupLayout = new QVBoxLayout;
	//-------------------------------------------------
	mRoadList = new QListWidget(mRoadsGroup);
	//-------------------------------------------------
	// List of roads
	unsigned int lRoadCount = mOpenDrive->GetRoadCount();
	for(unsigned int iRoad=0; iRoad<lRoadCount; iRoad++)
	{
		QListWidgetItem *lNewItem = new QListWidgetItem(mRoadList);
		lNewItem->setText(QString("Road %1 (Id: %2)").arg(iRoad).arg(mOpenDrive->GetRoad(iRoad)->GetRoadId().c_str()));
	}
	//-------------------------------------------------
	lGroupLayout->addWidget(mRoadList);
	mRoadsGroup->setLayout(lGroupLayout);
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
	lDialogLayout->addWidget(mRoadsGroup);
	lDialogLayout->addLayout(lButtonLayout);

	// Dialog window layout
	setLayout(lDialogLayout);

	setWindowTitle("Get road");

	// Connections of the interface elements
	connect(mOkButton, SIGNAL(pressed()), this, SLOT(OkPressed()));
	connect(mCancelButton, SIGNAL(pressed()), this, SLOT(CancelPressed()));
	connect(mRoadList, SIGNAL(itemSelectionChanged()), this, SLOT(RoadSelected()));
	connect(mRoadList, SIGNAL(itemDoubleClicked(QListWidgetItem*)), this, SLOT(RoadDoubleClicked()));
}

/**
 * Returns the road ID
 */
string GetRoadDialog::ReturnRoadId()
{
	// Resets the dialog data
	mSelectedRoad=NULL;
	mSelectedIndex=0;
	// Runs the dialog
	exec();
	// Returns the selected road ID
	if(mSelectedRoad!=NULL)
		return mSelectedRoad->GetRoadId();
	else
		return "";
}

/**
 * Returns the road index in the OpenDrive structure
 */
unsigned int GetRoadDialog::ReturnRoadIndex()
{
	// Resets the dialog data
	mSelectedRoad=NULL;
	mSelectedIndex=0;
	// Runs the dialog
	exec();
	// Returns the selected road index
	return mSelectedIndex;
}

/**
 * Closes the dialog
 */
void GetRoadDialog::OkPressed()
{
	accept();
}
void GetRoadDialog::CancelPressed()
{
	mSelectedRoad=NULL;
	mSelectedIndex=0;

	reject();
}

/**
 * Executed when the user selects a road
 */
void GetRoadDialog::RoadSelected()
{
	unsigned int iRoad = mRoadList->currentRow();

	if(iRoad>=0 && iRoad<mOpenDrive->GetRoadCount())
	{
		mSelectedRoad = mOpenDrive->GetRoad(iRoad);
		mSelectedIndex=iRoad;
	}
	else
	{
		mSelectedRoad = NULL;
		mSelectedIndex=0;
	}
}

void GetRoadDialog::RoadDoubleClicked()
{
	RoadSelected();

	accept();
}