#include "Lane.h"




/**
* Lane section class. Holds all the lane section information
*
*
*
*
*/

/**
* Constructor. Sets basic lane section parameters
* @param s s-offset of the lane section
*/
LaneSection::LaneSection (double s)
{	mS=s;	}

/**
* Add a lane to the lane section
* @param side the side of the road to which the lane will be added
* @param id ID of the lane
* @param type Type of the lane (Section 6.5 of the OpenDRIVE specification) 
* @param level Level parameter of the road
* @param sort Defines if the lanes should be sorted when added. True by default
*/
unsigned int LaneSection::AddLane(short int side, int id, string type, bool level, bool sort)
{	
	unsigned int index=0;
	//if lanes are sorted, add the lane to the correct side
	if(sort)
	{
		if(side<0)
		{
			index=GetLaneCount();
			mLaneVector.push_back(Lane(side,id,type,level));	
			mLastAddedLane=index;
		}
		else if(side==0)
		{
			int sz=GetLaneCount();
			if(sz>0)
			{
				for(int i=0; i<sz; i++)
				{
					if(mLaneVector[i].GetId()<0)
					{
						index=i;
						mLaneVector.insert(mLaneVector.begin()+index, Lane(side,id,type,level));
						mLastAddedLane=index;
						break;
					}
				}
			}
			else
			{
				index=0;
				mLaneVector.push_back(Lane(side,id,type,level));
				mLastAddedLane=index;
			}
		}
		else
		{
			index=0;
			mLaneVector.insert(mLaneVector.begin(), Lane(side,id,type,level));
			mLastAddedLane=index;
		}

		return index;
	}
	else
	{
		index=GetLaneCount();
		mLaneVector.push_back(Lane(side,id,type,level));	
		mLastAddedLane=index;
		return index;
	}	
}

/**
* Delete the lane at the provided index
*/
void LaneSection::DeleteLane(unsigned int index)
{
	mLaneVector.erase(mLaneVector.begin()+index);
}

/**
* Delete the outside left or right lane 
*/
void LaneSection::DeleteLeftLane()
{
	mLaneVector.erase(mLaneVector.begin());
}
void LaneSection::DeleteRigthLane()
{
	mLaneVector.pop_back();
}

/**
* Get the last lane
* @return A pointer to Lane object
*/
Lane* LaneSection::GetLastLane()
{
	if (mLaneVector.size()>0)
		return &mLaneVector.at(mLaneVector.size()-1);
	else
		return NULL;
}

/**
* Get the last added lane (which might not be the one from the end of the vector)
* @return A pointer to Lane object
*/
Lane* LaneSection::GetLastAddedLane()
{
	if(mLastAddedLane<mLaneVector.size())
		return &mLaneVector.at(mLastAddedLane);
	else
		return NULL;
}

/**
* Get the last left lane
* @return A pointer to Lane object
*/
Lane* LaneSection::GetLastLeftLane()
{
	if(mLaneVector.size()>0)
	{
		if(mLaneVector.at(0).GetSide()>0)
			return &mLaneVector.at(0);
		else
			return NULL;
	}
	else
		return NULL;
}

/**
* Get the last center lane
* @return A pointer to Lane object
*/
Lane* LaneSection::GetLastCenterLane()
{
	int sz=GetLaneCount();
	for(int i=0; i<sz; i++)
	{
		if(mLaneVector[i].GetSide()==0)
		{
			return &mLaneVector.at(i);
		}
	}
	return NULL;
}

/**
* Get the last right lane
* @return A pointer to Lane object
*/
Lane* LaneSection::GetLastRightLane()
{
	if(mLaneVector.size()>0)
	{
		int indexLast=mLaneVector.size()-1;
		if(mLaneVector.at(indexLast).GetSide()<0)
			return &mLaneVector.at(indexLast);
		else
			return NULL;
	}
	else return NULL;
}
/**
* Get the lane vector
* @return A pointer to a vector of type Lane
*/
vector<Lane>* LaneSection::GetLaneVector()
{
	return &mLaneVector;
}

/**
* Get the lane by providing its index
* @param i Index of the lane to be returned
* @return A pointer to Lane object
*/
Lane* LaneSection::GetLane(unsigned int i)
{
	if ((mLaneVector.size()>0)&&(i<mLaneVector.size()))
		return &mLaneVector.at(i);
	else
		return NULL;
}

/**
* Get the lane number
* @return Unsigned int with that stores the number of lanes
*/
unsigned int LaneSection::GetLaneCount()
{
	return mLaneVector.size();
}

/**
* Get the lane section s-offset
*/
double LaneSection::GetS()
{
	return mS;
}

