#include <QtGui/QApplication>

#include "Qt/MainWindow.h"
#include "OpenDrive/OpenDrive.h"
#include "Osg/OSGMain.h"

/**
 * Entry point
 */
int main(int argc, char *argv[])
{
	// Creates the main application
	QApplication app(argc, argv);

	// Loads and displays the splash screen
	QPixmap pixmap("Resources/splash.png");
	QSplashScreen splash(pixmap,Qt::WindowStaysOnTopHint);
	splash.show();
	app.processEvents();

	// Creates the OpenDrive structure
	OpenDrive mOpenDrive;

	// Creates the OSG object
	OSGMain mOsgMain(&mOpenDrive);
  
	// Creates the main window
    MainWindow mainWin(&mOsgMain, &mOpenDrive);
    mainWin.show();

	// Hides the splash screen
	splash.finish(&mainWin);

    // Runs the application
    return app.exec();
}