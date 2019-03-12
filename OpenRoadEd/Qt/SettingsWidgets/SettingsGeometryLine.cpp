#include "SettingsGeometryLine.h"
#include "moc_SettingsGeometryLine.cpp"

/**
 * Initializes the properties panel and the UI elements
 */
SettingsGeometryLine::SettingsGeometryLine(QWidget *parent )
{
	// Resets the record
	mLine=NULL;

	// Main vertical layout
	QVBoxLayout *mainLayout = new QVBoxLayout;

	//-------------------------------------------------
	// Group for settings
	QGroupBox *settingsGroup = new QGroupBox;
	settingsGroup->setSizePolicy(QSizePolicy::Preferred,QSizePolicy::Maximum);
	settingsGroup->setTitle(tr("Line geometry settings"));

	mS = new QLineEdit;
	mS->setDisabled(true);
	mX = new QDoubleSpinBox;
	mX->setKeyboardTracking(false);
	mX->setDecimals(9);
	mX->setRange(-1000000,1000000);
	mY = new QDoubleSpinBox;
	mY->setKeyboardTracking(false);
	mY->setDecimals(9);
	mY->setRange(-1000000,1000000);
	mHeading = new QDoubleSpinBox;
	mHeading->setKeyboardTracking(false);
	mHeading->setDecimals(9);
	mHeading->setSingleStep(0.001);
	mLineLength = new QDoubleSpinBox;
	mLineLength->setKeyboardTracking(false);
	mLineLength->setDecimals(9);
	mLineLength->setRange(-1000000,1000000);
	
	// Form Layout inside group
	QFormLayout *settingsFormLayout = new QFormLayout;
	settingsFormLayout->addRow(tr("S:"),mS);
	settingsFormLayout->addRow(tr("X position:"),mX);
	settingsFormLayout->addRow(tr("Y position:"),mY);
	settingsFormLayout->addRow(tr("Heading:"),mHeading);
	settingsFormLayout->addRow(tr("Line length:"),mLineLength);	

	settingsGroup->setLayout(settingsFormLayout);
	//-------------------------------------------------
	// Group for help
	QGroupBox *helpGroup = new QGroupBox;
	helpGroup->setTitle(tr("Help"));

	QTextEdit *helpText = new QTextEdit;
	helpText->setSizePolicy(QSizePolicy::Preferred,QSizePolicy::Expanding);
	helpText->setReadOnly(true);
	helpText->setHtml("This record describes a straight line as part of the road’s chord line."
						"<p><b>S</b> - start position (s-offset) [meters]</p>"
						"<p><b>X</b> - start position X [meters]</p>"
						"<p><b>Y</b> - start position Y [meters]</p>"
						"<p><b>Heading</b> - start orientation [radians]</p>"
						"<p><b>Line length</b> - length of the chord line for this record [meters]</p>");
	
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
 * @param block Geometry block record whose properties are to be loaded
 * @param first Set to true if it is the first record for this road
 */
void SettingsGeometryLine::LoadData(GeometryBlock *block)
{
	if(block!=NULL)
	{
		// Disconnects the "value changed" signals while the values are loaded
		disconnect(mS, SIGNAL(textChanged(const QString &)), this, SLOT(SChanged()));
		disconnect(mX, SIGNAL(valueChanged(double)), this, SLOT(XChanged(double)));
		disconnect(mY, SIGNAL(valueChanged(double)), this, SLOT(YChanged(double)));
		disconnect(mHeading, SIGNAL(valueChanged(double)), this, SLOT(HeadingChanged(double)));
		disconnect(mLineLength, SIGNAL(valueChanged(double)), this, SLOT(LineLengthChanged(double)));

		// Sets the record properties to the input widgets
		mLine=block;

		GeometryLine *lGeometryLine = static_cast<GeometryLine*>(mLine->GetGeometryAt(0));
		if(lGeometryLine!=NULL)
		{
			mS->setText(QString("%1").arg(lGeometryLine->GetS()));
			mX->setValue(lGeometryLine->GetX());
			mY->setValue(lGeometryLine->GetY());
			mHeading->setValue(lGeometryLine->GetHdg());
			mLineLength->setValue(lGeometryLine->GetLength());
		}

		// Connects the "value changed" signals back
		connect(mS, SIGNAL(textChanged(const QString &)), this, SLOT(SChanged()));
		connect(mX, SIGNAL(valueChanged(double)), this, SLOT(XChanged(double)));
		connect(mY, SIGNAL(valueChanged(double)), this, SLOT(YChanged(double)));
		connect(mHeading, SIGNAL(valueChanged(double)), this, SLOT(HeadingChanged(double)));
		connect(mLineLength, SIGNAL(valueChanged(double)), this, SLOT(LineLengthChanged(double)));
	}
}

/**
 * Makes this record the first for the road, thus enabling controls that only
 * the first record has, such as the X and Y coordinates, which are otherwise
 * computed automatically and are disabled
 */
void SettingsGeometryLine::SetFirst(bool first)
{
	if(first)
	{
		mX->setEnabled(true);
		mY->setEnabled(true);
		mHeading->setEnabled(true);
	}
	else
	{
		mX->setEnabled(false);
		mY->setEnabled(false);
		mHeading->setEnabled(false);
	}
}

/**
 * Methods called when properties change
 */
void SettingsGeometryLine::SChanged()
{
	// Shouldn't be called
	GeometryLine *lGeometryLine =  static_cast<GeometryLine*>(mLine->GetGeometryAt(0));
	if(lGeometryLine!=NULL)
	{
		lGeometryLine->SetS(mS->text().toDouble());
	}
}
void SettingsGeometryLine::XChanged(double value)
{
	// Gets the first geometry record from the block
	GeometryLine *lGeometryLine =  static_cast<GeometryLine*>(mLine->GetGeometryAt(0));
	if(lGeometryLine!=NULL)
	{
		// Set the new value to the record's property
		lGeometryLine->SetX(value);
		// Emit the road changed signal so the road gets redrawn
		emit RoadGeometryChanged(true);
	}
}
void SettingsGeometryLine::YChanged(double value)
{
	// See the first method in this group for details

	GeometryLine *lGeometryLine =  static_cast<GeometryLine*>(mLine->GetGeometryAt(0));
	if(lGeometryLine!=NULL)
	{
		lGeometryLine->SetY(value);
		emit RoadGeometryChanged(true);
	}
}
void SettingsGeometryLine::HeadingChanged(double value)
{
	// See the first method in this group for details

	GeometryLine *lGeometryLine =  static_cast<GeometryLine*>(mLine->GetGeometryAt(0));
	if(lGeometryLine!=NULL)
	{
		lGeometryLine->SetHdg(value);
		emit RoadGeometryChanged(true);
	}
}
void SettingsGeometryLine::LineLengthChanged(double value)
{
	// See the first method in this group for details

	GeometryLine *lGeometryLine =  static_cast<GeometryLine*>(mLine->GetGeometryAt(0));
	if(lGeometryLine!=NULL)
	{
		lGeometryLine->SetLength(value);
		emit RoadGeometryChanged(true);
	}
}
