#include "OpenDriveXmlParser.h"
#include <iostream>
#include <algorithm>
//#include "windows.h"

using std::cout;
using std::endl;

/**
 * Constructor which saves a reference to OpenDrive structure
 */
OpenDriveXmlParser::OpenDriveXmlParser (OpenDrive* openDriveObj)
{	
	mOpenDrive=openDriveObj;	
}

/**
 * The following methods are used to read the data from the XML file and fill in the the OpenDrive structure
 * Methods follow the hierarchical structure and are called automatically when ReadFile is executed
 */
bool OpenDriveXmlParser::ReadHeader(TiXmlElement *node)
{
	//Read the Header
	unsigned short int revMajor;
	unsigned short int revMinor;
	string name;
	float version;
	string date;
	double north;
	double south;
	double east;
	double west;

	int checker=TIXML_SUCCESS;
	checker+=node->QueryValueAttribute<unsigned short int>("revMajor",&revMajor);
	checker+=node->QueryValueAttribute<unsigned short int>("revMinor",&revMinor);
	checker+=node->QueryStringAttribute("name",&name);
	checker+=node->QueryFloatAttribute("version",&version);
	checker+=node->QueryStringAttribute("date",&date);
	checker+=node->QueryDoubleAttribute("north",&north);
	checker+=node->QueryDoubleAttribute("south",&south);
	checker+=node->QueryDoubleAttribute("east",&east);
	checker+=node->QueryDoubleAttribute("west",&west);

	if (checker!=TIXML_SUCCESS)
	{
		cout<<"Error parsing Header attributes"<<endl;
		return false;
	}

	mOpenDrive->SetHeader(revMajor, revMinor, name, version, date, north, south, east, west);

	return true;

}
//--------------

bool OpenDriveXmlParser::ReadRoad(TiXmlElement *node)
{
	//Read road attributes
	string name;
	double length;
	string id;
	string junction;

	int checker=TIXML_SUCCESS;
	
	checker+=node->QueryStringAttribute("name",&name);
	checker+=node->QueryDoubleAttribute("length",&length);
	checker+=node->QueryStringAttribute("id",&id);
	checker+=node->QueryStringAttribute("junction",&junction);

	if (checker!=TIXML_SUCCESS)
	{
		cout<<"Error parsing Road attributes"<<endl;
		return false;
	}
	//fill in
	mOpenDrive->AddRoad(name, length, id, junction);
	Road* road = mOpenDrive->GetLastAddedRoad();
	TiXmlElement* subNode;


	//Get links
	subNode=node->FirstChildElement("link");
	if (subNode)
	{
		ReadRoadLinks (road,subNode);
	}	

	//Proceed to road Type
	subNode=node->FirstChildElement("type");
	while (subNode)
	{
		ReadRoadType(road, subNode);
		subNode=subNode->NextSiblingElement("type");
	}

	//Proceed to planView
	subNode=node->FirstChildElement("planView");
	ReadPlanView(road, subNode);

	//Proceed to ElevationProfile
	subNode=node->FirstChildElement("elevationProfile");
	if (subNode)
	{
		ReadElevationProfile(road, subNode);
	}

	//Proceed to LateralProfile
	subNode=node->FirstChildElement("lateralProfile");
	if (subNode)
	{
		ReadLateralProfile(road, subNode);
	}

	//Proceed to Lanes
	subNode=node->FirstChildElement("lanes");
	ReadLanes(road, subNode);

	//Proceed to Objects
	subNode=node->FirstChildElement("objects");
	if (subNode)
	{
		ReadObjects(road, subNode);
	}

	//Proceed to Signals
	subNode=node->FirstChildElement("signals");
	if (subNode)
	{
		ReadSignals(road, subNode);
	}

	//Proceed to Surface
	subNode=node->FirstChildElement("surface");
	if (subNode)
	{
		ReadSurface(road, subNode);
	}

	return true;
}
//--------------

bool  OpenDriveXmlParser::ReadRoadLinks (Road* road, TiXmlElement *node)
{
	TiXmlElement* subNode;
	subNode=node->FirstChildElement("predecessor");
	if (subNode)
	{
		ReadRoadLink(road, subNode,0);
	}

	subNode=node->FirstChildElement("successor");
	if (subNode)
	{
		ReadRoadLink(road, subNode,1);
	}

	subNode=node->FirstChildElement("neighbor");
	if (subNode)
	{
		ReadRoadLink(road, subNode,2);
	}

	subNode=node->NextSiblingElement("neighbor");
	if (subNode)
	{
		ReadRoadLink(road, subNode,2);
	}

	return true;
}
//--------------

