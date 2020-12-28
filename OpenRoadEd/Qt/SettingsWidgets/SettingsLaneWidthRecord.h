#ifndef SETTINGSLANEWIDTHRECORD_H
#define SETTINGSLANEWIDTHRECORD_H


#include <QtWidgets>
#include <QtGui/QtGui>

#include "../../OpenDrive/Lane.h"

/**
 * Class that holds all the properties for the LANE_WIDTH record
 *
 */
class SettingsLaneWidthRecord : public QWidget
{
	Q_OBJECT
public:
	/**
	 * Initializes the properties panel and the UI elements
	 */
	SettingsLaneWidthRecord(QWidget *parent = 0);

	/**
	 * Loads the data for a given record
	 *
	 * @param laneWidth Lane width record whose properties are to be loaded
	 * @param minS Minimum "S" property for this record
	 * @param maxS Maximum "S" property for this record
	 */
	void LoadData(LaneWidth *laneWidth, double minS, double maxS);
private:
	/**
	 * Lane width whose properties are to be displayed
	 */
	LaneWidth *mLaneWidth;

	/**
	 * Interface widgets
	 */
	QDoubleSpinBox *mS;
	QDoubleSpinBox *mA;
	QDoubleSpinBox *mB;
	QDoubleSpinBox *mC;
	QDoubleSpinBox *mD;

public slots:
	/**
	 * Methods called when properties change
	 */
	void SChanged(double value);
	void AChanged(double value);
	void BChanged(double value);
	void CChanged(double value);
	void DChanged(double value);
signals:
	/**
	 * Signal emitted when critical road items are changed
	 * that require that the road to be redrawn
	 *
	 * @param recalculateRoad Set to true if geometry records have to be recalculated (usualy true for this record)
	 */
	void RoadLaneWidthChanged(bool recalculateRoad);
};

#endif