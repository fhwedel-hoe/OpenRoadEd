#include "OSGCameraControls2.h"

// Constructor and Destructor
OSGCameraControls2::OSGCameraControls2()
{
	mSpaceIsPressed=false;
}
OSGCameraControls2::~OSGCameraControls2()
{}

/**
* Getter and setters for the node used to get the bounding sphere
* Usually the root node
*/
void OSGCameraControls2::setNode(osg::Node* node)
{
	mNode = node;
	if (mNode.get())
	{
		const osg::BoundingSphere& boundingSphere=mNode->getBound();
		mModelScale = boundingSphere._radius;
	}
	if (getAutoComputeHomePosition()) computeHomePosition();
}
const osg::Node* OSGCameraControls2::getNode() const
{
	return mNode.get();
}
osg::Node* OSGCameraControls2::getNode()
{
	return mNode.get();
}

/**
* Home methods (inherited from the matrix manipulator)
*/
void OSGCameraControls2::home(double /*currentTime*/)
{
	if (getAutoComputeHomePosition()) computeHomePosition();
	computePosition(_homeEye, _homeCenter, _homeUp);
}
void OSGCameraControls2::home(const osgGA::GUIEventAdapter& ea ,osgGA::GUIActionAdapter& aa)
{
	home(ea.getTime());
	aa.requestRedraw();
	aa.requestContinuousUpdate(false);
}
void OSGCameraControls2::computeHomePosition()
{
	if(getNode())
	{
		const osg::BoundingSphere& boundingSphere=getNode()->getBound();

		double radius = boundingSphere._radius;
		if(radius < 1) radius = 100;

		// Gets the home position as a top-down view on the entire road network (using it's bounding box)
		setHomePosition(boundingSphere._center+osg::Vec3( 0.0,0.0,3.5f * radius),
                                boundingSphere._center,
                                osg::Vec3(0.0f,0.0f,1.0f),
                                _autoComputeHomePosition);
	}
}

/**
* Look straight down
*/
void OSGCameraControls2::lookDown(const osgGA::GUIEventAdapter& ea ,osgGA::GUIActionAdapter& aa)
{
	mRotation = osg::Matrixd::lookAt(osg::Vec3(0,0,0),osg::Vec3(0,0,-1),osg::Vec3(0,0,1)).getRotate().inverse();
}


/**
* Event handler
*/
bool OSGCameraControls2::handle(const osgGA::GUIEventAdapter &ea, osgGA::GUIActionAdapter &aa)
{
	switch(ea.getEventType())
	{
	case(osgGA::GUIEventAdapter::KEYDOWN):
		// Listens for space key down to set the mSpaceIsDown flag
		if (ea.getKey()== osgGA::GUIEventAdapter::KEY_Space)
		{
			mSpaceIsPressed=true;
		}
		// If H or h key is pressed while space is down - reset position to home position
		if ((ea.getKey()== 'h' || ea.getKey()== 'H') && mSpaceIsPressed)
		{
			home(ea,aa);
			return true;
		}
		// If G or g key is pressed while space is down - look straight down
		if ((ea.getKey()== 'g' || ea.getKey()== 'G') && mSpaceIsPressed)
		{
			lookDown(ea,aa);
			return true;
		}
		return false;
	case(osgGA::GUIEventAdapter::KEYUP):
		// Resets the mSpaceIsDown flag
		if (ea.getKey()== osgGA::GUIEventAdapter::KEY_Space)
		{
			mSpaceIsPressed=false;
		}
		return false;
	case(osgGA::GUIEventAdapter::PUSH):
		{
			flushMouseEvents();
			addMouseEvent(ea);
			// if (calcMovement()) us.requestRedraw();
			aa.requestContinuousUpdate(false);
			return true;
		}
	case(osgGA::GUIEventAdapter::DRAG):
		{
			addMouseEvent(ea);
			if (calculateMovement()) aa.requestRedraw();
			aa.requestContinuousUpdate(false);
			return true;
		}
	default:
		return false;
	}
}

/**
* Computes the position given eye,center and up vectors
*/
void OSGCameraControls2::computePosition(const osg::Vec3& eye,const osg::Vec3& center,const osg::Vec3& up)
{
	osg::Vec3 lv(center-eye);

	osg::Matrix rotation_matrix = osg::Matrixd::lookAt(eye,center,up);

	mPosition = center-lv;
	mRotation = rotation_matrix.getRotate().inverse();
}

