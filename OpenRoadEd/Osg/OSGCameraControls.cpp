#include "OSGCameraControls.h"

//// Constructor and Destructor
//OSGCameraControls::OSGCameraControls()
//{
//	mSpaceIsPressed=false;
//}
//OSGCameraControls::~OSGCameraControls()
//{}
//
///**
//* Sets the target node
//*/
//void OSGCameraControls::setNode(osg::Node* node)
//{
//	mNode = node;
//	if (mNode.get())
//	{
//		const osg::BoundingSphere& boundingSphere=mNode->getBound();
//		mModelScale = boundingSphere._radius;
//	}
//	if (getAutoComputeHomePosition()) computeHomePosition();
//}
//
///**
//* Gets the constant target node
//*/
//const osg::Node* OSGCameraControls::getNode() const
//{
//	return mNode.get();
//}
//
///**
//* Gets the target node
//*/
//osg::Node* OSGCameraControls::getNode()
//{
//	return mNode.get();
//}
//
///**
//* Goes to the home position
//*/
//void OSGCameraControls::home(double /*currentTime*/)
//{
//	if (getAutoComputeHomePosition()) computeHomePosition();
//	computePosition(_homeEye, _homeCenter, _homeUp);
//}
//
///**
//* Goes to the home position
//*/
//void OSGCameraControls::home(const osgGA::GUIEventAdapter& ea ,osgGA::GUIActionAdapter& aa)
//{
//	home(ea.getTime());
//	aa.requestRedraw();
//	aa.requestContinuousUpdate(false);
//}
//
///**
//* Event handler
//*/
//bool OSGCameraControls::handle(const osgGA::GUIEventAdapter &ea, osgGA::GUIActionAdapter &aa)
//{
//	switch(ea.getEventType())
//	{
//	case(osgGA::GUIEventAdapter::KEYDOWN):
//		// Listens for space key down to set the mSpaceIsDown flag
//		if (ea.getKey()== osgGA::GUIEventAdapter::KEY_Space)
//		{
//			mSpaceIsPressed=true;
//		}
//		// If H or h key is pressed while space is down - reset position to home position
//		if ((ea.getKey()== 'h' || ea.getKey()== 'H') && mSpaceIsPressed)
//		{
//			home(ea,aa);
//			return true;
//		}
//		return false;
//	case(osgGA::GUIEventAdapter::KEYUP):
//		// Resets the mSpaceIsDown flag
//		if (ea.getKey()== osgGA::GUIEventAdapter::KEY_Space)
//		{
//			mSpaceIsPressed=false;
//		}
//		return false;
//	case(osgGA::GUIEventAdapter::PUSH):
//		{
//			flushMouseEvents();
//			addMouseEvent(ea);
//			// if (calcMovement()) us.requestRedraw();
//			aa.requestContinuousUpdate(false);
//			return true;
//		}
//	case(osgGA::GUIEventAdapter::DRAG):
//		{
//			addMouseEvent(ea);
//			if (calculateMovement()) aa.requestRedraw();
//			aa.requestContinuousUpdate(false);
//			return true;
//		}
//	default:
//		return false;
//	}
//}
//
///**
//* Computes the position given eye,center and up vectors
//*/
//void OSGCameraControls::computePosition(const osg::Vec3& eye,const osg::Vec3& center,const osg::Vec3& up)
//{
//	osg::Vec3 lv(center-eye);
//
//	osg::Matrix rotation_matrix = osg::Matrixd::lookAt(eye,center,up);
//
//	mCenter = center;
//	mDistance = lv.length();
//	mRotation = rotation_matrix.getRotate().inverse();
//}
//
///**
//* Flushh mouse event history
//*/
//void OSGCameraControls::flushMouseEvents()
//{
//	mMouseEvent1=NULL;
//	mMouseEvent2=NULL;
//}
///**
//* Add event to mouse event history
//*/
//void OSGCameraControls::addMouseEvent(const osgGA::GUIEventAdapter &ea)
//{
//	mMouseEvent1=mMouseEvent2;
//	mMouseEvent2=&ea;
//}
///**
//* Calculate mouse movement
//*/
//bool OSGCameraControls::calculateMovement()
//{
//	// return if less then two events have been added.
//	if (mMouseEvent1.get()==NULL || mMouseEvent2.get()==NULL) return false;
//
//	double dx = mMouseEvent1->getXnormalized()-mMouseEvent2->getXnormalized();
//	double dy = mMouseEvent1->getYnormalized()-mMouseEvent2->getYnormalized();
//
//
//	// return if there is no movement.
//	if (dx==0 && dy==0) return false;
//
//	unsigned int buttonMask = mMouseEvent2->getButtonMask();
//	if (mSpaceIsPressed && ((buttonMask==osgGA::GUIEventAdapter::MIDDLE_MOUSE_BUTTON) || (buttonMask==(osgGA::GUIEventAdapter::LEFT_MOUSE_BUTTON|osgGA::GUIEventAdapter::RIGHT_MOUSE_BUTTON))))
//	{
//
//		// pan model.
//		double scale = 0.3f*mDistance;
//
//		osg::Matrixd rotation_matrix;
//		rotation_matrix.makeRotate(mRotation);
//		osg::Vec3d sideVector = getSideVector(rotation_matrix);
//
//		// Var1
//		//osg::CoordinateFrame coordinateFrame = getCoordinateFrame(mCenter);
//		//osg::Vec3d localUp = getUpVector(coordinateFrame);
//		// Var2
//		//osg::Matrix position_matrix;
//		//position_matrix.makeTranslate(mCenter);
//		//osg::Vec3d localUp = getUpVector(position_matrix);
//		// Var3
//		osg::Vec3d localUp(0,0,1);
//
//		osg::Vec3d forwardVector =localUp^sideVector;
//		//sideVector = forwardVector^localUp;
//
//		//forwardVector.normalize();
//		//sideVector.normalize();
//
//		osg::Vec3d dv = forwardVector * (dy*scale) + sideVector * (dx*scale);
//
//		mCenter += dv;
//
//		return true;
//	}
//	else if (mSpaceIsPressed && buttonMask==osgGA::GUIEventAdapter::RIGHT_MOUSE_BUTTON)
//	{
//
//		// zoom model.
//		double scale = 1.0f+dy;
//		mDistance *= scale;
//		return true;
//
//	}
//	else if (mSpaceIsPressed && buttonMask==osgGA::GUIEventAdapter::LEFT_MOUSE_BUTTON)
//	{
//
//		osg::Matrix rotation_matrix;
//		rotation_matrix.makeRotate(mRotation);
//		osg::Vec3d sideVector = getSideVector(rotation_matrix);
//
//		// Var1
//		//osg::CoordinateFrame coordinateFrame = getCoordinateFrame(mCenter);
//		//osg::Vec3d localUp = getUpVector(coordinateFrame);
//		// Var2
//		//osg::Matrix position_matrix;
//		//position_matrix.makeTranslate(mCenter);
//		//osg::Vec3d localUp = getUpVector(position_matrix);
//		// Var3
//		osg::Vec3d localUp(0,0,1);
//
//		//osg::Vec3d forwardVector = localUp^sideVector;
//		//sideVector = forwardVector^localUp;
//
//		//forwardVector.normalize();
//		//sideVector.normalize();
//
//		osg::Quat rotate_elevation;
//		rotate_elevation.makeRotate(-dy,sideVector);
//
//		osg::Quat rotate_azim;
//		rotate_azim.makeRotate(-dx,localUp);
//
//		mRotation = mRotation * rotate_elevation * rotate_azim;
//
//		return true;
//
//	}
//
//	return false;
//}
//
///**
//* Sets the position given a matrix
//*/
//void OSGCameraControls::setByMatrix(const osg::Matrixd& matrix) 
//{
//	mCenter = osg::Vec3(0.0f,0.0f,-mDistance)*matrix;
//	mRotation = matrix.getRotate();
//}
///**
//* Sets the position given an inverse matrix
//*/
//void OSGCameraControls::setByInverseMatrix(const osg::Matrixd& matrix) 
//{
//
//}
///**
//* Gets the matrix
//*/
//osg::Matrixd OSGCameraControls::getMatrix() const
//{
//	return osg::Matrixd::translate(0.0,0.0,mDistance)*osg::Matrixd::rotate(mRotation)*osg::Matrixd::translate(mCenter);
//}
///**
//* Gets the inverse matrix
//*/
//osg::Matrixd OSGCameraControls::getInverseMatrix() const
//{
//	return osg::Matrixd::translate(-mCenter)*osg::Matrixd::rotate(mRotation.inverse())*osg::Matrixd::translate(0.0,0.0,-mDistance);
//}
