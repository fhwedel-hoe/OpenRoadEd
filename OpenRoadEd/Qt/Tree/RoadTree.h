#ifndef OPENDRIVETREE_H
#define OPENDRIVETREE_H


#include <QtWidgets>
#include <QtGui/QtGui>
#include <QtCore/QSettings>

#include "../../OpenDrive/OpenDrive.h"
#include "../../OpenDrive/Road.h"
#include "../../OpenDrive/Lane.h"
#include "../../OpenDrive/RoadGeometry.h"
#include "../../OpenDrive/OtherStructures.h"

#include "RoadTreeItems.h"

/**
 * Class used to store indices and the type of the currently selected object
 * Those indices could be used to access the object in the OpenDrive structure
 *
 *
 *
 */
class Selection
{
public:
	/**
	 * Constructor
	 */
	Selection();

	/**
	 * Copy constructor
	 */
	Selection(const Selection& selection);

	/**
	 * Assignment operator overload
	 */
	Selection& operator=(Selection const& rhs);

	/**
	 * Operator overload used to access a specific index from the array using the class object name
	 */
	unsigned int& operator[](int index);

	/**
	 * Sets the type for the selected object
	 *
	 * @param type Type for the object, which is being selected
	 */
	void SetType(RoadTreeItemType type);

	/**
	 * Adds an index to the back of the index array
	 *
	 * @param index Index to be added
	 */
	void AddIndex(unsigned int index);

	/**
	 * Adds an index to the front of the index array
	 *
	 * @param index Index to be added
	 */
	void AddIndexFront(unsigned int index);

	/**
	 * Getter for the type
	 */
	RoadTreeItemType GetType();

	/**
	 * Getter for a single index from the array
	 *
	 * @param index Index of the index from the array
	 */
	unsigned int GetIndex(int index);

	/**
	 * Clears the index array and resets the type
	 */
	void Reset();

private:

	/**
	 * Type of the item
	 */
	RoadTreeItemType mType;

	/**
	 * Vector of indices that are used to access that object in the OpenDrive structure
	 */
	vector<unsigned int> mIndices;
};


/**
 * Road tree panel.
 * Holds a tree view widget of the OpenDrive structure
 * Each item can be clicked which issues a "selected" signal
 * For all the OpenDrive record types, there is an Add method, which takes the indices to respective object
 * in the OpenDrive structure and creates a new item in the road tree.
 * For all the OpenDrive record types, there is a Delete method, which removes the selected item from the road tree.
 * For all the OpenDrive record types, there is a Select method, used to select objects programatically
 * For all the OpenDrive record types, there is a Get Method, which returns the road tree item, given the indices
 * For all the OpenDrive record types, there is a Get Real Method, which returns the OpenDrive object, given the indices
 * For all the OpenDrive record types, there is a Get Real Method, which returns the OpenDrive object, using the indices
 * of the currently selected object
 *
 */
class RoadTree : public QWidget
{
	Q_OBJECT

public:

	/**
	 * Constructor
	 */
	RoadTree(QWidget *parent = 0);

	/**
	 * Initializes the road tree and saves the OpenDrive structure reference
	 *
	 * @param openDrive Pointer to the OpenDrive structure
	 */
	void Init(OpenDrive *openDrive);

	/**
	 * Loads the OpenDrive structure and fills in the road tree
	 *
	 * @param openDrive Pointer to the OpenDrive structure
	 */
	void LoadStructure(OpenDrive *openDrive);

	/**
	 * Gets the current selection object
	 *
	 * @return Returns the selection object, which holds the type and indices of the selected item
	 */
	Selection *GetSelection();

	
	/**
	 * Fiils in the selection object given an item from the tree
	 *
	 * @return item Item used to fill in the selection object
	 */
	void FillInSelectionObject(RoadTreeItemBase *item);

	/**
	 * Shifts the indices stored in the item when a new item is inserted or deleted from the tree
	 *
	 * @param container Container that holds the item that is to be deleted
	 * @param startingIndex Index of the item where the shift starts
	 * @param delta Shifting step (can be negative)
	 */
	void ShiftIndexes(QTreeWidgetItem *container, int startingIndex, int delta);

	/**
	 * Clears the tree, removing all the items
	 */
	void ClearTree();

