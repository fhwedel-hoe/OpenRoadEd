#ifndef ROAD_H
#define ROAD_H

#include <vector>
#include <string>

#include "RoadGeometry.h"
#include "Lane.h"
#include "Junction.h"
#include "ObjectSignal.h"
#include "OtherStructures.h"

//--Prototypes--
//road
class Road;
class RoadLink;
class RoadNeighbor;
class RoadType;
class GeometryBlock;
class Elevation;
class SuperElevation;
class Crossfall;
//lanes
class LaneSection;
class LaneSectionSample;
//objects, signals
class Object;
class Signal;
//--------------

using std::vector;
using std::string;

/**
 * One of the main classes in OpenDrive structure
 * Holds the properties of the Road record and vectors for child records
 * Has methods to add, clone, get and delete those child records
 * as well as evaluation methods used, for example, to render the road
 *
 */
class Road
{
private:
	// Main road record properties
	string mName;
	double mLength;
	string mId;
	string mJunction;

	// Linking complex properties (have multiple sub-properties)
	RoadLink* mPredecessor;
	RoadLink* mSuccessor;
	RoadNeighbor* mNeighbor1;
	RoadNeighbor* mNeighbor2;

	/**
	 * Vectors used to store the child records of the road
	 * such as chordline geometry, elevation profiles, etc
	 */
	// Road type vector
	vector<RoadType> mRoadTypeVector;
	// Geometry block vector
	vector<GeometryBlock> mGeometryBlockVector; 
	// Elevation Profile vector
	vector<Elevation> mElevationVector;
	// Superelevation vector
	vector<SuperElevation> mSuperElevationVector;
	// Crossfall vector
	vector<Crossfall> mCrossfallVector;
	// Lane Section vector
	vector<LaneSection> mLaneSectionsVector;
	// Objects vectors
	vector<Object> mObjectsVector;
	// Signal vector
	vector<Signal> mSignalsVector;

	/**
	 * Indices of the last added child records
	 */
	unsigned int mLastAddedRoadType;
	unsigned int mLastAddedGeometryBlock;
	unsigned int mLastAddedElevation;
	unsigned int mLastAddedSuperElevation;
	unsigned int mLastAddedCrossfall;
	unsigned int mLastAddedLaneSection;
	unsigned int mLastAddedObject;
	unsigned int mLastAddedSignal;

public:
	/**
	 * Constructor
	 */
	Road();

	/**
	 * Constructor that initializes the road with base properties
	 * 
	 * @param name Name of the road
	 * @param length Length of the road
	 * @param id Unique ID of the road
	 * @param junction ID of the junction, this road might be a part of
	 */
	Road(string name, double length, string id, string junction);

	/**
	 * Copy constructor
	 */
	Road (const Road& road);

	/**
	 * Assignment operator overload
	 */
	const Road& operator=(const Road& rhs);
	//-------------------------------------------------

	/**
	 * Getters for the base properties of the road
	 */
	string GetRoadName() const;
	double GetRoadLength() const;
	string GetRoadId() const;
	string GetRoadJunction() const;
	
	/**
	 * Getters for the linking properties of the road
	 */
	RoadLink* GetPredecessor();
	RoadLink* GetSuccessor();
	RoadNeighbor* GetNeighbor1();
	RoadNeighbor* GetNeighbor2();

	/**
	 * Getters for the child records and their vectors
	 */
	// Road type records
	vector<RoadType> *GetRoadTypeVector();
	RoadType* GetRoadType(unsigned int i);
	unsigned int GetRoadTypeCount();
	// Road geometry records
	vector<GeometryBlock> *GetGeometryBlockVector();
	GeometryBlock* GetGeometryBlock(unsigned int i);
	unsigned int GetGeometryBlockCount();
	// Road elevation records
	vector<Elevation> *GetElevationVector();
	Elevation*	GetElevation(unsigned int i);
	unsigned int GetElevationCount();
	// Road superelevation records
	vector<SuperElevation> *GetSuperElevationVector();
	SuperElevation*	GetSuperElevation(unsigned int i);
	unsigned int GetSuperElevationCount();
	// Road crossfall records
	vector<Crossfall> *GetCrossfallVector();
	Crossfall*	GetCrossfall(unsigned int i);
	unsigned int GetCrossfallCount();
	// Road lane section records
	vector<LaneSection> *GetLaneSectionVector();
	LaneSection*	GetLaneSection(unsigned int i);
	unsigned int GetLaneSectionCount();
	// Road object records
	vector<Object> *GetObjectVector();
	Object*	GetObject(unsigned int i);
	unsigned int GetObjectCount();
	// Road signal records
	vector<Signal> *GetSignalVector();
	Signal*	GetSignal(unsigned int i);
	unsigned int GetSignalCount();
	//-------------------------------------------------

