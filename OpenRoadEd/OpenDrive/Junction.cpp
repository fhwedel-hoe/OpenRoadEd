#include "Junction.h"

/**
* Junction class. Holds all the junction information
*
*
*
*
*/

/**
* Constructor. Sets basic junction parameters
* @param name Name of the junction
* @param id Unique ID of the junction
*/
Junction::Junction(	string name, string id)
{
	mName=name;
	mId=id;
}

/**
* Sets the name parameter
*/
void Junction::SetName(string name)
{	mName=name;	}

/**
* Sets the ID parameter
*/
void Junction::SetId(string id)
{	mId=id;	}


/**
* Adds a junction connection to the junction
* @param id ID within the junction
* @param incomingRoad ID of the incoming road
* @param connectingRoad ID of the connecting path
* @param contactPoint Contact point on the connecting road (start or end)
*/
unsigned int Junction::AddJunctionConnection(	string id,	string incomingRoad, string connectingRoad, string contactPoint)
{	
	// Adds a new junction connection
	mJunctionConnectionVector.push_back(JunctionConnection(id, incomingRoad, connectingRoad, contactPoint));	
	// Saves the index of the newly added junction connection
	mLastAddedJunctionConnection = mJunctionConnectionVector.size()-1;
	return mLastAddedJunctionConnection;
}


/**
* Adds a priority parameter to the junction
* @param high ID of the connecting road with higher priority
* @param low ID of the connecting road with lower priority
*/
unsigned int Junction::AddJunctionPriority ( string high, string low)
{	
	// Check the first method in the group for details

	mJunctionPriorityVector.push_back(JunctionPriorityRoad(high,low));	
	mLastAddedJunctionPriority = mJunctionPriorityVector.size()-1;
	return mLastAddedJunctionPriority;
}

/**
* Adds a controller to the junction
* @param id ID of the controller to add
* @param type Type of control
*/
unsigned int Junction::AddJunctionController ( string id, string type)
{	
	mJunctionControllerVector.push_back(JunctionController(id,type));	
	mLastAddedJunctionController = mJunctionControllerVector.size()-1;
	return mLastAddedJunctionController;
}
//--------------

/**
 * Methods used to clone child records in the respective vectors
 */
unsigned int Junction::CloneJunctionConnection(unsigned int index)
{
	// Clone the object and insert it in the middle of the vector
	if(index<mJunctionConnectionVector.size()-1)
		mJunctionConnectionVector.insert(mJunctionConnectionVector.begin()+index+1, mJunctionConnectionVector[index]);
	// or just push it to the back
	else if(index==mJunctionConnectionVector.size()-1)
		mJunctionConnectionVector.push_back(mJunctionConnectionVector[index]);
	// Save the last added record index
	mLastAddedJunctionConnection=index+1;
	return mLastAddedJunctionConnection;
}
unsigned int Junction::CloneJunctionPriority(unsigned int index)
{
	// Check the first method in the group for details

	if(index<mJunctionPriorityVector.size()-1)
		mJunctionPriorityVector.insert(mJunctionPriorityVector.begin()+index+1, mJunctionPriorityVector[index]);
	else if(index==mJunctionPriorityVector.size()-1)
		mJunctionPriorityVector.push_back(mJunctionPriorityVector[index]);
	mLastAddedJunctionPriority=index+1;
	return mLastAddedJunctionPriority;
}
unsigned int Junction::CloneJunctionController(unsigned int index)
{
	if(index<mJunctionControllerVector.size()-1)
		mJunctionControllerVector.insert(mJunctionControllerVector.begin()+index+1, mJunctionControllerVector[index]);
	else if(index==mJunctionControllerVector.size()-1)
		mJunctionControllerVector.push_back(mJunctionControllerVector[index]);
	mLastAddedJunctionController=index+1;
	return mLastAddedJunctionController;
}

/**
 * Methods used to delete child records from the respective vectors
 */
