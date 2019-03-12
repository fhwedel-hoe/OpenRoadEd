#ifndef OSGROAD_H
#define OSGROAD_H

#include <vector>
#include <osg/Version>
#include <osg/Node>
#include <osg/Geode>

#include "../OpenDrive/Road.h"
#include "OSGObjectNode.h"


/**
* A helper struct, used to simplify and reduce the parameters of the AddVertices method
*
*
*
*
*/
struct OSGGeometryArrays
{
	osg::ref_ptr<osg::Vec3Array> mVertices; 
	osg::ref_ptr<osg::Vec3Array> mNormals; 
	osg::ref_ptr<osg::Vec4Array> mColors;
	osg::ref_ptr<osg::Vec2Array> mTexCoords;
	osg::ref_ptr<osg::DrawElementsUInt> mTriangles;
};

/**
* Road geometry generation class
*
*
*
*
*/
class OSGRoad
{
private:

public:
	/**
	* Constructor
	*/
	OSGRoad();

	/* Drawing Methods */

	/**
	* Method used to draw the direction arrow helper object at the end of the road
	* @param road Pointer to an OpenDrive road object
	* @return A ref_ptr to a MatrixTransform object, which in its own case contains the arrow geode
	*/
	static osg::ref_ptr<osg::MatrixTransform> DrawDirectionArrow(Road *road);

	/**
	* Redraw the direction arrow helper object at the end of the road
	* @param matrix Pointer to the matrix transform object that contains the arrow helper. Used to adjust the transform without deleting / inserting objects into the vector
	* @param road Pointer to an OpenDrive road object
	*/
	static void RedrawDirectionArrow(osg::MatrixTransform* matrix, Road *road);

	/**
	* Draw the chord line of the road
	* @param road Pointer to an OpenDrive road object
	* @param step The double type size of the step used to sample the road
	* @return a ref_ptr to a geode with the current road's chord line
	*/
	static osg::ref_ptr<osg::Geode> DrawChordLine(Road *road, double step);

	/**
	* Redraw the chord line of the road. Return just a geometry. Is needed in order to not alter the road geodes vector, but instead alter its contents
	* @param road Pointer to an OpenDrive road object
	* @param step The double type size of the step used to sample the road
	* @return a ref_ptr to a geometry which contains the chord line
	*/
	static osg::ref_ptr<osg::Geometry> RedrawChordLine(Road *road, double step);

	/**
	* Add the vertices of the chord line to the vertex arrays. Fill the color arrays depending on the type of the geometry.
	* @param road Pointer to an OpenDrive road object
	* @param vertices A reference to the vertices array to fill
	* @param colors A reference to the colors array to fill
	* @param s s-offset position along the road at which the geometry is sampled and vertices are created
	*/
	static bool AddChordLineVertices (Road *road, osg::ref_ptr<osg::Vec3Array> &vertices, osg::ref_ptr<osg::Vec4Array> &colors, double s);

	/**
	* Draw the road. Creates the geode for the road and fills selection necessary information
	* @param road Pointer to an OpenDrive road object
	* @param nodeIndex index of the road in the roads vector
	* @param step The size of the step used to sample the road
	* @param maskVertexArrayVector A vertex array used to store the bounding vertices of the road. Needed for the landscape blending
	* @param roadTextureFile Texture of the road to be used
	* @param drawRoadMarks Defines if road marks have to be drawn
	* @param roadMarksTextureFile Texture filename that contains the image pack with the road mark textures
	* @param alphaDepthState Defines if the depth-testing has to be enabled, disabled or no alpha should be applied
	* @return a ref_ptr to a custom geode node with the current road's geometry
	*/
	static osg::ref_ptr<OSGGeodeNode> DrawRoad (Road *road, int nodeIndex, double step, vector<osg::ref_ptr<osg::Vec3Array>> &maskVertexArrayVector, 
		string roadTextureFile, 
		bool drawRoadMarks, string roadMarksTextureFile, short int alphaDepthState);


	/**
	* Create the geometry for the road which is used to create the geode in AddChordLineVertices method
	* @param geometries a pointer to a geometry node into which the road geometry should be generated
	* @param road Pointer to an OpenDrive road object
	* @param roadIndex index of the road in the roads vector
	* @param step The size of the step used to sample the road
	* @param maskVertexArrayVector A vertex array used to store the bounding vertices of the road. Needed for the landscape blending
	* @param roadTextureFile Texture of the road to be used
	* @param drawRoadMarks Defines if road marks have to be drawn
	* @param roadMarksTextureFile Texture filename that contains the image pack with the road mark textures
	* @param alphaDepthState Defines if the depth-testing has to be enabled, disabled or no alpha should be applied
	*/
	static void CreateRoadGeometry (vector<osg::ref_ptr<osg::Geometry>> &geometries, Road *road, unsigned int roadIndex, double step, 
		vector<osg::ref_ptr<osg::Vec3Array>> &maskVertexArrayVector, string roadTextureFile, 
		bool drawRoadMarks,string roadMarksTextureFile, 
		short int alphaDepthState);

