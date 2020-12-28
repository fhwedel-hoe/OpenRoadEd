#ifndef CREATIONPAGE_H
#define CREATIONPAGE_H


#include <QtWidgets>
#include <QtGui/QtGui>

#include "../../OpenDrive/OpenDrive.h"
#include "../Tree/RoadTree.h"
#include "../../Osg/OSGMain.h"

#include "CreationAllRoad.h"
#include "CreationAllJunction.h"

/**
 * Class that holds the tabbed panels and the creation groups
 *
 */
class CreationPage : public QWidget
{
	Q_OBJECT
public:
	/**
	 * Initializes the creation panel
	 */
	CreationPage(QWidget *parent = 0);

	/**
	 * Saves the references to the OpenDrive, road tree and OSG object
	 */
	void Init(OpenDrive *openDrive, RoadTree *roadTree, OSGMain *osgMain);

private:
	/**
	 * Pointers to the openDrive, road tree and OSG objects
	 */
	OpenDrive* mOpenDrive;
	RoadTree* mRoadTree;
	OSGMain* mOsgMain;

	/**
	 * Interface widgets
	 */
	QTabWidget *mTabWidget;

	CreationAllRoad *mCreationAllRoad;
	CreationAllJunction *mCreationAllJunction;

public slots:
	/**
	 * Method called when something is selected in the road tree
	 */
	void SomethingSelected();

	/**
	 * Method called when road critical changes are made that require
	 * a road redraw
	 */
	void OnRoadGeometryChanged(bool geometryChanged=false);

signals:
	/**
	 * Signal emitted when critical road items are created
	 * that require that the road to be redrawn
	 */
	void CurrentRoadChanged(bool geometryChanged);
	
};

#endif