bool  OpenDriveXmlParser::ReadRoadLink (Road* road, TiXmlElement *node, short int type)
{
	//all three types (neighbor, successor or predecessor) have the same number and same types of members,
	//but in case this changes in future, load it separately
	if (type == 0)
	{
		string elementType; 
		string elementId;
		string contactPoint="NA";

		int checker=TIXML_SUCCESS;
		checker+=node->QueryStringAttribute("elementType",&elementType);
		checker+=node->QueryStringAttribute("elementId",&elementId);
		if (elementType.compare("road")==0)
			checker+=node->QueryStringAttribute("contactPoint",&contactPoint);

		if (checker!=TIXML_SUCCESS)
		{
			cout<<"Error parsing Predecessor attributes"<<endl;
			return false;
		}
		road->SetPredecessor(elementType,elementId,contactPoint);
		return true;

	}
	else if (type == 1)
	{
		string elementType; 
		string elementId;
		string contactPoint="NA";

		int checker=TIXML_SUCCESS;
		checker+=node->QueryStringAttribute("elementType",&elementType);
		checker+=node->QueryStringAttribute("elementId",&elementId);
		if (elementType.compare("road")==0)
			checker+=node->QueryStringAttribute("contactPoint",&contactPoint);

		if (checker!=TIXML_SUCCESS)
		{
			cout<<"Error parsing Successor attributes"<<endl;
			return false;
		}
		road->SetSuccessor(elementType,elementId,contactPoint);
		return true;
	}

	else if (type == 2)
	{
		string side; 
		string elementId;
		string direction;

		int checker=TIXML_SUCCESS;
		checker+=node->QueryStringAttribute("side",&side);
		checker+=node->QueryStringAttribute("elementId",&elementId);
		checker+=node->QueryStringAttribute("direction",&direction);

		if (checker!=TIXML_SUCCESS)
		{
			cout<<"Error parsing Neighbor attributes"<<endl;
			return false;
		}
		road->SetNeighbor(side,elementId,direction);
		return true;
	}

	return false;
		
}
//--------------

bool OpenDriveXmlParser::ReadRoadType (Road* road, TiXmlElement *node)
{
	double s;
	string type;

	int checker=TIXML_SUCCESS;
	checker+=node->QueryDoubleAttribute("s",&s);
	checker+=node->QueryStringAttribute("type",&type);

	if (checker!=TIXML_SUCCESS)
	{
		cout<<"Error parsing Road Type attributes"<<endl;
		return false;
	}

	road->AddRoadType(s,type);
	return true;
}
//--------------

bool OpenDriveXmlParser::ReadPlanView(Road* road, TiXmlElement *node)
{
	//Get geometry
	TiXmlElement* subNode;
	TiXmlElement* subNodeType;
	subNode=node->FirstChildElement("geometry");
	
	while (subNode)
	{
		subNodeType=subNode->FirstChildElement();
		if (subNodeType->ValueStr().compare("line")==0)
		{
			ReadGeometryBlock(road, subNode,0);		//load a straight block
		}
		else if (subNodeType->ValueStr().compare("spiral")==0)
		{
			ReadGeometryBlock(road, subNode,1);		//load a turn block
		}
		else if (subNodeType->ValueStr().compare("poly3")==0)
		{
			ReadGeometryBlock(road, subNode,2);		//load a polynom spline block
		}
			

		subNode=subNode->NextSiblingElement("geometry");

	}
	return true;
}
//--------------

bool OpenDriveXmlParser::ReadGeometryBlock (Road* road, TiXmlElement *&node, short int blockType)
{
	road->AddGeometryBlock();
	GeometryBlock* geomBlock=road->GetLastAddedGeometryBlock();
	switch (blockType)
	{
	case 0:
		ReadGeometry(geomBlock, node, 0);
		break;
	case 1:
		ReadGeometry(geomBlock, node, 1);
		node=node->NextSiblingElement("geometry");
		ReadGeometry(geomBlock, node, 2);
		node=node->NextSiblingElement("geometry");
		ReadGeometry(geomBlock, node, 1);
		break;
	case 2:
		ReadGeometry(geomBlock, node, 3);
		break;
	}

	return true;
	
}
//--------------

