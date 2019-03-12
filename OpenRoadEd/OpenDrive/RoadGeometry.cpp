#include "RoadGeometry.h"
#define _USE_MATH_DEFINES
#include <math.h>

//#define PI 3.14159265358979323846264338327950288
extern int fresnl( double , double *, double * );


//***********************************************************************************
//Road Geometry Base Class
//***********************************************************************************
/**
 * Constructor that initializes the base properties of teh record
 */
RoadGeometry::RoadGeometry(double s, double x, double y, double hdg, double length)
{
	mS=s;	mX=x; mY=y, mHdg=hdg, mLength=length;
	mS2=s+length;
}

/**
 * Computes the required vars
 */
void RoadGeometry::ComputeVars()
{}

/**
 * Clones and returns the new geometry record
 */
RoadGeometry* RoadGeometry::Clone() const
{
	return new RoadGeometry(mS,mX,mY, mHdg, mLength);
}
//-------------------------------------------------

/**
 * Sets the type of the geometry
 * 0: Line, 1: Arc, 2: Spiral
 */
void RoadGeometry::SetGeomType(short int geomType)
{	
	mGeomType = geomType;	
}


/**
 * Setter for the base properties
 */
void RoadGeometry::SetBase(double s, double x, double y, double hdg, double length, bool recalculate)
{
	mS=s;
	mX=x;
	mY=y;
	mHdg=hdg;
	mLength=length;
	mS2=mS+mLength;
	if(recalculate) ComputeVars();
}
void RoadGeometry::SetS(double s)
{
	mS=s;
	mS2=mS+mLength;
	ComputeVars();
}
void RoadGeometry::SetX(double x)
{
	mX=x;
}
void RoadGeometry::SetY(double y)
{
	mY=y;
}
void RoadGeometry::SetHdg(double hdg)
{
	mHdg=hdg;
	ComputeVars();
}
void RoadGeometry::SetLength(double length)
{
	mLength=length;
	mS2=mS+mLength;
	ComputeVars();
}
//-------------------------------------------------

/**
 * Getter for the geometry type
 */
short int RoadGeometry::GetGeomType()
{	
	return mGeomType;
}

/**
 * Getter for the base properties
 */
double RoadGeometry::GetS()
{
	return mS;
}
double RoadGeometry::GetS2()
{
	return mS2;
}
double RoadGeometry::GetX()
{
	return mX;
}
double RoadGeometry::GetY()
{
	return mY;
}
double RoadGeometry::GetHdg()
{
	return mHdg;
}
double RoadGeometry::GetLength()
{
	return mLength;
}

//-------------------------------------------------

/**
 * Checks if the sample S gets in the current block interval
 */
bool RoadGeometry::CheckInterval (double s_check)
{
	if ((s_check >= mS) && (s_check<=mS2))
		return true;
	else
		return false;
}

/**
 * Gets the coordinates at the sample S offset
 */
void  RoadGeometry::GetCoords(double s_check, double &retX, double &retY)
{
	double tmp;
	GetCoords(s_check, retX, retY, tmp);
}
void RoadGeometry::GetCoords(double s_check, double &retX, double &retY, double &retHDG)
{}



//***********************************************************************************
//Line geometry 
//***********************************************************************************
/**
 * Constructor that initializes the base properties of the record
 */
GeometryLine::GeometryLine (double s, double x, double y, double hdg, double length):	RoadGeometry(s, x, y, hdg, length)
{	
	SetGeomType(0);	
}

/**
 * Clones and returns the new geometry record
 */
RoadGeometry* GeometryLine::Clone() const
{
	GeometryLine* ret=new GeometryLine(mS,mX,mY, mHdg, mLength);
	return ret;
}

//-------------------------------------------------

/**
 * Setter for the base properties
 */
void GeometryLine::SetAll(double s, double x, double y, double hdg, double length)
{
	SetBase(s,x,y,hdg,length,false);
	ComputeVars();
}

