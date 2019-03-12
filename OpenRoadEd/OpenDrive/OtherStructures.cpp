#include "OtherStructures.h"

//***********************************************************************************
//Polynom of third order
//***********************************************************************************
/**
 * Constructor that initializes the polynom with base properties
 * 
 * @param s S offset
 * @param a A parameter of the polynom
 * @param b B parameter of the polynom
 * @param c C parameter of the polynom
 * @param d D parameter of the polynom
 */
ThirdOrderPolynom::ThirdOrderPolynom (double s, double a, double b, double c, double d)
{	
	mS=s; mA=a; mB=b; mC=c; mD=d;	
}

/**
 * Getters for base properties
 */	
double ThirdOrderPolynom::GetS()
{
	return mS;
}
double ThirdOrderPolynom::GetA()
{
	return mA;
}
double ThirdOrderPolynom::GetB()
{
	return mB;
}
double ThirdOrderPolynom::GetC()
{
	return mC;
}

double ThirdOrderPolynom::GetD()
{
	return mD;
}

/**
 * Setters for base properties
 */
void ThirdOrderPolynom::SetS(double s)
{
	mS=s;
}
void ThirdOrderPolynom::SetA(double a)
{
	mA=a;
}
void ThirdOrderPolynom::SetB(double b)
{
	mB=b;
}
void ThirdOrderPolynom::SetC(double c)
{
	mC=c;
}
void ThirdOrderPolynom::SetD(double d)
{
	mD=d;
}


/**
 * Method to check if sample S is inside the record interval
 */	
bool ThirdOrderPolynom::CheckInterval (double s_check)
{
	if (s_check>=mS)
		return true;
	else 
		return false;
}

/**
 * Returns the value at sample S
 */	
double ThirdOrderPolynom::GetValue(double s_check)
{
	double ds = s_check-mS;
	double value = mA+ mB*ds+ mC*ds*ds + mD*ds*ds*ds;
	return value;
}
//----------------------------------------------------------------------------------
