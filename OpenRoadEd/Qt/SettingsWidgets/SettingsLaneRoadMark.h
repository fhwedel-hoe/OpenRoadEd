#ifndef SETTINGSLANEROADMARK_H
#define SETTINGSLANEROADMARK_H


#include <QtWidgets>
#include <QtGui/QtGui>

#include "../../OpenDrive/Lane.h"

/**
 * Class that holds all the properties for the LANE_ROAD_MARK record
 *
 */
class SettingsLaneRoadMark : public QWidget
{
	Q_OBJECT
public:
	/**
	 * Initializes the properties panel and the UI elements
	 */
	SettingsLaneRoadMark(QWidget *parent = 0);

	/**
	 * Loads the data for a given record
	 *
	 * @param laneRoadMark Lane road mark record whose properties are to be loaded
	 * @param minS Minimum "S" property for this record
	 * @param maxS Maximum "S" property for this record
	 */
	void LoadData(LaneRoadMark *laneRoadMark, double minS, double maxS);
private:
	/**
	 * Lane road mark whose properties are to be displayed
	 */
	LaneRoadMark *mRoadMark;

	/**
	 * Interface widgets
	 */
	QDoubleSpinBox *mS;
	QComboBox *mType;
	QComboBox *mWeight;
	QComboBox *mColor;

	QDoubleSpinBox *mWidth;
	QComboBox *mLaneChange;

public slots:
	/**
	 * Methods called when properties change
	 */
	void SChanged(double value);
	void TypeChanged(const QString & text);
	void WeightChanged(const QString & text);
	void ColorChanged(const QString & text);
	void WidthChanged(double value);
	void LaneChangeChanged(const QString & text);
signals:
	/**
	 * Signal emitted when critical road items are changed
	 * that require that the road to be redrawn
	 *
	 * @param recalculateRoad Set to true if geometry records have to be recalculated (usualy true for this record)
	 */
	void RoadLaneRoadMarkChanged(bool recalculateRoad);

};

#endif