bool OpenDriveXmlParser::ReadGeometry(GeometryBlock* geomBlock, TiXmlElement *node, short int geometryType)
{
	double s, x, y, hdg, length;
	//read the geometry node
	int checker=TIXML_SUCCESS;
	checker+=node->QueryDoubleAttribute("s",&s);
	checker+=node->QueryDoubleAttribute("x",&x);
	checker+=node->QueryDoubleAttribute("y",&y);
	checker+=node->QueryDoubleAttribute("hdg",&hdg);
	checker+=node->QueryDoubleAttribute("length",&length);

	if (checker!=TIXML_SUCCESS)
	{
		cout<<"Error parsing Geometry attributes"<<endl;
		return false;
	}

	TiXmlElement *subNode=node->FirstChildElement();

	//read the type nodes
	switch ( geometryType )
      {
	case 0:		//line
		geomBlock->AddGeometryLine(s,x,y,hdg,length);
		break;
	case 1:		//spiral
		checker=TIXML_SUCCESS;
		double curvatureStart, curvatureEnd; 
		checker+=subNode->QueryDoubleAttribute("curvStart",&curvatureStart);
		checker+=subNode->QueryDoubleAttribute("curvEnd",&curvatureEnd);
		if (checker!=TIXML_SUCCESS)
		{
			cout<<"Error parsing spiral attributes"<<endl;
			return false;
		}
		geomBlock->AddGeometrySpiral(s,x,y,hdg,length,curvatureStart,curvatureEnd);
		break;
	case 2:		//arc
		checker=TIXML_SUCCESS;
		double curvature;
		checker+=subNode->QueryDoubleAttribute("curvature",&curvature);
		if (checker!=TIXML_SUCCESS)
		{
			cout<<"Error parsing arc attributes"<<endl;
			return false;
		}
		geomBlock->AddGeometryArc(s,x,y,hdg,length,curvature);
		break;


	case 3:		//poly3
		checker=TIXML_SUCCESS;
		double a,b,c,d;
		checker+=subNode->QueryDoubleAttribute("a",&a);
		checker+=subNode->QueryDoubleAttribute("b",&b);
		checker+=subNode->QueryDoubleAttribute("c",&c);
		checker+=subNode->QueryDoubleAttribute("d",&d);
		if (checker!=TIXML_SUCCESS)
		{
			cout<<"Error parsing arc attributes"<<endl;
			return false;
		}

		geomBlock->AddGeometryPoly3(s,x,y,hdg,length,a,b,c,d);
		break;
	}

	return true;
}
//--------------

bool OpenDriveXmlParser::ReadElevationProfile (Road* road, TiXmlElement *node)
{
	TiXmlElement* subNode;
	subNode=node->FirstChildElement("elevation");
	double s, a, b, c, d;
	while (subNode)
	{
		int checker=TIXML_SUCCESS;
		checker+=subNode->QueryDoubleAttribute("s",&s);
		checker+=subNode->QueryDoubleAttribute("a",&a);
		checker+=subNode->QueryDoubleAttribute("b",&b);
		checker+=subNode->QueryDoubleAttribute("c",&c);
		checker+=subNode->QueryDoubleAttribute("d",&d);

		if (checker!=TIXML_SUCCESS)
		{
			cout<<"Error parsing Elevation attributes"<<endl;
			return false;
		}

		road->AddElevation(s,a,b,c,d);

		subNode=subNode->NextSiblingElement("elevation");
	}
	return true;
}
//--------------

bool OpenDriveXmlParser::ReadLateralProfile (Road* road, TiXmlElement *node)
{
	TiXmlElement* subNode;
	subNode=node->FirstChildElement("superelevation");
	double s, a, b, c, d;
	while (subNode)
	{
		int checker=TIXML_SUCCESS;
		checker+=subNode->QueryDoubleAttribute("s",&s);
		checker+=subNode->QueryDoubleAttribute("a",&a);
		checker+=subNode->QueryDoubleAttribute("b",&b);
		checker+=subNode->QueryDoubleAttribute("c",&c);
		checker+=subNode->QueryDoubleAttribute("d",&d);

		if (checker!=TIXML_SUCCESS)
		{
			cout<<"Error parsing Superelevation attributes"<<endl;
			return false;
		}

		road->AddSuperElevation(s,a,b,c,d);

		subNode=subNode->NextSiblingElement("superelevation");
	}

	subNode=node->FirstChildElement("crossfall");
	string side;
	while (subNode)
	{
		int checker=TIXML_SUCCESS;
		checker+=subNode->QueryStringAttribute("side",&side);
		checker+=subNode->QueryDoubleAttribute("s",&s);
		checker+=subNode->QueryDoubleAttribute("a",&a);
		checker+=subNode->QueryDoubleAttribute("b",&b);
		checker+=subNode->QueryDoubleAttribute("c",&c);
		checker+=subNode->QueryDoubleAttribute("d",&d);

		if (checker!=TIXML_SUCCESS)
		{
			cout<<"Error parsing Crossfall attributes"<<endl;
			return false;
		}

		road->AddCrossfall(side,s,a,b,c,d);

		subNode=subNode->NextSiblingElement("crossfall");
	}

	return true;
}
//--------------

