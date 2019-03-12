#include "OSGRoad.h"
#include <fstream>
#include <iostream>
#include <sstream>		//debug (convert double to string)
//#include "windows.h"	//debug (OutputDebugString)
#include <osg/Point>
#include <osg/Material>
#include <osg/Texture2D>
#include <osg/BlendFunc>
#include <osg/AlphaFunc>
#include <osg/Notify>

#include "../OpenDrive/Lane.h"
#include "OSGConstants.h"

#include <osgDB/ReadFile>
#include <osgDB/Registry>
#include <osgDB/WriteFile>

#include <osg/MatrixTransform>

#define _USE_MATH_DEFINES
#include <math.h>
using std::cout;
using std::endl;

/**
* Road geometry generation class
*
*
*
*
*/

/**
* Constructor
*/
OSGRoad::OSGRoad()
{
}

/**
* Method used to draw the direction arrow helper object at the end of the road
* @param road Pointer to an OpenDrive road object
* @return A ref_ptr to a MatrixTransform object, which in its own case contains the arrow geode
*/
osg::ref_ptr<osg::MatrixTransform> OSGRoad::DrawDirectionArrow(Road *road)
{
	osg::ref_ptr<osg::MatrixTransform> matrix = new osg::MatrixTransform;
	RedrawDirectionArrow(matrix.get(), road);

	return matrix;

}

/**
* Redraw the direction arrow helper object at the end of the road
* @param matrix Pointer to the matrix transform object that contains the arrow helper. Used to adjust the transform without deleting / inserting objects into the vector
* @param road Pointer to an OpenDrive road object
*/
void OSGRoad::RedrawDirectionArrow(osg::MatrixTransform* matrix, Road *road)
{
	matrix->removeChildren(0,matrix->getNumChildren());

	osg::ref_ptr<osg::Geode> geode = new osg::Geode();
	osg::ref_ptr<osg::Geometry> geometry = new osg::Geometry();
	//arrays for vertices
	osg::ref_ptr<osg::Vec3Array> vertices = new osg::Vec3Array;
	geometry->setVertexArray( vertices.get() );

	osg::ref_ptr<osg::DrawElementsUInt> tris = new osg::DrawElementsUInt(osg::PrimitiveSet::TRIANGLES, 0);
	geometry->addPrimitiveSet(tris.get());	
	//array  for colors
	osg::ref_ptr<osg::Vec4Array> colors = new osg::Vec4Array;
	colors->push_back(osg::Vec4(1.f, 1.f,  0.f, 1.0f) );
	geometry->setColorArray(colors.get());
	geometry->setColorBinding(osg::Geometry::BIND_OVERALL);

	double s,x,y,hdg,elevation;
	s=road->GetRoadLength();
	//Get coords
	short int resultID=road->GetGeometryCoords(s,x,y,hdg);

	//if no geometry at this s, return false
	if (resultID==-999)
		return ;

	elevation=road->GetElevationValue(s);

	//=======================
	//add the arrow vertices
	//=======================
	//bottom part
	vertices->push_back(osg::Vec3(-1,0,0));
	vertices->push_back(osg::Vec3(1,0,0));
	vertices->push_back(osg::Vec3(1,2,0));
	vertices->push_back(osg::Vec3(-1,2,0));
	//sides
	vertices->push_back(osg::Vec3(-2,2,0));
	vertices->push_back(osg::Vec3(2,2,0));
	//tip
	vertices->push_back(osg::Vec3(0,5,0));


	//=======================
	//add the arrow triangles
	//=======================

	tris->push_back(0);
	tris->push_back(1);
	tris->push_back(2);

	tris->push_back(0);
	tris->push_back(2);
	tris->push_back(3);

	tris->push_back(4);
	tris->push_back(3);
	tris->push_back(6);

	tris->push_back(3);
	tris->push_back(2);
	tris->push_back(6);

	tris->push_back(2);
	tris->push_back(5);
	tris->push_back(6);

	//assign the geometry to the geode
	geode->addDrawable(geometry.get());
	geometry->getOrCreateStateSet()->setMode(GL_LIGHTING, osg::StateAttribute::OFF);



	matrix->addChild(geode.get());
	matrix->setMatrix(	osg::Matrix::rotate(osg::inRadians(hdg-M_PI_2), osg::Vec3(0.0, 0.0, 1.0)) *
		osg::Matrix::translate(osg::Vec3(x,y,elevation+ROADMARK_ELEVATION_SHIFT+0.09))	);
}


/**
* Draw the chord line of the road
* @param road Pointer to an OpenDrive road object
* @param step The double type size of the step used to sample the road
* @return a ref_ptr to a geode with the current road's chord line
*/

osg::ref_ptr<osg::Geode> OSGRoad::DrawChordLine(Road *road, double step)
{
	//add the geode and a geometry node
	osg::ref_ptr<osg::Geode> geode = new osg::Geode();
	osg::ref_ptr<osg::Geometry> geometry = new osg::Geometry();
	//arrays for vertices
	osg::ref_ptr<osg::Vec3Array> vertices = new osg::Vec3Array;
	geometry->setVertexArray( vertices.get() );
	//array  for colors
	osg::ref_ptr<osg::Vec4Array> colors = new osg::Vec4Array;
	geometry->setColorArray(colors.get());
	geometry->setColorBinding(osg::Geometry::BIND_PER_VERTEX);


	//fill the vertex and color arrays for the entire road
	for (double s=0.0; s< road->GetRoadLength(); s+=step)
	{
		AddChordLineVertices(road,vertices,colors,s);
	}
	//and one vertex for the road end
	AddChordLineVertices(road,vertices,colors,road->GetRoadLength()-LENGTH_EPS);

	//If there no vertices, return an empty geode
	if (vertices->size()==0)
	{
		return geode.get();
	}


	//assign the geometry to the geode
	geode->addDrawable(geometry.get());
	//lines
	osg::ref_ptr<osg::DrawArrays> lines = new osg::DrawArrays(osg::PrimitiveSet::POINTS, 0, vertices.get()->size());
	geometry->addPrimitiveSet(lines.get());	
	geometry->getOrCreateStateSet()->setMode(GL_LIGHTING, osg::StateAttribute::OFF);
	geometry->getOrCreateStateSet()->setAttribute( new osg::Point( 2.0f ),osg::StateAttribute::ON );

	return geode.get();
}

