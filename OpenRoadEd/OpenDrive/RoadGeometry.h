#ifndef ROADGEOMETRY_H
#define ROADGEOMETRY_H

#include <vector>
#include <string>

//Prototypes
class RoadGeometry;
class GeometryLine;
class GeometrySpiral;
class GeometryArc;

using std::vector;
using std::string;


/**
 * RoadGeometry class is responsible for storing the basic chordline geometry properties
 *
 */
class RoadGeometry
{
protected:
	/**
	 * Base record properties
	 */
	double mS;
	double mX;
	double mY;
	double mHdg;
	double mLength;
	double mS2;
	short int mGeomType;	//0-line, 1-arc, 2-spiral
public:
	/**
	 * Constructor that initializes the base properties of teh record
	 */
	RoadGeometry(double s, double x, double y, double hdg, double length);
	
	/**
	 * Clones and returns the new geometry record
	 */
	virtual RoadGeometry* Clone() const;
	
	//-------------------------------------------------

	/**
	 * Sets the type of the geometry
	 * 0: Line, 1: Arc, 2: Spiral
	 */
	void SetGeomType(short int geomType);
	
	/**
	 * Setter for the base properties
	 */
	void SetBase(double s, double x, double y, double hdg, double length, bool recalculate=true);
	void SetS(double s);
	void SetX(double x);
	void SetY(double y);
	void SetHdg(double hdg);
	void SetLength(double length);

	//-------------------------------------------------
	/**
	 * Getter for the geometry type
	 */
	short int GetGeomType();
	
	/**
	 * Getter for the base properties
	 */
	double GetS();
	double GetS2();
	double GetX();
	double GetY();
	double GetHdg();
	double GetLength();

	//-------------------------------------------------

	/**
	 * Evaluation methods
	 */
	virtual bool CheckInterval (double s_check);
	virtual void GetCoords(double s_check, double &retX, double &retY);
	virtual void GetCoords(double s_check, double &retX, double &retY, double &retHDG);
protected:

	/**
	 * Computes the required vars
	 */
	virtual void ComputeVars();
};


//----------------------------------------------------------------------------------
/**
 * GeometryLine inherits the RoadGeometry class but adds no additional properties
 *
 */
class GeometryLine:public RoadGeometry
{
public:
	/**
	 * Constructor that initializes the base properties of the record
	 */
	GeometryLine (double s, double x, double y, double hdg, double length);

	/**
	 * Clones and returns the new geometry record
	 */
	RoadGeometry* Clone() const;
	
	//-------------------------------------------------

	/**
	 * Setter for the base properties
	 */
	void SetAll(double s, double x, double y, double hdg, double length);

	//-------------------------------------------------

	/**
	 * Gets the coordinates at the sample S offset
	 */
	void GetCoords(double s_check, double &retX, double &retY, double &retHDG);

};
//----------------------------------------------------------------------------------
/**
 * GeometryArc inherits the RoadGeometry class and adds Curvature property
 *
 */
class GeometryArc: public RoadGeometry
{
private:
	/**
	 * Base record properties
	 */
	double mCurvature;
	
	/**
	 * Optimization related variables
	 */ 
	double mCircleX;
	double mCircleY;

	/**
	 * Computation variables
	 */
	double mStartAngle;

public:
	/**
	 * Constructor that initializes the base properties of the record
	 */
	GeometryArc (double s, double x, double y, double hdg, double length, double curvature);

	/**
	 * Clones and returns the new geometry record
	 */
	RoadGeometry* Clone() const;

	//-------------------------------------------------
	
	/**
	 * Setter for the base properties
	 */
	void SetAll(double s, double x, double y, double hdg, double length, double curvature);
	void SetCurvature(double curvature);

	//-------------------------------------------------

	/**
	 * Getter for the base properties
	 */
	double GetCurvature();
	
	//-------------------------------------------------

	/**
	 * Gets the coordinates at the sample S offset
	 */
	void GetCoords(double s_check, double &retX, double &retY, double &retHDG);
protected:

	/**
	 * Computes the required vars
	 */
	virtual void ComputeVars();
};



//----------------------------------------------------------------------------------
/**
 * GeometrySpiral inherits the RoadGeometry class and adds Curvature properties
 *
 */
class GeometrySpiral: public RoadGeometry
{
private:
	/**
	 * Base record properties
	 */
	double mCurvatureStart;
	double mCurvatureEnd;

