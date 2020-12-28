#ifndef SETTINGSLANE_H
#define SETTINGSLANE_H


#include <QtWidgets>
#include <QtGui/QtGui>

#include "../../OpenDrive/Lane.h"

/**
 * Class that holds all the properties for the LANE record
 *
 */
class SettingsLane : public QWidget
{
	Q_OBJECT
public:
	/**
	 * Initializes the properties panel and the UI elements
	 */
	SettingsLane(QWidget *parent = 0);

	/**
	 * Loads the data for a given record
	 *
	 * @param lane Lane record whose properties are to be loaded
	 */
	void LoadData(Lane *lane);
private:
	/**
	 * Lane whose properties are to be displayed
	 */
	Lane *mLane;

	/**
	 * Interface widgets
	 */
	QSpinBox *mId;
	QComboBox *mType;
	QComboBox *mLevel;

	QGroupBox *mPredecessor;
	QSpinBox *mPredecessorId;

	QGroupBox *mSuccessor;
	QSpinBox *mSuccessorId;
public slots:
	/**
	 * Methods called when properties change
	 */
	void IdChanged(int value);
	void TypeChanged(const QString & text);
	void LevelChanged(const QString & text);

	void PredecessorChanged(bool on);
	void PredecessorIdChanged(int value);

	void SuccessorChanged(bool on);
	void SuccessorIdChanged(int value);
signals:
	/**
	 * Signal emitted when critical road items are changed
	 * that require that the road to be redrawn
	 *
	 * @param recalculateRoad Set to true if geometry records have to be recalculated (usualy true for this record)
	 */
	void RoadLaneChanged(bool recalculateRoad);

};


#endif