/**
* Get the lane section final s-offset which is the s-offset of the last record of the lane section
*/
double LaneSection::GetS2()
{
	double lHighestS=0;

	int sz=GetLaneCount();
	for(int i=0; i<sz; i++)
	{
		Lane *lLane = GetLane(i);

		//width
		LaneWidth *lWidth = lLane->GetLaneWidth(lLane->GetLaneWidthCount()-1);
		if(lWidth!=NULL) 
		{
			if(lWidth->GetS()>lHighestS) lHighestS=lWidth->GetS();
		}

		//road mark
		LaneRoadMark *lRoadMark = lLane->GetLaneRoadMark(lLane->GetLaneRoadMarkCount()-1);
		if(lRoadMark!=NULL) 
		{
			if(lRoadMark->GetS()>lHighestS) lHighestS=lRoadMark->GetS();
		}

		//material
		LaneMaterial *lMaterial = lLane->GetLaneMaterial(lLane->GetLaneMaterialCount()-1);
		if(lMaterial!=NULL) 
		{
			if(lMaterial->GetS()>lHighestS) lHighestS=lMaterial->GetS();
		}

		//visibility
		LaneVisibility *lVisibility = lLane->GetLaneVisibility(lLane->GetLaneVisibilityCount()-1);
		if(lVisibility!=NULL) 
		{
			if(lVisibility->GetS()>lHighestS) lHighestS=lVisibility->GetS();
		}

		//speed
		LaneSpeed *lSpeed = lLane->GetLaneSpeed(lLane->GetLaneSpeedCount()-1);
		if(lSpeed!=NULL) 
		{
			if(lSpeed->GetS()>lHighestS) lHighestS=lSpeed->GetS();
		}

		//access
		LaneAccess *lAccess = lLane->GetLaneAccess(lLane->GetLaneAccessCount()-1);
		if(lAccess!=NULL) 
		{
			if(lAccess->GetS()>lHighestS) lHighestS=lAccess->GetS();
		}

		//height
		LaneHeight *lHeight = lLane->GetLaneHeight(lLane->GetLaneHeightCount()-1);
		if(lHeight!=NULL) 
		{
			if(lHeight->GetS()>lHighestS) lHighestS=lHeight->GetS();
		}
	}

	return mS+lHighestS;

}

/**
* Set the lane section s-offset
*/
void LaneSection::SetS(double value)
{
	mS=value;
}


/**
* Check if the tested s-offset is inside the lane section interval
* @param A double s-offset value that has to be checked
* @return Return true if the s-offset value belongs to current lane section, false otherwise
*/
bool LaneSection::CheckInterval(double s_check)
{
	if (s_check>=mS)
		return true;
	else 
		return false;
}

/**
* Return the lane-0 index in the lanes vector
* @return An unsigned int value with the index
*/
unsigned int LaneSection::GetZeroLaneIndex()
{
	for (unsigned int i=0; i<GetLaneCount(); i++)
	{
		if(mLaneVector.at(i).GetId()==0)
			return i;
	}
	return 0;
}

/**
* Return the number of left lanes
* @return An unsigned int value with the number of left lanes
*/
unsigned int LaneSection::GetLeftLaneCount()
{
	unsigned int count=0;
	for (unsigned int i=0;i<GetLaneCount();i++)
	{
		if(mLaneVector.at(i).GetSide()==1)
			count++;
	}
	return count;
}

/**
* Return the number of central lanes
* @return An unsigned int value with the number of central lanes
*/
unsigned int LaneSection::GetCenterLaneCount()
{
	unsigned int count=0;
	for(unsigned int i=0; i<GetLaneCount(); i++)
	{
		if(mLaneVector[i].GetSide()==0)
		{
			count++;
		}
	}
	return count;
}

/**
* Return the number of right lanes
* @return An unsigned int value with the number of right lanes
*/
unsigned int LaneSection::GetRightLaneCount()
{
	unsigned int count=0;
	for (unsigned int i=0;i<GetLaneCount();i++)
	{
		if(mLaneVector.at(i).GetSide()==-1)
			count++;
	}
	return count;
}

/**
* Fill a special structure with all the lane / lane section data that is sampled at a provided s-offset position along the road
* This data is used later to fill the geometry arrays
* @param s_chek s-offset along the road at which to sample the lane section
* @param laneSectionSample The structure that has to be filled with the sampled data
* @return Returns true if the operation was successful. 
*/
bool LaneSection::FillLaneSectionSample(double s_check, LaneSectionSample& laneSectionSample)
{
	//clear and initialize variables
	laneSectionSample.ClearVectors();
	double width=0;
	int leftMax=0;
	int rightMax=GetLaneCount()-1;

	s_check-=GetS();

	bool level;
	string type;
	LaneHeight height; 
	LaneRoadMark roadMark;
	//Fill in left width vector
	//if there are left lanes
	if (GetLeftLaneCount()>0)
	{	
		//go through all of them
		for (int i=GetZeroLaneIndex(); i>=leftMax;i--)
		{	
			type=GetLane(i)->GetType();
			level=GetLane(i)->GetLevel();
			height=GetLane(i)->GetHeightValue(s_check);
			roadMark=GetLane(i)->GetRoadMarkValue(s_check);
			//and accumulate the width
			width=GetLane(i)->GetWidthValue(s_check);

			laneSectionSample.AddLeftRecord(type, width, height, roadMark, level);
		}
	}

	//same for the right side of the road
	if (GetRightLaneCount()>0)
	{	
		//go through all of them
		for (int i=GetZeroLaneIndex(); i<=rightMax;i++)
		{	
			type=GetLane(i)->GetType();
			level=GetLane(i)->GetLevel();
			height=GetLane(i)->GetHeightValue(s_check);
			roadMark=GetLane(i)->GetRoadMarkValue(s_check);
			//and accumulate the width
			width=GetLane(i)->GetWidthValue(s_check);

			laneSectionSample.AddRightRecord(type, width, height, roadMark, level);	
		}
	}
	return true;
}

/**
* Destructor. Delete all the members of the vectors: mLeft, mCenter, mRight
*/
LaneSection::~LaneSection()
{
	// DELETING LANES
	mLaneVector.clear();
}


/**
* Lane Section Sample. Holds all the lane information at a certain S value including lane widths, levels, 
* heights, etc
*
*
*
*
*/ 

LaneSectionSample::LaneSectionSample()
{}

