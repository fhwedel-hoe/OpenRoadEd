#ifndef SETTINGSJUNCTIONCONNECTION_H
#define SETTINGSJUNCTIONCONNECTION_H


#include <QtWidgets>
#include <QtGui/QtGui>

#include "../../OpenDrive/Junction.h"

/**
 * Class that holds all the properties for the JUNCTION_CONNECTION record
 *
 */
class SettingsJunctionConnection : public QWidget
{
	Q_OBJECT
public:
	/**
	 * Initializes the properties panel and the UI elements
	 */
	SettingsJunctionConnection(QWidget *parent = 0);

	/**
	 * Loads the data for a given record
	 *
	 * @param junctionConnection Junction connection record whose properties are to be loaded
	 */
	void LoadData(JunctionConnection *junctionConnection);
private:
	/**
	 * Junction connection record whose properties are to be displayed
	 */
	JunctionConnection *mJunctionConnection;

	/**
	 * Interface widgets
	 */
	QLineEdit *mId;
	QLineEdit *mIncomingRoad;
	QLineEdit *mConnectingRoad;
	QComboBox *mContactPoint;
public slots:
	/**
	 * Methods called when properties change
	 */
	void IdChanged();
	void IncomingRoadChanged();
	void ConnectingRoadChanged();
	void ContactPointChanged(const QString & text);
};

#endif