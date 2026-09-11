#include <QApplication>

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

	// Pump the event loop once so the 3D viewport's GL context gets initialized
	// (and OSGMain::initViewer runs) before a file given on the command line is
	// loaded below - that loading path expects the viewer to already exist.
	app.processEvents();

	// Hides the splash screen
	splash.finish(&mainWin);

	// prepare to parse command line arguments
	QCommandLineParser parser;
	parser.addPositionalArgument("xodrfile", "File to open.", "[xodrfile]");
	// Process the actual command line arguments given by the user
	parser.process(app);
	const QStringList args = parser.positionalArguments();
	if (args.length() > 0) {
		// name of file to open is at args.at(0)
		mainWin.openXML(args.at(0).toStdString());
	}

    // Runs the application
    return app.exec();
}