/*
* Add various elements to the structure. Depending on the the value to be added, various input parameters are used.
* The methods are divided into left and right for left and right sides of the road.
*/
void LaneSectionSample::AddLeftType(string type)
{	mLeftTypeVector.push_back(type);	}
void LaneSectionSample::AddLeftWidth(double width)
{	mLeftWidthVector.push_back(width);	}
void LaneSectionSample::AddLeftHeight(LaneHeight height)
{	mLeftHeightVector.push_back(height);	}
void LaneSectionSample::AddLeftRoadMark(LaneRoadMark roadMark)
{	mLeftRoadMarkVector.push_back(roadMark);	}
void LaneSectionSample::AddLeftLevel(bool level)
{	mLeftLevelVector.push_back(level);	}

void LaneSectionSample::AddRightType(string type)
{	mRightTypeVector.push_back(type);	}
void LaneSectionSample::AddRightWidth(double width)
{	mRightWidthVector.push_back(width);	}
void LaneSectionSample::AddRightHeight(LaneHeight height)
{	mRightHeightVector.push_back(height);	}
void LaneSectionSample::AddRightRoadMark(LaneRoadMark roadMark)
{	mRightRoadMarkVector.push_back(roadMark);	}
void LaneSectionSample::AddRightLevel(bool level)
{	mRightLevelVector.push_back(level);	}

void LaneSectionSample::AddLeftRecord(string type, double width, LaneHeight height, LaneRoadMark roadMark, bool level)
{
	AddLeftType(type);
	AddLeftWidth(width);
	AddLeftHeight(height);
	AddLeftRoadMark(roadMark);
	AddLeftLevel(level);
}
void LaneSectionSample::AddRightRecord(string type, double width, LaneHeight height, LaneRoadMark roadMark, bool level)
{
	AddRightType(type);
	AddRightWidth(width);
	AddRightHeight(height);
	AddRightRoadMark(roadMark);
	AddRightLevel(level);
}

/*
* Get various elements of the structure. The methods return type depends on the elements that are returned.
* The methods are divided into left and right for left and right sides of the road.
*/
string LaneSectionSample::GetLeftType(unsigned int i)
{	return mLeftTypeVector.at(i);	}
double LaneSectionSample::GetLeftWidth(unsigned int i)
{	return mLeftWidthVector.at(i);	}
LaneHeight LaneSectionSample::GetLeftHeight(unsigned int i)
{	return mLeftHeightVector.at(i);	}
LaneRoadMark LaneSectionSample::GetLeftRoadMark(unsigned int i)
{	return mLeftRoadMarkVector.at(i);	}
bool LaneSectionSample::GetLeftLevel(unsigned int i)
{	return mLeftLevelVector.at(i);	}

string LaneSectionSample::GetRightType(unsigned int i)
{	return mRightTypeVector.at(i);	}
double LaneSectionSample::GetRightWidth(unsigned int i)
{	return mRightWidthVector.at(i);	}
LaneHeight LaneSectionSample::GetRightHeight(unsigned int i)
{	return mRightHeightVector.at(i);	}
LaneRoadMark LaneSectionSample::GetRightRoadMark(unsigned int i)
{	return mRightRoadMarkVector.at(i);	}
bool LaneSectionSample::GetRightLevel(unsigned int i)
{	return mRightLevelVector.at(i);	}


/*
* Get the number of elements in the vectors
*/
unsigned int LaneSectionSample::GetLeftVectorsSize()
{	return mLeftWidthVector.size();	}
unsigned int LaneSectionSample::GetRightVectorsSize()
{	return mRightWidthVector.size();	}


/*
* Get the various record vectors. The vector type depends on the record
* The methods are divided into left and right for left and right sides of the road.
*/
vector<string>* LaneSectionSample::GetLeftTypeVector()
{	return &mLeftTypeVector;	}
vector<double>* LaneSectionSample::GetLeftWidthVector()
{	return &mLeftWidthVector;	}
vector<LaneHeight>* LaneSectionSample::GetLeftHeigthVector()
{	return &mLeftHeightVector;	}
vector<LaneRoadMark>* LaneSectionSample::GetLeftRoadMarkVector()
{	return &mLeftRoadMarkVector;	}
vector<bool>* LaneSectionSample::GetLeftLevelVector()
{	return &mLeftLevelVector;	}

vector<string>* LaneSectionSample::GetRightTypeVector()
{	return &mRightTypeVector;	}
vector<double>* LaneSectionSample::GetRightWidthVector()
{	return &mRightWidthVector;	}
vector<LaneHeight>* LaneSectionSample::GetRightHeigthVector()
{	return &mRightHeightVector;	}
vector<LaneRoadMark>* LaneSectionSample::GetRightRoadMarkVector()
{	return &mRightRoadMarkVector;	}
vector<bool>* LaneSectionSample::GetRightLevelVector()
{	return &mRightLevelVector;	}

/*
* Clear the vectors
*/
void LaneSectionSample::ClearVectors()
{
	mLeftTypeVector.clear();
	mLeftWidthVector.clear();
	mLeftHeightVector.clear();
	mLeftRoadMarkVector.clear();
	mLeftLevelVector.clear();

	mRightTypeVector.clear();
	mRightWidthVector.clear();
	mRightHeightVector.clear();
	mRightRoadMarkVector.clear();
	mRightLevelVector.clear();
}

/**
* Lane class. Holds all the record data that describes a lane
*
*
*
*
*
*/

/**
*	Constructor
*/
Lane::Lane(short int side, int id, string type, bool level)
{	mSide=side; mId=id; mType=type; mLevel=level;	mPredecessorExists=false; mSuccessorExists=false;	}

/**
*	Various set methods.
*/
void Lane::SetSide(short int side)
{
	mSide=side;
}
void Lane::SetId(int id)
{
	mId=id;
}
void Lane::SetType(string type)
{
	mType=type;
}
void Lane::SetLevel(bool level)
{
	mLevel=level;
}
//-------------
void Lane::SetPredecessor(int predecessor)
{	mPredecessor=predecessor; mPredecessorExists=true;	}
//-------------
void Lane::SetSuccessor(int successor)
{	mSuccessor=successor;	mSuccessorExists=true;	}

