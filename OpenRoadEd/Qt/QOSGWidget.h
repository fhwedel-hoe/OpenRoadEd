#ifndef QOSGWIDGET_H
#define QOSGWIDGET_H

#include <QtWidgets>
#include <QtGui/QMouseEvent>
#include <osgQOpenGL/osgQOpenGLWidget>

#include "Tree/RoadTree.h"
#include "../Osg/OSGMain.h"

/**
 * OSG widget class used as a 3D viewport.
 *
 * Embeds OpenSceneGraph via osgQOpenGLWidget (from the osgQt submodule), which owns
 * the OpenGL context/viewer and forwards Qt's own key/mouse events into OSG's event
 * queue. This is what makes the custom camera manipulator's Space+mouse navigation
 * actually receive events, regardless of window manager/focus quirks.
 */
class QOSGWidget : public osgQOpenGLWidget
{
	Q_OBJECT

public:
	/**
	 * Constructor, sets the references for the OSG object
	 *
	 * @param osgMain Pointer to the OSG object
	 * @param parent Parent widget
	 */
	QOSGWidget(OSGMain *osgMain, QWidget *parent = nullptr);

	/**
	 * Initializes the OSG widget
	 *
	 * @param roadTree Reference to the road tree panel
	 */
	void Init(RoadTree *roadTree);

protected:

	/**
	 * Mouse events. Picks (when not navigating), then forwards to OSG.
	 */
	virtual void mousePressEvent(QMouseEvent *e) override;

	/**
	 * Keyboard events. Tracks the "Camera mode" flag, then forwards to OSG.
	 */
	virtual void keyPressEvent(QKeyEvent *e) override;
	virtual void keyReleaseEvent(QKeyEvent *e) override;

private:

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
