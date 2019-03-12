#ifndef SETTINGSGEOMETRYTURN_H
#define SETTINGSGEOMETRYTURN_H


#include <QtGui/QWidget>
#include <QtGui/QtGui>

#include "../../OpenDrive/RoadGeometry.h"

/**
 * Class that holds all the properties for the GEOMETRY_TURN record
 *
 */
class SettingsGeometryTurn : public QWidget
{
	Q_OBJECT
public:
	/**
	 * Initializes the properties panel and the UI elements
	 */
	SettingsGeometryTurn(QWidget *parent = 0);

	/**
	 * Loads the data for a given record
	 *
	 * @param block Geometry block record whose properties are to be loaded
	 * @param first Set to true if it is the first record for this road
	 */
	void LoadData(GeometryBlock *block);

	/**
	 * Makes this record the first for the road, thus enabling controls that only
	 * the first record has, such as the X and Y coordinates, which are otherwise
	 * computed automatically and are disabled
	 */
	void SetFirst(bool first);

private:
	/**
	 * Geometry record whose properties are to be displayed
	 */
	GeometryBlock *mTurn;

	/**
	 * Interface widgets
	 */
	QLineEdit *mS;
	QDoubleSpinBox *mX;
	QDoubleSpinBox *mY;
	QDoubleSpinBox *mHeading;
	QDoubleSpinBox *mArcCurve;
	QDoubleSpinBox *mArcLength;
	QDoubleSpinBox *mSpiral1Length;
	QDoubleSpinBox *mSpiral2Length;

public slots:
	/**
	 * Methods called when properties change
	 */
	void SChanged();
	void XChanged(double value);
	void YChanged(double value);
	void HeadingChanged(double value);
	void ArcCurveChanged(double value);
	void ArcLengthChanged(double value);
	void Spiral1LengthChanged(double value);
	void Spiral2LengthChanged(double value);
signals:
	/**
	 * Signal emitted when critical road items are changed
	 * that require that the road to be redrawn
	 *
	 * @param recalculateRoad Set to true if geometry records have to be recalculated (usualy true for this record)
	 */
	void RoadGeometryChanged(bool recalculateRoad);
};


#endif