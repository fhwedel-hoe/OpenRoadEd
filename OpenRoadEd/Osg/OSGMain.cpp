#include <sstream>		//debug (convert double to string)
//#include "windows.h"	//debug (OutputDebugString)


#include <iostream>
#include <osg/Timer>
#include <osg/Point>
#include <osg/Light>
#include <osg/LightSource>
#include <osg/Texture2D>
#include <osg/Material>
#include <osg/MatrixTransform>
#include <osg/Notify>

#include <osgQt/GraphicsWindowQt>

#include "OSGMain.h"
#include "OSGCameraControls.h"
#include "OSGCameraControls2.h"
#include <osgGA/KeySwitchMatrixManipulator>

#include "OSGConstants.h"

using std::ifstream;
using std::ofstream;
using std::endl;
using std::cout;





#include <osgViewer/api/X11/GraphicsWindowX11>




/**
* Main Geometry generation class
* It uses OpenDrive structure to generate OpenSceneGraph geometry
*
*
*
*/

/**
* Constructor.
* @param openDriveIn A pointer to the OpenDrive structure
*/
OSGMain::OSGMain(OpenDrive* openDrive)
{
	mOpenDrive=openDrive;

	//create objects used to generate various geometry objects:
	//Road geometry
	mOsgRoad=new OSGRoad();
	//Junction geometry
	mOsgJunction=new OSGJunction;
	//Geometry for the scenery
	mOsgScenery=new OSGScenery();
	//Records helpers
	mOsgRecordHelpers=new OSGRecordsHelpers;


	//OpenSceneGraph groups with all the graphical data
	mRootGroup=new osg::Group;
	//Road Group
	mRoadsGroup=new osg::Group;
	//Road Group
	//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
	mRoadChordLineGroup=new osg::Group;
	//Junction Group
	mJunctionsGroup=new osg::Group;
	//Scenery Group
	mSceneryGroup=new osg::Group;
	//Road Helpers Group
	mRecordsHelpersGroup = new osg::Group;
	//Helpers Group
	mHelpersGroup=new osg::Group;
	//Grid Group
	mGridGroup=new osg::Group;

	//Add everything to root
	mRootGroup->addChild(mRoadChordLineGroup);
	mRootGroup->addChild(mRoadsGroup);
	mRootGroup->addChild(mJunctionsGroup);
	mRootGroup->addChild(mSceneryGroup);
	mRootGroup->addChild(mRecordsHelpersGroup);
	mRootGroup->addChild(mHelpersGroup);
	mRootGroup->addChild(mGridGroup);

	//Object used to take screenshots
	mScreenshotRequest = new OSGScreenshotRequest;

	//initialize node info objects
	mCurrentlySelected.ClearNodeInfoIndices();
}

/**
* Initialize the viewer
* @param x,y Position of the viewer
* @param width,height Dimensions of the viewer
* @param window Window handler
*/
void OSGMain::initViewer(int x, int y, int width, int height, const QWidget * parent)
{
	mViewer = new osgViewer::Viewer;
	mViewer->setKeyEventSetsDone(0);

	createContext(x,y,width,height,parent);

	//std::cerr << "x: " << x << " y: " << y << " w: " << width << " h: " << height << std::endl;

	//mViewer->setThreadingModel(osgViewer::Viewer::SingleThreaded);

	//********************************  CAMERA
	mViewer->getCamera()->setViewport(new osg::Viewport(0,0,width,height));
	mViewer->getCamera()->setProjectionMatrixAsPerspective(30.0f, static_cast<double>(width)/static_cast<double>(height), 1.0f, 10000.0f);
	mViewer->getCamera()->setGraphicsContext(mGw.get());
	mViewer->getCamera()->setClearColor( osg::Vec4( 0.30, 0.36, 0.40, 1. ) );

	//set the callback used to take the screenshot
	mViewer->getCamera()->setPostDrawCallback(new OSGCameraPostDrawCallback(mScreenshotRequest.get() ));


	//******************************** MANIPULATORS
	// set up the camera manipulators.
	{
		osg::ref_ptr<osgGA::KeySwitchMatrixManipulator> keyswitchManipulator = new osgGA::KeySwitchMatrixManipulator;

		keyswitchManipulator->addMatrixManipulator( '6', "Own2", new OSGCameraControls2());
		//keyswitchManipulator->addMatrixManipulator( '1', "Trackball", new osgGA::TrackballManipulator() );
		//keyswitchManipulator->addMatrixManipulator( '2', "Flight", new osgGA::FlightManipulator() );
		//keyswitchManipulator->addMatrixManipulator( '3', "Drive", new osgGA::DriveManipulator() );
		//keyswitchManipulator->addMatrixManipulator( '4', "Terrain", new osgGA::TerrainManipulator() );
		//keyswitchManipulator->addMatrixManipulator( '5', "Own", new OSGCameraControls());


		mViewer->setCameraManipulator( keyswitchManipulator.get() );
	}
	// LIGHTING, ETC.
	// add the state manipulator
	mViewer->addEventHandler( new osgGA::StateSetManipulator(mViewer->getCamera()->getOrCreateStateSet()) );
	// THREADING
	// add the thread model handler
	mViewer->addEventHandler(new osgViewer::ThreadingHandler);
	// FULL SCREEN BUTTON
	// add the window size toggle handler
	//mViewer->addEventHandler(new osgViewer::WindowSizeHandler);
	// add the stats handler
	mViewer->addEventHandler(new osgViewer::StatsHandler);
	// HELP
	// add the help handler
	//mViewer->addEventHandler(new osgViewer::HelpHandler(arguments.getApplicationUsage()));
	//mViewer->addEventHandler(new osgViewer::HelpHandler);


	//Draw the grid
	DrawGrid(MIN_GRID_X,MAX_GRID_X,GRID_COLLUMNS,MIN_GRID_Y,MAX_GRID_Y,GRID_ROWS);

	//Set light
	AddLight();

	//Add root to the viewer
	mViewer->setSceneData(mRootGroup.get());

	// lala
	mViewer->getCameraManipulator()->setNode(mRoadsGroup);
}

void OSGMain::setViewerRectangle(int x, int y, int width, int height)
{
    mGw->setWindowRectangle(x,y,width,height);
}

/**
* Load a mode
* @param filename A path to a file supported by OpenSceneGraph
*/
void OSGMain::loadModel(const std::string &filename)
{
	//read the model file
	osg::ref_ptr<osg::Node> loadedModel = osgDB::readNodeFile(filename);

	//add it to the group
	mRootGroup.get()->removeChildren(0, mRootGroup->getNumChildren());
	mRootGroup.get()->addChild(loadedModel.get());
}

/**
* Draw/redraw the frame
*/
void OSGMain::frame()
{
	mViewer->frame();
}


/**
* Creates the window context
*/
void OSGMain::createContext(int x, int y, int width, int height, const QWidget * parent)
{
	// Sets the properties of the window and prepares it for renderin

	osg::DisplaySettings* ds = osg::DisplaySettings::instance();

	osg::ref_ptr<osg::GraphicsContext::Traits> traits = new osg::GraphicsContext::Traits;

	traits->readDISPLAY();
	if (traits->displayNum<0) traits->displayNum = 0;

	traits->windowName = "osgViewerQt";
	traits->screenNum = 0;
	traits->x = x;
	traits->y = y;
	traits->width = width;
	traits->height = height;
	traits->alpha = ds->getMinimumNumAlphaBits();
	traits->stencil = ds->getMinimumNumStencilBits();
	traits->windowDecoration = false;
	traits->doubleBuffer = true;
	traits->sharedContext = 0;
	traits->sampleBuffers = ds->getMultiSamples();
	traits->samples = ds->getNumMultiSamples();

	traits->supportsResize = true;
	//traits->inheritedWindowData = new WindowData(winId());
	//traits->inheritedWindowData = new osgQt::GraphicsWindowQt::WindowData(parent); //new WindowData(window);

        osgViewer::GraphicsWindowX11::WindowData* data = new osgViewer::GraphicsWindowX11::WindowData((Window)parent->winId());
        traits->inheritedWindowData = data;
	if (ds->getStereo())
	{
		switch(ds->getStereoMode())
		{
		case(osg::DisplaySettings::QUAD_BUFFER): traits->quadBufferStereo = true; break;
		case(osg::DisplaySettings::VERTICAL_INTERLACE):
		case(osg::DisplaySettings::CHECKERBOARD):
		case(osg::DisplaySettings::HORIZONTAL_INTERLACE): traits->stencil = 8; break;
		default: break;
		}
	}

	osg::ref_ptr<osg::GraphicsContext> gc = osg::GraphicsContext::createGraphicsContext(traits.get());
	mGw = dynamic_cast<osgViewer::GraphicsWindow*>(gc.get());
}

