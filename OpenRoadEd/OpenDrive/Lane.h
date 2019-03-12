#ifndef LANE_H
#define LANE_H

#include "Road.h"
#include "OtherStructures.h"
#include <Vector>
#include <String>


//Prototypes
class LaneSection;
class LaneSectionSample;
class Lane;
class LaneWidth;
class LaneRoadMark;
class LaneMaterial;
class LaneVisibility;
class LaneSpeed;
class LaneAccess;
class LaneHeight;

using std::vector;
using std::string;

/**
* Lane section class. Holds all the lane section information
*
*
*
*
*/
class LaneSection
{
private:
	/**
	* Record parameters
	*/
	double mS;
	vector<Lane> mLaneVector;

	unsigned int mLastAddedLane;

public:
	/**
	* Constructor. Sets basic lane section parameters
	* @param s s-offset of the lane section
	*/
	LaneSection (double s);

	/**
	* Add a lane to the lane section
	* @param side the side of the road to which the lane will be added
	* @param id ID of the lane
	* @param type Type of the lane (Section 6.5 of the OpenDRIVE specification) 
	* @param level Level parameter of the road
	* @param sort Defines if the lanes should be sorted when added. True by default
	*/
	unsigned int AddLane(short int side, int id, string type, bool level, bool sort=true);


	/**
	* Delete the lane at the provided index
	*/
	void DeleteLane(unsigned int index);

	/**
	* Delete the outside left or right lane 
	*/
	void DeleteLeftLane();
	void DeleteRigthLane();

	/**
	* Get the last lane
	* @return A pointer to Lane object
	*/
	Lane* GetLastLane();

	/**
	* Get the last added lane (which might not be the one from the end of the vector)
	* @return A pointer to Lane object
	*/
	Lane* GetLastAddedLane();

	/**
	* Get the last left lane
	* @return A pointer to Lane object
	*/
	Lane* GetLastLeftLane();

	/**
	* Get the last right lane
	* @return A pointer to Lane object
	*/
	Lane* GetLastRightLane();

	/**
	* Get the last center lane
	* @return A pointer to Lane object
	*/
	Lane* GetLastCenterLane();

	/**
	* Get the lane by providing its index
	* @param i Index of the lane to be returned
	* @return A pointer to Lane object
	*/
	Lane* GetLane(unsigned int i);

	/**
	* Get the lane number
	* @return Unsigned int with that stores the number of lanes
	*/
	unsigned int GetLaneCount();

	/**
	* Get the lane vector
	* @return A pointer to a vector of type Lane
	*/
	vector<Lane>* GetLaneVector();

	/**
	* Get the lane section s-offset
	*/
	double GetS();

	/**
	* Get the lane section final s-offset which is the s-offset of the last record of the lane section
	*/
	double GetS2();

	/**
	* Set the lane section s-offset
	*/
	void SetS(double value);


	/**
	* Check if the tested s-offset is inside the lane section interval
	* @param A double s-offset value that has to be checked
	* @return Return true if the s-offset value belongs to current lane section, false otherwise
	*/
	bool CheckInterval(double s_check);

	/**
	* Return the lane-0 index in the lanes vector
	* @return An unsigned int value with the index
	*/
	unsigned int GetZeroLaneIndex();

	/**
	* Return the number of left lanes
	* @return An unsigned int value with the number of left lanes
	*/
	unsigned int GetLeftLaneCount();

	/**
	* Return the number of central lanes
	* @return An unsigned int value with the number of central lanes
	*/
	unsigned int GetCenterLaneCount();

	/**
	* Return the number of right lanes
	* @return An unsigned int value with the number of right lanes
	*/
	unsigned int GetRightLaneCount();

	/**
	* Fill a special structure with all the lane / lane section data that is sampled at a provided s-offset position along the road
	* @param s_chek s-offset along the road at which to sample the lane section
	* @param laneSectionSample The structure that has to be filled with the sampled data
	* @return Returns true if the operation was successful. 
	*/
	bool FillLaneSectionSample(double s_check, LaneSectionSample& laneSectionSample);

