#include "SettingsLaneSpeedRecord.h"
#include "moc_SettingsLaneSpeedRecord.cpp"

/**
 * Initializes the properties panel and the UI elements
 */
SettingsLaneSpeedRecord::SettingsLaneSpeedRecord(QWidget *parent)
{
	// Resets the record
	mLaneSpeed=NULL;

	// Main vertical layout
	QVBoxLayout *mainLayout = new QVBoxLayout;

	//-------------------------------------------------
	// Group for settings
	QGroupBox *settingsGroup = new QGroupBox;
	settingsGroup->setSizePolicy(QSizePolicy::Preferred,QSizePolicy::Maximum);
	settingsGroup->setTitle(tr("Lane speed settings"));

	mS=new QDoubleSpinBox;
	mS->setKeyboardTracking(false);
	mS->setDecimals(9);
	mS->setRange(0,1000000);
	mMax=new QDoubleSpinBox;
	mMax->setKeyboardTracking(false);
	mMax->setRange(0,1000000);
	
	// Form Layout inside group
	QFormLayout *settingsFormLayout = new QFormLayout;
	settingsFormLayout->addRow(tr("S:"),mS);
	settingsFormLayout->addRow(tr("Max:"),mMax);
	
	settingsGroup->setLayout(settingsFormLayout);
	//-------------------------------------------------
	// Group for help
	QGroupBox *helpGroup = new QGroupBox;
	helpGroup->setTitle(tr("Help"));

	QTextEdit *helpText = new QTextEdit;
	helpText->setSizePolicy(QSizePolicy::Preferred,QSizePolicy::Expanding);
	helpText->setReadOnly(true);
	helpText->setHtml("This record defines the lane's maximum allowed speed. The parameters of this entry are valid until the next entry starts or the road’s chord line ends."
						"<p><b>S</b> - start position (s-offset from the current lane section) [meters]</p>"
						"<p><b>Max</b> - maximum allowed speed [meters/second]</p>");
	
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
 * @param laneSpeed Lane speed record whose properties are to be loaded
 * @param minS Minimum "S" property for this record
 * @param maxS Maximum "S" property for this record
 */
void SettingsLaneSpeedRecord::LoadData(LaneSpeed *laneSpeed, double minS, double maxS)
{
	if(laneSpeed!=NULL)
	{
		// Disconnects the "value changed" signals while the values are loaded
		disconnect(mS, SIGNAL(valueChanged(double)), this, SLOT(SChanged(double)));
		disconnect(mMax, SIGNAL(valueChanged(double)), this, SLOT(MaxChanged(double)));

		// Sets the record properties to the input widgets
		mLaneSpeed=laneSpeed;

		mS->setRange(minS,maxS);
		mS->setValue(mLaneSpeed->GetS());
		mMax->setValue(mLaneSpeed->GetMax());

		// Connects the "value changed" signals back
		connect(mS, SIGNAL(valueChanged(double)), this, SLOT(SChanged(double)));
		connect(mMax, SIGNAL(valueChanged(double)), this, SLOT(MaxChanged(double)));
	}
}

/**
 * Methods called when properties change
 */
void SettingsLaneSpeedRecord::SChanged(double value)
{
	// Sets the new value 
	mLaneSpeed->SetS(value);
	// Emits "road changed" signal so the road gets redrawn
	emit RoadLaneSpeedChanged(false);
}

void SettingsLaneSpeedRecord::MaxChanged(double value)
{
	mLaneSpeed->SetMax(value);
}