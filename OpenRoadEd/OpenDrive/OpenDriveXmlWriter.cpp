#include "OpenDriveXmlWriter.h"
#include <iostream>
#include <algorithm>
#include "windows.h"

using std::cout;
using std::endl;

/**
 * Constructor which saves a reference to OpenDrive structure
 */
OpenDriveXmlWriter::OpenDriveXmlWriter (OpenDrive* openDriveObj)
{	
	mOpenDrive=openDriveObj;	
}

/**
 * The following methods are used to create the XML representation of the OpenDrive structure
 * Methods follow the same hierarchical structure and are called automatically when WriteFile
 * is executed
 */
bool OpenDriveXmlWriter::WriteHeader(TiXmlElement *node)
{
	//Write the Header
	unsigned short int revMajor;
	unsigned short int revMinor;
	string name;
	float version;
	string date;
	double north;
	double south;
	double east;
	double west;

	Header *lHeader = mOpenDrive->GetHeader();
	lHeader->GetAllParams(revMajor, revMinor, name, version, date, north, south, east, west);

	TiXmlElement *nodeHeader = new TiXmlElement("header");
	node->LinkEndChild(nodeHeader);

	nodeHeader->SetAttribute("revMajor",revMajor);
	nodeHeader->SetAttribute("revMinor",revMinor);
	nodeHeader->SetAttribute("name",name);
	nodeHeader->SetDoubleAttribute("version",version);
	nodeHeader->SetAttribute("date",date);

	std::stringstream snorth;
	snorth << setprecision(16) << setiosflags (ios_base::scientific) << north;
	nodeHeader->SetAttribute("north",snorth.str());

	std::stringstream ssouth;
	ssouth << setprecision(16) << setiosflags (ios_base::scientific) << south;
	nodeHeader->SetAttribute("south",ssouth.str());

	std::stringstream seast;
	seast << setprecision(16) << setiosflags (ios_base::scientific) << east;
	nodeHeader->SetAttribute("east",seast.str());

	std::stringstream swest;
	swest << setprecision(16) << setiosflags (ios_base::scientific) << west;
	nodeHeader->SetAttribute("west",swest.str());


	return true;
}
//--------------
bool OpenDriveXmlWriter::WriteRoad(TiXmlElement *node, Road *road)
{
	//Write road attributes
	string name;
	double length;
	string id;
	string junction;

	name = road->GetRoadName();
	length = road->GetRoadLength();
	id = road->GetRoadId();
	junction = road->GetRoadJunction();

	TiXmlElement *nodeRoad = new TiXmlElement("road");
	node->LinkEndChild(nodeRoad);

	nodeRoad->SetAttribute("name",name);
	std::stringstream slength;
	slength << setprecision(16) << setiosflags (ios_base::scientific) << length;
	nodeRoad->SetAttribute("length",slength.str());
	nodeRoad->SetAttribute("id",id);
	nodeRoad->SetAttribute("junction",junction);

	//Fill in

	//Links
	WriteRoadLinks (nodeRoad,road);

	//Types
	WriteRoadType(nodeRoad, road);

	//PlanView
	WritePlanView(nodeRoad, road);

	//ElevationProfile
	WriteElevationProfile(nodeRoad, road);

	//LateralProfile
	WriteLateralProfile(nodeRoad, road);

	//Proceed to Lanes
	WriteLanes(nodeRoad, road);


	//Proceed to Objects
	WriteObjects(nodeRoad, road);

	//Proceed to Signals
	WriteSignals(nodeRoad, road);

	/*
	//Proceed to Surface
	subNode=node->FirstChildElement("surface");
	if (subNode)
	{
	WriteSurface(road, subNode);
	}
	*/

	return true;
}
//--------------

