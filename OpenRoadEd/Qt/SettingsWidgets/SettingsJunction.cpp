#include "SettingsJunction.h"
#include "moc_SettingsJunction.cpp"

/**
 * Initializes the properties panel and the UI elements
 */
SettingsJunction::SettingsJunction(QWidget *parent)
{
	// Resets the record
	mJunction=NULL;

	// Main vertical layout
	QVBoxLayout *mainLayout = new QVBoxLayout;

	//-------------------------------------------------
	// Group for settings
	QGroupBox *settingsGroup = new QGroupBox;
	settingsGroup->setSizePolicy(QSizePolicy::Preferred,QSizePolicy::Maximum);
	settingsGroup->setTitle(tr("Junction settings"));

	mName = new QLineEdit;
	mId = new QLineEdit;

	// Form Layout inside group
	QFormLayout *settingsFormLayout = new QFormLayout;
	settingsFormLayout->addRow(tr("Name:"),mName);
	settingsFormLayout->addRow(tr("Id:"),mId);

	settingsGroup->setLayout(settingsFormLayout);
	//-------------------------------------------------
	// Group for help
	QGroupBox *helpGroup = new QGroupBox;
	helpGroup->setTitle(tr("Help"));

	QTextEdit *helpText = new QTextEdit;
	helpText->setSizePolicy(QSizePolicy::Preferred,QSizePolicy::Expanding);
	helpText->setReadOnly(true);
	helpText->setHtml("This record defines all possible connections between roads meeting at a physical junction."
						"<p><b>Name</b> - name of the junction (string)</p>"
						"<p><b>Id</b> - unique identifier of the junction (string)</p>");
	
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
 * @param junction Junction record whose properties are to be loaded
 */
void SettingsJunction::LoadData(Junction *junction)
{
	if(junction!=NULL)
	{
		// Disconnects the "value changed" signals while the values are loaded
		disconnect(mName, SIGNAL(editingFinished()), this, SLOT(NameChanged()));
		disconnect(mId, SIGNAL(editingFinished()), this, SLOT(IdChanged()));

		// Sets the record properties to the input widgets
		mJunction=junction;

		mName->setText(junction->GetName().c_str());
		mId->setText(junction->GetId().c_str());

		// Connects the "value changed" signals back
		connect(mName, SIGNAL(editingFinished()), this, SLOT(NameChanged()));
		connect(mId, SIGNAL(editingFinished()), this, SLOT(IdChanged()));
	}
}

/**
 * Methods called when properties change
 */
void SettingsJunction::NameChanged()
{
	mJunction->SetName(mName->text().toStdString());
}
void SettingsJunction::IdChanged()
{
	mJunction->SetId(mId->text().toStdString());
}