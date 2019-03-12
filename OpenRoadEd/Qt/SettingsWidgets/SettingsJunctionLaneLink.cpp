#include "SettingsJunctionLaneLink.h"
#include "moc_SettingsJunctionLaneLink.cpp"

/**
 * Initializes the properties panel and the UI elements
 */
SettingsJunctionLaneLink::SettingsJunctionLaneLink(QWidget *parent)
{
	// Resets the record
	mJunctionLaneLink=NULL;

	// Main vertical layout
	QVBoxLayout *mainLayout = new QVBoxLayout;

	//-------------------------------------------------
	// Group for settings
	QGroupBox *settingsGroup = new QGroupBox;
	settingsGroup->setSizePolicy(QSizePolicy::Preferred,QSizePolicy::Maximum);
	settingsGroup->setTitle(tr("Junction lane link settings"));

	mFrom=new QSpinBox;
	mFrom->setKeyboardTracking(false);
	mFrom->setRange(-100,100);
	mTo=new QSpinBox;
	mTo->setKeyboardTracking(false);
	mTo->setRange(-100,100);

	// Form Layout inside group
	QFormLayout *settingsFormLayout = new QFormLayout;
	settingsFormLayout->addRow(tr("From:"),mFrom);
	settingsFormLayout->addRow(tr("To:"),mTo);

	settingsGroup->setLayout(settingsFormLayout);
	//-------------------------------------------------
	// Group for help
	QGroupBox *helpGroup = new QGroupBox;
	helpGroup->setTitle(tr("Help"));

	QTextEdit *helpText = new QTextEdit;
	helpText->setSizePolicy(QSizePolicy::Preferred,QSizePolicy::Expanding);
	helpText->setReadOnly(true);
	helpText->setHtml("This record provides information about the lanes which are linked between incoming road and connecting road. This record may be omitted if all incoming lanes are linked to lanes with identical IDs on the connecting road. However, it is strongly recommended to provide this record."
						"<p><b>From</b> - identifier of the incoming lane</p>"
						"<p><b>To</b> - identifier of the connecting lane</p>");
	
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
 * @param junctionLaneLink Junction lane link record whose properties are to be loaded
 */
void SettingsJunctionLaneLink::LoadData(JunctionLaneLink *junctionLaneLink)
{
	if(junctionLaneLink!=NULL)
	{
		// Disconnects the "value changed" signals while the values are loaded
		disconnect(mFrom, SIGNAL(valueChanged(int)), this, SLOT(FromChanged(int)));
		disconnect(mTo, SIGNAL(valueChanged(int)), this, SLOT(ToChanged(int)));

		// Sets the record properties to the input widgets
		mJunctionLaneLink=junctionLaneLink;

		mFrom->setValue(mJunctionLaneLink->GetFrom());
		mTo->setValue(mJunctionLaneLink->GetTo());

		// Connects the "value changed" signals back
		connect(mFrom, SIGNAL(valueChanged(int)), this, SLOT(FromChanged(int)));
		connect(mTo, SIGNAL(valueChanged(int)), this, SLOT(ToChanged(int)));
	}
}

/**
 * Methods called when properties change
 */
void SettingsJunctionLaneLink::FromChanged(int value)
{
	mJunctionLaneLink->SetFrom(value);
}
void SettingsJunctionLaneLink::ToChanged(int value)
{
	mJunctionLaneLink->SetTo(value);
}