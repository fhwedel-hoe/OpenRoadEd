#include "Road.h"
#define _USE_MATH_DEFINES
#include <math.h>




//***********************************************************************************
//Road segment
//***********************************************************************************
/**
 * Constructor 
 */
Road::Road()
{	
	mPredecessor=NULL; mSuccessor=NULL; mNeighbor1=NULL; mNeighbor2=NULL;	
}

/**
 * Constructor that initializes the road with basic properties
 * 
 * @param name Name of the road
 * @param length Length of the road
 * @param id Unique ID of the road
 * @param junction ID of the junction, this road might be a part of
 */
Road::Road(string name, double length, string id, string junction)
{	
	mPredecessor=NULL; mSuccessor=NULL; mNeighbor1=NULL; mNeighbor2=NULL;	mName=name; mLength=length; mId=id; mJunction=junction;
}

/**
 * Copy constructor
 */
Road::Road (const Road& road)
{
	mName=road.mName;
	mLength=road.mLength;
	mId=road.mId;
	mJunction=road.mJunction;

	mPredecessor=NULL;
	mSuccessor=NULL;
	mNeighbor1=NULL;
	mNeighbor2=NULL;

	if (road.mPredecessor!=NULL)
		mPredecessor = new RoadLink(road.mPredecessor->GetElementType(), road.mPredecessor->GetElementId(), road.mPredecessor->GetContactPoint());
	if (road.mSuccessor!=NULL)
		mSuccessor = new RoadLink(road.mSuccessor->GetElementType(), road.mSuccessor->GetElementId(), road.mSuccessor->GetContactPoint());
	if (road.mNeighbor1!=NULL)
		mNeighbor1 = new RoadNeighbor(road.mNeighbor1->GetSide(), road.mNeighbor1->GetElementId(), road.mNeighbor1->GetDirection());
	if (road.mNeighbor2!=NULL)
		mNeighbor2 = new RoadNeighbor(road.mNeighbor2->GetSide(), road.mNeighbor2->GetElementId(), road.mNeighbor2->GetDirection());

	mRoadTypeVector=road.mRoadTypeVector;
	mGeometryBlockVector=road.mGeometryBlockVector;
	mElevationVector=road.mElevationVector;
	mSuperElevationVector=road.mSuperElevationVector;
	mCrossfallVector=road.mCrossfallVector;
	mLaneSectionsVector=road.mLaneSectionsVector;
	mObjectsVector=road.mObjectsVector;
	mSignalsVector=road.mSignalsVector;
}

/**
 * Assignment operator overload
 */
const Road& Road::operator=(const Road& otherRoad)
{
	if (this!= &otherRoad)
	{
		mName=otherRoad.mName;
		mLength=otherRoad.mLength;
		mId=otherRoad.mId;
		mJunction=otherRoad.mJunction;

		delete mPredecessor;
		delete mSuccessor;
		delete mNeighbor1;
		delete mNeighbor2;

		mPredecessor=NULL;
		mSuccessor=NULL;
		mNeighbor1=NULL;
		mNeighbor2=NULL;

		if (otherRoad.mPredecessor!=NULL)
			mPredecessor = new RoadLink(otherRoad.mPredecessor->GetElementType(), otherRoad.mPredecessor->GetElementId(), otherRoad.mPredecessor->GetContactPoint());
		if (otherRoad.mSuccessor!=NULL)
			mSuccessor = new RoadLink(otherRoad.mSuccessor->GetElementType(), otherRoad.mSuccessor->GetElementId(), otherRoad.mSuccessor->GetContactPoint());
		if (otherRoad.mNeighbor1!=NULL)
			mNeighbor1 = new RoadNeighbor(otherRoad.mNeighbor1->GetSide(), otherRoad.mNeighbor1->GetElementId(), otherRoad.mNeighbor1->GetDirection());
		if (otherRoad.mNeighbor2!=NULL)
			mNeighbor2 = new RoadNeighbor(otherRoad.mNeighbor2->GetSide(), otherRoad.mNeighbor2->GetElementId(), otherRoad.mNeighbor2->GetDirection());

		mRoadTypeVector=otherRoad.mRoadTypeVector;
		mGeometryBlockVector=otherRoad.mGeometryBlockVector;
		mElevationVector=otherRoad.mElevationVector;
		mSuperElevationVector=otherRoad.mSuperElevationVector;
		mCrossfallVector=otherRoad.mCrossfallVector;
		mLaneSectionsVector=otherRoad.mLaneSectionsVector;
		mObjectsVector=otherRoad.mObjectsVector;
		mSignalsVector=otherRoad.mSignalsVector;
	}
	return *this;
}
//-------------------------------------------------

/**
 * Recalculates the chordline geometry of the road
 */