/**
* Show or hide the chord line helper
*/
void OSGMain::ShowChordLine(bool show)
{
	mRoadChordLineGroup->setNodeMask(show);
} 

/**
* Show or hide the grid or the reference plane
*/
void  OSGMain::ShowGridOrRefPlane(bool show)
{
	mGridGroup->setNodeMask(show);
}

/**
* Show or hide the arrows showing the road direction
*/
void  OSGMain::ShowArrows(bool show)
{
	mHelpersGroup->setNodeMask(show);
}

/**
* Show or hide the scenery
*/
void OSGMain::ShowScenery(bool show)
{
	mSceneryGroup->setNodeMask(show);
}

/**
* Show or hide the records helpers
*/
void OSGMain::ShowRecordsHelpers(bool show)
{
	mRecordsHelpersGroup->setNodeMask(show);
}

/**
* Get pointer to Viewer
*/
osg::ref_ptr<osgViewer::Viewer> OSGMain::GetViewer()
{
	return mViewer;
}


/**
* Draw the chord line helper
*/
void OSGMain::DrawRoadChordLine()
{
	//start Timer for statistics
	osg::Timer_t startTick = osg::Timer::instance()->tick();

	//for all the roads
	for (unsigned int i=0; i<mOpenDrive->GetRoadCount(); i++)
	{
		//generate a chord line
		mRoadChordLineGroup->addChild(mOsgRoad->DrawChordLine(mOpenDrive->GetRoad(i), CHORDLINE_STEP));
	}

	//STATISTICS
	//*******************
	//return statistics
	std::ostringstream ss; 	std::string str;
	osg::Timer_t endTick = osg::Timer::instance()->tick();
	ss<<"Road ChordLine generation completed in "<<osg::Timer::instance()->delta_s(startTick,endTick)<<std::endl;
	str.append(ss.str());
	//Output to the debug window
    //OutputDebugString( "\n" ) ;
    //OutputDebugString( str.c_str() ) ;
    //OutputDebugString( "\n" ) ;
}


/**
* Redraw the chord line helper
*/
void OSGMain::RedrawRoadChordLine(unsigned int roadIndexToRedraw)
{
	//check if the road exists
	if (roadIndexToRedraw < mOpenDrive->GetRoadCount())
	{

		osg::Geode* geode;
		//either create a new object
		if (roadIndexToRedraw>=mRoadChordLineGroup->getNumChildren())
		{
			geode = new osg::Geode;
			mRoadChordLineGroup->addChild(geode);
		}
		else	//or clear the old geode
		{
			geode = mRoadChordLineGroup->getChild(roadIndexToRedraw)->asGeode();
			geode->removeDrawables(0);
		}

		//add the geometry to the geode
		geode->addDrawable(mOsgRoad->RedrawChordLine(mOpenDrive->GetRoad(roadIndexToRedraw), CHORDLINE_STEP).get());
	}
}


/**
* Draw all the roads
*/
void OSGMain::DrawRoads()
{
	//start Timer for statistics
	osg::Timer_t startTick = osg::Timer::instance()->tick();

	for (unsigned int i=0; i<mOpenDrive->GetRoadCount(); i++)
	{
		//if the road is a road, not a junction path
		if (mOpenDrive->GetRoad(i)->GetRoadJunction().compare("-1")==0)
		{
			//draw it
			mRoadsGroup->addChild(mOsgRoad->DrawRoad(mOpenDrive->GetRoad(i),i,ROAD_STEP, mOsgScenery->GetRoadConstraintVerticesVector(),"Resources/asphaltAlpha.tga",true,"Resources/roadMarks.tga", 0));
			mHelpersGroup->addChild(mOsgRoad->DrawDirectionArrow(mOpenDrive->GetRoad(i)));

		}
		else
		{
			//else add just the tracks with alpha channel
			mRoadsGroup->addChild(mOsgRoad->DrawRoad(mOpenDrive->GetRoad(i),i,JUNCTION_STEP, mOsgScenery->GetRoadConstraintVerticesVector(),"Resources/asphaltClear.jpg",false,"Resources/roadMarks.tga", 2));
			mHelpersGroup->addChild(mOsgRoad->DrawDirectionArrow(mOpenDrive->GetRoad(i)));
		}

		//Add records helpers
		mOsgRecordHelpers->FillHelperGroups(mOpenDrive->GetRoad(i),i,mRecordsHelpersGroup);

		//Set the recalculate flag to true, so the scenery has to recalculate the mask vertices
		mOsgScenery->SetRecalc(i,true);
	}

	//STATISTICS
	//*******************
	//return statistics
	std::ostringstream ss; 	std::string str;
	osg::Timer_t endTick = osg::Timer::instance()->tick();
	ss<<"Road generation completed in "<<osg::Timer::instance()->delta_s(startTick,endTick)<<std::endl;
	str.append(ss.str());
	//Output to the debug window
    //OutputDebugString( "\n" ) ;
    //OutputDebugString( str.c_str() ) ;
    //OutputDebugString( "\n" ) ;
}


/**
* Redraw a road at the provided index in the vector
*/
void OSGMain::RedrawRoad(unsigned int roadIndexToRedraw)
{
	//check if the requested road exists
	if (roadIndexToRedraw < mOpenDrive->GetRoadCount())
	{
		//redraw its chord line
		RedrawRoadChordLine(roadIndexToRedraw);

		// if there is no such road, create it
		OSGGeodeNode* geode;
		osg::MatrixTransform* matrix;
		if (roadIndexToRedraw>=mRoadsGroup->getNumChildren())
		{
			geode = new OSGGeodeNode;
			geode->SetNodeType(ROAD_NODE);
			mRoadsGroup->addChild(geode);

			matrix=new osg::MatrixTransform;
			mHelpersGroup->addChild(matrix);
		}
		else
		{	//otherwise clear the geode
			geode = static_cast<OSGGeodeNode*> (mRoadsGroup->getChild(roadIndexToRedraw));
			geode->removeDrawables(0,geode->getNumDrawables());

			matrix=static_cast<osg::MatrixTransform*>(mHelpersGroup->getChild(roadIndexToRedraw)->asTransform());

		}

		vector<osg::ref_ptr<osg::Geometry>> roadGeoms;

		//check if the road is not a junction path and assign a texture accordingly
		//draw the helper arrow as well
		if (mOpenDrive->GetRoad(roadIndexToRedraw)->GetRoadJunction().compare("-1")==0)
		{
			mOsgRoad->RedrawRoad(roadGeoms,mOpenDrive->GetRoad(roadIndexToRedraw),roadIndexToRedraw,ROAD_STEP,mOsgScenery->GetRoadConstraintVerticesVector(),"Resources/asphaltAlpha.tga",true,"Resources/roadMarks.tga", 0) ;

			mOsgRoad->RedrawDirectionArrow(matrix, mOpenDrive->GetRoad(roadIndexToRedraw));
		}
		else
		{
			mOsgRoad->RedrawRoad(roadGeoms,mOpenDrive->GetRoad(roadIndexToRedraw),roadIndexToRedraw,ROAD_STEP,mOsgScenery->GetRoadConstraintVerticesVector(),"Resources/asphaltClear.jpg",false,"Resources/roadMarks.tga", 2) ;

			mOsgRoad->RedrawDirectionArrow(matrix, mOpenDrive->GetRoad(roadIndexToRedraw));
		}

		//add the road and the road marks to the geode
		for (unsigned int i=0; i<roadGeoms.size();i++)
		{
			geode->addDrawable(roadGeoms.at(i));
		}

		//flag the road's mask as outdated
		mOsgScenery->SetRecalc(roadIndexToRedraw,true);

		//Add records helpers
		mOsgRecordHelpers->FillHelperGroups(mOpenDrive->GetRoad(roadIndexToRedraw),roadIndexToRedraw,mRecordsHelpersGroup);
	}
}


