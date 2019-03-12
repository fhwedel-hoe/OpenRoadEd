#ifndef CREATIONALLJUNCTION_H
#define CREATIONALLJUNCTION_H


#include <QtGui/QWidget>
#include <QtGui/QtGui>

#include "../../OpenDrive/OpenDrive.h"
#include "../../OpenDrive/RoadGeometry.h"
#include "../Tree/RoadTree.h"

/**
 * Class that holds all the buttons used to create junction related records
 *
 */
class CreationAllJunction : public QWidget
{
	Q_OBJECT
public:
	/**
	 * Initializes the creation panel
	 */
	CreationAllJunction(QWidget *parent = 0);

	/**
	 * Saves the references to the OpenDrive object and road tree widget
	 */
	void Init(OpenDrive *openDrive, RoadTree *roadTree);

	/**
	 * Enables or disables groups of buttons when they cannot be used
	 * due to an unrelated item selected in the road tree
	 * 
	 * @param wholeGroup Disable the whole group or just a part
	 * @param junctionItems Disable junction item buttons
	 * @param laneLink Disable just the laneLink button
	 */
	void SetEnabled(bool wholeGroup, bool junctionItems=false, bool laneLink=false);
private:
	/**
	 * Pointers to the openDrive and road tree objects
	 */
	OpenDrive *mOpenDrive;
	RoadTree *mRoadTree;

	/**
	 * Interface widgets
	 */
	QPushButton *mCreateJunction;

	QToolButton *mCreateJunctionConnection;
	QToolButton *mCreateJunctionLaneLink;
	QToolButton *mCreateJunctionPriority;
	QToolButton *mCreateJunctionController;

signals:
	/**
	 * Signal emitted when critical road items are created
	 * that require that the road to be redrawn
	 */
	void RoadChanged(bool recalculateRoad);

public slots:

	/**
	 * Methods called when one of the creation buttons is pressed
	 */
	void CreateJunctionPressed();
	void CreateJunctionConnectionPressed();
	void CreateJunctionLaneLinkPressed();
	void CreateJunctionPriorityPressed();
	void CreateJunctionControllerPressed();

};

#endif