	/**
	 * Getters for the last child records in their respective vectors
	 */
	RoadType*		GetLastRoadType();
	GeometryBlock*	GetLastGeometryBlock();
	Elevation*		GetLastElevation();
	SuperElevation*	GetLastSuperElevation();
	Crossfall*		GetLastCrossfall();
	LaneSection*	GetLastLaneSection();
	Object*			GetLastObject();
	Signal*			GetLastSignal();

	/**
	 * Getters for the last added child records in their respective vectors
	 */
	RoadType*		GetLastAddedRoadType();
	GeometryBlock*	GetLastAddedGeometryBlock();
	Elevation*		GetLastAddedElevation();
	SuperElevation*	GetLastAddedSuperElevation();
	Crossfall*		GetLastAddedCrossfall();
	LaneSection*	GetLastAddedLaneSection();
	Object*			GetLastAddedObject();
	Signal*			GetLastAddedSignal();

	//-------------------------------------------------

	/**
	 * Setters for the base road properties
	 */
	void SetRoadName(string name);
	void SetRoadLength(double length);
	void SetRoadId(string roadId);
	void SetRoadJunction(string junction);

	/**
	 * Setters for the linking road properties
	 */
	void SetPredecessor(string elementType, string elementId, string contactPoint);
	void SetSuccessor(string elementType, string elementId, string contactPoint);
	void SetNeighbor(string side, string elementId, string direction);
	void SetNeighbor1(string side, string elementId, string direction);
	void SetNeighbor2(string side, string elementId, string direction);
	
	/**
	 * Removers for the linking road properties
	 */
	void RemovePredecessor();
	void RemoveSuccessor();
	void RemoveNeighbor1();
	void RemoveNeighbor2();

	//-------------------------------------------------

	/**
	 * Methods used to add child records to the respective vectors
	 */
	unsigned int AddRoadType(double s, string type);
	unsigned int AddGeometryBlock();
	unsigned int AddElevation(double s, double a, double b, double c, double d);
	unsigned int AddSuperElevation(double s, double a, double b, double c, double d);
	unsigned int AddCrossfall (string side, double s, double a, double b, double c, double d);
	unsigned int AddLaneSection(double s);
	unsigned int AddObject();
	unsigned int AddSignal();

	/**
	 * Methods used to clone child records in the respective vectors
	 */
	unsigned int CloneRoadType(unsigned int index);
	unsigned int CloneElevation(unsigned int index);
	unsigned int CloneSuperElevation(unsigned int index);
	unsigned int CloneCrossfall(unsigned int index);
	unsigned int CloneLaneSection(unsigned int index);
	unsigned int CloneLaneSectionEnd(unsigned int index);
	unsigned int CloneObject(unsigned int index);
	unsigned int CloneSignal(unsigned int index);

	/**
	 * Methods used to delete child records from the respective vectors
	 */
	void DeleteRoadType(unsigned int index);
	void DeleteGeometryBlock(unsigned int index);
	void DeleteElevation(unsigned int index);
	void DeleteSuperElevation(unsigned int index);
	void DeleteCrossfall(unsigned int index);
	void DeleteLaneSection(unsigned int index);
	void DeleteObject(unsigned int index);
	void DeleteSignal(unsigned int index);
	
	//-------------------------------------------------

	/**
	 * Recalculates the chordline geometry of the road
	 */
	void RecalculateGeometry();

	//-------------------------------------------------
	// EVALUATION METHODS

	/**
	 * Geometry evaluation
	 */
	bool CheckGeometryInterval (double s_check);
	bool CheckGeometryInterval (double s_check, string &roadId);
	short int GetGeometryCoords(double s_check, double &retX, double &retY);
	short int GetGeometryCoords(double s_check, double &retX, double &retY, double &retHDG);
	