	/**
	 * Two methods used to add a new record to the road tree. Second method also returns the created item
	 *
	 * @param indexXXX Index or sequence of indices of the corresponding object in OpenDrive structure
	 * @param YYY Reference to the pointer that will hold the created road tree item
	 * @param select Flag that determines if the newly created object will be automatically selected
	 */
	void AddRoad(int index, bool select);
	void AddRoad(int index, RTIRoad *&road, bool select);
	void AddRoadType(int indexRoad, int indexRoadType, bool select);
	void AddRoadType(int indexRoad, int indexRoadType, RoadTreeItem *&roadType, bool select);
	void AddGeometry(int indexRoad, int indexGeometry, bool select);
	void AddGeometry(int indexRoad, int indexGeometry, RoadTreeItem *&geometry, bool select);
	void AddElevation(int indexRoad, int indexElevation, bool select);
	void AddElevation(int indexRoad, int indexElevation, RoadTreeItem *&elevation, bool select);
	void AddSuperElevation(int indexRoad, int indexSuperElevation, bool select);
	void AddSuperElevation(int indexRoad, int indexSuperElevation, RoadTreeItem *&superElevation, bool select);
	void AddCrossfall(int indexRoad, int indexCrossfall, bool select);
	void AddCrossfall(int indexRoad, int indexCrossfall, RoadTreeItem *&crossfall, bool select);
	void AddLaneSection(int indexRoad, int indexLaneSection, bool select);
	void AddLaneSection(int indexRoad, int indexLaneSection, RTILaneSection *&laneSection, bool select);
	void AddLaneLeft(int indexRoad, int indexLaneSection, int indexLane, bool select);
	void AddLaneLeft(int indexRoad, int indexLaneSection, int indexLane, RTILane *&lane, bool select);
	void AddLaneCenter(int indexRoad, int indexLaneSection, int indexLane, bool select);
	void AddLaneCenter(int indexRoad, int indexLaneSection, int indexLane, RTILane *&lane, bool select);
	void AddLaneRight(int indexRoad, int indexLaneSection, int indexLane, bool select);
	void AddLaneRight(int indexRoad, int indexLaneSection, int indexLane, RTILane *&lane, bool select);
	void AddLaneWidth(int indexRoad, int indexLaneSection, int indexLane, int indexLaneWidth, bool select);
	void AddLaneWidth(int indexRoad, int indexLaneSection, int indexLane, int indexLaneWidth, RoadTreeItem *&laneWidth, bool select);
	void AddLaneRoadMark(int indexRoad, int indexLaneSection, int indexLane, int indexLaneRoadMark, bool select);
	void AddLaneRoadMark(int indexRoad, int indexLaneSection, int indexLane, int indexLaneRoadMark, RoadTreeItem *&laneRoadMark, bool select);
	void AddLaneMaterial(int indexRoad, int indexLaneSection, int indexLane, int indexLaneMaterial, bool select);
	void AddLaneMaterial(int indexRoad, int indexLaneSection, int indexLane, int indexLaneMaterial, RoadTreeItem *&laneMaterial, bool select);
	void AddLaneVisibility(int indexRoad, int indexLaneSection, int indexLane, int indexLaneVisibility, bool select);
	void AddLaneVisibility(int indexRoad, int indexLaneSection, int indexLane, int indexLaneVisibility, RoadTreeItem *&laneVisibility, bool select);
	void AddLaneSpeed(int indexRoad, int indexLaneSection, int indexLane, int indexLaneSpeed, bool select);
	void AddLaneSpeed(int indexRoad, int indexLaneSection, int indexLane, int indexLaneSpeed, RoadTreeItem *&laneSpeed, bool select);
	void AddLaneAccess(int indexRoad, int indexLaneSection, int indexLane, int indexLaneAccess, bool select);
	void AddLaneAccess(int indexRoad, int indexLaneSection, int indexLane, int indexLaneAccess, RoadTreeItem *&laneAccess, bool select);
	void AddLaneHeight(int indexRoad, int indexLaneSection, int indexLane, int indexLaneHeight, bool select);
	void AddLaneHeight(int indexRoad, int indexLaneSection, int indexLane, int indexLaneHeight, RoadTreeItem *&laneHeight, bool select);
	void AddObject(int indexRoad, int indexObject, bool select);
	void AddObject(int indexRoad, int indexObject, RoadTreeItem *&object, bool select);
	void AddSignal(int indexRoad, int indexSignal, bool select);
	void AddSignal(int indexRoad, int indexSignal, RoadTreeItem *&signal, bool select);
	void AddJunction(int index, bool select);
	void AddJunction(int index, RTIJunction *&junction, bool select);
	void AddJunctionConnection(int indexJunction, int indexConnection, bool select);
	void AddJunctionConnection(int indexJunction, int indexConnection, RTIJunctionConnection *&junctionConnection, bool select);
	void AddJunctionLaneLink(int indexJunction, int indexConnection, int indexLaneLink, bool select);
	void AddJunctionLaneLink(int indexJunction, int indexConnection, int indexLaneLink, RoadTreeItem *&junctionLaneLink, bool select);
	void AddJunctionPriority(int indexJunction, int indexPriority, bool select);
	void AddJunctionPriority(int indexJunction, int indexPriority, RoadTreeItem *&junctionPriority, bool select);
	void AddJunctionController(int indexJunction, int indexController, bool select);
	void AddJunctionController(int indexJunction, int indexController, RoadTreeItem *&junctionController, bool select);


