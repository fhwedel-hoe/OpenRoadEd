#ifndef SETTINGSJUNCTION_H
#define SETTINGSJUNCTION_H


#include <QtGui/QWidget>
#include <QtGui/QtGui>

#include "../../OpenDrive/Junction.h"

/**
 * Class that holds all the properties for the JUNCTION record
 *
 */
class SettingsJunction : public QWidget
{
	Q_OBJECT
public:
	/**
	 * Initializes the properties panel and the UI elements
	 */
	SettingsJunction(QWidget *parent = 0);

	/**
	 * Loads the data for a given record
	 *
	 * @param junction Junction record whose properties are to be loaded
	 */
	void LoadData(Junction *junction);
private:
	/**
	 * Junction record whose properties are to be displayed
	 */
	Junction *mJunction;

	/**
	 * Interface widgets
	 */
	QLineEdit *mName;
	QLineEdit *mId;

public slots:
	/**
	 * Methods called when properties change
	 */
	void NameChanged();
	void IdChanged();
};

#endif