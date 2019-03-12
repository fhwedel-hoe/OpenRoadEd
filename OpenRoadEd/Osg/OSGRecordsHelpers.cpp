#include "OSGRecordsHelpers.h"
#include "OSGObjectNode.h"
#include <osg/Node>
#include <osg/Geode>
#include <osg/MatrixTransform>
#include <osg/Geometry>
#include <osgDB/ReadFile>
#include <osg/Texture2D>

#include "OSGConstants.h"

#define _USE_MATH_DEFINES
#include <math.h>
/**
* Records helpers class. Used to generate the geometry (billboards and other glyphs) to display the position and orientation of the various road records
*
*
*
*
*/
OSGRecordsHelpers::OSGRecordsHelpers()
{
	mSize=0.2;
	mOffset=0.2;
	mVerticalOffset=0.9;


	/**
	* Create a billboard node
	*/
	CreateBillboard();

	/**
	* Create an arrow 
	*/
	CreateArrow();
}


/**
* Create all the record helpers for a road
* @param road Pointer to an OpenDrive road object
* @param roadIndex of the road from the roads vector
* @param recordsHelpersGroup A OpenSceneGraph group where all the records for the current road should be added
*/
void OSGRecordsHelpers::FillHelperGroups (Road *road,unsigned int roadIndex, osg::Group* recordsHelpersGroup)
{
	osg::ref_ptr<osg::Group> group;


	if (roadIndex>=recordsHelpersGroup->getNumChildren())
	{
		group=new osg::Group;
		group->setName("Road");
		recordsHelpersGroup->addChild(group.get());
	}
	else
	{
		group=recordsHelpersGroup->getChild(roadIndex)->asGroup();
		group->removeChildren(0,group->getNumChildren());
	}

	mRoad=road;
	//=============================================================
	//Create the groups and add them to the recordsHelpersGroup
	//=============================================================
	osg::ref_ptr<osg::Group> mRoadTypeGroup=new osg::Group;
	mRoadTypeGroup->setName("mRoadTypeGroup");
	osg::ref_ptr<osg::Group> mGeometryBlockGroup=new osg::Group;
	mGeometryBlockGroup->setName ("mGeometryBlockGroup");
	osg::ref_ptr<osg::Group> mElevationGroup=new osg::Group;
	mElevationGroup->setName("mElevationGroup");
	osg::ref_ptr<osg::Group> mSuperElevationGroup=new osg::Group;
	mSuperElevationGroup->setName("mSuperElevationGroup");
	osg::ref_ptr<osg::Group> mCrossfallGroup=new osg::Group;
	mCrossfallGroup->setName("mCrossfallGroup");
	osg::ref_ptr<osg::Group> mLaneSectionGroup=new osg::Group;
	mLaneSectionGroup->setName("mLaneSectionGroup");

	osg::ref_ptr<osg::Group> mObjectGroup=new osg::Group;
	mObjectGroup->setName("mObjectGroup");
	osg::ref_ptr<osg::Group> mSignalGroup=new osg::Group;
	mSignalGroup->setName("mSignalGroup");

	group->addChild(mRoadTypeGroup);
	group->addChild(mGeometryBlockGroup);
	group->addChild(mElevationGroup);
	group->addChild(mSuperElevationGroup);
	group->addChild(mCrossfallGroup);
	group->addChild(mLaneSectionGroup);

	group->addChild(mObjectGroup);
	group->addChild(mSignalGroup);


	double tmpOffset=mOffset+mSize;
	double laneSectionOffset=0;
	osg::Vec4 leftColor;
	osg::Vec4 rightColor;
	osg::Vec4 centralColor;
	osg::Vec4 *currColor;
	centralColor.set(0.7f,0.7f,0.7f,1);
	rightColor.set(0.7f,0.0f,0.0f,1);
	leftColor.set(0.0f,0.0f,0.7f,1);
	currColor=&centralColor;

	std::string iconName;

	//=====================================================================
	//Go through all the elements of the road and add them to the subgroups
	//=====================================================================
	//Basic parameters
	for (unsigned int i = 0; i<road->GetRoadTypeCount(); i++)
	{
		iconName="Resources/Billboards/RoadType.jpg";
		mRoadTypeGroup->addChild(AddRecordHelper(road->GetRoadType(i)->GetS(),tmpOffset*7 ,0 ,ROAD_TYPE_NODE, iconName ).get());
	}

	for (unsigned int i = 0; i<road->GetGeometryBlockCount(); i++)
	{
		iconName="Resources/Billboards/Turn.jpg";
		mGeometryBlockGroup->addChild(AddRecordHelper(road->GetGeometryBlock(i)->GetGeometryAt(0)->GetS(),tmpOffset*6 ,0 ,GEOMETRY_BLOCK_NODE, iconName).get());
	}

	for (unsigned int i = 0; i<road->GetElevationCount(); i++)
	{
		iconName="Resources/Billboards/Elevation.jpg";
		mElevationGroup->addChild(AddRecordHelper(road->GetElevation(i)->GetS(),tmpOffset*5 ,0,ELEVATION_NODE,iconName).get());
	}

	for (unsigned int i = 0; i<road->GetSuperElevationCount(); i++)
	{
		iconName="Resources/Billboards/SuperElevation.jpg";
		mSuperElevationGroup->addChild(AddRecordHelper(road->GetSuperElevation(i)->GetS(),tmpOffset*4 ,0,SUPERELEVATION_NODE,iconName).get());
	}

	for (unsigned int i = 0; i<road->GetCrossfallCount(); i++)
	{
		iconName="Resources/Billboards/Crossfall.jpg";
		mCrossfallGroup->addChild(AddRecordHelper(road->GetCrossfall(i)->GetS(),tmpOffset*3 ,0,CROSSFALL_NODE,iconName).get());
	}

	//Lane sections
	for (unsigned int i = 0; i<road->GetLaneSectionCount(); i++)
	{
		iconName="Resources/Billboards/LaneSection.jpg";
		osg::ref_ptr<osg::Group> laneSection=new osg::Group;
		laneSection->setName("laneSection");
		mLaneSectionGroup->addChild(laneSection.get() );

		laneSection->addChild(AddRecordHelper(road->GetLaneSection(i)->GetS(),tmpOffset*2 ,0,LANE_SECTION_NODE,iconName).get());

		//add a group that will store all the lanes
		osg::ref_ptr<osg::Group> lanesGroup=new osg::Group;
		lanesGroup->setName("lanesGroup");
		laneSection->addChild(lanesGroup.get() );

		int laneNum=0;

		laneSectionOffset=road->GetLaneSection(i)->GetS();

		bool tmpCentralLane=false;
		//Lanes
		for (unsigned int j=0; j<road->GetLaneSection(i)->GetLaneCount(); j++)
		{
			Lane* lane=road->GetLaneSection(i)->GetLane(j);

			//create a lane group that will stor all lane params
			osg::ref_ptr<osg::Group> laneGroup=new osg::Group;
			laneGroup->setName("laneGroup");
			lanesGroup->addChild(laneGroup);

			//create all lane params
			osg::ref_ptr<osg::Group> laneWidthGroup=new osg::Group;
			laneWidthGroup->setName("laneWidthGroup");
			osg::ref_ptr<osg::Group> laneRoadMarkGroup=new osg::Group;
			laneRoadMarkGroup->setName("laneRoadMarkGroup");
			osg::ref_ptr<osg::Group> laneMaterialGroup=new osg::Group;
			laneMaterialGroup->setName("laneMaterialGroup");
			osg::ref_ptr<osg::Group> laneVisibilityGroup=new osg::Group;
			laneVisibilityGroup->setName("laneVisibilityGroup");
			osg::ref_ptr<osg::Group> laneSpeedGroup=new osg::Group;
			laneSpeedGroup->setName("laneSpeedGroup");
			osg::ref_ptr<osg::Group> laneAccessGroup=new osg::Group;
			laneAccessGroup->setName("laneAccessGroup");
			osg::ref_ptr<osg::Group> laneHeightGroup=new osg::Group;
			laneHeightGroup->setName("laneHeightGroup");

			laneGroup->addChild(laneWidthGroup);
			laneGroup->addChild(laneRoadMarkGroup);
			laneGroup->addChild(laneMaterialGroup);
			laneGroup->addChild(laneVisibilityGroup);
			laneGroup->addChild(laneSpeedGroup);
			laneGroup->addChild(laneAccessGroup);
			laneGroup->addChild(laneHeightGroup);


			if (lane->GetId()==0)
				currColor=&centralColor;
			else
				if (lane->GetId()>0)
					currColor=&leftColor;
				else
					currColor=&rightColor;

			//Width
			for (unsigned int k=0; k<lane->GetLaneWidthCount();k++)
			{

				iconName="Resources/Billboards/LaneWidth.jpg";
				laneWidthGroup->addChild(AddRecordHelper(lane->GetLaneWidth(k)->GetS()+laneSectionOffset,tmpOffset*1 ,tmpOffset*j,LANE_WIDTH_NODE,iconName,currColor));
			}

			//Road Mark
			for (unsigned int k=0; k<lane->GetLaneRoadMarkCount();k++)
			{
				iconName="Resources/Billboards/LaneRoadMark.jpg";
				laneRoadMarkGroup->addChild(AddRecordHelper(lane->GetLaneRoadMark(k)->GetS()+laneSectionOffset,tmpOffset*0 ,tmpOffset*j,LANE_ROAD_MARK_NODE,iconName,currColor));
			}
			//Lane Material
			for (unsigned int k=0; k<lane->GetLaneMaterialCount();k++)
			{
				iconName="Resources/Billboards/LaneMaterial.jpg";
				laneMaterialGroup->addChild(AddRecordHelper(lane->GetLaneMaterial(k)->GetS()+laneSectionOffset,tmpOffset*-1 ,tmpOffset*j,LANE_MATERIAL_NODE,iconName,currColor));
			}
			//Lane Visibility
			for (unsigned int k=0; k<lane->GetLaneVisibilityCount();k++)
			{
				iconName="Resources/Billboards/LaneVisibility.jpg";
				laneVisibilityGroup->addChild(AddRecordHelper(lane->GetLaneVisibility(k)->GetS()+laneSectionOffset,tmpOffset*-2 ,tmpOffset*j,LANE_VISIBILITY_NODE,iconName,currColor));
			}
			//Lane Speed
			for (unsigned int k=0; k<lane->GetLaneSpeedCount();k++)
			{
				iconName="Resources/Billboards/LaneSpeed.jpg";
				laneSpeedGroup->addChild(AddRecordHelper(lane->GetLaneSpeed(k)->GetS()+laneSectionOffset,tmpOffset*-3 ,tmpOffset*j,LANE_SPEED_NODE,iconName,currColor));
			}
			//Lane Access
			for (unsigned int k=0; k<lane->GetLaneAccessCount();k++)
			{			
				iconName="Resources/Billboards/LaneAccess.jpg";
				laneAccessGroup->addChild(AddRecordHelper(lane->GetLaneAccess(k)->GetS()+laneSectionOffset,tmpOffset*-4 ,tmpOffset*j,LANE_ACCESS_NODE,iconName,currColor));
			}
			//Lane Height
			for (unsigned int k=0; k<lane->GetLaneHeightCount();k++)
			{
				iconName="Resources/Billboards/LaneHeight.jpg";
				laneHeightGroup->addChild(AddRecordHelper(lane->GetLaneHeight(k)->GetS()+laneSectionOffset,tmpOffset*-5 ,tmpOffset*j,LANE_HEIGHT_NODE,iconName,currColor));
			}
			laneNum++;
		}		
	}
	////Objects and Signals
	//for (unsigned int i = 0; i<road->GetObjectCount(); i++)
	//{
	//	iconName="Resources/Billboards/Object.jpg";
	//	mObjectGroup->addChild(AddRecordHelper(road->GetObject(i)->GetS(),tmpOffset*-6 ,0,OBJECT_NODE,iconName).get()));
	//}
	//
	//for (unsigned int i = 0; i<road->GetSignalCount(); i++)
	//{
	//	iconName="Resources/Billboards/Signal.jpg";
	//	mSignalGroup->addChild(AddRecordHelper(road->GetSignal(i)->GetS(),tmpOffset*-7 ,0,SIGNAL_NODE,iconName).get()));
	//}
}