/**
* Redraw the chord line of the road. Return just a geometry. Is needed in order to not alter the road geodes vector, but instead alter its contents
* @param road Pointer to an OpenDrive road object
* @param step The double type size of the step used to sample the road
* @return a ref_ptr to a geometry which contains the chord line
*/
osg::ref_ptr<osg::Geometry> OSGRoad::RedrawChordLine(Road *road, double step)
{
	osg::ref_ptr<osg::Geometry> geometry = new osg::Geometry();
	//arrays for vertices
	osg::ref_ptr<osg::Vec3Array> vertices = new osg::Vec3Array;
	//array  for colors
	osg::ref_ptr<osg::Vec4Array> colors = new osg::Vec4Array;

	//fill the vertex and color arrays for the entire road
	for (double s=0.0; s< road->GetRoadLength(); s+=step)
	{
		AddChordLineVertices(road,vertices,colors,s);
	}
	//and one vertex for the road end
	AddChordLineVertices(road,vertices,colors,road->GetRoadLength()-LENGTH_EPS);

	//If there no vertices, return an empty geode
	if (vertices->size()==0)
	{
		return geometry.get();
	}

	//assign the arrays to the geometry
	geometry->setVertexArray( vertices.get() );

	geometry->setColorArray(colors.get());
	geometry->setColorBinding(osg::Geometry::BIND_PER_VERTEX);

	//lines
	osg::ref_ptr<osg::DrawArrays> lines = new osg::DrawArrays(osg::PrimitiveSet::POINTS, 0, vertices.get()->size());
	geometry->addPrimitiveSet(lines.get());	
	geometry->getOrCreateStateSet()->setMode(GL_LIGHTING, osg::StateAttribute::OFF);
	geometry->getOrCreateStateSet()->setAttribute( new osg::Point( 2.0f ),osg::StateAttribute::ON );

	return geometry.get();
}

/**
* Add the vertices of the chord line to the vertex arrays. Fill the color arrays depending on the type of the geometry.
* @param road Pointer to an OpenDrive road object
* @param vertices A reference to the vertices array to fill
* @param colors A reference to the colors array to fill
* @param s s-offset position along the road at which the geometry is sampled and vertices are created
*/
bool OSGRoad::AddChordLineVertices (Road *road, osg::ref_ptr<osg::Vec3Array> &vertices, osg::ref_ptr<osg::Vec4Array> &colors, double s)
{
	double x,y;
	short int resultID;
	double elevation;
	resultID=road->GetGeometryCoords(s,x,y);

	//if no geometry at this s, return false
	if (resultID==-999)
		return false;

	elevation=road->GetElevationValue(s)+0.001;
	if (resultID>=0)
	{
		vertices->push_back(osg::Vec3(x,y,elevation));
		if ((s!=0.0)&&(s!=road->GetRoadLength()))
		{

			//add colors for different geometry types
			switch (resultID)
			{
			case 0: 
				colors->push_back(osg::Vec4(0.f, 0.f,  1.f, 1.0f) );		//blue for lines
				break;
			case 1:
				colors->push_back(osg::Vec4(0.f, 1.f,  0.f, 1.0f) );		//green for arcs
				break;
			case 2:
				colors->push_back(osg::Vec4(1.f, 0.f,  0.f, 1.0f) );		//red for spirals
				break;
			}
		}
		else
		{
			colors->push_back(osg::Vec4(1.f, 0.f,  1.f, 1.0f) );		//magenta for end/start of the road
		}

	}

	return true;
}


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