/**
* Draw all the junctions
*/
void OSGMain::DrawJunctions()
{

	//start Timer for statistics
	osg::Timer_t startTick = osg::Timer::instance()->tick();

	//Go through all the junctions
	for (unsigned int j=0; j<mOpenDrive->GetJunctionCount(); j++)
	{
		//draw the junction plane
		mJunctionsGroup->addChild(mOsgJunction->DrawJunction(mOpenDrive->GetRoadVector(),j,mOpenDrive->GetJunction(j)->GetId(), mRoadsGroup,"Resources/asphaltAlpha.tga" ));
	}

	//STATISTICS
	//*******************
	//return statistics
	std::ostringstream ss; 	std::string str;
	osg::Timer_t endTick = osg::Timer::instance()->tick();
	ss<<"Junction generation completed in "<<osg::Timer::instance()->delta_s(startTick,endTick)<<std::endl;
	str.append(ss.str());
	//Output to the debug window
    //OutputDebugString( "\n" ) ;
    //OutputDebugString( str.c_str() ) ;
    //OutputDebugString( "\n" ) ;
}

/**
* Draw the scenery. The size of the landscape is calculated automatically, based on the road network bounding box
* @param heightMapFile The heightmap texture filename
* @param terrainFile The terrain texture filename
* @param resX, resY Number of collumns and rows
* @param heightMultiplier Used to scale the normalized height values read from the heightmap
* @param averageElevation Used to shift the landscape vertically according to the road, if needed.
*/
void OSGMain::DrawScenery(std::string heightMapFile, std::string terrainFile, double resX, double resY, double heightMultiplier, double averageElevation)
{
	//compute the road network bounding box
	osg::BoundingBox* bbox=new osg::BoundingBox; 
	bbox->expandBy( mRoadsGroup->getBound() );

	//use the bbox size to compute the scenery
	DrawScenery(heightMapFile,terrainFile,bbox->yMax(),bbox->yMin(),bbox->xMax(),bbox->xMin(),resX,resY,heightMultiplier,averageElevation);

}


/**
* Draw the scenery. 
* @param heightMapFile The heightmap texture filename
* @param terrainFile The terrain texture filename
* @param north, south, east, west The bounds of the terrain to be generated
* @param resX, resY Number of collumns and rows
* @param heightMultiplier Used to scale the normalized height values read from the heightmap
* @param averageElevation Used to shift the landscape vertically according to the road, if needed.
*/
void OSGMain::DrawScenery(std::string heightMapFile, std::string terrainFile, double north, double south, double east, double west, double resX, double resY, double heightMultiplier, double averageElevation)
{

	if (mOsgScenery->GetRoadConstraintVerticesVector().size()<=0)
		return;

	//clear the previous heightfield
	mOsgScenery->ClearHeightField();
	mSceneryGroup->removeChildren(0,mSceneryGroup->getNumChildren());

	//Send it to the scenery object
	mOsgScenery->SetData(north,south,east,west);

	//start Timer for statistics
	osg::Timer_t startTick = osg::Timer::instance()->tick();

	//-----------------------
	mOsgScenery->GenerateHeightField(heightMapFile,resX,resY,heightMultiplier,averageElevation);
	//-----------------------

	//STATISTICS
	//*******************
	//return statistics
	std::ostringstream ss; 	std::string str;
	osg::Timer_t endTick = osg::Timer::instance()->tick();
	ss<<"HeightMap generation completed in "<<osg::Timer::instance()->delta_s(startTick,endTick)<<std::endl;
	str.append(ss.str());
	//Output to the debug window
    //OutputDebugString( "\n" ) ;
    //OutputDebugString( str.c_str() ) ;
    //OutputDebugString( "\n" ) ;

	/////////////////////////////////////////////////////////////////////////////////////
	//start Timer for statistics
	startTick = osg::Timer::instance()->tick();

	//-----------------------
	//blend the road into the heightmap and draw it
	mSceneryGroup->addChild(mOsgScenery->DrawScenery(heightMapFile,terrainFile));

	//draw just the heightmap
	//mScenery->addChild(mOsgScenery->GetHeightMap());
	//-----------------------

	//STATISTICS
	//*******************
	//return statistics
	std::ostringstream ss2; 	std::string str2;
	endTick = osg::Timer::instance()->tick();
	ss2<<"Scenery generation completed in "<<osg::Timer::instance()->delta_s(startTick,endTick)<<std::endl;
	str2.append(ss2.str());
	//Output to the debug window
    //OutputDebugString( "\n" ) ;
    //OutputDebugString( str2.c_str() ) ;
    //OutputDebugString( "\n" ) ;
}

/**
* Create a helper grid based on the road network bounding box
*/
void  OSGMain::DrawGrid()
{
	//compute the bounding box
	osg::BoundingBox* bbox=new osg::BoundingBox; 
	bbox->expandBy(mRoadsGroup->getBound());
	double xMin,xMax,yMin,yMax;
	xMin=bbox->xMin();
	xMax= bbox->xMax();
	yMin= bbox->yMin();
	yMax=bbox->yMax();

	//raw definition of the resolution based on the grid size
	int numColls = fabs(xMax-xMin);
	int numRows = fabs(yMax-yMin);
	if (numColls>999)
		numColls/=100;
	else
		if (numColls>99)
			numColls/=10;

	if (numRows>999)
		numRows/=100;
	else
		if (numRows>99)
			numRows/=10;

	//create the grid
	DrawGrid(xMin, xMax, numColls, yMin,yMax, numRows);
}

/**
* Create a helper grid providing all the dimensions and the resolution
*/
void  OSGMain::DrawGrid(double xMin, double xMax, int numCollumns, double yMin,double yMax, int numRows)
{

	mGridGroup->removeChildren(0,mGridGroup->getNumChildren());
	//Create geometry
	osg::ref_ptr<osg::Geode> geode = new osg::Geode();
	osg::ref_ptr<osg::Geometry> geometry = new osg::Geometry();
	//arrays for vertices
	osg::ref_ptr<osg::Vec3Array> vertices = new osg::Vec3Array;
	geometry->setVertexArray( vertices.get() );
	//array  for colors
	osg::ref_ptr<osg::Vec4Array> colors = new osg::Vec4Array;
	colors->push_back(osg::Vec4(0.6f, 0.6f, 0.6f, 1.0f) );	
	geometry->setColorArray(colors.get());
	geometry->setColorBinding(osg::Geometry::BIND_OVERALL);

	double step=fabs(xMax-xMin)/numCollumns;
	//create vertices
	for (double s=xMin;s<=xMax; s+=step)
	{
		vertices->push_back(osg::Vec3(s,yMin,-1));
		vertices->push_back(osg::Vec3(s,yMax,-1));
	}

	step=fabs(yMax-yMin)/numRows;
	for (double s=yMin;s<=yMax; s+=step)
	{
		vertices->push_back(osg::Vec3(xMin,s,-1));
		vertices->push_back(osg::Vec3(xMax,s,-1));

	}

	//lines
	osg::ref_ptr<osg::DrawArrays> lines = new osg::DrawArrays(osg::PrimitiveSet::LINES, 0, vertices.get()->size());
	geometry->addPrimitiveSet(lines.get());	
	geometry->getOrCreateStateSet()->setMode(GL_LIGHTING, osg::StateAttribute::OFF);
	geometry->getOrCreateStateSet()->setAttribute( new osg::Point( 2.0f ),osg::StateAttribute::ON );

	geode->addDrawable(geometry.get());
	mGridGroup->addChild(geode);
}



