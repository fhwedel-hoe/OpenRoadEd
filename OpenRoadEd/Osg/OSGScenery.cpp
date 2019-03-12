#include "OSGScenery.h"
#include <osgUtil/DelaunayTriangulator>
#include <osgDB/ReadFile>
#include <osg/Texture2D>
#include <osg/Material>
#include <osg/ShapeDrawable>
#include <osgUtil/Simplifier>
#include <osg/Point>
#include <osgUtil/SmoothingVisitor>
#include <osg/Notify>

/**
* Scenery class. Used to generate scenery geometry
*
*
*
*
*/

/**
* Constructor. Initializes the ref_ptr of the heightmap mesh
*/

OSGScenery::OSGScenery()
{
	mHeightField=NULL;
}

/**
* Set the scenery bounds 
* @param boundNorth, boundSouth, boundEast,boundWest represent max and min values in the XY plane
*/
void OSGScenery::SetData(double boundNorth, double boundSouth,double boundEast,double boundWest)
{
	mBoundNorth=boundNorth;
	mBoundSouth=boundSouth;
	mBoundEast=boundEast;
	mBoundWest=boundWest;	
}


/**
* Get the constraints vertex arrays vector
* @return A reference to the vector of type osg::ref_ptr<osg::Vec3Array>
*/
std::vector<osg::ref_ptr<osg::Vec3Array>>&  OSGScenery::GetRoadConstraintVerticesVector()
{
	return mRoadConstraintVerticesVector;
}




/**
* Set the recalculate flag at a provided position in the vector
* @param i Index in the mRoadConstraintRecalc vector
* @param val The bool value that the flag should be set to
*/
void  OSGScenery::SetRecalc(unsigned int i, bool val)
{
	if (i>=mRoadConstraintRecalc.size())
		mRoadConstraintRecalc.push_back(val);
	else
		mRoadConstraintRecalc.at(i) = val;
}

/**
* Return the constraints recalculation flag at a provided index in the vector
* @param i Index in the mRoadConstraintRecalc vector
* @return The bool value that the flag is set to is returned
*/
bool OSGScenery::GetRecalc(unsigned int i)
{
	return mRoadConstraintRecalc.at(i);
}


/**
* Get the constraints vertex arrays recalculation vector
* @return A pointer to the vector of type bool
*/
std::vector<bool>* OSGScenery::GetRecalcVector()
{
	return &mRoadConstraintRecalc;
}


/**
* Generate the landscape and return the pointer to the geode that holds the landscape.
* @param heightMapFile Texture file with heightmap data
* @param terrainFile Texture file with the image that will be assigned to the terrain
* @return A ref_ptr to a geode that holds the geometry of the landscape
*/

