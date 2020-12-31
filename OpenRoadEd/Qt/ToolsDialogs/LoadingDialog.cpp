
#include <QtGui/QtGui>
#include "LoadingDialog.h"
#include "moc_LoadingDialog.cpp"
#include <QtWidgets>
#include <QApplication>

/**
 * Constructor
 * Initializes the widgets that make up the interface
 */
LoadingDialog::LoadingDialog()
{
	//-------------------------------------------------
	QVBoxLayout *lDialogLayout = new QVBoxLayout;
	//-------------------------------------------------
	QLabel *lSoftware = new QLabel("Loading");
	lSoftware->setFont(QFont("Arial",18,10));
	lSoftware->setAlignment(Qt::AlignHCenter);
	QLabel *lNames = new QLabel("Loading road structure and generating geometry");
	lNames->setAlignment(Qt::AlignHCenter);
	//-------------------------------------------------
	lDialogLayout->addWidget(lSoftware);
	lDialogLayout->addWidget(lNames);
	//-------------------------------------------------
	setLayout(lDialogLayout);
	//-------------------------------------------------

	setWindowFlags(Qt::Popup);
	setWindowTitle("Loading");
}