	/**
	* Destructor. Delete all the members of the vectors: mLeft, mCenter, mRight
	*/
	~LaneSection();
};


/**
* Lane Section Sample. Holds all the lane information at a certain S value including lane widths, levels, 
* heights, etc
*
*
*
*
*/ 
class LaneSectionSample
{
private:
	/*
	*	All the vectors for the data that is sampled. For ease of use the structure is divided into left and right lane groups.
	*
	*/
	vector<string> mLeftTypeVector;
	vector<double> mLeftWidthVector;
	vector<LaneHeight> mLeftHeightVector;
	vector<LaneRoadMark> mLeftRoadMarkVector;
	vector<bool> mLeftLevelVector;

	vector<string> mRightTypeVector;
	vector<double> mRightWidthVector;
	vector<LaneHeight> mRightHeightVector;
	vector<LaneRoadMark> mRightRoadMarkVector;
	vector<bool> mRightLevelVector;
public:
	LaneSectionSample();

	/*
	* Add various elements to the structure. Depending on the the value to be added, various input parameters are used.
	* The methods are divided into left and right for left and right sides of the road.
	*/
	void AddLeftType(string type);
	void AddLeftWidth(double width);
	void AddLeftHeight(LaneHeight height);
	void AddLeftRoadMark(LaneRoadMark roadMark);
	void AddLeftLevel(bool level);

	void AddRightType(string type);
	void AddRightWidth(double width);
	void AddRightHeight(LaneHeight height);
	void AddRightRoadMark(LaneRoadMark roadMark);
	void AddRightLevel(bool level);

	void AddLeftRecord(string type, double width, LaneHeight height, LaneRoadMark roadMark, bool level);
	void AddRightRecord(string type, double width, LaneHeight height, LaneRoadMark roadMark, bool level);

	/*
	* Get various elements of the structure. The methods return type depends on the elements that are returned.
	* The methods are divided into left and right for left and right sides of the road.
	*/
	string GetLeftType(unsigned int i);
	double GetLeftWidth(unsigned int i);
	LaneHeight GetLeftHeight(unsigned int i);
	LaneRoadMark GetLeftRoadMark(unsigned int i);
	bool GetLeftLevel(unsigned int i);

	string GetRightType(unsigned int i);
	double GetRightWidth(unsigned int i);
	LaneHeight GetRightHeight(unsigned int i);
	LaneRoadMark GetRightRoadMark(unsigned int i);
	bool GetRightLevel(unsigned int i);

	/*
	* Get the number of elements in the vectors
	*/
	unsigned int GetLeftVectorsSize();
	unsigned int GetRightVectorsSize();

	/*
	* Get the various record vectors. The vector type depends on the record
	* The methods are divided into left and right for left and right sides of the road.
	*/
	vector<string>* GetLeftTypeVector();
	vector<double>* GetLeftWidthVector();
	vector<LaneHeight>* GetLeftHeigthVector();
	vector<LaneRoadMark>* GetLeftRoadMarkVector();
	vector<bool>* GetLeftLevelVector();

	vector<string>* GetRightTypeVector();
	vector<double>* GetRightWidthVector();
	vector<LaneHeight>* GetRightHeigthVector();
	vector<LaneRoadMark>* GetRightRoadMarkVector();
	vector<bool>* GetRightLevelVector();


	/*
	* Clear the vectors
	*/
	void ClearVectors();

};



/**
* Lane class. Holds all the record data that describes a lane
*
*
*
*
*
*/
class Lane
{
private:
	/**
	*	Record parameters
	*/
	short int mSide; //0 = center, -1 = right, 1=left
	int mId;
	string mType; 
	bool mLevel; //true or false(default)