/**
*	Remove lane linkage
*/
void Lane::RemovePredecessor()
{	mPredecessor=0;	mPredecessorExists=false;	}

void Lane::RemoveSuccessor()
{	mSuccessor=0;	mSuccessorExists=false;		}


/**
 * Methods used to add child records to the respective vectors
 */
unsigned int Lane::AddWidthRecord(double s, double a, double b, double c, double d)
{	
	// Gets the index where the record should be inserted in the vector
	unsigned int index = CheckWidthInterval(s)+1;
	// If larger than the record count - push to the back
	if(index>=GetLaneWidthCount()) mLaneWidth.push_back(LaneWidth(s,a,b,c,d));	
	// else insert in the middle
	else mLaneWidth.insert(mLaneWidth.begin()+index, LaneWidth(s,a,b,c,d));
	// Save the last added record index
	mLastAddedLaneWidth=index;
	return index;
}
//-------------
unsigned int Lane::AddRoadMarkRecord(double sOffset, string type, string weight, string color, double width, string laneChange)
{	
	// Check the first method in the group for details

	unsigned int index = CheckRoadMarkInterval(sOffset)+1;
	if(index>=GetLaneRoadMarkCount()) mLaneRoadMark.push_back(LaneRoadMark(sOffset, type, weight, color, width, laneChange));	
	else mLaneRoadMark.insert(mLaneRoadMark.begin()+index, LaneRoadMark(sOffset, type, weight, color, width, laneChange));
	mLastAddedLaneRoadMark=index;
	return index;
}
//-------------
unsigned int Lane::AddMaterialRecord(double sOffset, string surface, double friction, double roughness)
{	
	// Check the first method in the group for details

	unsigned int index = CheckMaterialInterval(sOffset)+1;
	if(index>=GetLaneMaterialCount()) mLaneMaterial.push_back(LaneMaterial(sOffset,surface,friction,roughness));	
	else mLaneMaterial.insert(mLaneMaterial.begin()+index, LaneMaterial(sOffset,surface,friction,roughness));
	mLastAddedLaneMaterial=index;
	return index;
}
//-------------
unsigned int Lane::AddVisibilityRecord(double sOffset, double forward, double back, double left, double right)
{	
	// Check the first method in the group for details

	unsigned int index = CheckVisibilityInterval(sOffset)+1;
	if(index>=GetLaneVisibilityCount()) mLaneVisibility.push_back(LaneVisibility(sOffset,forward,back,left,right));	
	else mLaneVisibility.insert(mLaneVisibility.begin()+index, LaneVisibility(sOffset,forward,back,left,right));
	mLastAddedLaneVisibility=index;
	return index;
}
//-------------
unsigned int Lane::AddSpeedRecord(double sOffset, double max)
{	
	// Check the first method in the group for details

	unsigned int index = CheckSpeedInterval(sOffset)+1;
	if(index>=GetLaneSpeedCount()) mLaneSpeed.push_back(LaneSpeed(sOffset,max));	
	else mLaneSpeed.insert(mLaneSpeed.begin()+index, LaneSpeed(sOffset,max));
	mLastAddedLaneSpeed=index;
	return index;
}
//-------------
unsigned int Lane::AddAccessRecord(double sOffset, string restriction)
{	
	// Check the first method in the group for details

	unsigned int index = CheckAccessInterval(sOffset)+1;
	if(index>=GetLaneAccessCount()) mLaneAccess.push_back(LaneAccess(sOffset,restriction));	
	else mLaneAccess.insert(mLaneAccess.begin()+index, LaneAccess(sOffset,restriction));
	mLastAddedLaneAccess=index;
	return index;
}
//-------------
unsigned int Lane::AddHeightRecord(double sOffset, double inner, double outer)
{	
	// Check the first method in the group for details

	unsigned int index = CheckHeightInterval(sOffset)+1;
	if(index>=GetLaneHeightCount()) mLaneHeight.push_back(LaneHeight(sOffset,inner,outer));	
	else mLaneHeight.insert(mLaneHeight.begin()+index, LaneHeight(sOffset,inner,outer));
	mLastAddedLaneHeight=index;
	return index;
}

/**
 * Methods used to clone child records in the respective vectors
 */
