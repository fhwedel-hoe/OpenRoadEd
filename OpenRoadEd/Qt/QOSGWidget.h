#ifndef QOSGWIDGET_H
#define QOSGWIDGET_H

#include <QtCore/QTimer>
#include <QtGui/QWidget>
#include <QtGui/QMouseEvent>
using Qt::WindowFlags;

#include "Tree/RoadTree.h"
#include "../Osg/OSGMain.h"

/**
 * OSG widget class used as a 3D viewport
 *
 *
 *
 *
 */
class QOSGWidget : public QWidget
{
	Q_OBJECT

public:
	/**
	 * Constructor, sets the references for the OSG object
	 *
	 * @param osgMain Pointer to the OSG object
	 * @param parent Parent widget
	 * @param name Name of the widget
	 * @param f Windows flags, NULL for default flags
	 */
	QOSGWidget(OSGMain *osgMain, QWidget *parent = 0, const char * name = 0, WindowFlags f = 0);

	/**
	 * Initializes the OSG widget
	 *
	 * @param roadTree Reference to the road tree panel
	 */
	void Init(RoadTree *roadTree);

	void resizeEvent(QResizeEvent* event);

	/**
	 * Paint event, used to redraw the widget
	 *
	 * @param e Event object
	 */
	virtual void paintEvent(QPaintEvent *e);

protected:

	/**
	 * Mouse events
	 */
	virtual void mousePressEvent(QMouseEvent *e);
	virtual void mouseReleaseEvent(QMouseEvent *e);
	
	/**
	 * Keyboard events
	 */
	virtual void keyPressEvent(QKeyEvent *e);
	virtual void keyReleaseEvent(QKeyEvent *e);

private:

	/**
	 * Timer used to redraw the 3D viewport
	 */
	QTimer _timer;

	/**
	 * Pointer to road tree panel
	 */
	RoadTree *mRoadTree;

	/**
	 * Pointer to OSG object
	 */
	OSGMain *mOsgMain;

	/**
	 * Flag to determine if "Camera mode" button is down
	 */
	bool mSpaceIsDown;

	/**
	 * Prevent flicker on Windows Qt
	 */
	QPaintEngine* paintEngine () const { return 0; }

	/**
	 * Picks the node under the mouse cursor and selects the coresponding object in road tree
	 *
	 * @param e Mouse event
	 */
	void Pick(QMouseEvent *e);

private slots:
	/**
	 * Method called when a record is selected in the road tree panel
	 * Used to highlight the coresponding object in 3D viewport
	 */
	void SomethingSelected();

	/**
	 * Method called when the road is recalculated
	 * Used to regenerate the geometry and helpers
	 *
	 * @param index Index of the road that is recalculated
	 */
	void OnRoadRecalculated(unsigned int index);
};


#endif
