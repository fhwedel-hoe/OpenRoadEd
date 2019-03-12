#ifndef JUNCTION_H
#define JUNCTION_H

#include <string>
#include <vector>
using std::string;

//Prototypes
class Junction;
class JunctionConnection;
class JunctionLaneLink;
class JunctionController;
class JunctionPriorityRoad;

/**
 * Junction class. Holds all the junction information
 *
 *
 *
 *
 */
class Junction
{
private:
	/**
	 * Junction parameters
	 */
	std::string mName;
	std::string mId;

	/**
	 * Vector based parameters of the junction
	 */
	std::vector<JunctionConnection> mJunctionConnectionVector;
	std::vector<JunctionPriorityRoad> mJunctionPriorityVector;
	std::vector<JunctionController> mJunctionControllerVector;

public:

	/**
	 * Indices of the last added records
	 */
	unsigned int mLastAddedJunctionConnection;
	unsigned int mLastAddedJunctionPriority;
	unsigned int mLastAddedJunctionController;

	/**
	 * Constructor. Sets basic junction parameters
	 * @param name Name of the junction
	 * @param id Unique ID of the junction
	 */
	Junction(string name, string id);

	/**
	 * Sets the name parameter
	 */
	void SetName(string name);
	/**
	 * Sets the ID parameter
	 */
	void SetId(string id);

	/**
	 * Adds a junction connection to the junction
	 * @param id ID within the junction
	 * @param incomingRoad ID of the incoming road
	 * @param connectingRoad ID of the connecting path
	 * @param contactPoint Contact point on the connecting road (start or end)
	 */
	unsigned int AddJunctionConnection(string id,	string incomingRoad, string connectingRoad, string contactPoint);

	/**
	 * Adds a priority parameter to the junction
	 * @param high ID of the connecting road with higher priority
	 * @param low ID of the connecting road with lower priority
	 */
	unsigned int AddJunctionPriority(string high, string low);

	/**
	 * Adds a controller to the junction
	 * @param id ID of the controller to add
	 * @param type Type of control
	 */
	unsigned int AddJunctionController(string id, string type);

	/**
	 * Clone the connection record
	 * @param index Index of the record to clone
	 */
	unsigned int CloneJunctionConnection(unsigned int index);
	unsigned int CloneJunctionPriority(unsigned int index);
	unsigned int CloneJunctionController(unsigned int index);


	void DeleteJunctionConnection(unsigned int index);
	void DeleteJunctionPriority(unsigned int index);
	void DeleteJunctionController(unsigned int index);

	/**
	 * Return the name of the junction
	 */
	string GetName();

	/**
	 * Return the id of the junction
	 */
	string GetId();

	/**
	 * Return the vector that stores junction connections
	 * @return A pointer to std::vector of JunctionConnection type that stores junction connections
	 */
	std::vector<JunctionConnection>* GetJunctionConnectionVector ();

	/**
	 * Return the number of junction connections
	 * @return An unsigned int that stores the number of junction connections
	 */
	unsigned int GetJunctionConnectionCount();

	/**
	 * Return the pointer to a junction connection at provided index
	 * @param i Index to the junction connection that is returned
	 * @return A pointer to JunctionConnection object
	 */
	JunctionConnection* GetJunctionConnection(unsigned int i);

	/**
	 * Return the pointer to the last junction connection
	 * @return A pointer to JunctionConnection object
	 */
	JunctionConnection* Junction::GetLastJunctionConnection();

	/**
	 * Return the pointer to the last added junction connection (which might not be the one from the end of the vector)
	 * @return A pointer to JunctionConnection object
	 */
	JunctionConnection* Junction::GetLastAddedJunctionConnection();
	
	/**
	 * Return the vector that stores junction priority records
	 * @return A pointer to std::vector of JunctionPriorityRoad type that stores junction priority records
	 */
	std::vector<JunctionPriorityRoad>* GetJunctionPriorityVector();

	/**
	 * Return the number of junction priority records
	 * @return An unsigned int that stores the number of junction priority records
	 */
	unsigned int GetJunctionPriorityCount();

	/**
	 * Return the pointer to a junction priority record at provided index
	 * @param i Index to the junction priority record that is returned
	 * @return A pointer to JunctionPriorityRoad object
	 */
	JunctionPriorityRoad* GetJunctionPriority(unsigned int i);

	/**
	 * Return the pointer to the last junction priority record
	 * @return A pointer to JunctionPriorityRoad object
	 */
	JunctionPriorityRoad* Junction::GetLastJunctionPriority();

	
	/**
	 * Return the pointer to the last added junction priority record (which might not be the one from the end of the vector)
	 * @return A pointer to JunctionPriorityRoad object
	 */
	JunctionPriorityRoad* Junction::GetLastAddedJunctionPriority();

	/**
	 * Return the vector that stores junction controller records
	 * @return A pointer to std::vector of JunctionController type that stores junction controller records
	 */
	std::vector<JunctionController>* GetJunctionControllerVector();

	/**
	 * Return the number of junction controller records
	 * @return An unsigned int that stores the number of junction controller records
	 */
	unsigned int  GetJunctionControllerCount();

	/**
	 * Return the pointer to a junction controller record at provided index
	 * @param i Index to the junction controller record that is returned
	 * @return A pointer to JunctionController object
	 */
	JunctionController* GetJunctionController(unsigned int i);

	/**
	 * Return the pointer to the last junction controller record
	 * @return A pointer to JunctionController object
	 */
	JunctionController* Junction::GetLastJunctionController();