unsigned int Lane::CloneLaneWidth(unsigned int index)
{
	// Clone the object and insert it in the middle of the vector
	if(index<mLaneWidth.size()-1)
		mLaneWidth.insert(mLaneWidth.begin()+index+1, mLaneWidth[index]);
	// or just push it to the back
	else if(index==mLaneWidth.size()-1)
		mLaneWidth.push_back(mLaneWidth[index]);
	// Save the last added record index
	mLastAddedLaneWidth=index+1;
	return mLastAddedLaneWidth;
}
unsigned int Lane::CloneLaneRoadMark(unsigned int index)
{
	// Check the first method in the group for details

	if(index<mLaneRoadMark.size()-1)
		mLaneRoadMark.insert(mLaneRoadMark.begin()+index+1, mLaneRoadMark[index]);
	else if(index==mLaneRoadMark.size()-1)
		mLaneRoadMark.push_back(mLaneRoadMark[index]);
	mLastAddedLaneRoadMark=index+1;
	return mLastAddedLaneRoadMark;
}
unsigned int Lane::CloneLaneMaterial(unsigned int index)
{
	// Check the first method in the group for details

	if(index<mLaneMaterial.size()-1)
		mLaneMaterial.insert(mLaneMaterial.begin()+index+1, mLaneMaterial[index]);
	else if(index==mLaneMaterial.size()-1)
		mLaneMaterial.push_back(mLaneMaterial[index]);
	mLastAddedLaneMaterial=index+1;
	return mLastAddedLaneMaterial;
}
unsigned int Lane::CloneLaneVisibility(unsigned int index)
{
	// Check the first method in the group for details

	if(index<mLaneVisibility.size()-1)
		mLaneVisibility.insert(mLaneVisibility.begin()+index+1, mLaneVisibility[index]);
	else if(index==mLaneVisibility.size()-1)
		mLaneVisibility.push_back(mLaneVisibility[index]);
	mLastAddedLaneVisibility=index+1;
	return mLastAddedLaneVisibility;
}
unsigned int Lane::CloneLaneSpeed(unsigned int index)
{
	// Check the first method in the group for details

	if(index<mLaneSpeed.size()-1)
		mLaneSpeed.insert(mLaneSpeed.begin()+index+1, mLaneSpeed[index]);
	else if(index==mLaneSpeed.size()-1)
		mLaneSpeed.push_back(mLaneSpeed[index]);
	mLastAddedLaneSpeed=index+1;
	return mLastAddedLaneSpeed;
}
unsigned int Lane::CloneLaneAccess(unsigned int index)
{
	// Check the first method in the group for details

	if(index<mLaneAccess.size()-1)
		mLaneAccess.insert(mLaneAccess.begin()+index+1, mLaneAccess[index]);
	else if(index==mLaneAccess.size()-1)
		mLaneAccess.push_back(mLaneAccess[index]);
	mLastAddedLaneAccess=index+1;
	return mLastAddedLaneAccess;
}
unsigned int Lane::CloneLaneHeight(unsigned int index)
{
	// Check the first method in the group for details

	if(index<mLaneHeight.size()-1)
		mLaneHeight.insert(mLaneHeight.begin()+index+1, mLaneHeight[index]);
	else if(index==mLaneHeight.size()-1)
		mLaneHeight.push_back(mLaneHeight[index]);
	mLastAddedLaneHeight=index+1;
	return mLastAddedLaneHeight;
}

/**
 * Methods used to delete child records from the respective vectors
 */
void Lane::DeleteLaneWidth(unsigned int index)
{
	mLaneWidth.erase(mLaneWidth.begin()+index);
}
void Lane::DeleteLaneRoadMark(unsigned int index)
{
	mLaneRoadMark.erase(mLaneRoadMark.begin()+index);
}
void Lane::DeleteLaneMaterial(unsigned int index)
{
	mLaneMaterial.erase(mLaneMaterial.begin()+index);
}
void Lane::DeleteLaneVisibility(unsigned int index)
{
	mLaneVisibility.erase(mLaneVisibility.begin()+index);
}
void Lane::DeleteLaneSpeed(unsigned int index)
{
	mLaneSpeed.erase(mLaneSpeed.begin()+index);
}
void Lane::DeleteLaneAccess(unsigned int index)
{
	mLaneAccess.erase(mLaneAccess.begin()+index);
}
void Lane::DeleteLaneHeight(unsigned int index)
{
	mLaneHeight.erase(mLaneHeight.begin()+index);
}


/**
*	Getters of the lane parameters
*/
int Lane::GetSide()
{
	return mSide;
}
int Lane::GetId()
{
	return mId;
}
string Lane::GetType()
{
	return mType;
}
bool Lane::GetLevel()
{
	return mLevel;
}

/**
*	Check if linkage information is provided
*/
bool Lane::IsPredecessorSet()
{
	return mPredecessorExists;
}
int Lane::GetPredecessor()
{
	return mPredecessor;
}
bool Lane::IsSuccessorSet()
{
	return mSuccessorExists;
}
int Lane::GetSuccessor()
{
	return mSuccessor;
}


/**
*	Get pointers to the records vectors
*/
vector <LaneWidth> *Lane::GetLaneWidthVector()
{	return &mLaneWidth;	}

vector <LaneRoadMark> *Lane::GetLaneRoadMarkVector()
{	return &mLaneRoadMark;	}

vector <LaneMaterial> *Lane::GetLaneMaterialVector()
{	return &mLaneMaterial;	}

vector <LaneVisibility> *Lane::GetLaneVisibilityVector()
{	return &mLaneVisibility;	}

vector <LaneSpeed> *Lane::GetLaneSpeedVector()
{	return &mLaneSpeed;	}

vector <LaneAccess> *Lane::GetLaneAccessVector()
{	return &mLaneAccess;	}

vector <LaneHeight> *Lane::GetLaneHeightVector()
{	return &mLaneHeight;	}


/**
*	Get the number of elements in a certain vector
*/
unsigned int Lane::GetLaneWidthCount()
{	return mLaneWidth.size();	}

unsigned int Lane::GetLaneRoadMarkCount()
{	return mLaneRoadMark.size();	}

unsigned int Lane::GetLaneMaterialCount()
{	return mLaneMaterial.size();	}

unsigned int Lane::GetLaneVisibilityCount()
{	return mLaneVisibility.size();	}

unsigned int Lane::GetLaneSpeedCount()
{	return mLaneSpeed.size();	}

unsigned int Lane::GetLaneAccessCount()
{	return mLaneAccess.size();	}

unsigned int Lane::GetLaneHeightCount()
{	return mLaneHeight.size();	}

/**
*	Get the elements of a certain vectors at position i
*/
LaneWidth* Lane::GetLaneWidth(unsigned int i)
{
	if ((mLaneWidth.size()>0)&&(i<mLaneWidth.size()))
		return &mLaneWidth.at(i);
	else
		return NULL;
}

LaneRoadMark* Lane::GetLaneRoadMark(unsigned int i)
{
	if ((mLaneRoadMark.size()>0)&&(i<mLaneRoadMark.size()))
		return &mLaneRoadMark.at(i);
	else
		return NULL;
}