/**
* Create a reference plane
* @param xMin, xMax, yMin, yMax Size and position of the plane
* @param filename The name of the texture to be applied to the reference plane
*/
void  OSGMain::DrawReferencePlane(double xMin, double xMax, double yMin,double yMax, std::string filename)
{
	//clear the grid group
	mGridGroup->removeChildren(0,mGridGroup->getNumChildren());
	//Create geometry
	osg::ref_ptr<osg::Geode> geode = new osg::Geode();
	osg::ref_ptr<osg::Geometry> geometry = new osg::Geometry();
	//arrays for vertices
	osg::ref_ptr<osg::Vec3Array> vertices = new osg::Vec3Array;
	geometry->setVertexArray( vertices.get() );
	osg::ref_ptr<osg::Vec2Array> texCoords = new osg::Vec2Array;
	geometry->setTexCoordArray( 0, texCoords.get() );
	osg::ref_ptr<osg::Vec4Array> colors = new osg::Vec4Array;
	colors->push_back(osg::Vec4(1,1,1,1));
	geometry->setColorArray( colors.get() );
	geometry->setColorBinding(osg::Geometry::BIND_OVERALL);

	//create a quad
	vertices->push_back(osg::Vec3(xMin,yMin,-1));
	texCoords->push_back(osg::Vec2(0,0));
	vertices->push_back(osg::Vec3(xMax,yMin,-1));
	texCoords->push_back(osg::Vec2(1,0));
	vertices->push_back(osg::Vec3(xMax,yMax,-1));
	texCoords->push_back(osg::Vec2(1,1));
	vertices->push_back(osg::Vec3(xMin,yMax,-1));
	texCoords->push_back(osg::Vec2(0,1));


	//use quads
	osg::ref_ptr<osg::DrawArrays> quad = new osg::DrawArrays(osg::PrimitiveSet::QUADS, 0, vertices.get()->size());
	geometry->addPrimitiveSet(quad.get());	

	//create a material
	osg::ref_ptr<osg::Material> material = new osg::Material; 
	material->setEmission(osg::Material::FRONT, osg::Vec4(.8,0.8,0.8,1.));

	// load image for texture
	osg::Image *image = osgDB::readImageFile(filename);

	if (!image) 
	{
		image = osgDB::readImageFile("Resources/noTexture.jpg");

		osg::notify(osg::WARN) << "Couldn't load texture."  << std::endl;

		if (!image) 
		{
			return;
		}
	}
	osg::ref_ptr<osg::Texture2D> texture = new osg::Texture2D;
	texture->setDataVariance(osg::Object::DYNAMIC);
	texture->setWrap(osg::Texture::WRAP_S, osg::Texture::REPEAT);
	texture->setWrap(osg::Texture::WRAP_T, osg::Texture::REPEAT);
	texture->setImage(image);

	// assign the texture
	osg::StateSet * stateset = geometry->getOrCreateStateSet();
	stateset->setTextureAttributeAndModes(0, texture, osg::StateAttribute::ON);
	stateset->setAttributeAndModes( material, 	osg::StateAttribute::ON);
	stateset->setMode(GL_LIGHTING, osg::StateAttribute::OFF);


	//add it to the helper group
	geode->addDrawable(geometry.get());
	mGridGroup->addChild(geode);
}

/**
* Create a light to lit the scene
*/
void  OSGMain::AddLight()
{
	//create a light
	osg::ref_ptr<osg::Light> light = new osg::Light();
	osg::ref_ptr<osg::LightSource> lightSource=new osg::LightSource;

	// each light must have a unique number
	light->setLightNum(0);
	// set the light's position via a PositionAttitudeTransform object
	osg::Vec3 direction;
	direction.set(0.0, 0.5, 0.50 );
	direction.normalize();
	light->setDirection(direction);
	//set color parameters
	light->setDiffuse(osg::Vec4(0.9, 0.9, 0.9, 1.0));
	light->setSpecular(osg::Vec4(1.0, 1.0, 1.0, 1.0));
	light->setAmbient( osg::Vec4(0.0, 0.0, 0.0, 1.0));
	//setup the lightsource
	lightSource->setLight(light);
	lightSource->setLocalStateSetModes(osg::StateAttribute::ON);
	lightSource->setStateSetModes(*(mRootGroup->getOrCreateStateSet()), osg::StateAttribute::ON);

	//add it to the root
	mRootGroup->addChild(lightSource);
}


/**
* Create all the records helpers for all the roads
*/
void  OSGMain::DrawRecordHelpers()
{
	//For each road
	for (unsigned int i=0; i<mOpenDrive->GetRoadCount(); i++)
	{
		//Draw its records helpers
		mOsgRecordHelpers->FillHelperGroups(mOpenDrive->GetRoad(i),i, mRecordsHelpersGroup.get());
	}
}
/**
* Create a screenshot. The output is created in the "Screenshots" folder in the working directory
*/
void OSGMain::TakeScreenshot ()
{
	//backup the viewer
	osg::Matrixd matrix = mViewer->getCameraManipulator()->getMatrix();
	
	//move the camera to its default top position
	mViewer->home();

	//update the viewport
	frame();

	//get the screen size and take the screenshot
	int tmp=0, scrWidth=0, scrHeight=0;
	mGw->getWindowRectangle(tmp,tmp,scrWidth,scrHeight);
	mScreenshotRequest->TakeScreenshot( scrWidth ,scrHeight);

	frame();

	//set the viewport to its backed up position
	mViewer->getCameraManipulator()->setByMatrix(matrix);
}

