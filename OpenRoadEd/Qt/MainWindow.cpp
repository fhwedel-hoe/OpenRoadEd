
#include <QtGui/QtGui>
#include "MainWindow.h"
#include "moc_MainWindow.cpp"

/**
 * Constructor, sets the references for the OSG object and OpenDRIVE structure
 *
 * @param osgMain Pointer to the OSG object
 * @param openDrive Pointer to the OpenDrive structure
 */
MainWindow::MainWindow(OSGMain *osgMain, OpenDrive *openDrive) 
{
	// Saves the references to the OSG object and OpenDrive structure
	mOsgMain = osgMain;
	mOpenDrive = openDrive;

	// Initializes the various sections of the interfaces
	initRoadTreeAndSettings();
	initCreation();
	initDocks();
	initOSG(mOsgMain);
	initDialogs(mOsgMain);
	initActions();
	initMenus();
	initToolbars();

	// Resizes the window
	resize(1280,800);
	
	// Reads the last used / default settings
	readSettings();

	// Sets a blank header for a new document
	mOpenDrive->SetHeader(1, 1, "Testfile", 1.0f, "Thu Feb 8 14:24:06 2007", 2000, -2000, 2000, -2000);
}

/**
 * Initializes the road tree panel and the record properties panel
 */
void MainWindow::initRoadTreeAndSettings()
{
	// Creates a new record settings panel
	mSettingsPage = new SettingsPage(mOpenDrive);

	// Creates and initializes a new road tree panel
	mRoadTree = new RoadTree(this);
	mRoadTree->Init(mOpenDrive);

	// Connects the record selection signals of the road tree to the appropriate selected slots of the record settings panel 
	// This is used to show the appropriate set of properties for the selected record type
	connect(mRoadTree, SIGNAL(NothingSelected()), mSettingsPage, SLOT(OnNothingSelected()));
	connect(mRoadTree, SIGNAL(RoadSelected(Road*)), mSettingsPage, SLOT(OnRoadSelected(Road*)));
	connect(mRoadTree, SIGNAL(RoadTypeSelected(RoadType*,double,double)), mSettingsPage, SLOT(OnRoadTypeSelected(RoadType*,double,double)));
	connect(mRoadTree, SIGNAL(GeometryLineSelected(GeometryBlock*,bool)), mSettingsPage, SLOT(OnGeometryLineSelected(GeometryBlock*,bool)));
	connect(mRoadTree, SIGNAL(GeometryTurnSelected(GeometryBlock*,bool)), mSettingsPage, SLOT(OnGeometryTurnSelected(GeometryBlock*,bool)));
	connect(mRoadTree, SIGNAL(ElevationSelected(Elevation*,double,double)), mSettingsPage, SLOT(OnElevationSelected(Elevation*,double,double)));
	connect(mRoadTree, SIGNAL(SuperElevationSelected(SuperElevation*,double,double)), mSettingsPage, SLOT(OnSuperElevationSelected(SuperElevation*,double,double)));
	connect(mRoadTree, SIGNAL(CrossfallSelected(Crossfall*,double,double)), mSettingsPage, SLOT(OnCrossfallSelected(Crossfall*,double,double)));
	connect(mRoadTree, SIGNAL(LaneSectionSelected(LaneSection*,double,double,bool)), mSettingsPage, SLOT(OnLaneSectionSelected(LaneSection*,double,double,bool)));
	connect(mRoadTree, SIGNAL(LaneSelected(Lane*)), mSettingsPage, SLOT(OnLaneSelected(Lane*)));
	connect(mRoadTree, SIGNAL(LaneWidthSelected(LaneWidth*,double,double)), mSettingsPage, SLOT(OnLaneWidthSelected(LaneWidth*,double,double)));
	connect(mRoadTree, SIGNAL(LaneRoadMarkSelected(LaneRoadMark*,double,double)), mSettingsPage, SLOT(OnLaneRoadMarkSelected(LaneRoadMark*,double,double)));
	connect(mRoadTree, SIGNAL(LaneMaterialSelected(LaneMaterial*,double,double)), mSettingsPage, SLOT(OnLaneMaterialSelected(LaneMaterial*,double,double)));
	connect(mRoadTree, SIGNAL(LaneVisibilitySelected(LaneVisibility*,double,double)), mSettingsPage, SLOT(OnLaneVisibilitySelected(LaneVisibility*,double,double)));
	connect(mRoadTree, SIGNAL(LaneSpeedSelected(LaneSpeed*,double,double)), mSettingsPage, SLOT(OnLaneSpeedSelected(LaneSpeed*,double,double)));
	connect(mRoadTree, SIGNAL(LaneAccessSelected(LaneAccess*,double,double)), mSettingsPage, SLOT(OnLaneAccessSelected(LaneAccess*,double,double)));
	connect(mRoadTree, SIGNAL(LaneHeightSelected(LaneHeight*,double,double)), mSettingsPage, SLOT(OnLaneHeightSelected(LaneHeight*,double,double)));
	connect(mRoadTree, SIGNAL(ObjectSelected(Object*)), mSettingsPage, SLOT(OnObjectSelected(Object*)));
	connect(mRoadTree, SIGNAL(SignalSelected(Signal*)), mSettingsPage, SLOT(OnSignalSelected(Signal*)));
	connect(mRoadTree, SIGNAL(JunctionSelected(Junction*)), mSettingsPage, SLOT(OnJunctionSelected(Junction*)));
	connect(mRoadTree, SIGNAL(JunctionConnectionSelected(JunctionConnection*)), mSettingsPage, SLOT(OnJunctionConnectionSelected(JunctionConnection*)));
	connect(mRoadTree, SIGNAL(JunctionLaneLinkSelected(JunctionLaneLink*)), mSettingsPage, SLOT(OnJunctionLaneLinkSelected(JunctionLaneLink*)));
	connect(mRoadTree, SIGNAL(JunctionPrioritySelected(JunctionPriorityRoad*)), mSettingsPage, SLOT(OnJunctionPrioritySelected(JunctionPriorityRoad*)));
	connect(mRoadTree, SIGNAL(JunctionControllerSelected(JunctionController*)), mSettingsPage, SLOT(OnJunctionControllerSelected(JunctionController*)));

	// Connects the road changed signal of the record settings panel to the appropriate slot of the road tree
	connect(mSettingsPage, SIGNAL(CurrentRoadChanged(bool)), mRoadTree, SLOT(OnCurrentRoadChanged(bool)));
}