	/**
	* Redraw the road by create the geometry. This method is needed in order to not alter the road geodes vector, but instead alter its contents
	* @param geometries a pointer to a geometry node into which the road geometry should be generated
	* @param road Pointer to an OpenDrive road object
	* @param roadIndex index of the road in the roads vector
	* @param step The size of the step used to sample the road
	* @param maskVertexArrayVector A vertex array used to store the bounding vertices of the road. Needed for the landscape blending
	* @param roadTextureFile Texture of the road to be used
	* @param drawRoadMarks Defines if road marks have to be drawn
	* @param roadMarksTextureFile Texture filename that contains the image pack with the road mark textures
	* @param alphaDepthState Defines if the depth-testing has to be enabled, disabled or no alpha should be applied
	*/
	static void RedrawRoad (vector<osg::ref_ptr<osg::Geometry>> &geometries, Road *road, unsigned int roadIndex, double step, 
		vector<osg::ref_ptr<osg::Vec3Array>> &maskVertexArrayVector,  string roadTextureFile, 
		bool drawRoadMarks,string roadMarksTextureFile, 
		short int alphaDepthState);

	/**
	* Add the vertices of the road to the vertex arrays. Fill the color, normals and texture coordinates arrays.
	* @param road Pointer to an OpenDrive road object
	* @param roadGeometry a reference to the geometry structure that holds all of the geometry arrays
	* @param currSample a lane section structure that holds the sampled data of the lane related parameters like width, road marks, etc.
	* @param indices a helper vector that is filled with bounding vertex indices. Used later for triangulation of the road
	* @param currentIndex a reference to the index to the last vertex.
	* @param drawRoadMarks Defines if road marks have to be drawn
	* @param roadMarksIndices  a helper vector that is filled with bounding vertex indices of the road marks. Used later for triangulation of the road marks
	* @param currentRoadMarksIndex a reference to the index to the last added vertex of the road marks.
	* @param maskVertexArrayVector A vertex array used to store the bounding vertices of the road. Needed for the landscape blending
	* @param s s-offset position along the road at which the geometry is sampled and vertices are created
	*/
	static bool AddRoadVertices (Road *road, OSGGeometryArrays &roadGeometry, OSGGeometryArrays &roadMarksGeometry, LaneSectionSample currSample, 
		vector<unsigned int> &indices, unsigned int &currentIndex, 
		bool drawRoadMarks, vector<unsigned int> &roadMarksIndices, unsigned int &currentRoadMarksIndex, 
		osg::ref_ptr<osg::Vec3Array> &maskVertexArray, double s);

	/**
	* Add the vertices of the road marks to the road marks vertex arrays. Fill the color, normals and texture coordinates arrays.
	* @param roadMarksGeometry a reference to the geometry structure that holds all of the geometry arrays for the road marks
	* @param roadMark type of road marks to be drawn
	* @param laneBorderX, laneBorderY X and Y components of the lane border (position at which the road marks should be drawn)
	* @param elevation Elevation at which the road mark should be drawn
	* @param cosHdgPlusPiO2, sinHdgPlusPiO2 sine and cosine of the direction orthogonal to the heading angle
	* @param currentRoadMarksIndex a reference to the index to the last added vertex of the road marks.
	* @param s s-offset position along the road at which the geometry is sampled and vertices are created
	*/
	static bool AddRoadMarksVertices (OSGGeometryArrays &roadMarksGeometry, LaneRoadMark roadMark, double laneBorderX, double laneBorderY, double elevation, 
		double cosHdgPlusPiO2, double sinHdgPlusPiO2, unsigned int &currentRoadMarksIndex, double s );


	/**
	* Triangulate the road. Road marks triangulation method is called from here
	* @param roadGeometry a reference to the geometry structure that holds all of the geometry arrays
	* @param indices a helper vector that is filled with bounding vertex indices
	* @param i current index to process. Is provided per sampling line
	*/
	static void AddRoadTriangles(OSGGeometryArrays &roadGeometry, vector<unsigned int> &indices, unsigned int i);

	/**
	* Triangulate the road marks
	* @param roadMarksGeometry a reference to the geometry structure that holds all of the geometry arrays
	* @param roadMarksIndices a helper vector that is filled with bounding vertex indices
	* @param i current index to process. Is provided per sampling line
	*/
	static void AddRoadMarksTriangles(OSGGeometryArrays &roadMarksGeometry, vector<unsigned int> &roadMarksIndices, unsigned int i);

	//-----------
};






#endif