/**
* Pick a 3D object from the viewport
* @param x, y coordinates of the cursor at which to pick the objects 
*/
OSGObjectNode* OSGMain::PickNode(float x, float y)
{
	//start Timer for statistics
	osg::Timer_t startTick = osg::Timer::instance()->tick();


	OSGObjectNode* selectionInfo=new OSGObjectNode;

	osgUtil::LineSegmentIntersector::Intersections intersections;
	if (mViewer->computeIntersections(x,y,intersections))
	{
		//osgUtil::LineSegmentIntersector::Intersections::iterator hit=intersections.end();
		//hit--;

		osgUtil::LineSegmentIntersector::Intersections::iterator hit=intersections.begin();
		if (!hit->nodePath.empty())
		{
			//Get the path to the picked node
            const osg::NodePath* nodePath=&(hit->nodePath);

			//Get the selected object
			osg::Node* node = nodePath->back();
			OSGObjectNode* objNode=dynamic_cast<OSGObjectNode*> (node);
			if (objNode!=NULL)
			{
				//clear the indices of the object's NodeInfo in order to fill them
				selectionInfo->ClearNodeInfoIndices();

				//check the size of the node path, if it is a root node, ignore it, all the roads and helpers have parents
				if(nodePath->size()>1)
				{
					selectionInfo->SetNodeType(objNode->GetNodeType());
					//Get the indices of the helper to select it
					switch (selectionInfo->GetNodeType())
					{
					case ROAD_NODE:
						selectionInfo->AddNodeInfoIndex(mRoadsGroup->getChildIndex( node  ) );	
						break;

					case JUNCTION_NODE:
						selectionInfo->AddNodeInfoIndex(mRoadsGroup->getChildIndex( nodePath->at(nodePath->size()-2)->asTransform()  ) );
						break;

					case ROAD_TYPE_NODE:
					case GEOMETRY_BLOCK_NODE:
					case ELEVATION_NODE:
					case SUPERELEVATION_NODE:
					case CROSSFALL_NODE:
					case OBJECT_NODE:
					case SIGNAL_NODE:
						{
							//get the index of the parameter and then the index of the road
							//The object under these types are helpers and helpers are children of matrixTransforms, so, take the child's index of the
							//matrixTransform instead of the roadParam's itself:
							//(nodePath.size()-2) is the path to matrixTransform and (nodePath.size()-3) the path to it's parent, the road parameter group
							//(nodePath.size()-4) is the path to the road group that contains all the helper groups
							osg::Group* road = nodePath->at(nodePath->size()-4)->asGroup();
							osg::Group* roadParamGroup = nodePath->at(nodePath->size()-3)->asGroup();
							osg::MatrixTransform* roadParam = dynamic_cast<osg::MatrixTransform*> (nodePath->at(nodePath->size()-2)->asTransform());

							unsigned int roadInd,roadParamInd;

							roadParamInd=roadParamGroup->getChildIndex(roadParam);
							roadInd=mRecordsHelpersGroup->getChildIndex(road);

							selectionInfo->AddNodeInfoIndex(roadInd);
							selectionInfo->AddNodeInfoIndex(roadParamInd);
							break;
						}

					case LANE_SECTION_NODE:
						{
							//get the index of the parameter and then the index of the road
							//The object under these types are helpers and helpers are children of matrixTransforms, so, take the child's index of the
							//matrixTransform instead of the roadParam's itself:
							//(nodePath.size()-2) is the path to matrixTransform and (nodePath.size()-3) the path to it's parent, the road parameter group
							//(nodePath.size()-4) is the path to the road group that contains all the helper groups
							osg::Group* road = nodePath->at(nodePath->size()-5)->asGroup();
							osg::Group* roadParamGroup = nodePath->at(nodePath->size()-4)->asGroup();
							osg::Group* roadParam = nodePath->at(nodePath->size()-3)->asGroup();

							unsigned int roadInd,roadParamInd;

							roadParamInd=roadParamGroup->getChildIndex(roadParam);
							roadInd=mRecordsHelpersGroup->getChildIndex(road);

							selectionInfo->AddNodeInfoIndex(roadInd);
							selectionInfo->AddNodeInfoIndex(roadParamInd);
							break;
						}					
					case LANE_WIDTH_NODE:
					case LANE_ROAD_MARK_NODE:
					case LANE_MATERIAL_NODE:
					case LANE_VISIBILITY_NODE:
					case LANE_SPEED_NODE:
					case LANE_ACCESS_NODE:
					case LANE_HEIGHT_NODE:
						{

							//The same way, get the index of the parameter and then the index of the lane, laneSection and road
							//(nodePath.size()-2) is the path to matrixTransform and (nodePath.size()-3) the path to it's parent, the lane parameter group (laneRoadMarks, laneMaterial, etc)
							//(nodePath.size()-4) is the path to the lane group, (nodePath.size()-5) is the path to the lanesGroup inside the laneSection 
							//(nodePath.size()-6) laneSection (which is a road param) and (nodePath.size()-8) is the road group
							//

							osg::Group* road = nodePath->at(nodePath->size()-8)->asGroup();
							osg::Group* laneSectionGroup = nodePath->at(nodePath->size()-7)->asGroup();
							osg::Group* laneSection = nodePath->at(nodePath->size()-6)->asGroup();

							osg::Group* lanesGroup = nodePath->at(nodePath->size()-5)->asGroup();
							osg::Group* lane = nodePath->at(nodePath->size()-4)->asGroup();
							osg::Group* laneParamGroup = nodePath->at(nodePath->size()-3)->asGroup();
							osg::MatrixTransform* laneParam = dynamic_cast<osg::MatrixTransform*> (nodePath->at(nodePath->size()-2)->asTransform());

							unsigned int roadInd,laneSectionInd, laneInd, laneParamInd;

							laneParamInd=laneParamGroup->getChildIndex(laneParam);
							laneInd=lanesGroup->getChildIndex(lane);
							laneSectionInd=laneSectionGroup->getChildIndex(laneSection);
							roadInd=mRecordsHelpersGroup->getChildIndex(road);

							selectionInfo->AddNodeInfoIndex(roadInd);
							selectionInfo->AddNodeInfoIndex(laneSectionInd);
							selectionInfo->AddNodeInfoIndex(laneInd);
							selectionInfo->AddNodeInfoIndex(laneParamInd);
							break;
						}

					}

					//STATISTICS
					//*******************
					//return statistics
					std::ostringstream ss; 	std::string str;
					osg::Timer_t endTick = osg::Timer::instance()->tick();
					ss<<"Picked in "<<osg::Timer::instance()->delta_s(startTick,endTick)<<std::endl;
					str.append(ss.str());
					//Output to the debug window
                    //OutputDebugString( "\n" ) ;
                    //OutputDebugString( str.c_str() ) ;
                    //OutputDebugString( "\n" ) ;

				}
				///////////////////////////////////////////////


				return  selectionInfo;
			}
		}
	}


	ClearSelection();
	return NULL;
}

/**
* Change the color of the selected object, to visually represent the selection
* @param objToSelect Object to be selected
*/
void OSGMain::MakeSelection(OSGObjectNode* objToSelect)
{
	ClearSelection();
	mCurrentlySelected=*objToSelect;

	if (objToSelect!=NULL)
	{
		osg::Geometry* geom;
		osg::Vec4Array* colorArr;

		OSGGeodeNode* geode = FindNode(objToSelect);


		//If nothing found, return
		if (geode==NULL)
		{
			mCurrentlySelected.ClearNodeInfoIndices();
			return;
		}

		//change the colors
		geom=geode->getDrawable(0)->asGeometry();
		if (geom==NULL)
		{	
			mCurrentlySelected.ClearNodeInfoIndices();
			return;
		}
		colorArr=static_cast<osg::Vec4Array*>(geom->getColorArray());
		mCurrentlySelectedBinding=geom->getColorBinding();
		geom->setColorBinding(osg::Geometry::BIND_OVERALL);
		colorArr->insert(colorArr->begin(),osg::Vec4(1,0.75,0.3,1));

		//If display lists are used,dirty the lists here.
	}

}

/**
* Clear the selection
*/
void OSGMain::ClearSelection(bool objDeleted)
{
	if (!objDeleted)
	{
		//change back the colors of the currently selected object (deselect)
		if (!mCurrentlySelected.IsEmpty())
		{

			osg::Geometry* geom;
			osg::Vec4Array* colorArr;

			OSGGeodeNode* geode = FindNode(&mCurrentlySelected);

			//If nothing found, return
			if (geode==NULL)
			{
				mCurrentlySelected.ClearNodeInfoIndices();
				return;
			}

			//change the colors
			geom=geode->getDrawable(0)->asGeometry();
			if (geom==NULL)
			{
				mCurrentlySelected.ClearNodeInfoIndices();
				return;
			}

			colorArr=static_cast<osg::Vec4Array*>(geom->getColorArray());
			if (colorArr->size()>1)
			{
				colorArr->erase(colorArr->begin());
				geom->setColorBinding(mCurrentlySelectedBinding);
			}

		}
	}

	mCurrentlySelected.ClearNodeInfoIndices();
}

