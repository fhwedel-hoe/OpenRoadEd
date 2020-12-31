#ifndef GETROADDIALOG_H
#define GETROADDIALOG_H


#include <QWidget>
#include <QDialog> 
#include <QtWidgets>
#include <QtCore/QSettings>
#include "../../OpenDrive/OpenDrive.h"

/**
 * Dialog used for selecting a road from a list
 *
 */
class GetRoadDialog : public QDialog
{
	Q_OBJECT
public:
	/**
	 * Constructor
	 * Initializes the widgets that make up the interface
	 *
	 * @param openDrive Pointer to openDrive structure
	 */
	GetRoadDialog(OpenDrive *openDrive);

	/**
	 * Returns the road ID
	 */
	string ReturnRoadId();

	/**
	 * Returns the road index in the OpenDrive structure
	 */
	unsigned int ReturnRoadIndex();
private:
	/**
	 * Reference to the OpenDrive structure
	 */
	OpenDrive *mOpenDrive;

	/**
	 * Reference to the selected road
	 */
	Road *mSelectedRoad;

	/**
	 * Index of the selected road
	 */
	unsigned int mSelectedIndex;

	/**
	 * Widgets used in the dialog
	 */
	QGroupBox *mRoadsGroup;
	QListWidget *mRoadList;


private slots:

	/**
	 * Closes the dialog
	 */
	void OkPressed();
	void CancelPressed();

	/**
	 * Executed when the user selects a road
	 */
	void RoadSelected();
	void RoadDoubleClicked();
	
};


#endif
