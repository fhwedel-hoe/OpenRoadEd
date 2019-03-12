#include "SettingsRoad.h"
#include "moc_SettingsRoad.cpp"

/**
 * Initializes the properties panel and the UI elements
 */
SettingsRoad::SettingsRoad(OpenDrive *openDrive)
{
	// Resets the record
	mRoad=NULL;

	// Saves a reference to OpenDrive object
	mOpenDrive=openDrive;

	// Main vertical layout
	QVBoxLayout *mainLayout = new QVBoxLayout;

	//-------------------------------------------------
	// Group for settings
	QGroupBox *settingsGroup = new QGroupBox;
	settingsGroup->setSizePolicy(QSizePolicy::Preferred,QSizePolicy::Maximum);
	settingsGroup->setTitle(tr("Road Settings"));

	mName = new QLineEdit;
	mId = new QLineEdit;
	mLength = new QLineEdit;
	mLength->setDisabled(true);
	mJunction = new QLineEdit;

	mPredecessor = new QGroupBox;
	mPredecessor->setTitle(tr("Predecessor"));
	mPredecessor->setCheckable(true);
	mPredecessor->setChecked(false);
	QHBoxLayout *lPredecessorLayout = new QHBoxLayout;
	mPredecessorId = new QLineEdit;
	mBrowsePredecessor = new QToolButton();
	mBrowsePredecessor->setFocusPolicy(Qt::StrongFocus);
	mBrowsePredecessor->setIcon(QIcon("Resources/Icons/Folder1.png"));
	mBrowsePredecessor->setToolTip("Browse for predecessor");
	lPredecessorLayout->addWidget(mPredecessorId);
	lPredecessorLayout->addWidget(mBrowsePredecessor);
	mPredecessorType = new QComboBox;
	mPredecessorType->insertItem(0,tr("road"));
	mPredecessorType->insertItem(1,tr("junction"));
	mPredecessorContactPoint = new QComboBox;
	mPredecessorContactPoint->insertItem(0,tr("start"));
	mPredecessorContactPoint->insertItem(1,tr("end"));
	// Form Layout inside group PREDECESSOR
	QFormLayout *settingsPredecessorLayout = new QFormLayout;
	settingsPredecessorLayout->addRow(tr("Type:"),mPredecessorType);
	settingsPredecessorLayout->addRow(tr("Id:"),lPredecessorLayout);
	settingsPredecessorLayout->addRow(tr("Contact Point:"),mPredecessorContactPoint);
	mPredecessor->setLayout(settingsPredecessorLayout);

	mSuccessor = new QGroupBox;
	mSuccessor->setTitle(tr("Successor"));
	mSuccessor->setCheckable(true);
	mSuccessor->setChecked(false);
	QHBoxLayout *lSuccessorLayout = new QHBoxLayout;
	mSuccessorId = new QLineEdit;
	mBrowseSuccessor = new QToolButton();
	mBrowseSuccessor->setFocusPolicy(Qt::StrongFocus);
	mBrowseSuccessor->setIcon(QIcon("Resources/Icons/Folder1.png"));
	mBrowseSuccessor->setToolTip("Browse for successor");
	lSuccessorLayout->addWidget(mSuccessorId);
	lSuccessorLayout->addWidget(mBrowseSuccessor);
	mSuccessorType = new QComboBox;
	mSuccessorType->insertItem(0,tr("road"));
	mSuccessorType->insertItem(1,tr("junction"));
	mSuccessorContactPoint = new QComboBox;
	mSuccessorContactPoint->insertItem(0,tr("start"));
	mSuccessorContactPoint->insertItem(1,tr("end"));
	// Form Layout inside group Successor
	QFormLayout *settingsSuccessorLayout = new QFormLayout;
	settingsSuccessorLayout->addRow(tr("Type:"),mSuccessorType);
	settingsSuccessorLayout->addRow(tr("Id:"),lSuccessorLayout);
	settingsSuccessorLayout->addRow(tr("Contact Point:"),mSuccessorContactPoint);
	mSuccessor->setLayout(settingsSuccessorLayout);

	mNeighbor1 = new QGroupBox;
	mNeighbor1->setTitle(tr("Neighbor1"));
	mNeighbor1->setCheckable(true);
	mNeighbor1->setChecked(false);
	QHBoxLayout *lNeighbor1Layout = new QHBoxLayout;
	mNeighbor1Id = new QLineEdit;
	mBrowseNeighbor1 = new QToolButton();
	mBrowseNeighbor1->setFocusPolicy(Qt::StrongFocus);
	mBrowseNeighbor1->setIcon(QIcon("Resources/Icons/Folder1.png"));
	mBrowseNeighbor1->setToolTip("Browse for neighbor 1");
	lNeighbor1Layout->addWidget(mNeighbor1Id);
	lNeighbor1Layout->addWidget(mBrowseNeighbor1);
	mNeighbor1Side = new QComboBox;
	mNeighbor1Side->insertItem(0,tr("left"));
	mNeighbor1Side->insertItem(1,tr("right"));
	mNeighbor1Direction = new QComboBox;
	mNeighbor1Direction->insertItem(0,tr("same"));
	mNeighbor1Direction->insertItem(1,tr("opposite"));
	// Form Layout inside group Neighbor1
	QFormLayout *settingsNeighbor1Layout = new QFormLayout;
	settingsNeighbor1Layout->addRow(tr("Side:"),mNeighbor1Side);
	settingsNeighbor1Layout->addRow(tr("Id:"),lNeighbor1Layout);
	settingsNeighbor1Layout->addRow(tr("Direction:"),mNeighbor1Direction);
	mNeighbor1->setLayout(settingsNeighbor1Layout);

	mNeighbor2 = new QGroupBox;
	mNeighbor2->setTitle(tr("Neighbor2"));
	mNeighbor2->setCheckable(true);
	mNeighbor2->setChecked(false);
	QHBoxLayout *lNeighbor2Layout = new QHBoxLayout;
	mNeighbor2Id = new QLineEdit;
	mBrowseNeighbor2 = new QToolButton();
	mBrowseNeighbor2->setFocusPolicy(Qt::StrongFocus);
	mBrowseNeighbor2->setIcon(QIcon("Resources/Icons/Folder1.png"));
	mBrowseNeighbor2->setToolTip("Browse for neighbor 1");
	lNeighbor2Layout->addWidget(mNeighbor2Id);
	lNeighbor2Layout->addWidget(mBrowseNeighbor2);
	mNeighbor2Side = new QComboBox;
	mNeighbor2Side->insertItem(0,tr("left"));
	mNeighbor2Side->insertItem(1,tr("right"));
	mNeighbor2Direction = new QComboBox;
	mNeighbor2Direction->insertItem(0,tr("same"));
	mNeighbor2Direction->insertItem(1,tr("opposite"));
	// Form Layout inside group Neighbor2
	QFormLayout *settingsNeighbor2Layout = new QFormLayout;
	settingsNeighbor2Layout->addRow(tr("Side:"),mNeighbor2Side);
	settingsNeighbor2Layout->addRow(tr("Id:"),lNeighbor2Layout);
	settingsNeighbor2Layout->addRow(tr("Direction:"),mNeighbor2Direction);
	mNeighbor2->setLayout(settingsNeighbor2Layout);


	// Form Layout inside group
	QFormLayout *settingsFormLayout = new QFormLayout;
	settingsFormLayout->addRow(tr("Name:"),mName);
	settingsFormLayout->addRow(tr("Id:"),mId);
	settingsFormLayout->addRow(tr("Length:"),mLength);
	settingsFormLayout->addRow(tr("Junction:"),mJunction);

	QVBoxLayout *settingsGroupLayout = new QVBoxLayout;
	settingsGroupLayout->addLayout(settingsFormLayout);
	settingsGroupLayout->addWidget(mPredecessor);
	settingsGroupLayout->addWidget(mSuccessor);
	settingsGroupLayout->addWidget(mNeighbor1);
	settingsGroupLayout->addWidget(mNeighbor2);

	settingsGroup->setLayout(settingsGroupLayout);
	//-------------------------------------------------
	// Group for help
	QGroupBox *helpGroup = new QGroupBox;
	helpGroup->setTitle(tr("Help"));

	QTextEdit *helpText = new QTextEdit;
	helpText->setSizePolicy(QSizePolicy::Preferred,QSizePolicy::Expanding);
	helpText->setReadOnly(true);
	helpText->setHtml("This record is the principal containers of information about a road."
						"<p><b>Name</b> - name of the road</p>"
						"<p><b>Id</b> - unique identifier of the road (string)</p>"
						"<p><b>Length</b> - length of the road (calculated automatically) [meters]</p>"
						"<p><b>Junction</b> - identifier of the junction, to which this road belongs, or -1 if none (string)</p>"
						"<p><b>Predecessor</b> - check if this road has a predecessor</p>"
						"<p><b>Predecessor type</b> - type of predecessor</p>"
						"<p><b>Predecessor id</b> - identifier of the predecessor (string)</p>"
						"<p><b>Predecessor contact point</b> - contact point of the predecessor</p>"
						"<p><b>Successor</b> - check if this road has a successor</p>"
						"<p><b>Successor type</b> - type of successor</p>"
						"<p><b>Successor id</b> - identifier of the successor (string)</p>"
						"<p><b>Successor contact point</b> - contact point of the successor</p>"
						"<p><b>Neighbor 1</b> - check if this road has a neighbor</p>"
						"<p><b>Neighbor 1 side</b> - side of the neighbor</p>"
						"<p><b>Neighbor 1 id</b> - identifier of the neighbor (string)</p>"
						"<p><b>Neighbor 1 direction</b> - direction of the neighbor</p>"
						"<p><b>Neighbor 2</b> - check if this road has a second neighbor</p>"
						"<p><b>Neighbor 2 side</b> - side of the neighbor</p>"
						"<p><b>Neighbor 2 id</b> - identifier of the neighbor (string)</p>"
						"<p><b>Neighbor 2 direction</b> - direction of the neighbor</p>");
	
	QVBoxLayout *helpLayout = new QVBoxLayout;
	helpLayout->addWidget(helpText);

	helpGroup->setLayout(helpLayout);
	//-------------------------------------------------

	mainLayout->addWidget(settingsGroup);
	mainLayout->addWidget(helpGroup);
	setLayout(mainLayout);

	// Connects interface signals and slots
	connect(mBrowsePredecessor, SIGNAL(clicked()), this, SLOT(BrowseForPredecessor()));
	connect(mBrowseSuccessor, SIGNAL(clicked()), this, SLOT(BrowseForSuccessor()));
	connect(mBrowseNeighbor1, SIGNAL(clicked()), this, SLOT(BrowseForNeighbor1()));
	connect(mBrowseNeighbor2, SIGNAL(clicked()), this, SLOT(BrowseForNeighbor2()));
}