bool OpenDriveXmlParser::ReadLanes (Road* road, TiXmlElement *node)
{
	TiXmlElement *subNode = node->FirstChildElement("laneSection");
	while (subNode)
	{
		ReadLaneSections(road, subNode);
		subNode=subNode->NextSiblingElement("laneSection");
	}

	return true;
}
//--------------

bool OpenDriveXmlParser::ReadLaneSections (Road* road, TiXmlElement *node)
{

	int checker=TIXML_SUCCESS;
	double s;
	checker+=node->QueryDoubleAttribute("s",&s);

	if (checker!=TIXML_SUCCESS)
	{
		cout<<"Error parsing Lane Section attributes"<<endl;
		return false;
	}

	
	road->AddLaneSection(s);
	LaneSection* laneSection=road->GetLastAddedLaneSection();
	TiXmlElement *subNode=node->FirstChildElement("left");
	if (subNode)
	{
		subNode=subNode->FirstChildElement("lane");
		while(subNode)
		{
			
			ReadLane(laneSection,subNode,1);	//0 for left
			subNode=subNode->NextSiblingElement("lane");
		}

	}

	subNode=node->FirstChildElement("center");
	if (subNode)
	{
		subNode=subNode->FirstChildElement("lane");
		while(subNode)
		{
			
			ReadLane(laneSection,subNode,0);	//1 for center	
			subNode=subNode->NextSiblingElement("lane");
		}
	}

	subNode=node->FirstChildElement("right");
	if (subNode)
	{
		subNode=subNode->FirstChildElement("lane");
		while(subNode)
		{
			
			ReadLane(laneSection,subNode,-1);	//2 for right	
			subNode=subNode->NextSiblingElement("lane");
		}
	}


	//OutputDebugString( "\n") ;
	for (unsigned int i=0;i<laneSection->GetLaneVector()->size();i++)
	{
		int id = static_cast<Lane>(laneSection->GetLaneVector()->at(i)).GetId();

		/*char* buf;
		buf=new char[5];
		itoa(id,buf,10);

		OutputDebugString( buf ) ;
		OutputDebugString( " ") ;*/
	}
	//OutputDebugString( "\n") ;


	//sort in descending order
	std::sort(laneSection->GetLaneVector()->begin(),laneSection->GetLaneVector()->end());
	std::reverse(laneSection->GetLaneVector()->begin(),laneSection->GetLaneVector()->end());
	return true;
}
//--------------