/**
* Depending on the node type and the hierarchycal index array, find it in the structure
* @param objToSelect Object to be selected
* @return A pointer to the helper geode is returned, which contains the picked object
*/
OSGGeodeNode*  OSGMain::FindNode(OSGObjectNode* objToSelect)
{
	OSGGeodeNode* nodeToFind;
	unsigned int roadInd,roadParamInd,laneSectionInd,laneInd,laneParamInd;
	if(objToSelect!=NULL)
	{
		roadInd=objToSelect->GetNodeInfoIndex(0);
		switch(objToSelect->GetNodeType())
		{
		case ROAD_NODE:
		case JUNCTION_NODE:
			{
				//check if the road exists
				if (roadInd >= mRoadsGroup->getNumChildren())
					return	NULL;

				if (mRoadsGroup->getChild(roadInd)->asGeode()->getNumDrawables()<=0)
					return	NULL;


				nodeToFind=static_cast<OSGGeodeNode*>(mRoadsGroup->getChild(roadInd));
				break;
			}

		case ROAD_TYPE_NODE:
			{
				roadParamInd=objToSelect->GetNodeInfoIndex(1);

				//index of the group inside the road group
				unsigned int groupIndex=0;

				//check if the road exists
				if (roadInd >= mRecordsHelpersGroup->getNumChildren())
					return NULL;
				//same for the param
				if (roadParamInd >=  mRecordsHelpersGroup->getChild(roadInd)->asGroup()->getChild(groupIndex)->asGroup()->getNumChildren())
					return NULL;

				//same for the transform
				if ( mRecordsHelpersGroup->getChild(roadInd)->asGroup()->getChild(groupIndex)->asGroup()->getChild(roadParamInd)->asTransform()->getNumChildren()<=0)
					return NULL;

				nodeToFind=static_cast<OSGGeodeNode*>(mRecordsHelpersGroup->getChild(roadInd)->asGroup()->getChild(groupIndex)->asGroup()->getChild(roadParamInd)->asTransform()->getChild(0));
				break;
			}
		case GEOMETRY_BLOCK_NODE:
			{
				roadParamInd=objToSelect->GetNodeInfoIndex(1);

				//index of the group inside the road group
				unsigned int groupIndex=1;

				//check if the road exists
				if (roadInd >= mRecordsHelpersGroup->getNumChildren())
					return NULL;
				//same for the param
				if (roadParamInd >=  mRecordsHelpersGroup->getChild(roadInd)->asGroup()->getChild(groupIndex)->asGroup()->getNumChildren())
					return NULL;
				//same for the transform
				if ( mRecordsHelpersGroup->getChild(roadInd)->asGroup()->getChild(groupIndex)->asGroup()->getChild(roadParamInd)->asTransform()->getNumChildren()<=0)
					return NULL;

				nodeToFind=static_cast<OSGGeodeNode*>(mRecordsHelpersGroup->getChild(roadInd)->asGroup()->getChild(groupIndex)->asGroup()->getChild(roadParamInd)->asTransform()->getChild(0));
				break;
			}
		case ELEVATION_NODE:
			{
				roadParamInd=objToSelect->GetNodeInfoIndex(1);

				//index of the group inside the road group
				unsigned int groupIndex=2;

				//check if the road exists
				if (roadInd >= mRecordsHelpersGroup->getNumChildren())
					return NULL;
				//same for the param
				if (roadParamInd >=  mRecordsHelpersGroup->getChild(roadInd)->asGroup()->getChild(groupIndex)->asGroup()->getNumChildren())
					return NULL;
				//same for the transform
				if ( mRecordsHelpersGroup->getChild(roadInd)->asGroup()->getChild(groupIndex)->asGroup()->getChild(roadParamInd)->asTransform()->getNumChildren()<=0)
					return NULL;

				nodeToFind=static_cast<OSGGeodeNode*>(mRecordsHelpersGroup->getChild(roadInd)->asGroup()->getChild(groupIndex)->asGroup()->getChild(roadParamInd)->asTransform()->getChild(0));
				break;
			}
		case SUPERELEVATION_NODE:
			{
				roadParamInd=objToSelect->GetNodeInfoIndex(1);

				//index of the group inside the road group
				unsigned int groupIndex=3;

				//check if the road exists
				if (roadInd >= mRecordsHelpersGroup->getNumChildren())
					return NULL;
				//same for the param
				if (roadParamInd >=  mRecordsHelpersGroup->getChild(roadInd)->asGroup()->getChild(groupIndex)->asGroup()->getNumChildren())
					return NULL;
				//same for the transform
				if ( mRecordsHelpersGroup->getChild(roadInd)->asGroup()->getChild(groupIndex)->asGroup()->getChild(roadParamInd)->asTransform()->getNumChildren()<=0)
					return NULL;

				nodeToFind=static_cast<OSGGeodeNode*>(mRecordsHelpersGroup->getChild(roadInd)->asGroup()->getChild(groupIndex)->asGroup()->getChild(roadParamInd)->asTransform()->getChild(0));
				break;
			}
		case CROSSFALL_NODE:
			{
				roadParamInd=objToSelect->GetNodeInfoIndex(1);

				//index of the group inside the road group
				unsigned int groupIndex=4;

				//check if the road exists
				if (roadInd >= mRecordsHelpersGroup->getNumChildren())
					return NULL;
				//same for the param
				if (roadParamInd >=  mRecordsHelpersGroup->getChild(roadInd)->asGroup()->getChild(groupIndex)->asGroup()->getNumChildren())
					return NULL;
				//same for the transform
				if ( mRecordsHelpersGroup->getChild(roadInd)->asGroup()->getChild(groupIndex)->asGroup()->getChild(roadParamInd)->asTransform()->getNumChildren()<=0)
					return NULL;

				nodeToFind=static_cast<OSGGeodeNode*>(mRecordsHelpersGroup->getChild(roadInd)->asGroup()->getChild(groupIndex)->asGroup()->getChild(roadParamInd)->asTransform()->getChild(0));
				break;
			}
		case LANE_SECTION_NODE:
			{
				roadParamInd=objToSelect->GetNodeInfoIndex(1);


				//index of the group inside the road group
				unsigned int groupIndex=5;

				//check if the road exists
				if (roadInd >= mRecordsHelpersGroup->getNumChildren())
					return NULL;
				//same for the param
				if (roadParamInd >=  mRecordsHelpersGroup->getChild(roadInd)->asGroup()->getChild(groupIndex)->asGroup()->getNumChildren())
					return NULL;
				//same for the lanesparamGroup
				if ( mRecordsHelpersGroup->getChild(roadInd)->asGroup()->getChild(groupIndex)->asGroup()->getChild(roadParamInd)->asGroup()->getNumChildren()<=0)
					return NULL;
				//same for the transform
				if ( mRecordsHelpersGroup->getChild(roadInd)->asGroup()->getChild(groupIndex)->asGroup()->getChild(roadParamInd)->asGroup()->getChild(0)->asTransform()->getNumChildren()<=0)
					return NULL;

				nodeToFind=static_cast<OSGGeodeNode*>(mRecordsHelpersGroup->getChild(roadInd)->asGroup()->getChild(groupIndex)->asGroup()->getChild(roadParamInd)->asGroup()->getChild(0)->asTransform()->getChild(0));
				break;
			}
		case LANE_WIDTH_NODE:
			{
				laneSectionInd=objToSelect->GetNodeInfoIndex(1);
				laneInd=objToSelect->GetNodeInfoIndex(2);
				laneParamInd=objToSelect->GetNodeInfoIndex(3);

				//index of the group inside the road group
				unsigned int groupIndex=5;

				//index of the parameters group inside the lane group
				unsigned int laneParamGroup=0;


				//check if the road exists
				if (roadInd >= mRecordsHelpersGroup->getNumChildren())
					return NULL;

				osg::Group* road = mRecordsHelpersGroup->getChild(roadInd)->asGroup();
				//same for the laneSection
				if (laneSectionInd >= road ->getChild(groupIndex)->asGroup()->getNumChildren())
					return NULL;

				osg::Group* laneSection = road ->getChild(groupIndex)->asGroup()->getChild(laneSectionInd)->asGroup();

				//same for the lane
				if (laneInd >= laneSection->getChild(1)->asGroup()->getNumChildren())
					return NULL;

				osg::Group* lane = laneSection->getChild(1)->asGroup()->getChild(laneInd)->asGroup();
				//same for the lane param
				if (laneParamInd >=  lane->getChild(laneParamGroup)->asGroup()->getNumChildren())
					return NULL;

				//same for the transform
				if (lane->getChild(laneParamGroup)->asGroup()->getChild(laneParamInd)->asTransform()->getNumChildren()<=0)
					return NULL;



				nodeToFind=static_cast<OSGGeodeNode*>(lane->getChild(laneParamGroup)->asGroup()->getChild(laneParamInd)->asTransform()->getChild(0));
				break;
			}
		case LANE_ROAD_MARK_NODE:
			{
				laneSectionInd=objToSelect->GetNodeInfoIndex(1);
				laneInd=objToSelect->GetNodeInfoIndex(2);
				laneParamInd=objToSelect->GetNodeInfoIndex(3);

				//index of the group inside the road group
				unsigned int groupIndex=5;

				//index of the parameters group inside the lane group
				unsigned int laneParamGroup=1;


				//check if the road exists
				if (roadInd >= mRecordsHelpersGroup->getNumChildren())
					return NULL;

				osg::Group* road = mRecordsHelpersGroup->getChild(roadInd)->asGroup();
				//same for the laneSection
				if (laneSectionInd >= road ->getChild(groupIndex)->asGroup()->getNumChildren())
					return NULL;

				osg::Group* laneSection = road ->getChild(groupIndex)->asGroup()->getChild(laneSectionInd)->asGroup();

				//same for the lane
				if (laneInd >= laneSection->getChild(1)->asGroup()->getNumChildren())
					return NULL;

				osg::Group* lane = laneSection->getChild(1)->asGroup()->getChild(laneInd)->asGroup();
				//same for the lane param
				if (laneParamInd >=  lane->getChild(laneParamGroup)->asGroup()->getNumChildren())
					return NULL;
				//same for the transform
				if (lane->getChild(laneParamGroup)->asGroup()->getChild(laneParamInd)->asTransform()->getNumChildren()<=0)
					return NULL;


				nodeToFind=static_cast<OSGGeodeNode*>(lane->getChild(laneParamGroup)->asGroup()->getChild(laneParamInd)->asTransform()->getChild(0));
				break;
			}
		case LANE_MATERIAL_NODE:
			{
				laneSectionInd=objToSelect->GetNodeInfoIndex(1);
				laneInd=objToSelect->GetNodeInfoIndex(2);
				laneParamInd=objToSelect->GetNodeInfoIndex(3);

				//index of the group inside the road group
				unsigned int groupIndex=5;

				//index of the parameters group inside the lane group
				unsigned int laneParamGroup=2;


				//check if the road exists
				if (roadInd >= mRecordsHelpersGroup->getNumChildren())
					return NULL;

				osg::Group* road = mRecordsHelpersGroup->getChild(roadInd)->asGroup();
				//same for the laneSection
				if (laneSectionInd >= road ->getChild(groupIndex)->asGroup()->getNumChildren())
					return NULL;

				osg::Group* laneSection = road ->getChild(groupIndex)->asGroup()->getChild(laneSectionInd)->asGroup();

				//same for the lane
				if (laneInd >= laneSection->getChild(1)->asGroup()->getNumChildren())
					return NULL;

				osg::Group* lane = laneSection->getChild(1)->asGroup()->getChild(laneInd)->asGroup();
				//same for the lane param
				if (laneParamInd >=  lane->getChild(laneParamGroup)->asGroup()->getNumChildren())
					return NULL;
				//same for the transform
				if (lane->getChild(laneParamGroup)->asGroup()->getChild(laneParamInd)->asTransform()->getNumChildren()<=0)
					return NULL;


				nodeToFind=static_cast<OSGGeodeNode*>(lane->getChild(laneParamGroup)->asGroup()->getChild(laneParamInd)->asTransform()->getChild(0));
				break;
			}
		case LANE_VISIBILITY_NODE:
			{
				laneSectionInd=objToSelect->GetNodeInfoIndex(1);
				laneInd=objToSelect->GetNodeInfoIndex(2);
				laneParamInd=objToSelect->GetNodeInfoIndex(3);

				//index of the group inside the road group
				unsigned int groupIndex=5;

				//index of the parameters group inside the lane group
				unsigned int laneParamGroup=3;


				//check if the road exists
				if (roadInd >= mRecordsHelpersGroup->getNumChildren())
					return NULL;

				osg::Group* road = mRecordsHelpersGroup->getChild(roadInd)->asGroup();
				//same for the laneSection
				if (laneSectionInd >= road ->getChild(groupIndex)->asGroup()->getNumChildren())
					return NULL;

				osg::Group* laneSection = road ->getChild(groupIndex)->asGroup()->getChild(laneSectionInd)->asGroup();

				//same for the lane
				if (laneInd >= laneSection->getChild(1)->asGroup()->getNumChildren())
					return NULL;

				osg::Group* lane = laneSection->getChild(1)->asGroup()->getChild(laneInd)->asGroup();
				//same for the lane param
				if (laneParamInd >=  lane->getChild(laneParamGroup)->asGroup()->getNumChildren())
					return NULL;
				//same for the transform
				if (lane->getChild(laneParamGroup)->asGroup()->getChild(laneParamInd)->asTransform()->getNumChildren()<=0)
					return NULL;


				nodeToFind=static_cast<OSGGeodeNode*>(lane->getChild(laneParamGroup)->asGroup()->getChild(laneParamInd)->asTransform()->getChild(0));
				break;
			}
		case LANE_SPEED_NODE:
			{
				laneSectionInd=objToSelect->GetNodeInfoIndex(1);
				laneInd=objToSelect->GetNodeInfoIndex(2);
				laneParamInd=objToSelect->GetNodeInfoIndex(3);

				//index of the group inside the road group
				unsigned int groupIndex=5;

				//index of the parameters group inside the lane group
				unsigned int laneParamGroup=4;


				//check if the road exists
				if (roadInd >= mRecordsHelpersGroup->getNumChildren())
					return NULL;

				osg::Group* road = mRecordsHelpersGroup->getChild(roadInd)->asGroup();
				//same for the laneSection
				if (laneSectionInd >= road ->getChild(groupIndex)->asGroup()->getNumChildren())
					return NULL;

				osg::Group* laneSection = road ->getChild(groupIndex)->asGroup()->getChild(laneSectionInd)->asGroup();

				//same for the lane
				if (laneInd >= laneSection->getChild(1)->asGroup()->getNumChildren())
					return NULL;

				osg::Group* lane = laneSection->getChild(1)->asGroup()->getChild(laneInd)->asGroup();
				//same for the lane param
				if (laneParamInd >=  lane->getChild(laneParamGroup)->asGroup()->getNumChildren())
					return NULL;
				//same for the transform
				if (lane->getChild(laneParamGroup)->asGroup()->getChild(laneParamInd)->asTransform()->getNumChildren()<=0)
					return NULL;


				nodeToFind=static_cast<OSGGeodeNode*>(lane->getChild(laneParamGroup)->asGroup()->getChild(laneParamInd)->asTransform()->getChild(0));
				break;
			}
		case LANE_ACCESS_NODE:
			{
				laneSectionInd=objToSelect->GetNodeInfoIndex(1);
				laneInd=objToSelect->GetNodeInfoIndex(2);
				laneParamInd=objToSelect->GetNodeInfoIndex(3);

				//index of the group inside the road group
				unsigned int groupIndex=5;

				//index of the parameters group inside the lane group
				unsigned int laneParamGroup=5;


				//check if the road exists
				if (roadInd >= mRecordsHelpersGroup->getNumChildren())
					return NULL;

				osg::Group* road = mRecordsHelpersGroup->getChild(roadInd)->asGroup();
				//same for the laneSection
				if (laneSectionInd >= road ->getChild(groupIndex)->asGroup()->getNumChildren())
					return NULL;

				osg::Group* laneSection = road ->getChild(groupIndex)->asGroup()->getChild(laneSectionInd)->asGroup();

				//same for the lane
				if (laneInd >= laneSection->getChild(1)->asGroup()->getNumChildren())
					return NULL;

				osg::Group* lane = laneSection->getChild(1)->asGroup()->getChild(laneInd)->asGroup();
				//same for the lane param
				if (laneParamInd >=  lane->getChild(laneParamGroup)->asGroup()->getNumChildren())
					return NULL;
				//same for the transform
				if (lane->getChild(laneParamGroup)->asGroup()->getChild(laneParamInd)->asTransform()->getNumChildren()<=0)
					return NULL;


				nodeToFind=static_cast<OSGGeodeNode*>(lane->getChild(laneParamGroup)->asGroup()->getChild(laneParamInd)->asTransform()->getChild(0));
				break;
			}
		case LANE_HEIGHT_NODE:
			{
				laneSectionInd=objToSelect->GetNodeInfoIndex(1);
				laneInd=objToSelect->GetNodeInfoIndex(2);
				laneParamInd=objToSelect->GetNodeInfoIndex(3);

				//index of the group inside the road group
				unsigned int groupIndex=5;

				//index of the parameters group inside the lane group
				unsigned int laneParamGroup=6;


				//check if the road exists
				if (roadInd >= mRecordsHelpersGroup->getNumChildren())
					return NULL;

				osg::Group* road = mRecordsHelpersGroup->getChild(roadInd)->asGroup();
				//same for the laneSection
				if (laneSectionInd >= road ->getChild(groupIndex)->asGroup()->getNumChildren())
					return NULL;

				osg::Group* laneSection = road ->getChild(groupIndex)->asGroup()->getChild(laneSectionInd)->asGroup();

				//same for the lane
				if (laneInd >= laneSection->getChild(1)->asGroup()->getNumChildren())
					return NULL;

				osg::Group* lane = laneSection->getChild(1)->asGroup()->getChild(laneInd)->asGroup();
				//same for the lane param
				if (laneParamInd >=  lane->getChild(laneParamGroup)->asGroup()->getNumChildren())
					return NULL;
				//same for the transform
				if (lane->getChild(laneParamGroup)->asGroup()->getChild(laneParamInd)->asTransform()->getNumChildren()<=0)
					return NULL;


				nodeToFind=static_cast<OSGGeodeNode*>(lane->getChild(laneParamGroup)->asGroup()->getChild(laneParamInd)->asTransform()->getChild(0));
				break;
			}

		case OBJECT_NODE:
			{
				roadParamInd=objToSelect->GetNodeInfoIndex(1);

				//index of the group inside the road group
				unsigned int groupIndex=6;

				//check if the road exists
				if (roadInd >= mRecordsHelpersGroup->getNumChildren())
					return NULL;
				//same for the param
				if (roadParamInd >=  mRecordsHelpersGroup->getChild(roadInd)->asGroup()->getChild(groupIndex)->asGroup()->getNumChildren())
					return NULL;
				//same for the transform
				if ( mRecordsHelpersGroup->getChild(roadInd)->asGroup()->getChild(groupIndex)->asGroup()->getChild(roadParamInd)->asTransform()->getNumChildren()<=0)
					return NULL;

				nodeToFind=static_cast<OSGGeodeNode*>(mRecordsHelpersGroup->getChild(roadInd)->asGroup()->getChild(groupIndex)->asGroup()->getChild(roadParamInd)->asTransform()->getChild(0));
				break;
			}
		case SIGNAL_NODE:
			{
				roadParamInd=objToSelect->GetNodeInfoIndex(1);

				//index of the group inside the road group
				unsigned int groupIndex=7;

				//check if the road exists
				if (roadInd >= mRecordsHelpersGroup->getNumChildren())
					return NULL;
				//same for the param
				if (roadParamInd >=  mRecordsHelpersGroup->getChild(roadInd)->asGroup()->getChild(groupIndex)->asGroup()->getNumChildren())
					return NULL;
				//same for the transform
				if ( mRecordsHelpersGroup->getChild(roadInd)->asGroup()->getChild(groupIndex)->asGroup()->getChild(roadParamInd)->asTransform()->getNumChildren()<=0)
					return NULL;

				nodeToFind=static_cast<OSGGeodeNode*>(mRecordsHelpersGroup->getChild(roadInd)->asGroup()->getChild(groupIndex)->asGroup()->getChild(roadParamInd)->asTransform()->getChild(0));
				break;
			}
		}
		return nodeToFind;
	}
	return NULL;
}


