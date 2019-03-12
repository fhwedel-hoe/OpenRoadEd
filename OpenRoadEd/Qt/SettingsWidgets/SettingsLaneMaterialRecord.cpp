#include "SettingsLaneMaterialRecord.h"
#include "moc_SettingsLaneMaterialRecord.cpp"

/**
 * Initializes the properties panel and the UI elements
 */
SettingsLaneMaterialRecord::SettingsLaneMaterialRecord(QWidget *parent)
{
	// Resets the record
	mLaneMaterial=NULL;

	// Main vertical layout
	QVBoxLayout *mainLayout = new QVBoxLayout;

	//-------------------------------------------------
	// Group for settings
	QGroupBox *settingsGroup = new QGroupBox;
	settingsGroup->setSizePolicy(QSizePolicy::Preferred,QSizePolicy::Maximum);
	settingsGroup->setTitle(tr("Lane material settings"));

	mS=new QDoubleSpinBox;
	mS->setKeyboardTracking(false);
	mS->setDecimals(9);
	mS->setRange(0,1000000);
	mSurface=new QLineEdit;
	mFriction=new QDoubleSpinBox;
	mFriction->setKeyboardTracking(false);
	mFriction->setDecimals(9);
	mFriction->setRange(-1000,1000);
	mRoughness=new QDoubleSpinBox;
	mRoughness->setKeyboardTracking(false);
	mRoughness->setDecimals(9);
	mRoughness->setRange(-1000,1000);
	
	// Form Layout inside group
	QFormLayout *settingsFormLayout = new QFormLayout;
	settingsFormLayout->addRow(tr("S:"),mS);
	settingsFormLayout->addRow(tr("Surface:"),mSurface);
	settingsFormLayout->addRow(tr("Friction:"),mFriction);
	settingsFormLayout->addRow(tr("Roughness:"),mRoughness);

	settingsGroup->setLayout(settingsFormLayout);
	//-------------------------------------------------
	// Group for help
	QGroupBox *helpGroup = new QGroupBox;
	helpGroup->setTitle(tr("Help"));

	QTextEdit *helpText = new QTextEdit;
	helpText->setSizePolicy(QSizePolicy::Preferred,QSizePolicy::Expanding);
	helpText->setReadOnly(true);
	helpText->setHtml("This record defines the lane's surface material. The parameters of this entry are valid until the next entry starts or the road’s chord line ends."
						"<p><b>S</b> - start position (s-offset from the current lane section) [meters]</p>"
						"<p><b>Surface</b> - surface material code (string)</p>"
						"<p><b>Friction</b> - friction value</p>"
						"<p><b>Roughness</b> - roughness</p>");
	
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
 * @param laneMaterial Lane material record whose properties are to be loaded
 * @param minS Minimum "S" property for this record
 * @param maxS Maximum "S" property for this record
 */
void SettingsLaneMaterialRecord::LoadData(LaneMaterial *laneMaterial, double minS, double maxS)
{
	if(laneMaterial!=NULL)
	{
		// Disconnects the "value changed" signals while the values are loaded
		disconnect(mS, SIGNAL(valueChanged(double)), this, SLOT(SChanged(double)));
		disconnect(mSurface, SIGNAL(editingFinished()), this, SLOT(SurfaceChanged()));
		disconnect(mFriction, SIGNAL(valueChanged(double)), this, SLOT(FrictionChanged(double)));
		disconnect(mRoughness, SIGNAL(valueChanged(double)), this, SLOT(RoughnessChanged(double)));

		// Sets the record properties to the input widgets
		mLaneMaterial=laneMaterial;

		mS->setRange(minS,maxS);
		mS->setValue(mLaneMaterial->GetS());
		mSurface->setText(mLaneMaterial->GetSurface().c_str());
		mFriction->setValue(mLaneMaterial->GetFriction());
		mRoughness->setValue(mLaneMaterial->GetRoughness());

		// Connects the "value changed" signals back
		connect(mS, SIGNAL(valueChanged(double)), this, SLOT(SChanged(double)));
		connect(mSurface, SIGNAL(editingFinished()), this, SLOT(SurfaceChanged()));
		connect(mFriction, SIGNAL(valueChanged(double)), this, SLOT(FrictionChanged(double)));
		connect(mRoughness, SIGNAL(valueChanged(double)), this, SLOT(RoughnessChanged(double)));
	}
}

/**
 * Methods called when properties change
 */
void SettingsLaneMaterialRecord::SChanged(double value)
{
	// Sets the new value 
	mLaneMaterial->SetS(value);
	// Emits "road changed" signal so the road gets redrawn
	emit RoadLaneMaterialChanged(false);
}

void SettingsLaneMaterialRecord::SurfaceChanged()
{
	mLaneMaterial->SetSurface(mSurface->text().toStdString());
}

void SettingsLaneMaterialRecord::FrictionChanged(double value)
{
	mLaneMaterial->SetFriction(value);
}

void SettingsLaneMaterialRecord::RoughnessChanged(double value)
{
	mLaneMaterial->SetRoughness(value);
}