/**
 * Initializes the record creation panel
 */
void MainWindow::initCreation()
{
	// Creates and initializes a new creation panel
	mCreationPage = new CreationPage(this);
	mCreationPage->Init(mOpenDrive, mRoadTree, mOsgMain);

	// Connects record selected signal of the road tree panel to the appropriate slots of the creation panel.
	// This is used to enable/disable creation buttons for records that cannot be created when unrelated
	// records are selected in the road tree
	connect(mRoadTree, SIGNAL(NothingSelected()), mCreationPage, SLOT(SomethingSelected()));
	connect(mRoadTree, SIGNAL(RoadSelected(Road*)), mCreationPage, SLOT(SomethingSelected()));
	connect(mRoadTree, SIGNAL(RoadTypeSelected(RoadType*,double,double)), mCreationPage, SLOT(SomethingSelected()));
	connect(mRoadTree, SIGNAL(GeometryLineSelected(GeometryBlock*,bool)), mCreationPage, SLOT(SomethingSelected()));
	connect(mRoadTree, SIGNAL(GeometryTurnSelected(GeometryBlock*,bool)), mCreationPage, SLOT(SomethingSelected()));
	connect(mRoadTree, SIGNAL(ElevationSelected(Elevation*,double,double)), mCreationPage, SLOT(SomethingSelected()));
	connect(mRoadTree, SIGNAL(SuperElevationSelected(SuperElevation*,double,double)), mCreationPage, SLOT(SomethingSelected()));
	connect(mRoadTree, SIGNAL(CrossfallSelected(Crossfall*,double,double)), mCreationPage, SLOT(SomethingSelected()));
	connect(mRoadTree, SIGNAL(LaneSectionSelected(LaneSection*,double,double,bool)), mCreationPage, SLOT(SomethingSelected()));
	connect(mRoadTree, SIGNAL(LaneSelected(Lane*)), mCreationPage, SLOT(SomethingSelected()));
	connect(mRoadTree, SIGNAL(LaneWidthSelected(LaneWidth*,double,double)), mCreationPage, SLOT(SomethingSelected()));
	connect(mRoadTree, SIGNAL(LaneRoadMarkSelected(LaneRoadMark*,double,double)), mCreationPage, SLOT(SomethingSelected()));
	connect(mRoadTree, SIGNAL(LaneMaterialSelected(LaneMaterial*,double,double)), mCreationPage, SLOT(SomethingSelected()));
	connect(mRoadTree, SIGNAL(LaneVisibilitySelected(LaneVisibility*,double,double)), mCreationPage, SLOT(SomethingSelected()));
	connect(mRoadTree, SIGNAL(LaneSpeedSelected(LaneSpeed*,double,double)), mCreationPage, SLOT(SomethingSelected()));
	connect(mRoadTree, SIGNAL(LaneAccessSelected(LaneAccess*,double,double)), mCreationPage, SLOT(SomethingSelected()));
	connect(mRoadTree, SIGNAL(LaneHeightSelected(LaneHeight*,double,double)), mCreationPage, SLOT(SomethingSelected()));
	connect(mRoadTree, SIGNAL(ObjectSelected(Object*)), mCreationPage, SLOT(SomethingSelected()));
	connect(mRoadTree, SIGNAL(SignalSelected(Signal*)), mCreationPage, SLOT(SomethingSelected()));
	connect(mRoadTree, SIGNAL(JunctionSelected(Junction*)), mCreationPage, SLOT(SomethingSelected()));
	connect(mRoadTree, SIGNAL(JunctionConnectionSelected(JunctionConnection*)), mCreationPage, SLOT(SomethingSelected()));
	connect(mRoadTree, SIGNAL(JunctionLaneLinkSelected(JunctionLaneLink*)), mCreationPage, SLOT(SomethingSelected()));
	connect(mRoadTree, SIGNAL(JunctionPrioritySelected(JunctionPriorityRoad*)), mCreationPage, SLOT(SomethingSelected()));
	connect(mRoadTree, SIGNAL(JunctionControllerSelected(JunctionController*)), mCreationPage, SLOT(SomethingSelected()));

	// Connects the road changed signal of the creation panel with the appropriate slot of the road tree
	connect(mCreationPage, SIGNAL(CurrentRoadChanged(bool)), mRoadTree, SLOT(OnCurrentRoadChanged(bool)));

	// Creates and initializes a separate delete panel, which holds a generic delete button, used to delete any record type
	mDeleteAll = new DeleteAll;
	mDeleteAll->Init(mOpenDrive, mRoadTree, mOsgMain);

	// Connects the road change signal of the delete panel with the appropriate slot of the road tree
	connect(mDeleteAll, SIGNAL(RoadChanged(bool)), mRoadTree, SLOT(OnCurrentRoadChanged(bool)));
}

