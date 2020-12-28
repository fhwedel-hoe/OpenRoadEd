#ifndef SETTINGSJUNCTIONLANELINK_H
#define SETTINGSJUNCTIONLANELINK_H


#include <QtWidgets>
#include <QtGui/QtGui>

#include "../../OpenDrive/Junction.h"

/**
 * Class that holds all the properties for the JUNCTION_LANE_LINK record
 *
 */
class SettingsJunctionLaneLink : public QWidget
{
	Q_OBJECT
public:
	/**
	 * Initializes the properties panel and the UI elements
	 */
	SettingsJunctionLaneLink(QWidget *parent = 0);

	/**
	 * Loads the data for a given record
	 *
	 * @param junctionLaneLink Junction lane link record whose properties are to be loaded
	 */
	void LoadData(JunctionLaneLink *junctionLaneLink);
private:
	/**
	 * Junction lane link record whose properties are to be displayed
	 */
	JunctionLaneLink *mJunctionLaneLink;

	/**
	 * Interface widgets
	 */
	QSpinBox *mFrom;
	QSpinBox *mTo;
public slots:
	/**
	 * Methods called when properties change
	 */
	void FromChanged(int value);
	void ToChanged(int value);
};

#endif