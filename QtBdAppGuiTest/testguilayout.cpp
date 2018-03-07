// C++ includes
#include <iostream>
#include <fstream>
#include <sstream>
// Qt includes
#include <QtWidgets/QWidget>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QMessageBox>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QSplitter>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QHeaderView>
#include <QtCore/QTextStream>
#include <QtCore/QFile>
#include <QComboBox>
#include <QProcess>
#include <QLabel>
#include <QTextStream>
#include <QDateTime>
#include <QDirIterator>

// App include
#include "testguilayout.h"

namespace {
	//
	// Just some helpers to read file with data separated tab 
	void split( const std::string &s, char delim, std::vector<std::string> &elems) {
		std::stringstream ss;
		ss.str(s); // split to white space (see Bjarne Stroutstrup book "C++ Language And Practice")
		std::string item;
		while( std::getline(ss, item, delim)) {
			elems.push_back(item);
		}
	}

	// Read each line of the command file
	QList<QVector<QVariant>> readFileTab()
	{
		using namespace std;
		QList<QVector<QVariant>> w_list2Ret;

		// raw string (to be completed)
		const std::string w_filePath = R"(F:\EllignoContract\BoDuc\BoDucDev\BoDucApp01\ReportFiles\)";
		std::string w_fileName = w_filePath + std::string("BonLivraison_201217_withAlgo.txt");
		std::ifstream infile(w_fileName.c_str());
		std::string line;
		if (!infile)
		{
			std::cerr << "Could not open file for reading\n";
		}

		QVector<QVariant> w_vec2Fill;
		vector<string> row_values;
		w_vec2Fill.reserve(7); // number of fields

	  auto lineCounter = 0;
		while( std::getline(infile, line))
		{
			if (lineCounter == 0) { lineCounter += 1; continue; }
			if (!row_values.empty())
			{
				row_values.clear();
			}
			row_values.reserve(7); // number of fields

			split(line, '\t', row_values);
      if (!w_vec2Fill.empty())
      {
				w_vec2Fill.clear();
      }
			auto i = 0;
			// always const and ref to avoid copy
			for( const auto& v : row_values)
			{
				if( i==3)
				{
					int w_int = atoi(v.c_str());
					w_vec2Fill.push_back(QVariant(w_int));
				}
				else if(i==5)
				{
					// double value
					double w_dbl = atof(v.c_str());
					w_vec2Fill.push_back(QVariant(w_dbl));
				}
				else if (i==6)
				{
					int w_int = atoi(v.c_str());
					w_vec2Fill.push_back(QVariant(w_int));
				}
				else
				{
					w_vec2Fill.push_back(QVariant(v.c_str()));
				}
				++i;
			}//for-loop
		  //cout << v << ',';
			//cout << endl;
			w_list2Ret.push_back(w_vec2Fill);
		}//while-loop

		return w_list2Ret;
	}
	}// End of namespace

namespace bdGui {
	TestGuiLayout::TestGuiLayout(QWidget *parent /*= Q_NULLPTR*/)
		: QDialog(parent),
		m_listWidget(Q_NULLPTR),
		m_tblWidget(Q_NULLPTR),
		m_buttonBox(Q_NULLPTR),
		m_cmdBox(Q_NULLPTR),
		m_saveButton(Q_NULLPTR),
		m_closeButton(Q_NULLPTR),
		m_progressBarU1(Q_NULLPTR),
		m_progressBarU2(Q_NULLPTR),
		m_progressBarU3(Q_NULLPTR),
		m_progressBarU4(Q_NULLPTR),
		m_progressBarU5(Q_NULLPTR),
		m_splitWidget(Q_NULLPTR),
		m_listUnite(Q_NULLPTR),
		m_saveSelectBtn(Q_NULLPTR)
	{
		setWindowTitle("BdApp Bon De Livraison (creator)");
#if 1
		setupViews();
#else
		createListWidget();
#endif
		// create all components for the GUI
		createOtherWidgets();
		createLayout();
		createConnections();

//		setGeometry(200,200,0,0);

		// set initial
		m_progressBarU1->setValue(4);

		// this will be implemented in the selection 
		// of each command (save button in the BonLivraison)
		// this correspond at Qty 
		// just configuring the progress bar to display
		if (!m_progressBarU1->isEnabled())
		{
			m_progressBarU1->setEnabled(true);
		}
		if (m_progressBarU1->minimum() != 0)
		{
			m_progressBarU1->setMinimum(0);
		}
		if (m_progressBarU1->maximum() != 10)
		{
			m_progressBarU1->setMaximum(10);
		}

		// m_progressBarU1->repaint(false);
	// 	 m_progressBarU1->setVisible(true);
	// 	 m_progressBarU1->setMaximum(10);
	// 	 m_progressBarU1->setMinimum(0);
	// 	 m_progressBarU1->setTextVisible(true);
	// 	 m_progressBarU1->setFormat("Loading...");
	// 	 m_progressBarU1->setAlignment(Qt::AlignCenter);
	// 	 m_progressBarU1->setValue(4);

		 // set initial
	// 	 m_progressBarU2->setValue(8);
	// 
	// 	 // just configuring the progress bar to display
	// 	 if (!m_progressBarU2->isEnabled())
	// 	 {
	// 		 m_progressBarU2->setEnabled(true);
	// 	 }
	// 	 if (m_progressBarU2->minimum() != 0)
	// 	 {
	// 		 m_progressBarU2->setMinimum(0);
	// 	 }
	// 	 if (m_progressBarU2->maximum() != 10)
	// 	 {
	// 		 m_progressBarU2->setMaximum(10);
	// 	 }

	}