	/**
	 * Deletes the currently selected item
	 */
	void DeleteRoad();
	void DeleteRoadType();
	void DeleteGeometry();
	void DeleteLastGeometry();
	void DeleteElevation();
	void DeleteSuperElevation();
	void DeleteCrossfall();
	void DeleteLaneSection();
	void DeleteLaneLeft();
	void DeleteLaneCenter();
	void DeleteLaneRight();
	void DeleteLaneWidth();
	void DeleteLaneRoadMark();
	void DeleteLaneMaterial();
	void DeleteLaneVisibility();
	void DeleteLaneSpeed();
	void DeleteLaneAccess();
	void DeleteLaneHeight();
	void DeleteObject();
	void DeleteSignal();
	void DeleteJunction();
	void DeleteJunctionConnection();
	void DeleteJunctionLaneLink();
	void DeleteJunctionPriority();
	void DeleteJunctionController();

	/**
	 * Selects the item in the road tree, given the indices
	 *
	 * @param indexXXX Index or sequence of indices, used to select an object
	 */
	void SelectNone();
	void SelectRoad(int index);
	void SelectRoadType(int indexRoad, int indexRoadType);
	void SelectGeometry(int indexRoad, int indexGeometry);
	void SelectElevation(int indexRoad, int indexElevation);
	void SelectSuperElevation(int indexRoad, int indexSuperElevation);
	void SelectCrossfall(int indexRoad, int indexCrossfall);
	void SelectLaneSection(int indexRoad, int indexLaneSection);
	void SelectLane(int indexRoad, int indexLaneSection, int indexLane);
	void SelectLaneWidth(int indexRoad, int indexLaneSection, int indexLane, int indexLaneWidth);
	void SelectLaneRoadMark(int indexRoad, int indexLaneSection, int indexLane, int indexLaneRoadMark);
	void SelectLaneMaterial(int indexRoad, int indexLaneSection, int indexLane, int indexLaneMaterial);
	void SelectLaneVisibility(int indexRoad, int indexLaneSection, int indexLane, int indexLaneVisibility);
	void SelectLaneSpeed(int indexRoad, int indexLaneSection, int indexLane, int indexLaneSpeed);
	void SelectLaneAccess(int indexRoad, int indexLaneSection, int indexLane, int indexLaneAccess);
	void SelectLaneHeight(int indexRoad, int indexLaneSection, int indexLane, int indexLaneHeight);
	void SelectObject(int indexRoad, int indexObject);
	void SelectSignal(int indexRoad, int indexSignal);
	void SelectJunction(int index);
	void SelectJunctionConnection(int indexJunction, int indexConnection);
	void SelectJunctionLaneLink(int indexJunction, int indexConnection, int indexLaneLink);
	void SelectJunctionPriority(int indexJunction, int indexPriority);
	void SelectJunctionController(int indexJunction, int indexController);