/**
* Flushh mouse event history
*/
void OSGCameraControls2::flushMouseEvents()
{
	mMouseEvent1=NULL;
	mMouseEvent2=NULL;
}
/**
* Add event to mouse event history
*/
void OSGCameraControls2::addMouseEvent(const osgGA::GUIEventAdapter &ea)
{
	mMouseEvent1=mMouseEvent2;
	mMouseEvent2=&ea;
}
/**
* Calculate mouse movement
*/
bool OSGCameraControls2::calculateMovement()
{
	// return if less then two events have been added.
	if (mMouseEvent1.get()==NULL || mMouseEvent2.get()==NULL) return false;

	double dx = mMouseEvent1->getXnormalized()-mMouseEvent2->getXnormalized();
	double dy = mMouseEvent1->getYnormalized()-mMouseEvent2->getYnormalized();


	// return if there is no movement.
	if (dx==0 && dy==0) return false;

	unsigned int buttonMask = mMouseEvent2->getButtonMask();
	// Rotation
	if (mSpaceIsPressed && buttonMask==osgGA::GUIEventAdapter::LEFT_MOUSE_BUTTON)
	{

		double scale = 0.8;

		osg::Matrix rotation_matrix;
		rotation_matrix.makeRotate(mRotation);
		osg::Vec3d sideVector = getSideVector(rotation_matrix);

		osg::Vec3d localUp(0,0,1);

		osg::Quat rotate_elevation;
		rotate_elevation.makeRotate(-dy*scale,sideVector);

		osg::Quat rotate_azim;
		rotate_azim.makeRotate(dx*scale,localUp);

		mRotation = mRotation * rotate_elevation * rotate_azim;

		return true;

	}
	// Movement and rotation
	else if (mSpaceIsPressed && (buttonMask==(osgGA::GUIEventAdapter::LEFT_MOUSE_BUTTON|osgGA::GUIEventAdapter::RIGHT_MOUSE_BUTTON)))
	{

		osg::CoordinateFrame coordinateFrame = getCoordinateFrame(mPosition);
		double height = coordinateFrame.getTrans().z();
		double scaleMov = 80+height*2;
		double scaleRot = 0.8;

		osg::Matrix rotation_matrix;
		rotation_matrix.makeRotate(mRotation);
		osg::Vec3d sideVector = getSideVector(rotation_matrix);
		osg::Vec3d localUp(0,0,1);

		osg::Quat rotate_azim;
		rotate_azim.makeRotate(dx*scaleRot,localUp);

		// ROTATE
		mRotation = mRotation * rotate_azim;

		rotation_matrix.makeRotate(mRotation);
		sideVector = getSideVector(rotation_matrix);
		osg::Vec3d forwardVector =localUp^sideVector;

		osg::Vec3d dv = forwardVector * (dy*scaleMov);

		// MOVE
		mPosition -= dv;

		return true;
	}
	// Movement along vertical axis
	else if (mSpaceIsPressed && (buttonMask==osgGA::GUIEventAdapter::MIDDLE_MOUSE_BUTTON))
	{

		// pan XZ.

		osg::CoordinateFrame coordinateFrame = getCoordinateFrame(mPosition);
		double height = coordinateFrame.getTrans().z();

		double scale = 80+height*2;

		osg::Matrixd rotation_matrix;
		rotation_matrix.makeRotate(mRotation);
		osg::Vec3d sideVector = getSideVector(rotation_matrix);

		osg::Vec3d localUp(0,0,1);

		osg::Vec3d forwardVector =localUp^sideVector;

		osg::Vec3d dv = localUp * (dy*scale);// + sideVector * (dx*scale);

		mPosition -= dv;

		return true;
	}
	// Movement along the ground plane
	else if (mSpaceIsPressed && buttonMask==osgGA::GUIEventAdapter::RIGHT_MOUSE_BUTTON)
	{

		// pan XY
		osg::CoordinateFrame coordinateFrame = getCoordinateFrame(mPosition);
		double height = coordinateFrame.getTrans().z();

		double scale = 80+height*2;

		osg::Matrixd rotation_matrix;
		rotation_matrix.makeRotate(mRotation);
		osg::Vec3d sideVector = getSideVector(rotation_matrix);
		
		osg::Vec3d localUp(0,0,1);

		osg::Vec3d forwardVector =localUp^sideVector;

		osg::Vec3d dv = forwardVector * (dy*scale) + sideVector * (dx*scale);

		mPosition -= dv;

		return true;

	}

	return false;
}

/**
* Sets the position given a matrix
*/
void OSGCameraControls2::setByMatrix(const osg::Matrixd& matrix) 
{
	mRotation = matrix.getRotate();
	mPosition = matrix.getTrans();
}
/**
* Sets the position given an inverse matrix
*/
void OSGCameraControls2::setByInverseMatrix(const osg::Matrixd& matrix) 
{

}
/**
* Gets the matrix
*/
osg::Matrixd OSGCameraControls2::getMatrix() const
{
	return osg::Matrixd::rotate(mRotation)*osg::Matrixd::translate(mPosition);
}
/**
* Gets the inverse matrix
*/
osg::Matrixd OSGCameraControls2::getInverseMatrix() const
{
	return osg::Matrixd::translate(-mPosition)*osg::Matrixd::rotate(mRotation.inverse());
}