bool  OpenDriveXmlWriter::WriteRoadLinks (TiXmlElement *node, Road* road)
{
	TiXmlElement* nodeLink = new TiXmlElement("link");
	node->LinkEndChild(nodeLink);

	RoadLink *lPredecessor = road->GetPredecessor();
	if(lPredecessor)
	{
		TiXmlElement* nodeLinkPredecessor = new TiXmlElement("predecessor");
		nodeLink->LinkEndChild(nodeLinkPredecessor);
		nodeLinkPredecessor->SetAttribute("elementType", lPredecessor->GetElementType());
		nodeLinkPredecessor->SetAttribute("elementId", lPredecessor->GetElementId());
		nodeLinkPredecessor->SetAttribute("contactPoint", lPredecessor->GetContactPoint());
	}
	RoadLink *lSuccessor = road->GetSuccessor();
	if(lSuccessor)
	{
		TiXmlElement* nodeLinkSuccessor = new TiXmlElement("successor");
		nodeLink->LinkEndChild(nodeLinkSuccessor);
		nodeLinkSuccessor->SetAttribute("elementType", lSuccessor->GetElementType());
		nodeLinkSuccessor->SetAttribute("elementId", lSuccessor->GetElementId());
		nodeLinkSuccessor->SetAttribute("contactPoint", lSuccessor->GetContactPoint());
	}
	RoadNeighbor *lNeighbor1 = road->GetNeighbor1();
	if(lNeighbor1)
	{
		TiXmlElement* nodeLinkNeighbor1 = new TiXmlElement("neighbor");
		nodeLink->LinkEndChild(nodeLinkNeighbor1);
		nodeLinkNeighbor1->SetAttribute("side", lNeighbor1->GetSide());
		nodeLinkNeighbor1->SetAttribute("elementId", lNeighbor1->GetElementId());
		nodeLinkNeighbor1->SetAttribute("direction", lNeighbor1->GetDirection());
	}
	RoadNeighbor *lNeighbor2 = road->GetNeighbor2();
	if(lNeighbor2)
	{
		TiXmlElement* nodeLinkNeighbor2 = new TiXmlElement("neighbor");
		nodeLink->LinkEndChild(nodeLinkNeighbor2);
		nodeLinkNeighbor2->SetAttribute("side", lNeighbor2->GetSide());
		nodeLinkNeighbor2->SetAttribute("elementId", lNeighbor2->GetElementId());
		nodeLinkNeighbor2->SetAttribute("direction", lNeighbor2->GetDirection());
	}

	return true;
}
//--------------

bool OpenDriveXmlWriter::WriteRoadType (TiXmlElement *node, Road* road)
{
	double s;
	string type;

	unsigned int roadTypeCount = road->GetRoadTypeCount();
	for(unsigned int i=0; i<roadTypeCount; i++)
	{
		RoadType *lRoadType = road->GetRoadType(i);

		s=lRoadType->GetS();
		type=lRoadType->GetType();

		TiXmlElement *nodeRoadType = new TiXmlElement("type");
		node->LinkEndChild(nodeRoadType);

		std::stringstream ss;
		ss << setprecision(16) << setiosflags (ios_base::scientific) << s;
		nodeRoadType->SetAttribute("s",ss.str());
		nodeRoadType->SetAttribute("type",type);
	}

	return true;
}
//--------------

bool OpenDriveXmlWriter::WritePlanView(TiXmlElement *node, Road *road)
{
	TiXmlElement* nodePlanView = new TiXmlElement("planView");
	node->LinkEndChild(nodePlanView);

	unsigned int geometryCount = road->GetGeometryBlockCount();
	for(unsigned int i=0; i<geometryCount; i++)
	{
		WriteGeometryBlock(nodePlanView, road->GetGeometryBlock(i));
	}

	return true;
}
//--------------

bool OpenDriveXmlWriter::WriteGeometryBlock (TiXmlElement *node, GeometryBlock* geometryBlock)
{
	if(geometryBlock->CheckIfLine())
	{
		WriteGeometry(node, geometryBlock->GetGeometryAt(0), 0);
	}
	else
	{
		WriteGeometry(node, geometryBlock->GetGeometryAt(0), 1);
		WriteGeometry(node, geometryBlock->GetGeometryAt(1), 2);
		WriteGeometry(node, geometryBlock->GetGeometryAt(2), 1);
	}

	return true;
}
//--------------

