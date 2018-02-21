#ifndef TESTGUILAYOUT_H
#define TESTGUILAYOUT_H

#include <QtWidgets/QDialog>

// forward declaration
class QWidget;
class QGroupBox;
class QSplitter;
class QComboBox;
class QBoxLayout;
class QPushButton;
class QListWidget;
class QProgressBar;
class QListWidgetItem;
class QDialogButtonBox;

namespace bdGui {
class TestGuiLayout : public QDialog
{
  public:
    TestGuiLayout(QWidget *parent = Q_NULLPTR);
	public slots:
		void highlightChecked(QListWidgetItem* item);
		void save();
		void cancel(); // unselect what was selected by user

	//	void selectedItem();
		void clickedItem();
  private:
    QListWidget* m_listWidget;
    QDialogButtonBox* m_buttonBox;
    QGroupBox* m_cmdBox;
		QGroupBox* m_uniteBox;
    QPushButton* m_saveButton;     // when user push this button, report is saved
    QPushButton* m_closeButton;
		QPushButton* m_clearButton;
    QProgressBar* m_progressBarU1; // progress bar for unite #1
    QProgressBar* m_progressBarU2; // progress bar for unite #2
    QProgressBar* m_progressBarU3; // progress bar for unite #3
    QProgressBar* m_progressBarU4; // progress bar for unite #4
    QProgressBar* m_progressBarU5; // progress bar for unite #5
    // split window
    QSplitter* m_splitWidget;
		QComboBox* m_listUnite;   // ...
    // some helper functions
    void createListWidget();
    void createOtherWidgets();
    void createLayout();
		void setUniteBox();
		// ...
		QBoxLayout* setBottomButtons();
		void setListWidgetBox();
		// ...
		void createConnections();
		QPushButton* m_loadButton;
		int m_pbarmin = 0;
		int m_pbarmax = 0;
};
}
#endif // TESTGUILAYOUT_H