bool OpenDriveXmlParser::ReadLane (LaneSection* laneSection, TiXmlElement *node, short int laneType)
{
	//Read Lane attributes
	short int side=laneType;
	int id;
	string type; 
	string level; 
	bool boolLevel;
	int predecessor;
	int successor;

	int checker=TIXML_SUCCESS;
	checker+=node->QueryIntAttribute("id",&id);
	checker+=node->QueryStringAttribute("type",&type);
	if (checker!=TIXML_SUCCESS)
	{
		cout<<"Error parsing Lane attributes"<<endl;
		return false;
	}
	//in case "level" is missing, apply default value
	checker=node->QueryStringAttribute("level",&level);
	if (checker!=TIXML_SUCCESS)
	{	level="false"; }

	//convert level to bool

	if (level.compare("false")==0 || level.compare("0")==0)
		boolLevel=false;
	else
		boolLevel=true;

	//pointer to the lane
	Lane* lane; 
	//Depending on the laneType, add it to the appropriate vector and get a pointer to it

	laneSection->AddLane(side,id,type,boolLevel,false);
	lane=laneSection->GetLastAddedLane();


	//Read Link parameters and add them to the lane if available
	TiXmlElement *subNode=node->FirstChildElement("link");
	TiXmlElement *subSubNode;
	if (subNode)
		subSubNode=subNode->FirstChildElement("predecessor");
			if (subSubNode)
			{
				checker=subSubNode->QueryIntAttribute("id",&predecessor);
				if (checker==TIXML_SUCCESS)
					lane->SetPredecessor(predecessor);
			}
	if (subNode)
		subSubNode=subNode->FirstChildElement("successor");
			if (subSubNode)
			{
				checker=subSubNode->QueryIntAttribute("id",&successor);
				if (checker==TIXML_SUCCESS)
					lane->SetSuccessor(successor);
			}

	//Proceed to the Road width
	subNode=node->FirstChildElement("width");
	while (subNode)
	{
		ReadLaneWidth(lane, subNode);
		subNode=subNode->NextSiblingElement("width");
	}

	//Proceed to the Road Mark
	subNode=node->FirstChildElement("roadMark");
	while (subNode)
	{
		ReadLaneRoadMark(lane, subNode);
		subNode=subNode->NextSiblingElement("roadMark");
	}

	//Proceed to the Lane Material
	subNode=node->FirstChildElement("material");
	while (subNode)
	{
		ReadLaneMaterial(lane, subNode);
		subNode=subNode->NextSiblingElement("material");
	}

	//Proceed to the Lane Visibility
	subNode=node->FirstChildElement("visibility");
	while (subNode)
	{
		ReadLaneVisibility(lane, subNode);
		subNode=subNode->NextSiblingElement("visibility");
	}

	//Proceed to the Lane speed
	subNode=node->FirstChildElement("speed");
	while (subNode)
	{
		ReadLaneSpeed(lane, subNode);
		subNode=subNode->NextSiblingElement("speed");
	}

	//Proceed to the Lane access
	subNode=node->FirstChildElement("access");
	while (subNode)
	{
		ReadLaneAccess(lane, subNode);
		subNode=subNode->NextSiblingElement("access");
	}

	//Proceed to the Lane height
	subNode=node->FirstChildElement("height");
	while (subNode)
	{
		ReadLaneHeight(lane, subNode);
		subNode=subNode->NextSiblingElement("height");
	}

	return true;
}
//--------------


bool OpenDriveXmlParser::ReadLaneWidth(Lane* lane, TiXmlElement *node)
{
	double sOffset, a, b, c, d;

	int checker=TIXML_SUCCESS;
	checker+=node->QueryDoubleAttribute("sOffset",&sOffset);
	checker+=node->QueryDoubleAttribute("a",&a);
	checker+=node->QueryDoubleAttribute("b",&b);
	checker+=node->QueryDoubleAttribute("c",&c);
	checker+=node->QueryDoubleAttribute("d",&d);

	if (checker!=TIXML_SUCCESS)
	{
		cout<<"Error parsing Lane Weight attributes"<<endl;
		return false;
	}

	lane->AddWidthRecord(sOffset,a,b,c,d);

	return true;
}
//--------------

bool OpenDriveXmlParser::ReadLaneRoadMark(Lane* lane, TiXmlElement *node)
{
	
	double sOffset;
	string type;
	string weight;
	string color; 
	double width;
	string laneChange;

	int checker=TIXML_SUCCESS;
	checker+=node->QueryDoubleAttribute("sOffset",&sOffset);
	checker+=node->QueryStringAttribute("type",&type);
	checker+=node->QueryStringAttribute("weight",&weight);
	checker+=node->QueryStringAttribute("color",&color);
	
	if (checker!=TIXML_SUCCESS)
	{
		cout<<"Error parsing Lane Weight attributes"<<endl;
		return false;
	}

	checker+=node->QueryDoubleAttribute("width",&width);
	if (checker!=TIXML_SUCCESS)
	{	width=0;	}

	checker=node->QueryStringAttribute("laneChange",&laneChange);
	if (checker!=TIXML_SUCCESS)
	{	laneChange = "both"; }

	lane->AddRoadMarkRecord(sOffset,type,weight,color,width,laneChange);

	return true;
}
//--------------

