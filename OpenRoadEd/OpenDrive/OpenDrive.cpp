#include "OpenDrive.h"


//***********************************************************************************
//OpenDRIVE Structure
//***********************************************************************************
/**
 * Constructor
 */
OpenDrive::OpenDrive()
{
	mHeader=NULL;
}


/**
 * Sets the header of the OpenDrive file
 */
void OpenDrive::SetHeader(unsigned short int revMajor, unsigned short int revMinor, string name, float version, string date, 
						  double north, double south, double east,double west)
{	
	if (mHeader==NULL)
		mHeader=new Header(revMajor, revMinor, name, version, date, north, south, east, west);
	else
	{
		mHeader->SetAllParams(revMajor, revMinor, name, version, date, north, south, east, west);
	}

}

/**
 * Methods used to add records to the respective vectors
 */
unsigned int OpenDrive::AddRoad(string name, double length, string id, string junction)
{
	unsigned int index=GetRoadCount();
	// Adds the new road to the end of the vector
	mRoadVector.push_back(Road(name, length, id, junction));
	// Saves the index of the newly added road
	mLastAddedRoad=index;
	return index;
}
unsigned int OpenDrive::AddJunction(string name, string id)
{
	unsigned int index=GetJunctionCount();
	// Adds the new junction to the end of the vector
	mJunctionVector.push_back(Junction(name,id));
	// Saves the index of the newly added junction
	mLastAddedJunction=index;
	return index;
}

/**
 * Methods used to delete records from the respective vectors
 */
void OpenDrive::DeleteRoad(unsigned int index)
{
	mRoadVector.erase(mRoadVector.begin()+index);
}
void OpenDrive::DeleteJunction(unsigned int index)
{
	mJunctionVector.erase(mJunctionVector.begin()+index);
}

//-------------------------------------------------

/**
 * Getters for the last child records in their respective vectors
 */
Road* OpenDrive::GetLastRoad()
{	
	if (mRoadVector.size()>0)
		return &(mRoadVector.at(mRoadVector.size()-1));
	else
		return NULL;
}
Junction* OpenDrive::GetLastJunction()
{
	if (mJunctionVector.size()>0)
		return &(mJunctionVector.at(mJunctionVector.size()-1));
	else
		return NULL;
}

/**
 * Getters for the last added records in their respective vectors
 */
Road* OpenDrive::GetLastAddedRoad()
{	
	if(mLastAddedRoad<mRoadVector.size())
		return &mRoadVector.at(mLastAddedRoad);
	else
		return NULL;
}

/**
 * Getter for the OpenDrive header
 */
Header* OpenDrive::GetHeader()
{ 
	return mHeader;
}

/**
 * Getters for the records and their vectors
 */
// Road records
vector<Road> * OpenDrive::GetRoadVector()
{
	return &mRoadVector;
}
Road* OpenDrive::GetRoad(unsigned int i)
{	
	if ((i < mRoadVector.size())&&( mRoadVector.size()>0))
		return &(mRoadVector.at(i));	
	else
		return NULL;
}
unsigned int OpenDrive::GetRoadCount()
{	
	return mRoadVector.size();	
}
// Junction records
vector<Junction> * OpenDrive::GetJunctionVector()
{
	return &mJunctionVector;
}
Junction* OpenDrive::GetJunction(unsigned int i)
{	if (i < mJunctionVector.size())
		return &(mJunctionVector.at(i));
	else
		return NULL;
}
unsigned int OpenDrive::GetJunctionCount()
{	
	return mJunctionVector.size();	
}
//-------------------------------------------------

/**
 * Clears the OpenDrive structure, could be used to start a new document
 */
void OpenDrive::Clear()
{
	mRoadVector.clear();
	mJunctionVector.clear();
}

/**
 * Destructor
 */
OpenDrive::~OpenDrive()
{
	if (mHeader!=NULL)
		delete mHeader;

	// DELETING ROADS
	mRoadVector.clear();

	// DELETING JUNCTIONS
	mJunctionVector.clear();
}


//***********************************************************************************
//Header
//***********************************************************************************
/**
 * Constructor that initializes the base properties
 */
Header::Header(unsigned short int revMajor, unsigned short int revMinor, string name, float version, string date, 
			   double north, double south, double east,double west)
{
	mRevMajor=revMajor;
	mRevMinor=revMinor;
	mName=name;
	mVersion=version;
	mDate=date;
	mNorth=north;
	mSouth=south;
	mEast=east;
	mWest=west;

}

/**
 * Getter for all properties
 */
void Header::GetAllParams(unsigned short int &revMajor, unsigned short int &revMinor, string &name, float &version, string &date, 
						  double &north, double &south, double &east,double &west)
{
	revMajor=mRevMajor;
	revMinor=mRevMinor;
	name=mName;
	version=mVersion;
	date=mDate;
	north=mNorth;
	south=mSouth;
	east=mEast;
	west=mWest;

}
void Header::GetXYValues(double &north, double &south, double &east,double &west)
{
	north=mNorth;
	south=mSouth;
	east=mEast;
	west=mWest;
}

/**
 * Setter for all properties
 */
void Header::SetAllParams(unsigned short int revMajor, unsigned short int revMinor, string name, float version, string date, 
						  double north, double south, double east,double west)
{
	mRevMajor=revMajor;
	mRevMinor=revMinor;
	mName=name;
	mVersion=version;
	mDate=date;
	mNorth=north;
	mSouth=south;
	mEast=east;
	mWest=west;
}
void Header::SetXYValues(double north, double south, double east,double west)
{
	mNorth=north;
	mSouth=south;
	mEast=east;
	mWest=west;
}
