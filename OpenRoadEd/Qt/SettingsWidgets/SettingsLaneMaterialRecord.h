#ifndef SETTINGSLANEMATERIALRECORD_H
#define SETTINGSLANEMATERIALRECORD_H


#include <QtGui/QWidget>
#include <QtGui/QtGui>

#include "../../OpenDrive/Lane.h"

/**
 * Class that holds all the properties for the LANE_MATERIAL record
 *
 */
class SettingsLaneMaterialRecord : public QWidget
{
	Q_OBJECT
public:
	/**
	 * Initializes the properties panel and the UI elements
	 */
	SettingsLaneMaterialRecord(QWidget *parent = 0);

	/**
	 * Loads the data for a given record
	 *
	 * @param laneMaterial Lane material record whose properties are to be loaded
	 * @param minS Minimum "S" property for this record
	 * @param maxS Maximum "S" property for this record
	 */
	void LoadData(LaneMaterial *laneMaterial, double minS, double maxS);
private:
	/**
	 * Lane material whose properties are to be displayed
	 */
	LaneMaterial *mLaneMaterial;

	/**
	 * Interface widgets
	 */
	QDoubleSpinBox *mS;
	QLineEdit *mSurface;
	QDoubleSpinBox *mFriction;
	QDoubleSpinBox *mRoughness;

public slots:
	/**
	 * Methods called when properties change
	 */
	void SChanged(double value);
	void SurfaceChanged();
	void FrictionChanged(double value);
	void RoughnessChanged(double value);
signals:
	/**
	 * Signal emitted when critical road items are changed
	 * that require that the road to be redrawn
	 *
	 * @param recalculateRoad Set to true if geometry records have to be recalculated (usualy true for this record)
	 */
	void RoadLaneMaterialChanged(bool recalculateRoad);

};

#endif