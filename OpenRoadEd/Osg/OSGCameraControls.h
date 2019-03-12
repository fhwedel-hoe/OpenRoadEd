#ifndef OSGCAMERACONTROLS_H
#define OSGCAMERACONTROLS_H


//#include <osg/Matrixd>
////#include <osgViewer/ViewerEventHandlers>
//#include <osgGA/MatrixManipulator>
//
//
//class OSGCameraControls : public osgGA::MatrixManipulator
//{
////========== METHODS ============//
//public:
//	OSGCameraControls(); 
//	// Default getter and setter for the target node
//	virtual void setNode(osg::Node* node);
//	virtual const osg::Node* getNode() const;
//	virtual osg::Node* getNode();
//	// Default home methods
//	virtual void home(double /*currentTime*/);
//	virtual void home(const osgGA::GUIEventAdapter& ea ,osgGA::GUIActionAdapter& aa);
//	// Default event handler
//	virtual bool handle (const osgGA::GUIEventAdapter&ea, osgGA::GUIActionAdapter&aa);
//	// Default getter and setter for transformation matrix
//	virtual void setByMatrix(const osg::Matrixd& mat);
//	virtual void setByInverseMatrix(const osg::Matrixd&mat);
//	virtual osg::Matrixd getInverseMatrix() const;
//	virtual osg::Matrixd getMatrix() const;
//
//protected:
//	~OSGCameraControls();
//
//	// Calculates the position and rotation with given eye, center and up vectors
//	void computePosition(const osg::Vec3& eye,const osg::Vec3& center,const osg::Vec3& up);
//	// Clears the history of mouse events
//	void flushMouseEvents();
//	// Adds an event to the history of mouse events
//	void addMouseEvent(const osgGA::GUIEventAdapter &ea);
//	// Calculate mouse movement
//	bool calculateMovement();
//
//
////========== VARIABLES ============//
//	// History of mouse events
//	osg::ref_ptr<const osgGA::GUIEventAdapter> mMouseEvent1;
//	osg::ref_ptr<const osgGA::GUIEventAdapter> mMouseEvent2;
//	// Node reference
//	osg::ref_ptr<osg::Node>	mNode;
//	// Camera position, rotation, distance from target
//	osg::Vec3d	mCenter;
//	osg::Quat	mRotation;
//	double		mDistance;
//	// Scale of the root node
//	double mModelScale;
//	// SpaceIsPressed flag
//	bool mSpaceIsPressed;
//};




#endif