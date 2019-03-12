#ifndef SETTINGSROAD_H
#define SETTINGSROAD_H


#include <QtGui/QWidget>
#include <QtGui/QtGui>

#include "../../OpenDrive/OpenDrive.h"
#include "../../OpenDrive/Road.h"

#include "../ToolsDialogs/GetRoadDialog.h"

/**
 * Class that holds all the properties for the ROAD record
 *
 */
class SettingsRoad : public QWidget
{
	Q_OBJECT
public:
	/**
	 * Initializes the properties panel and the UI elements
	 */
	SettingsRoad(OpenDrive *openDrive);

	/**
	 * Loads the data for a given record
	 *
	 * @param road Road record whose properties are to be loaded
	 */
	void LoadData(Road *road);
private:
	/**
	 * OpenDrive reference for "Select Road" dialog
	 */
	OpenDrive *mOpenDrive;
	/**
	 * Road whose properties are to be displayed
	 */
	Road *mRoad;

	/**
	 * Interface widgets
	 */
	QLineEdit *mName;
	QLineEdit *mLength;
	QLineEdit *mId;
	QLineEdit *mJunction;

	QGroupBox *mPredecessor;
	QLineEdit *mPredecessorId;
	QToolButton *mBrowsePredecessor;
	QComboBox *mPredecessorType;
	QComboBox *mPredecessorContactPoint;

	QGroupBox *mSuccessor;
	QLineEdit *mSuccessorId;
	QToolButton *mBrowseSuccessor;
	QComboBox *mSuccessorType;
	QComboBox *mSuccessorContactPoint;

	QGroupBox *mNeighbor1;
	QLineEdit *mNeighbor1Id;
	QToolButton *mBrowseNeighbor1;
	QComboBox *mNeighbor1Side;
	QComboBox *mNeighbor1Direction;

	QGroupBox *mNeighbor2;
	QLineEdit *mNeighbor2Id;
	QToolButton *mBrowseNeighbor2;
	QComboBox *mNeighbor2Side;
	QComboBox *mNeighbor2Direction;
public slots:
	
	/**
	 * Methods used to select roads from a list
	 */
	void BrowseForPredecessor();
	void BrowseForSuccessor();
	void BrowseForNeighbor1();
	void BrowseForNeighbor2();

	/**
	 * Methods called when properties change
	 */
	void NameChanged();
	void LengthChanged();
	void IdChanged();
	void JunctionChanged();
	
	void PredecessorChanged(bool on);
	void PredecessorIdChanged();
	void PredecessorTypeChanged(const QString & text);
	void PredecessorContactPointChanged(const QString & text);

	void SuccessorChanged(bool on);
	void SuccessorIdChanged();
	void SuccessorTypeChanged(const QString & text);
	void SuccessorContactPointChanged(const QString & text);

	void Neighbor1Changed(bool on);
	void Neighbor1IdChanged();
	void Neighbor1SideChanged(const QString & text);
	void Neighbor1DirectionChanged(const QString & text);

	void Neighbor2Changed(bool on);
	void Neighbor2IdChanged();
	void Neighbor2SideChanged(const QString & text);
	void Neighbor2DirectionChanged(const QString & text);
};

#endif