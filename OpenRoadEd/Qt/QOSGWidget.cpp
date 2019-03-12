#include "QOSGWidget.h"
#include "moc_QOSGWidget.cpp"

#include "../Osg/OSGMain.h"

/**
 * Constructor, sets the references for the OSG object
 *
 * @param osgMain Pointer to the OSG object
 * @param parent Parent widget
 * @param name Name of the widget
 * @param f Windows flags, NULL for default flags
 */
QOSGWidget::QOSGWidget(OSGMain *osgMain, QWidget * parent, const char * name, WindowFlags f):QWidget(parent, f)
{
	mOsgMain=osgMain;
	connect(&_timer, SIGNAL(timeout()), this, SLOT(update()));
	_timer.start(10);
}

/**
 * Initializes the OSG widget
 *
 * @param roadTree Reference to the road tree panel
 */
void QOSGWidget::Init(RoadTree *roadTree)
{
	// Saves the reference to the road tree panel
	mRoadTree=roadTree;

	// Updates the size of the 3D viewport
	mOsgMain->initViewer(x(),y(),width(),height(),winId());

	setAttribute(Qt::WA_PaintOnScreen);
	setAttribute(Qt::WA_NoSystemBackground);
	setFocusPolicy(Qt::ClickFocus);
}

/**
 * Paint event, used to redraw the widget
 *
 * @param e Event object
 */
void QOSGWidget::paintEvent(QPaintEvent *e)
{
	mOsgMain->frame();
}

/**
 * Mouse events. Checks if Space (camera mode) is not active and Picks an object in 3D
 */
void QOSGWidget::mousePressEvent(QMouseEvent *e)
{
	if(!mSpaceIsDown) Pick(e);
}
void QOSGWidget::mouseReleaseEvent(QMouseEvent *e)
{
}

/**
 * Keybpard events. Checks if Space is down and sets the camera mode flag to true/false
 */
void QOSGWidget::keyPressEvent(QKeyEvent *e)
{
	grabKeyboard();
	if(e->key()==Qt::Key::Key_Space) mSpaceIsDown=true;
}
void QOSGWidget::keyReleaseEvent(QKeyEvent *e)
{
	releaseKeyboard();
	if(e->key()==Qt::Key::Key_Space) mSpaceIsDown=false;
}

/**
 * Method called when a record is selected in the road tree panel
 * Used to highlight the coresponding object in 3D viewport
 */