	/**
	 * Return the pointer to the last added junction controller record (which might not be the one from the end of the vector)
	 * @return A pointer to JunctionController object
	 */
	JunctionController* Junction::GetLastAddedJunctionController();

};


/**
 * Junction connection class. Holds all the information for a connection record
 *
 *
 *
 *
 */
class JunctionConnection
{
private:
	/**
	 * Connection parameters
	 */
	string mId;
	string mIncomingRoad;
	string mConnectingRoad;
	string mContactPoint;	//Possible values: start / end

	/**
	 * Lane linkage parameters vector
	 */
	std::vector<JunctionLaneLink> mJunctionLaneLinkVector;
public:
	
	unsigned int mLastAddedJunctionLaneLink;

	/**
	 * Constructor. Sets basic junction connection parameters
	 * @param id ID within the junction
	 * @param incomingRoad ID of the incoming road
	 * @param connectingRoad ID of the connecting path
	 * @param contactPoint Contact point on the connecting road (start / end)
	 */
	JunctionConnection(	string id, string incomingRoad, string connectingRoad, string contactPoint);

	/**
	 * Set the ID parameter
	 */
	void SetId(string id);

	/**
	 * Set the ID of the incoming road 
	 */
	void SetIncomingRoad(string incomingRoad);

	/**
	 * Set the ID of the connecting path
	 */
	void SetConnectingRoad(string connectingRoad);

	/**
	 * Set the contact point parameter
	 * @param contactPoint Contact point of the connecting road. Can be either start or end
	 */
	void SetContactPoint(string contactPoint);

	/**
	 * Add a lane link record
	 * @param from ID of the incoming lane
	 * @param to ID of the connecting lane
	 */
	unsigned int AddJunctionLaneLink(int from, int to);

	//clone elements
	unsigned int CloneJunctionLaneLink(unsigned int index);

	/**
	 * Delete the lane link parameter at the provided index
	 */
	void DeleteJunctionLaneLink(unsigned int index);

	/**
	 * Get the ID parameter
	 */
	string GetId();

	/**
	 * Get the ID fo the incoming road
	 */
	string GetIncomingRoad();
	
	/**
	 * Get the ID of the connecting road
	 */
	string GetConnectingRoad();
	
	/**
	 * Get the contact point parameter
	 */
	string GetContactPoint();

	/**
	 * Return the vector that stores junction lane link records
	 * @return A pointer to std::vector of JunctionLaneLink type that stores junction lane link records
	 */
	std::vector<JunctionLaneLink>* GetJunctionLaneLinkVector();
	
	/**
	 * Return the number of junction lane link records
	 * @return An unsigned int that stores the number of junction lane link records
	 */
	unsigned int GetJunctionLaneLinkCount();

	/**
	 * Return the pointer to a junction lane link record at provided index
	 * @param i Index to the junction lane link record that is returned
	 * @return A pointer to JunctionLaneLink object
	 */
	JunctionLaneLink* GetJunctionLaneLink(unsigned int);

	/**
	 * Return the pointer to the last junction lane link record
	 * @return A pointer to JunctionLaneLink object
	 */
	JunctionLaneLink* GetLastJunctionLaneLink();

	/**
	 * Return the pointer to the last added junction lane link record (which might not be the one from the end of the vector)
	 * @return A pointer to JunctionLaneLink object
	 */
	JunctionLaneLink* GetLastAddedJunctionLaneLink();


};

/**
 * Junction lane link class. Holds all the information for a lane link record
 *
 *
 *
 *
 */
class JunctionLaneLink
{
private:
	/**
	 * Record parameters
	 */
	int mFrom;
	int mTo;

public:
	/**
	 * Constructor. Initializes the parameters
	 * @param from ID of the incoming lane
	 * @param to ID of the connecting lane
	 */
	JunctionLaneLink(int from, int to);

	/**
	 * Set the ID of the incoming lane
	 */
	void SetFrom (int from);

	/**
	 * Set the ID of the connecting lane
	 */
	void SetTo (int to);

	/**
	 * Get the ID of the incoming lane
	 */
	int GetFrom();

	/**
	 * Get the ID of the connecting lane
	 */
	int GetTo();
};


/**
 * Junction priority class. Holds all the information for a priority record
 *
 *
 *
 *
 */
class JunctionPriorityRoad
{
private:
	/**
	 * Record parameters
	 */
	string mHigh;
	string mLow;
public:

	/**
	 * Constructor. Initializes the parameters
	 * @param high ID of the connecting road with higher priority
	 * @param low ID of the connecting road with lower priority
	 */
	JunctionPriorityRoad(string high, string low);

	/**
	 * Set the ID of the connecting road with higher priority
	 */
	void SetHigh (string high);

	/**
	 * Set the ID of the connecting road with lower priority
	 */
	void SetLow (string low);

	/**
	 * Get the ID of the connecting road with higher priority
	 */
	string GetHigh();

	/**
	 * Get the ID of the connecting road with lower priority
	 */
	string GetLow();

};



/**
 * Junction controller class. Holds all the information for a priority record
 *
 *
 *
 *
 */
class JunctionController
{
private:
	/**
	 * Record parameters
	 */
	string mId;
	string mType;
public:
	/**
	 * Constructor. Initializes the parameters
	 * @param id ID of the controller to add
	 * @param type Type of control
	 */
	JunctionController(string id, string type);

	/**
	 * Set the ID of the controller to add
	 */
	void SetId (string id);

	/**
	 * Set the type of control
	 */
	void SetType (string type);

	/**
	 * Get the ID of the controller to add
	 */
	string GetId();

	/**
	 * Get the type of control
	 */
	string GetType();

};

#endif