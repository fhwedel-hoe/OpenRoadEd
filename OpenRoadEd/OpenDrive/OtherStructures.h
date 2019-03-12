#ifndef OTHERSTRUCTURES_H
#define OTHERSTRUCTURES_H
#include <string>
using std::string;

/**
 * Polynom of third order
 *
 */
class ThirdOrderPolynom
{
protected:
	double mS;
	double mA;
	double mB;
	double mC;
	double mD;
public:
	/**
	 * Constructor that initializes the polynom with base properties
	 * 
	 * @param s S offset
	 * @param a A parameter of the polynom
	 * @param b B parameter of the polynom
	 * @param c C parameter of the polynom
	 * @param d D parameter of the polynom
	 */
	ThirdOrderPolynom (double s, double a, double b, double c, double d);
	

	/**
	 * Setters for base properties
	 */	
	void SetS(double s);
	void SetA(double a);
	void SetB(double b);
	void SetC(double c);
	void SetD(double d);
	

	/**
	 * Getters for base properties
	 */		
	double GetS();
	double GetA();
	double GetB();
	double GetC();
	double GetD();
	

	/**
	 * Method to check if sample S is inside the record interval
	 */	
	bool CheckInterval (double s_check);

	/**
	 * Returns the value at sample S
	 */	
	double GetValue(double s_check);

};
//----------------------------------------------------------------------------------



#endif