	void TestGuiLayout::savetest()
	{
		//just testing some stuff
		m_progressBarU1->setValue(1);
	//	m_progressBarU2->setValue(4);

		// for now we are just testing, so we fill
		// some data to test our implementation
		createTableWidget();
	}

	void TestGuiLayout::cancel()
	{
		// not implemented yet
	}

	void TestGuiLayout::open()
	{
		// for now we are just testing, so we fill
		// some data to test our implementation
//		createTableWidget();
		m_read4test = readFileTab();
	}

	void TestGuiLayout::clickedItem()
	{
		// not implemented yet
	}

	void TestGuiLayout::currentUniteON()
	{
		int w_uniteCurrent = m_listUnite->currentIndex(); // user choice
		QString w_uniteStr = m_listUnite->itemText(w_uniteCurrent);
	//	m_activeAlgo = w_algoName.toStdString(); // set user choice as active 
//		m_currentUnite = aTextChanged;
	}

	void TestGuiLayout::testItemClick( QTableWidgetItem * aItem)
	{
		QTableWidget*  w_tblWgt = aItem->tableWidget();
		Q_ASSERT(w_tblWgt!=Q_NULLPTR);
		QItemSelectionModel* select = w_tblWgt->selectionModel();
		if( select->hasSelection())
		{
			//return selected row
			QModelIndexList w_mdl = select->selectedRows();
			auto w_rowSiz = w_mdl.size();

			int w_rowNo = aItem->row();
			QVector<QVariant> w_cmd2Report; w_cmd2Report.reserve(w_tblWgt->columnCount());
			for( auto col=0;col<w_tblWgt->columnCount();++col)
			{
				QTableWidgetItem* w_chckItem = w_tblWgt->item(w_rowNo, col);
				QVariant w_val = w_chckItem->data(Qt::DisplayRole);
				w_cmd2Report.push_back(w_val);
				// add it to the list
			}
		
			//unite ON
			QString w_uniteON = m_listUnite->currentText();
			//QDir w_reportFolder; 
			QString w_path = QDir::currentPath();
			QString w_bonLivraisonFile = w_uniteON + "_BonLiveraison_date.txt";
			QFileInfo w_fileRep(w_path, w_bonLivraisonFile);
			if( !w_fileRep.exists(w_bonLivraisonFile))
			{
				// create a new file with the given name
				QFile w_data(w_fileRep.absoluteFilePath());
				// then create it write report
				if( w_data.open(QFile::WriteOnly | QFile::Text))
				{
					QTextStream out(&w_data);
		//			QString w_tetsVar = w_cmd2Report[0].toString();
				//	w_tetsVar.data()
					out << w_cmd2Report[0].toString() << "\n";
// 					<< " " << w_cmd2Report[1] << " " << w_cmd2Report[2] << " " << w_cmd2Report[3] << " "
// 						<< w_cmd2Report[4] << " " << w_cmd2Report[5] << " " << w_cmd2Report[6]
				}
			}
			else
			{
				// create a new file with the given name
				QFile w_data(w_fileRep.absoluteFilePath());

				// open and append it
				if (w_data.open(QFile::WriteOnly | QFile::Text | QFile::Append))
				{
					QTextStream out(&w_data);
				}
			}

			// we need to create or append info to "Unite1_BonLivraison_Date.txt" report
		//	QString w_filePath = w_fileRep.absoluteFilePath();
		
			// remove all items for this row (removeCellWidget(row,col))
		}
	}
	void TestGuiLayout::createListWidget()
	{
		m_listWidget = new QListWidget;
		QStringList w_strList;
		w_strList << "Anthony Fluet" << "Enviroporc" << "Dujardin" << "taratura"
			<< "porcibel" << "jani" << "Commande_7" << "Commande_8";

		// add list widget item to the list widget
		m_listWidget->addItems(w_strList);

		// retrieve list widget item to configure
		QListWidgetItem* w_item = Q_NULLPTR;
		for (int i = 0; i < m_listWidget->count(); ++i)
		{
			w_item = m_listWidget->item(i);
			w_item->setFlags(w_item->flags() | Qt::ItemIsUserCheckable);
			w_item->setCheckState(Qt::Unchecked);
		}
	}
	void TestGuiLayout::setupViews()
	{
		m_tblWidget = new QTableWidget(200, 7, this); //
		m_tblWidget->setHorizontalHeaderLabels(QStringList() << tr("No Command")
			<< tr("Shipped To")
			<< tr("Delivery date")
			<< tr("Product")
			<< tr("Code")
			<< tr("Quantity")
			<< tr("Silo"));
		m_tblWidget->verticalHeader()->setVisible(false);
		m_tblWidget->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
		m_tblWidget->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
		m_tblWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
		m_tblWidget->setSelectionMode(QAbstractItemView::SingleSelection);
		m_tblWidget->setShowGrid(true);
		m_tblWidget->setGeometry(QRect(0, 100, 781, 281));
		m_tblWidget->horizontalHeader()->resizeSection(1, 250);
		m_tblWidget->horizontalHeader()->resizeSection(2, 250);
		m_tblWidget->horizontalHeader()->resizeSection(3, 180);
		//m_tblWidget->setStyleSheet("QTableView {selection-background-color: red;}");
	}
	void TestGuiLayout::saveDataIntoTable()
	{
		if (!m_tblWidget)
			return;

		const int currentRow = m_tblWidget->rowCount();
		m_tblWidget->setRowCount(currentRow + 1);
	}
	void TestGuiLayout::createTableWidget()
	{
// 		QVector<QVariant> w_vecVariant;
// 		w_vecVariant.reserve(7);
// 		w_vecVariant.push_back(QVariant(QString("CO00473438")));
// 		w_vecVariant.push_back(QVariant(QString("FERME ERILIS INC. 672 ACADEMIE,VICTORIAVILLE, Québec, G6R 0V2")));
// 		w_vecVariant.push_back(QVariant(QString("2018/03/01")));
// 		w_vecVariant.push_back(QVariant(23126212));
// 		w_vecVariant.push_back(QVariant(QString("S SYNCHROMIX ERILIS C VR")));
// 		w_vecVariant.push_back(QVariant(3.));
// 		w_vecVariant.push_back(QVariant(1));

		auto i = 0;
		for( const QVector<QVariant>& w_vecVariant : m_read4test)
		{
		//}
		QTableWidgetItem* myTableWidgetItem = Q_NULLPTR;
// 		for (auto i = 0; i < m_tblWidget->rowCount(); ++i) // loop on file line number
// 		{
			for (auto j = 0; j < m_tblWidget->columnCount(); ++j)
			{
				myTableWidgetItem = new QTableWidgetItem; // i am not sure about this one
				myTableWidgetItem->setData(Qt::DisplayRole, w_vecVariant[j]);
				m_tblWidget->setItem(i, j, myTableWidgetItem);
			}
			++i;
		}
	}