void Road::RecalculateGeometry()
{
	// Goes through geometry blocks and recalculates their coordinates and headings starting with the second record
	// so the second geometry will start at the coordinates where the first one ended
	double length=0;
	unsigned int lGeometryVectorSize = mGeometryBlockVector.size();
	if(lGeometryVectorSize>0)
	{
		double lS=0;
		double lX=0;
		double lY=0;
		double lHdg=0;
		mGeometryBlockVector.at(0).GetLastCoords(lS,lX,lY,lHdg);
		length+=mGeometryBlockVector.at(0).GetBlockLength();

		GeometryBlock *lGeometry;
		for(unsigned int i=1; i<lGeometryVectorSize; i++)
		{
			lGeometry=&mGeometryBlockVector.at(i);
			lGeometry->Recalculate(lS,lX,lY,lHdg);
			lGeometry->GetLastCoords(lS,lX,lY,lHdg);
			length+=lGeometry->GetBlockLength();
		}
	}

	mLength=length;
}

/**
 * Getters for the basic properties of the road
 */
string Road::GetRoadName() const
{
	return mName;
}
double Road::GetRoadLength() const
{
	return mLength;
}
string Road::GetRoadId() const
{
	return mId;
}
string Road::GetRoadJunction() const
{
	return mJunction;
}

/**
 * Getters for the linking properties of the road
 */
RoadLink* Road::GetPredecessor()
{	
	return mPredecessor;	
}
RoadLink* Road::GetSuccessor()
{	
	return mSuccessor;	
}
RoadNeighbor* Road::GetNeighbor1()
{	
	return mNeighbor1;	
}
RoadNeighbor* Road::GetNeighbor2()
{	
	return mNeighbor2;	
}


/**
 * Getters for the child records and their vectors
 */
// Road type records
vector<RoadType> *Road::GetRoadTypeVector()
{
	return &mRoadTypeVector;
}
RoadType* Road::GetRoadType(unsigned int i)
{	
	if ((mRoadTypeVector.size()>0)&&(i<mRoadTypeVector.size()))
		return &mRoadTypeVector.at(i);
	else
		return NULL;
}
unsigned int Road::GetRoadTypeCount()
{
	return mRoadTypeVector.size();
}
// Road geometry records
vector<GeometryBlock> *Road::GetGeometryBlockVector()
{
	return &mGeometryBlockVector;
}
GeometryBlock* Road::GetGeometryBlock(unsigned int i)
{	
	if ((mGeometryBlockVector.size()>0)&&(i<mGeometryBlockVector.size()))
		return &mGeometryBlockVector.at(i);
	else
		return NULL;
}
unsigned int Road::GetGeometryBlockCount()
{
	return mGeometryBlockVector.size();
}
// Road elevation records
vector<Elevation> *Road::GetElevationVector()
{
	return &mElevationVector;
}
Elevation*	Road::GetElevation(unsigned int i)
{	
	if ((mElevationVector.size()>0)&&(i<mElevationVector.size()))
		return &mElevationVector.at(i);
	else
		return NULL;
}
unsigned int Road::GetElevationCount()
{
	return mElevationVector.size();
}
// Road superelevation records
vector<SuperElevation> *Road::GetSuperElevationVector()
{
	return &mSuperElevationVector;
}
SuperElevation*	Road::GetSuperElevation(unsigned int i)
{	
	if ((mSuperElevationVector.size()>0)&&(i<mSuperElevationVector.size()))
		return &mSuperElevationVector.at(i);
	else
		return NULL;
}
unsigned int Road::GetSuperElevationCount()
{
	return mSuperElevationVector.size();
}
// Road crossfall records
vector<Crossfall> *Road::GetCrossfallVector()
{
	return &mCrossfallVector;
}
Crossfall*	Road::GetCrossfall(unsigned int i)
{	
	if ((mCrossfallVector.size()>0)&&(i<mCrossfallVector.size()))
		return &mCrossfallVector.at(i);
	else
		return NULL;
}
unsigned int Road::GetCrossfallCount()
{
	return mCrossfallVector.size();
}
// Road lane section records
vector<LaneSection> *Road::GetLaneSectionVector()
{
	return &mLaneSectionsVector;
}
LaneSection*	Road::GetLaneSection(unsigned int i)
{	
	if ((mLaneSectionsVector.size()>0)&&(i<mLaneSectionsVector.size()))
		return &mLaneSectionsVector.at(i);
	else
		return NULL;
}
unsigned int Road::GetLaneSectionCount()
{
	return mLaneSectionsVector.size();
}
// Road object records
vector<Object> *Road::GetObjectVector()
{
	return &mObjectsVector;
}
Object*	Road::GetObject(unsigned int i)
{	
	if ((mObjectsVector.size()>0)&&(i<mObjectsVector.size()))
		return &mObjectsVector.at(i);
	else
		return NULL;
}
unsigned int Road::GetObjectCount()
{
	return mObjectsVector.size();
}
// Road signal records
vector<Signal> *Road::GetSignalVector()
{
	return &mSignalsVector;
}
Signal*	Road::GetSignal(unsigned int i)
{	
	if ((mSignalsVector.size()>0)&&(i<mSignalsVector.size()))
		return &mSignalsVector.at(i);
	else
		return NULL;
}
unsigned int Road::GetSignalCount()
{
	return mSignalsVector.size();
}
//-------------------------------------------------