/**
 * Loads the data for a given record
 *
 * @param road Road record whose properties are to be loaded
 */
void SettingsRoad::LoadData(Road *road)
{
	if(road!=NULL)
	{
		// Disconnects the "value changed" signals while the values are loaded
		disconnect(mName, SIGNAL(editingFinished()), this, SLOT(NameChanged()));
		disconnect(mId, SIGNAL(editingFinished()), this, SLOT(IdChanged()));
		disconnect(mLength, SIGNAL(editingFinished()), this, SLOT(LengthChanged()));
		disconnect(mJunction, SIGNAL(editingFinished()), this, SLOT(JunctionChanged()));

		disconnect(mPredecessor, SIGNAL(clicked(bool)), this, SLOT(PredecessorChanged(bool)));
		disconnect(mPredecessorId, SIGNAL(editingFinished()), this, SLOT(PredecessorIdChanged()));
		disconnect(mPredecessorType, SIGNAL(currentIndexChanged(const QString &)), this, SLOT(PredecessorTypeChanged(const QString &)));
		disconnect(mPredecessorContactPoint, SIGNAL(currentIndexChanged(const QString &)), this, SLOT(PredecessorContactPointChanged(const QString &)));

		disconnect(mSuccessor, SIGNAL(clicked(bool)), this, SLOT(SuccessorChanged(bool)));
		disconnect(mSuccessorId, SIGNAL(editingFinished()), this, SLOT(SuccessorIdChanged()));
		disconnect(mSuccessorType, SIGNAL(currentIndexChanged(const QString &)), this, SLOT(SuccessorTypeChanged(const QString &)));
		disconnect(mSuccessorContactPoint, SIGNAL(currentIndexChanged(const QString &)), this, SLOT(SuccessorContactPointChanged(const QString &)));

		disconnect(mNeighbor1, SIGNAL(clicked(bool)), this, SLOT(Neighbor1Changed(bool)));
		disconnect(mNeighbor1Id, SIGNAL(editingFinished()), this, SLOT(Neighbor1IdChanged()));
		disconnect(mNeighbor1Side, SIGNAL(currentIndexChanged(const QString &)), this, SLOT(Neighbor1SideChanged(const QString &)));
		disconnect(mNeighbor1Direction, SIGNAL(currentIndexChanged(const QString &)), this, SLOT(Neighbor1DirectionChanged(const QString &)));

		disconnect(mNeighbor2, SIGNAL(clicked(bool)), this, SLOT(Neighbor2Changed(bool)));
		disconnect(mNeighbor2Id, SIGNAL(editingFinished()), this, SLOT(Neighbor2IdChanged()));
		disconnect(mNeighbor2Side, SIGNAL(currentIndexChanged(const QString &)), this, SLOT(Neighbor2SideChanged(const QString &)));
		disconnect(mNeighbor2Direction, SIGNAL(currentIndexChanged(const QString &)), this, SLOT(Neighbor2DirectionChanged(const QString &)));


		// Sets the record properties to the input widgets
		mRoad=road;

		mName->setText(road->GetRoadName().c_str());
		mId->setText(road->GetRoadId().c_str());
		mLength->setText(QString("%1").arg(road->GetRoadLength()));
		mJunction->setText(road->GetRoadJunction().c_str());

		RoadLink *lPredecessor = road->GetPredecessor();
		if(lPredecessor!=NULL)
		{
			mPredecessor->setChecked(true);
			mPredecessorId->setText(lPredecessor->GetElementId().c_str());
			if(lPredecessor->GetElementType().compare("road")==0) mPredecessorType->setCurrentIndex(0);
			else mPredecessorType->setCurrentIndex(1);
			if(lPredecessor->GetContactPoint().compare("start")==0) mPredecessorContactPoint->setCurrentIndex(0);
			else mPredecessorContactPoint->setCurrentIndex(1);
		}
		else mPredecessor->setChecked(false);

		RoadLink *lSuccessor = road->GetSuccessor();
		if(lSuccessor!=NULL)
		{
			mSuccessor->setChecked(true);
			mSuccessorId->setText(lSuccessor->GetElementId().c_str());
			if(lSuccessor->GetElementType().compare("road")==0) mSuccessorType->setCurrentIndex(0);
			else mSuccessorType->setCurrentIndex(1);
			if(lSuccessor->GetContactPoint().compare("start")==0) mSuccessorContactPoint->setCurrentIndex(0);
			else mSuccessorContactPoint->setCurrentIndex(1);
		}
		else mSuccessor->setChecked(false);

		RoadNeighbor *lNeighbor1 = road->GetNeighbor1();
		if(lNeighbor1!=NULL)
		{
			mNeighbor1->setChecked(true);
			mNeighbor1Id->setText(lNeighbor1->GetElementId().c_str());
			if(lNeighbor1->GetSide().compare("left")==0) mNeighbor1Side->setCurrentIndex(0);
			else mNeighbor1Side->setCurrentIndex(1);
			if(lNeighbor1->GetDirection().compare("same")==0) mNeighbor1Direction->setCurrentIndex(0);
			else mNeighbor1Direction->setCurrentIndex(1);
		}
		else mNeighbor1->setChecked(false);

		RoadNeighbor *lNeighbor2 = road->GetNeighbor2();
		if(lNeighbor2!=NULL)
		{
			mNeighbor2->setChecked(true);
			mNeighbor2Id->setText(lNeighbor2->GetElementId().c_str());
			if(lNeighbor2->GetSide().compare("left")==0) mNeighbor2Side->setCurrentIndex(0);
			else mNeighbor2Side->setCurrentIndex(1);
			if(lNeighbor2->GetDirection().compare("same")==0) mNeighbor2Direction->setCurrentIndex(0);
			else mNeighbor2Direction->setCurrentIndex(1);
		}
		else mNeighbor2->setChecked(false);

		// Connects the "value changed" signals back
		connect(mName, SIGNAL(editingFinished()), this, SLOT(NameChanged()));
		connect(mId, SIGNAL(editingFinished()), this, SLOT(IdChanged()));
		connect(mLength, SIGNAL(editingFinished()), this, SLOT(LengthChanged()));
		connect(mJunction, SIGNAL(editingFinished()), this, SLOT(JunctionChanged()));

		connect(mPredecessor, SIGNAL(clicked(bool)), this, SLOT(PredecessorChanged(bool)));
		connect(mPredecessorId, SIGNAL(editingFinished()), this, SLOT(PredecessorIdChanged()));
		connect(mPredecessorType, SIGNAL(currentIndexChanged(const QString &)), this, SLOT(PredecessorTypeChanged(const QString &)));
		connect(mPredecessorContactPoint, SIGNAL(currentIndexChanged(const QString &)), this, SLOT(PredecessorContactPointChanged(const QString &)));

		connect(mSuccessor, SIGNAL(clicked(bool)), this, SLOT(SuccessorChanged(bool)));
		connect(mSuccessorId, SIGNAL(editingFinished()), this, SLOT(SuccessorIdChanged()));
		connect(mSuccessorType, SIGNAL(currentIndexChanged(const QString &)), this, SLOT(SuccessorTypeChanged(const QString &)));
		connect(mSuccessorContactPoint, SIGNAL(currentIndexChanged(const QString &)), this, SLOT(SuccessorContactPointChanged(const QString &)));

		connect(mNeighbor1, SIGNAL(clicked(bool)), this, SLOT(Neighbor1Changed(bool)));
		connect(mNeighbor1Id, SIGNAL(editingFinished()), this, SLOT(Neighbor1IdChanged()));
		connect(mNeighbor1Side, SIGNAL(currentIndexChanged(const QString &)), this, SLOT(Neighbor1SideChanged(const QString &)));
		connect(mNeighbor1Direction, SIGNAL(currentIndexChanged(const QString &)), this, SLOT(Neighbor1DirectionChanged(const QString &)));

		connect(mNeighbor2, SIGNAL(clicked(bool)), this, SLOT(Neighbor2Changed(bool)));
		connect(mNeighbor2Id, SIGNAL(editingFinished()), this, SLOT(Neighbor2IdChanged()));
		connect(mNeighbor2Side, SIGNAL(currentIndexChanged(const QString &)), this, SLOT(Neighbor2SideChanged(const QString &)));
		connect(mNeighbor2Direction, SIGNAL(currentIndexChanged(const QString &)), this, SLOT(Neighbor2DirectionChanged(const QString &)));
	}
}

