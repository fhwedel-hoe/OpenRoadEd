
#include <QtGui/QtGui>
#include "SceneryDialog.h"
#include "moc_SceneryDialog.cpp"

/**
 * Constructor
 * Initializes the widgets that make up the interface
 *
 * @param osgMain Pointer to OSG object
 */
SceneryDialog::SceneryDialog(OSGMain *osgMain) 
{
	// Reference for OSG Main Class
	mOsgMain = osgMain;

	//-------------------------------------------------
	mSceneryGroup = new QGroupBox;
	QFormLayout *lSceneryCfgLayout = new QFormLayout();
	//-------------------------------------------------
	mCustomSize = new QGroupBox("Custom size");
	mCustomSize->setCheckable(true);
	mCustomSize->setChecked(false);
	QFormLayout *lScenerySizeLayout = new QFormLayout();
	//-------------------------------------------------
	mSceneryXMin = new QDoubleSpinBox;
	mSceneryXMin->setRange(-10000,10000);
	mSceneryXMin->setValue(-1000);
	//-------------------------------------------------
	mSceneryYMin = new QDoubleSpinBox;
	mSceneryYMin->setRange(-10000,10000);
	mSceneryYMin->setValue(-1000);
	//-------------------------------------------------
	mSceneryXMax = new QDoubleSpinBox;
	mSceneryXMax->setRange(-10000,10000);
	mSceneryXMax->setValue(1000);
	//-------------------------------------------------
	mSceneryYMax = new QDoubleSpinBox;
	mSceneryYMax->setRange(-10000,10000);
	mSceneryYMax->setValue(1000);
	//-------------------------------------------------
	lScenerySizeLayout->addRow("Min X", mSceneryXMin);
	lScenerySizeLayout->addRow("Min Y", mSceneryYMin);
	lScenerySizeLayout->addRow("Max X", mSceneryXMax);
	lScenerySizeLayout->addRow("Max Y", mSceneryYMax);
	mCustomSize->setLayout(lScenerySizeLayout);
	//-------------------------------------------------
	mSceneryResolutionX = new QSpinBox;
	mSceneryResolutionX->setRange(1,1000);
	mSceneryResolutionX->setValue(10);
	//-------------------------------------------------
	mSceneryResolutionY = new QSpinBox;
	mSceneryResolutionY->setRange(1,1000);
	mSceneryResolutionY->setValue(10);
	//-------------------------------------------------
	mSceneryHeightMultiplier = new QDoubleSpinBox;
	mSceneryHeightMultiplier->setRange(-1000,1000);
	mSceneryHeightMultiplier->setValue(20);
	//-------------------------------------------------
	mSceneryAverageElevation = new QDoubleSpinBox;
	mSceneryAverageElevation->setRange(-100,100);
	mSceneryAverageElevation->setValue(0.0);
	//-------------------------------------------------
	QHBoxLayout *lTextureLayout = new QHBoxLayout;
	mSceneryTexture = new QLineEdit;

	mBrowseTexture = new QToolButton();
	mBrowseTexture->setFocusPolicy(Qt::StrongFocus);
	mBrowseTexture->setIcon(QIcon("Resources/Icons/Folder.png"));
	mBrowseTexture->setToolTip("Browse texture");

	lTextureLayout->addWidget(mSceneryTexture);
	lTextureLayout->addWidget(mBrowseTexture);
	//-------------------------------------------------
	QHBoxLayout *lHeightmapLayout = new QHBoxLayout;
	mSceneryHeightmap = new QLineEdit;

	mBrowseHeightmap = new QToolButton();
	mBrowseHeightmap->setFocusPolicy(Qt::StrongFocus);
	mBrowseHeightmap->setIcon(QIcon("Resources/Icons/Folder.png"));
	mBrowseHeightmap->setToolTip("Browse heightmap");

	lHeightmapLayout->addWidget(mSceneryHeightmap);
	lHeightmapLayout->addWidget(mBrowseHeightmap);
	//-------------------------------------------------
	lSceneryCfgLayout->addRow("Heightmap", lHeightmapLayout);
	lSceneryCfgLayout->addRow("Texture", lTextureLayout);
	lSceneryCfgLayout->addRow(mCustomSize);
	lSceneryCfgLayout->addRow("Resolution X", mSceneryResolutionX);
	lSceneryCfgLayout->addRow("Resolution Y", mSceneryResolutionY);
	lSceneryCfgLayout->addRow("Height", mSceneryHeightMultiplier);
	lSceneryCfgLayout->addRow("Elevation", mSceneryAverageElevation);
	//-------------------------------------------------
	mSceneryGroup->setLayout(lSceneryCfgLayout);
	//-------------------------------------------------


	// Layout of the settings and Ok Cancel buttons
	QVBoxLayout *lDialogLayout = new QVBoxLayout;

	// Horizontal layout of the Ok Cancel buttons
	QHBoxLayout *lButtonLayout = new QHBoxLayout;
	QPushButton *mOkButton = new QPushButton("Ok");
	QPushButton *mCancelButton = new QPushButton("Cancel");
	lButtonLayout->addWidget(mOkButton);
	lButtonLayout->addWidget(mCancelButton);

	// Adding groupbox and buttons to the main layout
	lDialogLayout->addWidget(mSceneryGroup);
	lDialogLayout->addLayout(lButtonLayout);

	// Dialog window layout
	setLayout(lDialogLayout);

	setWindowTitle("Generate scenery");

	// Connections of the interface elements
	connect(mOkButton, SIGNAL(pressed()), this, SLOT(OkPressed()));
	connect(mCancelButton, SIGNAL(pressed()), this, SLOT(CancelPressed()));
	connect(mBrowseTexture, SIGNAL(pressed()), this, SLOT(BrowseForTexture()));
	connect(mBrowseHeightmap, SIGNAL(pressed()), this, SLOT(BrowseForHeightmap()));

}