/**
 * Getters for the last child records in their respective vectors
 */
RoadType* Road::GetLastRoadType()
{	
	if (mRoadTypeVector.size()>0)
		return &mRoadTypeVector.at(mRoadTypeVector.size()-1);
	else
		return NULL;
}
GeometryBlock* Road::GetLastGeometryBlock()
{	
	if (mGeometryBlockVector.size()>0)
		return &mGeometryBlockVector.at(mGeometryBlockVector.size()-1);
	else
		return NULL;
}
Elevation*	Road::GetLastElevation()
{	
	if (mElevationVector.size()>0)
		return &mElevationVector.at(mElevationVector.size()-1);
	else
		return NULL;
}
SuperElevation*	Road::GetLastSuperElevation()
{	
	if (mSuperElevationVector.size()>0)
		return &mSuperElevationVector.at(mSuperElevationVector.size()-1);
	else
		return NULL;
}
Crossfall*	Road::GetLastCrossfall()
{	
	if (mCrossfallVector.size()>0)
		return &mCrossfallVector.at(mCrossfallVector.size()-1);
	else
		return NULL;
}
LaneSection*	Road::GetLastLaneSection()
{	
	if (mLaneSectionsVector.size()>0)
		return &mLaneSectionsVector.at(mLaneSectionsVector.size()-1);
	else
		return NULL;
}
Object*	Road::GetLastObject()
{	
	if (mObjectsVector.size()>0)
		return &mObjectsVector.at(mObjectsVector.size()-1);
	else
		return NULL;
}
Signal*	Road::GetLastSignal()
{	
	if (mSignalsVector.size()>0)
		return &mSignalsVector.at(mSignalsVector.size()-1);
	else
		return NULL;
}


/**
 * Getters for the last added child records in their respective vectors
 */
RoadType* Road::GetLastAddedRoadType()
{
	if(mLastAddedRoadType<mRoadTypeVector.size())
		return &mRoadTypeVector.at(mLastAddedRoadType);
	else
		return NULL;
}
GeometryBlock* Road::GetLastAddedGeometryBlock()
{
	if(mLastAddedGeometryBlock<mGeometryBlockVector.size())
		return &mGeometryBlockVector.at(mLastAddedGeometryBlock);
	else
		return NULL;
}
Elevation* Road::GetLastAddedElevation()
{
	if(mLastAddedElevation<mElevationVector.size())
		return &mElevationVector.at(mLastAddedElevation);
	else
		return NULL;
}
SuperElevation* Road::GetLastAddedSuperElevation()
{
	if(mLastAddedSuperElevation<mSuperElevationVector.size())
		return &mSuperElevationVector.at(mLastAddedSuperElevation);
	else
		return NULL;
}
Crossfall* Road::GetLastAddedCrossfall()
{
	if(mLastAddedCrossfall<mCrossfallVector.size())
		return &mCrossfallVector.at(mLastAddedCrossfall);
	else
		return NULL;
}
LaneSection* Road::GetLastAddedLaneSection()
{
	if(mLastAddedLaneSection<mLaneSectionsVector.size())
		return &mLaneSectionsVector.at(mLastAddedLaneSection);
	else
		return NULL;
}
Object* Road::GetLastAddedObject()
{
	if(mLastAddedObject<mObjectsVector.size())
		return &mObjectsVector.at(mLastAddedObject);
	else
		return NULL;
}
Signal* Road::GetLastAddedSignal()
{
	if(mLastAddedSignal<mSignalsVector.size())
		return &mSignalsVector.at(mLastAddedSignal);
	else
		return NULL;
}
//-------------------------------------------------

/**
 * Setters for the basic road properties
 */
void Road::SetRoadName(string name)
{
	mName=name;
}
void Road::SetRoadLength(double length)
{
	mLength=length;
}
void Road::SetRoadId(string id)
{
	mId=id;
}
void Road::SetRoadJunction(string junction)
{
	mJunction=junction;
}

/**
 * Setters for the linking road properties
 */
