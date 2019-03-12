#include "SettingsLaneRoadMark.h"
#include "moc_SettingsLaneRoadMark.cpp"

/**
 * Initializes the properties panel and the UI elements
 */
SettingsLaneRoadMark::SettingsLaneRoadMark(QWidget *parent)
{
	// Resets the record
	mRoadMark=NULL;

	// Main vertical layout
	QVBoxLayout *mainLayout = new QVBoxLayout;

	//-------------------------------------------------
	// Group for settings
	QGroupBox *settingsGroup = new QGroupBox;
	settingsGroup->setSizePolicy(QSizePolicy::Preferred,QSizePolicy::Maximum);
	settingsGroup->setTitle(tr("Lane road mark settings"));

	mS=new QDoubleSpinBox;
	mS->setKeyboardTracking(false);
	mS->setDecimals(9);
	mS->setRange(0,1000000);
	mType=new QComboBox;
	mType->insertItem(0,tr("none"));
	mType->insertItem(1,tr("solid"));
	mType->insertItem(2,tr("broken"));
	mType->insertItem(3,tr("solid solid"));
	mType->insertItem(4,tr("solid broken"));
	mType->insertItem(5,tr("broken solid"));
	mWeight=new QComboBox;
	mWeight->insertItem(0,tr("standard"));
	mWeight->insertItem(1,tr("bold"));
	mColor=new QComboBox;
	mColor->insertItem(0,tr("standard"));
	mColor->insertItem(1,tr("yellow"));
	mWidth=new QDoubleSpinBox;
	mWidth->setKeyboardTracking(false);
	mWidth->setDecimals(9);
	mWidth->setRange(0,1000);
	mLaneChange=new QComboBox;
	mLaneChange->insertItem(0,tr("increase"));
	mLaneChange->insertItem(1,tr("decrease"));
	mLaneChange->insertItem(2,tr("both"));
	mLaneChange->insertItem(3,tr("none"));

	
	// Form Layout inside group
	QFormLayout *settingsFormLayout = new QFormLayout;
	settingsFormLayout->addRow(tr("S:"),mS);
	settingsFormLayout->addRow(tr("Type:"),mType);
	settingsFormLayout->addRow(tr("Weight:"),mWeight);
	settingsFormLayout->addRow(tr("Color:"),mColor);
	settingsFormLayout->addRow(tr("Width:"),mWidth);	
	settingsFormLayout->addRow(tr("LaneChange:"),mLaneChange);	

	settingsGroup->setLayout(settingsFormLayout);
	//-------------------------------------------------
	// Group for help
	QGroupBox *helpGroup = new QGroupBox;
	helpGroup->setTitle(tr("Help"));

	QTextEdit *helpText = new QTextEdit;
	helpText->setSizePolicy(QSizePolicy::Preferred,QSizePolicy::Expanding);
	helpText->setReadOnly(true);
	helpText->setHtml("This record defines the lane's road mark. The parameters of this entry are valid until the next entry starts or the road’s chord line ends."
						"<p><b>S</b> - start position (s-offset from the current lane section) [meters]</p>"
						"<p><b>Type</b> - type of the road mark</p>"
						"<p><b>Weight</b> - weight of the road mark</p>"
						"<p><b>Color</b> - color of the road mark</p>"
						"<p><b>Width</b> - width of the road mark [meters]</p>"
						"<p><b>Lane change</b> - allows a lane change in the indicated direction</p>");
	
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
 * @param laneRoadMark Lane road mark record whose properties are to be loaded
 * @param minS Minimum "S" property for this record
 * @param maxS Maximum "S" property for this record
 */
void SettingsLaneRoadMark::LoadData(LaneRoadMark *laneRoadMark, double minS, double maxS)
{
	if(laneRoadMark!=NULL)
	{
		// Disconnects the "value changed" signals while the values are loaded
		disconnect(mS, SIGNAL(valueChanged(double)), this, SLOT(SChanged(double)));
		disconnect(mType, SIGNAL(currentIndexChanged(const QString &)), this, SLOT(TypeChanged(const QString &)));
		disconnect(mWeight, SIGNAL(currentIndexChanged(const QString &)), this, SLOT(WeightChanged(const QString &)));
		disconnect(mColor, SIGNAL(currentIndexChanged(const QString &)), this, SLOT(ColorChanged(const QString &)));
		disconnect(mWidth, SIGNAL(valueChanged(double)), this, SLOT(WidthChanged(double)));
		disconnect(mLaneChange, SIGNAL(currentIndexChanged(const QString &)), this, SLOT(LaneChangeChanged(const QString &)));

		// Sets the record properties to the input widgets
		mRoadMark=laneRoadMark;

		mS->setRange(minS,maxS);
		mS->setValue(mRoadMark->GetS());
		mWidth->setValue(mRoadMark->GetWidth());
		
		if(mRoadMark->GetType().compare("none")==0) mType->setCurrentIndex(0);
		else if(mRoadMark->GetType().compare("solid")==0) mType->setCurrentIndex(1);
		else if(mRoadMark->GetType().compare("broken")==0) mType->setCurrentIndex(2);
		else if(mRoadMark->GetType().compare("solid solid")==0) mType->setCurrentIndex(3);
		else if(mRoadMark->GetType().compare("solid broken")==0) mType->setCurrentIndex(4);
		else if(mRoadMark->GetType().compare("broken solid")==0) mType->setCurrentIndex(5);

		if(mRoadMark->GetWeight().compare("standard")==0) mWeight->setCurrentIndex(0);
		else if(mRoadMark->GetWeight().compare("bold")==0) mWeight->setCurrentIndex(1);

		if(mRoadMark->GetColor().compare("standard")==0) mColor->setCurrentIndex(0);
		else if(mRoadMark->GetColor().compare("yellow")==0) mColor->setCurrentIndex(1);
		
		if(mRoadMark->GetLaneChange().compare("increase")==0) mLaneChange->setCurrentIndex(0);
		else if(mRoadMark->GetLaneChange().compare("decrease")==0) mLaneChange->setCurrentIndex(1);
		else if(mRoadMark->GetLaneChange().compare("both")==0) mLaneChange->setCurrentIndex(2);
		else if(mRoadMark->GetLaneChange().compare("none")==0) mLaneChange->setCurrentIndex(3);

		// Connects the "value changed" signals back
		connect(mS, SIGNAL(valueChanged(double)), this, SLOT(SChanged(double)));
		connect(mType, SIGNAL(currentIndexChanged(const QString &)), this, SLOT(TypeChanged(const QString &)));
		connect(mWeight, SIGNAL(currentIndexChanged(const QString &)), this, SLOT(WeightChanged(const QString &)));
		connect(mColor, SIGNAL(currentIndexChanged(const QString &)), this, SLOT(ColorChanged(const QString &)));
		connect(mWidth, SIGNAL(valueChanged(double)), this, SLOT(WidthChanged(double)));
		connect(mLaneChange, SIGNAL(currentIndexChanged(const QString &)), this, SLOT(LaneChangeChanged(const QString &)));

	}
}

/**
 * Methods called when properties change
 */
void SettingsLaneRoadMark::SChanged(double value)
{
	// Sets the new value 
	mRoadMark->SetS(value);
	// Emits "road changed" signal so the road gets redrawn
	emit RoadLaneRoadMarkChanged(false);
}
void SettingsLaneRoadMark::TypeChanged(const QString & text)
{
	// See the first few methods in this group for details

	mRoadMark->SetType(text.toStdString());
	emit RoadLaneRoadMarkChanged(false);
}
void SettingsLaneRoadMark::WeightChanged(const QString & text)
{
	// See the first few methods in this group for details

	mRoadMark->SetWeight(text.toStdString());
	emit RoadLaneRoadMarkChanged(false);
}
void SettingsLaneRoadMark::ColorChanged(const QString & text)
{
	// See the first few methods in this group for details

	mRoadMark->SetColor(text.toStdString());
	emit RoadLaneRoadMarkChanged(false);
}
void SettingsLaneRoadMark::WidthChanged(double value)
{
	// See the first few methods in this group for details

	mRoadMark->SetWidth(value);
	emit RoadLaneRoadMarkChanged(false);
}
void SettingsLaneRoadMark::LaneChangeChanged(const QString & text)
{
	// See the first few methods in this group for details

	mRoadMark->SetLaneChange(text.toStdString());
	emit RoadLaneRoadMarkChanged(false);
}