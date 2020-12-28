#ifndef DELETEALL_H
#define DELETEALL_H


#include <QtWidgets>
#include <QtGui/QtGui>
#include <QtCore/QSettings>

#include "../../OpenDrive/OpenDrive.h"
#include "../../OpenDrive/RoadGeometry.h"
#include "../../Osg/OSGMain.h"
#include "../Tree/RoadTree.h"

/**
 * Class that holds the buttons used to delete any type of record
 *
 */
class DeleteAll : public QWidget
{
	Q_OBJECT
public:
	/**
	 * Initializes the creation panel
	 */
	DeleteAll(QWidget *parent = 0);

	/**
	 * Saves the references to the OpenDrive, road tree and OSG object
	 */
	void Init(OpenDrive *openDrive, RoadTree *roadTree, OSGMain *osgMain);
private:
	/**
	 * Pointers to the openDrive, road tree and OSG objects
	 */
	OpenDrive *mOpenDrive;
	RoadTree *mRoadTree;
	OSGMain *mOsgMain;

	/**
	 * Interface widgets
	 */
	QPushButton *mDelete;
	bool mDeleteConfirmation;

	
public slots:
	/**
	 * Method called when delete buttons is pressed
	 */
	void DeletePressed();

	/**
	 * Methods used to toggle delete confirmations on or off
	 */
	void ToggleDeleteConfirmation(bool state);
signals:

	/**
	 * Signal emitted when critical road items are deleted
	 * that require that the road to be redrawn
	 */
	void RoadChanged(bool recalculateRoad);
};

#endif