void Road::SetPredecessor(string elementType, string elementId, string contactPoint)
{
	if(mPredecessor!=NULL)
	{
		mPredecessor->SetElementType(elementType);
		mPredecessor->SetElementId(elementId);
		mPredecessor->SetContactPoint(contactPoint);
	}
	else mPredecessor = new RoadLink(elementType, elementId,contactPoint);	
}
void Road::SetSuccessor(string elementType, string elementId, string contactPoint)
{
	if(mSuccessor!=NULL)
	{
		mSuccessor->SetElementType(elementType);
		mSuccessor->SetElementId(elementId);
		mSuccessor->SetContactPoint(contactPoint);
	}
	else mSuccessor=new RoadLink(elementType, elementId,contactPoint);	
}
void Road::SetNeighbor(string side, string elementId, string direction)
{
	if (mNeighbor1==NULL)
		mNeighbor1=new RoadNeighbor(side, elementId, direction);
	else
		mNeighbor2=new RoadNeighbor(side, elementId, direction);
}
void Road::SetNeighbor1(string side, string elementId, string direction)
{
	if (mNeighbor1==NULL) mNeighbor1=new RoadNeighbor(side, elementId, direction);
}
void Road::SetNeighbor2(string side, string elementId, string direction)
{
	if (mNeighbor2==NULL) mNeighbor2=new RoadNeighbor(side, elementId, direction);
}

/**
 * Removers for the linking road properties
 */
void Road::RemovePredecessor()
{
	if(mPredecessor!=NULL)
	{
		delete mPredecessor;
		mPredecessor = NULL;
	}
}
void Road::RemoveSuccessor()
{
	if(mSuccessor!=NULL)
	{
		delete mSuccessor;
		mSuccessor = NULL;
	}
}
void Road::RemoveNeighbor1()
{
	if(mNeighbor1!=NULL)
	{
		delete mNeighbor1;
		mNeighbor1 = NULL;
	}
}
void Road::RemoveNeighbor2()
{
	if(mNeighbor2!=NULL)
	{
		delete mNeighbor2;
		mNeighbor2 = NULL;
	}
}
//-------------------------------------------------

/**
 * Methods used to add child records to the respective vectors
 */
unsigned int Road::AddRoadType(double s, string type)
{	
	// Gets the index where the record should be inserted in the vector
	unsigned int index = CheckRoadTypeInterval(s)+1;
	// If larger than the record count - push to the back
	if(index>=GetRoadTypeCount()) mRoadTypeVector.push_back(RoadType(s, type));
	// else insert in the middle
	else mRoadTypeVector.insert(mRoadTypeVector.begin()+index, RoadType(s, type));
	// Save the last added record index
	mLastAddedRoadType=index;
	return index;
}
//-------------
unsigned int Road::AddGeometryBlock()
{	
	// Check the first method in the group for details

	unsigned int index=GetGeometryBlockCount();
	mGeometryBlockVector.push_back(GeometryBlock());
	mLastAddedGeometryBlock=index;
	return index;
}
//-------------
unsigned int Road::AddElevation(double s, double a, double b, double c, double d)
{	
	// Check the first method in the group for details

	unsigned int index = CheckElevationInterval(s)+1;
	if(index>=GetElevationCount()) mElevationVector.push_back(Elevation(s,a,b,c,d));
	else mElevationVector.insert(mElevationVector.begin()+index, Elevation(s,a,b,c,d));
	mLastAddedElevation=index;
	return index;
}
//-------------
unsigned int Road::AddSuperElevation(double s, double a, double b, double c, double d)
{	
	// Check the first method in the group for details

	unsigned int index = CheckSuperElevationInterval(s)+1;
	if(index>=GetSuperElevationCount()) mSuperElevationVector.push_back(SuperElevation(s,a,b,c,d));
	else mSuperElevationVector.insert(mSuperElevationVector.begin()+index, SuperElevation(s,a,b,c,d));
	mLastAddedSuperElevation=index;
	return index;
}
//-------------
unsigned int Road::AddCrossfall (string side, double s, double a, double b, double c, double d)
{	
	// Check the first method in the group for details

	unsigned int index = CheckCrossfallInterval(s)+1;
	if(index>=GetCrossfallCount()) mCrossfallVector.push_back(Crossfall(side,s,a,b,c,d));
	else mCrossfallVector.insert(mCrossfallVector.begin()+index, Crossfall(side,s,a,b,c,d));
	mLastAddedCrossfall=index;
	return index;
}
//-------------
unsigned int Road::AddLaneSection(double s)
{
	// Check the first method in the group for details

	unsigned int index = CheckLaneSectionInterval(s)+1;
	if(index>=GetLaneSectionCount()) mLaneSectionsVector.push_back(LaneSection(s));
	else mLaneSectionsVector.insert(mLaneSectionsVector.begin()+index, LaneSection(s));
	mLastAddedLaneSection=index;
	return index;
}
//-------------
unsigned int Road::AddObject()
{	
	// Check the first method in the group for details

	unsigned int index=GetObjectCount();
	mObjectsVector.push_back(Object());
	mLastAddedObject=index;
	return index;
}
//-------------
unsigned int Road::AddSignal()
{
	// Check the first method in the group for details

	unsigned int index=GetSignalCount();
	mSignalsVector.push_back(Signal());	
	mLastAddedSignal=index;
	return index;
}
//-----------