/**
* Export all the useful geometry to a file
* @param fileName Filename of the file to be created
*/
void OSGMain::SaveGeometry(std::string fileName)
{
	//Create a fresh group
	osg::ref_ptr<osg::Group> groupToSave = new osg::Group;

	//Add all the important geometry to it
	groupToSave->addChild(mRoadsGroup);
	groupToSave->addChild(mSceneryGroup);
	groupToSave->addChild(mJunctionsGroup);

	//Save it to a file 
	osgDB::writeNodeFile( *groupToSave,fileName);

	//Clear it
	groupToSave->removeChildren(0,groupToSave->getNumChildren());
}

/**
* Delete road geometry from the roads group
* @param roadToRemove Index of the road to be removed
*/
void OSGMain::DeleteRoad(unsigned int roadToRemove)
{
	//remove the road form the osg roads group
	mRoadsGroup->removeChild(roadToRemove);

	//remove it from the scenery's constraints vector and recalc vector
	if (mOsgScenery->GetRoadConstraintVerticesVector().size()>roadToRemove)
	{	
		mOsgScenery->GetRoadConstraintVerticesVector().erase(mOsgScenery->GetRoadConstraintVerticesVector().begin()+roadToRemove);
		mOsgScenery->GetRecalcVector()->erase(mOsgScenery->GetRecalcVector()->begin()+roadToRemove);
	}

	//remove it from the osg chordline group
	mRoadChordLineGroup->removeChild(roadToRemove);

	//remove it from the records helper group
	mRecordsHelpersGroup->removeChild(roadToRemove);

	//remove it from the helpers (arrows) group
	mHelpersGroup->removeChild(roadToRemove);
}

