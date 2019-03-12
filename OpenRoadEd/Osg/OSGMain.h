#ifndef OSGMAIN_H
#define OSGMAIN_H


#include <osg/Version>
#include <osgDB/ReadFile>
#include <osgDB/WriteFile>
#include <osg/Node>
#include <osgViewer/Viewer>
#include <osgViewer/GraphicsWindow>
#include <osgViewer/ViewerEventHandlers>
#include <osgViewer/api/Win32/GraphicsWindowWin32>

#include <osgGA/TrackballManipulator>
#include <osgGA/FlightManipulator>
#include <osgGA/DriveManipulator>
#include <osgGA/KeySwitchMatrixManipulator>
#include <osgGA/StateSetManipulator>
#include <osgGA/AnimationPathManipulator>
#include <osgGA/TerrainManipulator>


typedef osgViewer::GraphicsWindowWin32::WindowData WindowData;


#include "../OpenDrive/OpenDrive.h"
#include "OSGRoad.h"
#include "OSGScenery.h"
#include "OSGJunction.h"
#include "OSGRecordsHelpers.h"

#include <QtGui/QtGui>

class OSGScreenshotRequest;


/**
* Main Geometry generation class
* It uses OpenDrive structure to generate OpenSceneGraph geometry
*
*
*
*/
class OSGMain
{

private:
	// OSG Viewer
	osg::ref_ptr<osgViewer::Viewer> mViewer;
	// Window
	osg::ref_ptr<osgViewer::GraphicsWindow> mGw;
	// OpenDrive reference
	OpenDrive* mOpenDrive;
	//Root OSG Node
public:
	osg::ref_ptr<osg::Group> mRootGroup;

	//Road Group
	osg::ref_ptr<osg::Group> mRoadsGroup;
	osg::ref_ptr<osg::Group> mRoadChordLineGroup;
	osg::ref_ptr<osg::Group> mJunctionsGroup;
	//Scenery Group
	osg::ref_ptr<osg::Group> mSceneryGroup;
	//Record Helpers Group
	osg::ref_ptr<osg::Group> mRecordsHelpersGroup;
	//Helper Group
	osg::ref_ptr<osg::Group> mHelpersGroup;
	//Helpers Group
	osg::ref_ptr<osg::Group> mGridGroup;


	//Class with methods for road drawing
	OSGRoad* mOsgRoad;
	//Class with methods for junction drawing
	OSGJunction* mOsgJunction;
	//Class with methods for scenery drawing
	OSGScenery* mOsgScenery;
	//Class with methods for record helpers drawing
	OSGRecordsHelpers* mOsgRecordHelpers;

	//Class with methods needed to take the screenshots
	osg::ref_ptr<OSGScreenshotRequest> mScreenshotRequest;


	//Selection
	OSGObjectNode mCurrentlySelected;
	osg::Geometry::AttributeBinding mCurrentlySelectedBinding;


private:
	/**
	*
	*/
	void createContext(int x, int y, int widht, int height, HWND window);

public:
	//--------------
	//Init
	//--------------

	/**
	* Constructor.
	* @param openDriveIn A pointer to the OpenDrive structure
	*/
	OSGMain(OpenDrive* openDriveIn);
	/**
	* Initialize the viewer
	* @param x,y Position of the viewer
	* @param width,height Dimensions of the viewer
	* @param window Window handler
	*/
	void initViewer(int x, int y, int width, int height, HWND window);

	/**
	* Load a mode
	* @param filename A path to a file supported by OpenSceneGraph
	*/
	void loadModel(const std::string &filename);

	/**
	* Draw/redraw the frame
	*/
	void frame();

	/**
	* Show or hide the chord line helper
	*/
	void ShowChordLine(bool show);

	/**
	* Show or hide the grid or the reference plane
	*/
	void ShowGridOrRefPlane(bool show);

	/**
	* Show or hide the arrows showing the road direction
	*/
	void ShowArrows(bool show);

	/**
	* Show or hide the scenery
	*/
	void ShowScenery(bool show);

	/**
	* Show or hide the records helpers
	*/
	void ShowRecordsHelpers(bool show);



	/**
	* Get pointer to Viewer
	*/
	osg::ref_ptr<osgViewer::Viewer> GetViewer();



	/**
	* Draw the chord line helper
	*/
	void DrawRoadChordLine();

	/**
	* Redraw the chord line helper
	*/
	void RedrawRoadChordLine(unsigned int roadIndexToRedraw);

	/**
	* Draw all the roads
	*/
	void DrawRoads();

	/**
	* Redraw a road at the provided index in the vector
	*/
	void RedrawRoad(unsigned int roadIndexToRedraw);

	/**
	* Draw all the junctions
	*/
	void DrawJunctions();

	/**
	* Draw the scenery. The size of the landscape is calculated automatically, based on the road network bounding box
	* @param heightMapFile The heightmap texture filename
	* @param terrainFile The terrain texture filename
	* @param resX, resY Number of collumns and rows
	* @param heightMultiplier Used to scale the normalized height values read from the heightmap
	* @param averageElevation Used to shift the landscape vertically according to the road, if needed.
	*/
	void DrawScenery(std::string heightMapFile, std::string terrainFile, double resX, double resY, double heightMultiplier, double averageElevation);