/**
 * Initializes the dock widgets
 */
void MainWindow::initDocks()
{
	// Creates the left dock widget
	mLeftDock = new QDockWidget("Road tree",this);
	mLeftDock->setTitleBarWidget(new QWidget(this));
	addDockWidget(Qt::DockWidgetArea::LeftDockWidgetArea,mLeftDock);

	// Creates a box layout and a generic widget used to store both the road tree and the delete button
	QVBoxLayout *lLeftDockLayout = new QVBoxLayout;
	lLeftDockLayout->addWidget(mRoadTree);
	lLeftDockLayout->addWidget(mDeleteAll);
	QWidget *lLeftDockWidget = new QWidget(this);
	lLeftDockWidget->setLayout(lLeftDockLayout);
	mLeftDock->setWidget(lLeftDockWidget);

	// Creates the right dock widget
	mRightDock = new QDockWidget("Record properties",this);
	mRightDock->setTitleBarWidget(new QWidget(this));
	addDockWidget(Qt::DockWidgetArea::RightDockWidgetArea,mRightDock);

	// Creates a scroll area widget to store the record properties panel
	QScrollArea *scrollArea = new QScrollArea(this);
	scrollArea->setWidget(mSettingsPage);
	scrollArea->setWidgetResizable(true);
	scrollArea->setMinimumWidth(250);
	mRightDock->setWidget(scrollArea);
}

/**
 * Initializes all the actions
 */
