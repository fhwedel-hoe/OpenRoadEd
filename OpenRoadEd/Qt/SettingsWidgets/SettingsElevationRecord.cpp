#include "SettingsElevationRecord.h"
#include "moc_SettingsElevationRecord.cpp"

/**
 * Initializes the properties panel and the UI elements
 */
SettingsElevationRecord::SettingsElevationRecord(QWidget *parent)
{
	// Resets the elevation record
	mElevation=NULL;

	// Main vertical layout
	QVBoxLayout *mainLayout = new QVBoxLayout;

	//-------------------------------------------------
	// Group for settings
	QGroupBox *settingsGroup = new QGroupBox;
	settingsGroup->setSizePolicy(QSizePolicy::Preferred,QSizePolicy::Maximum);
	settingsGroup->setTitle(tr("Elevation record settings"));

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
	helpText->setHtml("This record defines an elevation entry at a given chord line position. The parameters of this entry are valid until the next entry starts or the road’s chord line ends."
						"<p><b>S</b> - start position (s-offset) [meters]</p>"
						"<p><b>A</b> - elevation [meters]</p>"
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
 * @param elevation Elevation record whose properties are to be loaded
 * @param minS Minimum "S" property for this record
 * @param maxS Maximum "S" property for this record
 */
void SettingsElevationRecord::LoadData(Elevation *elevation, double minS, double maxS)
{
	if(elevation!=NULL)
	{
		// Disconnects the "value changed" signals while the values are loaded
		disconnect(mS, SIGNAL(valueChanged(double)), this, SLOT(SChanged(double)));
		disconnect(mA, SIGNAL(valueChanged(double)), this, SLOT(AChanged(double)));
		disconnect(mB, SIGNAL(valueChanged(double)), this, SLOT(BChanged(double)));
		disconnect(mC, SIGNAL(valueChanged(double)), this, SLOT(CChanged(double)));
		disconnect(mD, SIGNAL(valueChanged(double)), this, SLOT(DChanged(double)));


		// Sets the record properties to the input widgets
		mElevation=elevation;

		mS->setRange(minS, maxS);
		mS->setValue(mElevation->GetS());
		mA->setValue(mElevation->GetA());
		mB->setValue(mElevation->GetB());
		mC->setValue(mElevation->GetC());
		mD->setValue(mElevation->GetD());


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
void SettingsElevationRecord::SChanged(double value)
{
	// Set the new value to the record's property in OpenDrive structure
	mElevation->SetS(value);
	// Emit the road changed signal so the road gets redrawn
	emit RoadElevationChanged(false);
}
void SettingsElevationRecord::AChanged(double value)
{
	// See the first method in this group for details

	mElevation->SetA(value);
	emit RoadElevationChanged(false);
}
void SettingsElevationRecord::BChanged(double value)
{
	// See the first method in this group for details

	mElevation->SetB(value);
	emit RoadElevationChanged(false);
}
void SettingsElevationRecord::CChanged(double value)
{
	// See the first method in this group for details

	mElevation->SetC(value);
	emit RoadElevationChanged(false);
}
void SettingsElevationRecord::DChanged(double value)
{
	// See the first method in this group for details

	mElevation->SetD(value);
	emit RoadElevationChanged(false);
}