//-------------------------------------------------

/**
 * Gets the coordinates at the sample S offset
 */
void GeometryLine::GetCoords(double s_check, double &retX, double &retY, double &retHDG)
{
	double newLength=s_check-mS;
	//find the end of the chord line
	retX=mX+cos(mHdg)*newLength;
	retY=mY+sin(mHdg)*newLength;

	retHDG=mHdg;
}





//***********************************************************************************
//Arc geometry
//***********************************************************************************
/**
 * Constructor that initializes the base properties of the record
 */
GeometryArc::GeometryArc (double s, double x, double y, double hdg, double length, double curvature):	RoadGeometry(s, x, y, hdg, length)
{
	SetGeomType(1);
	mCurvature=curvature;

	ComputeVars();
}

/**
 * Computes the required vars
 */
void GeometryArc::ComputeVars()
{
	double radius=0.0;
	//if curvature is 0, radius is also 0, otherwise, radius is 1/curvature
	if (fabs(mCurvature)>1.00e-15)
	{
		radius = fabs(1.0/mCurvature);
	}
	//calculate the start angle for the arc plot
	if (mCurvature<=0)
		mStartAngle=mHdg+M_PI_2; 
	else
		mStartAngle=mHdg-M_PI_2;

	mCircleX=mX+cos(mStartAngle-M_PI)*radius;
	mCircleY=mY+sin(mStartAngle-M_PI)*radius;
}

/**
 * Clones and returns the new geometry record
 */
RoadGeometry* GeometryArc::Clone() const
{
	GeometryArc* ret=new GeometryArc(mS,mX,mY, mHdg, mLength, mCurvature);
	return ret;
}

//-------------------------------------------------

/**
 * Setter for the base properties
 */
void GeometryArc::SetAll(double s, double x, double y, double hdg, double length, double curvature)
{
	SetBase(s,x,y,hdg,length,false);
	mCurvature=curvature;
	
	ComputeVars();
}
void GeometryArc::SetCurvature(double curvature)
{
	mCurvature=curvature;
	ComputeVars();
}

//-------------------------------------------------

/**
 * Getter for the base properties
 */
double GeometryArc::GetCurvature()
{
	return mCurvature;
}

//-------------------------------------------------

/**
 * Gets the coordinates at the sample S offset
 */
void GeometryArc::GetCoords(double s_check, double &retX, double &retY, double &retHDG)
{
	//s from the beginning of the segment
	double currentLength = s_check - mS;
	double endAngle=mStartAngle;
	double radius=0.0;
	//if curvature is 0, radius is also 0, so don't add anything to the initial radius, 
	//otherwise, radius is 1/curvature so the central angle can be calculated and added to the initial direction
	if (fabs(mCurvature)>1.00e-15)
	{
		endAngle+= currentLength/(1.0/mCurvature);
		radius = fabs(1.0/mCurvature);
	}

	//coords on the arc for given s value
	retX=mCircleX+cos(endAngle)*radius;
	retY=mCircleY+sin(endAngle)*radius;

	//heading at the given position
	if (mCurvature<=0)
		retHDG=endAngle-M_PI_2; 
	else
		retHDG=endAngle+M_PI_2;
}






//***********************************************************************************
//Spiral geometry
//***********************************************************************************
const double GeometrySpiral::sqrtPiO2=sqrt(M_PI_2);
/**
 * Constructor that initializes the base properties of the record
 */
GeometrySpiral::GeometrySpiral (double s, double x, double y, double hdg, double length, double curvatureStart,double curvatureEnd):	RoadGeometry(s, x, y, hdg, length)
{
	SetGeomType(2);
	mCurvatureStart=curvatureStart;
	mCurvatureEnd=curvatureEnd;
	ComputeVars();
}

/**
 * Computes the required vars
 */
