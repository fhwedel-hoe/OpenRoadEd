#ifndef SETTINGSROADTYPERECORD_H
#define SETTINGSROADTYPERECORD_H


#include <QtWidgets>
#include <QtGui/QtGui>

#include "../../OpenDrive/Road.h"

/**
 * Class that holds all the properties for the ROAD_TYPE record
 *
 */
class SettingsRoadTypeRecord : public QWidget
{
	Q_OBJECT
public:
	/**
	 * Initializes the properties panel and the UI elements
	 */
	SettingsRoadTypeRecord(QWidget *parent = 0);

	/**
	 * Loads the data for a given record
	 *
	 * @param roadType Road type record whose properties are to be loaded
	 */
	void LoadData(RoadType *roadType, double minS, double maxS);
private:
	/**
	 * Road whose properties are to be displayed
	 */
	RoadType *mRoadType;

	/**
	 * Interface widgets
	 */
	QDoubleSpinBox *mS;
	QComboBox *mType;

public slots:
	/**
	 * Methods called when properties change
	 */
	void SChanged(double value);
	void TypeChanged(const QString &text);
signals:
	/**
	 * Signal emitted when critical road items are changed
	 * that require that the road to be redrawn
	 *
	 * @param recalculateRoad Set to true if geometry records have to be recalculated (usualy true for this record)
	 */
	void RoadRoadTypeChanged(bool recalculateRoad);
};

#endif