/**
 * Methods used to clone child records in the respective vectors
 */
unsigned int Road::CloneRoadType(unsigned int index)
{
	// Clone the object and insert it in the middle of the vector
	if(index<mRoadTypeVector.size()-1)
		mRoadTypeVector.insert(mRoadTypeVector.begin()+index+1, mRoadTypeVector[index]);
	// or just push it to the back
	else if(index==mRoadTypeVector.size()-1)
		mRoadTypeVector.push_back(mRoadTypeVector[index]);
	// Save the last added record index
	mLastAddedRoadType=index+1;
	return mLastAddedRoadType;
}
unsigned int Road::CloneElevation(unsigned int index)
{
	// Check the first method in the group for details

	if(index<mElevationVector.size()-1)
		mElevationVector.insert(mElevationVector.begin()+index+1, mElevationVector[index]);
	else if(index==mElevationVector.size()-1)
		mElevationVector.push_back(mElevationVector[index]);
	mLastAddedElevation=index+1;
	return mLastAddedElevation;
}
unsigned int Road::CloneSuperElevation(unsigned int index)
{
	// Check the first method in the group for details

	if(index<mSuperElevationVector.size()-1)
		mSuperElevationVector.insert(mSuperElevationVector.begin()+index+1, mSuperElevationVector[index]);
	else if(index==mSuperElevationVector.size()-1)
		mSuperElevationVector.push_back(mSuperElevationVector[index]);
	mLastAddedSuperElevation=index+1;
	return mLastAddedSuperElevation;
}
unsigned int Road::CloneCrossfall(unsigned int index)
{
	// Check the first method in the group for details

	if(index<mCrossfallVector.size()-1)
		mCrossfallVector.insert(mCrossfallVector.begin()+index+1, mCrossfallVector[index]);
	else if(index==mCrossfallVector.size()-1)
		mCrossfallVector.push_back(mCrossfallVector[index]);
	mLastAddedCrossfall=index+1;
	return mLastAddedCrossfall;
}
unsigned int Road::CloneLaneSection(unsigned int index)
{
	// Check the first method in the group for details

	if(index<mLaneSectionsVector.size()-1)
		mLaneSectionsVector.insert(mLaneSectionsVector.begin()+index+1, mLaneSectionsVector[index]);
	else if(index==mLaneSectionsVector.size()-1)
		mLaneSectionsVector.push_back(mLaneSectionsVector[index]);
	mLastAddedLaneSection=index+1;
	return mLastAddedLaneSection;
}
unsigned int Road::CloneLaneSectionEnd(unsigned int index)
{
	// Check the first method in the group for details

	// Clones the lane section, duplicating only the last records in each child category
	LaneSection lNewLaneSection(mLaneSectionsVector[index].GetS());
	unsigned int iLaneCount=mLaneSectionsVector[index].GetLaneCount();

	double lHighestS = 0;

	for(unsigned int iLane=0; iLane<iLaneCount; iLane++)
	{
		Lane *lLane = mLaneSectionsVector[index].GetLane(iLane);
		lNewLaneSection.AddLane(lLane->GetSide(), lLane->GetId(), lLane->GetType(), lLane->GetLevel(),false);

		Lane *lNewLane = lNewLaneSection.GetLastAddedLane();

		//width
		LaneWidth *lWidth = lLane->GetLaneWidth(lLane->GetLaneWidthCount()-1);
		if(lWidth!=NULL) 
		{
			lNewLane->AddWidthRecord(0.0, lWidth->GetA(), lWidth->GetB(), lWidth->GetC(), lWidth->GetD());
			if(lWidth->GetS()>lHighestS) lHighestS=lWidth->GetS();
		}

		//road mark
		LaneRoadMark *lRoadMark = lLane->GetLaneRoadMark(lLane->GetLaneRoadMarkCount()-1);
		if(lRoadMark!=NULL) 
		{
			lNewLane->AddRoadMarkRecord(0.0, lRoadMark->GetType(), lRoadMark->GetWeight(), lRoadMark->GetColor(), lRoadMark->GetWidth(), lRoadMark->GetLaneChange());
			if(lRoadMark->GetS()>lHighestS) lHighestS=lRoadMark->GetS();
		}

		//material
		LaneMaterial *lMaterial = lLane->GetLaneMaterial(lLane->GetLaneMaterialCount()-1);
		if(lMaterial!=NULL) 
		{
			lNewLane->AddMaterialRecord(0.0, lMaterial->GetSurface(), lMaterial->GetFriction(), lMaterial->GetRoughness());
			if(lMaterial->GetS()>lHighestS) lHighestS=lMaterial->GetS();
		}

		//visibility
		LaneVisibility *lVisibility = lLane->GetLaneVisibility(lLane->GetLaneVisibilityCount()-1);
		if(lVisibility!=NULL) 
		{
			lNewLane->AddVisibilityRecord(0.0, lVisibility->GetForward(), lVisibility->GetBack(), lVisibility->GetLeft(), lVisibility->GetRight());
			if(lVisibility->GetS()>lHighestS) lHighestS=lVisibility->GetS();
		}

		//speed
		LaneSpeed *lSpeed = lLane->GetLaneSpeed(lLane->GetLaneSpeedCount()-1);
		if(lSpeed!=NULL) 
		{
			lNewLane->AddSpeedRecord(0.0, lSpeed->GetMax());
			if(lSpeed->GetS()>lHighestS) lHighestS=lSpeed->GetS();
		}

		//access
		LaneAccess *lAccess = lLane->GetLaneAccess(lLane->GetLaneAccessCount()-1);
		if(lAccess!=NULL) 
		{
			lNewLane->AddAccessRecord(0.0, lAccess->GetRestriction());
			if(lAccess->GetS()>lHighestS) lHighestS=lAccess->GetS();
		}

		//height
		LaneHeight *lHeight = lLane->GetLaneHeight(lLane->GetLaneHeightCount()-1);
		if(lHeight!=NULL) 
		{
			lNewLane->AddHeightRecord(0.0, lHeight->GetInner(), lHeight->GetOuter());
			if(lHeight->GetS()>lHighestS) lHighestS=lHeight->GetS();
		}
	}

	lHighestS += mLaneSectionsVector[index].GetS();

	if(index+1 < mLaneSectionsVector.size())
	{
		if(lHighestS < mLaneSectionsVector[index+1].GetS())
			lNewLaneSection.SetS(lHighestS);
	}


	if(index<mLaneSectionsVector.size()-1)
		mLaneSectionsVector.insert(mLaneSectionsVector.begin()+index+1, lNewLaneSection);
	else if(index==mLaneSectionsVector.size()-1)
		mLaneSectionsVector.push_back(lNewLaneSection);
	mLastAddedLaneSection=index+1;
	return mLastAddedLaneSection;
}
unsigned int Road::CloneObject(unsigned int index)
{
	// Check the first method in the group for details

	if(index<mSignalsVector.size()-1)
		mSignalsVector.insert(mSignalsVector.begin()+index+1, mSignalsVector[index]);
	else if(index==mSignalsVector.size()-1)
		mSignalsVector.push_back(mSignalsVector[index]);
	mLastAddedObject=index+1;
	return mLastAddedObject;
}
unsigned int Road::CloneSignal(unsigned int index)
{
	// Check the first method in the group for details

	if(index<mSignalsVector.size()-1)
		mSignalsVector.insert(mSignalsVector.begin()+index+1, mSignalsVector[index]);
	else if(index==mSignalsVector.size()-1)
		mSignalsVector.push_back(mSignalsVector[index]);
	mLastAddedSignal=index+1;
	return mLastAddedSignal;
}

