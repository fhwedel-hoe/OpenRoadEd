#include "SettingsLaneVisibilityRecord.h"
#include "moc_SettingsLaneVisibilityRecord.cpp"

/**
 * Initializes the properties panel and the UI elements
 */
SettingsLaneVisibilityRecord::SettingsLaneVisibilityRecord(QWidget *parent)
{
	// Resets the record
	mLaneVisibility=NULL;

	// Main vertical layout
	QVBoxLayout *mainLayout = new QVBoxLayout;

	//-------------------------------------------------
	// Group for settings
	QGroupBox *settingsGroup = new QGroupBox;
	settingsGroup->setSizePolicy(QSizePolicy::Preferred,QSizePolicy::Maximum);
	settingsGroup->setTitle(tr("Lane visibility settings"));

	mS=new QDoubleSpinBox;
	mS->setKeyboardTracking(false);
	mS->setDecimals(9);
	mS->setRange(0,1000000);
	mForward=new QDoubleSpinBox;
	mForward->setKeyboardTracking(false);
	mForward->setDecimals(9);
	mForward->setRange(-1000000,1000000);
	mBack=new QDoubleSpinBox;
	mBack->setKeyboardTracking(false);
	mBack->setDecimals(9);
	mBack->setRange(-1000000,1000000);
	mLeft=new QDoubleSpinBox;
	mLeft->setKeyboardTracking(false);
	mLeft->setDecimals(9);
	mLeft->setRange(-1000000,1000000);
	mRight=new QDoubleSpinBox;
	mRight->setKeyboardTracking(false);
	mRight->setDecimals(9);
	mRight->setRange(-1000000,1000000);
	
	// Form Layout inside group
	QFormLayout *settingsFormLayout = new QFormLayout;
	settingsFormLayout->addRow(tr("S:"),mS);
	settingsFormLayout->addRow(tr("Forward:"),mForward);
	settingsFormLayout->addRow(tr("Back:"),mBack);
	settingsFormLayout->addRow(tr("Left:"),mLeft);
	settingsFormLayout->addRow(tr("Right:"),mRight);	

	settingsGroup->setLayout(settingsFormLayout);
	//-------------------------------------------------
	// Group for help
	QGroupBox *helpGroup = new QGroupBox;
	helpGroup->setTitle(tr("Help"));

	QTextEdit *helpText = new QTextEdit;
	helpText->setSizePolicy(QSizePolicy::Preferred,QSizePolicy::Expanding);
	helpText->setReadOnly(true);
	helpText->setHtml("This record defines the lane's visibility. The parameters of this entry are valid until the next entry starts or the road’s chord line ends."
						"<p><b>S</b> - start position (s-offset from the current lane section) [meters]</p>"
						"<p><b>Forward</b> - visibility in forward direction [meters]</p>"
						"<p><b>Back</b> - visibility in reverse direction [meters]</p>"
						"<p><b>Left</b> - visibility to the left [meters] </p>"
						"<p><b>Right</b> - visibility to the right [meters] </p>");
	
	QVBoxLayout *helpLayout = new QVBoxLayout;
	helpLayout->addWidget(helpText);

	helpGroup->setLayout(helpLayout);
	//-------------------------------------------------
	
	mainLayout->addWidget(settingsGroup);
	mainLayout->addWidget(helpGroup);
	setLayout(mainLayout);
}

/**
 * Loads the data for a given record
 *
 * @param laneVisibility Lane visibility record whose properties are to be loaded
 * @param minS Minimum "S" property for this record
 * @param maxS Maximum "S" property for this record
 */
void SettingsLaneVisibilityRecord::LoadData(LaneVisibility *laneVisibility, double minS, double maxS)
{
	if(laneVisibility!=NULL)
	{
		// Disconnects the "value changed" signals while the values are loaded
		disconnect(mS, SIGNAL(valueChanged(double)), this, SLOT(SChanged(double)));
		disconnect(mForward, SIGNAL(valueChanged(double)), this, SLOT(ForwardChanged(double)));
		disconnect(mBack, SIGNAL(valueChanged(double)), this, SLOT(BackChanged(double)));
		disconnect(mLeft, SIGNAL(valueChanged(double)), this, SLOT(LeftChanged(double)));
		disconnect(mRight, SIGNAL(valueChanged(double)), this, SLOT(RightChanged(double)));

		// Sets the record properties to the input widgets
		mLaneVisibility=laneVisibility;

		mS->setRange(minS,maxS);
		mS->setValue(mLaneVisibility->GetS());
		mForward->setValue(mLaneVisibility->GetForward());
		mBack->setValue(mLaneVisibility->GetBack());
		mLeft->setValue(mLaneVisibility->GetLeft());
		mRight->setValue(mLaneVisibility->GetRight());

		// Connects the "value changed" signals back
		connect(mS, SIGNAL(valueChanged(double)), this, SLOT(SChanged(double)));
		connect(mForward, SIGNAL(valueChanged(double)), this, SLOT(ForwardChanged(double)));
		connect(mBack, SIGNAL(valueChanged(double)), this, SLOT(BackChanged(double)));
		connect(mLeft, SIGNAL(valueChanged(double)), this, SLOT(LeftChanged(double)));
		connect(mRight, SIGNAL(valueChanged(double)), this, SLOT(RightChanged(double)));
	}
}

/**
 * Methods called when properties change
 */
void SettingsLaneVisibilityRecord::SChanged(double value)
{
	// Sets the new value 
	mLaneVisibility->SetS(value);
	// Emits "road changed" signal so the road gets redrawn
	emit RoadLaneVisibilityChanged(false);
}
void SettingsLaneVisibilityRecord::ForwardChanged(double value)
{
	mLaneVisibility->SetForward(value);
}
void SettingsLaneVisibilityRecord::BackChanged(double value)
{
	mLaneVisibility->SetBack(value);
}
void SettingsLaneVisibilityRecord::LeftChanged(double value)
{
	mLaneVisibility->SetLeft(value);
}
void SettingsLaneVisibilityRecord::RightChanged(double value)
{
	mLaneVisibility->SetRight(value);
}