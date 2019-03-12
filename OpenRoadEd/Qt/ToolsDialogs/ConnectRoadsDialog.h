#ifndef CONNECTROADSDIALOG_H
#define CONNECTROADSDIALOG_H


#include <QtGui/QDialog>
#include <QtCore/QSettings>
#include "../../OpenDrive/OpenDrive.h"
#include "../Tree/RoadTree.h"
#include "GetRoadDialog.h"


/**
 * Connect roads dialog
 * Used to move one roads to connect it with another road
 *
 */
class ConnectRoadsDialog : public QDialog
{
	Q_OBJECT
public:
	/**
	 * Constructor
	 * Initializes the widgets that make up the interface
	 *
	 * @param openDrive Pointer to openDrive structure
	 * @param roadTree Pointer to road tree panel
	 */
	ConnectRoadsDialog(OpenDrive *openDrive, RoadTree *roadTree);
private:
	/**
	 * References to the openDrive and road tree objects
	 */
	OpenDrive *mOpenDrive;
	RoadTree *mRoadTree;

	/**
	 * Widgets used in the dialog
	 */
	QLineEdit *mRoad1;
	QToolButton *mBrowseRoad1;
	QToolButton *mSelectRoad1;
	QComboBox *mRoad1ContactPoint;

	QLineEdit *mRoad2;
	QToolButton *mBrowseRoad2;	
	QToolButton *mSelectRoad2;
	QComboBox *mRoad2ContactPoint;

	QRadioButton *mMoveRoad1;
	QRadioButton *mMoveRoad2;


	/**
	 * Ids of the selected roads
	 */
	unsigned int mRoad1Index;
	unsigned int mRoad2Index;

	/**
	 * Phase of the selection
	 */
	short mSelectionStage;

	/**
	 * Clears the parameters
	 */
	void Clear();

	/**
	 * Connects the roads
	 */
	void ConnectRoads();

signals:
	/**
	 * Signal emitted when roads are connected to tell teh rendering engine to redraw
	 */
	void RoadChanged(unsigned int roadToRedraw);


private slots:

	/**
	 * Launches the dialog
	 */
	void Run();

	/**
	 * Shows a list of roads for the user to select
	 */
	void BrowseForRoad1();
	void BrowseForRoad2();

	/**
	 * Hides the dialog and waits for the user to select the road
	 * in the road tree or 3D viewport
	 */
	void SelectRoad1();
	void SelectRoad2();

	/**
	 * Closes the dialog
	 */
	void OkPressed();
	void CancelPressed();

	/**
	 * Executed when the user selects a road
	 */
	void RoadSelected();
	
};


#endif