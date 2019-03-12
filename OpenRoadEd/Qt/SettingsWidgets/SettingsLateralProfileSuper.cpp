#include "SettingsLateralProfileSuper.h"
#include "moc_SettingsLateralProfileSuper.cpp"

/**
 * Initializes the properties panel and the UI elements
 */
SettingsLateralProfileSuper::SettingsLateralProfileSuper(QWidget *parent)
{
	// Resets the record
	mSuperElevation = NULL;

	// Main vertical layout
	QVBoxLayout *mainLayout = new QVBoxLayout;

	//-------------------------------------------------
	// Group for settings
	QGroupBox *settingsGroup = new QGroupBox;
	settingsGroup->setSizePolicy(QSizePolicy::Preferred,QSizePolicy::Maximum);
	settingsGroup->setTitle(tr("Lateral superelevation settings"));

	mS=new QDoubleSpinBox;
	mS->setKeyboardTracking(false);
	mS->setDecimals(9);
	mS->setRange(0, 1000000);
	mA=new QDoubleSpinBox;
	mA->setKeyboardTracking(false);
	mA->setDecimals(9);
	mA->setSingleStep(0.001);
	mA->setRange(-1000, 1000);
	mB=new QDoubleSpinBox;
	mB->setKeyboardTracking(false);
	mB->setDecimals(9);
	mB->setSingleStep(0.001);
	mB->setRange(-1000, 1000);
	mC=new QDoubleSpinBox;
	mC->setKeyboardTracking(false);
	mC->setDecimals(9);
	mC->setSingleStep(0.001);
	mC->setRange(-1000, 1000);
	mD=new QDoubleSpinBox;
	mD->setKeyboardTracking(false);
	mD->setDecimals(9);
	mD->setSingleStep(0.001);
	mD->setRange(-1000, 1000);
	
	// Form Layout inside group
	QFormLayout *settingsFormLayout = new QFormLayout;
	settingsFormLayout->addRow(tr("S:"),mS);
	settingsFormLayout->addRow(tr("A:"),mA);
	settingsFormLayout->addRow(tr("B:"),mB);
	settingsFormLayout->addRow(tr("C:"),mC);
	settingsFormLayout->addRow(tr("D:"),mD);	

	settingsGroup->setLayout(settingsFormLayout);
	//-------------------------------------------------
	// Group for help
	QGroupBox *helpGroup = new QGroupBox;
	helpGroup->setTitle(tr("Help"));

	QTextEdit *helpText = new QTextEdit;
	helpText->setSizePolicy(QSizePolicy::Preferred,QSizePolicy::Expanding);
	helpText->setReadOnly(true);
	helpText->setHtml("This record defines the road's banking along the chord line. The parameters of this entry are valid until the next entry starts or the road’s chord line ends."
						"<p><b>S</b> - start position (s-offset) [meters]</p>"
						"<p><b>A</b> - superelevation [radians]</p>"
						"<p><b>B</b> - slope</p>"
						"<p><b>C</b> - vertical curvature</p>"
						"<p><b>D</b> - curvature change</p>");
	
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
 * @param superElevation Superelevation record whose properties are to be loaded
 * @param minS Minimum "S" property for this record
 * @param maxS Maximum "S" property for this record
 */
void SettingsLateralProfileSuper::LoadData(SuperElevation *superElevation, double minS, double maxS)
{
	if(superElevation!=NULL)
	{
		// Disconnects the "value changed" signals while the values are loaded
		disconnect(mS, SIGNAL(valueChanged(double)), this, SLOT(SChanged(double)));
		disconnect(mA, SIGNAL(valueChanged(double)), this, SLOT(AChanged(double)));
		disconnect(mB, SIGNAL(valueChanged(double)), this, SLOT(BChanged(double)));
		disconnect(mC, SIGNAL(valueChanged(double)), this, SLOT(CChanged(double)));
		disconnect(mD, SIGNAL(valueChanged(double)), this, SLOT(DChanged(double)));

		// Sets the record properties to the input widgets
		mSuperElevation=superElevation;

		mS->setRange(minS,maxS);
		mS->setValue(mSuperElevation->GetS());
		mA->setValue(mSuperElevation->GetA());
		mB->setValue(mSuperElevation->GetB());
		mC->setValue(mSuperElevation->GetC());
		mD->setValue(mSuperElevation->GetD());

		// Connects the "value changed" signals back
		connect(mS, SIGNAL(valueChanged(double)), this, SLOT(SChanged(double)));
		connect(mA, SIGNAL(valueChanged(double)), this, SLOT(AChanged(double)));
		connect(mB, SIGNAL(valueChanged(double)), this, SLOT(BChanged(double)));
		connect(mC, SIGNAL(valueChanged(double)), this, SLOT(CChanged(double)));
		connect(mD, SIGNAL(valueChanged(double)), this, SLOT(DChanged(double)));
	}
}

/**
 * Methods called when properties change
 */
void SettingsLateralProfileSuper::SChanged(double value)
{
	// Sets the new value 
	mSuperElevation->SetS(value);
	// Emits "road changed" signal so the road gets redrawn
	emit RoadSuperElevationChanged(false);
}
void SettingsLateralProfileSuper::AChanged(double value)
{
	// See the first few methods in this group for details

	mSuperElevation->SetA(value);
	emit RoadSuperElevationChanged(false);
}
void SettingsLateralProfileSuper::BChanged(double value)
{
	// See the first few methods in this group for details

	mSuperElevation->SetB(value);
	emit RoadSuperElevationChanged(false);
}
void SettingsLateralProfileSuper::CChanged(double value)
{
	// See the first few methods in this group for details

	mSuperElevation->SetC(value);
	emit RoadSuperElevationChanged(false);
}
void SettingsLateralProfileSuper::DChanged(double value)
{
	// See the first few methods in this group for details

	mSuperElevation->SetD(value);
	emit RoadSuperElevationChanged(false);
}