#include "SettingsLaneAccessRecord.h"
#include "moc_SettingsLaneAccessRecord.cpp"

/**
 * Initializes the properties panel and the UI elements
 */
SettingsLaneAccessRecord::SettingsLaneAccessRecord(QWidget *parent)
{
	// Resets the record
	mLaneAccess=NULL;

	// Main vertical layout
	QVBoxLayout *mainLayout = new QVBoxLayout;

	//-------------------------------------------------
	// Group for settings
	QGroupBox *settingsGroup = new QGroupBox;
	settingsGroup->setSizePolicy(QSizePolicy::Preferred,QSizePolicy::Maximum);
	settingsGroup->setTitle(tr("Lane access settings"));

	mS=new QDoubleSpinBox;
	mS->setKeyboardTracking(false);
	mS->setDecimals(9);
	mS->setRange(0,1000000);
	mRestriction=new QComboBox;
	mRestriction->insertItem(0,tr("simulator"));
	mRestriction->insertItem(1,tr("autonomous traffic"));
	mRestriction->insertItem(2,tr("pedestrian"));
	
	// Form Layout inside group
	QFormLayout *settingsFormLayout = new QFormLayout;
	settingsFormLayout->addRow(tr("S:"),mS);
	settingsFormLayout->addRow(tr("Restriction:"),mRestriction);
	
	settingsGroup->setLayout(settingsFormLayout);
	//-------------------------------------------------
	// Group for help
	QGroupBox *helpGroup = new QGroupBox;
	helpGroup->setTitle(tr("Help"));

	QTextEdit *helpText = new QTextEdit;
	helpText->setSizePolicy(QSizePolicy::Preferred,QSizePolicy::Expanding);
	helpText->setReadOnly(true);
	helpText->setHtml("This record defines the lane's access restriction to certain types of road users. The parameters of this entry are valid until the next entry starts or the road’s chord line ends."
						"<p><b>S</b> - start position (s-offset from the current lane section) [meters]</p>"
						"<p><b>Restriction</b> - identifier of the participant to which the restriction applies (string)</p>");
	
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
 * @param laneAccess Lane access record whose properties are to be loaded
 * @param minS Minimum "S" property for this record
 * @param maxS Maximum "S" property for this record
 */
void SettingsLaneAccessRecord::LoadData(LaneAccess *laneAccess, double minS, double maxS)
{
	if(laneAccess!=NULL)
	{
		// Disconnects the "value changed" signals while the values are loaded
		disconnect(mS, SIGNAL(valueChanged(double)), this, SLOT(SChanged(double)));
		disconnect(mRestriction, SIGNAL(currentIndexChanged(const QString &)), this, SLOT(RestrictionChanged(const QString &)));


		// Sets the record properties to the input widgets
		mLaneAccess=laneAccess;

		mS->setRange(minS,maxS);
		mS->setValue(mLaneAccess->GetS());
		
		if(mLaneAccess->GetRestriction().compare("simulator")==0) mRestriction->setCurrentIndex(0);
		else if(mLaneAccess->GetRestriction().compare("autonomous traffic")==0) mRestriction->setCurrentIndex(1);
		else if(mLaneAccess->GetRestriction().compare("pedestrian")==0) mRestriction->setCurrentIndex(2);

		// Connects the "value changed" signals back
		connect(mS, SIGNAL(valueChanged(double)), this, SLOT(SChanged(double)));
		connect(mRestriction, SIGNAL(currentIndexChanged(const QString &)), this, SLOT(RestrictionChanged(const QString &)));
	}
}

/**
 * Methods called when properties change
 */
void SettingsLaneAccessRecord::SChanged(double value)
{
	// Sets the new value 
	mLaneAccess->SetS(value);
	// Emits "road changed" signal so the road gets redrawn
	emit RoadLaneAccessChanged(false);
}
void SettingsLaneAccessRecord::RestrictionChanged(const QString &text)
{
	mLaneAccess->SetRestriction(text.toStdString());
}