void Junction::DeleteJunctionConnection(unsigned int index)
{
	mJunctionConnectionVector.erase(mJunctionConnectionVector.begin()+index);
}
void Junction::DeleteJunctionPriority(unsigned int index)
{
	mJunctionPriorityVector.erase(mJunctionPriorityVector.begin()+index);
}
void Junction::DeleteJunctionController(unsigned int index)
{
	mJunctionControllerVector.erase(mJunctionControllerVector.begin()+index);
}

/**
* Return the name of the junction
*/
string Junction::GetName()
{	return mName;	}

/**
* Return the id of the junction
*/
string Junction::GetId()
{	return mId;	}

/**
* Return the vector that stores junction connections
* @return A pointer to std::vector of JunctionConnection type that stores junction connections
*/
std::vector<JunctionConnection>* Junction::GetJunctionConnectionVector ()
{	return &mJunctionConnectionVector;	}

/**
* Return the number of junction connections
* @return An unsigned int that stores the number of junction connections
*/
unsigned int Junction::GetJunctionConnectionCount()
{	return mJunctionConnectionVector.size();	}

/**
* Return the pointer to a junction connection at provided index
* @param i Index to the junction connection that is returned
* @return A pointer to JunctionConnection object
*/
JunctionConnection* Junction::GetJunctionConnection(unsigned int i)
{	return &mJunctionConnectionVector.at(i);	}

/**
* Return the pointer to the last junction connection
* @return A pointer to JunctionConnection object
*/
JunctionConnection* Junction::GetLastJunctionConnection()
{	
	if(mJunctionConnectionVector.size()>0)
		return &mJunctionConnectionVector.at(mJunctionConnectionVector.size()-1);	
	else
		return NULL;
}
/**
* Return the pointer to the last added junction connection (which might not be the one from the end of the vector)
* @return A pointer to JunctionConnection object
*/
JunctionConnection* Junction::GetLastAddedJunctionConnection()
{	
	if(mLastAddedJunctionConnection<mJunctionConnectionVector.size())
		return &mJunctionConnectionVector.at(mLastAddedJunctionConnection);
	else
		return NULL;
}

/**
* Return the vector that stores junction priority records
* @return A pointer to std::vector of JunctionPriorityRoad type that stores junction priority records
*/
std::vector<JunctionPriorityRoad>* Junction::GetJunctionPriorityVector()
{	return &mJunctionPriorityVector;	}

/**
* Return the number of junction priority records
* @return An unsigned int that stores the number of junction priority records
*/
unsigned int Junction::GetJunctionPriorityCount()
{	return mJunctionPriorityVector.size();	}

/**
* Return the pointer to a junction priority record at provided index
* @param i Index to the junction priority record that is returned
* @return A pointer to JunctionPriorityRoad object
*/
JunctionPriorityRoad* Junction::GetJunctionPriority(unsigned int i)
{	return &mJunctionPriorityVector.at(i);	}

/**
* Return the pointer to the last junction priority record
* @return A pointer to JunctionPriorityRoad object
*/
JunctionPriorityRoad* Junction::GetLastJunctionPriority()
{	
	if(mJunctionPriorityVector.size()>0)
		return &mJunctionPriorityVector.at(mJunctionPriorityVector.size()-1);	
	else 
		return NULL;
}

/**
* Return the pointer to the last added junction priority record (which might not be the one from the end of the vector)
* @return A pointer to JunctionPriorityRoad object
*/
JunctionPriorityRoad* Junction::GetLastAddedJunctionPriority()
{	
	if(mLastAddedJunctionPriority<mJunctionPriorityVector.size())
		return &mJunctionPriorityVector.at(mLastAddedJunctionPriority);
	else
		return NULL;
}


/**
* Return the vector that stores junction controller records
* @return A pointer to std::vector of JunctionController type that stores junction controller records
*/
std::vector<JunctionController>* Junction::GetJunctionControllerVector()
{	return &mJunctionControllerVector;	}

/**
* Return the number of junction controller records
* @return An unsigned int that stores the number of junction controller records
*/
unsigned int  Junction::GetJunctionControllerCount()
{	return mJunctionControllerVector.size();	}

