#ifndef SCENERYDIALOG_H
#define SCENERYDIALOG_H


#include <QDialog>
#include <QtCore/QSettings>

#include "../../Osg/OSGMain.h"

#include "../ToolsDialogs/LoadingDialog.h"


/**
 * Dialog used to define properties and generate a landscape
 *
 */
class SceneryDialog : public QDialog
{
	Q_OBJECT
public:
	/**
	 * Constructor
	 * Initializes the widgets that make up the interface
	 *
	 * @param osgMain Pointer to OSG object
	 */
	SceneryDialog(OSGMain *osgMain);
private:
	/**
	 * OSG object pointer
	 */
	OSGMain *mOsgMain;

	/**
	 * Widgets used in the dialog
	 */
	QGroupBox *mSceneryGroup;

	QGroupBox *mCustomSize;
	QDoubleSpinBox *mSceneryXMin;
	QDoubleSpinBox *mSceneryXMax;
	QDoubleSpinBox *mSceneryYMin;
	QDoubleSpinBox *mSceneryYMax;

	QSpinBox *mSceneryResolutionX;
	QSpinBox *mSceneryResolutionY;

	QDoubleSpinBox *mSceneryHeightMultiplier;
	QDoubleSpinBox *mSceneryAverageElevation;

	QLineEdit *mSceneryTexture;
	QToolButton *mBrowseTexture;

	QLineEdit *mSceneryHeightmap;
	QToolButton *mBrowseHeightmap;


private slots:
	/**
	 * Launches the dialog
	 */
	void Run();

	/**
	 * Shows or hides the scenery
	 */
	void ShowHide(bool state);

	/**
	 * Shows a open file dialog to select an image for texture and heightmap
	 */
	void BrowseForTexture();
	void BrowseForHeightmap();

	/**
	 * Closes the dialog
	 */
	void OkPressed();
	void CancelPressed();
	
};


#endif