void MainWindow::initActions()
{
	// Creates a new document action and connects it to the newDocument method
	mNewAct = new QAction(tr("&New..."), this);
	mNewAct->setShortcut(QKeySequence::New);
	connect(mNewAct, SIGNAL(triggered()), this, SLOT(newDocument()));

	// Creates an open document action and connects it to the openXML method
	mOpenAct = new QAction(tr("&Open..."), this);
	mOpenAct->setShortcuts(QKeySequence::Open);
	connect(mOpenAct, SIGNAL(triggered()), this, SLOT(openXML()));

	// Creates a save document action and connects it to the saveXML method
	mSaveAct = new QAction(tr("&Save..."), this);
	mSaveAct->setShortcuts(QKeySequence::Save);
	connect(mSaveAct, SIGNAL(triggered()), this, SLOT(saveXML()));

	// Creates a save geometry action and connects it to the saveOSG method
	mSaveGeometryAct = new QAction(tr("Save geometry..."), this);
	connect(mSaveGeometryAct, SIGNAL(triggered()), this, SLOT(saveOSG()));

	// Creates an exit action and connects it to the close slot
	mExitAct = new QAction(tr("E&xit"), this);
	mExitAct->setShortcuts(QKeySequence::Quit);
	connect(mExitAct, SIGNAL(triggered()), this, SLOT(close()));

	// Creates an about action and connects it to the about method
	mAboutAct = new QAction(tr("&About"), this);
	connect(mAboutAct, SIGNAL(triggered()), this, SLOT(about()));

	// Creates a help action and connects it to the help method
	mHelpAct = new QAction(tr("Help"), this);
	connect(mHelpAct, SIGNAL(triggered()), this, SLOT(help()));

	// Creates a show/hide chordline action and connects it to the OnChordLineShowHide method
	mChordlineShowHide = new QAction(QIcon("Resources/Icons/ChordLine.png"),tr("&Chord line"), this);
	mChordlineShowHide->setCheckable(true);
	connect(mChordlineShowHide, SIGNAL(toggled(bool)), this, SLOT(OnChordLineShowHide(bool)));

	// Creates a show/hide road tree coloring action and connects it to the ColorCode method of the RoadTree object
	mTreeColorCodingShowHide = new QAction(QIcon("Resources/Icons/TreeColoring.png"),tr("Tree coloring"), this);
	mTreeColorCodingShowHide->setCheckable(true);
	connect(mTreeColorCodingShowHide, SIGNAL(toggled(bool)), mRoadTree, SLOT(ColorCode(bool)));

	// Creates a delete confirmation action and connects it to the ToggleDeleteConfirmation method of the DeleteAll object
	mDeleteConfirmationToggle = new QAction(QIcon("Resources/Icons/DeleteConfirmation.png"),tr("Delete confirmation"), this);
	mDeleteConfirmationToggle->setCheckable(true);
	connect(mDeleteConfirmationToggle, SIGNAL(toggled(bool)), mDeleteAll, SLOT(ToggleDeleteConfirmation(bool)));

	// Creates a grid settings dialog action and connects it to the Run method of the ReferencePlaneDialog object
	mReferencePlaneShowDialog = new QAction(tr("Grid settings..."), this);
	connect(mReferencePlaneShowDialog, SIGNAL(triggered()), mReferencePlaneDialog, SLOT(Run()));

	// Creates a show/hide grid action and connects it to the ShowHide method of the ReferencePlaneDialog object
	mReferencePlaneShowHide = new QAction(QIcon("Resources/Icons/Grid.png"),tr("Show grid"), this);
	mReferencePlaneShowHide->setCheckable(true);
	connect(mReferencePlaneShowHide, SIGNAL(toggled(bool)), mReferencePlaneDialog, SLOT(ShowHide(bool)));

	// Creates a generate scenery action and connects it to the Run method of the SceneryDialog object
	mSceneryShowDialog = new QAction(QIcon("Resources/Icons/GenerateScenery.png"),tr("Generate scenery..."), this);
	connect(mSceneryShowDialog, SIGNAL(triggered()), mSceneryDialog, SLOT(Run()));
	
	// Creates a show/hide scenery action and connects it to the ShowHide method of the SceneryDialog object
	mSceneryShowHide = new QAction(QIcon("Resources/Icons/Scenery.png"),tr("Show scenery"),this);
	mSceneryShowHide->setCheckable(true);
	mSceneryShowHide->setChecked(false);
	connect(mSceneryShowHide, SIGNAL(toggled(bool)), mSceneryDialog, SLOT(ShowHide(bool)));

	// Creates a show/hide helpers action and connects it to the OnHelpersShowHide method
	mHelpersShowHide = new QAction(QIcon("Resources/Icons/Helpers.png"),tr("Show helpers"),this);
	mHelpersShowHide->setCheckable(true);
	mHelpersShowHide->setChecked(true);
	connect(mHelpersShowHide, SIGNAL(toggled(bool)), this, SLOT(OnHelpersShowHide(bool)));

	// Creates a connect roads dialog action and connects it to the Run method of the ConnectRoadsDialog object
	mConnectRoadsShowDialog = new QAction(QIcon("Resources/Icons/ConnectRoads.png"),tr("Connect roads..."), this);
	connect(mConnectRoadsShowDialog, SIGNAL(triggered()), mConnectRoadsDialog, SLOT(Run()));

	// Creates a take screenshot action and connects it to the OnTakeScreenshot method
	mTakeScreenshotAct = new QAction(QIcon("Resources/Icons/Screenshot.png"),tr("Take screenshot"), this);
	connect(mTakeScreenshotAct, SIGNAL(triggered()), this, SLOT(OnTakeScreenshot()));
}