bool OpenDriveXmlParser::ReadLaneMaterial(Lane* lane, TiXmlElement *node)
{
	double sOffset;
	string surface;
	double friction;
	double roughness;

	int checker=TIXML_SUCCESS;
	checker+=node->QueryDoubleAttribute("sOffset",&sOffset);
	checker+=node->QueryStringAttribute("surface",&surface);
	checker+=node->QueryDoubleAttribute("friction",&friction);
	checker+=node->QueryDoubleAttribute("roughness",&roughness);
	if (checker!=TIXML_SUCCESS)
	{
		cout<<"Error parsing Lane Weight attributes"<<endl;
		return false;
	}

	lane->AddMaterialRecord(sOffset,surface,friction,roughness);

	return true;

}
//--------------

bool OpenDriveXmlParser::ReadLaneVisibility(Lane* lane, TiXmlElement *node)
{
	double sOffset;
	double forward;
	double back;
	double left;
	double right;

	int checker=TIXML_SUCCESS;
	checker+=node->QueryDoubleAttribute("sOffset",&sOffset);
	checker+=node->QueryDoubleAttribute("forward",&forward);
	checker+=node->QueryDoubleAttribute("back",&back);
	checker+=node->QueryDoubleAttribute("left",&left);
	checker+=node->QueryDoubleAttribute("right",&right);
	if (checker!=TIXML_SUCCESS)
	{
		cout<<"Error parsing Lane Weight attributes"<<endl;
		return false;
	}

	lane->AddVisibilityRecord(sOffset,forward,back,left,right);

	return true;
}
//--------------

bool OpenDriveXmlParser::ReadLaneSpeed(Lane* lane, TiXmlElement *node)
{	
	double sOffset;
	double max;

	int checker=TIXML_SUCCESS;
	checker+=node->QueryDoubleAttribute("sOffset",&sOffset);
	checker+=node->QueryDoubleAttribute("max",&max);
	if (checker!=TIXML_SUCCESS)
	{
		cout<<"Error parsing Lane Weight attributes"<<endl;
		return false;
	}

	lane->AddSpeedRecord(sOffset,max);

	return true;
}
//--------------

bool OpenDriveXmlParser::ReadLaneAccess(Lane* lane, TiXmlElement *node)
{
	double sOffset;
	string restriction;

	int checker=TIXML_SUCCESS;
	checker+=node->QueryDoubleAttribute("sOffset",&sOffset);
	checker+=node->QueryStringAttribute("restriction",&restriction);
	if (checker!=TIXML_SUCCESS)
	{
		cout<<"Error parsing Lane Weight attributes"<<endl;
		return false;
	}

	lane->AddAccessRecord(sOffset,restriction);

	return true;
}
//--------------

bool OpenDriveXmlParser::ReadLaneHeight(Lane* lane, TiXmlElement *node)
{
	double sOffset;
	double inner;
	double outer;

	int checker=TIXML_SUCCESS;
	checker+=node->QueryDoubleAttribute("sOffset",&sOffset);
	checker+=node->QueryDoubleAttribute("inner",&inner);
	checker+=node->QueryDoubleAttribute("outer",&outer);
	if (checker!=TIXML_SUCCESS)
	{
		cout<<"Error parsing Lane Weight attributes"<<endl;
		return false;
	}

	lane->AddHeightRecord(sOffset,inner,outer);

	return true;
}
//--------------

//--------------

bool OpenDriveXmlParser::ReadObjects (Road* road, TiXmlElement *node)
{
	return true;
}
//--------------

bool OpenDriveXmlParser::ReadSignals (Road* road, TiXmlElement *node)
{
	return true;
}
//--------------

bool OpenDriveXmlParser::ReadSurface (Road* road, TiXmlElement *node)
{
	return true;
}
//--------------

bool OpenDriveXmlParser::ReadController (TiXmlElement *node)
{	return true;	}
//--------------

