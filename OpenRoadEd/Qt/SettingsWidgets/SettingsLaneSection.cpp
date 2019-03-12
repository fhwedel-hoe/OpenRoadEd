#include "SettingsLaneSection.h"
#include "moc_SettingsLaneSection.cpp"

/**
 * Initializes the properties panel and the UI elements
 */
SettingsLaneSection::SettingsLaneSection(QWidget *parent)
{
	// Resets the record
	mLaneSection=NULL;

	// Main vertical layout
	QVBoxLayout *mainLayout = new QVBoxLayout;

	//-------------------------------------------------
	// Group for settings
	QGroupBox *settingsGroup = new QGroupBox;
	settingsGroup->setSizePolicy(QSizePolicy::Preferred,QSizePolicy::Maximum);
	settingsGroup->setTitle(tr("Lane section settings"));

	mS=new QDoubleSpinBox;
	mS->setKeyboardTracking(false);
	mS->setDecimals(9);
	mS->setRange(0,1000000);
	
	// Form Layout inside group
	QFormLayout *settingsFormLayout = new QFormLayout;
	settingsFormLayout->addRow(tr("S:"),mS);	

	settingsGroup->setLayout(settingsFormLayout);
	//-------------------------------------------------
	// Group for help
	QGroupBox *helpGroup = new QGroupBox;
	helpGroup->setTitle(tr("Help"));

	QTextEdit *helpText = new QTextEdit;
	helpText->setSizePolicy(QSizePolicy::Preferred,QSizePolicy::Expanding);
	helpText->setReadOnly(true);
	helpText->setHtml("This record defines the characteristics of a road cross-section. It specifies the numbers and types of lanes and further features of the lanes. At least one record must be defined in order to use a road. A lane section record is valid until a new lane section record is defined."
						"<p><b>S</b> - start position (s-offset) [meters]</p>");
	
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
 * @param laneSection Lane section record whose properties are to be loaded
 * @param minS Minimum "S" property for this record
 * @param maxS Maximum "S" property for this record
 * @param first Set to true if it's the first lane section on the road
 */
void SettingsLaneSection::LoadData(LaneSection *laneSection, double minS, double maxS, bool first)
{
	if(laneSection!=NULL)
	{
		// Disconnects the "value changed" signals while the values are loaded
		disconnect(mS, SIGNAL(valueChanged(double)), this, SLOT(SChanged(double)));

		// Sets the record properties to the input widgets
		mLaneSection=laneSection;

		mS->setRange(minS,maxS);
		mS->setEnabled(!first);
		mS->setValue(mLaneSection->GetS());

		// Connects the "value changed" signals back
		connect(mS, SIGNAL(valueChanged(double)), this, SLOT(SChanged(double)));
	}
}

/**
 * Methods called when properties change
 */
void SettingsLaneSection::SChanged(double value)
{
	// Sets the new value 
	mLaneSection->SetS(value);
	// Emits "road changed" signal so the road gets redrawn
	emit RoadLaneSectionChanged(false);
}