#ifndef SETTINGSLANEVISIBILITYRECORD_H
#define SETTINGSLANEVISIBILITYRECORD_H


#include <QtGui/QWidget>
#include <QtGui/QtGui>

#include "../../OpenDrive/Lane.h"

/**
 * Class that holds all the properties for the LANE_VISIBILITY record
 *
 */
class SettingsLaneVisibilityRecord : public QWidget
{
	Q_OBJECT
public:
	/**
	 * Initializes the properties panel and the UI elements
	 */
	SettingsLaneVisibilityRecord(QWidget *parent = 0);

	/**
	 * Loads the data for a given record
	 *
	 * @param laneVisibility Lane visibility record whose properties are to be loaded
	 * @param minS Minimum "S" property for this record
	 * @param maxS Maximum "S" property for this record
	 */
	void LoadData(LaneVisibility *laneVisibility, double minS, double maxS);
private:
	/**
	 * Lane visibility whose properties are to be displayed
	 */
	LaneVisibility *mLaneVisibility;

	/**
	 * Interface widgets
	 */
	QDoubleSpinBox *mS;
	QDoubleSpinBox *mForward;
	QDoubleSpinBox *mBack;
	QDoubleSpinBox *mLeft;
	QDoubleSpinBox *mRight;

public slots:
	/**
	 * Methods called when properties change
	 */
	void SChanged(double value);
	void ForwardChanged(double value);
	void BackChanged(double value);
	void LeftChanged(double value);
	void RightChanged(double value);
signals:
	/**
	 * Signal emitted when critical road items are changed
	 * that require that the road to be redrawn
	 *
	 * @param recalculateRoad Set to true if geometry records have to be recalculated (usualy true for this record)
	 */
	void RoadLaneVisibilityChanged(bool recalculateRoad);
};

#endif