	/**
	 * Other evaluation
	 */
	int CheckRoadTypeInterval(double s_check);
	string GetRoadTypeValue(double s_check);

	int CheckElevationInterval(double s_check);
	double GetElevationValue (double s_check);

	int CheckSuperElevationInterval(double s_check);
	double GetSuperElevationValue (double s_check);

	int CheckCrossfallInterval(double s_check);
	void GetCrossfallValue (double s_check, double &angleLeft, double &angleRight);

	int CheckLaneSectionInterval(double s_check);
	void FillLaneSectionSample(double s_check, LaneSectionSample &laneSectionSample);
	
	//-------------------------------------------------

	/**
	 * Destructor
	 */
	~Road();
};


//----------------------------------------------------------------------------------
/**
 * RoadLink class is used to store information about road's predecessors/successors
 *
 *
 *
 *
 */
class RoadLink
{
private:
	/**
	 * Base properties of a successor/predecessor record
	 */
	string mElementType;
	string mElementId;
	string mContactPoint;
public:
	/**
	 * Constructor which intializes the base properties
	 */
	RoadLink(string elementType, string elementId, string contactPoint);
	
	/**
	 * Setters for the base properties
	 */
	void SetElementType(string elementType);
	void SetElementId(string elementId);
	void SetContactPoint(string contactPoint);
	

	/**
	 * Getters for the base properties
	 */
	string GetElementType();
	string GetElementId();
	string GetContactPoint();
};



//----------------------------------------------------------------------------------
/**
 * RoadLink class is used to store information about road's neighbors
 *
 *
 *
 *
 */
class RoadNeighbor
{
private:
	/**
	 * Base properties of a neighbor record
	 */
	string mSide;
	string mElementId;
	string mDirection;
public:
	/**
	 * Constructor which intializes the base properties
	 */
	RoadNeighbor(string side, string elementId, string direction);
	
	/**
	 * Setters for the base properties
	 */
	void SetSide(string side);
	void SetElementId(string elementId);
	void SetDirection(string direction);
	
	/**
	 * Getters for the base properties
	 */
	string GetSide();
	string GetElementId();
	string GetDirection();
};

//----------------------------------------------------------------------------------
/**
 * RoadType class is used to store information about a road type record
 *
 *
 *
 *
 */
class RoadType
{
private:
	/**
	 * Base properties of a road type
	 */
	double mS;
	string mType;
public:
	/**
	 * Constructor which intializes the base properties
	 */
	RoadType (double s, string type);
	
	/**
	 * Setters for the base properties
	 */
	void SetS(double value);
	void SetType(string type);
	
	/**
	 * Getters for the base properties
	 */
	double GetS();
	string GetType();
};

//----------------------------------------------------------------------------------
/**
 * Elevation class is used to store information about a road elevation record
 * It inherits the Polynom class and has no additional properties
 *
 *
 *
 */
class Elevation : public ThirdOrderPolynom
{
public:
	/**
	 * Constructor which intializes the base properties
	 */
	Elevation(double s, double a, double b, double c, double d);
};
//----------------------------------------------------------------------------------


/**
 * Superlevation class is used to store information about a road superelevation record
 * It inherits the Polynom class and has no additional properties
 *
 *
 *
 */
class SuperElevation : public ThirdOrderPolynom
{
public:
	/**
	 * Constructor which intializes the base properties
	 */
	SuperElevation(double s, double a, double b, double c, double d);
};
//----------------------------------------------------------------------------------

/**
 * Crossfall class is used to store information about a road superelevation record
 * It inherits the Polynom class and has one additional properties
 *
 *
 *
 */
class Crossfall : public ThirdOrderPolynom
{
private:
	/**
	 * Base crossfall property
	 */
	string mSide;
	
public:
	/**
	 * Constructor which intializes the base properties
	 */
	Crossfall (string side, double s, double a, double b, double c, double d);
	
	/**
	 * Setter for the crossfall side
	 */
	void SetSide(string side);
	
	/**
	 * Getter for the crossfall side
	 */
	string GetSide();
};

//----------------------------------------------------------------------------------


#endif
