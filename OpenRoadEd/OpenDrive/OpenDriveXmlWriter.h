#ifndef OPENDRIVEXMLWRITER_H
#define OPENDRIVEXMLWRITER_H

#include <vector>
#include <string>

#include <iostream>
#include <iomanip>
using namespace std;
#include <fstream>
#include "../TinyXML/tinyxml.h"

#include "OpenDrive.h"

/**
 * Class used to write the content of the OpenDrive structure to the file
 *
 */
class OpenDriveXmlWriter
{
private:
	OpenDrive* mOpenDrive;
public:
	/**
	 * Constructor which saves a reference to OpenDrive structure
	 */
	OpenDriveXmlWriter (OpenDrive* openDriveObj);

	/**
	 * Writes the data from the OpenDrive structure to a file
	 */
	bool WriteFile(std::string fileName);
	
	/**
	 * The following methods are used to create the XML representation of the OpenDrive structure
	 * Methods follow the same hierarchical structure and are called automatically when WriteFile
	 * is executed
	 */
	bool WriteHeader (TiXmlElement *node);
	bool WriteRoad (TiXmlElement *node, Road *road);
	bool WriteRoadLinks (TiXmlElement *node, Road* road);
	bool WriteRoadType (TiXmlElement *node, Road* road);
	//--------------

	bool WritePlanView(TiXmlElement *node, Road* road);
	bool WriteGeometryBlock (TiXmlElement *node, GeometryBlock *geometryBlock);
	bool WriteGeometry(TiXmlElement *node, RoadGeometry* roadGeometry, short int geometryType);
	//--------------

	bool WriteElevationProfile (TiXmlElement *node, Road* road);
	bool WriteLateralProfile (TiXmlElement *node, Road* road);
	//--------------

	bool WriteLanes (TiXmlElement *node, Road* road);
	bool WriteLaneSections (TiXmlElement *node, LaneSection *laneSection);
	bool WriteLane (TiXmlElement *node, Lane* lane);
	bool WriteLaneWidth(TiXmlElement *node, LaneWidth* laneWidth);
	bool WriteLaneRoadMark(TiXmlElement *node, LaneRoadMark* laneRoadMark);
	bool WriteLaneMaterial(TiXmlElement *node, LaneMaterial* laneMaterial);
	bool WriteLaneVisibility(TiXmlElement *node, LaneVisibility* laneVisibility);
	bool WriteLaneSpeed(TiXmlElement *node, LaneSpeed* laneSpeed);
	bool WriteLaneAccess(TiXmlElement *node, LaneAccess* laneAccess);
	bool WriteLaneHeight(TiXmlElement *node, LaneHeight* laneHeight);
	//--------------

	bool WriteObjects (TiXmlElement *node, Road* road);
	bool WriteSignals (TiXmlElement *node, Road* road);
	//--------------

	bool WriteSurface (TiXmlElement *node, Road* road);
	//--------------

	bool WriteController (TiXmlElement *node);
	//--------------

	bool WriteJunction (TiXmlElement *node, Junction *junction);
	bool WriteJunctionConnection (TiXmlElement *node, Junction* junction);
	bool WriteJunctionConnectionLaneLink (TiXmlElement *node, JunctionConnection* junctionConnection);
	//--------------

	bool WriteJunctionPriority (TiXmlElement *node, Junction* junction);
	bool WriteJunctionController (TiXmlElement *node, Junction* junction);
	//--------------
};


#endif