bool OpenDriveXmlParser::ReadJunction (TiXmlElement *node)
{	
	string name;
	string id;

	int checker=TIXML_SUCCESS;
	checker+=node->QueryStringAttribute("name",&name);
	checker+=node->QueryStringAttribute("id",&id);
	if (checker!=TIXML_SUCCESS)
	{
		cout<<"Error parsing Junction attributes"<<endl;
		return false;
	}

	mOpenDrive->AddJunction(name,id);
	Junction* junction=mOpenDrive->GetLastJunction();

	//Read connection parameters and add them to the lane if available
	TiXmlElement *subNode=node->FirstChildElement("connection");

	while (subNode)
	{
		ReadJunctionConnection(junction, subNode);
		subNode=subNode->NextSiblingElement("connection");
	}


	//Read connection parameters and add them to the lane if available
	subNode=node->FirstChildElement("priority");

	while (subNode)
	{
		ReadJunctionPriority(junction, subNode);
		subNode=subNode->NextSiblingElement("priority");
	}



	//Read connection parameters and add them to the lane if available
	subNode=node->FirstChildElement("controller");

	while (subNode)
	{
		ReadJunctionController(junction, subNode);
		subNode=subNode->NextSiblingElement("controller");
	}


	return true;
	
}
//--------------
bool OpenDriveXmlParser::ReadJunctionConnection (Junction* junction, TiXmlElement *node)
{
	string id;
	string incomingRoad;
	string connectingRoad;
	string contactPoint;

	int checker=TIXML_SUCCESS;
	checker+=node->QueryStringAttribute("id",&id);
	checker+=node->QueryStringAttribute("incomingRoad",&incomingRoad);
	checker+=node->QueryStringAttribute("connectingRoad",&connectingRoad);
	checker+=node->QueryStringAttribute("contactPoint",&contactPoint);
	if (checker!=TIXML_SUCCESS)
	{
		cout<<"Error parsing Junction Connection attributes"<<endl;
		return false;
	}

	junction->AddJunctionConnection(id,incomingRoad,connectingRoad,contactPoint);
	JunctionConnection* junctionConnetion = junction->GetLastJunctionConnection();

	TiXmlElement *subNode=node->FirstChildElement("laneLink");

	while (subNode)
	{
		ReadJunctionConnectionLaneLink(junctionConnetion, subNode);
		subNode=subNode->NextSiblingElement("laneLink");
	}

	return true;
}
bool OpenDriveXmlParser::ReadJunctionConnectionLaneLink (JunctionConnection* junctionConnection, TiXmlElement *node)
{
	int from;
	int to;

	int checker=TIXML_SUCCESS;
	checker+=node->QueryIntAttribute("from",&from);
	checker+=node->QueryIntAttribute("to",&to);
	if (checker!=TIXML_SUCCESS)
	{
		cout<<"Error parsing Junction Lane Link attributes"<<endl;
		return false;
	}

	junctionConnection->AddJunctionLaneLink(from,to);
	return true;
}

bool OpenDriveXmlParser::ReadJunctionPriority (Junction* junction, TiXmlElement *node)
{
	string high;
	string low;

	int checker=TIXML_SUCCESS;
	checker+=node->QueryStringAttribute("high",&high);
	checker+=node->QueryStringAttribute("low",&low);
	if (checker!=TIXML_SUCCESS)
	{
		cout<<"Error parsing Junction Priority attributes"<<endl;
		return false;
	}

	junction->AddJunctionPriority(high,low);
	return true;
}
bool OpenDriveXmlParser::ReadJunctionController (Junction* junction, TiXmlElement *node)
{
	string id;
	string type;

	int checker=TIXML_SUCCESS;
	checker+=node->QueryStringAttribute("id",&id);
	checker+=node->QueryStringAttribute("type",&type);
	if (checker!=TIXML_SUCCESS)
	{
		cout<<"Error parsing Junction Controller attributes"<<endl;
		return false;
	}

	junction->AddJunctionController(id,type);
	return true;
}


//---------------------------------------------------------------------------
/**
 * Reads the data from the OpenDrive structure to a file
 */
bool OpenDriveXmlParser::ReadFile(std::string fileName)
{
	//Read and load File
	TiXmlDocument doc( fileName );
	bool loadOkay = doc.LoadFile();
	if (loadOkay)
	{
		TiXmlElement *rootNode=doc.FirstChildElement();
		//read header
		int checker=TIXML_SUCCESS;
		TiXmlElement *node=rootNode->FirstChildElement("header");
		ReadHeader(node);

		//read roads
		node=rootNode->FirstChildElement("road");
		while (node!=0)
		{
			ReadRoad(node);
			node=node->NextSiblingElement("road");
		}

		//read controllers
		node=rootNode->FirstChildElement("controller");
		while (node!=0)
		{
			ReadController(node);
			node=node->NextSiblingElement("controller");
		}

		//read junctions
		node=rootNode->FirstChildElement("junction");
		while (node!=0)
		{
			ReadJunction(node);
			node=node->NextSiblingElement("junction");
		}

		return true;
	}
	
	//failed to read the file
	cout<<"Could not read file: "<<fileName<<endl;
	return false;
}
//--------------
