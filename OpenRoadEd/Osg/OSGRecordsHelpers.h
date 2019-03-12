#ifndef OSGRECORDSHELPERS_H
#define OSGRECORDSHELPERS_H

#include "OSGObjectNode.h"
#include "../OpenDrive/Road.h"
/**
* Records helpers class. Used to generate the geometry (billboards and other glyphs) to display the position and orientation of the various road records
*
*
*
*
*/
class OSGRecordsHelpers
{
private:
	Road* mRoad;

	osg::ref_ptr<osg::Geometry> mBillboard;

	//these are shared between all the arrows
	osg::ref_ptr<osg::Vec3Array>mArrowVertices;
	osg::ref_ptr<osg::DrawElementsUInt> mArrowTris;

	double mSize;
	double mOffset;
	double mVerticalOffset;

	/**
	* Create a billboard node
	*/
	void CreateBillboard();

	/**
	* Create an arrow 
	*/
	void CreateArrow();

	/**
	* Create the geometry for a helper and return the matrix transform that translates the helper according to its type
	* @param s s-offset of the record helpers along the road
	* @param offsetX Translation in the x direction
	* @param offsetZ Translation in the vertical direction. Used for lane records in order to allow multiple lane parameters to be displayed simultaneously
	* @param type Type of the helper to be created (based on the record type)
	* @param iconName Filename (with path) of the icon to be rendered on the billboard
	* @param color Color of the glyph. Used to distinguish between the left and right lane records
	*/
	osg::ref_ptr<osg::MatrixTransform> AddRecordHelper(double s, double offsetX,double offsetZ, OSGNodeType type, std::string iconName, osg::Vec4* color=NULL);
public:
	OSGRecordsHelpers();

	/**
	* Create all the record helpers for a road
	* @param road Pointer to an OpenDrive road object
	* @param roadIndex of the road from the roads vector
	* @param recordsHelpersGroup A OpenSceneGraph group where all the records for the current road should be added
	*/
	void FillHelperGroups (Road *road, unsigned int roadIndex, osg::Group* recordsHelpersGroup);
};

#endif