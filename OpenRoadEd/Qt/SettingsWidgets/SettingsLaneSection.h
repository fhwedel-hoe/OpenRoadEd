#ifndef SETTINGSLANESECTION_H
#define SETTINGSLANESECTION_H


#include <QtGui/QWidget>
#include <QtGui/QtGui>

#include "../../OpenDrive/Lane.h"

/**
 * Class that holds all the properties for the LANE_SECTION record
 *
 */
class SettingsLaneSection : public QWidget
{
	Q_OBJECT
public:
	/**
	 * Initializes the properties panel and the UI elements
	 */
	SettingsLaneSection(QWidget *parent = 0);

	/**
	 * Loads the data for a given record
	 *
	 * @param laneSection Lane section record whose properties are to be loaded
	 * @param minS Minimum "S" property for this record
	 * @param maxS Maximum "S" property for this record
	 * @param first Set to true if it's the first lane section on the road
	 */
	void LoadData(LaneSection *laneSection, double minS, double maxS, bool first);
private:
	/**
	 * Lane section whose properties are to be displayed
	 */
	LaneSection *mLaneSection;

	/**
	 * Interface widgets
	 */
	QDoubleSpinBox *mS;

public slots:
	/**
	 * Methods called when properties change
	 */
	void SChanged(double value);
signals:
	/**
	 * Signal emitted when critical road items are changed
	 * that require that the road to be redrawn
	 *
	 * @param recalculateRoad Set to true if geometry records have to be recalculated (usualy true for this record)
	 */
	void RoadLaneSectionChanged(bool recalculateRoad);
};

#endif