osg::ref_ptr<osg::Geode>  OSGScenery::DrawScenery(std::string heightMapFile, std::string terrainFile)
{
	//---------------------------------------------
	//OSG Geometry Setup
	//----------------------------------------------
	//create the geode and a geometry node
	osg::ref_ptr<osg::Geode> geode = new osg::Geode;

	osg::ref_ptr<osg::Geometry> geometry = new osg::Geometry();
	geometry->setUseDisplayList( false );

	osg::ref_ptr<osg::Vec3Array> vertices = dynamic_cast<osg::Vec3Array*>(dynamic_cast<osg::Geometry*>(mHeightField->getDrawable(0))->getVertexArray());

	//if there are no mask vertices, return an empty geode
	if (vertices->size()==0)
	{
		return geode.get();
	}
	//if there is no hieghtfield, return
	if (mHeightField==NULL)
	{
		return geode.get();
	}




	//assign the geometry to the geode
	geode->addDrawable(geometry.get());
	// create triangulator and set the points as the area
	osg::ref_ptr<osgUtil::DelaunayTriangulator> trig = new osgUtil::DelaunayTriangulator();
	trig->setInputPointArray(vertices);

	//Create a vector for triangulator constraints for each road
	std::vector<osg::ref_ptr<osgUtil::DelaunayConstraint>> constraints;

	//A temporary vertex array structure
	osg::ref_ptr<osg::Vec3Array> tempConstraintVertices;

	//-----------------------------------------------------------
	//Transform all the vertexMasks of the roads into line_loops
	//-----------------------------------------------------------

	//This loop goes through the contents of mRoadConstraintVerticesVector, which contains the vertex arrays (left/right edges) for each road.
	//It transforms the vertex structure/ordering from the TRIANGLES to LINE_LOOP. This is done in order to create a line loop around the road polygons,
	//so that they could be deleted from the terrain geometry.
	for (unsigned int i=0; i<mRoadConstraintVerticesVector.size();i++)
	{
		if (mRoadConstraintRecalc.at(i))
		{
			mRoadConstraintRecalc.at(i)=false;

			//allocate memory for the new LINE_LOOP vertex array structure
			tempConstraintVertices = new osg::Vec3Array;

			//go through the left edge vertices of the road and push them into the temporary vertex array
			for (osg::Vec3Array::iterator it=mRoadConstraintVerticesVector.at(i)->begin(); it!=mRoadConstraintVerticesVector.at(i)->end(); it+=2)
			{
				tempConstraintVertices->push_back((*it));
			}

			//go through the right edge vertices of the road and push them into the temporary vertex array
			for (osg::Vec3Array::reverse_iterator rit=mRoadConstraintVerticesVector.at(i)->rbegin(); rit!=mRoadConstraintVerticesVector.at(i)->rend(); rit+=2)
			{
				tempConstraintVertices->push_back((*rit));
			}

			//Delete all vertices from the current vertex array
			mRoadConstraintVerticesVector.at(i)->clear();
			//Assign the current iterator/pointer to the newly created/restructured vertex array
			mRoadConstraintVerticesVector.at(i)=tempConstraintVertices;
		}

		//Add the vertices of the current road "mask" (vertices that surround the current road in a LINE_LOOP) to the constraint for the current road
		constraints.push_back(new osgUtil::DelaunayConstraint);
		constraints.at(constraints.size()-1)->setVertexArray(mRoadConstraintVerticesVector.at(i));


		constraints.at(constraints.size()-1)->addPrimitiveSet(new osg::DrawArrays(osg::PrimitiveSet::LINE_LOOP,0,mRoadConstraintVerticesVector.at(i)->size()) );
	}

	//----------------------------------------------
	//Add the constraints and triangulate
	//----------------------------------------------

	// add constraint to triangulator
	for (std::vector<osg::ref_ptr<osgUtil::DelaunayConstraint>>::iterator it=constraints.begin(); it!=constraints.end(); ++it )
	{
		trig->addInputConstraint((*it).get());
	}

	//triangulate
	trig->triangulate();

	//remove triangles surrounded by the road masks from the generated terrain 
	for(std::vector<osg::ref_ptr<osgUtil::DelaunayConstraint>>::iterator it=constraints.begin(); it!=constraints.end(); ++it )
	{
		trig->removeInternalTriangles((*it).get());
	}

	//add triangles
	geometry->setVertexArray( vertices.get() );
	geometry->addPrimitiveSet(trig->getTriangles());

	//Add per-vertex normal information
	osgUtil::SmoothingVisitor::smooth(*(geometry.get()));

	//-------------------------------------------------------------------------------------------
	//In case of wrong normals being generated, fix them and generate vertex normals
	//------------------------------------------------------------------------------------------
	//In case that Delaunay triangulator generated invalid normals (pointing downwards), invert them
	osg::Vec3Array* normals=dynamic_cast<osg::Vec3Array*> (geometry->getNormalArray());
	for (osg::Vec3Array::iterator it=normals->begin(); it!=normals->end(); ++it )
	{
		(*it).normalize();
		if ((*it).z()<=0)
		{
			(*it).z() = - (*it).z();
			(*it).x() = - (*it).x();
			(*it).y() = - (*it).y();
		}
	}

	//--------------------------
	// create a noise texture
	//--------------------------
	//Texture coordinates
	osg::ref_ptr<osg::Vec2Array> texCoords = new osg::Vec2Array;

	//calculate the size of the heightfield
	double sizeX=fabs(mBoundEast-mBoundWest), sizeY=fabs(mBoundNorth-mBoundSouth); 
	//set the number of tiles of the texture
	double tileX=120, tileY=120;
	//calculate the tiling coefficient
	double tileCoefX=sizeX/tileX, tileCoefY=sizeY/tileY;
	double xc, yc;	//texture coord values based on the vertex coords
	for (osg::Vec3Array::iterator itr=vertices->begin(); itr!=vertices->end(); itr++) 
	{
		xc=(*itr).x()-mBoundWest;		//subtract the bound values in order to compensate for the vertex translated position
		yc=(*itr).y()-mBoundSouth;		//so that the texture coordinate 0,0 is the heightfield's corner and 1,1 the opposite corner
		osg::Vec2 tcatxy(xc/tileCoefX,yc/tileCoefY);
		texCoords->push_back(tcatxy);
	}
	geometry->setTexCoordArray( 0, texCoords.get() );

	//create a material
	osg::ref_ptr<osg::Material> material = new osg::Material; 
	//material->setEmission(osg::Material::FRONT, osg::Vec4(.5,0.5,0.5,1.));

	//set colors
	osg::Vec4Array* colors = new osg::Vec4Array(1);
	colors->push_back(osg::Vec4(1,1,1,1));
	geometry->setColorArray(colors);
	geometry->setColorBinding(osg::Geometry::BIND_OVERALL);

	// load image for texture
	osg::Image *image = osgDB::readImageFile("Resources/grass.jpg");
	if (!image) 
	{
		//std::cout << "Couldn't load texture." << std::endl;
		image = osgDB::readImageFile("Resources/noTexture.jpg");
		osg::notify(osg::WARN) << "Couldn't load texture, loading default image file"  << std::endl;
		if (!image) 
		{
			osg::notify(osg::WARN) << "Couldn't load default texture"  << std::endl;
			return geode.get();
		}
	}
	osg::ref_ptr<osg::Texture2D> texture = new osg::Texture2D;
	texture->setDataVariance(osg::Object::DYNAMIC);
	texture->setFilter(osg::Texture::MIN_FILTER, osg::Texture::LINEAR_MIPMAP_LINEAR);
	texture->setFilter(osg::Texture::MAG_FILTER, osg::Texture::LINEAR);
	texture->setWrap(osg::Texture::WRAP_S, osg::Texture::REPEAT);
	texture->setWrap(osg::Texture::WRAP_T, osg::Texture::REPEAT);
	texture->setImage(image);

	// assign the texture
	osg::StateSet * stateset = geometry->getOrCreateStateSet();
	stateset->setTextureAttributeAndModes(0, texture, osg::StateAttribute::ON);
	stateset->setAttributeAndModes( material, 	osg::StateAttribute::ON);
	stateset->setMode(GL_LIGHTING, osg::StateAttribute::ON);


	//---------------------------------------------------------------
	//create another texture with detailed terrain (terrain texture)
	//---------------------------------------------------------------

	//Texture coordinates
	osg::ref_ptr<osg::Vec2Array> texCoords2 = new osg::Vec2Array;

	tileX=1, tileY=1;
	//calculate the tiling coefficient
	tileCoefX=sizeX/tileX, tileCoefY=sizeY/tileY;

	for (osg::Vec3Array::iterator itr=vertices->begin(); itr!=vertices->end(); itr++) 
	{	
		xc=(*itr).x()-mBoundWest;		//subtract the bound values in order to compensate for the vertex translated position
		yc=(*itr).y()-mBoundSouth;		//so that the texture coordinate 0,0 is the heightfield's corner and 1,1 the opposite corner
		osg::Vec2 tcatxy(xc/tileCoefX,yc/tileCoefY);
		texCoords2->push_back(tcatxy);
	}
	geometry->setTexCoordArray( 1, texCoords2.get() );


	// load image for texture
	osg::Image *image2 = osgDB::readImageFile(terrainFile);
	if (!image2) 
	{
		//std::cout << "Couldn't load texture." << std::endl;
		image2 = osgDB::readImageFile("Resources/terrain.jpg");

		osg::notify(osg::WARN) << "Couldn't load texture, loading default image file."  << std::endl;

		if (!image2) 
		{
			osg::notify(osg::WARN) << "Couldn't load texture."  << std::endl;
			return geode.get();
		}
	}
	osg::ref_ptr<osg::Texture2D> texture2 = new osg::Texture2D;
	texture2->setDataVariance(osg::Object::DYNAMIC);
	texture2->setWrap(osg::Texture::WRAP_S, osg::Texture::REPEAT);
	texture2->setWrap(osg::Texture::WRAP_T, osg::Texture::REPEAT);
	texture2->setImage(image2);
	stateset->setTextureAttributeAndModes(1, texture2, osg::StateAttribute::ON);

	return geode.get();
}
//------------