LaneMaterial* Lane::GetLaneMaterial(unsigned int i)
{
	if ((mLaneMaterial.size()>0)&&(i<mLaneMaterial.size()))
		return &mLaneMaterial.at(i);
	else
		return NULL;
}

LaneVisibility* Lane::GetLaneVisibility(unsigned int i)
{
	if ((mLaneVisibility.size()>0)&&(i<mLaneVisibility.size()))
		return &mLaneVisibility.at(i);
	else
		return NULL;
}

LaneSpeed* Lane::GetLaneSpeed(unsigned int i)
{
	if ((mLaneSpeed.size()>0)&&(i<mLaneSpeed.size()))
		return &mLaneSpeed.at(i);
	else
		return NULL;
}

LaneAccess* Lane::GetLaneAccess(unsigned int i)
{
	if ((mLaneAccess.size()>0)&&(i<mLaneAccess.size()))
		return &mLaneAccess.at(i);
	else
		return NULL;
}

LaneHeight* Lane::GetLaneHeight(unsigned int i)
{
	if ((mLaneHeight.size()>0)&&(i<mLaneHeight.size()))
		return &mLaneHeight.at(i);
	else
		return NULL;
}


/**
*	Get the last elements of a certain vectors
*/
LaneWidth* Lane::GetLastLaneWidth()
{
	if (mLaneWidth.size()>0)
		return &mLaneWidth.at(mLaneWidth.size()-1);
	else
		return NULL;
}
LaneRoadMark* Lane::GetLastLaneRoadMark()
{
	if (mLaneRoadMark.size()>0)
		return &mLaneRoadMark.at(mLaneRoadMark.size()-1);
	else
		return NULL;
}
LaneMaterial* Lane::GetLastLaneMaterial()
{
	if (mLaneMaterial.size()>0)
		return &mLaneMaterial.at(mLaneMaterial.size()-1);
	else
		return NULL;
}
LaneVisibility* Lane::GetLastLaneVisibility()
{
	if (mLaneVisibility.size()>0)
		return &mLaneVisibility.at(mLaneVisibility.size()-1);
	else
		return NULL;
}
LaneSpeed* Lane::GetLastLaneSpeed()
{
	if (mLaneSpeed.size()>0)
		return &mLaneSpeed.at(mLaneSpeed.size()-1);
	else
		return NULL;
}
LaneAccess* Lane::GetLastLaneAccess()
{
	if (mLaneAccess.size()>0)
		return &mLaneAccess.at(mLaneAccess.size()-1);
	else
		return NULL;
}
LaneHeight* Lane::GetLastLaneHeight()
{
	if (mLaneHeight.size()>0)
		return &mLaneHeight.at(mLaneHeight.size()-1);
	else
		return NULL;
}

/**
*	Get the last added elements of a certain vectors (their position might not be at the end of the vector)
*/
LaneWidth* Lane::GetLastAddedLaneWidth()
{
	if(mLastAddedLaneWidth<mLaneWidth.size())
		return &mLaneWidth.at(mLastAddedLaneWidth);
	else
		return NULL;
}
LaneRoadMark* Lane::GetLastAddedLaneRoadMark()
{
	if(mLastAddedLaneRoadMark<mLaneRoadMark.size())
		return &mLaneRoadMark.at(mLastAddedLaneRoadMark);
	else
		return NULL;
}
LaneMaterial* Lane::GetLastAddedLaneMaterial()
{
	if(mLastAddedLaneMaterial<mLaneMaterial.size())
		return &mLaneMaterial.at(mLastAddedLaneMaterial);
	else
		return NULL;
}
LaneVisibility* Lane::GetLastAddedLaneVisibility()
{
	if(mLastAddedLaneVisibility<mLaneVisibility.size())
		return &mLaneVisibility.at(mLastAddedLaneVisibility);
	else
		return NULL;
}
LaneSpeed* Lane::GetLastAddedLaneSpeed()
{
	if(mLastAddedLaneSpeed<mLaneSpeed.size())
		return &mLaneSpeed.at(mLastAddedLaneSpeed);
	else
		return NULL;
}
LaneAccess* Lane::GetLastAddedLaneAccess()
{
	if(mLastAddedLaneAccess<mLaneAccess.size())
		return &mLaneAccess.at(mLastAddedLaneAccess);
	else
		return NULL;
}
LaneHeight* Lane::GetLastAddedLaneHeight()
{
	if(mLastAddedLaneHeight<mLaneHeight.size())
		return &mLaneHeight.at(mLastAddedLaneHeight);
	else
		return NULL;
}