/**
 * Methods used to select roads from a list
 */
void SettingsRoad::BrowseForPredecessor()
{
	GetRoadDialog lGetRoadDialog(mOpenDrive);
	string lId = lGetRoadDialog.ReturnRoadId();
	if(lId!="") mPredecessorId->setText(lId.c_str());
}
void SettingsRoad::BrowseForSuccessor()
{
	GetRoadDialog lGetRoadDialog(mOpenDrive);
	string lId = lGetRoadDialog.ReturnRoadId();
	if(lId!="") mSuccessorId->setText(lId.c_str());
}
void SettingsRoad::BrowseForNeighbor1()
{
	GetRoadDialog lGetRoadDialog(mOpenDrive);
	string lId = lGetRoadDialog.ReturnRoadId();
	if(lId!="") mNeighbor1Id->setText(lId.c_str());
}
void SettingsRoad::BrowseForNeighbor2()
{
	GetRoadDialog lGetRoadDialog(mOpenDrive);
	string lId = lGetRoadDialog.ReturnRoadId();
	if(lId!="") mNeighbor2Id->setText(lId.c_str());
}

/**
 * Methods called when properties change
 */
void SettingsRoad::NameChanged()
{
	// Sets the new value 
	mRoad->SetRoadName(mName->text().toStdString());
}
void SettingsRoad::LengthChanged()
{
	//mRoad->SetRoadLength(mLength->text().toDouble());
}
void SettingsRoad::IdChanged()
{
	mRoad->SetRoadId(mId->text().toStdString());
}
void SettingsRoad::JunctionChanged()
{
	mRoad->SetRoadJunction(mJunction->text().toStdString());
}