	// Top group box, actually it's the original buttons layout
	// Open, load, save, process (buttons)
	QGroupBox* TestGuiLayout::createAnalyzerBox()
	{
		QPushButton* w_procButton = new QPushButton("Process");
		QPushButton* w_saveButton = new QPushButton("Save");
		QPushButton* w_loadButton = new QPushButton("Load");
		QPushButton* w_openButton = new QPushButton("Open");

		QHBoxLayout* w_analyzeHbox = new QHBoxLayout;
		w_analyzeHbox->addWidget(w_procButton);
		w_analyzeHbox->addWidget(w_saveButton);
		w_analyzeHbox->addWidget(w_loadButton);
		w_analyzeHbox->addWidget(w_openButton);
	
		// set layout of this box
		m_analyzerBox->setLayout(w_analyzeHbox);

		return m_analyzerBox;
	}

	QGroupBox* TestGuiLayout::createCreatorBox()
	{
		// Create a first row of buttons
		QHBoxLayout* w_buttonsTop = new QHBoxLayout;

		// List of unite available
		QLabel* w_listUniteLabl = new QLabel(tr("Unite Selectionne"));
		m_listUnite = new QComboBox;
		QStringList w_listUniteAvailable = { QString("Unite1"), QString("Unite2"), 
			QString("Unite3"), QString("Unite4"), QString("Unite5") };

		m_listUnite->addItems(w_listUniteAvailable);

		QVBoxLayout* w_uniteComboBox = new QVBoxLayout;
		w_uniteComboBox->addWidget(w_listUniteLabl);
		w_uniteComboBox->addWidget(m_listUnite);
		w_uniteComboBox->addStretch(3);
		w_buttonsTop->addLayout(w_uniteComboBox);

		QLabel* w_loadCmd = new QLabel(tr("Load Command Report"));
		m_loadButton = new QPushButton(tr("Open")); // open file for reading command from report file 
		QVBoxLayout* w_readCmd = new QVBoxLayout;
		w_readCmd->addWidget(w_loadCmd);
		w_readCmd->addWidget(m_loadButton);
		w_readCmd->addStretch(3);
		w_buttonsTop->addLayout(w_readCmd);

		QLabel* w_createBon = new QLabel(tr("Cree Bon Livraison"));
		QVBoxLayout* w_bonCreator = new QVBoxLayout;
		w_bonCreator->addWidget(w_createBon);
// 		QComboBox* w_listCbox = new QComboBox;
// 		w_listCbox->addItems(w_listUniteAvailable);
		QPushButton* w_bonCree = new QPushButton("Proceed");
		w_bonCreator->addWidget(w_bonCree);
		w_bonCreator->addStretch(2);
		w_buttonsTop->addLayout(w_bonCreator);

		// Save selection
		QLabel* w_lblsaveSelect = new QLabel(tr("Save Selection"));
 		QVBoxLayout* w_hboxsaveSelection = new QVBoxLayout;
		w_hboxsaveSelection->addWidget(w_lblsaveSelect);
		m_saveSelectBtn = new QPushButton("Save Select");
		w_hboxsaveSelection->addWidget(m_saveSelectBtn);
		w_hboxsaveSelection->addStretch(2);
		w_buttonsTop->addLayout(w_hboxsaveSelection);

		// now set our box 
		m_creatorBox->setLayout(w_buttonsTop);

		return m_creatorBox;
	}

