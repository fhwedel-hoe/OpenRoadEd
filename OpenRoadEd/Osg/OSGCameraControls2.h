#ifndef OSGCAMERACONTROLS2_H
#define OSGCAMERACONTROLS2_H


#include <osg/Matrixd>
#include <osgGA/MatrixManipulator>

/**
 * Free look camera that moves along the ground plane and along the vertical axis.
 * Camera mode is activated when the space button is held down.
 * Rotation: Space + Left mouse button
 * Movement along the ground plane: Space + Right mouse button
 * Movement along the vertical axis: Space + Middle mouse button
 */
class OSGCameraControls2 : public osgGA::MatrixManipulator
{
public:
	/**
	* Constructor
	*/
	OSGCameraControls2(); 
	
	/**
	* Getter and setters for the node used to get the bounding sphere
	* Usually the root node
	*/
	virtual void setNode(osg::Node* node);
	virtual const osg::Node* getNode() const;
	virtual osg::Node* getNode();
	
	/**
	* Home methods (inherited from the matrix manipulator)
	*/
	virtual void home(double /*currentTime*/);
	virtual void home(const osgGA::GUIEventAdapter& ea ,osgGA::GUIActionAdapter& aa);
	virtual void computeHomePosition();
	
	/**
	* Event handler
	*/
	virtual bool handle (const osgGA::GUIEventAdapter&ea, osgGA::GUIActionAdapter&aa);
	
	/**
	* Getter and setter for camera matrix
	*/
	virtual void setByMatrix(const osg::Matrixd& mat);
	virtual void setByInverseMatrix(const osg::Matrixd&mat);
	virtual osg::Matrixd getInverseMatrix() const;
	virtual osg::Matrixd getMatrix() const;

	/**
	* Method to look down
	*/
	virtual void lookDown(const osgGA::GUIEventAdapter& ea ,osgGA::GUIActionAdapter& aa);

protected:
	~OSGCameraControls2();

	/**
	* Calculates the position and rotation with given eye, center and up vectors
	*/
	void computePosition(const osg::Vec3& eye,const osg::Vec3& center,const osg::Vec3& up);

	/**
	* Clears the history of mouse events
	*/
	void flushMouseEvents();

	/**
	* Adds an event to the history of mouse events
	*/
	void addMouseEvent(const osgGA::GUIEventAdapter &ea);
	
	
	/**
	* Calculates mouse movement
	*/
	bool calculateMovement();


	/**
	* History of mouse events
	*/
	osg::ref_ptr<const osgGA::GUIEventAdapter> mMouseEvent1;
	osg::ref_ptr<const osgGA::GUIEventAdapter> mMouseEvent2;
	
	/**
	* Node reference
	*/
	osg::ref_ptr<osg::Node>	mNode;

	/**
	* Camera position, rotation
	*/
	osg::Vec3d	mPosition;
	osg::Quat	mRotation;
	
	/**
	* Scale of the root node
	*/
	double mModelScale;

	/**
	* Flag that is set to true when Space is pressed (activates camera mode)
	*/
	bool mSpaceIsPressed;
};




#endif