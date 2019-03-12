
#include <QtGui/QtGui>
#include "ReferencePlaneDialog.h"
#include "moc_ReferencePlaneDialog.cpp"

/**
 * Constructor
 * Initializes the widgets that make up the interface
 *
 * @param osgMain Pointer to OSG object
 */
ReferencePlaneDialog::ReferencePlaneDialog(OSGMain *osgMain) 
{
	// Reference for OSG Main Class
	mOsgMain = osgMain;

	// Main vertical layout
	QHBoxLayout *lMainLayout = new QHBoxLayout;

	//-------------------------------------------------
	mGridButton = new QRadioButton("Grid", this);
	mGridGroup = new QGroupBox;
	QFormLayout *lGridCfgLayout = new QFormLayout();
	//-------------------------------------------------
	mGridRows = new QSpinBox;
	mGridRows->setRange(1,10000);
	mGridRows->setValue(50);
	//-------------------------------------------------
	mGridCollumns = new QSpinBox;
	mGridCollumns->setRange(1,10000);
	mGridCollumns->setValue(50);
	//-------------------------------------------------
	mGridXMin = new QDoubleSpinBox;
	mGridXMin->setRange(-10000,10000);
	mGridXMin->setValue(-5000);
	//-------------------------------------------------
	mGridYMin = new QDoubleSpinBox;
	mGridYMin->setRange(-10000,10000);
	mGridYMin->setValue(-5000);
	//-------------------------------------------------
	mGridXMax = new QDoubleSpinBox;
	mGridXMax->setRange(-10000,10000);
	mGridXMax->setValue(5000);
	//-------------------------------------------------
	mGridYMax = new QDoubleSpinBox;
	mGridYMax->setRange(-10000,10000);
	mGridYMax->setValue(5000);
	//-------------------------------------------------
	lGridCfgLayout->addRow("Rows", mGridRows);
	lGridCfgLayout->addRow("Collumns", mGridCollumns);
	lGridCfgLayout->addRow("Min X", mGridXMin);
	lGridCfgLayout->addRow("Min Y", mGridYMin);
	lGridCfgLayout->addRow("Max X", mGridXMax);
	lGridCfgLayout->addRow("Max Y", mGridYMax);
	//-------------------------------------------------
	mGridGroup->setLayout(lGridCfgLayout);
	//-------------------------------------------------
	QVBoxLayout *lAllGridLayout = new QVBoxLayout;
	lAllGridLayout->addWidget(mGridButton);
	lAllGridLayout->addWidget(mGridGroup);


	mReferencePlaneButton = new QRadioButton("Reference image", this);
	mReferenceGroup = new QGroupBox;
	QFormLayout *lReferenceCfgLayout = new QFormLayout();
	//-------------------------------------------------
	mReferenceXMin = new QDoubleSpinBox;
	mReferenceXMin->setRange(-10000,10000);
	mReferenceXMin->setValue(-1000);
	//-------------------------------------------------
	mReferenceYMin = new QDoubleSpinBox;
	mReferenceYMin->setRange(-10000,10000);
	mReferenceYMin->setValue(-1000);
	//-------------------------------------------------
	mReferenceXMax = new QDoubleSpinBox;
	mReferenceXMax->setRange(-10000,10000);
	mReferenceXMax->setValue(1000);
	//-------------------------------------------------
	mReferenceYMax = new QDoubleSpinBox;
	mReferenceYMax->setRange(-10000,10000);
	mReferenceYMax->setValue(1000);
	//-------------------------------------------------
	QHBoxLayout *lTextureLayout = new QHBoxLayout;
	mReferenceTexture = new QLineEdit;

	mBrowseButton = new QToolButton();
	mBrowseButton->setFocusPolicy(Qt::StrongFocus);
	mBrowseButton->setIcon(QIcon("Resources/Icons/Folder.png"));
	mBrowseButton->setToolTip("Browse");

	lTextureLayout->addWidget(mReferenceTexture);
	lTextureLayout->addWidget(mBrowseButton);
	//-------------------------------------------------
	lReferenceCfgLayout->addRow("Texture", lTextureLayout);
	lReferenceCfgLayout->addRow("Min X", mReferenceXMin);
	lReferenceCfgLayout->addRow("Max X", mReferenceXMax);
	lReferenceCfgLayout->addRow("Min Y", mReferenceYMin);
	lReferenceCfgLayout->addRow("Max Y", mReferenceYMax);
	//-------------------------------------------------
	QVBoxLayout *lReferenceMainLayout = new QVBoxLayout;
	lReferenceMainLayout->addLayout(lReferenceCfgLayout);
	//-------------------------------------------------
	mReferenceGroup->setLayout(lReferenceMainLayout);
	//-------------------------------------------------
	QVBoxLayout *lAllReferenceLayout = new QVBoxLayout;
	lAllReferenceLayout->addWidget(mReferencePlaneButton);
	lAllReferenceLayout->addWidget(mReferenceGroup);


	// Horizontal layout of the two groups
	lMainLayout->addLayout(lAllGridLayout);
	lMainLayout->addLayout(lAllReferenceLayout);

	// Layout of the settings and Ok Cancel buttons
	QVBoxLayout *lDialogLayout = new QVBoxLayout;

	// Horizontal layout of the Ok Cancel buttons
	QHBoxLayout *lButtonLayout = new QHBoxLayout;
	QPushButton *mOkButton = new QPushButton("Ok");
	QPushButton *mCancelButton = new QPushButton("Cancel");
	lButtonLayout->addWidget(mOkButton);
	lButtonLayout->addWidget(mCancelButton);

	lDialogLayout->addLayout(lMainLayout);
	lDialogLayout->addLayout(lButtonLayout);

	// Dialog window layout
	setLayout(lDialogLayout);


	// Connections of the interface elements
	connect(mOkButton, SIGNAL(pressed()), this, SLOT(OkPressed()));
	connect(mCancelButton, SIGNAL(pressed()), this, SLOT(CancelPressed()));
	connect(mBrowseButton, SIGNAL(pressed()), this, SLOT(BrowseForTexture()));
	connect(mGridButton, SIGNAL(toggled(bool)), this, SLOT(GridSelected(bool)));
	connect(mReferencePlaneButton, SIGNAL(toggled(bool)), this, SLOT(ReferenceSelected(bool)));


	// Default values
	mCurSelected=0;
	mGridButton->setChecked(true);

	setWindowTitle("Grid settings");
}