/**
* Delete junction geometry from the junctions group
* @param junctionToRemove Index of the junction to be removed
*/
void OSGMain::DeleteJunction(unsigned int junctionToRemove)
{
	mJunctionsGroup->removeChild(junctionToRemove);
}


/**
* Clear everything geometry related. 
*/
void OSGMain::Clear()
{
	//Clear osg groups
	mRoadsGroup->removeChildren(0,mRoadsGroup->getNumChildren());
	mRoadChordLineGroup->removeChildren(0,mRoadChordLineGroup->getNumChildren());
	mJunctionsGroup->removeChildren(0,mJunctionsGroup->getNumChildren());
	mSceneryGroup->removeChildren(0,mSceneryGroup->getNumChildren());
	mHelpersGroup->removeChildren(0,mHelpersGroup->getNumChildren());
	mRecordsHelpersGroup->removeChildren(0,mRecordsHelpersGroup->getNumChildren());

	//Clear helper objects
	delete mOsgJunction;
	delete mOsgRoad;
	delete mOsgRecordHelpers;
	delete mOsgScenery;


	//Reallocate the memory for the geometry creation objects
	mOsgRoad=new OSGRoad();
	mOsgJunction=new OSGJunction;
	mOsgRecordHelpers=new OSGRecordsHelpers;
	mOsgScenery=new OSGScenery;

	mCurrentlySelected.ClearNodeInfoIndices();
}