bool OpenDriveXmlWriter::WriteGeometry(TiXmlElement *node, RoadGeometry* roadGeometry,  short int geometryType)
{
	double s, x, y, hdg, length;

	s=roadGeometry->GetS();
	x=roadGeometry->GetX();
	y=roadGeometry->GetY();
	hdg=roadGeometry->GetHdg();
	length=roadGeometry->GetLength();

	//Write the geometry node
	TiXmlElement *nodeGeometry = new TiXmlElement("geometry");
	node->LinkEndChild(nodeGeometry);

	std::stringstream ss;
	ss << setprecision(16) << setiosflags (ios_base::scientific) << s;
	nodeGeometry->SetAttribute("s",ss.str());

	std::stringstream sx;
	sx << setprecision(16) << setiosflags (ios_base::scientific) << x;
	nodeGeometry->SetAttribute("x",sx.str());

	std::stringstream sy;
	sy << setprecision(16) << setiosflags (ios_base::scientific) << y;
	nodeGeometry->SetAttribute("y",sy.str());

	std::stringstream shdg;
	shdg << setprecision(16) << setiosflags (ios_base::scientific) << hdg;
	nodeGeometry->SetAttribute("hdg",shdg.str());

	std::stringstream slength;
	slength << setprecision(16) << setiosflags (ios_base::scientific) << length;
	nodeGeometry->SetAttribute("length",slength.str());


	//Write the type nodes
	switch ( geometryType )
	{
	case 0:	
		{
			//line
			TiXmlElement *nodeLine = new TiXmlElement("line");
			nodeGeometry->LinkEndChild(nodeLine);
			break;
		}
	case 1:
		{		
			//spiral
			double curvatureStart, curvatureEnd; 
			GeometrySpiral *lSpiral=static_cast<GeometrySpiral*>(roadGeometry);
			curvatureStart=lSpiral->GetCurvatureStart();
			curvatureEnd=lSpiral->GetCurvatureEnd();

			TiXmlElement *nodeSpiral = new TiXmlElement("spiral");
			nodeGeometry->LinkEndChild(nodeSpiral);


			std::stringstream scurvatureStart;
			scurvatureStart << setprecision(16) << setiosflags (ios_base::scientific) << curvatureStart;
			nodeSpiral->SetAttribute("curvStart",scurvatureStart.str());

			std::stringstream scurvatureEnd;
			scurvatureEnd << setprecision(16) << setiosflags (ios_base::scientific) << curvatureEnd;
			nodeSpiral->SetAttribute("curvEnd",scurvatureEnd.str());
			break;
		}
	case 2:
		{		
			//arc
			double curvature;
			GeometryArc *lArc=static_cast<GeometryArc*>(roadGeometry);
			curvature=lArc->GetCurvature();

			TiXmlElement *nodeArc = new TiXmlElement("arc");
			nodeGeometry->LinkEndChild(nodeArc);

			std::stringstream scurvature;
			scurvature << setprecision(16) << setiosflags (ios_base::scientific) << curvature;
			nodeArc->SetAttribute("curvature",scurvature.str());
			break;
		}
	case 3:
		{		
			//poly3
			break;
		}
	}

	return true;
}
//--------------

bool OpenDriveXmlWriter::WriteElevationProfile (TiXmlElement *node, Road* road)
{
	double s, a, b, c, d;

	TiXmlElement* nodeElevationProfile = new TiXmlElement("elevationProfile");
	node->LinkEndChild(nodeElevationProfile);

	unsigned int lElevationCount = road->GetElevationCount();
	for(unsigned int i=0; i<lElevationCount; i++)
	{
		Elevation *lElevation = road->GetElevation(i);
		s=lElevation->GetS();
		a=lElevation->GetA();
		b=lElevation->GetB();
		c=lElevation->GetC();
		d=lElevation->GetD();

		TiXmlElement *nodeElevation = new TiXmlElement("elevation");
		nodeElevationProfile->LinkEndChild(nodeElevation);

		std::stringstream ss;
		ss << setprecision(16) << setiosflags (ios_base::scientific) << s;
		nodeElevation->SetAttribute("s",ss.str());

		std::stringstream sa;
		sa << setprecision(16) << setiosflags (ios_base::scientific) << a;
		nodeElevation->SetAttribute("a",sa.str());

		std::stringstream sb;
		sb << setprecision(16) << setiosflags (ios_base::scientific) << b;
		nodeElevation->SetAttribute("b",sb.str());

		std::stringstream sc;
		sc << setprecision(16) << setiosflags (ios_base::scientific) << c;
		nodeElevation->SetAttribute("c",sc.str());

		std::stringstream sd;
		sd << setprecision(16) << setiosflags (ios_base::scientific) << d;
		nodeElevation->SetAttribute("d",sd.str());
	}
	return true;
}
//--------------

