#ifndef SETTINGSLATERALPROFILECROSSFALL_H
#define SETTINGSLATERALPROFILECROSSFALL_H


#include <QtWidgets>
#include <QtGui/QtGui>

#include "../../OpenDrive/Road.h"

/**
 * Class that holds all the properties for the CROSSFALL record
 *
 */
class SettingsLateralProfileCrossfall : public QWidget
{
	Q_OBJECT
public:
	/**
	 * Initializes the properties panel and the UI elements
	 */
	SettingsLateralProfileCrossfall(QWidget *parent = 0);

	/**
	 * Loads the data for a given record
	 *
	 * @param crossfall Crossfall record whose properties are to be loaded
	 * @param minS Minimum "S" property for this record
	 * @param maxS Maximum "S" property for this record
	 */
	void LoadData(Crossfall *crossfall, double minS, double maxS);
private:
	/**
	 * Crossfall whose properties are to be displayed
	 */
	Crossfall *mCrossfall;

	/**
	 * Interface widgets
	 */
	QDoubleSpinBox *mS;
	QDoubleSpinBox *mA;
	QDoubleSpinBox *mB;
	QDoubleSpinBox *mC;
	QDoubleSpinBox *mD;
	QComboBox *mSide;

public slots:
	/**
	 * Methods called when properties change
	 */
	void SChanged(double value);
	void AChanged(double value);
	void BChanged(double value);
	void CChanged(double value);
	void DChanged(double value);
	void SideChanged(const QString & text);
signals:
	/**
	 * Signal emitted when critical road items are changed
	 * that require that the road to be redrawn
	 *
	 * @param recalculateRoad Set to true if geometry records have to be recalculated (usualy true for this record)
	 */
	void RoadCrossfallChanged(bool recalculateRoad);
};

#endif