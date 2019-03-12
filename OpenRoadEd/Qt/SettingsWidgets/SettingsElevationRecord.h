#ifndef SETTINGSELEVATIONRECORD_H
#define SETTINGSELEVATIONRECORD_H


#include <QtGui/QWidget>
#include <QtGui/QtGui>

#include "../../OpenDrive/Road.h"

/**
 * Class that holds all the properties for the ELEVATION record
 *
 */
class SettingsElevationRecord : public QWidget
{
	Q_OBJECT
public:
	/**
	 * Initializes the properties panel and the UI elements
	 */
	SettingsElevationRecord(QWidget *parent = 0);

	/**
	 * Loads the data for a given record
	 *
	 * @param elevation Elevation record whose properties are to be loaded
	 * @param minS Minimum "S" property for this record
	 * @param maxS Maximum "S" property for this record
	 */
	void LoadData(Elevation *elevation, double minS, double maxS);
private:
	/**
	 * Elevation record whose properties are to be displayed
	 */
	Elevation *mElevation;

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
	 * @param recalculateRoad Set to true if geometry records have to be recalculated
	 */
	void RoadElevationChanged(bool recalculateRoad);
};

#endif