/**
* Return the pointer to a junction controller record at provided index
* @param i Index to the junction controller record that is returned
* @return A pointer to JunctionController object
*/
JunctionController* Junction::GetJunctionController(unsigned int i)
{	return &mJunctionControllerVector.at(i);	}

/**
* Return the pointer to the last junction controller record
* @return A pointer to JunctionController object
*/
JunctionController* Junction::GetLastJunctionController()
{	
	if(mJunctionControllerVector.size()>0)
		return &mJunctionControllerVector.at(mJunctionControllerVector.size()-1);	
	else
		return NULL;
}

/**
* Return the pointer to the last added junction controller record (which might not be the one from the end of the vector)
* @return A pointer to JunctionController object
*/
JunctionController* Junction::GetLastAddedJunctionController()
{	
	if(mLastAddedJunctionController<mJunctionControllerVector.size())
		return &mJunctionControllerVector.at(mLastAddedJunctionController);
	else
		return NULL;
}
//--------------


/**
* Junction connection class. Holds all the information for a connection record
*
*
*
*
*/

/**
* Constructor. Sets basic junction connection parameters
* @param id ID within the junction
* @param incomingRoad ID of the incoming road
* @param connectingRoad ID of the connecting path
* @param contactPoint Contact point on the connecting road (start / end)
*/
JunctionConnection::JunctionConnection(	string id, string incomingRoad, string connectingRoad, string contactPoint	)
{
	mId=id;
	mIncomingRoad=incomingRoad;
	mConnectingRoad=connectingRoad;
	mContactPoint=contactPoint;	
}

/**
* Set the ID parameter
*/
void JunctionConnection::SetId(string id)
{	mId=id;	}

/**
* Set the ID of the incoming road 
*/
void JunctionConnection::SetIncomingRoad(string incomingRoad)
{	mIncomingRoad=incomingRoad;	}

/**
* Set the ID of the connecting path
*/
void JunctionConnection::SetConnectingRoad(string connectingRoad)
{	mConnectingRoad=connectingRoad;	}

/**
* Set the contact point parameter
* @param contactPoint Contact point of the connecting road. Can be either start or end
*/
void JunctionConnection::SetContactPoint(string contactPoint)
{	mContactPoint=contactPoint;	}

/**
* Add a lane link record
* @param from ID of the incoming lane
* @param to ID of the connecting lane
*/
unsigned int JunctionConnection::AddJunctionLaneLink(int from, int to)
{	
	mJunctionLaneLinkVector.push_back(JunctionLaneLink(from, to));	
	mLastAddedJunctionLaneLink = mJunctionLaneLinkVector.size()-1;
	return mLastAddedJunctionLaneLink;
}
//--------------

/**
 * Method used to clone child record in the respective vectors
 */
unsigned int JunctionConnection::CloneJunctionLaneLink(unsigned int index)
{
	// Clone the object and insert it in the middle of the vector
	if(index<mJunctionLaneLinkVector.size()-1)
		mJunctionLaneLinkVector.insert(mJunctionLaneLinkVector.begin()+index+1, mJunctionLaneLinkVector[index]);
	// or just push it to the back
	else if(index==mJunctionLaneLinkVector.size()-1)
		mJunctionLaneLinkVector.push_back(mJunctionLaneLinkVector[index]);
	// Save the last added record index
	mLastAddedJunctionLaneLink=index+1;
	return mLastAddedJunctionLaneLink;
}

/**
* Delete the lane link parameter at the provided index
*/
void JunctionConnection::DeleteJunctionLaneLink(unsigned int index)
{
	mJunctionLaneLinkVector.erase(mJunctionLaneLinkVector.begin()+index);
}


/**
* Get the ID parameter
*/
string JunctionConnection::GetId()
{	return mId;	}

/**
* Get the ID fo the incoming road
*/
string JunctionConnection::GetIncomingRoad()
{	return mIncomingRoad;	}

/**
* Get the ID of the connecting road
*/
string JunctionConnection::GetConnectingRoad()
{	return mConnectingRoad;	}

/**
* Get the contact point parameter
*/
string JunctionConnection::GetContactPoint()
{	return mContactPoint;	}