bool OpenDriveXmlWriter::WriteLateralProfile (TiXmlElement *node, Road* road)
{
	double s, a, b, c, d;
	string side;

	TiXmlElement* nodeLateralProfile = new TiXmlElement("lateralProfile");
	node->LinkEndChild(nodeLateralProfile);

	unsigned int lSuperElevationCount = road->GetSuperElevationCount();
	for(unsigned int i=0; i<lSuperElevationCount; i++)
	{
		SuperElevation *lSuperElevation = road->GetSuperElevation(i);
		s=lSuperElevation->GetS();
		a=lSuperElevation->GetA();
		b=lSuperElevation->GetB();
		c=lSuperElevation->GetC();
		d=lSuperElevation->GetD();

		TiXmlElement *nodeSuperElevation = new TiXmlElement("superelevation");
		nodeLateralProfile->LinkEndChild(nodeSuperElevation);

		std::stringstream ss;
		ss << setprecision(16) << setiosflags (ios_base::scientific) << s;
		nodeSuperElevation->SetAttribute("s",ss.str());

		std::stringstream sa;
		sa << setprecision(16) << setiosflags (ios_base::scientific) << a;
		nodeSuperElevation->SetAttribute("a",sa.str());

		std::stringstream sb;
		sb << setprecision(16) << setiosflags (ios_base::scientific) << b;
		nodeSuperElevation->SetAttribute("b",sb.str());

		std::stringstream sc;
		sc << setprecision(16) << setiosflags (ios_base::scientific) << c;
		nodeSuperElevation->SetAttribute("c",sc.str());

		std::stringstream sd;
		sd << setprecision(16) << setiosflags (ios_base::scientific) << d;
		nodeSuperElevation->SetAttribute("d",sd.str());
	}


	unsigned int lCrossfallCount = road->GetCrossfallCount();
	for(unsigned int i=0; i<lCrossfallCount; i++)
	{
		Crossfall *lCrossfall = road->GetCrossfall(i);
		s=lCrossfall->GetS();
		a=lCrossfall->GetA();
		b=lCrossfall->GetB();
		c=lCrossfall->GetC();
		d=lCrossfall->GetD();
		side=lCrossfall->GetSide();

		TiXmlElement *nodeCrossfall = new TiXmlElement("crossfall");
		nodeLateralProfile->LinkEndChild(nodeCrossfall);

		nodeCrossfall->SetAttribute("side",side);

		std::stringstream ss;
		ss << setprecision(16) << setiosflags (ios_base::scientific) << s;
		nodeCrossfall->SetAttribute("s",ss.str());

		std::stringstream sa;
		sa << setprecision(16) << setiosflags (ios_base::scientific) << a;
		nodeCrossfall->SetAttribute("a",sa.str());

		std::stringstream sb;
		sb << setprecision(16) << setiosflags (ios_base::scientific) << b;
		nodeCrossfall->SetAttribute("b",sb.str());

		std::stringstream sc;
		sc << setprecision(16) << setiosflags (ios_base::scientific) << c;
		nodeCrossfall->SetAttribute("c",sc.str());

		std::stringstream sd;
		sd << setprecision(16) << setiosflags (ios_base::scientific) << d;
		nodeCrossfall->SetAttribute("d",sd.str());
	}

	return true;
}
//--------------

bool OpenDriveXmlWriter::WriteLanes (TiXmlElement *node, Road* road)
{
	TiXmlElement* nodeLanes = new TiXmlElement("lanes");
	node->LinkEndChild(nodeLanes);

	unsigned int lLaneSectionCount = road->GetLaneSectionCount();
	for(unsigned int i=0; i<lLaneSectionCount; i++)
	{
		WriteLaneSections(nodeLanes, road->GetLaneSection(i));
	}

	return true;
}
//--------------

bool OpenDriveXmlWriter::WriteLaneSections (TiXmlElement *node, LaneSection *laneSection)
{
	double s;
	s=laneSection->GetS();

	TiXmlElement* nodeLaneSection = new TiXmlElement("laneSection");
	node->LinkEndChild(nodeLaneSection);

	std::stringstream ss;
	ss << setprecision(16) << setiosflags (ios_base::scientific) << s;
	nodeLaneSection->SetAttribute("s",ss.str());

	//Fill in lane section
	short int curType=1;
	TiXmlElement* nodeLanesLeft=NULL;
	if(laneSection->GetLeftLaneCount()>0)
	{
		nodeLanesLeft = new TiXmlElement("left");
		nodeLaneSection->LinkEndChild(nodeLanesLeft);
	}
	
	TiXmlElement* nodeLanesCenter = new TiXmlElement("center");
	nodeLaneSection->LinkEndChild(nodeLanesCenter);

	TiXmlElement* nodeLanesRight=NULL;
	if(laneSection->GetRightLaneCount()>0)
	{
		nodeLanesRight = new TiXmlElement("right");
		nodeLaneSection->LinkEndChild(nodeLanesRight);
	}


	unsigned int lLaneCount = laneSection->GetLaneCount();
	for(unsigned int i=0; i<lLaneCount; i++)
	{
		Lane *lLane = laneSection->GetLane(i);
		short int lType=lLane->GetSide();
		if(lType>0 && nodeLanesLeft!=NULL)
		{
			WriteLane(nodeLanesLeft, lLane);
		}
		else if(lType==0)
		{
			WriteLane(nodeLanesCenter, lLane);
		}
		else if(lType<0 && nodeLanesRight!=NULL)
		{
			WriteLane(nodeLanesRight, lLane);
		}
	}

	return true;
}
//--------------

