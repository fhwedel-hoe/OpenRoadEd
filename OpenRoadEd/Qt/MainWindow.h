#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QtWidgets/QMainWindow>
#include <QtCore/QSettings>
#include "QOSGWidget.h"
#include "Tree/RoadTree.h"
#include "SettingsWidgets/SettingsPage.h"
#include "CreationWidgets/CreationPage.h"
#include "CreationWidgets/DeleteAll.h"
#include "../OpenDrive/OpenDrive.h"
#include "../OpenDrive/OtherStructures.h"
#include "../OpenDrive/OpenDriveXmlParser.h"
#include "../OpenDrive/OpenDriveXmlWriter.h"
#include "../Osg/OSGMain.h"
#include "ConfigDialogs/ReferencePlaneDialog.h"
#include "ConfigDialogs/SceneryDialog.h"
#include "ToolsDialogs/ConnectRoadsDialog.h"
#include "ToolsDialogs/LoadingDialog.h"

/**
 * Main window class used as a main application window
 */
class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	/**
	 * Constructor, sets the references for the OSG object and OpenDRIVE structure
	 *
	 * @param osgMain Pointer to the OSG object
	 * @param openDrive Pointer to the OpenDrive structure
	 */
	MainWindow(OSGMain *osgMain, OpenDrive *openDrive);

private:
	/**
	 * Menus for the main window menu bar
	 */
	QMenu *mFileMenu;
	QMenu *mHelpMenu;
	QMenu *mToolsMenu;
	QMenu *mOptionsMenu;

	/**
	 * Default application actions
	 */
	QAction *mNewAct;
	QAction *mOpenAct;
	QAction *mSaveAct;
	QAction *mSaveGeometryAct;
	QAction *mExitAct;
	QAction *mAboutAct;
	QAction *mHelpAct;

	/**
	 * Various application settings actions
	 */
	QAction *mChordlineShowHide;
	QAction *mTreeColorCodingShowHide;
	QAction *mDeleteConfirmationToggle;
	QAction *mReferencePlaneShowHide;
	QAction *mSceneryShowHide;
	QAction *mHelpersShowHide;
	QAction *mTakeScreenshotAct;

	/**
	 * Dialog launching actions
	 */
	QAction *mReferencePlaneShowDialog;
	QAction *mSceneryShowDialog;
	QAction *mConnectRoadsShowDialog;
	QAction *mConnectRoadsRunInBgr;

	/**
	 * OSG widget pointer used to store a reference to the 3D viewport widget
	 */
	QOSGWidget *mOSGViewer;

	/**
	 * Two dock widgets used by the main window class for road tree and properties panels
	 */
	QDockWidget *mLeftDock;
	QDockWidget *mRightDock;

	/**
	 * Toolbar widget
	 */
	QToolBar *mMainToolBar;

	/**
	 * Pointers to record properties, record creation, delete button panels
	 */
	SettingsPage *mSettingsPage;
	CreationPage *mCreationPage;
	DeleteAll *mDeleteAll;

	/**
	 * Pointers to grid settings dialog and scenery generation dialog
	 */
	ReferencePlaneDialog *mReferencePlaneDialog;
	SceneryDialog *mSceneryDialog;

	/**
	 * Pointer to road connection dialog
	 */
	ConnectRoadsDialog *mConnectRoadsDialog;

	/**
	 * Pointer to the road tree panel
	 */
	RoadTree *mRoadTree;

	/**
	 * Pointer to OSG object and OpenDrive structure
	 */
	OSGMain *mOsgMain;
	OpenDrive *mOpenDrive;


	/**
	 * Initializes the road tree panel and the record properties panel
	 */
	void initRoadTreeAndSettings();

	/**
	 * Initializes the record creation panel
	 */
	void initCreation();

	/**
	 * Initializes the dock widgets
	 */
	void initDocks();

	/**
	 * Initializes all the actions
	 */
	void initActions();

	/**
	 * Initializes the menu
	 */
	void initMenus();

	/**
	 * Initializes the toolbar and the appropriate tool buttons
	 */
	void initToolbars();

	/**
	 * Initializes the OSG widget and the 3D viewport
	 */
	void initOSG(OSGMain *osgMain);

	/**
	 * Initializes the dialogs
	 * 
	 * @param osgMain OSG object reference
	 */
	void initDialogs(OSGMain *osgMain);

	/**
	 * Loads the default or the last used settings
	 */
	void readSettings();


private slots:
	/**
	 * Clears the structure and starts a new document
	 */
	void newDocument();
	/**
	 * Opens the "about" dialog
	 */
	void about();
	/**
	 * Opens the help file
	 */
	void help();
	/**
	 * Opens an "open file" dialog and parses the selected file
	 */
	void openXML();
	/**
	 * Opens a "save file" dialog and saves the road structure to the selected file
	 */
	void saveXML();
	/**
	 * Opens a "save file" dialog and saves the road geometry to the selected file
	 */
	void saveOSG();
	/**
	 * Shows or hides the chord line
	 */
	void OnChordLineShowHide(bool state);
	/**
	 * Shows or hides the helpers
	 */
	void OnHelpersShowHide(bool state);
	/**
	 * Takes a top-down view screenshot of the whole road network.
	 * The generated screenshot could be used for heightmap generation.
	 */
	void OnTakeScreenshot();

public:

	/**
	 * Parses the given file
	 */
	void openXML(const std::string fileName);

};


#endif