/**
 * Initializes the menu
 */
void MainWindow::initMenus()
{
	// Creates a new File menu and adds the appropriate actions
	mFileMenu = new QMenu(tr("&File"), this);
	mFileMenu->addAction(mNewAct);
	mFileMenu->addAction(mOpenAct);
	mFileMenu->addAction(mSaveAct);
	mFileMenu->addAction(mSaveGeometryAct);
	mFileMenu->addSeparator();
	mFileMenu->addAction(mExitAct);

	// Creates a new Help menu and adds the appropriate actions
	mHelpMenu = new QMenu(tr("&Help"), this);
	mHelpMenu->addAction(mHelpAct);
	mHelpMenu->addAction(mAboutAct);

	// Creates a new Options menu and adds the appropriate actions
	mOptionsMenu = new QMenu(tr("&Options"), this);
	mOptionsMenu->addAction(mTreeColorCodingShowHide);
	mOptionsMenu->addAction(mDeleteConfirmationToggle);
	mOptionsMenu->addSeparator();
	mOptionsMenu->addAction(mChordlineShowHide);
	mOptionsMenu->addSeparator();
	mOptionsMenu->addAction(mReferencePlaneShowHide);
	mOptionsMenu->addAction(mReferencePlaneShowDialog);
	mOptionsMenu->addSeparator();
	mOptionsMenu->addAction(mSceneryShowHide);
	mOptionsMenu->addSeparator();
	mOptionsMenu->addAction(mHelpersShowHide);

	// Creates the new Tools menu and adds the appropriate actions
	mToolsMenu = new QMenu(tr("&Tools"), this);
	mToolsMenu->addAction(mConnectRoadsShowDialog);
	mToolsMenu->addSeparator();
	mToolsMenu->addAction(mTakeScreenshotAct);
	mToolsMenu->addAction(mSceneryShowDialog);
	
	// Adds the menus to the menu bar
	menuBar()->addMenu(mFileMenu);
	menuBar()->addMenu(mOptionsMenu);
	menuBar()->addMenu(mToolsMenu);
	menuBar()->addMenu(mHelpMenu);
}

/**
 * Initializes the toolbar and the appropriate tool buttons
 */
void MainWindow::initToolbars()
{
	// Creates a new tool bar and adds the appropriate actions as tool buttons
	mMainToolBar= new QToolBar("MainToolbar",this);
	addToolBar(mMainToolBar);
	mMainToolBar->setIconSize(QSize(18,18));
	mMainToolBar->addAction(mChordlineShowHide);
	mMainToolBar->addAction(mReferencePlaneShowHide);
	mMainToolBar->addAction(mHelpersShowHide);
	mMainToolBar->addSeparator();
	mMainToolBar->addAction(mSceneryShowHide);
	mMainToolBar->addAction(mSceneryShowDialog);
	mMainToolBar->addAction(mTakeScreenshotAct);
	mMainToolBar->addSeparator();
	mMainToolBar->addAction(mConnectRoadsShowDialog);

	// Sets the default message for the status bar
	statusBar()->showMessage("Ready");
}

/**
 * Initializes the OSG widget and the 3D viewport
 */