/**
* Create the geometry for a helper and return the matrix transform that translates the helper according to its type
* @param s s-offset of the record helpers along the road
* @param offsetX Translation in the x direction
* @param offsetZ Translation in the vertical direction. Used for lane records in order to allow multiple lane parameters to be displayed simultaneously
* @param type Type of the helper to be created (based on the record type)
* @param iconName Filename (with path) of the icon to be rendered on the billboard
* @param color Color of the glyph. Used to distinguish between the left and right lane records
*/
osg::ref_ptr<osg::MatrixTransform> OSGRecordsHelpers::AddRecordHelper(double s, double offsetX,double offsetZ, OSGNodeType type,
																	  std::string iconName, osg::Vec4* color)
{
	osg::ref_ptr<osg::MatrixTransform> matrix =	new osg::MatrixTransform;
	matrix->setName("RecordMatrix");


	//Get the coords and the heading for the current record
	double x,y,hdg,elevation;
	short int resultID=mRoad->GetGeometryCoords(s,x,y,hdg);

	if (resultID==-999)
		return matrix;

	elevation=mRoad->GetElevationValue(s);


	//=========================================================
	//Ad an arrow
	//=========================================================
	osg::ref_ptr<OSGGeodeNode> arrowGeode = new OSGGeodeNode();
	osg::ref_ptr<osg::Geometry> arrowGeom=new osg::Geometry;
	arrowGeom->setUseDisplayList( false );

	arrowGeode->addDrawable(arrowGeom);
	arrowGeom->setVertexArray( mArrowVertices.get() );
	arrowGeom->addPrimitiveSet(mArrowTris.get());

	osg::ref_ptr<osg::Vec4Array> colors = new osg::Vec4Array;
	arrowGeom->setColorArray(colors.get());
	arrowGeom->setColorBinding(osg::Geometry::BIND_OVERALL);
	if (color!=NULL)
	{
		colors->push_back(*color);
	}
	else
		colors->push_back(osg::Vec4(0.8f, 0.8f,  0.8f, 1.0f) );

	arrowGeom->getOrCreateStateSet()->setMode(GL_LIGHTING, osg::StateAttribute::OFF);


	arrowGeode->SetNodeType(type);


	//=========================================================
	//Now, add a billboard with the texture of the needed type
	//=========================================================
	osg::ref_ptr<OSGBillboardNode> billboardIcon = new OSGBillboardNode;

	billboardIcon->SetNodeType(type);

	billboardIcon->addDrawable(mBillboard);
	billboardIcon->setMode(osg::Billboard::POINT_ROT_EYE);
	billboardIcon->setNormal(osg::Vec3(0.0f,-1.0f,0.0f));


	osg::StateSet* stateSet= billboardIcon->getOrCreateStateSet();
	// create a texture
	// load image for texture
	osg::Image *billboardIconImage = osgDB::readImageFile(iconName);
	if (!billboardIconImage) 
	{
		billboardIconImage = osgDB::readImageFile("Resources/noTexture.jpg");
		if (!billboardIconImage) 
		{
			return matrix.get();
		}
	}
	osg::ref_ptr<osg::Texture2D> roadTexture = new osg::Texture2D;
	roadTexture->setDataVariance(osg::Object::DYNAMIC);
	roadTexture->setWrap(osg::Texture::WRAP_S, osg::Texture::REPEAT);
	roadTexture->setWrap(osg::Texture::WRAP_T, osg::Texture::REPEAT);
	roadTexture->setImage(billboardIconImage);

	// assign the material and texture
	stateSet->setTextureAttributeAndModes(0, roadTexture, osg::StateAttribute::ON);
	//stateSet->setMode(GL_DEPTH_TEST,osg::StateAttribute::OFF);


	//===========================================================================================
	//in order to translate the helper orthogonally to the heading, compute the cos and sin
	//===========================================================================================
	double difX=cos(hdg+M_PI_2)*offsetX;
	double difY=sin(hdg+M_PI_2)*offsetX;

	double dif2X=cos(hdg)*mSize;
	double dif2Y=sin(hdg)*mSize;

	matrix->setMatrix(	osg::Matrix::rotate(osg::inRadians(hdg-M_PI_2), osg::Vec3(0.0, 0.0, 1.0)) *
		//osg::Matrix::translate(osg::Vec3(x+difX,y+difY,elevation+ROADMARK_ELEVATION_SHIFT+mVerticalOffset+offsetZ))	);
		osg::Matrix::translate(osg::Vec3(x+difX+dif2X,y+difY+dif2Y,elevation+ROADMARK_ELEVATION_SHIFT+mVerticalOffset+offsetZ))	);


	matrix->addChild(arrowGeode);
	matrix->addChild(billboardIcon);

	return matrix;
}

