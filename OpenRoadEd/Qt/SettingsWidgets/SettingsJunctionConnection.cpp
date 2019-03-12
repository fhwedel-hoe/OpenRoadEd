#include "SettingsJunctionConnection.h"
#include "moc_SettingsJunctionConnection.cpp"

/**
 * Initializes the properties panel and the UI elements
 */
SettingsJunctionConnection::SettingsJunctionConnection(QWidget *parent)
{
	// Resets the record
	mJunctionConnection=NULL;

	// Main vertical layout
	QVBoxLayout *mainLayout = new QVBoxLayout;

	//-------------------------------------------------
	// Group for settings
	QGroupBox *settingsGroup = new QGroupBox;
	settingsGroup->setSizePolicy(QSizePolicy::Preferred,QSizePolicy::Maximum);
	settingsGroup->setTitle(tr("Junction connection settings"));

	mId = new QLineEdit;
	mIncomingRoad = new QLineEdit;
	mConnectingRoad = new QLineEdit;
	mContactPoint = new QComboBox;
	mContactPoint->insertItem(0,tr("start"));
	mContactPoint->insertItem(1,tr("end"));

	// Form Layout inside group
	QFormLayout *settingsFormLayout = new QFormLayout;
	settingsFormLayout->addRow(tr("Id:"),mId);
	settingsFormLayout->addRow(tr("Incoming road:"),mIncomingRoad);
	settingsFormLayout->addRow(tr("Connecting road:"),mConnectingRoad);
	settingsFormLayout->addRow(tr("Contact point:"),mContactPoint);

	settingsGroup->setLayout(settingsFormLayout);
	//-------------------------------------------------
	// Group for help
	QGroupBox *helpGroup = new QGroupBox;
	helpGroup->setTitle(tr("Help"));

	QTextEdit *helpText = new QTextEdit;
	helpText->setSizePolicy(QSizePolicy::Preferred,QSizePolicy::Expanding);
	helpText->setReadOnly(true);
	helpText->setHtml("This record provides information about a single connection within a junction."
						"<p><b>Id</b> - unique identifier withing the junction (string)</p>"
						"<p><b>Incoming road</b> - identifier of the incoming road (string)</p>"
						"<p><b>Connecting road</b> - identifier of the connecting road (string)</p>"
						"<p><b>Contact point</b> - contact point of the incoming road</p>");
	
	QVBoxLayout *helpLayout = new QVBoxLayout;
	helpLayout->addWidget(helpText);

	helpGroup->setLayout(helpLayout);
	//-------------------------------------------------

	mainLayout->addWidget(settingsGroup);
	mainLayout->addWidget(helpGroup);
	setLayout(mainLayout);
}

/**
 * Loads the data for a given record
 *
 * @param junctionConnection Junction connection record whose properties are to be loaded
 */
void SettingsJunctionConnection::LoadData(JunctionConnection *junctionConnection)
{
	if(junctionConnection!=NULL)
	{
		// Disconnects the "value changed" signals while the values are loaded
		disconnect(mId, SIGNAL(editingFinished()), this, SLOT(IdChanged()));
		disconnect(mIncomingRoad, SIGNAL(editingFinished()), this, SLOT(IncomingRoadChanged()));
		disconnect(mConnectingRoad, SIGNAL(editingFinished()), this, SLOT(ConnectingRoadChanged()));
		disconnect(mContactPoint, SIGNAL(currentIndexChanged(const QString &)), this, SLOT(ContactPointChanged(const QString &)));

		// Sets the record properties to the input widgets
		mJunctionConnection=junctionConnection;

		mId->setText(junctionConnection->GetId().c_str());
		mIncomingRoad->setText(junctionConnection->GetIncomingRoad().c_str());
		mConnectingRoad->setText(junctionConnection->GetConnectingRoad().c_str());
		if(junctionConnection->GetContactPoint().compare("start")==0) mContactPoint->setCurrentIndex(0);
		else mContactPoint->setCurrentIndex(1);

		// Connects the "value changed" signals back
		connect(mId, SIGNAL(editingFinished()), this, SLOT(IdChanged()));
		connect(mIncomingRoad, SIGNAL(editingFinished()), this, SLOT(IncomingRoadChanged()));
		connect(mConnectingRoad, SIGNAL(editingFinished()), this, SLOT(ConnectingRoadChanged()));
		connect(mContactPoint, SIGNAL(currentIndexChanged(const QString &)), this, SLOT(ContactPointChanged(const QString &)));
	}
}

/**
 * Methods called when properties change
 */
void SettingsJunctionConnection::IdChanged()
{
	mJunctionConnection->SetId(mId->text().toStdString());
}
void SettingsJunctionConnection::IncomingRoadChanged()
{
	mJunctionConnection->SetIncomingRoad(mIncomingRoad->text().toStdString());
}
void SettingsJunctionConnection::ConnectingRoadChanged()
{
	mJunctionConnection->SetConnectingRoad(mConnectingRoad->text().toStdString());
}
void SettingsJunctionConnection::ContactPointChanged(const QString & text)
{
	mJunctionConnection->SetContactPoint(text.toStdString());
}