	//links
	bool mPredecessorExists;
	int mPredecessor;
	bool mSuccessorExists;
	int mSuccessor;

	//Width
	vector <LaneWidth> mLaneWidth;
	//Road Mark
	vector <LaneRoadMark> mLaneRoadMark;
	//Lane Material
	vector <LaneMaterial> mLaneMaterial;
	//Lane Visibility
	vector <LaneVisibility> mLaneVisibility;
	//Lane Speed
	vector <LaneSpeed> mLaneSpeed;
	//Lane Access
	vector<LaneAccess> mLaneAccess;
	//Lane Height
	vector<LaneHeight> mLaneHeight;


	unsigned int mLastAddedLaneWidth;
	unsigned int mLastAddedLaneRoadMark;
	unsigned int mLastAddedLaneMaterial;
	unsigned int mLastAddedLaneVisibility;
	unsigned int mLastAddedLaneSpeed;
	unsigned int mLastAddedLaneAccess;
	unsigned int mLastAddedLaneHeight;

public:
	/**
	*	Constructor
	*/
	Lane(short int side, int id, string type, bool level);
	/**
	*	Operator less, Used to sort the lanes
	*/
	bool operator<(Lane rhs)const { return (mId < rhs.mId); }


	/**
	*	Various set methods.
	*/
	void SetSide(short int side);
	void SetId(int id);
	void SetType(string type);
	void SetLevel(bool level);
	void SetPredecessor(int predecessor);
	void SetSuccessor(int successor);

	/**
	*	Remove lane linkage methods.
	*/
	void RemovePredecessor();
	void RemoveSuccessor();

	/**
	 * Methods used to add child records to the respective vectors
	 */
	unsigned int AddWidthRecord(double s, double a, double b, double c, double d);
	unsigned int AddRoadMarkRecord(double sOffset, string type, string weight, string color, double width, string laneChange);
	unsigned int AddMaterialRecord(double sOffset, string surface, double friction, double roughness);
	unsigned int AddVisibilityRecord(double sOffset, double forward, double back, double left, double right);
	unsigned int AddSpeedRecord(double sOffset, double max);
	unsigned int AddAccessRecord(double sOffset, string restriction);
	unsigned int AddHeightRecord(double sOffset, double inner, double outer);

	/**
	 * Methods used to clone child records in the respective vectors
	 */
	unsigned int CloneLaneWidth(unsigned int index);
	unsigned int CloneLaneRoadMark(unsigned int index);
	unsigned int CloneLaneMaterial(unsigned int index);
	unsigned int CloneLaneVisibility(unsigned int index);
	unsigned int CloneLaneSpeed(unsigned int index);
	unsigned int CloneLaneAccess(unsigned int index);
	unsigned int CloneLaneHeight(unsigned int index);

	/**
	 * Methods used to delete child records from the respective vectors
	 */
	void DeleteLaneWidth(unsigned int index);
	void DeleteLaneRoadMark(unsigned int index);
	void DeleteLaneMaterial(unsigned int index);
	void DeleteLaneVisibility(unsigned int index);
	void DeleteLaneSpeed(unsigned int index);
	void DeleteLaneAccess(unsigned int index);
	void DeleteLaneHeight(unsigned int index);


	/**
	*	Getters of the lane parameters
	*/
	int GetSide();
	int GetId();
	string GetType();
	bool GetLevel();

	/**
	*	Check if linkage information is provided
	*/
	bool IsPredecessorSet();
	int GetPredecessor();
	bool IsSuccessorSet();
	int GetSuccessor();

	/**
	*	Get pointers to the records vectors
	*/
	vector <LaneWidth> *GetLaneWidthVector();
	vector <LaneRoadMark> *GetLaneRoadMarkVector();
	vector <LaneMaterial> *GetLaneMaterialVector();
	vector <LaneVisibility> *GetLaneVisibilityVector();
	vector <LaneSpeed> *GetLaneSpeedVector();
	vector <LaneAccess> *GetLaneAccessVector();
	vector <LaneHeight> *GetLaneHeightVector();