	void TestGuiLayout::createOtherWidgets()
	{
		// create the group box
		m_cmdBox = new QGroupBox(tr("Liste de Commandes"));
		m_uniteBox = new QGroupBox(tr("Liste des Unites"));
		m_analyzerBox = new QGroupBox(tr("Analyse des commandes"));
		m_creatorBox = new QGroupBox(tr("Bon De Livraison"));

		// create buttons at the bottom 
		m_buttonBox = new QDialogButtonBox;
		m_saveButton =  m_buttonBox->addButton(QDialogButtonBox::Save);
		m_closeButton = m_buttonBox->addButton(QDialogButtonBox::Close);
		m_clearButton = m_buttonBox->addButton(QDialogButtonBox::Cancel);
#if 0
		// widget that hold other widget separated by a boundary
		m_splitWidget = new QSplitter;
#endif
	}

	void TestGuiLayout::createLayout()
	{
		// create report button
#if 0
		setListWidgetBox();
#else
		// display box (command display in the right panel)
		setTableWidgetBox();
#endif
		QBoxLayout* w_horizontalLayout = setBottomButtons();
#if 0
		setUniteBox(); // create the display box that list unite of transport
#endif
		setHProgressBar(); // display the progress horizontally
		// main dialog
		QVBoxLayout* w_mainLayout = new QVBoxLayout;
		//w_mainLayout->addLayout(w_buttonsTop);
		w_mainLayout->addWidget(createAnalyzerBox());
		w_mainLayout->addWidget(createCreatorBox());
#if 0
		w_mainLayout->addWidget(m_splitWidget);
#endif
		w_mainLayout->addWidget(m_uniteBox);
		w_mainLayout->addWidget(m_cmdBox);
		w_mainLayout->addLayout(w_horizontalLayout);
		w_mainLayout->setGeometry(QRect(200,200,0,0));
		setLayout(w_mainLayout);
	}

