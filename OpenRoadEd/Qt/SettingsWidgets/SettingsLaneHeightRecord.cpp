#include "SettingsLaneHeightRecord.h"
#include "moc_SettingsLaneHeightRecord.cpp"

/**
 * Initializes the properties panel and the UI elements
 */
SettingsLaneHeightRecord::SettingsLaneHeightRecord(QWidget *parent)
{
	// Resets the record
	mLaneHeight=NULL;

	// Main vertical layout
	QVBoxLayout *mainLayout = new QVBoxLayout;

	//-------------------------------------------------
	// Group for settings
	QGroupBox *settingsGroup = new QGroupBox;
	settingsGroup->setSizePolicy(QSizePolicy::Preferred,QSizePolicy::Maximum);
	settingsGroup->setTitle(tr("Lane height settings"));

	mS=new QDoubleSpinBox;
	mS->setKeyboardTracking(false);
	mS->setDecimals(9);
	mS->setRange(0,1000000);
	mInner=new QDoubleSpinBox;
	mInner->setKeyboardTracking(false);
	mInner->setDecimals(9);
	mInner->setRange(-1000,1000);
	mOuter=new QDoubleSpinBox;
	mOuter->setKeyboardTracking(false);
	mOuter->setDecimals(9);
	mOuter->setRange(-1000,1000);
	
	// Form Layout inside group
	QFormLayout *settingsFormLayout = new QFormLayout;
	settingsFormLayout->addRow(tr("S:"),mS);
	settingsFormLayout->addRow(tr("Inner:"),mInner);
	settingsFormLayout->addRow(tr("Outer:"),mOuter);
	
	settingsGroup->setLayout(settingsFormLayout);
	//-------------------------------------------------
	// Group for help
	QGroupBox *helpGroup = new QGroupBox;
	helpGroup->setTitle(tr("Help"));

	QTextEdit *helpText = new QTextEdit;
	helpText->setSizePolicy(QSizePolicy::Preferred,QSizePolicy::Expanding);
	helpText->setReadOnly(true);
	helpText->setHtml("This record defines the lane's offset from the plane defined by the chordline and elevation profiles . The parameters of this entry are valid until the next entry starts or the road’s chord line ends."
						"<p><b>S</b> - start position (s-offset from the current lane section) [meters]</p>"
						"<p><b>Inner</b> - inner offset from the road level [meters]</p>"
						"<p><b>Outer</b> - outer offset from the road level [meters]</p>");
	
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
 * @param laneHeight Lane height record whose properties are to be loaded
 * @param minS Minimum "S" property for this record
 * @param maxS Maximum "S" property for this record
 */
void SettingsLaneHeightRecord::LoadData(LaneHeight *laneHeight, double minS, double maxS)
{
	if(laneHeight!=NULL)
	{
		// Disconnects the "value changed" signals while the values are loaded
		disconnect(mS, SIGNAL(valueChanged(double)), this, SLOT(SChanged(double)));
		disconnect(mInner, SIGNAL(valueChanged(double)), this, SLOT(InnerChanged(double)));
		disconnect(mOuter, SIGNAL(valueChanged(double)), this, SLOT(OuterChanged(double)));

		// Sets the record properties to the input widgets
		mLaneHeight=laneHeight;

		mS->setRange(minS,maxS);
		mS->setValue(mLaneHeight->GetS());
		mInner->setValue(mLaneHeight->GetInner());
		mOuter->setValue(mLaneHeight->GetOuter());

		// Connects the "value changed" signals back
		connect(mS, SIGNAL(valueChanged(double)), this, SLOT(SChanged(double)));
		connect(mInner, SIGNAL(valueChanged(double)), this, SLOT(InnerChanged(double)));
		connect(mOuter, SIGNAL(valueChanged(double)), this, SLOT(OuterChanged(double)));
	}
}

/**
 * Methods called when properties change
 */
void SettingsLaneHeightRecord::SChanged(double value)
{
	// Sets the new value 
	mLaneHeight->SetS(value);
	// Emits "road changed" signal so the road gets redrawn
	emit RoadLaneHeightChanged(false);
}
void SettingsLaneHeightRecord::InnerChanged(double value)
{
	// See the first few methods in this group for details

	mLaneHeight->SetInner(value);
	emit RoadLaneHeightChanged(false);
}
void SettingsLaneHeightRecord::OuterChanged(double value)
{
	// See the first few methods in this group for details

	mLaneHeight->SetOuter(value);
	emit RoadLaneHeightChanged(false);
}