/**
*	Check the intervals and return the index of the records that applies to the provided s-offset
*/
int  Lane::CheckWidthInterval(double s_check)
{

	int res=-1;
	//Go through all the width records
	for (unsigned int i=0;i<mLaneWidth.size();i++)
	{
		//check if the s_check belongs to the current record
		if (s_check >= mLaneWidth.at(i).GetS())
			res=i;	//assign it to the result id
		else 
			break;	//if not, break;
	}
	return res;		//return the result: 0 to MaxInt as the index to the record containing s_check or -1 if nothing found
}
int Lane::CheckRoadMarkInterval(double s_check)
{
	int res=-1;
	//Go through all the road mark records
	for (unsigned int i=0;i<mLaneRoadMark.size();i++)
	{
		//check if the s_check belongs to the current record
		if (s_check >= mLaneRoadMark.at(i).GetS())
			res=i;	//assign it to the result id
		else 
			break;	//if not, break;
	}
	return res;		//return the result: 0 to MaxInt as the index to the record containing s_check or -1 if nothing found
}
int Lane::CheckMaterialInterval(double s_check)
{
	int res=-1;
	//Go through all the material records
	for (unsigned int i=0;i<mLaneMaterial.size();i++)
	{
		//check if the s_check belongs to the current record
		if (s_check >= mLaneMaterial.at(i).GetS())
			res=i;	//assign it to the result id
		else 
			break;	//if not, break;
	}
	return res;		//return the result: 0 to MaxInt as the index to the record containing s_check or -1 if nothing found
}
int Lane::CheckVisibilityInterval(double s_check)
{
	int res=-1;
	//Go through all the visibility records
	for (unsigned int i=0;i<mLaneVisibility.size();i++)
	{
		//check if the s_check belongs to the current record
		if (s_check >= mLaneVisibility.at(i).GetS())
			res=i;	//assign it to the result id
		else 
			break;	//if not, break;
	}
	return res;		//return the result: 0 to MaxInt as the index to the record containing s_check or -1 if nothing found
}
int Lane::CheckSpeedInterval(double s_check)
{
	int res=-1;
	//Go through all the speed records
	for (unsigned int i=0;i<mLaneSpeed.size();i++)
	{
		//check if the s_check belongs to the current record
		if (s_check >= mLaneSpeed.at(i).GetS())
			res=i;	//assign it to the result id
		else 
			break;	//if not, break;
	}
	return res;		//return the result: 0 to MaxInt as the index to the record containing s_check or -1 if nothing found
}
int Lane::CheckAccessInterval(double s_check)
{
	int res=-1;
	//Go through all the access records
	for (unsigned int i=0;i<mLaneAccess.size();i++)
	{
		//check if the s_check belongs to the current record
		if (s_check >= mLaneAccess.at(i).GetS())
			res=i;	//assign it to the result id
		else 
			break;	//if not, break;
	}
	return res;		//return the result: 0 to MaxInt as the index to the record containing s_check or -1 if nothing found
}
int Lane::CheckHeightInterval(double s_check)
{
	int res=-1;
	//Go through all the height records
	for (unsigned int i=0;i<mLaneHeight.size();i++)
	{
		//check if the s_check belongs to the current record
		if (s_check >= mLaneHeight.at(i).GetS())
			res=i;	//assign it to the result id
		else 
			break;	//if not, break;
	}
	return res;		//return the result: 0 to MaxInt as the index to the record containing s_check or -1 if nothing found
}

/**
*	Evaluate the record and return the width value
*/
double  Lane::GetWidthValue(double s_check)
{
	double retVal=0;
	//find the record where s_check belongs
	int index=CheckWidthInterval(s_check);
	//If found, return the type
	if (index>=0)
		retVal= mLaneWidth.at(index).GetValue(s_check);
	return retVal;
}

/**
*	Evaluate the record and return the height object
*/
LaneHeight  Lane::GetHeightValue(double s_check)
{
	LaneHeight  retVal(0,0,0);
	//find the record where s_check belongs
	int index=CheckHeightInterval(s_check);
	//If found, return the type
	if (index>=0)
	{
		retVal.SetInner(mLaneHeight.at(index).GetInner());
		retVal.SetOuter(mLaneHeight.at(index).GetOuter());
	}
	return retVal;
}


/**
*	Evaluate the road marks records and return the road mark object corresponding to the provided s-offset
*/
LaneRoadMark Lane::GetRoadMarkValue(double s_check)
{
	LaneRoadMark returnRoadMark;
	//find the record where s_check belongs
	int index=CheckRoadMarkInterval(s_check);
	//If found, return the params 
	if (index>=0)
	{
		returnRoadMark.SetColor(mLaneRoadMark.at(index).GetColor());
		returnRoadMark.SetLaneChange(mLaneRoadMark.at(index).GetLaneChange());
		returnRoadMark.SetType(mLaneRoadMark.at(index).GetType());
		returnRoadMark.SetWeight(mLaneRoadMark.at(index).GetWeight());
		returnRoadMark.SetWidth(mLaneRoadMark.at(index).GetWidth());
	}

	return returnRoadMark;

}

/**
* Destructor
* Delete all the members of the vectors:
* mLaneWidth, mRoadMark, mLaneMaterial, mLaneVisibility, mLaneSpeed, mLaneAccess, mLaneHeight
*/
Lane::~Lane()
{
	// DELETING LANE WIDTHS
	mLaneWidth.clear();

	// DELETING LANE ROAD MARKS
	mLaneRoadMark.clear();

	// DELETING LANE MATERIAL
	mLaneMaterial.clear();

	// DELETING LANE VISIBILITY
	mLaneVisibility.clear();

	// DELETING LANE SPEED
	mLaneSpeed.clear();

	// DELETING LANE ACCESS
	mLaneAccess.clear();

	// DELETING LANE HEIGHTS
	mLaneHeight.clear();
}

/**
* Lane width class. Holds all the data that describes a lane width
*
*
*
*
*
*/

/**
* Constructor
* @param s s-offset of the record starting from the lane section s-offset
* @ param a,b,c,d The 4 parameters of the polynomial
*/
LaneWidth::LaneWidth(double s, double a, double b, double c, double d):ThirdOrderPolynom (s,a,b,c,d)
{}

/**
* Road mark class. Holds all the data that describes a road mark
*
*
*
*
*
*/

/*
* Constructors
*/
LaneRoadMark::LaneRoadMark()
{	mSOffset=0, mType="none"; mWeight="standard"; mColor="standard"; mWidth=0.75; mLaneChange="both"; 	}
//-------------
LaneRoadMark::LaneRoadMark(double sOffset, string type, string weight, string color, double width, string laneChange)
{	mSOffset=sOffset; mType=type; mWeight=weight; mColor=color; mWidth=width; mLaneChange=laneChange;	
}
//-------------
LaneRoadMark::LaneRoadMark(double sOffset, string type, string weight, string color, double width)
{	mSOffset=sOffset; mType=type; mWeight=weight; mColor=color; mWidth=width; mLaneChange="both"; }

