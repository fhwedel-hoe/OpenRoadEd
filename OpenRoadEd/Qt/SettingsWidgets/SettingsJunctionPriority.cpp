#include "SettingsJunctionPriority.h"
#include "moc_SettingsJunctionPriority.cpp"

/**
 * Initializes the properties panel and the UI elements
 */
SettingsJunctionPriority::SettingsJunctionPriority(QWidget *parent)
{
	// Resets the record
	mJunctionPriority=NULL;

	// Main vertical layout
	QVBoxLayout *mainLayout = new QVBoxLayout;

	//-------------------------------------------------
	// Group for settings
	QGroupBox *settingsGroup = new QGroupBox;
	settingsGroup->setSizePolicy(QSizePolicy::Preferred,QSizePolicy::Maximum);
	settingsGroup->setTitle(tr("Junction priority settings"));

	mHigh = new QLineEdit;
	mLow = new QLineEdit;

	// Form Layout inside group
	QFormLayout *settingsFormLayout = new QFormLayout;
	settingsFormLayout->addRow(tr("High:"),mHigh);
	settingsFormLayout->addRow(tr("Low:"),mLow);

	settingsGroup->setLayout(settingsFormLayout);
	//-------------------------------------------------
	// Group for help
	QGroupBox *helpGroup = new QGroupBox;
	helpGroup->setTitle(tr("Help"));

	QTextEdit *helpText = new QTextEdit;
	helpText->setSizePolicy(QSizePolicy::Preferred,QSizePolicy::Expanding);
	helpText->setReadOnly(true);
	helpText->setHtml("This record provides information about the priority of a connecting road over another connecting road. It is only required if priorities cannot be derived from signs or signals in a junction or on tracks leading to a junction."
						"<p><b>High</b> - identifier of the prioritized connecting road (string)</p>"
						"<p><b>Low</b> - identifier of the connecting road with lower priority (string)</p>");
	
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
 * @param junctionPriority Junction priority record whose properties are to be loaded
 */
void SettingsJunctionPriority::LoadData(JunctionPriorityRoad *junctionPriority)
{
	if(junctionPriority!=NULL)
	{
		// Disconnects the "value changed" signals while the values are loaded
		disconnect(mHigh, SIGNAL(editingFinished()), this, SLOT(HighChanged()));
		disconnect(mLow, SIGNAL(editingFinished()), this, SLOT(LowChanged()));

		// Sets the record properties to the input widgets
		mJunctionPriority=junctionPriority;

		mHigh->setText(mJunctionPriority->GetHigh().c_str());
		mLow->setText(mJunctionPriority->GetLow().c_str());

		// Connects the "value changed" signals back
		connect(mHigh, SIGNAL(editingFinished()), this, SLOT(HighChanged()));
		connect(mLow, SIGNAL(editingFinished()), this, SLOT(LowChanged()));
	}
}

/**
 * Methods called when properties change
 */
void SettingsJunctionPriority::HighChanged()
{
	mJunctionPriority->SetHigh(mHigh->text().toStdString());
}
void SettingsJunctionPriority::LowChanged()
{
	mJunctionPriority->SetLow(mLow->text().toStdString());
}