//alphaDepthState - 0 for no alpha and depthTesting enabled, 1 for alpha and depthTesting disabled, 2 for no alpha and depthTesting disabled
osg::ref_ptr<OSGGeodeNode> OSGRoad::DrawRoad (Road *road, int nodeIndex, double step, vector<osg::ref_ptr<osg::Vec3Array>> &maskVertexArrayVector, 
											  string roadTextureFile, 
											  bool drawRoadMarks, string roadMarksTextureFile, short int alphaDepthState)
{
	//OSG Geometry Setup
	//====================================
	//create the geode and a geometry node
	osg::ref_ptr<OSGGeodeNode> geode = new OSGGeodeNode();

	geode->SetNodeType(ROAD_NODE);

	//assign the geometries to the geode
	vector<osg::ref_ptr<osg::Geometry>> roadGeometries;
	CreateRoadGeometry(roadGeometries, road, nodeIndex, step, maskVertexArrayVector, roadTextureFile,drawRoadMarks,roadMarksTextureFile, alphaDepthState);
	for (unsigned int i=0; i< roadGeometries.size(); i++)
	{
		geode->addDrawable(roadGeometries.at(i));
	}

	return geode.get();
}


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
//alphaDepthState - 0 for no alpha and depthTesting enabled, 1 for alpha and depthTesting disabled, 2 for no alpha and depthTesting disabled
void OSGRoad::CreateRoadGeometry (vector<osg::ref_ptr<osg::Geometry>> &geometries, Road *road, unsigned int roadIndex, double step, 
								  vector<osg::ref_ptr<osg::Vec3Array>> &maskVertexArrayVector, string roadTextureFile, 
								  bool drawRoadMarks,string roadMarksTextureFile, 
								  short int alphaDepthState)
{


	//================================================================
	//Check if everything needed for the road generation exists
	//================================================================
	if (road->GetLaneSectionCount()<1)
		return;	

	//================================================================
	//road geometry
	//================================================================
	osg::ref_ptr<osg::Geometry> roadGeometry = new osg::Geometry();	
	roadGeometry->setUseDisplayList( false );
	//its arrays
	osg::ref_ptr<osg::Vec3Array> roadVertices = new osg::Vec3Array;
	osg::ref_ptr<osg::Vec3Array> roadNormals = new osg::Vec3Array;
	osg::ref_ptr<osg::Vec4Array> roadColors = new osg::Vec4Array;
	osg::ref_ptr<osg::Vec2Array> roadTexCoords = new osg::Vec2Array;
	osg::ref_ptr<osg::DrawElementsUInt> roadTriangles = new osg::DrawElementsUInt(osg::PrimitiveSet::TRIANGLES, 0);

	//struct with pointers to pass the above arrays to the method
	OSGGeometryArrays roadGeomArrays;
	roadGeomArrays.mVertices=roadVertices;
	roadGeomArrays.mNormals=roadNormals;
	roadGeomArrays.mColors=roadColors;
	roadGeomArrays.mTexCoords=roadTexCoords;
	roadGeomArrays.mTriangles=roadTriangles;

	//set the geometry arrays and continue
	roadGeometry->setVertexArray( roadVertices.get() );

	roadGeometry->setNormalArray( roadNormals.get() );
	roadGeometry->setNormalBinding(osg::Geometry::BIND_PER_VERTEX);

	roadGeometry->setColorArray(roadColors.get());
	roadGeometry->setColorBinding(osg::Geometry::BIND_PER_VERTEX);

	roadGeometry->setTexCoordArray( 0, roadTexCoords.get() );

	roadGeometry->addPrimitiveSet(roadTriangles.get());	
	//----------------------------------------------------------------

	//================================================================
	//road marks
	//================================================================
	osg::ref_ptr<osg::Geometry> roadMarksGeometry = new osg::Geometry();	
	roadMarksGeometry->setUseDisplayList( false );
	//its arrays
	OSGGeometryArrays roadMarksGeomArrays;
	if (drawRoadMarks)
	{
		osg::ref_ptr<osg::Vec3Array> roadMarksVertices = new osg::Vec3Array;
		osg::ref_ptr<osg::Vec3Array> roadMarksNormals = new osg::Vec3Array;
		osg::ref_ptr<osg::Vec4Array> roadMarksColors = new osg::Vec4Array;
		osg::ref_ptr<osg::Vec2Array> roadMarksTexCoords = new osg::Vec2Array;
		osg::ref_ptr<osg::DrawElementsUInt> roadMarksTriangles = new osg::DrawElementsUInt(osg::PrimitiveSet::TRIANGLES, 0);

		//struct with pointers to pass the above arrays to the method
		roadMarksGeomArrays.mVertices=roadMarksVertices;
		roadMarksGeomArrays.mNormals=roadMarksNormals;
		roadMarksGeomArrays.mColors=roadMarksColors;
		roadMarksGeomArrays.mTexCoords=roadMarksTexCoords;
		roadMarksGeomArrays.mTriangles=roadMarksTriangles;

		//set the geometry arrays and continue
		roadMarksGeometry->setVertexArray( roadMarksVertices.get() );

		roadMarksGeometry->setNormalArray( roadMarksNormals.get() );
		roadMarksGeometry->setNormalBinding(osg::Geometry::BIND_PER_VERTEX);

		roadMarksGeometry->setColorArray(roadMarksColors.get());
		roadMarksGeometry->setColorBinding(osg::Geometry::BIND_PER_VERTEX);

		roadMarksGeometry->setTexCoordArray( 0, roadMarksTexCoords.get() );

		roadMarksGeometry->addPrimitiveSet(roadMarksTriangles.get());	
		//----------------------------------------------------------------
	}


	//index array and var
	//these are used to create the triangles from the vertex array. 
	//The left and right ends and the center/"lane 0" of the road are stored here for each line/sample.
	vector<unsigned int> indices;
	unsigned int currentIndex=0;

	vector<unsigned int> roadMarksIndices;
	unsigned int currentRoadMarksIndex=0;


	//OSG Mask vertices - used for the generation of the terrain along the road
	osg::ref_ptr<osg::Vec3Array> maskVertexArray = new osg::Vec3Array;

	//Checker
	bool vertsAdded;

	//Lane Section Samples
	//Previous and next ones are used to deal with the texture coordinates problem
	//when there is a lane count or type change along the road
	LaneSectionSample currLaneSectionSample;

	bool prevChange;
	bool nextChange;

	//==========================================
	//Main Pass that fills the geometry arrays 
	//==========================================
	for (double s=0.0; s< road->GetRoadLength(); s+=step)
	{
		prevChange=false;
		nextChange=false;

		//First, sample the road
		//Take a lane section sample at current S
		road->FillLaneSectionSample(s,currLaneSectionSample);

		vertsAdded=AddRoadVertices(road,roadGeomArrays, roadMarksGeomArrays,currLaneSectionSample, indices, currentIndex, drawRoadMarks,roadMarksIndices, currentRoadMarksIndex, maskVertexArray, s);
	}
	//add the vertices at the road length s value - last point on the road
	//check the returned value - if no vertices calculated at current s, don't add anything to the mask
	double s=road->GetRoadLength()-LENGTH_EPS;
	road->FillLaneSectionSample(s,currLaneSectionSample);
	vertsAdded&=AddRoadVertices(road, roadGeomArrays, roadMarksGeomArrays,currLaneSectionSample, indices, currentIndex, drawRoadMarks, roadMarksIndices, currentRoadMarksIndex, maskVertexArray, s);

	//If nothing added (AddRoadVertices returns false), return
	if (!vertsAdded)
	{
		return;
	}


	//==================================================================================================================
	//loop that goes through the indices vector and based on those indices, generates triangles from the vertices array
	//==================================================================================================================
	for (unsigned int i=0; i<indices.size()-4;i+=4)
	{
		AddRoadTriangles(roadGeomArrays,indices,i);
	}

	//same for the road markings
	if (drawRoadMarks)
	{
		if (roadMarksGeomArrays.mVertices->size()>0)
		{
			for (unsigned int i=0; i<roadMarksIndices.size()-4;i+=4)
			{
				AddRoadMarksTriangles(roadMarksGeomArrays,roadMarksIndices,i);
			}
		}
		else
			roadMarksIndices.clear();
	}


	//==========================================
	//add the mask vertex array to the vector
	//==========================================
	if (roadIndex<maskVertexArrayVector.size())
	{
		maskVertexArrayVector.at(roadIndex)->clear();
		maskVertexArrayVector.at(roadIndex)=maskVertexArray;
	}
	else
		maskVertexArrayVector.push_back(maskVertexArray);


	//==========================================
	//OSG Material and textures for the road
	//==========================================
	// create a simple material
	osg::ref_ptr<osg::Material> roadMaterial = new osg::Material();
	//roadMaterial->setEmission(osg::Material::FRONT, osg::Vec4(0.0, 0.0, 0.0, 1.0));
	roadMaterial->setColorMode(osg::Material::AMBIENT_AND_DIFFUSE);

	// create a texture
	// load image for texture
	osg::Image *roadImage = osgDB::readImageFile(roadTextureFile);
	if (!roadImage) 
	{
		roadImage = osgDB::readImageFile("Resources/noTexture.jpg");

		osg::notify(osg::WARN) << "Couldn't load texture."  << std::endl;

		if (!roadImage) 
		{
			return;
		}
	}
	osg::ref_ptr<osg::Texture2D> roadTexture = new osg::Texture2D;
	roadTexture->setDataVariance(osg::Object::DYNAMIC);
	roadTexture->setWrap(osg::Texture::WRAP_S, osg::Texture::REPEAT);
	roadTexture->setWrap(osg::Texture::WRAP_T, osg::Texture::REPEAT);
	roadTexture->setImage(roadImage);

	osg::StateSet* roadStateSet=roadGeometry->getOrCreateStateSet();
	// assign the material and texture
	roadStateSet->setAttribute(roadMaterial);
	roadStateSet->setTextureAttributeAndModes(0, roadTexture, osg::StateAttribute::ON);
	roadStateSet->setMode(GL_LIGHTING, osg::StateAttribute::ON);


	switch (alphaDepthState)
	{
	case 1:
		roadStateSet->setMode(GL_BLEND,osg::StateAttribute::ON); 
		roadStateSet->setMode(GL_DEPTH_TEST,osg::StateAttribute::OFF);
		break;
	case 2:
		roadStateSet->setMode(GL_DEPTH_TEST,osg::StateAttribute::OFF);
		break;
	}


	if (drawRoadMarks)
	{
		//================================================
		//OSG Material and textures for the road marks
		//================================================
		// create a simple material
		osg::ref_ptr<osg::Material> roadMarksMaterial = new osg::Material();
		roadMarksMaterial->setEmission(osg::Material::FRONT, osg::Vec4(0.4, 0.4, 0.4, 1.0));
		roadMarksMaterial->setColorMode(osg::Material::AMBIENT_AND_DIFFUSE);

		// create a texture
		// load image for texture
		osg::Image *roadMarksImage = osgDB::readImageFile(roadMarksTextureFile);
		if (!roadMarksImage) 
		{
			roadMarksImage = osgDB::readImageFile("Resources/noTexture.jpg");

			osg::notify(osg::WARN) << "Couldn't load texture."  << std::endl;

			if (!roadMarksImage) 
			{
				return;
			}
		}
		osg::ref_ptr<osg::Texture2D> roadMarksTexture = new osg::Texture2D;
		roadMarksTexture->setDataVariance(osg::Object::DYNAMIC);
		roadMarksTexture->setFilter(osg::Texture::MIN_FILTER, osg::Texture::LINEAR_MIPMAP_LINEAR);
		roadMarksTexture->setFilter(osg::Texture::MAG_FILTER, osg::Texture::LINEAR);
		roadMarksTexture->setWrap(osg::Texture::WRAP_S, osg::Texture::REPEAT);
		roadMarksTexture->setWrap(osg::Texture::WRAP_T, osg::Texture::REPEAT);
		roadMarksTexture->setImage(roadMarksImage);

		osg::StateSet* roadMarksStateSet=roadMarksGeometry->getOrCreateStateSet();
		// assign the material and texture
		roadMarksStateSet->setAttribute(roadMarksMaterial);
		roadMarksStateSet->setTextureAttributeAndModes(0, roadMarksTexture, osg::StateAttribute::ON);
		roadMarksStateSet->setMode(GL_LIGHTING, osg::StateAttribute::ON);
		roadMarksStateSet->setMode(GL_BLEND,osg::StateAttribute::ON); 
		roadMarksStateSet->setMode(GL_DEPTH_TEST,osg::StateAttribute::OFF);
	}


	//add the road and road markings geometries to the output vector
	geometries.push_back(roadGeometry);
	geometries.push_back(roadMarksGeometry);
}


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
bool  OSGRoad::AddRoadVertices (Road *road, OSGGeometryArrays &roadGeometry, OSGGeometryArrays &roadMarksGeometry, LaneSectionSample currSample, 
								vector<unsigned int> &indices, unsigned int &currentIndex, 
								bool drawRoadMarks, vector<unsigned int> &roadMarksIndices, unsigned int &currentRoadMarksIndex, 
								osg::ref_ptr<osg::Vec3Array> &maskVertexArray, double s)
{
	//temp vars
	double x,y,hdg;
	short int resultID;
	double elevation,superElevation;
	double angleLeft=0;
	double angleRight=0;
	double cosAngleLeft, cosAngleRight,sinAngleLeft, sinAngleRight;

	double currentX,currentY;
	double curWidth,widthAccum;
	double currentElevation, elevationAccum;

	double oldHeight=0;
	double heightModifier=0;

	string type;


	//For the moment, there are 2 types of road textures : for driving and for walking+everything else.
	//All of them are placed in a single texture file.
	//In order to change the type visually, texture coordinates are translated
	//Parameter below define the width of the driving texture in the texture image
	//This is brute forcing, but as additional types will be added, this option might get its own property window, etc.
	const double roadTexWidth=0.666666666666;
	//Texture coord modifiers
	double roadTexModifierMin=0;
	double roadTexModifierMax=0;


	//++++++++++++++++++++++++++++++++++++++++++
	//Sample the road parameters for current S
	//++++++++++++++++++++++++++++++++++++++++++

	//Get chord line coords
	resultID=road->GetGeometryCoords(s,x,y,hdg);
	//if no geometry at this s, return false
	if (resultID==-999)
		return false;

	//Get Elevation
	elevation=road->GetElevationValue(s);
	//Get SuperElevation and Crossfall values and calculate the required angles for both sides of the road
	superElevation=road->GetSuperElevationValue(s);
	//because negative superelevation falls to the left, invert the value to simplify the calculations
	superElevation=-superElevation;
	road->GetCrossfallValue(s,angleLeft,angleRight);
	angleLeft-=superElevation;
	angleRight+=superElevation;

	//get the sine and cosine of these angles to speed up the calculations
	cosAngleLeft=cos(angleLeft);
	cosAngleRight=cos(angleRight);
	sinAngleLeft=sin(angleLeft);
	sinAngleRight=sin(angleRight);

	//Use the width vectors to calculate coordinates
	//Also, depending on the "level" param, multiply by sin and cos of angleLeft/angleRight
	//to take superelevation and crossfall into account

	//cosine and sine for the tangent (lateral position in track coords)
	double cosHdgPlusPiO2=cos(hdg+M_PI_2);
	double sinHdgPlusPiO2=sin(hdg+M_PI_2);

	//central index for the left side of the road
	indices.push_back(currentIndex);



	if (drawRoadMarks)
	{
		//Check the sample for road marks, if there are none, the drawRoadMarks is set to false
		drawRoadMarks=false;
		for (unsigned int i=0; i<currSample.GetLeftVectorsSize(); i++)
		{
			if (currSample.GetLeftRoadMark(i).GetType().compare("none")!=0)
				drawRoadMarks=true;
		}

		for (unsigned int i=0; i<currSample.GetRightVectorsSize(); i++)
		{
			if (currSample.GetRightRoadMark(i).GetType().compare("none")!=0)
				drawRoadMarks=true;
		}	
	}

	if (drawRoadMarks)
	{
		//central index for the left side of the road mark
		roadMarksIndices.push_back(currentRoadMarksIndex);
	}

	//Calculate texture coords
	double texX,texY;
	texY=s/TEXTURE_LENGTH_SCALING;
	texX=0;


	currentX=0;
	currentY=0;
	curWidth=0;
	widthAccum=0;
	elevationAccum=elevation;

	//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	//go through all the lanes from the central until the left bound lane (right to left)
	//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	int numElements = int(currSample.GetLeftVectorsSize())-1;
	for (int i=0, i2=i+1; i<numElements;i++, i2++)
	{
		//=============================
		//First Vertex of current lane
		//=============================
		currentElevation=elevationAccum;

		//.....................................
		//Check the type of the lane 
		//.....................................
		type=currSample.GetLeftType(i2);
		if (type.compare("driving")!=0)
		{
			roadTexModifierMin=roadTexWidth;
			roadTexModifierMax=1;
		}
		else
		{
			roadTexModifierMin=0;
			roadTexModifierMax=roadTexWidth;
		}

		//.........................
		//Check the height parameter
		//.........................
		//get the lane height
		LaneHeight height = currSample.GetLeftHeight(i2);
		heightModifier=height.GetInner();
		//if the height changed, add a vertical face
		if (fabs( oldHeight - heightModifier) > HEIGHT_EPS )
		{

			/////////////////
			//bottom vertex
			/////////////////
			//push the vertex
			roadGeometry.mVertices->push_back(osg::Vec3(x+currentX,y+currentY,currentElevation+oldHeight));
			roadGeometry.mNormals->push_back(osg::Vec3(0,0,1));
			roadGeometry.mColors->push_back(osg::Vec4(1, 1,  1.f, 1.0f) );
			//add texture coords
			texX=roadTexModifierMin;
			roadGeometry.mTexCoords->push_back(osg::Vec2(texX,texY));

			//increment the triangles index;
			currentIndex++;

			/////////////////
			//top vertex
			/////////////////
			//push the vertex
			roadGeometry.mVertices->push_back(osg::Vec3(x+currentX,y+currentY,currentElevation+heightModifier));
			roadGeometry.mNormals->push_back(osg::Vec3(0,0,1));
			roadGeometry.mColors->push_back(osg::Vec4(1, 1,  1.f, 1.0f) );
			//add texture coords
			texX=roadTexModifierMax;
			roadGeometry.mTexCoords->push_back(osg::Vec2(texX,texY));

			//increment the triangles index;
			currentIndex++;
		}

		//push the vertex
		roadGeometry.mVertices->push_back(osg::Vec3(x+currentX,y+currentY,currentElevation+heightModifier));
		roadGeometry.mNormals->push_back(osg::Vec3(0,0,1));
		roadGeometry.mColors->push_back(osg::Vec4(1, 1,  1.f, 1.0f) );
		//add texture coords
		texX=roadTexModifierMin;
		roadGeometry.mTexCoords->push_back(osg::Vec2(texX,texY));

		//increment the triangles index;
		currentIndex++;



		//======================================================================================
		//Second Vertex of the lane / at the position of the first vertex of the next lane
		//======================================================================================
		curWidth=currSample.GetLeftWidth(i2);
		widthAccum+=curWidth;
		currentX=cosHdgPlusPiO2*widthAccum;
		currentY=sinHdgPlusPiO2*widthAccum;

		//check for the level param
		if(!currSample.GetLeftLevel(i2))
		{
			currentX*=cosAngleLeft;
			currentY*=cosAngleLeft;
			currentElevation+=sinAngleLeft*curWidth;
			elevationAccum=currentElevation;
		}


		heightModifier=height.GetOuter();
		oldHeight=heightModifier;

		//push the vertex
		roadGeometry.mVertices->push_back(osg::Vec3(x+currentX,y+currentY,currentElevation+heightModifier));
		roadGeometry.mNormals->push_back(osg::Vec3(0,0,1));
		roadGeometry.mColors->push_back(osg::Vec4(1, 1,  1.f, 1.0f) );
		//add texture coords
		texX=roadTexModifierMax;
		roadGeometry.mTexCoords->push_back(osg::Vec2(texX,texY));


		if (drawRoadMarks)
		{
			//push the vertices for the road marks
			AddRoadMarksVertices (roadMarksGeometry, currSample.GetLeftRoadMark(i2), x+currentX,y+currentY,currentElevation+heightModifier, 
				cosHdgPlusPiO2, sinHdgPlusPiO2,currentRoadMarksIndex,s );
		}

		//increment the index;
		currentIndex++;
	}

	//Left bound index
	//Next check is necessary because in case there are no left lanes, the left index should be the same as the central one for the left side
	if (numElements>=0)
	{
		indices.push_back(currentIndex-1);
	}
	else
	{
		indices.push_back(currentIndex);	
	}

	//Add the second index for the road mark triangulation as well, if needed
	if (drawRoadMarks)
	{
		if (roadMarksIndices.size()>1)
		{	roadMarksIndices.push_back(currentRoadMarksIndex-1);	}
		else
		{	roadMarksIndices.push_back(currentRoadMarksIndex);		}
	}

	//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	//Add the vertices for the road marks for the central lane
	//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	if (drawRoadMarks)
	{	
		//add second central road mark index
		roadMarksIndices.push_back(currentRoadMarksIndex);
		//Check if there are left lanes, take the lane 0 road marks from the left side vector
		if (currSample.GetLeftVectorsSize()>0)
		{
			//push the vertices for the central road mark (taken from the left vector)
			AddRoadMarksVertices (roadMarksGeometry, currSample.GetLeftRoadMark(0), x,y,elevation+heightModifier, 
				cosHdgPlusPiO2, sinHdgPlusPiO2,currentRoadMarksIndex,s );
		}
		//otherwise, take it from the right vector
		else
		{
			//push the vertices for the central road mark (taken from the right vector)
			AddRoadMarksVertices (roadMarksGeometry, currSample.GetRightRoadMark(0), x,y,elevation+heightModifier, 
				cosHdgPlusPiO2, sinHdgPlusPiO2,currentRoadMarksIndex,s );
		}
	}



	//The second central index, used for the creation of the right side of the road
	indices.push_back(currentIndex);

	currentX=0;
	currentY=0;
	curWidth=0;
	widthAccum=0;
	elevationAccum=elevation;

	//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	//go through all the lanes until the Right lane bound (left to right)
	//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	numElements=int(currSample.GetRightVectorsSize())-1;
	for (int i=0, i2=i+1; i<numElements;i++, i2++)
	{

		//=============================
		//First Vertex of current lane
		//=============================
		currentElevation=elevationAccum;

		//.....................................
		//Check the type of the lane parameter
		//.....................................
		type=currSample.GetRightType(i2);
		if (type.compare("driving")!=0)
		{
			roadTexModifierMin=roadTexWidth;
			roadTexModifierMax=1;
		}
		else
		{
			roadTexModifierMin=0;
			roadTexModifierMax=roadTexWidth;
		}

		//.........................
		//Check the height parameter
		//.........................
		//get the lane height
		LaneHeight height = currSample.GetRightHeight(i2);
		heightModifier=height.GetInner();
		//if the height changed, add a vertical face
		if (fabs( oldHeight - heightModifier) > HEIGHT_EPS )
		{
			/////////////////
			//bottom vertex
			/////////////////
			//push the vertex
			roadGeometry.mVertices->push_back(osg::Vec3(x+currentX,y+currentY,currentElevation+oldHeight));
			roadGeometry.mNormals->push_back(osg::Vec3(0,0,1));
			//blue for left side vertices
			//colors->push_back(osg::Vec4(0.8f, 0.8f,  1.f, 1.0f) );
			roadGeometry.mColors->push_back(osg::Vec4(1, 1,  1.f, 1.0f) );
			//add texture coords
			texX=roadTexModifierMin;
			roadGeometry.mTexCoords->push_back(osg::Vec2(texX,texY));

			//increment the triangles index;
			currentIndex++;

			/////////////////
			//top vertex
			/////////////////
			//push the vertex
			roadGeometry.mVertices->push_back(osg::Vec3(x+currentX,y+currentY,currentElevation+heightModifier));
			roadGeometry.mNormals->push_back(osg::Vec3(0,0,1));
			//blue for left side vertices
			//colors->push_back(osg::Vec4(0.8f, 0.8f,  1.f, 1.0f) );
			roadGeometry.mColors->push_back(osg::Vec4(1, 1,  1.f, 1.0f) );
			//add texture coords
			texX=roadTexModifierMax;
			roadGeometry.mTexCoords->push_back(osg::Vec2(texX,texY));

			//increment the triangles index;
			currentIndex++;
		}

		//push the vertex
		roadGeometry.mVertices->push_back(osg::Vec3(x+currentX,y+currentY,currentElevation+heightModifier));
		roadGeometry.mNormals->push_back(osg::Vec3(0,0,1));
		//blue for left side vertices
		//colors->push_back(osg::Vec4(0.8f, 0.8f,  1.f, 1.0f) );
		roadGeometry.mColors->push_back(osg::Vec4(1, 1,  1.f, 1.0f) );
		//add texture coords
		texX=roadTexModifierMin;
		roadGeometry.mTexCoords->push_back(osg::Vec2(texX,texY));

		//increment the triangles index;
		currentIndex++;



		//========================================================================================
		//Second Vertex of the lane / at the position of the first vertex of the next lane
		//========================================================================================
		curWidth=currSample.GetRightWidth(i2);
		widthAccum+=curWidth;
		currentX=-cosHdgPlusPiO2*widthAccum;
		currentY=-sinHdgPlusPiO2*widthAccum;

		//check for the level param
		if(!currSample.GetRightLevel(i2))
		{
			currentX*=cosAngleRight;
			currentY*=cosAngleRight;
			currentElevation+=sinAngleRight*curWidth;
			elevationAccum=currentElevation;
		}

		heightModifier=height.GetOuter();
		oldHeight=heightModifier;

		//push the vertex
		roadGeometry.mVertices->push_back(osg::Vec3(x+currentX,y+currentY,currentElevation+heightModifier));
		roadGeometry.mNormals->push_back(osg::Vec3(0,0,1));
		//blue for left side vertices
		//colors->push_back(osg::Vec4(0.8f, 0.8f,  1.f, 1.0f) );
		roadGeometry.mColors->push_back(osg::Vec4(1, 1,  1.f, 1.0f) );
		//add texture coords
		texX=roadTexModifierMax;
		roadGeometry.mTexCoords->push_back(osg::Vec2(texX,texY));



		if (drawRoadMarks)
		{
			//push the vertices for the road marks
			AddRoadMarksVertices (roadMarksGeometry, currSample.GetRightRoadMark(i2), x+currentX,y+currentY,currentElevation+heightModifier,
				-cosHdgPlusPiO2, -sinHdgPlusPiO2, currentRoadMarksIndex, s );
		}

		//increment the index;
		currentIndex++;
	}

	//Line end index
	indices.push_back(currentIndex-1);
	if (drawRoadMarks)
	{
		roadMarksIndices.push_back(currentRoadMarksIndex-1);
	}

	//Add bound vertices to the mask
	maskVertexArray->push_back(roadGeometry.mVertices->at(indices.at(indices.size()-3)));
	maskVertexArray->push_back(roadGeometry.mVertices->at(indices.at(indices.size()-1)));

	return true;
}


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
bool  OSGRoad::AddRoadMarksVertices (OSGGeometryArrays &roadMarksGeometry, LaneRoadMark roadMark, double laneBorderX, double laneBorderY, double elevation, 
									 double cosHdgPlusPiO2, double sinHdgPlusPiO2, unsigned int &currentRoadMarksIndex, double s )
{

	double width;
	osg::Vec4 roadMarkColor;

	const double roadMarkTexWidth=0.5;
	double roadMarkTexModifierMin1=0;
	double roadMarkTexModifierMax1=0;

	double roadMarkTexModifierMin2=0;
	double roadMarkTexModifierMax2=0;

	double x1,y1,x2,y2;
	double x3=0,y3=0,x4=0,y4=0;
	double z=elevation+ROADMARK_ELEVATION_SHIFT;
	//type 0 = one mark, type 1 = solid solid, 2 = solid broken, 3 = broken solid
	short int type=0;		


	//Define the width of the current road mark:
	//If a width is given, ignore the weight parameter and set the width explicitly
	if (roadMark.GetWidth()>0)
	{	
		width = roadMark.GetWidth();	
	}
	else
	{
		//otherwise, check the weight param
		if (roadMark.GetWeight().compare("standard")==0)
		{	width=STD_ROADMARK_WIDTH;	}
		else
		{	width=BOLD_ROADMARK_WIDTH;	}
	}


	x1 = laneBorderX + cosHdgPlusPiO2*width/2.;
	y1 = laneBorderY + sinHdgPlusPiO2*width/2.;

	x2 = laneBorderX - cosHdgPlusPiO2*width/2.;
	y2 = laneBorderY - sinHdgPlusPiO2*width/2.;

	//Define the color of the current road mark:
	if (roadMark.GetColor().compare("standard")==0)
	{	roadMarkColor.set(1,1,1,1);	}//set to white	
	else
	{	roadMarkColor.set(1,1,0,1);	}//set to yellow 


	//Set the tex coords modifiers based on the type of the road mark
	if (roadMark.GetType().compare("none")==0)
	{
		type=-1;	//debug only
		return false;
	}
	if (roadMark.GetType().compare("solid")==0)
	{
		type=0;
		roadMarkTexModifierMax1=roadMarkTexWidth;
	}
	else 
		if (roadMark.GetType().compare("broken")==0)
		{
			type=0;
			roadMarkTexModifierMin1=roadMarkTexWidth;
			roadMarkTexModifierMax1=1;
		}
		else 
			if (roadMark.GetType().compare("solid solid")==0)
			{
				type=1;		
				roadMarkTexModifierMax1=roadMarkTexWidth;
				roadMarkTexModifierMax2=roadMarkTexWidth;
			}
			else 
				if (roadMark.GetType().compare("solid broken")==0)
				{
					type=2;		
					roadMarkTexModifierMin1=0;
					roadMarkTexModifierMax1=roadMarkTexWidth;
					roadMarkTexModifierMin2=roadMarkTexWidth;
					roadMarkTexModifierMax2=1;
				}
				else 
					if (roadMark.GetType().compare("broken solid")==0)
					{
						type=3;		
						roadMarkTexModifierMin1=roadMarkTexWidth;
						roadMarkTexModifierMax1=1;
						roadMarkTexModifierMin2=0;
						roadMarkTexModifierMax2=roadMarkTexWidth;
					}

					//===============================
					//Add Vertices
					//===============================
					double texX;
					double texY=s/ROADMARK_BROKEN_TILING;

					if (type>0)
					{
						//shift the x,y in case it is a 2 line mark
						x1 = laneBorderX + cosHdgPlusPiO2*1.5*width;
						y1 = laneBorderY + sinHdgPlusPiO2*1.5*width;

						x2 = laneBorderX + cosHdgPlusPiO2*0.25*width;
						y2 = laneBorderY + sinHdgPlusPiO2*0.25*width;

						x3 = laneBorderX - cosHdgPlusPiO2*0.25*width;
						y3 = laneBorderY - sinHdgPlusPiO2*0.25*width;

						x4 = laneBorderX - cosHdgPlusPiO2*1.5*width;
						y4 = laneBorderY - sinHdgPlusPiO2*1.5*width;

					}

					//First vertex
					texX=roadMarkTexModifierMin1;

					roadMarksGeometry.mVertices->push_back(osg::Vec3(x1,y1,z));
					roadMarksGeometry.mNormals->push_back(osg::Vec3(0,0,1));
					roadMarksGeometry.mColors->push_back(roadMarkColor);
					roadMarksGeometry.mTexCoords->push_back(osg::Vec2(texX,texY));

					currentRoadMarksIndex++;


					//Second vertex
					texX=roadMarkTexModifierMax1;
					roadMarksGeometry.mVertices->push_back(osg::Vec3(x2,y2,z));
					roadMarksGeometry.mNormals->push_back(osg::Vec3(0,0,1));
					roadMarksGeometry.mColors->push_back(roadMarkColor);
					roadMarksGeometry.mTexCoords->push_back(osg::Vec2(texX,texY));

					currentRoadMarksIndex++;

					//If it is a double line mark, add the second pair of vertices
					if (type>0)
					{
						//First vertex of the second line
						texX=roadMarkTexModifierMin2;
						roadMarksGeometry.mVertices->push_back(osg::Vec3(x3,y3,z));
						roadMarksGeometry.mNormals->push_back(osg::Vec3(0,0,1));
						roadMarksGeometry.mColors->push_back(roadMarkColor);
						roadMarksGeometry.mTexCoords->push_back(osg::Vec2(texX,texY));

						currentRoadMarksIndex++;


						//Second vertex  of the second line
						texX=roadMarkTexModifierMax2;
						roadMarksGeometry.mVertices->push_back(osg::Vec3(x4,y4,z));
						roadMarksGeometry.mNormals->push_back(osg::Vec3(0,0,1));
						roadMarksGeometry.mColors->push_back(roadMarkColor);
						roadMarksGeometry.mTexCoords->push_back(osg::Vec2(texX,texY));

						currentRoadMarksIndex++;
					}

					return true;

}

