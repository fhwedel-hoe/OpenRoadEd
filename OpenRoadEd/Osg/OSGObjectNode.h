#ifndef OSGOBJECTNODE_H
#define OSGOBJECTNODE_H

#include <osg/Node>
#include <osg/Geode>
#include <osg/Billboard>
#include <Vector>

/**
* Enumeration type that contains all the OpenDRIVE available records
* 
*
*
*
*/
enum OSGNodeType 
{
	ROAD_NODE = 1,
	ROAD_TYPE_NODE, 
	GEOMETRY_BLOCK_NODE,
	ELEVATION_NODE,
	SUPERELEVATION_NODE,
	CROSSFALL_NODE,
	LANE_SECTION_NODE,
	LANE_NODE,
	LANE_WIDTH_NODE,
	LANE_ROAD_MARK_NODE,
	LANE_MATERIAL_NODE,
	LANE_VISIBILITY_NODE,
	LANE_SPEED_NODE,
	LANE_ACCESS_NODE,
	LANE_HEIGHT_NODE,
	OBJECT_NODE,
	SIGNAL_NODE,
	JUNCTION_NODE
};

/**
* A helper class
* It stores information about the records and thus it is used to link the OpenSceneGraph objects with the OpenDRIVE entities stored in the tree structure
*
*
*
*/
class OSGObjectNode
{
private:
	/**
	* Type of the object
	*/
	OSGNodeType mNodeType;
	/**
	* Hierarchycal list of indices used to access the objects in the structure
	*/
	std::vector<int> mIndices;
public:
	/**
	* Constructor
	*/
	OSGObjectNode();

	/**
	* Copy constructor
	*/
	OSGObjectNode(const OSGObjectNode& nodeInfo);

	/**
	* Assignment operator
	*/
	OSGObjectNode& operator=(OSGObjectNode const& rhs);

	/**
	* Set the type of the node
	*/
	void SetNodeType(OSGNodeType nodeType);

	/**
	* Add an index to the index vector
	*/
	void AddNodeInfoIndex(int index);

	/**
	* Get the type of the node
	*/
	OSGNodeType GetNodeType();
	/**
	* Get the index at a certain position
	*/
	int GetNodeInfoIndex(int index);

	/**
	* Clear the index array
	*/
	void ClearNodeInfoIndices();

	/**
	* Check if the index vector is empty
	*/
	bool IsEmpty();

};


/**
* Additional Object Node class that inherits OpenSceneGraph geode class
* Inherits osg::Geode
* Contains data used to identify the related OpenDrive object
*
*/
class OSGGeodeNode: public osg::Geode, public OSGObjectNode
{
public:
	/**
	* Constructors and ssignment operators
	*/
	OSGGeodeNode();
	OSGGeodeNode( const OSGGeodeNode& objectNode,  const osg::CopyOp &copyop=osg::CopyOp::SHALLOW_COPY);
	OSGGeodeNode& operator=(OSGGeodeNode const& rhs);
};


/**
* Additional Object Node class that inherits OpenSceneGraph billboard class
* Inherits osg::Geode
* Contains data used to identify the related OpenDrive object
*
*/
class OSGBillboardNode: public osg::Billboard, public OSGObjectNode
{
public:
	/**
	* Constructors and ssignment operators
	*/
	OSGBillboardNode();
	OSGBillboardNode( const OSGBillboardNode& objectNode,  const osg::CopyOp &copyop=osg::CopyOp::SHALLOW_COPY);
	OSGBillboardNode& operator=(OSGBillboardNode const& rhs);
};




#endif