/**
* Generate the heightfield from the provided heightmap texture.
* @param heightMapFile Texture file with heightmap data
* @param resolutionX, resolutionY Resolution of the heightmap mesh (number of collumns and rows)
* @param heightMultiplier Used to scale the normalized height values read from the heightmap
* @param averageElevation Used to shift the landscape vertically according to the road, if needed.
*/

void OSGScenery::GenerateHeightField(std::string heightMapFile,int resolutionX, int resolutionY, double heightMultiplier, double averageElevation)
{


	//read the heightmap file
	osg::ref_ptr<osg::Image> heightMapImage = osgDB::readImageFile(heightMapFile);
	if (!heightMapImage) 
	{
		//read the default image
		osg::notify(osg::WARN) << "Couldn't load texture, loading default image file."  << std::endl;
		heightMapImage = osgDB::readImageFile("Resources/heightmap.jpg");
		if (!heightMapImage) 
		{
			osg::notify(osg::WARN) << "Couldn't load texture."  << std::endl;
			return;
		}
	}

	mHeightField = new osg::Geode;
	//get image width and height
	int imgWidth=heightMapImage->s();
	int  imgHeight = heightMapImage->t();

	//calculate the width and height of the terrain using its bound values
	float width=fabs(mBoundWest-mBoundEast);
	float height = fabs(mBoundNorth-mBoundSouth);

	//calculate the step/interval
	float stepX = width/(float)resolutionX;
	float stepY = height/(float)resolutionY;

	//texture step
	float mapStepX = (float)(imgWidth-1)/(float)(resolutionX);
	float mapStepY = (float)(imgHeight-1)/(float)(resolutionY);

	osg::ref_ptr<osg::Geometry> heightFieldGeometry=new osg::Geometry;
	osg::ref_ptr<osg::Vec3Array> vertices=new osg::Vec3Array;

	double dataV;
	int coordX, coordY;
	for (int c = 0; c < resolutionX; c++) 
	{
		if (c%2==0)
		{
			//The image has lower left origin
			//We start from it's top and move down
			for (int r = resolutionY; r >= 0; r--) 
			{
				coordX=(int)floor(c*mapStepX);
				coordY=(int)floor(r*mapStepY);
				dataV=heightMapImage->getColor(coordX,coordY).r() * heightMultiplier + averageElevation;
				vertices->push_back(osg::Vec3 (mBoundWest+c*stepX, mBoundSouth+r*stepY, dataV));

				coordX=(int)floor((c+1)*mapStepX);
				dataV=heightMapImage->getColor(coordX,coordY).r() * heightMultiplier + averageElevation;
				vertices->push_back(osg::Vec3 (mBoundWest+(c+1)*stepX, mBoundSouth+r*stepY, dataV));
			}
			//add one more vertex at same position to create a degenerate triangle
			coordX=(int)floor((c+1)*mapStepX);
			dataV=heightMapImage->getColor(coordX,coordY).r() * heightMultiplier + averageElevation;
			vertices->push_back(osg::Vec3 (mBoundWest+(c+1)*stepX, mBoundSouth,dataV ));
		}
		else
		{
			//Move up
			for (int r = 0; r <= resolutionY; r++) 
			{
				coordX=(int)floor(c*mapStepX);
				coordY=(int)floor(r*mapStepY);
				//dataV=(*heightMapImage->data(c, r) / 255.0f) * heightMultiplier - averageElevation;
				dataV=heightMapImage->getColor(coordX,coordY).r() * heightMultiplier + averageElevation;
				vertices->push_back(osg::Vec3 (mBoundWest+c*stepX, mBoundSouth+r*stepY,dataV ));

				coordX=(int)floor((c+1)*mapStepX);
				dataV=heightMapImage->getColor(coordX,coordY).r() * heightMultiplier + averageElevation;
				vertices->push_back(osg::Vec3 (mBoundWest+(c+1)*stepX, mBoundSouth+r*stepY, dataV));

			}
			//add one more vertex at same position to create a degenerate triangle
			coordX=(int)floor((c+1)*mapStepX);
			dataV=heightMapImage->getColor(coordX,coordY).r() * heightMultiplier + averageElevation;
			vertices->push_back(osg::Vec3 (mBoundWest+(c+1)*stepX, mBoundSouth+(resolutionY)*stepY,dataV ));

		}	
	}

	heightFieldGeometry->setVertexArray(vertices.get());
	heightFieldGeometry->addPrimitiveSet(new osg::DrawArrays(osg::PrimitiveSet::TRIANGLE_STRIP,0,vertices.get()->size()));


	osg::ref_ptr<osg::Vec4Array> colors = new osg::Vec4Array;
	colors->push_back(osg::Vec4(1.0f,1.0f,0.0f,1.0f));
	heightFieldGeometry->setColorArray(colors.get());
	heightFieldGeometry->setColorBinding(osg::Geometry::BIND_OVERALL);

	heightFieldGeometry->getOrCreateStateSet()->setMode(GL_LIGHTING, osg::StateAttribute::OFF);
	heightFieldGeometry->getOrCreateStateSet()->setAttribute( new osg::Point( 2.0f ),osg::StateAttribute::ON );


	mHeightField->addDrawable(heightFieldGeometry.get());

	//osgUtil::Simplifier simpl;
	//simpl.setSampleRatio(0.5f);
	//mHeightField->accept(simpl);
}


/**
* Return the geode that containsthe heightmap mesh.
* @return A ref_ptr to a geode that contains the heightmap mesh.
*/
osg::ref_ptr<osg::Geode> OSGScenery::GetHeightMap()
{
	return mHeightField.get();
}

/**
* Clear the geometries of the heightmap mesh
*/
void  OSGScenery::ClearHeightField()
{
	if(mHeightField!=NULL)
		mHeightField->removeDrawables(0, mHeightField->getNumDrawables());
}