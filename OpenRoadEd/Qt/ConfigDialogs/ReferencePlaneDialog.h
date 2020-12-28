#ifndef REFERENCEPLANEDIALOG_H
#define REFERENCEPLANEDIALOG_H


#include <QDialog>
#include <QtCore/QSettings>
#include <QtWidgets>
#include "../../Osg/OSGMain.h"

/**
 * Dialog used to configure the grid or the reference plane
 *
 */
class ReferencePlaneDialog : public QDialog
{
	Q_OBJECT
public:
	/**
	 * Constructor
	 * Initializes the widgets that make up the interface
	 *
	 * @param osgMain Pointer to OSG object
	 */
	ReferencePlaneDialog(OSGMain *osgMain);

	/**
	 * Sets the grid values programmatically
	 */
	void SetGridValues(int rows, int colls, double minX, double minY, double maxX, double maxY);


private:
	/**
	 * OSG object pointer
	 */
	OSGMain *mOsgMain;

	/**
	 * Currently selected mode
	 */
	short int mCurSelected;

	/**
	 * Widgets used in the dialog
	 */
	QRadioButton *mGridButton;
	QRadioButton *mReferencePlaneButton;

	QGroupBox *mGridGroup;
	QDoubleSpinBox *mGridXMin;
	QDoubleSpinBox *mGridXMax;
	QDoubleSpinBox *mGridYMin;
	QDoubleSpinBox *mGridYMax;
	QSpinBox *mGridRows;
	QSpinBox *mGridCollumns;

	QGroupBox *mReferenceGroup;
	QLineEdit *mReferenceTexture;
	QToolButton *mBrowseButton;
	QDoubleSpinBox *mReferenceXMin;
	QDoubleSpinBox *mReferenceXMax;
	QDoubleSpinBox *mReferenceYMin;
	QDoubleSpinBox *mReferenceYMax;

private slots:
	/**
	 * Launches the dialog
	 */
	void Run();	

	/**
	 * Shows or hides the grid/reference plane
	 */
	void ShowHide(bool state);

	/**
	 * Shows a open file dialog to select an image for reference plane
	 */
	void BrowseForTexture();

	/**
	 * Called when either the grid or reference plane radio button is selected
	 */
	void GridSelected(bool checked);
	void ReferenceSelected(bool checked);

	/**
	 * Closes the dialog
	 */
	void OkPressed();
	void CancelPressed();
	
};


#endif