/*
* Methods that set the parameters of the road mark
*/
void LaneRoadMark::SetS(double value)
{	mSOffset = value;	}
void LaneRoadMark::SetType(string type)
{	mType=type;	}
void LaneRoadMark::SetWeight(string weight)
{	mWeight=weight;	}
void LaneRoadMark::SetColor(string color)
{	mColor=color;	}
void LaneRoadMark::SetWidth(double value)
{	mWidth=value;	}
void LaneRoadMark::SetLaneChange(string laneChange)
{	mLaneChange=laneChange;	}


/*
* Methods that return the parameters of the road mark
*/
double LaneRoadMark::GetS()
{	return mSOffset;	}
string LaneRoadMark::GetType()
{	return mType;	}
string LaneRoadMark::GetWeight()
{	return mWeight;	}
string LaneRoadMark::GetColor()
{	return mColor;	}
double LaneRoadMark::GetWidth()
{	return mWidth;	}
string LaneRoadMark::GetLaneChange()
{	return mLaneChange;	}

/**
* Lane material class. Contains all the data that describes a lane material
*
*
*
*
*
*/

/*
* Constructor
*/
LaneMaterial::LaneMaterial (double sOffset, string surface, double friction, double roughness)
{	mSOffset=sOffset; mSurface=surface; mFriction=friction; mRoughness=roughness;	}

/*
* Methods that return the parameters of the lane material
*/
double LaneMaterial::GetS()
{	return mSOffset;	}
string LaneMaterial::GetSurface()
{	return mSurface;	}
double LaneMaterial::GetFriction()
{	return mFriction;	}
double LaneMaterial::GetRoughness()
{	return mRoughness;	}

/*
* Methods that set the parameters of the lane material
*/
void LaneMaterial::SetS(double value)
{	mSOffset=value;	}
void LaneMaterial::SetSurface(string surface)
{	mSurface=surface;	}
void LaneMaterial::SetFriction(double value)
{	mFriction=value;	}
void LaneMaterial::SetRoughness(double value)
{	mRoughness=value;	}


/**
* Lane visibility class. Contains all the data that describes lane visibility record
*
*
*
*
*
*/

/*
* Constructor
*/
LaneVisibility::LaneVisibility(double sOffset, double forward, double back, double left, double right)
{	mSOffset=sOffset; mForward=forward; mBack=back; mLeft=left; mRight=right;	}

/*
* Methods that return the parameters of the lane visibility
*/
double LaneVisibility::GetS()
{	return mSOffset;	}
double LaneVisibility::GetForward()
{	return mForward;	}
double LaneVisibility::GetBack()
{	return mBack;	}
double LaneVisibility::GetLeft()
{	return mLeft;	}
double LaneVisibility::GetRight()
{	return mRight;	}

/*
* Methods that set the parameters of the lane visibility
*/
void LaneVisibility::SetS(double value)
{	mSOffset=value;	}
void LaneVisibility::SetForward(double value)
{	mForward=value;	}
void LaneVisibility::SetBack(double value)
{	mBack=value;	}
void LaneVisibility::SetLeft(double value)
{	mLeft=value;	}
void LaneVisibility::SetRight(double value)
{	mRight=value;	}


/**
* Lane speed class. Contains all the data that describes lane speed record
*
*
*
*
*
*/

/*
* Constructor
*/
LaneSpeed::LaneSpeed (double sOffset, double max)
{	mSOffset=sOffset; mMax=max;}

/*
* Methods that return the parameters of the lane speed
*/
double LaneSpeed::GetS()
{	return mSOffset;	}
double LaneSpeed::GetMax()
{	return mMax;	}

/*
* Methods that set the parameters of the lane speed
*/
void LaneSpeed::SetS(double value)
{	mSOffset=value;	}
void LaneSpeed::SetMax(double value)
{	mMax=value;	}


/**
* Lane access class. Contains all the data that describes lane access record
*
*
*
*
*
*/
/*
* Constructor
*/
LaneAccess::LaneAccess (double sOffset, string restriction)
{	mSOffset=sOffset; mRestriction = restriction;	}

/*
* Methods that return the parameters of the lane access
*/
double LaneAccess::GetS()
{	return mSOffset;	}
string LaneAccess::GetRestriction()
{	return mRestriction;	}

/*
* Methods that set the parameters of the lane access
*/
void LaneAccess::SetS(double value)
{	mSOffset=value;	}
void LaneAccess::SetRestriction(string restriction)
{	mRestriction=restriction;	}

/**
* Lane height class. Contains all the data that describes lane access record
*
*
*
*
*
*/
/*
* Constructors
*/
LaneHeight::LaneHeight()
{mSOffset=0; mInner=0; mOuter=0;}
LaneHeight::LaneHeight (double sOffset, double inner, double outer)
{	mSOffset=sOffset; mInner=inner; mOuter=outer;	}

/*
* Methods that return the parameters of the lane height
*/
double LaneHeight::GetS()
{	return mSOffset;	}
double LaneHeight::GetInner()
{	return mInner;	}
double LaneHeight::GetOuter()
{	return mOuter;	}

/*
* Methods that set the parameters of the lane height
*/
void LaneHeight::SetS(double value)
{	mSOffset=value;	}
void LaneHeight::SetInner(double value)
{	mInner=value;	}
void LaneHeight::SetOuter(double value)
{	mOuter=value;	}