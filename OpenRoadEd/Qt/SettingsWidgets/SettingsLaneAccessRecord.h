#ifndef SETTINGSLANEACCESSRECORD_H
#define SETTINGSLANEACCESSRECORD_H


#include <QtGui/QWidget>
#include <QtGui/QtGui>

#include "../../OpenDrive/Lane.h"

/**
 * Class that holds all the properties for the LANE_ACCESS record
 *
 */
class SettingsLaneAccessRecord : public QWidget
{
	Q_OBJECT
public:
	/**
	 * Initializes the properties panel and the UI elements
	 */
	SettingsLaneAccessRecord(QWidget *parent = 0);

	/**
	 * Loads the data for a given record
	 *
	 * @param laneAccess Lane access record whose properties are to be loaded
	 * @param minS Minimum "S" property for this record
	 * @param maxS Maximum "S" property for this record
	 */
	void LoadData(LaneAccess *laneAccess, double minS, double maxS);
private:
	/**
	 * Lane access whose properties are to be displayed
	 */
	LaneAccess *mLaneAccess;

	/**
	 * Interface widgets
	 */
	QDoubleSpinBox *mS;
	QComboBox *mRestriction;

public slots:
	/**
	 * Methods called when properties change
	 */
	void SChanged(double value);
	void RestrictionChanged(const QString &text);
signals:
	/**
	 * Signal emitted when critical road items are changed
	 * that require that the road to be redrawn
	 *
	 * @param recalculateRoad Set to true if geometry records have to be recalculated (usualy true for this record)
	 */
	void RoadLaneAccessChanged(bool recalculateRoad);
};

#endif