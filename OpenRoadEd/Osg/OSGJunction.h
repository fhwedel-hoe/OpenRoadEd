#ifndef OSGJUNCTION_H
#define OSGJUNCTION_H

#include <osg/PositionAttitudeTransform>
#include "OSGObjectNode.h"
#include "../OpenDrive/Road.h"
using std::string;


/**
 * Junction geometry generation class.
 *
 *
 *
 *
 */
class OSGJunction
{
public:
	/**
	* Empty constructor
	*/
	OSGJunction();

	/**
	* Draw junction's second layer - wheel tracks.
	* @param roads Pointer to the roads vector of the OpenDrive structure
	* @param nodeIndex index of the junction in the junction vector
	* @param junctionID ID string of the junction
	* @param roadsGroup OpenSceneGraph group with all the roads
	* @param roadTextureFile Filename (with path) of the texture to be used for the second layer
	*/
	osg::ref_ptr<osg::PositionAttitudeTransform> DrawJunction (vector<Road> *roads, int nodeIndex, string junctionId, osg::ref_ptr<osg::Group> roadsGroup,string roadTextureFile);
};


#endif