	/**
	*	Get the number of elements in a certain vector
	*/
	unsigned int GetLaneWidthCount();
	unsigned int GetLaneRoadMarkCount();
	unsigned int GetLaneMaterialCount();
	unsigned int GetLaneVisibilityCount();
	unsigned int GetLaneSpeedCount();
	unsigned int GetLaneAccessCount();
	unsigned int GetLaneHeightCount();


	/**
	*	Get the elements of a certain vectors at position i
	*/
	LaneWidth* GetLaneWidth(unsigned int i); 
	LaneRoadMark* GetLaneRoadMark(unsigned int i);
	LaneMaterial* GetLaneMaterial(unsigned int i);
	LaneVisibility* GetLaneVisibility(unsigned int i);
	LaneSpeed* GetLaneSpeed(unsigned int i);
	LaneAccess* GetLaneAccess(unsigned int i);
	LaneHeight* GetLaneHeight(unsigned int i);


	/**
	*	Get the last elements of a certain vectors
	*/
	LaneWidth* GetLastLaneWidth(); 
	LaneRoadMark* GetLastLaneRoadMark();
	LaneMaterial* GetLastLaneMaterial();
	LaneVisibility* GetLastLaneVisibility();
	LaneSpeed* GetLastLaneSpeed();
	LaneAccess* GetLastLaneAccess();
	LaneHeight* GetLastLaneHeight();

	/**
	*	Get the last added elements of a certain vectors (their position might not be at the end of the vector)
	*/
	LaneWidth* GetLastAddedLaneWidth(); 
	LaneRoadMark* GetLastAddedLaneRoadMark();
	LaneMaterial* GetLastAddedLaneMaterial();
	LaneVisibility* GetLastAddedLaneVisibility();
	LaneSpeed* GetLastAddedLaneSpeed();
	LaneAccess* GetLastAddedLaneAccess();
	LaneHeight* GetLastAddedLaneHeight();

	/**
	*	Check the intervals and return the index of the records that applies to the provided s-offset
	*/
	int CheckWidthInterval(double s_check);
	int CheckRoadMarkInterval(double s_check);
	int CheckMaterialInterval(double s_check);
	int CheckVisibilityInterval(double s_check);
	int CheckSpeedInterval(double s_check);
	int CheckAccessInterval(double s_check);
	int CheckHeightInterval(double s_check);


	/**
	*	Evaluate the record and return the width value
	*/
	double GetWidthValue(double s_check);

	/**
	*	Evaluate the record and return the height object
	*/
	LaneHeight GetHeightValue(double s_check);

	/**
	*	Evaluate the road marks records and return the road mark object corresponding to the provided s-offset
	*/
	LaneRoadMark GetRoadMarkValue(double s_check);


	/**
	* Destructor
	* Delete all the members of the vectors:
	* mLaneWidth, mRoadMark, mLaneMaterial, mLaneVisibility, mLaneSpeed, mLaneAccess, mLaneHeight
	*/
	~Lane();
	//--------------

};

/**
* Lane width class. Holds all the data that describes a lane width
*
*
*
*
*
*/
class LaneWidth : public ThirdOrderPolynom
{
public:

	/**
	* Constructor
	* @param s s-offset of the record starting from the lane section s-offset
	* @ param a,b,c,d The 4 parameters of the polynomial
	*/
	LaneWidth(double s, double a, double b, double c, double d);

};

/**
* Road mark class. Holds all the data that describes a road mark
*
*
*
*
*
*/
class LaneRoadMark
{
private:

	/*
	* Parameters of the road mark
	*/
	double mSOffset;
	string mType;
	string mWeight;
	string mColor; 
	double mWidth;
	string mLaneChange;
public:
	/*
	* Constructors
	*/
	LaneRoadMark();
	LaneRoadMark(double sOffset, string type, string weight, string color, double width, string laneChange);
	LaneRoadMark(double sOffset, string type, string weight, string color, double width);

