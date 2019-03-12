#include "OSGObjectNode.h"
#include <osg/Material>
#include <osg/MatrixTransform>
#include <osg/Geometry>


/**
* A helper class
* It stores information about the records and thus it is used to link the OpenSceneGraph objects with the OpenDRIVE entities stored in the tree structure
*
*
*
*/

/**
* Constructor
*/
OSGObjectNode::OSGObjectNode()
{}

/**
* Copy constructor
*/
OSGObjectNode::OSGObjectNode(const OSGObjectNode& nodeInfo)
{
	mNodeType=nodeInfo.mNodeType;
	mIndices=nodeInfo.mIndices;
}

/**
* Assignment operator
*/
OSGObjectNode& OSGObjectNode::operator=(OSGObjectNode const& rhs)
{
	if(this != &rhs)
	{
		mNodeType=rhs.mNodeType;
		mIndices=rhs.mIndices;
	}
	return *this;
}

/**
* Set the type of the node
*/
void OSGObjectNode::SetNodeType(OSGNodeType nodeType)
{
	mNodeType=nodeType;
}

/**
* Add an index to the index vector
*/
void  OSGObjectNode::AddNodeInfoIndex(int index)
{
	mIndices.push_back(index);
}

/**
* Get the type of the node
*/
OSGNodeType OSGObjectNode::GetNodeType()
{
	return mNodeType;
}

/**
* Get the index at a certain position
*/
int OSGObjectNode::GetNodeInfoIndex(int index)
{
	return mIndices[index];
}

/**
* Clear the index array
*/
void OSGObjectNode::ClearNodeInfoIndices()
{
	mIndices.clear();
}

/**
* Check if the index vector is empty
*/
bool OSGObjectNode::IsEmpty()
{
	if (mIndices.size()>0)
		return false;
	else 
		return true;
}

/**
* Additional Object Node class that inherits OpenSceneGraph geode class
* Inherits osg::Geode
* Contains data used to identify the related OpenDrive object
*
*/

/**
* Constructors and ssignment operators
*/
OSGGeodeNode::OSGGeodeNode()
{}
OSGGeodeNode::OSGGeodeNode( const OSGGeodeNode& objectNode,  const osg::CopyOp &copyop):Geode(objectNode,copyop),OSGObjectNode(objectNode)
{
}
OSGGeodeNode& OSGGeodeNode::operator=(OSGGeodeNode const& rhs)
{
	if(this != &rhs)
	{
		osg::Referenced::operator=(rhs);
		OSGObjectNode::operator =(rhs);
	}
	return *this;
}

/**
* Additional Object Node class that inherits OpenSceneGraph billboard class
* Inherits osg::Geode
* Contains data used to identify the related OpenDrive object
*
*/

/**
* Constructors and ssignment operators
*/
OSGBillboardNode::OSGBillboardNode()
{}
OSGBillboardNode::OSGBillboardNode( const OSGBillboardNode& objectNode,  const osg::CopyOp &copyop):Billboard(objectNode,copyop),OSGObjectNode(objectNode)
{
}
OSGBillboardNode& OSGBillboardNode::operator=(OSGBillboardNode const& rhs)
{
	if(this != &rhs)
	{
		osg::Referenced::operator=(rhs);
		OSGObjectNode::operator =(rhs);
	}
	return *this;
}