/**
 * Launches the dialog
 */
void SceneryDialog::Run()
{
	exec();
}

/**
 * Shows or hides the scenery
 */
void SceneryDialog::ShowHide(bool state)
{
	// Toggles the visibility of the scenery node
	mOsgMain->ShowScenery(state);

	// Saves the state to the settings file
	QSettings lSettingsFile("Settings.ini", QSettings::IniFormat);
	lSettingsFile.setValue("View/Scenery", state);
	lSettingsFile.sync();
}

/**
 * Shows a open file dialog to select an image for texture
 */
void SceneryDialog::BrowseForTexture()
{
	QString fileName = QFileDialog::getOpenFileName(this,tr("Open File"), QDir::currentPath(), tr("Images (*.jpg *.tga)"));

	if (fileName!=nullptr)
		mSceneryTexture->setText(fileName);
}

/**
 * Shows a open file dialog to select an image for heightmap
 */
void SceneryDialog::BrowseForHeightmap()
{
	QString fileName = QFileDialog::getOpenFileName(this,tr("Open File"), QDir::currentPath(), tr("Images (*.jpg *.tga)"));

	if (fileName!=nullptr)
		mSceneryHeightmap->setText(fileName);
}

/**
 * Closes the dialog and generates the scenery
 */
void SceneryDialog::OkPressed()
{
	// Shows the loading screen
	LoadingDialog lLoading;
	lLoading.show();
	QApplication::processEvents();

	// Generates the landscape
	if(mCustomSize->isChecked())
	{
		mOsgMain->DrawScenery(mSceneryHeightmap->text().toStdString(),mSceneryTexture->text().toStdString(),  
								mSceneryYMax->value(), mSceneryYMin->value(), mSceneryXMax->value(), mSceneryXMin->value(),
								mSceneryResolutionX->value(), mSceneryResolutionY->value(),
								mSceneryHeightMultiplier->value(),mSceneryAverageElevation->value());
	}
	else
	{
		mOsgMain->DrawScenery(mSceneryHeightmap->text().toStdString(), mSceneryTexture->text().toStdString(),
								mSceneryResolutionX->value(), mSceneryResolutionY->value(),
								mSceneryHeightMultiplier->value(),mSceneryAverageElevation->value() );
	}

	// Hides the loading screen
	lLoading.hide();
	accept();
}
void SceneryDialog::CancelPressed()
{
	reject();
}
