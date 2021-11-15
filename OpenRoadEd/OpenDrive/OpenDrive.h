#ifndef OPENDRIVE_H
#define OPENDRIVE_H

#include <vector>
#include <string>

#include "Road.h"
//--Prototypes--
//main
class Header;
//--------------


using std::vector;
using std::string;


/**
 * The main class in OpenDrive structure
 * Holds the two vectors of the top-level records: ROAD and JUNCTION
 * Has methods to add, get and delete those records
 * From this class - one could get access to any record in OpenDrive structure
 * going down the hierarchy
 */
class OpenDrive
{
private:
	/**
	 * Header of the OpenDrive file
	 */
	Header* mHeader;

	/**
	 * Vectors used to store the top-level ROAD and JUNCTION records
	 */
	vector<Road> mRoadVector;
	vector<Junction> mJunctionVector;
	
	/**
	 * Indices of the last added records
	 */
	unsigned int mLastAddedRoad;
	unsigned int mLastAddedJunction;

	//-------------------------------------------------

	/**
	 * Copy constructor, makes the object non-copyable
	 */
	OpenDrive (const OpenDrive& openDrive){};

	const OpenDrive& operator=(const OpenDrive& rhs);

public:
	/**
	 * Constructor
	 */
	OpenDrive();

	//-------------------------------------------------

	/**
	 * Sets the header of the OpenDrive file
	 */
	void SetHeader(unsigned short int revMajor, unsigned short int revMinor, string name, float version, string date, 
					double north, double south, double east,double west);
	
	/**
	 * Methods used to add records to the respective vectors
	 */
	unsigned int AddRoad(string name, double length, string id, string junction);
	unsigned int AddJunction(string name, string id);

	/**
	 * Methods used to delete records from the respective vectors
	 */
	void DeleteRoad(unsigned int index);
	void DeleteJunction(unsigned int index);

	//-------------------------------------------------

	/**
	 * Getters for the last child records in their respective vectors
	 */
	Road* GetLastRoad();
	Junction* GetLastJunction();

	/**
	 * Getters for the last added records in their respective vectors
	 */
	Road* GetLastAddedRoad();

	/**
	 * Getter for the OpenDrive header
	 */
	Header* GetHeader();

	/**
	 * Getters for the records and their vectors
	 */
	// Road records
	vector<Road> * GetRoadVector();
	Road* GetRoad(unsigned int i);
	unsigned int GetRoadCount();
	// Junction records
	vector<Junction> * GetJunctionVector();
	Junction* GetJunction(unsigned int i);
	unsigned int GetJunctionCount();
	
	//-------------------------------------------------


	/**
	 * Clears the OpenDrive structure, could be used to start a new document
	 */
	void Clear();


	/**
	 * Destructor
	 */
	~OpenDrive();
};



/**
 * Class used to store the heading details of the OpenDrive file
 */
class Header
{
private:
	/**
	 * Base properties
	 */
	unsigned short int mRevMajor;
	unsigned short int mRevMinor;
	string mName;
	float mVersion;
	string mDate;
	double mNorth;
	double mSouth;
	double mEast;
	double mWest;
public:
	/**
	 * Constructor that initializes the base properties
	 */
	Header(unsigned short int revMajor, unsigned short int revMinor, string name, float version, string date, 
		double north, double south, double east,double west);
	
	/**
	 * Getter for all properties
	 */
	void GetAllParams(unsigned short int &revMajor, unsigned short int &revMinor, string &name, float &version, string &date, 
		double &north, double &south, double &east,double &west);
	void GetXYValues(double &north, double &south, double &east,double &west);
	
	/**
	 * Setter for all properties
	 */
	void SetAllParams(unsigned short int revMajor, unsigned short int revMinor, string name, float version, string date, 
		double north, double south, double east,double west);
	void SetXYValues(double north, double south, double east,double west);
};


#endif
