#include "SettingsRoadTypeRecord.h"
#include "moc_SettingsRoadTypeRecord.cpp"

/**
 * Initializes the properties panel and the UI elements
 */
SettingsRoadTypeRecord::SettingsRoadTypeRecord(QWidget *parent)
{
	// Resets the record
	mRoadType=NULL;

	// Main vertical layout
	QVBoxLayout *mainLayout = new QVBoxLayout;

	//-------------------------------------------------
	// Group for settings
	QGroupBox *settingsGroup = new QGroupBox;
	settingsGroup->setSizePolicy(QSizePolicy::Preferred,QSizePolicy::Maximum);
	settingsGroup->setTitle(tr("Road type settings"));

	mS=new QDoubleSpinBox;
	mS->setKeyboardTracking(false);
	mS->setDecimals(9);
	mS->setRange(0,1000000);
	mType=new QComboBox;
	mType->insertItem(0,tr("unknown"));
	mType->insertItem(1,tr("rural"));
	mType->insertItem(2,tr("motorway"));
	mType->insertItem(3,tr("town"));
	mType->insertItem(4,tr("lowSpeed"));
	mType->insertItem(5,tr("predestrian"));
	
	// Form Layout inside group
	QFormLayout *settingsFormLayout = new QFormLayout;
	settingsFormLayout->addRow(tr("S:"),mS);
	settingsFormLayout->addRow(tr("Restriction:"),mType);
	
	settingsGroup->setLayout(settingsFormLayout);
	//-------------------------------------------------
	// Group for help
	QGroupBox *helpGroup = new QGroupBox;
	helpGroup->setTitle(tr("Help"));

	QTextEdit *helpText = new QTextEdit;
	helpText->setSizePolicy(QSizePolicy::Preferred,QSizePolicy::Expanding);
	helpText->setReadOnly(true);
	helpText->setHtml("This record sets the type of the road. The type may change over roads entire length. It is valid until a new road type record is provided or the road ends."
						"<p><b>S</b> - start position (s-offset) [meters]</p>"
						"<p><b>Restriction</b> - the type of the road</p>");
	
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
 * @param roadType Road type record whose properties are to be loaded
 */
void SettingsRoadTypeRecord::LoadData(RoadType *roadType, double minS, double maxS)
{
	if(roadType!=NULL)
	{
		// Disconnects the "value changed" signals while the values are loaded
		disconnect(mS, SIGNAL(valueChanged(double)), this, SLOT(SChanged(double)));
		disconnect(mType, SIGNAL(currentIndexChanged(const QString &)), this, SLOT(TypeChanged(const QString &)));

		// Sets the record properties to the input widgets
		mRoadType=roadType;

		mS->setRange(minS, maxS);
		mS->setValue(mRoadType->GetS());
		
		if(mRoadType->GetType().compare("unknown")==0) mType->setCurrentIndex(0);
		else if(mRoadType->GetType().compare("rural")==0) mType->setCurrentIndex(1);
		else if(mRoadType->GetType().compare("motorway")==0) mType->setCurrentIndex(2);
		else if(mRoadType->GetType().compare("town")==0) mType->setCurrentIndex(3);
		else if(mRoadType->GetType().compare("lowSpeed")==0) mType->setCurrentIndex(4);
		else if(mRoadType->GetType().compare("pedestrian")==0) mType->setCurrentIndex(5);

		// Connects the "value changed" signals back
		connect(mS, SIGNAL(valueChanged(double)), this, SLOT(SChanged(double)));
		connect(mType, SIGNAL(currentIndexChanged(const QString &)), this, SLOT(TypeChanged(const QString &)));
	}
}

/**
 * Methods called when properties change
 */
void SettingsRoadTypeRecord::SChanged(double value)
{
	// Sets the new value 
	mRoadType->SetS(value);
	// Emits "road changed" signal so the road gets redrawn
	emit RoadRoadTypeChanged(false);
}
void SettingsRoadTypeRecord::TypeChanged(const QString &text)
{
	// See the first few methods in this group for details

	mRoadType->SetType(text.toStdString());
	emit RoadRoadTypeChanged(false);
}