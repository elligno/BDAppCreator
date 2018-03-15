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
#include <QFileDialog>
#include <QComboBox>
#include <QProcess>
#include <QLabel>
#include <QTextStream>
#include <QDateTime>
#include <QDirIterator>

// App include
#include "testguilayout.h"

namespace {
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
		m_saveSelectBtn(Q_NULLPTR),
		m_bonCreateReport(Q_NULLPTR)
	{
		setWindowTitle("BdApp Bon De Livraison (creator)");

		// set display formating (Widget table) 
		setupViews(); 

		// create all components for the GUI
		createOtherWidgets();
		createLayout();
		createConnections();

		// set config of the progress bar 
		initProgressBar();
	}

	// at the moment we support 4-5 unit just do a check on each of them
	// call when user select to save selection
	void TestGuiLayout::updateProgress()
	{
		if( m_currUnityON.compare(m_listUniteAvailable.at(0)) == 0) // identical
		{
			double w_val2Show = m_progressBarU1->value() + std::get<2>(m_bdBonFields);
			m_progressBarU1->setValue(w_val2Show);
		}
		else if (m_currUnityON.compare(m_listUniteAvailable.at(1)) == 0)
		{
			double w_val2Show = m_progressBarU2->value() + std::get<2>(m_bdBonFields);
			m_progressBarU2->setValue(w_val2Show);
		}
		else if (m_currUnityON.compare(m_listUniteAvailable.at(2)) == 0)
		{
			double w_val2Show = m_progressBarU3->value() + std::get<2>(m_bdBonFields);
			m_progressBarU3->setValue(w_val2Show);
		}
		else if (m_currUnityON.compare(m_listUniteAvailable.at(3)) == 0)
		{
			double w_val2Show = m_progressBarU4->value() + std::get<2>(m_bdBonFields);
			m_progressBarU4->setValue(w_val2Show);
		}
	}

	// just configuring the progress bar to display
	void TestGuiLayout::initProgressBar()
	{
		//
		// Unit #1
		//
		if (!m_progressBarU1->isEnabled())
		{
			m_progressBarU1->setEnabled(true);
		}
		if (m_progressBarU1->value()!=0)
		{
			// set initial value
			m_progressBarU1->setValue(0.);
		}
		if (m_progressBarU1->minimum() != 0)
		{
			m_progressBarU1->setMinimum(0);
		}
		if (m_progressBarU1->maximum() != 10)
		{
			m_progressBarU1->setMaximum(10);
		}

		//
		// Unit #2
		//
		if (!m_progressBarU2->isEnabled())
		{
			m_progressBarU2->setEnabled(true);
		}
		if (m_progressBarU2->value() != 0)
		{
			// set initial value
			m_progressBarU2->setValue(0.);
		}
		if (m_progressBarU2->minimum() != 0)
		{
			m_progressBarU2->setMinimum(0);
		}
		if (m_progressBarU2->maximum() != 10)
		{
			m_progressBarU2->setMaximum(10);
		}

		//
		// Unit #3
		//
		if (!m_progressBarU3->isEnabled())
		{
			m_progressBarU3->setEnabled(true);
		}
		if (m_progressBarU3->value() != 0)
		{
			// set initial value
			m_progressBarU3->setValue(0.);
		}
		if (m_progressBarU3->minimum() != 0)
		{
			m_progressBarU3->setMinimum(0);
		}
		if (m_progressBarU3->maximum() != 10)
		{
			m_progressBarU3->setMaximum(10);
		}

		//
		// Unit #4
		//
		if (!m_progressBarU4->isEnabled())
		{
			m_progressBarU4->setEnabled(true);
		}
		if (m_progressBarU4->value() != 0)
		{
			// set initial value
			m_progressBarU4->setValue(0.);
		}
		if (m_progressBarU4->minimum() != 0)
		{
			m_progressBarU4->setMinimum(0);
		}
		if (m_progressBarU4->maximum() != 10)
		{
			m_progressBarU4->setMaximum(10);
		}
	}

	void TestGuiLayout::savetest()
	{
		updateProgress();

		//QMessageBox(tr("Delete it from table"));
		QMessageBox msgBox;
		msgBox.setWindowTitle("Delete Command");
		msgBox.setText("Sure you want delete it?");
		msgBox.setStandardButtons(QMessageBox::Yes);
		msgBox.addButton(QMessageBox::No);
		msgBox.setDefaultButton(QMessageBox::No);
		if (msgBox.exec() == QMessageBox::Yes) {
			m_tblWidget->removeRow(m_currowNoSelected); // row number
		}
		else {
			// do something else
		}
		// for now we are just testing, so we fill
		// some data to test our implementation
		//createTableWidget();
	}