//--------------


void OSGRecordsHelpers::CreateBillboard()
{
	mBillboard = new osg::Geometry();
	//arrays for vertices
	osg::ref_ptr<osg::Vec3Array> vertices = new osg::Vec3Array;
	mBillboard->setVertexArray( vertices.get() );
	osg::ref_ptr<osg::Vec2Array> texCoords = new osg::Vec2Array;
	mBillboard->setTexCoordArray( 0, texCoords.get() );
	osg::ref_ptr<osg::Vec4Array> colors = new osg::Vec4Array;
	colors->push_back(osg::Vec4(1,1,1,1));
	mBillboard->setColorArray( colors.get() );
	mBillboard->setColorBinding(osg::Geometry::BIND_OVERALL);

	double halfSize=mSize/2;

	vertices->push_back(osg::Vec3(-halfSize,0,-halfSize));
	texCoords->push_back(osg::Vec2(0,0));
	vertices->push_back(osg::Vec3(halfSize,0,-halfSize));
	texCoords->push_back(osg::Vec2(1,0));
	vertices->push_back(osg::Vec3(halfSize,0,halfSize));
	texCoords->push_back(osg::Vec2(1,1));
	vertices->push_back(osg::Vec3(-halfSize,0,halfSize));
	texCoords->push_back(osg::Vec2(0,1));

	//lines
	osg::ref_ptr<osg::DrawArrays> quad = new osg::DrawArrays(osg::PrimitiveSet::QUADS, 0, vertices.get()->size());
	mBillboard->addPrimitiveSet(quad.get());	


	mBillboard->getOrCreateStateSet()->setMode(GL_LIGHTING, osg::StateAttribute::OFF);

}


