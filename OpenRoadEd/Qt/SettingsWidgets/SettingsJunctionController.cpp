#include "SettingsJunctionController.h"
#include "moc_SettingsJunctionController.cpp"

/**
 * Initializes the properties panel and the UI elements
 */
SettingsJunctionController::SettingsJunctionController(QWidget *parent)
{
	// Resets the record
	mJunctionController=NULL;

	// Main vertical layout
	QVBoxLayout *mainLayout = new QVBoxLayout;

	//-------------------------------------------------
	// Group for settings
	QGroupBox *settingsGroup = new QGroupBox;
	settingsGroup->setSizePolicy(QSizePolicy::Preferred,QSizePolicy::Maximum);
	settingsGroup->setTitle(tr("Junction controller settings"));

	mId = new QLineEdit;
	mType = new QLineEdit;

	// Form Layout inside group
	QFormLayout *settingsFormLayout = new QFormLayout;
	settingsFormLayout->addRow(tr("Id:"),mId);
	settingsFormLayout->addRow(tr("Type:"),mType);

	settingsGroup->setLayout(settingsFormLayout);
	//-------------------------------------------------
	// Group for help
	QGroupBox *helpGroup = new QGroupBox;
	helpGroup->setTitle(tr("Help"));

	QTextEdit *helpText = new QTextEdit;
	helpText->setSizePolicy(QSizePolicy::Preferred,QSizePolicy::Expanding);
	helpText->setReadOnly(true);
	helpText->setHtml("This record lists the controllers which are used for the management of a junction."
						"<p><b>Id</b> - identifier of the controller (string)</p>"
						"<p><b>Type</b> - type of control for this junction (string)</p>");
	
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
 * @param junctionController Junction controller record whose properties are to be loaded
 */
void SettingsJunctionController::LoadData(JunctionController *junctionController)
{
	if(junctionController!=NULL)
	{
		// Disconnects the "value changed" signals while the values are loaded
		disconnect(mId, SIGNAL(editingFinished()), this, SLOT(IdChanged()));
		disconnect(mType, SIGNAL(editingFinished()), this, SLOT(TypeChanged()));

		// Sets the record properties to the input widgets
		mJunctionController=junctionController;

		mId->setText(mJunctionController->GetId().c_str());
		mType->setText(mJunctionController->GetType().c_str());

		// Connects the "value changed" signals back
		connect(mId, SIGNAL(editingFinished()), this, SLOT(IdChanged()));
		connect(mType, SIGNAL(editingFinished()), this, SLOT(TypeChanged()));
	}
}

/**
 * Methods called when properties change
 */
void SettingsJunctionController::IdChanged()
{
	mJunctionController->SetId(mId->text().toStdString());
}
void SettingsJunctionController::TypeChanged()
{
	mJunctionController->SetType(mType->text().toStdString());
}
