#include "SettingsLane.h"
#include "moc_SettingsLane.cpp"

/**
 * Initializes the properties panel and the UI elements
 */
SettingsLane::SettingsLane(QWidget *parent)
{
	// Resets the record
	mLane=NULL;

	// Main vertical layout
	QVBoxLayout *mainLayout = new QVBoxLayout;

	//-------------------------------------------------
	// Group for settings
	QGroupBox *settingsGroup = new QGroupBox;
	settingsGroup->setSizePolicy(QSizePolicy::Preferred,QSizePolicy::Maximum);
	settingsGroup->setTitle(tr("Lane settings settings"));

	mId=new QSpinBox;
	mId->setKeyboardTracking(false);
	mId->setRange(-100,100);
	mId->setDisabled(true);
	mType=new QComboBox;
	mType->insertItem(0,tr("none"));
	mType->insertItem(1,tr("driving"));
	mType->insertItem(2,tr("stop"));
	mType->insertItem(3,tr("shoulder"));
	mType->insertItem(4,tr("biking"));
	mType->insertItem(5,tr("sidewalk"));
	mType->insertItem(6,tr("border"));
	mType->insertItem(7,tr("restricted"));
	mType->insertItem(8,tr("parking"));
	mType->insertItem(9,tr("mwyEntry"));
	mType->insertItem(10,tr("mwyExit"));
	mType->insertItem(11,tr("special1"));
	mType->insertItem(12,tr("special2"));
	mType->insertItem(13,tr("special3"));
	mLevel=new QComboBox;
	mLevel->insertItem(0,tr("false"));
	mLevel->insertItem(1,tr("true"));

	mPredecessor = new QGroupBox;
	mPredecessor->setTitle(tr("Predecessor"));
	mPredecessor->setCheckable(true);
	mPredecessor->setChecked(false);
	mPredecessorId=new QSpinBox;
	mPredecessorId->setKeyboardTracking(false);
	mPredecessorId->setRange(-100,100);
	// Form Layout inside group PREDECESSOR
	QFormLayout *settingsPredecessorLayout = new QFormLayout;
	settingsPredecessorLayout->addRow(tr("Id:"),mPredecessorId);
	mPredecessor->setLayout(settingsPredecessorLayout);

	mSuccessor = new QGroupBox;
	mSuccessor->setTitle(tr("Successor"));
	mSuccessor->setCheckable(true);
	mSuccessor->setChecked(false);
	mSuccessorId=new QSpinBox;
	mSuccessorId->setKeyboardTracking(false);
	mSuccessorId->setRange(-100,100);
	// Form Layout inside group Successor
	QFormLayout *settingsSuccessorLayout = new QFormLayout;
	settingsSuccessorLayout->addRow(tr("Id:"),mSuccessorId);
	mSuccessor->setLayout(settingsSuccessorLayout);
	
	// Form Layout inside group
	QFormLayout *settingsFormLayout = new QFormLayout;
	settingsFormLayout->addRow(tr("Id:"),mId);
	settingsFormLayout->addRow(tr("Type:"),mType);
	settingsFormLayout->addRow(tr("Level:"),mLevel);

	QVBoxLayout *settingsGroupLayout = new QVBoxLayout;
	settingsGroupLayout->addLayout(settingsFormLayout);
	settingsGroupLayout->addWidget(mPredecessor);
	settingsGroupLayout->addWidget(mSuccessor);

	settingsGroup->setLayout(settingsGroupLayout);
	//-------------------------------------------------
	// Group for help
	QGroupBox *helpGroup = new QGroupBox;
	helpGroup->setTitle(tr("Help"));

	QTextEdit *helpText = new QTextEdit;
	helpText->setSizePolicy(QSizePolicy::Preferred,QSizePolicy::Expanding);
	helpText->setReadOnly(true);
	helpText->setHtml("This record defines a lane."
						"<p><b>Id</b> - determines it's position on the road going from the center of the road to it's edges (int)</p>"
						"<p><b>Type</b> - type of the lane</p>"
						"<p><b>Level</b> - set to true to keep the lane on level (ignore crossfall or superelevation)</p>"
						"<p><b>Predecessor</b> - check if this lane has a predecessor</p>"
						"<p><b>Predecessor id</b> - identifier of the predecessor</p>"
						"<p><b>Successor</b> - check if this lane has a successor</p>"
						"<p><b>Successor id</b> - identifier of the successor</p>");
	
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
 * @param lane Lane record whose properties are to be loaded
 */
void SettingsLane::LoadData(Lane *lane)
{
	if(lane!=NULL)
	{
		// Disconnects the "value changed" signals while the values are loaded
		disconnect(mId, SIGNAL(valueChanged(int)), this, SLOT(IdChanged(int)));
		disconnect(mType, SIGNAL(currentIndexChanged(const QString &)), this, SLOT(TypeChanged(const QString &)));
		disconnect(mLevel, SIGNAL(currentIndexChanged(const QString &)), this, SLOT(LevelChanged(const QString &)));
		disconnect(mPredecessor, SIGNAL(clicked(bool)), this, SLOT(PredecessorChanged(bool)));
		disconnect(mPredecessorId, SIGNAL(valueChanged(int)), this, SLOT(PredecessorIdChanged(int)));
		disconnect(mSuccessor, SIGNAL(clicked(bool)), this, SLOT(SuccessorChanged(bool)));
		disconnect(mSuccessorId, SIGNAL(valueChanged(int)), this, SLOT(SuccessorIdChanged(int)));


		// Sets the record properties to the input widgets
		mLane=lane;

		mId->setValue(mLane->GetId());

		if(mLane->GetType().compare("none")==0) mType->setCurrentIndex(0);
		else if(mLane->GetType().compare("driving")==0) mType->setCurrentIndex(1);
		else if(mLane->GetType().compare("stop")==0) mType->setCurrentIndex(2);
		else if(mLane->GetType().compare("shoulder")==0) mType->setCurrentIndex(3);
		else if(mLane->GetType().compare("biking")==0) mType->setCurrentIndex(4);
		else if(mLane->GetType().compare("sidewalk")==0) mType->setCurrentIndex(5);
		else if(mLane->GetType().compare("border")==0) mType->setCurrentIndex(6);
		else if(mLane->GetType().compare("restricted")==0) mType->setCurrentIndex(7);
		else if(mLane->GetType().compare("parking")==0) mType->setCurrentIndex(8);
		else if(mLane->GetType().compare("mwyEntry")==0) mType->setCurrentIndex(9);
		else if(mLane->GetType().compare("mwyExit")==0) mType->setCurrentIndex(10);
		else if(mLane->GetType().compare("special1")==0) mType->setCurrentIndex(11);
		else if(mLane->GetType().compare("special2")==0) mType->setCurrentIndex(12);
		else if(mLane->GetType().compare("special3")==0) mType->setCurrentIndex(13);

		if(mLane->GetLevel()==false) mLevel->setCurrentIndex(0);
		else if(mLane->GetLevel()==true) mLevel->setCurrentIndex(1);
		
		if(mLane->IsPredecessorSet())
		{
			mPredecessor->setChecked(true);
			mPredecessorId->setValue(mLane->GetPredecessor());
		}
		else mPredecessor->setChecked(false);

		if(mLane->IsSuccessorSet())
		{
			mSuccessor->setChecked(true);
			mSuccessorId->setValue(mLane->GetSuccessor());
		}
		else mSuccessor->setChecked(false);


		// Connects the "value changed" signals back
		connect(mId, SIGNAL(valueChanged(int)), this, SLOT(IdChanged(int)));
		connect(mType, SIGNAL(currentIndexChanged(const QString &)), this, SLOT(TypeChanged(const QString &)));
		connect(mLevel, SIGNAL(currentIndexChanged(const QString &)), this, SLOT(LevelChanged(const QString &)));
		connect(mPredecessor, SIGNAL(clicked(bool)), this, SLOT(PredecessorChanged(bool)));
		connect(mPredecessorId, SIGNAL(valueChanged(int)), this, SLOT(PredecessorIdChanged(int)));
		connect(mSuccessor, SIGNAL(clicked(bool)), this, SLOT(SuccessorChanged(bool)));
		connect(mSuccessorId, SIGNAL(valueChanged(int)), this, SLOT(SuccessorIdChanged(int)));
	}
}

/**
 * Methods called when properties change
 */
void SettingsLane::IdChanged(int value)
{
	mLane->SetId(value);
}
void SettingsLane::TypeChanged(const QString & text)
{
	// Sets new value
	mLane->SetType(text.toStdString());
	// Emits "road changed" signal so the road gets redrawn
	emit RoadLaneChanged(false);
}
void SettingsLane::LevelChanged(const QString & text)
{
	// See the first few methods in this group for details

	if(text.compare("true")==0) mLane->SetLevel(true);
	else mLane->SetLevel(false);
	emit RoadLaneChanged(false);
}

void SettingsLane::PredecessorChanged(bool on)
{
	if(on)
	{
		mLane->SetPredecessor(mPredecessorId->value());
	}
	else
	{
		mLane->RemovePredecessor();
	}
}
void SettingsLane::PredecessorIdChanged(int value)
{
	// Sets the new value
	mLane->SetPredecessor(value);
}

void SettingsLane::SuccessorChanged(bool on)
{
	if(on)
	{
		mLane->SetSuccessor(mSuccessorId->value());
	}
	else
	{
		mLane->RemoveSuccessor();
	}
}
void SettingsLane::SuccessorIdChanged(int value)
{
	// Sets the new value
	mLane->SetSuccessor(value);
}