/**
 * Methods used to delete child records from the respective vectors
 */
void Road::DeleteRoadType(unsigned int index)
{
	mRoadTypeVector.erase(mRoadTypeVector.begin()+index);
}
void Road::DeleteGeometryBlock(unsigned int index)
{
	mGeometryBlockVector.erase(mGeometryBlockVector.begin()+index);
}
void Road::DeleteElevation(unsigned int index)
{
	mElevationVector.erase(mElevationVector.begin()+index);
}
void Road::DeleteSuperElevation(unsigned int index)
{
	mSuperElevationVector.erase(mSuperElevationVector.begin()+index);
}
void Road::DeleteCrossfall(unsigned int index)
{
	mCrossfallVector.erase(mCrossfallVector.begin()+index);
}
void Road::DeleteLaneSection(unsigned int index)
{
	mLaneSectionsVector.erase(mLaneSectionsVector.begin()+index);
}
void Road::DeleteObject(unsigned int index)
{
	mObjectsVector.erase(mObjectsVector.begin()+index);
}
void Road::DeleteSignal(unsigned int index)
{
	mSignalsVector.erase(mSignalsVector.begin()+index);
}

//-------------------------------------------------
// EVALUATION METHODS

/**
 * Geometry evaluation
 */
bool Road::CheckGeometryInterval (double s_check)
{
	string tmp;
	return CheckGeometryInterval(s_check,tmp);
}
//-----------
bool Road::CheckGeometryInterval (double s_check, string &roadId)
{
	for (unsigned int i=0;i<mGeometryBlockVector.size();i++)
	{
		if (mGeometryBlockVector.at(i).CheckInterval(s_check))
		{
			roadId=mId;
			return true;
		}
	}
	roadId="N/A";
	return false;
}
//-----------
short int Road::GetGeometryCoords(double s_check, double &retX, double &retY)
{
	double tmp;
	return GetGeometryCoords(s_check,retX,retY, tmp);
}
//-------------
short int Road::GetGeometryCoords(double s_check, double &retX, double &retY, double &retHDG)
{
	//go trough all of the blocks
	for (unsigned int i=0; i<mGeometryBlockVector.size();i++)
	{
		//Check the block and get coords.
		short int res=mGeometryBlockVector.at(i).GetCoords(s_check,retX,retY, retHDG);
		// If the returned value is one of the geometry types (for 0=line,1=arc and 2=spiral) then the result has been found and parameters filled, so, return the value
		if (res>=0  ) 
			return res;
	}
	//if s_check does not belong to the road, return -999
	return -999;
}
//-----------