	/**
	 * Computation variables
	 */
	static const double sqrtPiO2;
	double mA;
	double mCurvature;
	double mDenormalizeFactor;
	double mEndX;
	double mEndY;
	bool mNormalDir;

	double differenceAngle;
	double mRotCos;
	double mRotSin;

public:
	/**
	 * Constructor that initializes the base properties of the record
	 */
	GeometrySpiral (double s, double x, double y, double hdg, double length, double curvatureStart,double curvatureEnd);

	/**
	 * Clones and returns the new geometry record
	 */
	RoadGeometry* Clone() const;

	//-------------------------------------------------

	/**
	 * Setter for the base properties
	 */
	void SetAll(double s, double x, double y, double hdg, double length, double curvatureStart,double curvatureEnd);
	void SetCurvatureStart(double curvature);
	void SetCurvatureEnd(double curvature);
	
	//-------------------------------------------------
	/**
	 * Getter for the base properties
	 */
	double GetCurvatureStart();
	double GetCurvatureEnd();
	
	//-------------------------------------------------
	/**
	 * Gets the coordinates at the sample S offset
	 */
	void GetCoords(double s_check, double &retX, double &retY, double &retHDG);
protected:

	/**
	 * Computes the required vars
	 */
	virtual void ComputeVars();
};


//----------------------------------------------------------------------------------
/**
 * GeometryPoly3 inherits the RoadGeometry class and adds polynomial properties
 *
 */
class GeometryPoly3: public RoadGeometry
{
private:
	/**
	 * Base record properties
	 */
	double mA;
	double mB;
	double mC;
	double mD;
public:
	/**
	 * Constructor that initializes the base properties of the record
	 */
	GeometryPoly3 (double s, double x, double y, double hdg, double length, double a,double b,double c,double d );

	/**
	 * Clones and returns the new geometry record
	 */
	RoadGeometry* Clone() const;
	
	//-------------------------------------------------
	/**
	 * Setter for the base properties
	 */
	void SetAll(double s, double x, double y, double hdg, double length, double a,double b,double c,double d);

};



//----------------------------------------------------------------------------------
/**
 * GeometryBlock is a class used to combine multiple geometry records into blocks.
 * The basic use for this is to combine spiral-arc-spiral sequence of records into 
 * a signel "Turn" block for an easier way to define turns, keeping close to the
 * road building practice of curvature use for transitions between straight segments and arcs
 */
class GeometryBlock
{
private:
	/**
	 * Vector of geometry records that make up a block
	 */
	vector<RoadGeometry*> mGeometryBlockElement;
public:
	/**
	 * Constructor
	 */
	GeometryBlock();
	
	/**
	 * Copy constructor
	 */
	GeometryBlock(const GeometryBlock& geomBlock);

	/**
	 * Assignment operator overload
	 */
	const GeometryBlock& operator=(const GeometryBlock& otherGeomBlock);
	
	//-------------------------------------------------

	/**
	 * Methods used to add geometry recors to the geometry record vector
	 */
	void AddGeometryLine(double s, double x, double y, double hdg, double length);
	void AddGeometryArc(double s, double x, double y, double hdg, double length, double curvature);
	void AddGeometrySpiral(double s, double x, double y, double hdg, double length, double curvatureStart,double curvatureEnd);
	void AddGeometryPoly3(double s, double x, double y, double hdg, double length, double a,double b,double c,double d);
	
	//-------------------------------------------------

	/**
	 * Getter for the geometry record at a given index position of the vector
	 */
	RoadGeometry* GetGeometryAt(int index);

	/**
	 * Getter for the overal block length (summ of geometry record lengths)
	 */
	double GetBlockLength();

	/**
	 *  Checks if the block is a straight line block or a turn
	 */
	bool CheckIfLine();
	
	//-------------------------------------------------

	/**
	 * Recalculates the geometry blocks when one of the geometry records is modified
	 * Makes sure that every geometry records starts where the previous record ends
	 */
	void Recalculate(double s, double x, double y, double hdg);

	//-------------------------------------------------

	/**
	 *  Evaluation methods
	 */
	double GetLastS2();
	RoadGeometry* GetLastGeometry();
	virtual short int GetLastCoords(double &s, double &retX, double &retY, double &retHDG);
	bool CheckInterval(double s_check);
	virtual short int GetCoords(double s_check, double &retX, double &retY);
	virtual short int GetCoords(double s_check, double &retX, double &retY, double &retHDG);

	//-------------------------------------------------
	/**
	 *  Destructor
	 */
	~GeometryBlock();
};


#endif