void GeometrySpiral::ComputeVars()
{
	mA=0;

	//if the curvatureEnd is the non-zero curvature, then the motion is in normal direction along the spiral
	if ((fabs(mCurvatureEnd)>1.00e-15)&&(fabs(mCurvatureStart)<=1.00e-15))
	{
		mNormalDir=true;
		mCurvature=mCurvatureEnd;
		//Calculate the normalization term : a = 1.0/sqrt(2*End_Radius*Total_Curve_Length) 
		mA=1.0/sqrt(2*1.0/fabs(double(mCurvature))*mLength);			
		//Denormalization Factor
		mDenormalizeFactor=1.0/mA;	

		//Calculate the sine and cosine of the heading angle used to rotate the spiral according to the heading
		mRotCos=cos(mHdg);
		mRotSin=sin(mHdg);
	}
	//else the motion is in the inverse direction along the spiral
	else
	{
		mNormalDir=false;
		mCurvature=mCurvatureStart;
		//Calculate the normalization term : a = 1.0/sqrt(2*End_Radius*Total_Curve_Length) 
		mA=1.0/sqrt(2*1.0/fabs(mCurvature)*mLength);			

		//Because we move in the inverse direction, we need to rotate the curve according to the heading
		//around the last point of the normalized spiral
		//Calculate the total length, normalize it and divide by sqrtPiO2, then, calculate the position of the final point.
		double L=(mS2-mS)*mA/sqrtPiO2;							
		fresnl(L,&mEndY,&mEndX);
		//Invert the curve if the curvature is negative
		if (mCurvature<0)
			mEndY=-mEndY;

		//Denormalization factor
		mDenormalizeFactor=1.0/mA;									
		//Find the x,y coords of the final point of the curve in local curve coordinates
		mEndX*=mDenormalizeFactor*sqrtPiO2;						
		mEndY*=mDenormalizeFactor*sqrtPiO2;

		//Calculate the tangent angle
		differenceAngle=L*L*(sqrtPiO2*sqrtPiO2);
		double diffAngle;
		//Calculate the tangent and heading angle difference that will be used to rotate the spiral
		if (mCurvature<0)
		{
			diffAngle=mHdg-differenceAngle-M_PI;
		}
		else
		{
			diffAngle=mHdg+differenceAngle-M_PI;
		}

		//Calculate the sine and cosine of the difference angle
		mRotCos=cos(diffAngle);
		mRotSin=sin(diffAngle);
	}
}

/**
 * Clones and returns the new geometry record
 */
RoadGeometry* GeometrySpiral::Clone() const
{
	GeometrySpiral* ret=new GeometrySpiral(mS,mX,mY, mHdg, mLength, mCurvatureStart, mCurvatureEnd);
	return ret;
}


//-------------------------------------------------

/**
 * Setter for the base properties
 */
void GeometrySpiral::SetAll(double s, double x, double y, double hdg, double length, double curvatureStart,double curvatureEnd)
{
	SetBase(s,x,y,hdg,length,false);
	mCurvatureStart=curvatureStart;
	mCurvatureEnd=curvatureEnd;
	ComputeVars();
}
void GeometrySpiral::SetCurvatureStart(double curvature)
{
	mCurvatureStart=curvature;
	ComputeVars();
}
void GeometrySpiral::SetCurvatureEnd(double curvature)
{
	mCurvatureEnd=curvature;
	ComputeVars();
}

//-------------------------------------------------

/**
 * Getter for the base properties
 */
double GeometrySpiral::GetCurvatureStart()
{
	return mCurvatureStart;
}
double GeometrySpiral::GetCurvatureEnd()
{
	return mCurvatureEnd;
}

//-------------------------------------------------
/**
 * Gets the coordinates at the sample S offset
 */