	void TestGuiLayout::cancel()
	{
		// not implemented yet
	}

	// loading commands form file (created by the parser)
	void TestGuiLayout::open()
	{
		// for now we are just testing, so we fill
		// some data to test our implementation
#if 0
		createTableWidget(); // testing purpose
#else
		m_read4test = readFileTab(); // from file
		createTableWidget();
#endif
	}

	void TestGuiLayout::clickedItem()
	{
		// not implemented yet
	}

	void TestGuiLayout::currentUniteON()
	{
		// user change unity selection
		int w_uniteCurrent = m_listUnite->currentIndex(); // user choice
		m_currUnityON = m_listUnite->itemText(w_uniteCurrent);
	}

	// create report for each transport unit
	void TestGuiLayout::createBonReport()
	{
		//unite ON
		QString w_uniteON = m_listUnite->currentText();

		// If you want to retrieve all the values for a single key, 
		// you can use values(const Key &key), which returns a QList<T>:

		//QDir w_reportFolder; 
		QString w_path = QDir::currentPath();
		QString w_bonLivraisonFile = w_uniteON + "_BonLiveraison.txt";
		QFileInfo w_fileRep(w_path, w_bonLivraisonFile);
		// create a new file with the given name
		QFile w_data(w_fileRep.absoluteFilePath());
		QList<tplbonlivraison> values = m_unitBonLivraisonData.values(w_uniteON);
		if (!w_fileRep.exists(w_bonLivraisonFile))
		{
			QTextStream out(&w_data);
			// then create it write report
			if (w_data.open(QFile::WriteOnly | QFile::Text))
			{
				for (int i = 0; i < values.size(); ++i)
				{
					tplbonlivraison w_val2File = values.at(i);
					out << std::get<0>(w_val2File) << "\t" << std::get<1>(w_val2File) << "\t"
						<< std::get<2>(w_val2File) << "\t" << std::get<3>(w_val2File) << "\t" << "\n";
				}
			}
	  }
		else
		{
			// open and append it
			if( w_data.open(QFile::WriteOnly | QFile::Text | QFile::Append))
			{
				QTextStream out(&w_data);
				for( int i = 0; i < values.size(); ++i)
				{
					tplbonlivraison w_val2File = values.at(i);
					out << std::get<0>(w_val2File) << "\t" << std::get<1>(w_val2File) << "\t"
						<< std::get<2>(w_val2File) << "\t" << std::get<3>(w_val2File) << "\t" << "\n";
				}
			}
		}
		w_data.close();
	}