	void TestGuiLayout::setHProgressBar()
	{
		// create a layout for progress bar in a vertical layout
		QHBoxLayout* w_hProgressBar = new QHBoxLayout;

		addProgressBar(w_hProgressBar, std::string("Unite 1"));
		addProgressBar(w_hProgressBar, std::string("Unite 2"));
		addProgressBar(w_hProgressBar, std::string("Unite 3"));
		addProgressBar(w_hProgressBar, std::string("Unite 4"));
		m_uniteBox->setLayout(w_hProgressBar);
	}

	void TestGuiLayout::setUniteBox()
	{
		// create a layout for progress bar in a vertical layout
		QVBoxLayout* w_vProgressBar = new QVBoxLayout;

		addProgressBar(w_vProgressBar,std::string("Unite 1"));
		addProgressBar(w_vProgressBar, std::string("Unite 2"));
		addProgressBar(w_vProgressBar, std::string("Unite 3"));
		addProgressBar(w_vProgressBar, std::string("Unite 4"));
#if 0
		// Unite 2 
		QLabel* w_barU2 = new QLabel(tr("Unite 2"));
		m_progressBarU2 = new QProgressBar;
		// 	m_progressBarU2->setMinimum(m_pbarmin);
		// 	m_progressBarU2->setMaximum(m_pbarmax);
		//	m_progressBarU2->setValue(1);
		QVBoxLayout* w_lablandLayout2 = new QVBoxLayout;
		w_lablandLayout2->addWidget(w_barU2);
		w_lablandLayout2->addWidget(m_progressBarU2);
		w_vProgressBar->addStretch(2);
		w_vProgressBar->addLayout(w_lablandLayout2);
		
		// Unite 3
		QLabel* w_barU3 = new QLabel(tr("Unite 3"));
		m_progressBarU3 = new QProgressBar;
		// 	m_progressBarU3->setMinimum(m_pbarmin);
		// 	m_progressBarU3->setMaximum(m_pbarmax);
		//	m_progressBarU3->setValue(8);
		QVBoxLayout* w_lablandLayout3 = new QVBoxLayout;
		w_lablandLayout3->addWidget(w_barU3);
		w_lablandLayout3->addWidget(m_progressBarU3);
		w_vProgressBar->addStretch(2);
		w_vProgressBar->addLayout(w_lablandLayout3);
		
		// Unite 4
		QLabel* w_barU4 = new QLabel(tr("Unite 4"));
		m_progressBarU4 = new QProgressBar;
		QVBoxLayout* w_lablandLayout4 = new QVBoxLayout;
		w_lablandLayout4->addWidget(w_barU4);
		w_lablandLayout4->addWidget(m_progressBarU4);
		w_vProgressBar->addStretch(2);
		w_vProgressBar->addLayout(w_lablandLayout4);
		// 	m_progressBarU4->setMinimum(m_pbarmin);
		// 	m_progressBarU4->setMaximum(m_pbarmax);
		//	m_progressBarU4->setValue(4);

#endif
		m_uniteBox->setLayout(w_vProgressBar);

#if 0
		// add ... to be completed
		m_splitWidget->addWidget(m_uniteBox);
#endif
	}

	void TestGuiLayout::addProgressBar( QBoxLayout* aProgressBar, std::string&& aUniteNb)
	{
		if( QVBoxLayout* w_lablandLayout1 = dynamic_cast<QVBoxLayout*>(aProgressBar))
		{
			//std::string w_qstring("Unite 1");
			QLabel* w_barU1 = new QLabel(tr(aUniteNb.c_str()));
			m_progressBarU1 = new QProgressBar;

			// 	m_progressBarU1->setMinimum(m_pbarmin);
			// 	m_progressBarU1->setMaximum(m_pbarmax);

			//	m_progressBarU1->setValue(5);
			// 		w_vProgressBar->addWidget(w_barU1);
			//     w_vProgressBar->addWidget(m_progressBarU1);

			// Both label and button together
//			QVBoxLayout* w_lablandLayout1 = new QVBoxLayout;
			w_lablandLayout1->addWidget(w_barU1);
			w_lablandLayout1->addWidget(m_progressBarU1);
			aProgressBar->addStretch(2);
			aProgressBar->addLayout(w_lablandLayout1);
		}
		else if (QHBoxLayout* w_lablandLayout1 = dynamic_cast<QHBoxLayout*>(aProgressBar))
		{
			QLabel* w_barU1 = new QLabel(tr(aUniteNb.c_str()));
			m_progressBarU1 = new QProgressBar;
			w_lablandLayout1->addWidget(w_barU1);
			w_lablandLayout1->addWidget(m_progressBarU1);
			aProgressBar->addStretch(2);
			aProgressBar->addLayout(w_lablandLayout1);
		}
		else
		{
			return;
		}
	}