void GeometrySpiral::GetCoords(double s_check, double &retX, double &retY, double &retHDG)
{
	double l=0.0;
	double tmpX=0.0, tmpY=0.0;

	//Depending on the moving direction, calculate the length of the curve from its beginning to the current point and normalize
	//it by multiplying with the "a" normalization term
	//Cephes lib for solving Fresnel Integrals, uses cos/sin (PI/2 * X^2) format in its function.
	//So, in order to use the function, transform the argument (which is just L) by dividing it by the sqrt(PI/2) factor and multiply the results by it.
	if (mNormalDir)
	{ 
		l=(s_check-mS)*mA/sqrtPiO2;
	}
	else
	{
		l=(mS2-s_check)*mA/sqrtPiO2;		
	}

	//Solve the Fresnel Integrals
	fresnl(l,&tmpY,&tmpX);
	//If the curvature is negative, invert the curve on the Y axis
	if (mCurvature<0)
		tmpY=-tmpY;

	//Denormalize the results and multiply by the sqrt(PI/2) term
	tmpX*=mDenormalizeFactor*sqrtPiO2;	
	tmpY*=mDenormalizeFactor*sqrtPiO2;

	//Calculate the heading at the found position. Kill the sqrt(PI/2) term that was added to the L
	l=(s_check-mS)*mA;
	double tangentAngle = l*l;
	if (mCurvature<0)
		tangentAngle=-tangentAngle;
	retHDG=mHdg+tangentAngle;


	if (!mNormalDir)
	{
		//If we move in the inverse direction, translate the spiral in order to rotate around its final point
		tmpX-=mEndX;	
		tmpY-=mEndY;
		//also invert the spiral in the y axis
		tmpY=-tmpY;
	}

	//Translate the curve to the required position and rotate it according to the heading
	retX=mX+ tmpX*mRotCos-tmpY*mRotSin;
	retY=mY+ tmpY*mRotCos+tmpX*mRotSin;
}





//***********************************************************************************
//Cubic Polynom geometry. Has to be implemented
//***********************************************************************************
/**
 * Constructor that initializes the base properties of the record
 */
GeometryPoly3::GeometryPoly3 (double s, double x, double y, double hdg, double length, double a, double b,double c, double d ):	RoadGeometry(s, x, y, hdg, length)
{	
	SetGeomType(3); mA=a; mB=b; mC=c; mD=d;	
}

/**
 * Clones and returns the new geometry record
 */
RoadGeometry* GeometryPoly3::Clone() const
{
	GeometryPoly3* ret=new GeometryPoly3(mS,mX,mY, mHdg, mLength, mA, mB, mC, mD);
	return ret;
}

//-------------------------------------------------
/**
 * Setter for the base properties
 */
void GeometryPoly3::SetAll(double s, double x, double y, double hdg, double length, double a,double b,double c,double d)
{
	SetBase(s,x,y,hdg,length,false);
	mA=a;
	mB=b;
	mC=c;
	mD=d;
	ComputeVars();
}




//***********************************************************************************
//Base class for Geometry blocks
//***********************************************************************************
/**
 * Constructor
 */
GeometryBlock::GeometryBlock()
{}

/**
 * Copy constructor
 */
GeometryBlock::GeometryBlock(const GeometryBlock& geomBlock)
{
	for (vector<RoadGeometry*>::const_iterator member = geomBlock.mGeometryBlockElement.begin();	member != geomBlock.mGeometryBlockElement.end();	 member++)
		mGeometryBlockElement.push_back((*member)->Clone());

}

/**
 * Assignment operator overload
 */
const GeometryBlock& GeometryBlock::operator=(const GeometryBlock& otherGeomBlock)
{
	if (this!= &otherGeomBlock)
	{

		for (vector<RoadGeometry*>::iterator member = mGeometryBlockElement.begin();	member != mGeometryBlockElement.end();	 member++)
		{
			if(GeometryLine *line = dynamic_cast<GeometryLine *>(*member))
			{
				delete line;
			}
			else if(GeometryArc *arc = dynamic_cast<GeometryArc *>(*member))
			{
				delete arc;
			}
			else if(GeometrySpiral *spiral = dynamic_cast<GeometrySpiral *>(*member))
			{
				delete spiral;
			}
			else if(GeometryPoly3 *poly = dynamic_cast<GeometryPoly3 *>(*member))
			{
				delete poly;
			}
		}
		mGeometryBlockElement.clear();

		for (vector<RoadGeometry*>::const_iterator member = otherGeomBlock.mGeometryBlockElement.begin();	member != otherGeomBlock.mGeometryBlockElement.end();	 member++)
			mGeometryBlockElement.push_back((*member)->Clone());
	}
	return *this;
}