bool OpenDriveXmlWriter::WriteLane (TiXmlElement *node, Lane* lane)
{
	//Write Lane attributes
	int id;
	string type; 
	string level; 
	bool boolLevel;
	int predecessor;
	int successor;

	id=lane->GetId();
	type=lane->GetType();
	boolLevel=lane->GetLevel();
	if(boolLevel) level="true";
	else level="false";
	predecessor=lane->GetPredecessor();
	successor=lane->GetSuccessor();
	
	TiXmlElement* nodeLane = new TiXmlElement("lane");
	node->LinkEndChild(nodeLane);

	//Attributes
	nodeLane->SetAttribute("id",id);
	nodeLane->SetAttribute("type",type);
	nodeLane->SetAttribute("level",level);
	
	//Links
	TiXmlElement* nodeLaneLink = new TiXmlElement("link");
	nodeLane->LinkEndChild(nodeLaneLink);
	if(lane->IsPredecessorSet())
	{
		TiXmlElement* nodeLaneLinkPredecessor = new TiXmlElement("predecessor");
		nodeLaneLink->LinkEndChild(nodeLaneLinkPredecessor);
		nodeLaneLinkPredecessor->SetAttribute("id",predecessor);
	}
	if(lane->IsSuccessorSet())
	{
		TiXmlElement* nodeLaneLinkSuccessor = new TiXmlElement("successor");
		nodeLaneLink->LinkEndChild(nodeLaneLinkSuccessor);
		nodeLaneLinkSuccessor->SetAttribute("id",successor);
	}

	//Lane Width
	unsigned int lLaneWidthCount = lane->GetLaneWidthCount();
	for(unsigned int i=0; i<lLaneWidthCount; i++)
	{
		WriteLaneWidth(nodeLane, lane->GetLaneWidth(i));
	}

	//Lane Road Mark
	unsigned int lLaneRoadMark = lane->GetLaneRoadMarkCount();
	for(unsigned int i=0; i<lLaneRoadMark; i++)
	{
		WriteLaneRoadMark(nodeLane, lane->GetLaneRoadMark(i));
	}

	//Lane Material
	unsigned int lLaneMaterial = lane->GetLaneMaterialCount();
	for(unsigned int i=0; i<lLaneMaterial; i++)
	{
		WriteLaneMaterial(nodeLane, lane->GetLaneMaterial(i));
	}

	//Lane Visibility
	unsigned int lLaneVisibility = lane->GetLaneVisibilityCount();
	for(unsigned int i=0; i<lLaneVisibility; i++)
	{
		WriteLaneVisibility(nodeLane, lane->GetLaneVisibility(i));
	}

	//Lane speed
	unsigned int lLaneSpeed = lane->GetLaneSpeedCount();
	for(unsigned int i=0; i<lLaneSpeed; i++)
	{
		WriteLaneSpeed(nodeLane, lane->GetLaneSpeed(i));
	}

	//Lane access
	unsigned int lLaneAccess = lane->GetLaneAccessCount();
	for(unsigned int i=0; i<lLaneAccess; i++)
	{
		WriteLaneAccess(nodeLane, lane->GetLaneAccess(i));
	}

	//Lane height
	unsigned int lLaneHeight = lane->GetLaneHeightCount();
	for(unsigned int i=0; i<lLaneHeight; i++)
	{
		WriteLaneHeight(nodeLane, lane->GetLaneHeight(i));
	}

	return true;
}
//--------------


