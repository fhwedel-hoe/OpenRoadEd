#ifndef LOADINGDIALOG_H
#define LOADINGDIALOG_H


#include <QDialog>
#include <QtCore/QSettings>
#include "../../Osg/OSGMain.h"

/**
 * "Loading" dialog
 *
 */
class LoadingDialog : public QDialog
{
	Q_OBJECT
public:
	/**
	 * Constructor
	 * Initializes the widgets that make up the interface
	 */
	LoadingDialog();
};


#endif
