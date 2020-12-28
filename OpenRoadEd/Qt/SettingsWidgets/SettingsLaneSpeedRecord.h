#ifndef SETTINGSLANESPEEDRECORD_H
#define SETTINGSLANESPEEDRECORD_H


#include <QtWidgets>
#include <QtGui/QtGui>

#include "../../OpenDrive/Lane.h"

/**
 * Class that holds all the properties for the LANE_SPEED record
 *
 */
class SettingsLaneSpeedRecord : public QWidget
{
	Q_OBJECT
public:
	/**
	 * Initializes the properties panel and the UI elements
	 */
	SettingsLaneSpeedRecord(QWidget *parent = 0);

	/**
	 * Loads the data for a given record
	 *
	 * @param laneSpeed Lane speed record whose properties are to be loaded
	 * @param minS Minimum "S" property for this record
	 * @param maxS Maximum "S" property for this record
	 */
	void LoadData(LaneSpeed *laneSpeed, double minS, double maxS);
private:
	/**
	 * Lane speed whose properties are to be displayed
	 */
	LaneSpeed *mLaneSpeed;

	/**
	 * Interface widgets
	 */
	QDoubleSpinBox *mS;
	QDoubleSpinBox *mMax;

public slots:
	/**
	 * Methods called when properties change
	 */
	void SChanged(double value);
	void MaxChanged(double value);
signals:
	/**
	 * Signal emitted when critical road items are changed
	 * that require that the road to be redrawn
	 *
	 * @param recalculateRoad Set to true if geometry records have to be recalculated (usualy true for this record)
	 */
	void RoadLaneSpeedChanged(bool recalculateRoad);
};

#endif