void MainWindow::initOSG(OSGMain *osgMain)
{
	// Creates a new OSG 3D viewport
	mOSGViewer = new QOSGWidget(osgMain, this);

	// Creates a new generic central widget used to hold both thw OSG 3D viewport and the creation panel
	QWidget *mCentralWidget = new QWidget;
	QVBoxLayout *mCentralLayout = new QVBoxLayout;
	mCentralLayout->addWidget(mOSGViewer);
	mCentralLayout->addWidget(mCreationPage);
	mCentralWidget->setLayout(mCentralLayout);
	setCentralWidget(mCentralWidget);

	// Initializes the 3D viewport a gives it the keyboard focus
	mOSGViewer->Init(mRoadTree);
	mOSGViewer->setFocus();

	// Connects the road recalculated signal of the road tree to the appropriate slot of the OSG widget 
	connect(mRoadTree, SIGNAL(RoadRecalculated(unsigned int)), mOSGViewer, SLOT(OnRoadRecalculated(unsigned int)));

	// Connects the record selected signal of the road tree to teh appropriate slot of the OSG widget
	// This is used to highlight the selected items in the 3D-view
	connect(mRoadTree, SIGNAL(NothingSelected()), mOSGViewer, SLOT(SomethingSelected()));
	connect(mRoadTree, SIGNAL(RoadSelected(Road*)), mOSGViewer, SLOT(SomethingSelected()));
	connect(mRoadTree, SIGNAL(RoadTypeSelected(RoadType*,double,double)), mOSGViewer, SLOT(SomethingSelected()));
	connect(mRoadTree, SIGNAL(GeometryLineSelected(GeometryBlock*,bool)), mOSGViewer, SLOT(SomethingSelected()));
	connect(mRoadTree, SIGNAL(GeometryTurnSelected(GeometryBlock*,bool)), mOSGViewer, SLOT(SomethingSelected()));
	connect(mRoadTree, SIGNAL(ElevationSelected(Elevation*,double,double)), mOSGViewer, SLOT(SomethingSelected()));
	connect(mRoadTree, SIGNAL(SuperElevationSelected(SuperElevation*,double,double)), mOSGViewer, SLOT(SomethingSelected()));
	connect(mRoadTree, SIGNAL(CrossfallSelected(Crossfall*,double,double)), mOSGViewer, SLOT(SomethingSelected()));
	connect(mRoadTree, SIGNAL(LaneSectionSelected(LaneSection*,double,double,bool)), mOSGViewer, SLOT(SomethingSelected()));
	connect(mRoadTree, SIGNAL(LaneSelected(Lane*)), mOSGViewer, SLOT(SomethingSelected()));
	connect(mRoadTree, SIGNAL(LaneWidthSelected(LaneWidth*,double,double)), mOSGViewer, SLOT(SomethingSelected()));
	connect(mRoadTree, SIGNAL(LaneRoadMarkSelected(LaneRoadMark*,double,double)), mOSGViewer, SLOT(SomethingSelected()));
	connect(mRoadTree, SIGNAL(LaneMaterialSelected(LaneMaterial*,double,double)), mOSGViewer, SLOT(SomethingSelected()));
	connect(mRoadTree, SIGNAL(LaneVisibilitySelected(LaneVisibility*,double,double)), mOSGViewer, SLOT(SomethingSelected()));
	connect(mRoadTree, SIGNAL(LaneSpeedSelected(LaneSpeed*,double,double)), mOSGViewer, SLOT(SomethingSelected()));
	connect(mRoadTree, SIGNAL(LaneAccessSelected(LaneAccess*,double,double)), mOSGViewer, SLOT(SomethingSelected()));
	connect(mRoadTree, SIGNAL(LaneHeightSelected(LaneHeight*,double,double)), mOSGViewer, SLOT(SomethingSelected()));
	connect(mRoadTree, SIGNAL(ObjectSelected(Object*)), mOSGViewer, SLOT(SomethingSelected()));
	connect(mRoadTree, SIGNAL(SignalSelected(Signal*)), mOSGViewer, SLOT(SomethingSelected()));
	connect(mRoadTree, SIGNAL(JunctionSelected(Junction*)), mOSGViewer, SLOT(SomethingSelected()));
	connect(mRoadTree, SIGNAL(JunctionConnectionSelected(JunctionConnection*)), mOSGViewer, SLOT(SomethingSelected()));
	connect(mRoadTree, SIGNAL(JunctionLaneLinkSelected(JunctionLaneLink*)), mOSGViewer, SLOT(SomethingSelected()));
	connect(mRoadTree, SIGNAL(JunctionPrioritySelected(JunctionPriorityRoad*)), mOSGViewer, SLOT(SomethingSelected()));
	connect(mRoadTree, SIGNAL(JunctionControllerSelected(JunctionController*)), mOSGViewer, SLOT(SomethingSelected()));
}

/**
 * Initializes the dialogs
 * 
 * @param osgMain OSG object reference
 */