	QBoxLayout* TestGuiLayout::setBottomButtons()
	{
		// buttons at the bottom of the dialog
		QHBoxLayout* w_horizontalLayout = new QHBoxLayout;
		w_horizontalLayout->addWidget(m_buttonBox);

		return w_horizontalLayout;
	}

	void TestGuiLayout::setTableWidgetBox()
	{
		QVBoxLayout* w_viewLayout = new QVBoxLayout;
		w_viewLayout->addWidget(m_tblWidget);
		m_cmdBox->setLayout(w_viewLayout); // add it to Group box
	}

	void TestGuiLayout::setListWidgetBox()
	{
		QVBoxLayout* w_viewLayout = new QVBoxLayout;
		w_viewLayout->addWidget(m_listWidget);
		m_cmdBox->setLayout(w_viewLayout); // add it to Group box

		// adding to the splitter (this is the left panel)
		// Reminder: group box is a widget
		m_splitWidget->addWidget(m_cmdBox);
	}

	void TestGuiLayout::createConnections()
	{
// 		QObject::connect( m_listWidget, SIGNAL(itemChanged(QListWidgetItem*)),
// 			this, SLOT(highlightChecked(QListWidgetItem*)));
		//	QObject::connect(m_listWidget, SIGNAL(itemSelectionChanged()),this,SLOT(selectedItem()));
		QObject::connect( m_listWidget,    SIGNAL(itemClicked()), this, SLOT(clickedItem()));
	//	QObject::connect( m_saveButton, SIGNAL(clicked()),     this, SLOT(save()));
		QObject::connect( m_closeButton,   SIGNAL(clicked()),     this, SLOT(close()));
		QObject::connect( m_loadButton,    SIGNAL(clicked()),     this, SLOT(open()));
		QObject::connect( m_listUnite,     SIGNAL(activated(int)),this, SLOT(currentUniteON()));
		QObject::connect( m_saveSelectBtn, SIGNAL(clicked()),     this, SLOT(savetest()));
		QObject::connect( m_tblWidget,     SIGNAL(itemClicked(QTableWidgetItem*)), this, SLOT(testItemClick(QTableWidgetItem*)));
	}

#if 0
	void TestGuiLayout::on_pushButton_clicked1()
	{
		QProcess p;
		QStringList params;

		params << "script.py -arg1 arg1";
		p.start("python", params);
		p.waitForFinished(-1);
		QString p_stdout = p.readAll();
		ui->lineEdit->setText(p_stdout);
	}

	// path: you can set your own path
	//command: in which program you want to run(in this case python)
	// params : the script you want to be executed
	// &processID is for kill the process if the main window is closed
	void TestGuiLayout::on_pushButton_clicked2()
	{
		QString path = QCoreApplication::applicationDirPath();
		QString  command("python");
		QStringList params = QStringList() << "script.py";

		// don't really need the process ID
		QProcess *process = new QProcess();
		process->startDetached(command, params, path, &processID);
		process->waitForFinished();
		process->close();
	}

	void MainWindow::on_pushButton_clicked()
	{
		QProcess p;
		QStringList params;
		QString pythonPath = "C:/Python27/python.exe";
		QString pythonScript = "C:/Users/Martini/Desktop/trash/pythonTest.py";

		params << pythonScript;
		p.start(pythonPath, params);
		p.waitForFinished(-1);
		QString p_stdout = p.readAll();
		QString p_stderr = p.readAllStandardError();
		if (!p_stderr.isEmpty())
			qDebug() << "Python error:" << p_stderr;
		qDebug() << "Python result=" << p_stdout;
	}
	// update
	QProcessEnvironment env = QProcessEnvironment::systemEnvironment();
	env.insert("PYTHONPATH", "C:\\Python27\\Lib");
	env.insert("PYTHONHOME", "C:\\Python27");
	p.setProcessEnvironment(env);
#endif
} // End of namespace
