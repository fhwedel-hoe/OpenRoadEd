#ifndef SETTINGSLANEHEIGHTRECORD_H
#define SETTINGSLANEHEIGHTRECORD_H


#include <QtWidgets>
#include <QtGui/QtGui>

#include "../../OpenDrive/Lane.h"

/**
 * Class that holds all the properties for the LANE_HEIGHT record
 *
 */
class SettingsLaneHeightRecord : public QWidget
{
	Q_OBJECT
public:
	/**
	 * Initializes the properties panel and the UI elements
	 */
	SettingsLaneHeightRecord(QWidget *parent = 0);

	/**
	 * Loads the data for a given record
	 *
	 * @param laneHeight Lane height record whose properties are to be loaded
	 * @param minS Minimum "S" property for this record
	 * @param maxS Maximum "S" property for this record
	 */
	void LoadData(LaneHeight *laneHeight, double minS, double maxS);
private:
	/**
	 * Lane height whose properties are to be displayed
	 */
	LaneHeight *mLaneHeight;

	/**
	 * Interface widgets
	 */
	QDoubleSpinBox *mS;
	QDoubleSpinBox *mInner;
	QDoubleSpinBox *mOuter;

public slots:
	/**
	 * Methods called when properties change
	 */
	void SChanged(double value);
	void InnerChanged(double value);
	void OuterChanged(double value);
signals:
	/**
	 * Signal emitted when critical road items are changed
	 * that require that the road to be redrawn
	 *
	 * @param recalculateRoad Set to true if geometry records have to be recalculated (usualy true for this record)
	 */
	void RoadLaneHeightChanged(bool recalculateRoad);
};

#endif