void OSGRecordsHelpers::CreateArrow()
{
	mArrowVertices=new osg::Vec3Array;
	mArrowTris = new osg::DrawElementsUInt(osg::PrimitiveSet::TRIANGLES, 0);

	//array  for colors
	double halfSize=mSize/2;
	double quarterSize=halfSize/2;
	double yOffset=halfSize;
	//=======================
	//add the arrow vertices
	//=======================
	//bottom part
	mArrowVertices->push_back(osg::Vec3(-quarterSize,yOffset,quarterSize));
	mArrowVertices->push_back(osg::Vec3(quarterSize,yOffset,quarterSize));
	mArrowVertices->push_back(osg::Vec3(quarterSize,2*halfSize+yOffset,quarterSize));
	mArrowVertices->push_back(osg::Vec3(-quarterSize,2*halfSize+yOffset,quarterSize));
	//sides
	mArrowVertices->push_back(osg::Vec3(-halfSize,2*halfSize+yOffset,quarterSize));
	mArrowVertices->push_back(osg::Vec3(halfSize,2*halfSize+yOffset,quarterSize));
	//tip
	mArrowVertices->push_back(osg::Vec3(0,halfSize*5+yOffset,quarterSize));

	//Same for the back face
	//-------------------------------
	//bottom part
	mArrowVertices->push_back(osg::Vec3(-quarterSize,yOffset,0));
	mArrowVertices->push_back(osg::Vec3(quarterSize,yOffset,0));
	mArrowVertices->push_back(osg::Vec3(quarterSize,2*halfSize+yOffset,0));
	mArrowVertices->push_back(osg::Vec3(-quarterSize,2*halfSize+yOffset,0));
	//sides
	mArrowVertices->push_back(osg::Vec3(-halfSize,2*halfSize+yOffset,0));
	mArrowVertices->push_back(osg::Vec3(halfSize,2*halfSize+yOffset,0));
	//tip
	mArrowVertices->push_back(osg::Vec3(0,halfSize*5+yOffset,0));


	//=======================
	//add the arrow triangles
	//=======================

	//Front face
	//----------------------------
	mArrowTris->push_back(0);
	mArrowTris->push_back(1);
	mArrowTris->push_back(2);

	mArrowTris->push_back(0);
	mArrowTris->push_back(2);
	mArrowTris->push_back(3);

	mArrowTris->push_back(4);
	mArrowTris->push_back(3);
	mArrowTris->push_back(6);

	mArrowTris->push_back(3);
	mArrowTris->push_back(2);
	mArrowTris->push_back(6);

	mArrowTris->push_back(2);
	mArrowTris->push_back(5);
	mArrowTris->push_back(6);




	//Back face
	//----------------------------
	mArrowTris->push_back(7);
	mArrowTris->push_back(8);
	mArrowTris->push_back(9);

	mArrowTris->push_back(7);
	mArrowTris->push_back(9);
	mArrowTris->push_back(10);

	mArrowTris->push_back(11);
	mArrowTris->push_back(10);
	mArrowTris->push_back(13);

	mArrowTris->push_back(10);
	mArrowTris->push_back(9);
	mArrowTris->push_back(13);

	mArrowTris->push_back(9);
	mArrowTris->push_back(12);
	mArrowTris->push_back(13);


	//left faces
	//----------------------------
	mArrowTris->push_back(1);
	mArrowTris->push_back(8);
	mArrowTris->push_back(9);

	mArrowTris->push_back(1);
	mArrowTris->push_back(9);
	mArrowTris->push_back(2);

	mArrowTris->push_back(2);
	mArrowTris->push_back(9);
	mArrowTris->push_back(12);

	mArrowTris->push_back(2);
	mArrowTris->push_back(12);
	mArrowTris->push_back(5);

	mArrowTris->push_back(5);
	mArrowTris->push_back(12);
	mArrowTris->push_back(13);

	mArrowTris->push_back(5);
	mArrowTris->push_back(13);
	mArrowTris->push_back(6);


	//Right faces
	//----------------------------
	mArrowTris->push_back(6);
	mArrowTris->push_back(13);
	mArrowTris->push_back(11);

	mArrowTris->push_back(6);
	mArrowTris->push_back(11);
	mArrowTris->push_back(4);

	mArrowTris->push_back(4);
	mArrowTris->push_back(11);
	mArrowTris->push_back(9);

	mArrowTris->push_back(4);
	mArrowTris->push_back(10);
	mArrowTris->push_back(3);

	mArrowTris->push_back(3);
	mArrowTris->push_back(10);
	mArrowTris->push_back(7);

	mArrowTris->push_back(3);
	mArrowTris->push_back(7);
	mArrowTris->push_back(0);


	//bottom face
	//----------------------------
	mArrowTris->push_back(0);
	mArrowTris->push_back(7);
	mArrowTris->push_back(8);

	mArrowTris->push_back(0);
	mArrowTris->push_back(8);
	mArrowTris->push_back(1);


}