	// selected a row with mouse
	void TestGuiLayout::testItemClick( QTableWidgetItem * aItem)
	{
		QTableWidget*  w_tblWgt = aItem->tableWidget();
		Q_ASSERT(w_tblWgt != Q_NULLPTR);
		QItemSelectionModel* select = w_tblWgt->selectionModel();
		if( select->hasSelection())
		{
			//return selected row
			QModelIndexList w_mdl = select->selectedRows();
			auto w_rowSiz = w_mdl.size();

			m_currowNoSelected = aItem->row();
			QVector<QVariant> w_cmd2Report; 
			w_cmd2Report.reserve( w_tblWgt->columnCount());
			// nor sure about this one
			QMap<int, tplbonlivraison> w_checkMap;
		
			// fill the struct for report
			for( auto col=0;col<w_tblWgt->columnCount();++col)
			{
				QTableWidgetItem* w_chckItem = w_tblWgt->item(m_currowNoSelected, col);
				QVariant w_val = w_chckItem->data(Qt::DisplayRole);
				// BoDuc selection
        if(col==1)
        {
					std::get<0>(m_bdBonFields) = w_val.toString();
        }
				else if (col == 4)
				{
					std::get<1>(m_bdBonFields) = w_val.toString();
				}
				else if (col == 5)
				{
					std::get<2>(m_bdBonFields) = w_val.toDouble();
				}
				else if (col == 6)
				{
					std::get<3>(m_bdBonFields) = w_val.toInt();
				}

				w_cmd2Report.push_back(w_val);
				// add it to the list
			}

			// just a test
			w_checkMap.insert(m_currowNoSelected, m_bdBonFields);
			// store all data selected by user to be retrieved 
			// when creating bon de livraison (file format) 
			// key is the unit name that is currently selected
			m_unitBonLivraisonData.insert( m_currUnityON, m_bdBonFields);
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
		m_tblWidget = new QTableWidget(50, 7, this); //
		m_tblWidget->setHorizontalHeaderLabels(QStringList() //<< tr("Selected")
			<< tr("No Command")
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
#if 0
		// fill table widget with data
		populateTableWidget();
#endif

		auto i = 0; // create each row of the table
		for( const QVector<QVariant>& w_vecVariant : m_read4test)
		{
			QTableWidgetItem* myTableWidgetItem = Q_NULLPTR;
			for( auto j = 0; j < m_tblWidget->columnCount(); ++j)
			{
				myTableWidgetItem = new QTableWidgetItem;     // i am not sure about this one
				//myTableWidgetItem->data(Qt::CheckStateRole);  // 
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
		w_openButton = new QPushButton("Open");

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

		m_listUnite->addItems(m_listUniteAvailable);

		QVBoxLayout* w_uniteComboBox = new QVBoxLayout;
		w_uniteComboBox->addWidget(w_listUniteLabl);
		w_uniteComboBox->addWidget(m_listUnite);
//		w_uniteComboBox->addStretch(3);
		w_buttonsTop->addLayout(w_uniteComboBox);

		int w_uniteCurrent = m_listUnite->currentIndex(); // user choice
		m_currUnityON = m_listUnite->itemText(w_uniteCurrent);

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
		m_bonCreateReport = new QPushButton("Proceed");
		w_bonCreator->addWidget(m_bonCreateReport);
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

	void TestGuiLayout::populateTableWidget()
	{
		// for now we are testing table widget functionality 
		QVector<QVariant> w_vecVariant1;
		w_vecVariant1.reserve(7);
		w_vecVariant1.push_back(QVariant(QString("CO00473438")));
		w_vecVariant1.push_back(QVariant(QString("FERME ERILIS INC. 672 ACADEMIE,VICTORIAVILLE, Québec, G6R 0V2")));
		w_vecVariant1.push_back(QVariant(QString("2018/03/01")));
		w_vecVariant1.push_back(QVariant(23126212));
		w_vecVariant1.push_back(QVariant(QString("S SYNCHROMIX ERILIS C VR")));
		w_vecVariant1.push_back(QVariant(3.));
		w_vecVariant1.push_back(QVariant(1));
		// fill the list of cmd
		m_read4test.push_back(w_vecVariant1);

		QVector<QVariant> w_vecVariant2;
		w_vecVariant2.reserve(7);
		w_vecVariant2.push_back(QVariant(QString("CO00401038")));
		w_vecVariant2.push_back(QVariant(QString("Ferme Duno inc E-1. 485 ACADEMIE,Lyster, Québec, G0S 1V0")));
		w_vecVariant2.push_back(QVariant(QString("2018/03/04")));
		w_vecVariant2.push_back(QVariant(21126012));
		w_vecVariant2.push_back(QVariant(QString("PORC LA COOP 6AA 0.4SE VE 0.21SAL C VR")));
		w_vecVariant2.push_back(QVariant(1.5));
		w_vecVariant2.push_back(QVariant(4));
		// fill the list of cmd
		m_read4test.push_back(w_vecVariant2);

		QVector<QVariant> w_vecVariant3;
		w_vecVariant3.reserve(7);
		//w_vecVariant.push_back(QVariant(QString("Selected")));
		w_vecVariant3.push_back(QVariant(QString("CO00435638")));
		w_vecVariant3.push_back(QVariant(QString("Ferme Pomerleau& Frere. 72 Bois-Franc,VICTORIAVILLE, Québec, G6R 0V2")));
		w_vecVariant3.push_back(QVariant(QString("2018/03/02")));
		w_vecVariant3.push_back(QVariant(20126200));
		w_vecVariant3.push_back(QVariant(QString("A PORC LC 6B 0.4SE VE C VR")));
		w_vecVariant3.push_back(QVariant(2.));
		w_vecVariant3.push_back(QVariant(2));
		// fill the list of cmd
		m_read4test.push_back(w_vecVariant3);

		QVector<QVariant> w_vecVariant4;
		w_vecVariant4.reserve(7);
		//w_vecVariant.push_back(QVariant(QString("Selected")));
		w_vecVariant4.push_back(QVariant(QString("CO00430602")));
		w_vecVariant4.push_back(QVariant(QString("LES PORCHERIES IKCO SENC E-3. 123 blvd Gnogno, VICTORIAVILLE, Québec, G6R 0V2")));
		w_vecVariant4.push_back(QVariant(QString("2018/03/02")));
		w_vecVariant4.push_back(QVariant(26136812));
		w_vecVariant4.push_back(QVariant(QString("A PORC LA COOP 3 0.4SE VE C VR")));
		w_vecVariant4.push_back(QVariant(5.5));
		w_vecVariant4.push_back(QVariant(1));
		// fill the list of cmd
		m_read4test.push_back(w_vecVariant4);
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

		// display the progress horizontally
		setHProgressBar(); 
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

		addProgressBar(w_hProgressBar, m_listUniteAvailable.at(0).toStdString().c_str());
		addProgressBar(w_hProgressBar, m_listUniteAvailable.at(1).toStdString().c_str());
		addProgressBar(w_hProgressBar, m_listUniteAvailable.at(2).toStdString().c_str());
		addProgressBar(w_hProgressBar, m_listUniteAvailable.at(3).toStdString().c_str());
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
		m_uniteBox->setLayout(w_vProgressBar);

#if 0
		// add ... to be completed
		m_splitWidget->addWidget(m_uniteBox);
#endif
	}

	void TestGuiLayout::addProgressBar(QBoxLayout* aProgressBar, const std::string& aUniteNb)
	{
		if (QVBoxLayout* w_lablandLayout1 = dynamic_cast<QVBoxLayout*>(aProgressBar))
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
			QLabel* w_barlbl = new QLabel(tr(aUniteNb.c_str()));
			if( QString::compare( m_listUniteAvailable.at(0), QString(aUniteNb.c_str()))==0)
			{
				m_progressBarU1 = new QProgressBar;
				w_lablandLayout1->addWidget(w_barlbl);
				w_lablandLayout1->addWidget(m_progressBarU1);
				aProgressBar->addStretch(2);
				aProgressBar->addLayout(w_lablandLayout1);
			}
			else if (QString::compare(m_listUniteAvailable.at(1), QString(aUniteNb.c_str())) == 0)
			{
				m_progressBarU2 = new QProgressBar;
				w_lablandLayout1->addWidget(w_barlbl);
				w_lablandLayout1->addWidget(m_progressBarU2);
				aProgressBar->addStretch(2);
				aProgressBar->addLayout(w_lablandLayout1);
			}
			else if(QString::compare(m_listUniteAvailable.at(2), QString(aUniteNb.c_str())) == 0)
			{
				m_progressBarU3 = new QProgressBar;
				w_lablandLayout1->addWidget(w_barlbl);
				w_lablandLayout1->addWidget(m_progressBarU3);
				aProgressBar->addStretch(2);
				aProgressBar->addLayout(w_lablandLayout1);
			}
			else if (QString::compare(m_listUniteAvailable.at(3), QString(aUniteNb.c_str())) == 0)
			{
				m_progressBarU4 = new QProgressBar;
				w_lablandLayout1->addWidget(w_barlbl);
				w_lablandLayout1->addWidget(m_progressBarU4);
				aProgressBar->addStretch(2);
				aProgressBar->addLayout(w_lablandLayout1);
			}
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
		// just testing 
		QObject::connect( w_openButton, SIGNAL(clicked()), this, SLOT(on_pushButton_clicked1()));

// 		QObject::connect( m_listWidget, SIGNAL(itemChanged(QListWidgetItem*)),
// 			this, SLOT(highlightChecked(QListWidgetItem*)));
		//	QObject::connect(m_listWidget, SIGNAL(itemSelectionChanged()),this,SLOT(selectedItem()));
//		QObject::connect( m_listWidget,    SIGNAL(itemClicked()), this, SLOT(clickedItem()));
	//	QObject::connect( m_saveButton, SIGNAL(clicked()),     this, SLOT(save()));
	
		QObject::connect( m_closeButton,    SIGNAL(clicked()),     this, SLOT(close()));
		QObject::connect( m_loadButton,     SIGNAL(clicked()),     this, SLOT(open()));
		QObject::connect( m_bonCreateReport,SIGNAL(clicked()),     this, SLOT(createBonReport()));
		QObject::connect( m_listUnite,      SIGNAL(activated(int)),this, SLOT(currentUniteON()));
		QObject::connect( m_saveSelectBtn,  SIGNAL(clicked()),     this, SLOT(savetest()));
		QObject::connect( m_tblWidget,      SIGNAL(itemClicked(QTableWidgetItem*)), this, SLOT(testItemClick(QTableWidgetItem*)));
	}

	// pdf2txt.py [options] filename.pdf
// Options:
// 	-o output file name
// 	- p comma - separated list of page numbers to extract
// 	- t output format(text / html / xml / tag[for Tagged PDFs])
// 	- O dirname(triggers extraction of images from PDF into directory)
// 	- P password
	void TestGuiLayout::on_pushButton_clicked1()
	{
		// some usefull path
 		const QString pythonScript = R"(F:\EllignoContract\BoDuc\pdfminerTxt\pdfminer-20140328\build/scripts-2.7\pdf2txt.py)";
		const QString w_pdfilesPath = R"(F:\EllignoContract\BoDuc\QtBdAppGuiTest\QtBdAppGuiTest\Pdf2Text\)"; // pdf files folder

		QProcess w_process(this);
		QProcessEnvironment env = QProcessEnvironment::systemEnvironment();
		env.insert("PYTHONPATH", "C:\\Python27\\Lib");
		env.insert("PYTHONHOME", "C:\\Python27");
		w_process.setProcessEnvironment(env);
		// Sets the working directory to dir. QProcess will start the process in this directory.
		// The default behavior is to start the process in the working directory of the calling process.
		w_process.setWorkingDirectory(w_pdfilesPath); // otherwise set path working dir of app

		//QStringList params;
// 		QString w_testArgStr("desilets.pdf");
// 		QString w_tesTxtFile("desilets.txt");
// 		QString w_ofile("-o");
// 		QString w_txtTest = w_ofile + " " + w_pdfilesPath + w_tesTxtFile;
// 		QString w_argPDF = w_pdfilesPath + w_testArgStr;

		// params << "script.py -arg1 arg1"; example
	//	params << pythonScript << "desilets.pdf"; // "pdf2txt.py -o qtpdf2test.txt desilets.pdf";
		QStringList w_selectedFiles = QFileDialog::getOpenFileNames(
			this,
			"Select one or more files to open",
			w_pdfilesPath,
			"Text (*.pdf *.txt)");

		// String list contains the whole path
// 		QFileInfo w_fileInfo(w_selectedFiles.front());
// 		QString w_fname = w_fileInfo.fileName();
// 		QString w_bname = w_fileInfo.baseName();
//		QString w_extFile = w_fileInfo.suffix();
// 		QString w_complPdfFile = w_fname; // filename with corresponding extension
// 		QString w_complTxtFile = w_bname + ".txt";
// 		QString w_ofile("-o");
// 		QString w_txtTest = w_ofile + " " + w_pdfilesPath + w_tesTxtFile;
// 		QString w_argPDF = w_pdfilesPath + w_testArgStr;
// ***************** this cmd works ***********************
//  params << pythonScript << "-o desilets.txt" << "desilets.pdf";
	
    // now we go each file and convert
		QStringListIterator filesListIterator( w_selectedFiles);
		while( filesListIterator.hasNext())
		{
			// String list contains the whole path
			QFileInfo w_fileInfo(filesListIterator.next());
			QString w_fname = w_fileInfo.fileName();
			QString w_bname = w_fileInfo.baseName();
			QString w_complPdfFile = w_fname; // filename with corresponding extension
			QString w_complTxtFile = w_bname + ".txt";
			QString w_ofile("-o");
			QStringList params;
			//w_process.start("Python", params);
//			QStringList params;
			//std::cout << filesListIterator.next().constData() << std::endl;
			params << pythonScript << w_ofile + " " + w_complTxtFile << w_complPdfFile;

			// ...
			w_process.start("Python", params);
			if (w_process.waitForFinished(-1))
			{
				QByteArray p_stdout = w_process.readAll();
				QByteArray p_stderr = w_process.readAllStandardError();
				if (!p_stderr.isEmpty())
					std::cout << "Python error:" << p_stderr.data();
				//		qDebug() << "Python result=" << p_stdout;
				if (!p_stdout.isEmpty())
				{
					std::cout << "Python conversion:" << p_stdout.data();
				}
				p_stdout; // write to console
			}
			// kill process
			w_process.close();
		}
		// kill process
//		w_process.close();

		std::cout << "Finished conversion pdf of text\n";
	//	ui->lineEdit->setText(p_stdout);
	}
#if 0
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