//-------------------------------------------------

/**
 * Methods used to add geometry recors to the geometry record vector
 */
void GeometryBlock::AddGeometryLine(double s, double x, double y, double hdg, double length)
{	
	mGeometryBlockElement.push_back(new GeometryLine(s, x, y, hdg, length));	
}
void GeometryBlock::AddGeometryArc(double s, double x, double y, double hdg, double length, double curvature)
{	
	mGeometryBlockElement.push_back(new GeometryArc(s, x, y, hdg, length, curvature));	
}
void GeometryBlock::AddGeometrySpiral(double s, double x, double y, double hdg, double length, double curvatureStart,double curvatureEnd)
{	
	mGeometryBlockElement.push_back(new GeometrySpiral(s, x, y, hdg, length, curvatureStart, curvatureEnd));	
}
void GeometryBlock::AddGeometryPoly3(double s, double x, double y, double hdg, double length, double a,double b,double c,double d)
{	
	mGeometryBlockElement.push_back(new GeometryPoly3(s, x, y, hdg, length, a, b, c, d));	
}

//-------------------------------------------------

/**
 * Getter for the geometry record at a given index position of the vector
 */
RoadGeometry* GeometryBlock::GetGeometryAt(int index)
{
	return mGeometryBlockElement.at(index);
}

/**
 * Getter for the overal block length (summ of geometry record lengths)
 */
double GeometryBlock::GetBlockLength()
{
	double lTotal=0;
	for (unsigned int i=0;i<mGeometryBlockElement.size();i++)
	{
		lTotal+=mGeometryBlockElement.at(i)->GetLength();
	}
	return lTotal;
}

/**
 *  Checks if the block is a straight line block or a turn
 */
bool GeometryBlock::CheckIfLine()
{
	if(mGeometryBlockElement.size()>1) return false;
	else return true;
}

//-------------------------------------------------

/**
 * Recalculates the geometry blocks when one of the geometry records is modified
 * Makes sure that every geometry records starts where the previous record ends
 */
void GeometryBlock::Recalculate(double s, double x, double y, double hdg)
{
	double lS=s;
	double lX=x;
	double lY=y;
	double lHdg=hdg;

	if(mGeometryBlockElement.size()==1)
	{
		GeometryLine *lGeometryLine	=  static_cast<GeometryLine*>(mGeometryBlockElement.at(0));
		if(lGeometryLine!=NULL)
		{
			// Updates the line to reflect the changes of the previous block
			lGeometryLine->SetBase(lS,lX,lY,lHdg,lGeometryLine->GetLength());
		}
	}
	else if(mGeometryBlockElement.size()==3)
	{
		GeometrySpiral *lGeometrySpiral1	=  static_cast<GeometrySpiral*>(mGeometryBlockElement.at(0));
		GeometryArc *lGeometryArc			=  static_cast<GeometryArc*>(mGeometryBlockElement.at(1));
		GeometrySpiral *lGeometrySpiral2	=  static_cast<GeometrySpiral*>(mGeometryBlockElement.at(2));
		if(lGeometrySpiral1!=NULL && lGeometryArc!=NULL && lGeometrySpiral2!=NULL)
		{
			// Updates the first spiral to reflect the changes of the previous block
			lGeometrySpiral1->SetBase(lS,lX,lY,lHdg,lGeometrySpiral1->GetLength());

			// Reads the new coords of the spiral
			lS=lGeometrySpiral1->GetS2();
			lGeometrySpiral1->GetCoords(lS,lX,lY,lHdg);

			// Updates the arc to reflect the changes to the first spiral
			lGeometryArc->SetBase(lS,lX,lY,lHdg,lGeometryArc->GetLength());

			// Reads the new coords of the arc
			lS=lGeometryArc->GetS2();
			lGeometryArc->GetCoords(lS,lX,lY,lHdg);

			// Updates the second spiral to reflect hte changes to the arc
			lGeometrySpiral2->SetBase(lS,lX,lY,lHdg,lGeometrySpiral2->GetLength());
		}
	}
}