bool OpenDriveXmlWriter::WriteLaneWidth(TiXmlElement *node, LaneWidth* laneWidth)
{
	double sOffset, a, b, c, d;

	sOffset=laneWidth->GetS();
	a=laneWidth->GetA();
	b=laneWidth->GetB();
	c=laneWidth->GetC();
	d=laneWidth->GetD();

	TiXmlElement* nodeLaneWidth = new TiXmlElement("width");
	node->LinkEndChild(nodeLaneWidth);

	std::stringstream ssOffset;
	ssOffset << setprecision(16) << setiosflags (ios_base::scientific) << sOffset;
	nodeLaneWidth->SetAttribute("sOffset",ssOffset.str());

	std::stringstream sa;
	sa << setprecision(16) << setiosflags (ios_base::scientific) << a;
	nodeLaneWidth->SetAttribute("a",sa.str());

	std::stringstream sb;
	sb << setprecision(16) << setiosflags (ios_base::scientific) << b;
	nodeLaneWidth->SetAttribute("b",sb.str());

	std::stringstream sc;
	sc << setprecision(16) << setiosflags (ios_base::scientific) << c;
	nodeLaneWidth->SetAttribute("c",sc.str());

	std::stringstream sd;
	sd << setprecision(16) << setiosflags (ios_base::scientific) << d;
	nodeLaneWidth->SetAttribute("d",sd.str());

	return true;
}
//--------------

bool OpenDriveXmlWriter::WriteLaneRoadMark(TiXmlElement *node, LaneRoadMark* laneRoadMark)
{

	double sOffset;
	string type;
	string weight;
	string color; 
	double width;
	string laneChange;

	sOffset=laneRoadMark->GetS();
	type=laneRoadMark->GetType();
	weight=laneRoadMark->GetWeight();
	color=laneRoadMark->GetColor();
	width=laneRoadMark->GetWidth();
	laneChange=laneRoadMark->GetLaneChange();

	TiXmlElement* nodeLaneRoadMark = new TiXmlElement("roadMark");
	node->LinkEndChild(nodeLaneRoadMark);

	std::stringstream ssOffset;
	ssOffset << setprecision(16) << setiosflags (ios_base::scientific) << sOffset;
	nodeLaneRoadMark->SetAttribute("sOffset",ssOffset.str());
	nodeLaneRoadMark->SetAttribute("type",type);
	nodeLaneRoadMark->SetAttribute("weight",weight);
	nodeLaneRoadMark->SetAttribute("color",color);

	std::stringstream swidth;
	swidth << setprecision(16) << setiosflags (ios_base::scientific) << width;
	nodeLaneRoadMark->SetAttribute("width",swidth.str());
	nodeLaneRoadMark->SetAttribute("laneChange",laneChange);

	return true;
}
//--------------

bool OpenDriveXmlWriter::WriteLaneMaterial(TiXmlElement *node, LaneMaterial* laneMaterial)
{
	double sOffset;
	string surface;
	double friction;
	double roughness;

	sOffset=laneMaterial->GetS();
	surface=laneMaterial->GetSurface();
	friction=laneMaterial->GetFriction();
	roughness=laneMaterial->GetRoughness();

	TiXmlElement* nodeLaneMaterial = new TiXmlElement("material");
	node->LinkEndChild(nodeLaneMaterial);

	std::stringstream ssOffset;
	ssOffset << setprecision(16) << setiosflags (ios_base::scientific) << sOffset;
	nodeLaneMaterial->SetAttribute("sOffset",ssOffset.str());
	nodeLaneMaterial->SetAttribute("surface",surface);

	std::stringstream sfriction;
	sfriction << setprecision(16) << setiosflags (ios_base::scientific) << friction;
	nodeLaneMaterial->SetAttribute("friction",sfriction.str());

	std::stringstream sroughness;
	sroughness << setprecision(16) << setiosflags (ios_base::scientific) << roughness;
	nodeLaneMaterial->SetAttribute("roughness",sroughness.str());

	return true;
}
//--------------

bool OpenDriveXmlWriter::WriteLaneVisibility(TiXmlElement *node, LaneVisibility* laneVisibility)
{
	double sOffset;
	double forward;
	double back;
	double left;
	double right;

	sOffset=laneVisibility->GetS();
	forward=laneVisibility->GetForward();
	back=laneVisibility->GetBack();
	left=laneVisibility->GetLeft();
	right=laneVisibility->GetRight();

	TiXmlElement* nodeLaneVisibility = new TiXmlElement("visibility");
	node->LinkEndChild(nodeLaneVisibility);

	std::stringstream ssOffset;
	ssOffset << setprecision(16) << setiosflags (ios_base::scientific) << sOffset;
	nodeLaneVisibility->SetAttribute("sOffset",ssOffset.str());

	std::stringstream sforward;
	sforward << setprecision(16) << setiosflags (ios_base::scientific) << forward;
	nodeLaneVisibility->SetAttribute("forward",sforward.str());

	std::stringstream sback;
	sback << setprecision(16) << setiosflags (ios_base::scientific) << back;
	nodeLaneVisibility->SetAttribute("back",sback.str());

	std::stringstream sleft;
	sleft << setprecision(16) << setiosflags (ios_base::scientific) << left;
	nodeLaneVisibility->SetAttribute("left",sleft.str());

	std::stringstream sright;
	sright << setprecision(16) << setiosflags (ios_base::scientific) << right;
	nodeLaneVisibility->SetAttribute("right",sright.str());

	return true;
}
//--------------