void SettingsRoad::PredecessorChanged(bool on)
{
	if(on)
	{
		if(mRoad->GetPredecessor()==NULL)
		{
			mRoad->SetPredecessor(mPredecessorType->currentText().toStdString(), mPredecessorId->text().toStdString(), mPredecessorContactPoint->currentText().toStdString());
		}
	}
	else
	{
		if(mRoad->GetPredecessor()!=NULL)
		{
			mRoad->RemovePredecessor();
		}
	}
}
void SettingsRoad::PredecessorIdChanged()
{
	if(mRoad->GetPredecessor()!=NULL)
	mRoad->GetPredecessor()->SetElementId(mPredecessorId->text().toStdString());
}
void SettingsRoad::PredecessorTypeChanged(const QString & text)
{
	if(mRoad->GetPredecessor()!=NULL)
	mRoad->GetPredecessor()->SetElementType(text.toStdString());
}
void SettingsRoad::PredecessorContactPointChanged(const QString & text)
{
	if(mRoad->GetPredecessor()!=NULL)
	mRoad->GetPredecessor()->SetContactPoint(text.toStdString());
}

void SettingsRoad::SuccessorChanged(bool on)
{
	if(on)
	{
		if(mRoad->GetSuccessor()==NULL)
		{
			mRoad->SetSuccessor(mSuccessorType->currentText().toStdString(), mSuccessorId->text().toStdString(), mSuccessorContactPoint->currentText().toStdString());
		}
	}
	else
	{
		if(mRoad->GetSuccessor()!=NULL)
		{
			mRoad->RemoveSuccessor();
		}
	}
}
void SettingsRoad::SuccessorIdChanged()
{
	if(mRoad->GetSuccessor()!=NULL)
	mRoad->GetSuccessor()->SetElementId(mSuccessorId->text().toStdString());
}
void SettingsRoad::SuccessorTypeChanged(const QString & text)
{
	if(mRoad->GetSuccessor()!=NULL)
	mRoad->GetSuccessor()->SetElementType(text.toStdString());
}
void SettingsRoad::SuccessorContactPointChanged(const QString & text)
{
	if(mRoad->GetSuccessor()!=NULL)
	mRoad->GetSuccessor()->SetContactPoint(text.toStdString());
}

