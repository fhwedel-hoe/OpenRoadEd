#ifndef OPENDRIVEXMLPARSER_H
#define OPENDRIVEXMLPARSER_H

#include <vector>
#include <string>

#include <iostream>
#include <fstream>
#include "../TinyXML/tinyxml.h"

#include "OpenDrive.h"

/**
 * Class used to parse an XML file and fill in the OpenDrive structure
 *
 */
class OpenDriveXmlParser
{
private:
	OpenDrive* mOpenDrive;
public:
	/**
	 * Constructor which saves a reference to OpenDrive structure
	 */
	OpenDriveXmlParser (OpenDrive* openDriveObj);

	/**
	 * Reads the data from the OpenDrive structure to a file
	 */
	bool ReadFile(std::string fileName);


	/**
	 * The following methods are used to read the data from the XML file and fill in the the OpenDrive structure
	 * Methods follow the hierarchical structure and are called automatically when ReadFile is executed
	 */
	bool ReadHeader (TiXmlElement *node);
	bool ReadRoad (TiXmlElement *node);
	bool ReadRoadLinks (Road* road, TiXmlElement *node);
	bool ReadRoadLink (Road* road, TiXmlElement *node, short int type);
	bool ReadRoadType (Road* road, TiXmlElement *node);
	//--------------

	bool ReadPlanView(Road* road, TiXmlElement *node);
	bool ReadGeometryBlock (Road* road, TiXmlElement *&node, short int blockType);
	bool ReadGeometry(GeometryBlock* geomBlock, TiXmlElement *node, short int geometryType);
	//--------------

	bool ReadElevationProfile (Road* road, TiXmlElement *node);
	bool ReadLateralProfile (Road* road, TiXmlElement *node);
	//--------------

	bool ReadLanes (Road* road, TiXmlElement *node);
	bool ReadLaneSections (Road* road, TiXmlElement *node);
	bool ReadLane (LaneSection* laneSection, TiXmlElement *node, short int laneType);
	bool ReadLaneWidth(Lane* lane, TiXmlElement *node);
	bool ReadLaneRoadMark(Lane* lane, TiXmlElement *node);
	bool ReadLaneMaterial(Lane* lane, TiXmlElement *node);
	bool ReadLaneVisibility(Lane* lane, TiXmlElement *node);
	bool ReadLaneSpeed(Lane* lane, TiXmlElement *node);
	bool ReadLaneAccess(Lane* lane, TiXmlElement *node);
	bool ReadLaneHeight(Lane* lane, TiXmlElement *node);
	//--------------

	bool ReadObjects (Road* road, TiXmlElement *node);
	bool ReadSignals (Road* road, TiXmlElement *node);
	//--------------

	bool ReadSurface (Road* road, TiXmlElement *node);
	//--------------

	bool ReadController (TiXmlElement *node);
	//--------------

	bool ReadJunction (TiXmlElement *node);
	bool ReadJunctionConnection (Junction* junction, TiXmlElement *node);
	bool ReadJunctionConnectionLaneLink (JunctionConnection* junctionConnection, TiXmlElement *node);
	//--------------

	bool ReadJunctionPriority (Junction* junction, TiXmlElement *node);
	bool ReadJunctionController (Junction* junction, TiXmlElement *node);
	//--------------
};


#endif