void QOSGWidget::SomethingSelected()
{
	// Gets the current selection from the road tree panel
	Selection *lSelection=mRoadTree->GetSelection();
	RoadTreeItemType lType = lSelection->GetType();

	// Creates a object node which will hold the selected object details
	OSGObjectNode osgNode;
	
	// Fills in the object node with the indices of the selected object
	switch (lType)
	{
	case ROAD:
		{
			osgNode.SetNodeType(ROAD_NODE);
			osgNode.AddNodeInfoIndex(lSelection->GetIndex(0));
			mOsgMain->MakeSelection(&osgNode);
			break;
		}
	case ROAD_TYPE:
		{
			osgNode.SetNodeType(ROAD_TYPE_NODE);
			osgNode.AddNodeInfoIndex(lSelection->GetIndex(0));
			osgNode.AddNodeInfoIndex(lSelection->GetIndex(1));
			mOsgMain->MakeSelection(&osgNode);
			break;
		}
	case GEOMETRY_LINE:
		{
			osgNode.SetNodeType(GEOMETRY_BLOCK_NODE);
			osgNode.AddNodeInfoIndex(lSelection->GetIndex(0));
			osgNode.AddNodeInfoIndex(lSelection->GetIndex(1));
			mOsgMain->MakeSelection(&osgNode);
			break;
		}
	case GEOMETRY_TURN:
		{
			osgNode.SetNodeType(GEOMETRY_BLOCK_NODE);
			osgNode.AddNodeInfoIndex(lSelection->GetIndex(0));
			osgNode.AddNodeInfoIndex(lSelection->GetIndex(1));
			mOsgMain->MakeSelection(&osgNode);
			break;
		}
	case ELEVATION:
		{
			osgNode.SetNodeType(ELEVATION_NODE);
			osgNode.AddNodeInfoIndex(lSelection->GetIndex(0));
			osgNode.AddNodeInfoIndex(lSelection->GetIndex(1));
			mOsgMain->MakeSelection(&osgNode);
			break;
		}
	case SUPERELEVATION:
		{
			osgNode.SetNodeType(SUPERELEVATION_NODE);
			osgNode.AddNodeInfoIndex(lSelection->GetIndex(0));
			osgNode.AddNodeInfoIndex(lSelection->GetIndex(1));
			mOsgMain->MakeSelection(&osgNode);
			break;
		}
	case CROSSFALL:
		{
			osgNode.SetNodeType(CROSSFALL_NODE);
			osgNode.AddNodeInfoIndex(lSelection->GetIndex(0));
			osgNode.AddNodeInfoIndex(lSelection->GetIndex(1));
			mOsgMain->MakeSelection(&osgNode);
			break;
		}
	case LANE_SECTION:
		{
			osgNode.SetNodeType(LANE_SECTION_NODE);
			osgNode.AddNodeInfoIndex(lSelection->GetIndex(0));
			osgNode.AddNodeInfoIndex(lSelection->GetIndex(1));
			mOsgMain->MakeSelection(&osgNode);
			break;
		}
	case LANE:
		{
			break;
		}
	case LANE_WIDTH:
		{
			osgNode.SetNodeType(LANE_WIDTH_NODE);
			osgNode.AddNodeInfoIndex(lSelection->GetIndex(0));
			osgNode.AddNodeInfoIndex(lSelection->GetIndex(1));
			osgNode.AddNodeInfoIndex(lSelection->GetIndex(2));
			osgNode.AddNodeInfoIndex(lSelection->GetIndex(3));
			mOsgMain->MakeSelection(&osgNode);
			break;
		}
	case LANE_ROAD_MARK:
		{
			osgNode.SetNodeType(LANE_ROAD_MARK_NODE);
			osgNode.AddNodeInfoIndex(lSelection->GetIndex(0));
			osgNode.AddNodeInfoIndex(lSelection->GetIndex(1));
			osgNode.AddNodeInfoIndex(lSelection->GetIndex(2));
			osgNode.AddNodeInfoIndex(lSelection->GetIndex(3));
			mOsgMain->MakeSelection(&osgNode);
			break;
		}
	case LANE_MATERIAL:
		{
			osgNode.SetNodeType(LANE_MATERIAL_NODE);
			osgNode.AddNodeInfoIndex(lSelection->GetIndex(0));
			osgNode.AddNodeInfoIndex(lSelection->GetIndex(1));
			osgNode.AddNodeInfoIndex(lSelection->GetIndex(2));
			osgNode.AddNodeInfoIndex(lSelection->GetIndex(3));
			mOsgMain->MakeSelection(&osgNode);
			break;
		}
	case LANE_VISIBILITY:
		{
			osgNode.SetNodeType(LANE_VISIBILITY_NODE);
			osgNode.AddNodeInfoIndex(lSelection->GetIndex(0));
			osgNode.AddNodeInfoIndex(lSelection->GetIndex(1));
			osgNode.AddNodeInfoIndex(lSelection->GetIndex(2));
			osgNode.AddNodeInfoIndex(lSelection->GetIndex(3));
			mOsgMain->MakeSelection(&osgNode);
			break;
		}
	case LANE_SPEED:
		{
			osgNode.SetNodeType(LANE_SPEED_NODE);
			osgNode.AddNodeInfoIndex(lSelection->GetIndex(0));
			osgNode.AddNodeInfoIndex(lSelection->GetIndex(1));
			osgNode.AddNodeInfoIndex(lSelection->GetIndex(2));
			osgNode.AddNodeInfoIndex(lSelection->GetIndex(3));
			mOsgMain->MakeSelection(&osgNode);
			break;
		}
	case LANE_ACCESS:
		{
			osgNode.SetNodeType(LANE_ACCESS_NODE);
			osgNode.AddNodeInfoIndex(lSelection->GetIndex(0));
			osgNode.AddNodeInfoIndex(lSelection->GetIndex(1));
			osgNode.AddNodeInfoIndex(lSelection->GetIndex(2));
			osgNode.AddNodeInfoIndex(lSelection->GetIndex(3));
			mOsgMain->MakeSelection(&osgNode);
			break;
		}
	case LANE_HEIGHT:
		{
			osgNode.SetNodeType(LANE_HEIGHT_NODE);
			osgNode.AddNodeInfoIndex(lSelection->GetIndex(0));
			osgNode.AddNodeInfoIndex(lSelection->GetIndex(1));
			osgNode.AddNodeInfoIndex(lSelection->GetIndex(2));
			osgNode.AddNodeInfoIndex(lSelection->GetIndex(3));
			mOsgMain->MakeSelection(&osgNode);
			break;
		}
	case OBJECT:
		{
			break;
		}
	case SIGNAL:
		{
			break;
		}
	case CONTROLLER:
		{
			break;
		}
	case JUNCTION:
		{
			break;
		}
	case JUNCTION_CONNECTION:
		{
			break;
		}
	case JUNCTION_LANE_LINK:
		{
			break;
		}
	case JUNCTION_PRIORITY:
		{
			break;
		}
	case JUNCTION_CONTROLLER:
		{
			break;
		}
	default:
		{
			break;
		}
	}
}

/**
 * Picks the node under the mouse cursor and selects the coresponding object in road tree
 *
 * @param e Mouse event
 */
