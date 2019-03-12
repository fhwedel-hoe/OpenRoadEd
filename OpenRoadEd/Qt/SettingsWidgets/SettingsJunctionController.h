#ifndef SETTINGSJUNCTIONCONTROLLER_H
#define SETTINGSJUNCTIONCONTROLLER_H


#include <QtGui/QWidget>
#include <QtGui/QtGui>

#include "../../OpenDrive/Junction.h"

/**
 * Class that holds all the properties for the JUNCTION_CONTROLLER record
 *
 */
class SettingsJunctionController : public QWidget
{
	Q_OBJECT
public:
	/**
	 * Initializes the properties panel and the UI elements
	 */
	SettingsJunctionController(QWidget *parent = 0);

	/**
	 * Loads the data for a given record
	 *
	 * @param junctionController Junction controller record whose properties are to be loaded
	 */
	void LoadData(JunctionController *junctionController);
private:
	/**
	 * Junction controller record whose properties are to be displayed
	 */
	JunctionController *mJunctionController;

	/**
	 * Interface widgets
	 */
	QLineEdit *mId;
	QLineEdit *mType;
public slots:
	/**
	 * Methods called when properties change
	 */
	void IdChanged();
	void TypeChanged();
};

#endif