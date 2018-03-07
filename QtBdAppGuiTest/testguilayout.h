#ifndef TESTGUILAYOUT_H
#define TESTGUILAYOUT_H

#include <QtWidgets/QDialog>
#include <QMultiMap>
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
		void savetest(); // do what??
		void cancel();   // unselect what was selected by user
		void open();     // open command file for reading
	//	void selectedItem();
		void clickedItem();
		void currentUniteON();
		void createBonReport();
		void testItemClick(QTableWidgetItem* aItem);
  private:
		// struct to hold data (bon livraison report )
		using tplbonlivraison = std::tuple<QString, QString, double, short>;

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
		void addProgressBar( QBoxLayout* w_vProgressBar, const std::string& aUniteNb);
		void setHProgressBar();
		void setListWidgetBox();
		void setupViews();
		void saveDataIntoTable();
		void setTableWidgetBox();
    // ...
		void updateProgress();
		void initProgressBar();

		// ...
		QBoxLayout* setBottomButtons();
		// ...
		void createConnections();
		QGroupBox* createAnalyzerBox();
		QGroupBox* createCreatorBox();
		void populateTableWidget();
		QPushButton* m_loadButton;
		QPushButton* m_saveSelectBtn;
		QPushButton* m_bonCreateReport;
		int m_pbarmin = 0;
		int m_pbarmax = 0;
		int m_currowNoSelected;
		QGroupBox* m_analyzerBox;
		QGroupBox* m_creatorBox;
		QString m_currUnityON;
		// vector of all command fields that will be used 
		// for a given row 
		QVector<QVariant> m_vecVariant; 
		tplbonlivraison m_bdBonFields; // testing 
	  // key is the unit no and all values for report creation
		QMultiMap<QString, tplbonlivraison> m_unitBonLivraisonData;
		QStringList m_listUniteAvailable = { QString("Unit 1"), QString("Unit 2"),
			QString("Unit 3"), QString("Unit 4"), QString("Unit 5") };
};
}
#endif // TESTGUILAYOUT_H
