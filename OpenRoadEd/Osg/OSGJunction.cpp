#define _USE_MATH_DEFINES

#include "OSGJunction.h"
#include "OSGConstants.h"
#include "OSGRoad.h"
#include <sstream>		//debug (convert double to string)
#include "windows.h"	//debug (OutputDebugString)

#include <osg/Geometry>
#include <osgUtil/DelaunayTriangulator>
#include <osg/Point>
#include <osg/Material>
#include <osg/Texture2D>
#include <osgDB/ReadFile>
#include <osg/Notify>

/**
* Junction geometry generation class.
*
*
*
*
*/

/**
* Empty constructor
*/
OSGJunction::OSGJunction()
{	}


/**
* Draw junction's second layer - wheel tracks.
* @param roads Pointer to the roads vector of the OpenDrive structure
* @param nodeIndex index of the junction in the junction vector
* @param junctionID ID string of the junction
* @param roadsGroup OpenSceneGraph group with all the roads
* @param roadTextureFile Filename (with path) of the texture to be used for the second layer
*/
osg::ref_ptr<osg::PositionAttitudeTransform> OSGJunction::DrawJunction (vector<Road> *roads, int nodeIndex, string junctionId, osg::ref_ptr<osg::Group> roadsGroup,string roadTextureFile)
{
	//create the geode and a geometry node
	osg::ref_ptr<osg::PositionAttitudeTransform> posTransform = new osg::PositionAttitudeTransform();
	osg::ref_ptr<OSGGeodeNode> geode = new OSGGeodeNode();

	geode->SetNodeType(JUNCTION_NODE);
	geode->AddNodeInfoIndex(nodeIndex);

	//roads geometry vector
	std::vector<osg::ref_ptr<osg::Geometry>> junctionRoadGeometries;
	Road * road;
	for (unsigned int i=0; i<roads->size(); i++)
	{
		road = &roads->at(i);
		//if the road is a connecting road of the junction
		if (road->GetRoadJunction().compare(junctionId)==0)
		{
			//make a deep copy of the geode
			osg::ref_ptr<osg::Geometry> tempGeom=new osg::Geometry(*(roadsGroup->getChild(i)->asGeode()->getDrawable(0)->asGeometry()),osg::CopyOp::DEEP_COPY_ALL);

			osg::Image *roadImage = osgDB::readImageFile(roadTextureFile);
			if (!roadImage) 
			{
				osg::notify(osg::WARN) << "Couldn't load texture, loading default image file."  << std::endl;
				roadImage = osgDB::readImageFile("Resources/noTexture.jpg");
				if (!roadImage) 
				{
					osg::notify(osg::WARN) << "Couldn't load texture."  << std::endl;
					return posTransform.get();
				}
			}

			//setup texture properties
			osg::ref_ptr<osg::Texture2D> roadTexture = new osg::Texture2D;
			roadTexture->setDataVariance(osg::Object::DYNAMIC);
			roadTexture->setWrap(osg::Texture::WRAP_S, osg::Texture::REPEAT);
			roadTexture->setWrap(osg::Texture::WRAP_T, osg::Texture::REPEAT);
			roadTexture->setImage(roadImage);

			//setup state set
			osg::StateSet* roadStateSet=tempGeom->getOrCreateStateSet();
			roadStateSet->setTextureAttributeAndModes(0, roadTexture, osg::StateAttribute::ON);
			roadStateSet->setMode(GL_LIGHTING, osg::StateAttribute::ON);
			roadStateSet->setMode(GL_BLEND,osg::StateAttribute::ON); 
			roadStateSet->setMode(GL_DEPTH_TEST,osg::StateAttribute::OFF);

			junctionRoadGeometries.push_back(tempGeom);
		}

	}

	//add the geometries of the roads that form the junction to the junction geode
	for (unsigned int i=0; i < junctionRoadGeometries.size(); i++)
	{
		geode->addDrawable(junctionRoadGeometries.at(i).get());
	}


	osg::Vec3* position=new osg::Vec3(0,0,JUNCTION_ELEVATION_SHIFT);
	posTransform->setPosition( *position );
	posTransform->addChild(geode.get());



	return posTransform.get();
}