/**
 * Sets the grid values programmatically
 */
void ReferencePlaneDialog::SetGridValues(int rows, int colls, double minX, double minY, double maxX, double maxY)
{
	mGridRows->setValue(rows);
	mGridCollumns->setValue(colls);
	mGridXMin->setValue(minX);
	mGridYMin->setValue(minY);
	mGridXMax->setValue(maxX);
	mGridYMax->setValue(maxY);
	mOsgMain->DrawGrid(mGridXMin->value(), mGridXMax->value(), mGridCollumns->value(), mGridYMin->value(), mGridYMax->value(), mGridRows->value());
}

/**
 * Launches the dialog
 */
void ReferencePlaneDialog::Run()
{
	exec();
}

/**
 * Shows or hides the grid/reference plane
 */
void ReferencePlaneDialog::ShowHide(bool state)
{
	mOsgMain->ShowGridOrRefPlane(state);

	QSettings lSettingsFile("Settings.ini", QSettings::IniFormat);
	lSettingsFile.setValue("View/ReferencePlane", state);
	lSettingsFile.sync();
}

/**
 * Shows a open file dialog to select an image for reference plane
 */
void ReferencePlaneDialog::BrowseForTexture()
{
	QString fileName = QFileDialog::getOpenFileName(this,tr("Open File"), QDir::currentPath(), tr("Images (*.jpg *.tga)"));

	mReferenceTexture->setText(fileName);
}

/**
 * Called when the grid radio button is selected
 */
void ReferencePlaneDialog::GridSelected(bool checked)
{
	if(checked)
	{
		mGridGroup->setEnabled(true);
		mReferenceGroup->setEnabled(false);
	}
}

/**
 * Called when reference plane radio button is selected
 */
void ReferencePlaneDialog::ReferenceSelected(bool checked)
{
	if(checked)
	{
		mGridGroup->setEnabled(false);
		mReferenceGroup->setEnabled(true);
	}
}

/**
 * Closes the dialog
 */
void ReferencePlaneDialog::OkPressed()
{
	if(mGridButton->isChecked())
	{
		// Draws the grid
		mOsgMain->DrawGrid(mGridXMin->value(), mGridXMax->value(), mGridCollumns->value(), mGridYMin->value(), mGridYMax->value(), mGridRows->value());
		mCurSelected=0;

		// Saves the grid settings to the settings file
		QSettings lSettingsFile("Settings.ini", QSettings::IniFormat);
		lSettingsFile.setValue("Grid/Rows",mGridRows->value());
		lSettingsFile.setValue("Grid/Collumns", mGridCollumns->value());
		lSettingsFile.setValue("Grid/MinX",mGridXMin->value());
		lSettingsFile.setValue("Grid/MinY",mGridYMin->value());
		lSettingsFile.setValue("Grid/MaxX",mGridXMax->value());
		lSettingsFile.setValue("Grid/MaxY",mGridYMax->value());
		lSettingsFile.sync();
	}
	else if(mReferencePlaneButton->isChecked())
	{
		// Draws the reference plane
		mOsgMain->DrawReferencePlane(mReferenceXMin->value(),mReferenceXMax->value(),mReferenceYMin->value(),mReferenceYMax->value(),mReferenceTexture->text().toStdString());
		mCurSelected=1;
	}
	accept();
}
void ReferencePlaneDialog::CancelPressed()
{
	if(mCurSelected==0)
		mGridButton->setChecked(true);
	else if(mCurSelected==1)
		mReferencePlaneButton->setChecked(true);

	reject();
}