	/**
	* Draw the scenery. 
	* @param heightMapFile The heightmap texture filename
	* @param terrainFile The terrain texture filename
	* @param north, south, east, west The bounds of the terrain to be generated
	* @param resX, resY Number of collumns and rows
	* @param heightMultiplier Used to scale the normalized height values read from the heightmap
	* @param averageElevation Used to shift the landscape vertically according to the road, if needed.
	*/
	void DrawScenery(std::string heightMapFile, std::string terrainFile, double north, double south, double east, double west, double resX, double resY, double heightMultiplier, double averageElevation);

	/**
	* Create a light to lit the scene
	*/
	void AddLight();

	/**
	* Create a helper grid based on the road network bounding box
	*/
	void DrawGrid();

	/**
	* Create a helper grid providing all the dimensions and the resolution
	*/
	void DrawGrid(double xMin, double xMax, int numCollumns, double yMin,double yMax, int numRows);

	/**
	* Create a reference plane
	* @param xMin, xMax, yMin, yMax Size and position of the plane
	* @param filename The name of the texture to be applied to the reference plane
	*/
	void DrawReferencePlane(double xMin, double xMax, double yMin,double yMax, std::string filename);

	/**
	* Create all the records helpers for all the roads
	*/
	void DrawRecordHelpers();

	/**
	* Create a screenshot. The output is created in the "Screenshots" folder in the working directory
	*/
	void TakeScreenshot ();

	/**
	* Pick a 3D object from the viewport
	* @param x, y coordinates of the cursor at which to pick the objects 
	*/
	OSGObjectNode* OSGMain::PickNode(float x, float y);

	/**
	* Depending on the node type and the hierarchycal index array, find it in the structure
	* @param objToSelect Object to be selected
	* @return A pointer to the helper geode is returned, which contains the picked object
	*/
	OSGGeodeNode*  FindNode(OSGObjectNode* objToSelect);

	/**
	* Change the color of the selected object, to visually represent the selection
	* @param objToSelect Object to be selected
	*/
	void MakeSelection(OSGObjectNode* objToSelect);

	/**
	* Clear the selection
	*/
	void ClearSelection(bool objDeleted=false);


	/**
	* Export all the useful geometry to a file
	* @param fileName Filename of the file to be created
	*/
	void SaveGeometry(std::string fileName);


	/**
	* Delete road geometry from the roads group
	* @param roadToRemove Index of the road to be removed
	*/
	void DeleteRoad(unsigned int roadToRemove);

	/**
	* Delete junction geometry from the junctions group
	* @param junctionToRemove Index of the junction to be removed
	*/
	void DeleteJunction(unsigned int junctionToRemove);

	/**
	* Clear everything geometry related. 
	*/
	void Clear();
};


/**
* OSG classes needed to take the screenshot, that can be used to generate the heightmap and terrain map
* It uses OpenDrive structure to generate OpenSceneGraph geometry
*
*
*
*/
class OSGScreenshotRequest : public osg::Referenced
{
private:
	bool mTakeScreenshotFlag;
	int mHeight;
	int mWidth;

public:
	/**
	* Constructor
	*/
	OSGScreenshotRequest()
	{	mTakeScreenshotFlag = false;	}

	/**
	* Set Dimensions of the screenshot
	*/
	void SetDimensions (int width, int height)
	{	mWidth=width; mHeight=height; 	}

	/**
	* Set the flag
	*/
	void SetTakeScreenshotFlag(bool value)
	{	mTakeScreenshotFlag=value;	}

	/**
	* Getters 
	*/
	int GetHeight ()
	{	return mHeight;	}
	int GetWidth ()
	{	return mWidth;	}
	bool GetTakeScreenshotFlag()
	{	return mTakeScreenshotFlag;	}

	/**
	* Take a screenshot
	* @param width,height Dimensions of the screenshot to take
	*/
	void TakeScreenshot (int width, int height )
	{	mWidth=width; mHeight=height; mTakeScreenshotFlag=true; 	}
};

class OSGCameraPostDrawCallback : public osg::Camera::DrawCallback
{
private:
	osg::ref_ptr<OSGScreenshotRequest> mScreenshotRequest;

public:
	/**
	* A callback used to take the screenshot
	*/
	OSGCameraPostDrawCallback( OSGScreenshotRequest* pScreenShotRequest )
	{
		mScreenshotRequest = pScreenShotRequest;
	}

	void operator () ( const osg::Camera& cam ) const 
	{
		// has there been requested a screenshot?
		if ( mScreenshotRequest->GetTakeScreenshotFlag() )
		{
			// save render buffer to file
			osg::ref_ptr<osg::Image> scrImage = new osg::Image;
			scrImage->readPixels( 0, 0, mScreenshotRequest->GetWidth(), mScreenshotRequest->GetHeight(), GL_RGB, GL_UNSIGNED_BYTE );
			osgDB::writeImageFile( *scrImage, "ScreenShots/Screenshot.jpg" );

			// done, reset request
			mScreenshotRequest->SetTakeScreenshotFlag(false);
		}
	}

};


#endif