	/**
	 * Returns the item in the road tree, given the indices
	 *
	 * @param indexXXX Index or sequence of indices, used to select an object
	 * @return Road tree item that is to be returned
	 */
	QTreeWidgetItem* GetRoad(int index);
	QTreeWidgetItem* GetRoadType(int indexRoad, int indexRoadType);
	QTreeWidgetItem* GetGeometry(int indexRoad, int indexGeometry);
	QTreeWidgetItem* GetElevation(int indexRoad, int indexElevation);
	QTreeWidgetItem* GetSuperElevation(int indexRoad, int indexSuperElevation);
	QTreeWidgetItem* GetCrossfall(int indexRoad, int indexCrossfall);
	QTreeWidgetItem* GetLaneSection(int indexRoad, int indexLaneSection);
	QTreeWidgetItem* GetLane(int indexRoad, int indexLaneSection, int indexLane);
	QTreeWidgetItem* GetLaneWidth(int indexRoad, int indexLaneSection, int indexLane, int indexLaneWidth);
	QTreeWidgetItem* GetLaneRoadMark(int indexRoad, int indexLaneSection, int indexLane, int indexLaneRoadMark);
	QTreeWidgetItem* GetLaneMaterial(int indexRoad, int indexLaneSection, int indexLane, int indexLaneMaterial);
	QTreeWidgetItem* GetLaneVisibility(int indexRoad, int indexLaneSection, int indexLane, int indexLaneVisibility);
	QTreeWidgetItem* GetLaneSpeed(int indexRoad, int indexLaneSection, int indexLane, int indexLaneSpeed);
	QTreeWidgetItem* GetLaneAccess(int indexRoad, int indexLaneSection, int indexLane, int indexLaneAccess);
	QTreeWidgetItem* GetLaneHeight(int indexRoad, int indexLaneSection, int indexLane, int indexLaneHeight);
	QTreeWidgetItem* GetObject(int indexRoad, int indexObject);
	QTreeWidgetItem* GetSignal(int indexRoad, int indexSignal);
	QTreeWidgetItem* GetJunction(int index);
	QTreeWidgetItem* GetJunctionConnection(int indexJunction, int indexConnection);
	QTreeWidgetItem* GetJunctionLaneLink(int indexJunction, int indexConnection, int indexLaneLink);
	QTreeWidgetItem* GetJunctionPriority(int indexJunction, int indexPriority);
	QTreeWidgetItem* GetJunctionController(int indexJunction, int indexController);


	/**
	 * Returns the Open Drive structure object that is currently selected in the road tree
	 *
	 * @return OpenDrive related object from the OpenDrive structure
	 */
	Road* GetRealRoad();
	RoadType* GetRealRoadType();
	GeometryBlock* GetRealGeometry();
	Elevation* GetRealElevation();
	SuperElevation* GetRealSuperElevation();
	Crossfall* GetRealCrossfall();
	LaneSection* GetRealLaneSection();
	Lane* GetRealLane();
	LaneWidth* GetRealLaneWidth();
	LaneRoadMark* GetRealLaneRoadMark();
	LaneMaterial* GetRealLaneMaterial();
	LaneVisibility* GetRealLaneVisibility();
	LaneSpeed* GetRealLaneSpeed();
	LaneAccess* GetRealLaneAccess();
	LaneHeight* GetRealLaneHeight();
	Object* GetRealObject();
	Signal* GetRealSignal();
	Junction* GetRealJunction();
	JunctionConnection* GetRealJunctionConnection();
	JunctionLaneLink* GetRealJunctionLaneLink();
	JunctionPriorityRoad* GetRealJunctionPriority();
	JunctionController* GetRealJunctionController();

