#ifndef SETTINGSLATERALPROFILESUPER_H
#define SETTINGSLATERALPROFILESUPER_H


#include <QtGui/QWidget>
#include <QtGui/QtGui>

#include "../../OpenDrive/Road.h"

/**
 * Class that holds all the properties for the SUPERELEVATION record
 *
 */
class SettingsLateralProfileSuper : public QWidget
{
	Q_OBJECT
public:
	/**
	 * Initializes the properties panel and the UI elements
	 */
	SettingsLateralProfileSuper(QWidget *parent = 0);

	/**
	 * Loads the data for a given record
	 *
	 * @param superElevation Superelevation record whose properties are to be loaded
	 * @param minS Minimum "S" property for this record
	 * @param maxS Maximum "S" property for this record
	 */
	void LoadData(SuperElevation *superElevation, double minS, double maxS);
private:
	/**
	 * Superelevation whose properties are to be displayed
	 */
	SuperElevation *mSuperElevation;

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
	void RoadSuperElevationChanged(bool recalculateRoad);
};

#endif