	/*
	* Methods that set the parameters of the road mark
	*/
	void SetS(double value);
	void SetType(string type);
	void SetWeight(string weight);
	void SetColor(string color);
	void SetWidth(double value);
	void SetLaneChange(string laneChange);

	/*
	* Methods that return the parameters of the road mark
	*/
	double GetS();
	string GetType();
	string GetWeight();
	string GetColor();
	double GetWidth();
	string GetLaneChange();

};

/**
* Lane material class. Contains all the data that describes a lane material
*
*
*
*
*
*/
class LaneMaterial
{
private:
	/*
	* Parameters that describe the lane material
	*/
	double mSOffset;
	string mSurface;
	double mFriction;
	double mRoughness;
public:

	/*
	* Constructor
	*/
	LaneMaterial (double sOffset, string surface, double friction, double roughness);

	/*
	* Methods that return the parameters of the lane material
	*/
	double GetS();
	string GetSurface();
	double GetFriction();
	double GetRoughness();

	/*
	* Methods that set the parameters of the lane material
	*/
	void SetS(double value);
	void SetSurface(string surface);
	void SetFriction(double value);
	void SetRoughness(double value);

};

/**
* Lane visibility class. Contains all the data that describes lane visibility record
*
*
*
*
*
*/
class LaneVisibility
{
private:
	/*
	* Parameters that describe the lane visibility
	*/
	double mSOffset;
	double mForward;
	double mBack;
	double mLeft;
	double mRight;
public:
	/*
	* Constructor
	*/
	LaneVisibility(double sOffset, double forward, double back, double left, double right);

	/*
	* Methods that return the parameters of the lane visibility
	*/
	double GetS();
	double GetForward();
	double GetBack();
	double GetLeft();
	double GetRight();

	/*
	* Methods that set the parameters of the lane visibility
	*/
	void SetS(double value);
	void SetForward(double value);
	void SetBack(double value);
	void SetLeft(double value);
	void SetRight(double value);

};

/**
* Lane speed class. Contains all the data that describes lane speed record
*
*
*
*
*
*/
class LaneSpeed
{
private:
	/*
	* Parameters that describe the lane speed
	*/
	double mSOffset;
	double mMax;
public:
	/*
	* Constructor
	*/
	LaneSpeed (double sOffset, double max);

	/*
	* Methods that return the parameters of the lane speed
	*/
	double GetS();
	double GetMax();

	/*
	* Methods that set the parameters of the lane speed
	*/
	void SetS(double value);
	void SetMax(double value);
};

/**
* Lane access class. Contains all the data that describes lane access record
*
*
*
*
*
*/
class LaneAccess
{
private:
	/*
	* Parameters that describe the lane access
	*/
	double mSOffset;
	string mRestriction;
public:
	/*
	* Constructor
	*/
	LaneAccess (double sOffset, string restriction);

	/*
	* Methods that return the parameters of the lane access
	*/
	double GetS();
	string GetRestriction();

	/*
	* Methods that set the parameters of the lane access
	*/
	void SetS(double value);
	void SetRestriction(string restriction);
};

/**
* Lane height class. Contains all the data that describes lane access record
*
*
*
*
*
*/
class LaneHeight
{
private:
	/*
	* Parameters that describe the lane height
	*/
	double mSOffset;
	double mInner;
	double mOuter;
public:
	/*
	* Constructors
	*/
	LaneHeight();
	LaneHeight (double sOffset, double inner, double outer);

	/*
	* Methods that return the parameters of the lane height
	*/
	double GetS();
	double GetInner();
	double GetOuter();

	/*
	* Methods that set the parameters of the lane height
	*/
	void SetS(double value);
	void SetInner(double value);
	void SetOuter(double value);
};

//----------------------------------------------------------------------------------


#endif