void SettingsRoad::Neighbor1Changed(bool on)
{
	if(on)
	{
		if(mRoad->GetNeighbor1()==NULL)
		{
			mRoad->SetNeighbor1(mNeighbor1Side->currentText().toStdString(), mNeighbor1Id->text().toStdString(), mNeighbor1Direction->currentText().toStdString());
		}
	}
	else
	{
		mRoad->RemoveNeighbor1();
	}
}
void SettingsRoad::Neighbor1IdChanged()
{
	if(mRoad->GetNeighbor1()!=NULL)
	mRoad->GetNeighbor1()->SetElementId(mNeighbor1Id->text().toStdString());
}
void SettingsRoad::Neighbor1SideChanged(const QString & text)
{
	if(mRoad->GetNeighbor1()!=NULL)
	mRoad->GetNeighbor1()->SetSide(text.toStdString());
}
void SettingsRoad::Neighbor1DirectionChanged(const QString & text)
{
	if(mRoad->GetNeighbor1()!=NULL)
	mRoad->GetNeighbor1()->SetDirection(text.toStdString());
}

void SettingsRoad::Neighbor2Changed(bool on)
{
	if(on)
	{
		if(mRoad->GetNeighbor2()==NULL)
		{
			mRoad->SetNeighbor2(mNeighbor2Side->currentText().toStdString(), mNeighbor2Id->text().toStdString(), mNeighbor2Direction->currentText().toStdString());
		}
	}
	else
	{
		mRoad->RemoveNeighbor2();
	}
}
void SettingsRoad::Neighbor2IdChanged()
{
	if(mRoad->GetNeighbor2()!=NULL)
	mRoad->GetNeighbor2()->SetElementId(mNeighbor2Id->text().toStdString());
}
void SettingsRoad::Neighbor2SideChanged(const QString & text)
{
	if(mRoad->GetNeighbor2()!=NULL)
	mRoad->GetNeighbor2()->SetSide(text.toStdString());
}
void SettingsRoad::Neighbor2DirectionChanged(const QString & text)
{
	if(mRoad->GetNeighbor2()!=NULL)
	mRoad->GetNeighbor2()->SetDirection(text.toStdString());
}