	/**
	 * Returns the OpenDrive structure object, given the indices
	 *
	 * @param indexXXX Index or sequence of indices, used to select an object
	 * @return OpenDrive related object from the OpenDrive structure
	 */
	Road* GetRealRoad(int indexRoad);
	RoadType* GetRealRoadType(int indexRoad, int indexRoadType);
	GeometryBlock* GetRealGeometry(int indexRoad, int indexGeometry);
	Elevation* GetRealElevation(int indexRoad, int indexElevation);
	SuperElevation* GetRealSuperElevation(int indexRoad, int indexSuperElevation);
	Crossfall* GetRealCrossfall(int indexRoad, int indexCrossfall);
	LaneSection* GetRealLaneSection(int indexRoad, int indexLaneSection);
	Lane* GetRealLane(int indexRoad, int indexLaneSection, int indexLane);
	LaneWidth* GetRealLaneWidth(int indexRoad, int indexLaneSection, int indexLane, int indexLaneWidth);
	LaneRoadMark* GetRealLaneRoadMark(int indexRoad, int indexLaneSection, int indexLane, int indexLaneRoadMark);
	LaneMaterial* GetRealLaneMaterial(int indexRoad, int indexLaneSection, int indexLane, int indexLaneMaterial);
	LaneVisibility* GetRealLaneVisibility(int indexRoad, int indexLaneSection, int indexLane, int indexLaneVisibility);
	LaneSpeed* GetRealLaneSpeed(int indexRoad, int indexLaneSection, int indexLane, int indexLaneSpeed);
	LaneAccess* GetRealLaneAccess(int indexRoad, int indexLaneSection, int indexLane, int indexLaneAccess);
	LaneHeight* GetRealLaneHeight(int indexRoad, int indexLaneSection, int indexLane, int indexLaneHeight);
	Object* GetRealObject(int indexRoad, int indexObject);
	Signal* GetRealSignal(int indexRoad, int indexSignal);
	Junction* GetRealJunction(int indexJunction);
	JunctionConnection* GetRealJunctionConnection(int indexJunction, int indexConnection);
	JunctionLaneLink* GetRealJunctionLaneLink(int indexJunction, int indexConnection, int indexLaneLink);
	JunctionPriorityRoad* GetRealJunctionPriority(int indexJunction, int indexPriority);
	JunctionController* GetRealJunctionController(int indexJunction, int indexController);


private:
	/**
	 * OpenDrive pointer
	 */
	OpenDrive* mOpenDrive;

	/**
	 * Tree widget
	 */
	QTreeWidget *mTreeWidget;

	/**
	 * Tov level tree item: road container
	 */
	RoadTreeItemBase *mRoadContainer;

	/**
	 * Tov level tree item: junction container
	 */
	RoadTreeItemBase *mJunctionContainer;

	/**
	 * Selection object ot hold the currently selected object type and indices
	 */
	Selection mSelection;

signals:

	/**
	 * Signals emited when a tree item is selected
	 * Signals hold the pointer to the real OpenDrive object and some parameters limitations
	 * used in the record settings panel
	 */
	void NothingSelected();
	void RoadSelected(Road *node);
	void RoadTypeSelected(RoadType *node, double minS, double maxS);
	void GeometryLineSelected(GeometryBlock *node, bool first);
	void GeometryTurnSelected(GeometryBlock *node, bool first);
	void ElevationSelected(Elevation *node, double minS, double maxS);
	void SuperElevationSelected(SuperElevation *node, double minS, double maxS);
	void CrossfallSelected(Crossfall *node, double minS, double maxS);
	void LaneSectionSelected(LaneSection *node, double minS, double maxS, bool first);
	void LaneSelected(Lane *node);
	void LaneWidthSelected(LaneWidth *node, double minS, double maxS);
	void LaneRoadMarkSelected(LaneRoadMark *node, double minS, double maxS);
	void LaneMaterialSelected(LaneMaterial *node, double minS, double maxS);
	void LaneVisibilitySelected(LaneVisibility *node, double minS, double maxS);
	void LaneSpeedSelected(LaneSpeed *node, double minS, double maxS);
	void LaneAccessSelected(LaneAccess *node, double minS, double maxS);
	void LaneHeightSelected(LaneHeight *node, double minS, double maxS);
	void ObjectSelected(Object *node);
	void SignalSelected(Signal *node);
	void JunctionSelected(Junction *node);
	void JunctionConnectionSelected(JunctionConnection *node);
	void JunctionLaneLinkSelected(JunctionLaneLink *node);
	void JunctionPrioritySelected(JunctionPriorityRoad *node);
	void JunctionControllerSelected(JunctionController *node);

	/**
	 * Signals emited when a road is recalculated
	 */
	void RoadRecalculated(unsigned int indexRoad);

public slots:

	/**
	 * Method called when the tree item color coding is toggled
	 */
	void ColorCode(bool enable);

private slots:

	/**
	 * Method called when an item in the road tree is clicked
	 */
	void OnItemActivation( QTreeWidgetItem * item, int column);
	void OnItemSelected();

	/**
	 * Method called when one of the rods is wiether changed in the settings panel or a new tree item is added
	 */
	void OnCurrentRoadChanged(bool geometryChanged);	
};


#endif