void MainWindow::initDialogs(OSGMain *osgMain)
{
	// Creates a new grid settings dialog
	mReferencePlaneDialog = new ReferencePlaneDialog(osgMain);

	// Creates a new scenery generation dialog
	mSceneryDialog = new SceneryDialog(osgMain);
	
	// Creates a new road connection dialog
	mConnectRoadsDialog = new ConnectRoadsDialog(mOpenDrive, mRoadTree);

	// Connects the road changed signal of the road connection dialog to the appropriate slot of the OSG widget
	// This is used to update the roads when the roads are moved/connected in the dialog
	connect(mConnectRoadsDialog, SIGNAL(RoadChanged(unsigned int)), mOSGViewer, SLOT(OnRoadRecalculated(unsigned int)));
	
	// Connects the record selected signal of the road tree to the appropriate slot of the road connection dialog
	// This is used to allow for road selection through the 3D viewport while using the dialog
	connect(mRoadTree, SIGNAL(RoadSelected(Road*)), mConnectRoadsDialog, SLOT(RoadSelected()));
}

/**
 * Loads the default or the last used settings
 */
void MainWindow::readSettings()
{
	// Opens the settings file
	QSettings lSettingsFile("Settings.ini", QSettings::IniFormat);

	// Reads the chord line visibility state
	bool lChordLineState = lSettingsFile.value("View/ChordLine",false).toBool();
	mChordlineShowHide->setChecked(lChordLineState);
	mOsgMain->ShowChordLine(lChordLineState);

	// Reads the road tree coloring state
	bool lTreeColorCodingState = lSettingsFile.value("View/TreeColorCoding",true).toBool();
	mTreeColorCodingShowHide->setChecked(lTreeColorCodingState);
	mRoadTree->ColorCode(lTreeColorCodingState);

	// Reads the delete confirmation state
	bool lDeleteConfirmationState = lSettingsFile.value("View/DeleteConfirmation",true).toBool();
	mDeleteConfirmationToggle->setChecked(lDeleteConfirmationState);
	mDeleteAll->ToggleDeleteConfirmation(lDeleteConfirmationState);

	// Reads the grid visibility state
	bool lReferencePlaneState = lSettingsFile.value("View/ReferencePlane",true).toBool();
	mReferencePlaneShowHide->setChecked(lReferencePlaneState);
	mOsgMain->ShowGridOrRefPlane(lReferencePlaneState);

	// Reads the scenery visibility state
	bool lSceneryState = lSettingsFile.value("View/Scenery",true).toBool();
	mSceneryShowHide->setChecked(lSceneryState);
	mOsgMain->ShowScenery(lSceneryState);

	// Reads the helpers visibility state
	bool lHelpersState = lSettingsFile.value("View/Helpers",true).toBool();
	mHelpersShowHide->setChecked(lHelpersState);
	mOsgMain->ShowRecordsHelpers(lHelpersState);

	// Reads the grid settings
	int lSGridRows = lSettingsFile.value("Grid/Rows",50).toInt();
	int lSGridCollumns = lSettingsFile.value("Grid/Collumns",50).toInt();
	double lSGridMinX = lSettingsFile.value("Grid/MinX",-5000).toDouble();
	double lSGridMinY = lSettingsFile.value("Grid/MinY",-5000).toDouble();
	double lSGridMaxX = lSettingsFile.value("Grid/MaxX",5000).toDouble();
	double lSGridMaxY = lSettingsFile.value("Grid/MaxY",5000).toDouble();
	mReferencePlaneDialog->SetGridValues(lSGridRows, lSGridCollumns, lSGridMinX, lSGridMinY, lSGridMaxX, lSGridMaxY);

	// Sets the camera to it's home positon
	mOsgMain->GetViewer()->home(); 
}

/**
 * Clears the structure and starts a new document
 */
void MainWindow::newDocument()
{
	// Clears the OpenDrive structure, the road tree and the OSG hierarchy
	mOpenDrive->Clear();
	mRoadTree->ClearTree();
	mOsgMain->Clear();
}

/**
 * Opens the "about" dialog
 */
void MainWindow::about()
{
	// Creates a new dialog with the basic "about" information
	QDialog lAbout;
	QLabel *lSoftware = new QLabel("OpenRoadEd");
	lSoftware->setFont(QFont("Arial",21,20));
	lSoftware->setAlignment(Qt::AlignHCenter);
	QLabel *lDesc = new QLabel("Open Source Road Editor\n");
	lDesc->setFont(QFont("Arial",11,12));
	lDesc->setAlignment(Qt::AlignHCenter);
	QLabel *lNames = new QLabel("by Dmitri and Egor Kurteanu");
	lNames->setAlignment(Qt::AlignHCenter);
	QVBoxLayout *lMainLayout=new QVBoxLayout;
	lMainLayout->addWidget(lSoftware);
	lMainLayout->addWidget(lDesc);
	lMainLayout->addWidget(lNames);
	lAbout.setLayout(lMainLayout);
	lAbout.exec();
}

