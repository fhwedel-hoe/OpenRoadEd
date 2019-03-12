#ifndef OSGSCENERY_H
#define OSGSCENERY_H

#include <vector>
#include <osg/Node>
#include <osg/Geode>


/**
* Scenery class. Used to generate scenery geometry
*
*
*
*
*/
class OSGScenery
{
private:
	/**
	* Bounds of the landscape
	* Defines the rectangle that the landscape mesh fits into
	*/
	double mBoundNorth;
	double mBoundSouth;
	double mBoundEast;
	double mBoundWest;

	/**
	* Vector that holds the vertices arrays for constrained Delaunay triangulation
	*/
	std::vector<osg::ref_ptr<osg::Vec3Array>> mRoadConstraintVerticesVector;

	/**
	* Vector that holds the flag if the the vertices arrays for constrained Delaunay triangulation should be recalculated
	*/
	std::vector<bool> mRoadConstraintRecalc;

	/**
	* Reference to the heightfield mesh
	*/
	osg::ref_ptr<osg::Geode> mHeightField;

public:

	/**
	* Constructor
	*/
	OSGScenery();

	/**
	* Set the scenery bounds 
	* @param boundNorth, boundSouth, boundEast,boundWest represent max and min values in the XY plane
	*/
	void SetData(double boundNorth, double boundSouth,double boundEast,double boundWest);

	/**
	* Get the constraints vertex arrays vector
	* @return A reference to the vector of type osg::ref_ptr<osg::Vec3Array>
	*/
	std::vector<osg::ref_ptr<osg::Vec3Array>>& GetRoadConstraintVerticesVector();

	/**
	* Get the constraints vertex arrays recalculation vector
	* @return A pointer to the vector of type bool
	*/
	std::vector<bool>* GetRecalcVector();

	/**
	* Set the recalculate flag at a provided position in the vector
	* @param i Index in the mRoadConstraintRecalc vector
	* @param val The bool value that the flag should be set to
	*/
	void SetRecalc(unsigned int i, bool val);

	/**
	* Return the constraints recalculation flag at a provided index in the vector
	* @param i Index in the mRoadConstraintRecalc vector
	* @return The bool value that the flag is set to is returned
	*/
	bool GetRecalc(unsigned int i);

	/**
	* Generate the landscape and return the pointer to the geode that holds the landscape.
	* @param heightMapFile Texture file with heightmap data
	* @param terrainFile Texture file with the image that will be assigned to the terrain
	* @return A ref_ptr to a geode that holds the geometry of the landscape
	*/
	osg::ref_ptr<osg::Geode>  DrawScenery(std::string heightMapFile, std::string terrainFile);

	/**
	* Generate the heightfield from the provided heightmap texture.
	* @param heightMapFile Texture file with heightmap data
	* @param resolutionX, resolutionY Resolution of the heightmap mesh (number of collumns and rows)
	* @param heightMultiplier Used to scale the normalized height values read from the heightmap
	* @param averageElevation Used to shift the landscape vertically according to the road, if needed.
	*/
	void GenerateHeightField(std::string heightMapFile,int resolutionX, int resolutionY, double heightMultiplier, double averageElevation);

	/**
	* Return the geode that containsthe heightmap mesh.
	* @return A ref_ptr to a geode that contains the heightmap mesh.
	*/
	osg::ref_ptr<osg::Geode> GetHeightMap();

	/**
	* Clear the geometries of the heightmap mesh
	*/
	void ClearHeightField();
};

#endif