/**
 * Other evaluation
 */
int  Road::CheckRoadTypeInterval(double s_check)
{
	int res=-1;
	//Go through all the road type records
	for (unsigned int i=0;i<mRoadTypeVector.size();i++)
	{
		//check if the s_check belongs to the current record
		if (s_check >= mRoadTypeVector.at(i).GetS())
			res=i;	//assign it to the result id
		else 
			break;	//if not, break;
	}
	return res;		//return the result: 0 to MaxInt as the index to the record containing s_check or -1 if nothing found
}
//-----------
string  Road::GetRoadTypeValue(double s_check)
{
	string retType="unknown";
	//find the record where s_check belongs
	int index=	CheckRoadTypeInterval(s_check);
	//If found, return the type
	if (index>=0)
		retType= mRoadTypeVector.at(index).GetType();
	return retType;
}
//-----------
int  Road::CheckElevationInterval(double s_check)
{
	int res=-1;
	//Go through all the road type records
	for (unsigned int i=0;i<mElevationVector.size();i++)
	{
		//check if the s_check belongs to the current record
		if (mElevationVector.at(i).CheckInterval(s_check))
			res=i;	//assign it to the result id
		else 
			break;	//if not, break;
	}
	return res;		//return the result: 0 to MaxInt as the index to the record containing s_check or -1 if nothing found
}
//-----------
double  Road::GetElevationValue (double s_check)
{
	double retVal=0;
	//find the record where s_check belongs
	int index=CheckElevationInterval(s_check);
	//If found, return the type
	if (index>=0)
		retVal= (mElevationVector.at(index).GetValue(s_check));
	return retVal;

}
//-----------
int  Road::CheckSuperElevationInterval(double s_check)
{
	int res=-1;
	//Go through all the road type records
	for (unsigned int i=0;i<mSuperElevationVector.size();i++)
	{
		//check if the s_check belongs to the current record
		if (mSuperElevationVector.at(i).CheckInterval(s_check))
			res=i;	//assign it to the result id
		else 
			break;	//if not, break;
	}
	return res;		//return the result: 0 to MaxInt as the index to the record containing s_check or -1 if nothing found
}
//-----------
double  Road::GetSuperElevationValue (double s_check)
{
	double retVal=0;
	//find the record where s_check belongs
	int index=CheckSuperElevationInterval(s_check);
	//If found, return the type
	if (index>=0)
		retVal= (mSuperElevationVector.at(index).GetValue(s_check));

	return retVal;
}
//-----------
int  Road::CheckCrossfallInterval(double s_check)
{
	int res=-1;
	//Go through all the road type records
	for (unsigned int i=0;i<mCrossfallVector.size();i++)
	{
		//check if the s_check belongs to the current record
		if (mCrossfallVector.at(i).CheckInterval(s_check))
			res=i;	//assign it to the result id
		else 
			break;	//if not, break;
	}
	return res;		//return the result: 0 to MaxInt as the index to the record containing s_check or -1 if nothing found
}
//-----------
void  Road::GetCrossfallValue (double s_check, double &angleLeft, double &angleRight)
{
	angleLeft=0.0;
	angleRight=0.0;
	//find the record where s_check belongs
	int index=CheckCrossfallInterval(s_check);
	//If found, return the type
	string side;
	double angle=0.0;
	if (index>=0)
	{
		angle =(mCrossfallVector.at(index).GetValue(s_check));
		side=(mCrossfallVector.at(index).GetSide());
	}
	
	if (side.compare("left")==0)
	{
		angleLeft=-angle;
	}
	else if (side.compare("right")==0)
	{
		angleRight=-angle;
	}
	else
	{
		angleLeft=-angle;
		angleRight=-angle;
	}
}
//-----------
int  Road::CheckLaneSectionInterval(double s_check)
{
	int res=-1;
	//Go through all the lane section records
	for (unsigned int i=0;i<mLaneSectionsVector.size();i++)
	{
		//check if the s_check belongs to the current record
		if (mLaneSectionsVector.at(i).CheckInterval(s_check))
			res=i;	//assign it to the result id
		else 
			break;	//if not, break;
	}
	return res;		//return the result: 0 to MaxInt as the index to the record containing s_check or -1 if nothing found
}
//-----------
void  Road::FillLaneSectionSample(double s_check, LaneSectionSample& laneSectionSample)
{
	int index=CheckLaneSectionInterval(s_check);
	if (index>=0)
		mLaneSectionsVector.at(index).FillLaneSectionSample(s_check,laneSectionSample);
}