/**
 * Opens the help file
 */
void MainWindow::help()
{
	// Opens the help file
	QString filename = "file:///";
	filename.append(QDir::currentPath());
	filename.append("/Help/OpenRoadEdHelp.pdf");
	QDesktopServices::openUrl(QUrl(filename));
}

/**
 * Opens an "open file" dialog and parses the selected file
 */
void MainWindow::openXML()
{
	// Opens an "open file" dialog
	QString fileName = QFileDialog::getOpenFileName(this,tr("Open File"), QDir::currentPath(), tr("OpenDRIVE (*.xodr *.xml)"));
	if (fileName==NULL)
		return;

	// Cleares the road structure, road tree and OSG hierarchy
	newDocument();

	// Shows a "Loading" dialog
	LoadingDialog lLoading;
	lLoading.show();
	QApplication::processEvents();

	// Parses the file and fills in the OpenDrive structure
	OpenDriveXmlParser parser(mOpenDrive);
	parser.ReadFile(fileName.toStdString());

	// Fills in the road tree
	mRoadTree->LoadStructure(mOpenDrive);

	// Generates geometry
	mOsgMain->DrawRoadChordLine();
	mOsgMain->DrawRoads();
	mOsgMain->DrawJunctions();

	// Zooms the camera to capture the road
	mOsgMain->GetViewer()->home(); 

	// Updates the rendering window
	mOsgMain->frame();
	mOSGViewer->update();
	QApplication::processEvents();

	// Returns the keyboard focus to the 3D viewport
	setFocus();
	mOSGViewer->setFocus();
	
	// Hides the "Loading" dialog
	lLoading.hide();
}

/**
 * Opens a "save file" dialog and saves the road structure to the selected file
 */
void MainWindow::saveXML()
{
	// Opens an "save file" dialog
	QString fileName = QFileDialog::getSaveFileName(this,tr("Save File"), QDir::currentPath(), tr("OpenDRIVE (*.xodr *.xml)"));
	if (fileName==NULL)
		return;

	// Saves the road data to the file
	OpenDriveXmlWriter writer(mOpenDrive);
	writer.WriteFile(fileName.toStdString());

	// Returns the keyboard focus to the 3D viewport
	setFocus();
	mOSGViewer->setFocus();
}

/**
 * Opens a "save file" dialog and saves the road geometry to the selected file
 */
void MainWindow::saveOSG()
{
	// Opens an "save file" dialog
	QString fileName = QFileDialog::getSaveFileName(this,tr("Save File"), QDir::currentPath(), tr("OpenDRIVE (*.osg)"));
	if (fileName==NULL)
		return;

	// Saves the geometry data to the file
	mOsgMain->SaveGeometry(fileName.toStdString());

	// Returns the keyboard focus to the 3D viewport
	setFocus();
	mOSGViewer->setFocus();
}

/**
 * Shows or hides the chord line
 */
void MainWindow::OnChordLineShowHide(bool state)
{
	// Toggles the chord line
	mOsgMain->ShowChordLine(state);

	// Saves the current state to the settings file
	QSettings lSettingsFile("Settings.ini", QSettings::IniFormat);
	lSettingsFile.setValue("View/ChordLine",mChordlineShowHide->isChecked());
	lSettingsFile.sync();
}

/**
 * Shows or hides the helpers
 */
void MainWindow::OnHelpersShowHide(bool state)
{
	// Toggles the helpers
	mOsgMain->ShowRecordsHelpers(state);

	// Saves the current state to the settings file
	QSettings lSettingsFile("Settings.ini", QSettings::IniFormat);
	lSettingsFile.setValue("View/Helpers",state);
	lSettingsFile.sync();
}

/**
 * Takes a top-down view screenshot of the whole road network.
 * The generated screenshot could be used for heightmap generation.
 */
void MainWindow::OnTakeScreenshot()
{
	// Hides the helpers
	mOsgMain->ShowChordLine(false);
	mOsgMain->ShowGridOrRefPlane(false);
	mOsgMain->ShowScenery(false);
	mOsgMain->ShowRecordsHelpers(false);

	// Takes a screenshot
	mOsgMain->TakeScreenshot();

	// Restores the helpers
	mOsgMain->ShowChordLine(mChordlineShowHide->isChecked());
	mOsgMain->ShowGridOrRefPlane(mReferencePlaneShowHide->isChecked());
	mOsgMain->ShowScenery(mSceneryShowHide->isChecked());
	mOsgMain->ShowRecordsHelpers(mHelpersShowHide->isChecked());
}