/**
* Return the vector that stores junction lane link records
* @return A pointer to std::vector of JunctionLaneLink type that stores junction lane link records
*/
std::vector<JunctionLaneLink>* JunctionConnection::GetJunctionLaneLinkVector()
{	return &mJunctionLaneLinkVector;	}

/**
* Return the number of junction lane link records
* @return An unsigned int that stores the number of junction lane link records
*/
unsigned int JunctionConnection::GetJunctionLaneLinkCount()
{	return mJunctionLaneLinkVector.size();	}

/**
* Return the pointer to a junction lane link record at provided index
* @param i Index to the junction lane link record that is returned
* @return A pointer to JunctionLaneLink object
*/
JunctionLaneLink* JunctionConnection::GetJunctionLaneLink(unsigned int i)
{	return &mJunctionLaneLinkVector.at(i);	}

/**
* Return the pointer to the last junction lane link record
* @return A pointer to JunctionLaneLink object
*/
JunctionLaneLink* JunctionConnection::GetLastJunctionLaneLink()
{	
	if(mJunctionLaneLinkVector.size()>0)
		return &mJunctionLaneLinkVector.at(mJunctionLaneLinkVector.size()-1);	
	else
		return NULL;
}

/**
* Return the pointer to the last added junction lane link record (which might not be the one from the end of the vector)
* @return A pointer to JunctionLaneLink object
*/
JunctionLaneLink* JunctionConnection::GetLastAddedJunctionLaneLink()
{	
	if(mLastAddedJunctionLaneLink<mJunctionLaneLinkVector.size())
		return &mJunctionLaneLinkVector.at(mLastAddedJunctionLaneLink);
	else
		return NULL;
}



/**
* Junction lane link class. Holds all the information for a lane link record
*
*
*
*
*/

/**
* Constructor. Initializes the parameters
* @param from ID of the incoming lane
* @param to ID of the connecting lane
*/
JunctionLaneLink::JunctionLaneLink(int from, int to)
{	mFrom=from; mTo=to;	}


/**
* Set the ID of the incoming lane
*/
void JunctionLaneLink::SetFrom (int from)
{	mFrom=from;	}

/**
* Set the ID of the connecting lane
*/
void JunctionLaneLink::SetTo (int to)
{	mTo=to;	}

/**
* Get the ID of the incoming lane
*/
int JunctionLaneLink::GetFrom()
{	return mFrom;	}

/**
* Get the ID of the connecting lane
*/
int JunctionLaneLink::GetTo()
{	return mTo;	}


/**
* Junction priority class. Holds all the information for a priority record
*
*
*
*
*/

/**
* Constructor. Initializes the parameters
* @param high ID of the connecting road with higher priority
* @param low ID of the connecting road with lower priority
*/
JunctionPriorityRoad::JunctionPriorityRoad(string high, string low)
{
	mHigh=high;
	mLow=low;
}

/**
* Set the ID of the connecting road with higher priority
*/
void JunctionPriorityRoad::SetHigh (string high)
{	mHigh=high;	}

/**
* Set the ID of the connecting road with lower priority
*/
void JunctionPriorityRoad::SetLow (string low)
{	mLow=low;	}

/**
* Get the ID of the connecting road with higher priority
*/
string JunctionPriorityRoad::GetHigh()
{	return mHigh;	}

/**
* Get the ID of the connecting road with lower priority
*/
string JunctionPriorityRoad::GetLow()
{	return mLow;	}


/**
* Junction controller class. Holds all the information for a priority record
*
*
*
*
*/

/**
* Constructor. Initializes the parameters
* @param id ID of the controller to add
* @param type Type of control
*/
JunctionController::JunctionController(string id, string type)
{	mId=id; mType=type;	}

/**
* Set the ID of the controller to add
*/
void JunctionController::SetId (string id)
{	mId=id;	}

/**
* Set the type of control
*/
void JunctionController::SetType (string type)
{	mType=type;	}

/**
* Get the ID of the controller to add
*/
string JunctionController::GetId()
{	return mId;	}

/**
* Get the type of control
*/
string JunctionController::GetType()
{	return mType;	}