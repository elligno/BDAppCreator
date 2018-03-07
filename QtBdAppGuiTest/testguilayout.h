#ifndef TESTGUILAYOUT_H
#define TESTGUILAYOUT_H

#include <QtWidgets/QDialog>

// forward declaration
class QWidget;
class QGroupBox;
class QSplitter;
class QComboBox;
class QBoxLayout;
class QVBoxLayout;
class QPushButton;
class QListWidget;
class QProgressBar;
class QTableWidget;
class QListWidgetItem;
class QDialogButtonBox;
class QTableWidgetItem;

namespace bdGui {
class TestGuiLayout : public QDialog
{
	Q_OBJECT
  public:
    TestGuiLayout(QWidget *parent = Q_NULLPTR);
	public slots:
		//void highlightChecked(QListWidgetItem* item);
		void savetest();   // do what??
		void cancel(); // unselect what was selected by user
		void open();   // open command file for reading
	//	void selectedItem();
		void clickedItem();
		void currentUniteON();
		void testItemClick(QTableWidgetItem* aItem);
  private:
    QListWidget* m_listWidget;
		QTableWidget* m_tblWidget;
		QStringList m_TableHeader;
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
		QString m_currentUnite;
		QList<QVector<QVariant>> m_read4test;
    // some helper functions
    void createListWidget();
		void createTableWidget();
		void createOtherWidgets();
    void createLayout();
		void setUniteBox();
		
		// progress bar handler (move semantic)
		void addProgressBar( QBoxLayout* w_vProgressBar, std::string&& aUniteNb);
		void setHProgressBar();
		void setListWidgetBox();
		void setupViews();
		void saveDataIntoTable();
		void setTableWidgetBox();
		// ...
		QBoxLayout* setBottomButtons();
		// ...
		void createConnections();
		QGroupBox* createAnalyzerBox();
		QGroupBox* createCreatorBox();
		QPushButton* m_loadButton;
		QPushButton* m_saveSelectBtn;
		int m_pbarmin = 0;
		int m_pbarmax = 0;
		QGroupBox* m_analyzerBox;
		QGroupBox* m_creatorBox;
};
}
#endif // TESTGUILAYOUT_H