/**
* Triangulate the road. Road marks triangulation method is called from here
* @param roadGeometry a reference to the geometry structure that holds all of the geometry arrays
* @param indices a helper vector that is filled with bounding vertex indices
* @param i current index to process. Is provided per sampling line
*/
void  OSGRoad::AddRoadTriangles(OSGGeometryArrays &roadGeometry, vector<unsigned int> &indices,unsigned int i)
{	

	//indices
	unsigned int l1, c1,c11, r1;
	unsigned int l2, c2,c22, r2;

	//line 1
	c1=indices.at(i);		//center of the road for the left side
	l1=indices.at(i+1);
	c11=indices.at(i+2);	//center of the road for the right side
	r1=indices.at(i+3);

	//line 2
	c2=indices.at(i+4);		//center of the road for the left side
	l2=indices.at(i+5);
	c22=indices.at(i+6);	//center of the road for the right side
	r2=indices.at(i+7);

	//iterators: j - first line; k - second line
	unsigned int j,k;

	//create triangles for the left portion with the same number of lanes
	j=c1;
	k=c2;
	while ((j < l1)&&(k < l2))
	{
		//first triangle
		roadGeometry.mTriangles->push_back(j);
		roadGeometry.mTriangles->push_back(k+1);
		roadGeometry.mTriangles->push_back(j+1);

		//second triangle
		roadGeometry.mTriangles->push_back(j);
		roadGeometry.mTriangles->push_back(k);
		roadGeometry.mTriangles->push_back(k+1);

		j+=2;
		k+=2;
	}

	//check which case it is for the left part:
	//1) first line has less lanes
	if (l1-c1 < l2-c2)
	{
		//decrement the first line index
		j--;
		//and proceed
		while (k<l2)
		{
			roadGeometry.mTriangles->push_back(j);
			roadGeometry.mTriangles->push_back(k);
			roadGeometry.mTriangles->push_back(k+1);
			k+=2;
		}
	}

	//2)first line has more lanes
	if (l1-c1 > l2-c2)
	{
		//decrement the second line index
		k--;
		//and proceed
		while (j<l1)
		{
			roadGeometry.mTriangles->push_back(j);
			roadGeometry.mTriangles->push_back(k);
			roadGeometry.mTriangles->push_back(j+1);
			j+=2;
		}
	}

	//create triangles for the right portion with the same number of lanes
	j=c11;
	k=c22;
	while ((j < r1)&&(k < r2))
	{
		//first triangle
		roadGeometry.mTriangles->push_back(j);
		roadGeometry.mTriangles->push_back(j+1);
		roadGeometry.mTriangles->push_back(k+1);

		//second triangle
		roadGeometry.mTriangles->push_back(j);
		roadGeometry.mTriangles->push_back(k+1);
		roadGeometry.mTriangles->push_back(k);

		j+=2;
		k+=2;
	}

	//check which case it is for the right part:
	//1) first line has less lanes
	if (r1-c11 < r2-c22)
	{
		//decrement the first line index
		j--;
		//and proceed
		while (k<r2)
		{
			roadGeometry.mTriangles->push_back(j);
			roadGeometry.mTriangles->push_back(k+1);
			roadGeometry.mTriangles->push_back(k);
			k+=2;
		}
	}

	//2)first line has more lanes
	if (r1-c11 > r2-c22)
	{
		//decrement the second line index
		k--;
		//and proceed
		while (j<r1)
		{
			roadGeometry.mTriangles->push_back(j);
			roadGeometry.mTriangles->push_back(j+1);
			roadGeometry.mTriangles->push_back(k);
			j+=2;
		}
	}
}

/**
* Triangulate the road marks
* @param roadMarksGeometry a reference to the geometry structure that holds all of the geometry arrays
* @param roadMarksIndices a helper vector that is filled with bounding vertex indices
* @param i current index to process. Is provided per sampling line
*/
void OSGRoad::AddRoadMarksTriangles(OSGGeometryArrays &roadMarksGeometry, vector<unsigned int> &roadMarksIndices, unsigned int i)
{
	AddRoadTriangles(roadMarksGeometry, roadMarksIndices, i);
}

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
//alphaDepthState - 0 for no alpha and depthTesting enabled, 1 for alpha and depthTesting disabled, 2 for no alpha and depthTesting disabled
void OSGRoad::RedrawRoad (vector<osg::ref_ptr<osg::Geometry>> &geometries, Road *road, unsigned int roadIndex, double step, 
						  vector<osg::ref_ptr<osg::Vec3Array>> &maskVertexArrayVector,  string roadTextureFile, 
						  bool drawRoadMarks,string roadMarksTextureFile, 
						  short int alphaDepthState)
{
	CreateRoadGeometry(geometries,road,roadIndex,step,maskVertexArrayVector,roadTextureFile,drawRoadMarks,roadMarksTextureFile,alphaDepthState);
}
//-----------
