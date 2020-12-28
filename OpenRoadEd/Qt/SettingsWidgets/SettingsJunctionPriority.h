#ifndef SETTINGSJUNCTIONPRIORITY_H
#define SETTINGSJUNCTIONPRIORITY_H


#include <QtWidgets>
#include <QtGui/QtGui>

#include "../../OpenDrive/Junction.h"

/**
 * Class that holds all the properties for the JUNCTION_PRIORITY record
 *
 */
class SettingsJunctionPriority : public QWidget
{
	Q_OBJECT
public:
	/**
	 * Initializes the properties panel and the UI elements
	 */
	SettingsJunctionPriority(QWidget *parent = 0);

	/**
	 * Loads the data for a given record
	 *
	 * @param junctionPriority Junction priority record whose properties are to be loaded
	 */
	void LoadData(JunctionPriorityRoad *junctionPriority);
private:
	/**
	 * Junction priority record whose properties are to be displayed
	 */
	JunctionPriorityRoad *mJunctionPriority;

	/**
	 * Interface widgets
	 */
	QLineEdit *mHigh;
	QLineEdit *mLow;

public slots:
	/**
	 * Methods called when properties change
	 */
	void HighChanged();
	void LowChanged();
};

#endif