//-------------------------------------------------

/**
 *  Gets the S at the end of the block
 */
double GeometryBlock::GetLastS2()
{
	if(mGeometryBlockElement.size()>0)
		return mGeometryBlockElement.at(mGeometryBlockElement.size()-1)->GetS2();
	else
		return 0;
}

/**
 *  Gets the last geometry in the geometry vector
 */
RoadGeometry* GeometryBlock::GetLastGeometry()
{
	return mGeometryBlockElement.at(mGeometryBlockElement.size()-1);
}

/**
 *  Gets the coordinates at the end of the last geometry
 */
short int GeometryBlock::GetLastCoords(double &s, double &retX, double &retY, double &retHDG)
{
	int lSize = mGeometryBlockElement.size();
	if(lSize>0)
	{
		RoadGeometry* lGeometry = mGeometryBlockElement.at(lSize-1);
		s = lGeometry->GetS2();
		lGeometry->GetCoords(s, retX, retY, retHDG);
	}
	else
	{
		s=0;
		retX=0;
		retY=0;
		retHDG=0;
	}
	return 0;
}

/**
 *  Check if sample S belongs to this block
 */
bool GeometryBlock::CheckInterval(double s_check)
{
	for (unsigned int i=0;i<mGeometryBlockElement.size();i++)
	{
		//if the s_check belongs to one of the geometries
		if (mGeometryBlockElement.at(i)->CheckInterval(s_check))
			return true;
	}
	return false;
}

/**
 *  Gets the coordinates at the sample S offset
 */
short int GeometryBlock::GetCoords(double s_check, double &retX, double &retY)
{
	double tmp;
	return GetCoords(s_check, retX, retY, tmp);
}

/**
 *  Gets the coordinates and heading at the end of the last geometry 
 */
short int  GeometryBlock::GetCoords(double s_check, double &retX, double &retY, double &retHDG)
{
	// go through all the elements
	for (unsigned int i=0;i<mGeometryBlockElement.size();i++)
	{
		//if the s_check belongs to one of the geometries
		if (mGeometryBlockElement.at(i)->CheckInterval(s_check))
		{
			//get the x,y coords and return the type of the geometry
			mGeometryBlockElement.at(i)->GetCoords(s_check, retX, retY, retHDG);
			return mGeometryBlockElement.at(i)->GetGeomType();
		}
	}
	//if nothing found, return -999
	return -999;

}

//-------------------------------------------------
/**
 *  Destructor
 */
GeometryBlock::~GeometryBlock()
{
	// Clears the geometry record vector
	for (vector<RoadGeometry*>::iterator member = mGeometryBlockElement.begin();	member != mGeometryBlockElement.end();	 member++)
	{
		if(GeometryLine *line = dynamic_cast<GeometryLine *>(*member))
		{
			delete line;
		}
		else if(GeometryArc *arc = dynamic_cast<GeometryArc *>(*member))
		{
			delete arc;
		}
		else if(GeometrySpiral *spiral = dynamic_cast<GeometrySpiral *>(*member))
		{
			delete spiral;
		}
		else if(GeometryPoly3 *poly = dynamic_cast<GeometryPoly3 *>(*member))
		{
			delete poly;
		}
	}
	mGeometryBlockElement.clear();
}

//----------------------------------------------------------------------------------