//-------------------------------------------------

/**
 * Destructor
 */
Road::~Road()
{
	delete mPredecessor;
	delete mSuccessor;
	delete mNeighbor1;
	delete mNeighbor2;

	// DELETING ROAD TYPES
	mRoadTypeVector.clear();

	// DELETING GEOMETRY BLOKS
	mGeometryBlockVector.clear();

	// DELETING ELEVATIONS
	mElevationVector.clear();

	// DELETING SUPERELEVATION
	mSuperElevationVector.clear();

	// DELETING CROSSFALL
	mCrossfallVector.clear();

	// DELETING LANE SECTIONS
	mLaneSectionsVector.clear();

	// DELETING OBJECTS
	mObjectsVector.clear();

	// DELETING SIGNALS
	mSignalsVector.clear();
}




//***********************************************************************************
//Road Link Record
//***********************************************************************************
/**
 * Constructor which intializes the basic properties
 */
RoadLink::RoadLink(string elementType, string elementId, string contactPoint)
{
	mElementType=elementType;
	mElementId=elementId;
	mContactPoint=contactPoint;
}

/**
 * Getters for the basic properties
 */
string RoadLink::GetElementType()
{	
	return mElementType;	
}
string RoadLink::GetElementId()
{	
	return mElementId;	
}
string RoadLink::GetContactPoint()
{	
	return mContactPoint;	
}

/**
 * Setters for the basic properties
 */
void RoadLink::SetElementType(string elementType)
{	
	mElementType=elementType;	
}
void RoadLink::SetElementId(string elementId)
{	
	mElementId=elementId;
}
void RoadLink::SetContactPoint(string contactPoint)
{	
	mContactPoint=contactPoint;	
}


//***********************************************************************************
//Road Neighbor Record
//***********************************************************************************
/**
 * Constructor which intializes the basic properties
 */
RoadNeighbor::RoadNeighbor(string side, string elementId, string direction)
{
	mSide=side;
	mElementId=elementId;
	mDirection=direction;
}
/**
 * Getters for the basic properties
 */
string RoadNeighbor::GetSide()
{	
	return mSide;	
}
string RoadNeighbor::GetElementId()
{	
	return mElementId;	
}
string RoadNeighbor::GetDirection()
{	
	return mDirection;	
}

/**
 * Setters for the basic properties
 */
void RoadNeighbor::SetSide(string side)
{	
	mSide=side;	
}
void RoadNeighbor::SetElementId(string elementId)
{	
	mElementId=elementId;	
}
void RoadNeighbor::SetDirection(string direction)
{	
	mDirection=direction;	
}


//***********************************************************************************
//Road Type
//***********************************************************************************
/**
 * Constructor which intializes the basic properties
 */
RoadType::RoadType (double s, string type)
{	
	mS=s; mType=type;	
}

/**
 * Setters for the basic properties
 */
void RoadType::SetS(double value)
{
	mS=value;
}
void RoadType::SetType(string type)
{
	mType=type;
}

/**
 * Getters for the basic properties
 */
double RoadType::GetS()
{
	return mS;
}
string RoadType::GetType()
{
	return mType;
}




//***********************************************************************************
//Elevation record
//***********************************************************************************
/**
 * Constructor which intializes the basic properties
 */
Elevation::Elevation(double s, double a, double b, double c, double d): ThirdOrderPolynom(s,a,b,c,d)
{}





//***********************************************************************************
//Elevation record
//***********************************************************************************
/**
 * Constructor which intializes the basic properties
 */
SuperElevation::SuperElevation(double s, double a, double b, double c, double d): ThirdOrderPolynom(s,a,b,c,d)
{}





//***********************************************************************************
//Crossfall Record
//***********************************************************************************
/**
 * Constructor which intializes the basic properties
 */
Crossfall::Crossfall (string side, double s, double a, double b, double c, double d):ThirdOrderPolynom(s,a,b,c,d)
{	
	mSide=side;	
}

/**
 * Getters for the crossfall side
 */
string Crossfall::GetSide()
{
	return mSide;
}

/**
 * Setters for the crossfall side
 */
void Crossfall::SetSide(string side)
{
	mSide=side;
}