bool OpenDriveXmlWriter::WriteLaneSpeed(TiXmlElement *node, LaneSpeed* laneSpeed)
{	
	double sOffset;
	double max;

	sOffset=laneSpeed->GetS();
	max=laneSpeed->GetMax();

	TiXmlElement* nodeLaneSpeed = new TiXmlElement("speed");
	node->LinkEndChild(nodeLaneSpeed);

	std::stringstream ssOffset;
	ssOffset << setprecision(16) << setiosflags (ios_base::scientific) << sOffset;
	nodeLaneSpeed->SetAttribute("sOffset",ssOffset.str());

	std::stringstream smax;
	smax << setprecision(16) << setiosflags (ios_base::scientific) << max;
	nodeLaneSpeed->SetAttribute("max",smax.str());

	return true;
}
//--------------

bool OpenDriveXmlWriter::WriteLaneAccess(TiXmlElement *node, LaneAccess* laneAccess)
{
	double sOffset;
	string restriction;

	sOffset=laneAccess->GetS();
	restriction=laneAccess->GetRestriction();

	TiXmlElement* nodeLaneAccess = new TiXmlElement("access");
	node->LinkEndChild(nodeLaneAccess);

	std::stringstream ssOffset;
	ssOffset << setprecision(16) << setiosflags (ios_base::scientific) << sOffset;
	nodeLaneAccess->SetAttribute("sOffset",ssOffset.str());
	nodeLaneAccess->SetAttribute("restriction",restriction);

	return true;
}
//--------------

bool OpenDriveXmlWriter::WriteLaneHeight(TiXmlElement *node, LaneHeight* laneHeight)
{
	double sOffset;
	double inner;
	double outer;

	sOffset=laneHeight->GetS();
	inner=laneHeight->GetInner();
	outer=laneHeight->GetOuter();

	TiXmlElement* nodeLaneHeight = new TiXmlElement("height");
	node->LinkEndChild(nodeLaneHeight);

	std::stringstream ssOffset;
	ssOffset << setprecision(16) << setiosflags (ios_base::scientific) << sOffset;
	nodeLaneHeight->SetAttribute("sOffset",ssOffset.str());

	std::stringstream sinner;
	sinner << setprecision(16) << setiosflags (ios_base::scientific) << inner;
	nodeLaneHeight->SetAttribute("inner",sinner.str());

	std::stringstream souter;
	souter << setprecision(16) << setiosflags (ios_base::scientific) << outer;
	nodeLaneHeight->SetAttribute("outer",souter.str());
	
	return true;
}
//--------------

//--------------

bool OpenDriveXmlWriter::WriteObjects (TiXmlElement *node, Road* road)
{
	TiXmlElement* nodeObjects = new TiXmlElement("objects");
	node->LinkEndChild(nodeObjects);

	return true;
}
//--------------

bool OpenDriveXmlWriter::WriteSignals (TiXmlElement *node, Road* road)
{
	TiXmlElement* nodeSignals = new TiXmlElement("signals");
	node->LinkEndChild(nodeSignals);

	return true;
}
//--------------

bool OpenDriveXmlWriter::WriteSurface (TiXmlElement *node, Road* road)
{
	return true;
}
//--------------

bool OpenDriveXmlWriter::WriteController (TiXmlElement *node)
{	return true;	}
//--------------

