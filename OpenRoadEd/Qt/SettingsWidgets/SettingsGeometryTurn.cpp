#include "SettingsGeometryTurn.h"
#include "moc_SettingsGeometryTurn.cpp"

/**
 * Initializes the properties panel and the UI elements
 */
SettingsGeometryTurn::SettingsGeometryTurn(QWidget *parent )
{
	// Resets the record
	mTurn=NULL;

	// Main vertical layout
	QVBoxLayout *mainLayout = new QVBoxLayout;

	//-------------------------------------------------
	// Group for settings
	QGroupBox *settingsGroup = new QGroupBox;
	settingsGroup->setSizePolicy(QSizePolicy::Preferred,QSizePolicy::Maximum);
	settingsGroup->setTitle(tr("Turn geometry settings"));

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
	mArcLength = new QDoubleSpinBox;
	mArcLength->setKeyboardTracking(false);
	mArcLength->setDecimals(9);
	mArcLength->setRange(-1000000,1000000);
	mArcCurve = new QDoubleSpinBox;
	mArcCurve->setKeyboardTracking(false);
	mArcCurve->setRange(-1000000,1000000);
	mArcCurve->setDecimals(9);
	mArcCurve->setSingleStep(0.001);
	mSpiral1Length = new QDoubleSpinBox;
	mSpiral1Length->setKeyboardTracking(false);
	mSpiral1Length->setDecimals(9);
	mSpiral1Length->setRange(-1000000,1000000);
	mSpiral2Length = new QDoubleSpinBox;
	mSpiral2Length->setKeyboardTracking(false);
	mSpiral2Length->setDecimals(9);
	mSpiral2Length->setRange(-1000000,1000000);
	
	// Form Layout inside group
	QFormLayout *settingsFormLayout = new QFormLayout;
	settingsFormLayout->addRow(tr("S:"),mS);
	settingsFormLayout->addRow(tr("X position:"),mX);
	settingsFormLayout->addRow(tr("Y position:"),mY);
	settingsFormLayout->addRow(tr("Heading:"),mHeading);
	settingsFormLayout->addRow(tr("Turn curve"),mArcCurve);
	settingsFormLayout->addRow(tr("Start length"),mSpiral1Length);
	settingsFormLayout->addRow(tr("Curve length"),mArcLength);
	settingsFormLayout->addRow(tr("End length"),mSpiral2Length);	

	settingsGroup->setLayout(settingsFormLayout);
	//-------------------------------------------------
	// Group for help
	QGroupBox *helpGroup = new QGroupBox;
	helpGroup->setTitle(tr("Help"));

	QTextEdit *helpText = new QTextEdit;
	helpText->setSizePolicy(QSizePolicy::Preferred,QSizePolicy::Expanding);
	helpText->setReadOnly(true);
	helpText->setHtml("This record describes a turn as part of the road’s chord line."
						"<p><b>S</b> - start position (s-offset) [meters]</p>"
						"<p><b>X</b> - start position X [meters]</p>"
						"<p><b>Y</b> - start position Y [meters]</p>"
						"<p><b>Heading</b> - start orientation [radians]</p>"
						"<p><b>Turn curve</b> - curvature of the turn</p>"
						"<p><b>Start length</b> - length of turn entrance</p>"
						"<p><b>Curve length</b> - length of the curvature</p>"
						"<p><b>End length</b> - length of the turn exit</p>");
	
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
void SettingsGeometryTurn::LoadData(GeometryBlock *block)
{
	if(block!=NULL)
	{
		// Disconnects the "value changed" signals while the values are loaded
		disconnect(mS, SIGNAL(textChanged(const QString &)), this, SLOT(SChanged()));
		disconnect(mX, SIGNAL(valueChanged(double)), this, SLOT(XChanged(double)));
		disconnect(mY, SIGNAL(valueChanged(double)), this, SLOT(YChanged(double)));
		disconnect(mHeading, SIGNAL(valueChanged(double)), this, SLOT(HeadingChanged(double)));
		disconnect(mArcLength, SIGNAL(valueChanged(double)), this, SLOT(ArcLengthChanged(double)));
		disconnect(mArcCurve, SIGNAL(valueChanged(double)), this, SLOT(ArcCurveChanged(double)));
		disconnect(mSpiral1Length, SIGNAL(valueChanged(double)), this, SLOT(Spiral1LengthChanged(double)));
		disconnect(mSpiral2Length, SIGNAL(valueChanged(double)), this, SLOT(Spiral2LengthChanged(double)));

		// Sets the record properties to the input widgets
		mTurn=block;

		GeometrySpiral *lGeometrySpiral1 =	static_cast<GeometrySpiral*>(mTurn->GetGeometryAt(0));
		GeometryArc *lGeometryArc =			static_cast<GeometryArc*>(mTurn->GetGeometryAt(1));
		GeometrySpiral *lGeometrySpiral2 =	static_cast<GeometrySpiral*>(mTurn->GetGeometryAt(2));

		if(lGeometrySpiral1!=NULL)
		{
			mS->setText(QString("%1").arg(lGeometrySpiral1->GetS()));
			mX->setValue(lGeometrySpiral1->GetX());
			mY->setValue(lGeometrySpiral1->GetY());
			mHeading->setValue(lGeometrySpiral1->GetHdg());
			mSpiral1Length->setValue(lGeometrySpiral1->GetLength());
		}

		if(lGeometryArc!=NULL)
		{
			mArcLength->setValue(lGeometryArc->GetLength());
			mArcCurve->setValue(lGeometryArc->GetCurvature());
		}

		if(lGeometrySpiral2!=NULL)
		{
			mSpiral2Length->setValue(lGeometrySpiral2->GetLength());
		}

		// Connects the "value changed" signals back
		connect(mS, SIGNAL(textChanged(const QString &)), this, SLOT(SChanged()));
		connect(mX, SIGNAL(valueChanged(double)), this, SLOT(XChanged(double)));
		connect(mY, SIGNAL(valueChanged(double)), this, SLOT(YChanged(double)));
		connect(mHeading, SIGNAL(valueChanged(double)), this, SLOT(HeadingChanged(double)));
		connect(mArcLength, SIGNAL(valueChanged(double)), this, SLOT(ArcLengthChanged(double)));
		connect(mArcCurve, SIGNAL(valueChanged(double)), this, SLOT(ArcCurveChanged(double)));
		connect(mSpiral1Length, SIGNAL(valueChanged(double)), this, SLOT(Spiral1LengthChanged(double)));
		connect(mSpiral2Length, SIGNAL(valueChanged(double)), this, SLOT(Spiral2LengthChanged(double)));
	}
}

/**
 * Makes this record the first for the road, thus enabling controls that only
 * the first record has, such as the X and Y coordinates, which are otherwise
 * computed automatically and are disabled
 */
void SettingsGeometryTurn::SetFirst(bool first)
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
void SettingsGeometryTurn::SChanged()
{
	// Shouldn't be called
	GeometrySpiral *lGeometrySpiral1 =  static_cast<GeometrySpiral*>(mTurn->GetGeometryAt(0));
	if(lGeometrySpiral1!=NULL)
	{
		lGeometrySpiral1->SetS(mS->text().toDouble());
	}
}
void SettingsGeometryTurn::XChanged(double value)
{
	double lS=0;
	double lX=0;
	double lY=0;
	double lHdg=0;

	// Gets the spiral, arc, spiral geometry records from the block
	GeometrySpiral *lGeometrySpiral1	=  static_cast<GeometrySpiral*>(mTurn->GetGeometryAt(0));
	GeometryArc *lGeometryArc			=  static_cast<GeometryArc*>(mTurn->GetGeometryAt(1));
	GeometrySpiral *lGeometrySpiral2	=  static_cast<GeometrySpiral*>(mTurn->GetGeometryAt(2));
	if(lGeometrySpiral1!=NULL && lGeometryArc!=NULL && lGeometrySpiral2!=NULL)
	{
		// Changes X for the first spiral
		lGeometrySpiral1->SetX(value);

		// Reads the new coords of the spiral
		lS=lGeometrySpiral1->GetS2();
		lGeometrySpiral1->GetCoords(lS,lX,lY,lHdg);

		// Updates the arc to reflect the changes to the first spiral
		lGeometryArc->SetBase(lS,lX,lY,lHdg,lGeometryArc->GetLength());

		// Reads the new coords of the arc
		lS=lGeometryArc->GetS2();
		lGeometryArc->GetCoords(lS,lX,lY,lHdg);

		// Updates the second spiral to reflect hte changes to the arc
		lGeometrySpiral2->SetBase(lS,lX,lY,lHdg,lGeometrySpiral2->GetLength());

		// Emit the road changed signal so the road gets redrawn
		emit RoadGeometryChanged(true);
	}
}
void SettingsGeometryTurn::YChanged(double value)
{
	// See the first method in this group for details

	double lS=0;
	double lX=0;
	double lY=0;
	double lHdg=0;

	GeometrySpiral *lGeometrySpiral1	=  static_cast<GeometrySpiral*>(mTurn->GetGeometryAt(0));
	GeometryArc *lGeometryArc			=  static_cast<GeometryArc*>(mTurn->GetGeometryAt(1));
	GeometrySpiral *lGeometrySpiral2	=  static_cast<GeometrySpiral*>(mTurn->GetGeometryAt(2));
	if(lGeometrySpiral1!=NULL && lGeometryArc!=NULL && lGeometrySpiral2!=NULL)
	{
		// Changes X for the first spiral
		lGeometrySpiral1->SetY(value);

		// Reads the new coords of the spiral
		lS=lGeometrySpiral1->GetS2();
		lGeometrySpiral1->GetCoords(lS,lX,lY,lHdg);

		// Updates the arc to reflect the changes to the first spiral
		lGeometryArc->SetBase(lS,lX,lY,lHdg,lGeometryArc->GetLength());

		// Reads the new coords of the arc
		lS=lGeometryArc->GetS2();
		lGeometryArc->GetCoords(lS,lX,lY,lHdg);

		// Updates the second spiral to reflect hte changes to the arc
		lGeometrySpiral2->SetBase(lS,lX,lY,lHdg, lGeometrySpiral2->GetLength());

		emit RoadGeometryChanged(true);
	}
}
void SettingsGeometryTurn::HeadingChanged(double value)
{
	// See the first method in this group for details

	double lS=0;
	double lX=0;
	double lY=0;
	double lHdg=0;

	GeometrySpiral *lGeometrySpiral1	=  static_cast<GeometrySpiral*>(mTurn->GetGeometryAt(0));
	GeometryArc *lGeometryArc			=  static_cast<GeometryArc*>(mTurn->GetGeometryAt(1));
	GeometrySpiral *lGeometrySpiral2	=  static_cast<GeometrySpiral*>(mTurn->GetGeometryAt(2));
	if(lGeometrySpiral1!=NULL && lGeometryArc!=NULL && lGeometrySpiral2!=NULL)
	{
		// Changes X for the first spiral
		lGeometrySpiral1->SetHdg(value);

		// Reads the new coords of the spiral
		lS=lGeometrySpiral1->GetS2();
		lGeometrySpiral1->GetCoords(lS,lX,lY,lHdg);

		// Updates the arc to reflect the changes to the first spiral
		lGeometryArc->SetBase(lS,lX,lY,lHdg,lGeometryArc->GetLength());

		// Reads the new coords of the arc
		lS=lGeometryArc->GetS2();
		lGeometryArc->GetCoords(lS,lX,lY,lHdg);

		// Updates the second spiral to reflect hte changes to the arc
		lGeometrySpiral2->SetBase(lS,lX,lY,lHdg,lGeometrySpiral2->GetLength());

		emit RoadGeometryChanged(true);
	}
}
void SettingsGeometryTurn::Spiral1LengthChanged(double value)
{
	// See the first method in this group for details

	double lS=0;
	double lX=0;
	double lY=0;
	double lHdg=0;

	GeometrySpiral *lGeometrySpiral1	=  static_cast<GeometrySpiral*>(mTurn->GetGeometryAt(0));
	GeometryArc *lGeometryArc			=  static_cast<GeometryArc*>(mTurn->GetGeometryAt(1));
	GeometrySpiral *lGeometrySpiral2	=  static_cast<GeometrySpiral*>(mTurn->GetGeometryAt(2));
	if(lGeometrySpiral1!=NULL && lGeometryArc!=NULL && lGeometrySpiral2!=NULL)
	{
		// Changes X for the first spiral
		lGeometrySpiral1->SetLength(value);

		// Reads the new coords of the spiral
		lS=lGeometrySpiral1->GetS2();
		lGeometrySpiral1->GetCoords(lS,lX,lY,lHdg);

		// Updates the arc to reflect the changes to the first spiral
		lGeometryArc->SetBase(lS,lX,lY,lHdg,lGeometryArc->GetLength());

		// Reads the new coords of the arc
		lS=lGeometryArc->GetS2();
		lGeometryArc->GetCoords(lS,lX,lY,lHdg);

		// Updates the second spiral to reflect hte changes to the arc
		lGeometrySpiral2->SetBase(lS,lX,lY,lHdg,lGeometrySpiral2->GetLength());

		emit RoadGeometryChanged(true);
	}
}

void SettingsGeometryTurn::ArcLengthChanged(double value)
{
	// See the first method in this group for details

	double lS=0;
	double lX=0;
	double lY=0;
	double lHdg=0;

	GeometryArc *lGeometryArc			=  static_cast<GeometryArc*>(mTurn->GetGeometryAt(1));
	GeometrySpiral *lGeometrySpiral2	=  static_cast<GeometrySpiral*>(mTurn->GetGeometryAt(2));
	if(lGeometryArc!=NULL && lGeometrySpiral2!=NULL)
	{
		// Sets length for the arc
		lGeometryArc->SetLength(value);

		// Reads the new coords of the arc
		lS=lGeometryArc->GetS2();
		lGeometryArc->GetCoords(lS,lX,lY,lHdg);

		// Updates the second spiral to reflect hte changes to the arc
		lGeometrySpiral2->SetBase(lS,lX,lY,lHdg, lGeometrySpiral2->GetLength());

		emit RoadGeometryChanged(true);
	}
}

void SettingsGeometryTurn::ArcCurveChanged(double value)
{
	// See the first method in this group for details

	double lS=0;
	double lX=0;
	double lY=0;
	double lHdg=0;

	GeometrySpiral *lGeometrySpiral1	=  static_cast<GeometrySpiral*>(mTurn->GetGeometryAt(0));
	GeometryArc *lGeometryArc			=  static_cast<GeometryArc*>(mTurn->GetGeometryAt(1));
	GeometrySpiral *lGeometrySpiral2	=  static_cast<GeometrySpiral*>(mTurn->GetGeometryAt(2));
	if(lGeometrySpiral1!=NULL && lGeometryArc!=NULL && lGeometrySpiral2!=NULL)
	{
		// Changes curvature for the first spiral
		lGeometrySpiral1->SetCurvatureEnd(value);

		// Reads the new coords of the spiral
		lS=lGeometrySpiral1->GetS2();
		lGeometrySpiral1->GetCoords(lS,lX,lY,lHdg);

		// Updates the arc to reflect the changes to the first spiral
		lGeometryArc->SetAll(lS,lX,lY,lHdg,lGeometryArc->GetLength(),value);

		// Reads the new coords of the arc
		lS=lGeometryArc->GetS2();
		lGeometryArc->GetCoords(lS,lX,lY,lHdg);

		// Updates the second spiral to reflect hte changes to the arc
		lGeometrySpiral2->SetAll(lS,lX,lY,lHdg,lGeometrySpiral2->GetLength(),value,0);

		emit RoadGeometryChanged(true);
	}
}

void SettingsGeometryTurn::Spiral2LengthChanged(double value)
{
	// See the first method in this group for details

	GeometrySpiral *lGeometrySpiral2	=  static_cast<GeometrySpiral*>(mTurn->GetGeometryAt(2));
	if(lGeometrySpiral2!=NULL)
	{
		// Sets length for the second spiral
		lGeometrySpiral2->SetLength(value);

		emit RoadGeometryChanged(true);
	}
}