void QOSGWidget::Pick(QMouseEvent *e)
{
	// If the left mouse button was clicked - pick the closest object in 3D space under the mouse cursor
	if(e->buttons()==Qt::LeftButton)
	{
		OSGObjectNode *lLastPicked = mOsgMain->PickNode(e->x(), height()-e->y());

		// If the picked object is not null - check it's type and select the object in road tree panel
  		if(lLastPicked!=NULL)
		{
			switch(lLastPicked->GetNodeType())
			{
			case ROAD_NODE:
				mRoadTree->SelectRoad(lLastPicked->GetNodeInfoIndex(0));
				break;
			case ROAD_TYPE_NODE:
				mRoadTree->SelectRoadType(lLastPicked->GetNodeInfoIndex(0),lLastPicked->GetNodeInfoIndex(1));
				break;
			case GEOMETRY_BLOCK_NODE:
				mRoadTree->SelectGeometry(lLastPicked->GetNodeInfoIndex(0),lLastPicked->GetNodeInfoIndex(1));
				break;
			case ELEVATION_NODE:
				mRoadTree->SelectElevation(lLastPicked->GetNodeInfoIndex(0),lLastPicked->GetNodeInfoIndex(1));
				break;
			case SUPERELEVATION_NODE:
				mRoadTree->SelectSuperElevation(lLastPicked->GetNodeInfoIndex(0),lLastPicked->GetNodeInfoIndex(1));
				break;
			case CROSSFALL_NODE:
				mRoadTree->SelectCrossfall(lLastPicked->GetNodeInfoIndex(0),lLastPicked->GetNodeInfoIndex(1));
				break;
			case LANE_SECTION_NODE:
				mRoadTree->SelectLaneSection(lLastPicked->GetNodeInfoIndex(0),lLastPicked->GetNodeInfoIndex(1));
				break;
			case LANE_NODE:
				mRoadTree->SelectLane(lLastPicked->GetNodeInfoIndex(0),lLastPicked->GetNodeInfoIndex(1),lLastPicked->GetNodeInfoIndex(2));
				break;
			case LANE_WIDTH_NODE:
				mRoadTree->SelectLaneWidth(lLastPicked->GetNodeInfoIndex(0),lLastPicked->GetNodeInfoIndex(1),lLastPicked->GetNodeInfoIndex(2),lLastPicked->GetNodeInfoIndex(3));
				break;
			case LANE_ROAD_MARK_NODE:
				mRoadTree->SelectLaneRoadMark(lLastPicked->GetNodeInfoIndex(0),lLastPicked->GetNodeInfoIndex(1),lLastPicked->GetNodeInfoIndex(2),lLastPicked->GetNodeInfoIndex(3));
				break;
			case LANE_MATERIAL_NODE:
				mRoadTree->SelectLaneMaterial(lLastPicked->GetNodeInfoIndex(0),lLastPicked->GetNodeInfoIndex(1),lLastPicked->GetNodeInfoIndex(2),lLastPicked->GetNodeInfoIndex(3));
				break;
			case LANE_VISIBILITY_NODE:
				mRoadTree->SelectLaneVisibility(lLastPicked->GetNodeInfoIndex(0),lLastPicked->GetNodeInfoIndex(1),lLastPicked->GetNodeInfoIndex(2),lLastPicked->GetNodeInfoIndex(3));
				break;
			case LANE_SPEED_NODE:
				mRoadTree->SelectLaneSpeed(lLastPicked->GetNodeInfoIndex(0),lLastPicked->GetNodeInfoIndex(1),lLastPicked->GetNodeInfoIndex(2),lLastPicked->GetNodeInfoIndex(3));
				break;
			case LANE_ACCESS_NODE:
				mRoadTree->SelectLaneAccess(lLastPicked->GetNodeInfoIndex(0),lLastPicked->GetNodeInfoIndex(1),lLastPicked->GetNodeInfoIndex(2),lLastPicked->GetNodeInfoIndex(3));
				break;
			case LANE_HEIGHT_NODE:
				mRoadTree->SelectLaneHeight(lLastPicked->GetNodeInfoIndex(0),lLastPicked->GetNodeInfoIndex(1),lLastPicked->GetNodeInfoIndex(2),lLastPicked->GetNodeInfoIndex(3));
				break;
			case OBJECT_NODE:
				mRoadTree->SelectObject(lLastPicked->GetNodeInfoIndex(0),lLastPicked->GetNodeInfoIndex(1));
				break;
			case SIGNAL_NODE:
				mRoadTree->SelectSignal(lLastPicked->GetNodeInfoIndex(0),lLastPicked->GetNodeInfoIndex(1));
				break;
			case JUNCTION_NODE:
				mRoadTree->SelectJunction(lLastPicked->GetNodeInfoIndex(0));
				break;
			}
		}
		else
		{
			mRoadTree->SelectNone();
		}
	}
}

/**
 * Method called when the road is recalculated
 * Used to regenerate the geometry and helpers
 *
 * @param index Index of the road that is recalculated
 */
void QOSGWidget::OnRoadRecalculated(unsigned int index)
{
	// Redraw the recalculated road and it's chord line
	mOsgMain->RedrawRoad(index);
	mOsgMain->RedrawRoadChordLine(index);
}