bool OpenDriveXmlWriter::WriteJunction (TiXmlElement *node, Junction *junction)
{
	string name;
	string id;

	name = junction->GetName();
	id = junction->GetId();

	TiXmlElement *nodeJunction = new TiXmlElement("junction");
	node->LinkEndChild(nodeJunction);

	nodeJunction->SetAttribute("name",name);
	nodeJunction->SetAttribute("id",id);

	//Connections
	WriteJunctionConnection(nodeJunction, junction);

	//Priorities
	WriteJunctionPriority(nodeJunction, junction);

	//Controllers
	WriteJunctionController(nodeJunction, junction);

	return true;
}
//--------------
bool OpenDriveXmlWriter::WriteJunctionConnection (TiXmlElement *node, Junction* junction)
{
	string id;
	string incomingRoad;
	string connectingRoad;
	string contactPoint;

	unsigned int junctionConnectionCount = junction->GetJunctionConnectionCount();
	for(unsigned int i=0; i<junctionConnectionCount; i++)
	{
		JunctionConnection *lJunctionConnection = junction->GetJunctionConnection(i);

		id = lJunctionConnection->GetId();
		incomingRoad = lJunctionConnection->GetIncomingRoad();
		connectingRoad = lJunctionConnection->GetConnectingRoad();
		contactPoint = lJunctionConnection->GetContactPoint();

		TiXmlElement *nodeJunctionConnection = new TiXmlElement("connection");
		node->LinkEndChild(nodeJunctionConnection);

		nodeJunctionConnection->SetAttribute("id",id);
		nodeJunctionConnection->SetAttribute("incomingRoad",incomingRoad);
		nodeJunctionConnection->SetAttribute("connectingRoad",connectingRoad);
		nodeJunctionConnection->SetAttribute("contactPoint",contactPoint);

		//Lane links
		WriteJunctionConnectionLaneLink(nodeJunctionConnection, lJunctionConnection);
	}

	return true;
}
bool OpenDriveXmlWriter::WriteJunctionConnectionLaneLink (TiXmlElement *node, JunctionConnection* junctionConnection)
{
	int from;
	int to;
	
	unsigned int junctionLaneLinkCount = junctionConnection->GetJunctionLaneLinkCount();
	for(unsigned int i=0; i<junctionLaneLinkCount; i++)
	{
		JunctionLaneLink *lJunctionLaneLink = junctionConnection->GetJunctionLaneLink(i);

		from = lJunctionLaneLink->GetFrom();
		to = lJunctionLaneLink->GetTo();

		TiXmlElement *nodeJunctionLaneLink = new TiXmlElement("laneLink");
		node->LinkEndChild(nodeJunctionLaneLink);

		nodeJunctionLaneLink->SetAttribute("from",from);
		nodeJunctionLaneLink->SetAttribute("to",to);
	}
	return true;
}

bool OpenDriveXmlWriter::WriteJunctionPriority (TiXmlElement *node, Junction* junction)
{
	string high;
	string low;

	unsigned int junctionPriorityCount = junction->GetJunctionPriorityCount();
	for(unsigned int i=0; i<junctionPriorityCount; i++)
	{
		JunctionPriorityRoad *lJunctionPriority = junction->GetJunctionPriority(i);

		high = lJunctionPriority->GetHigh();
		low = lJunctionPriority->GetLow();

		TiXmlElement *nodeJunctionPriority = new TiXmlElement("priority");
		node->LinkEndChild(nodeJunctionPriority);

		nodeJunctionPriority->SetAttribute("high",high);
		nodeJunctionPriority->SetAttribute("low",low);
	}

	return true;
}
bool OpenDriveXmlWriter::WriteJunctionController (TiXmlElement *node, Junction* junction)
{
	string id;
	string type;

	unsigned int junctionControllerCount = junction->GetJunctionControllerCount();
	for(unsigned int i=0; i<junctionControllerCount; i++)
	{
		JunctionController *lJunctionController = junction->GetJunctionController(i);

		id = lJunctionController->GetId();
		type = lJunctionController->GetType();

		TiXmlElement *nodeJunctionController = new TiXmlElement("controller");
		node->LinkEndChild(nodeJunctionController);

		nodeJunctionController->SetAttribute("id",id);
		nodeJunctionController->SetAttribute("type",type);
	}
	return true;
}


//---------------------------------------------------------------------------

/**
 * Writes the data from the OpenDrive structure to a file
 */
bool OpenDriveXmlWriter::WriteFile(std::string fileName)
{
	// XML document
	TiXmlDocument doc;

	TiXmlDeclaration* decl = new TiXmlDeclaration( "1.0", "", "" );  
	doc.LinkEndChild( decl );

	TiXmlElement *rootNode = new TiXmlElement("OpenDRIVE");
	doc.LinkEndChild(rootNode);

	// Write header
	WriteHeader(rootNode);

	// Write roads
	unsigned int roadCount = mOpenDrive->GetRoadCount();
	for(unsigned int i=0; i<roadCount; i++)
	{
		WriteRoad(rootNode, mOpenDrive->GetRoad(i));
	}

	// Write junctions
	unsigned int junctionCount = mOpenDrive->GetJunctionCount();
	for(unsigned int i=0; i<junctionCount; i++)
	{
		WriteJunction(rootNode, mOpenDrive->GetJunction(i));
	}

	// Saves the XML structure to the file
	doc.SaveFile( fileName ); 

	return true;

}
//--------------
