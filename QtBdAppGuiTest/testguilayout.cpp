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
#include <QtCore/QTextStream>
#include <QtCore/QFile>
#include <QComboBox>
#include <QLabel>
// App include
#include "testguilayout.h"

namespace bdGui {
TestGuiLayout::TestGuiLayout(QWidget *parent /*= Q_NULLPTR*/)
: QDialog(parent),
  m_listWidget(Q_NULLPTR),
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
	m_listUnite(Q_NULLPTR)
{
   setWindowTitle("BdApp Bon De Livraison (creator)");

   // create all components for the GUI
   createListWidget();
   createOtherWidgets();
   createLayout();
   createConnections();

	 // set initial
	 m_progressBarU1->setValue(4);


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

void TestGuiLayout::save()
{
	// not implemented yet
	m_progressBarU1->setValue(1);
	m_progressBarU2->setValue(4);
}

void TestGuiLayout::clickedItem()
{
	// not implemented yet
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
    for(int i = 0; i < m_listWidget->count(); ++i) 
		{
        w_item = m_listWidget->item(i);
        w_item->setFlags(w_item->flags() | Qt::ItemIsUserCheckable);
        w_item->setCheckState(Qt::Unchecked);
    }
}

void TestGuiLayout::createOtherWidgets()
{
	// create the group box
	m_cmdBox = new QGroupBox(tr("Liste de Commandes"));
	m_uniteBox = new QGroupBox(tr("Liste des Unites"));
	// create buttons at the bottom 
	m_buttonBox = new QDialogButtonBox;
	m_saveButton = m_buttonBox->addButton(QDialogButtonBox::Save);
	m_closeButton = m_buttonBox->addButton(QDialogButtonBox::Close);
	m_clearButton = m_buttonBox->addButton(QDialogButtonBox::Cancel);
	// widget that hold other widget separated by a boundary
	m_splitWidget = new QSplitter;
}

void TestGuiLayout::createLayout()
{
	// Create a first row of buttons
	QHBoxLayout* w_buttonsTop = new QHBoxLayout;
	
	// List of unite available
	QLabel* w_listUniteLabl = new QLabel(tr("Unite Disponible"));
	m_listUnite = new QComboBox;
	QStringList w_listUniteAvailable = { QString("Unite1"),QString("Unite2"), QString("Unite3"), QString("Unite4") };
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

	// create report button

	// display box (command display in the right panel)
	setListWidgetBox();
	QBoxLayout* w_horizontalLayout = setBottomButtons();
	setUniteBox(); // create the display box that list unite of transport

	// main dialog
	QVBoxLayout* w_mainLayout = new QVBoxLayout;
	w_mainLayout->addLayout(w_buttonsTop);
	w_mainLayout->addWidget(m_splitWidget);
	w_mainLayout->addLayout(w_horizontalLayout);
	setLayout(w_mainLayout);
}

void TestGuiLayout::setUniteBox()
{
	// create a layout for progress bar in a vertical layout
	QVBoxLayout* w_vProgressBar = new QVBoxLayout;

	QLabel* w_barU1 = new QLabel(tr("Unite 1"));
	m_progressBarU1 = new QProgressBar;
// 	m_progressBarU1->setMinimum(m_pbarmin);
// 	m_progressBarU1->setMaximum(m_pbarmax);

//	m_progressBarU1->setValue(5);
	// 		w_vProgressBar->addWidget(w_barU1);
	//     w_vProgressBar->addWidget(m_progressBarU1);

	// Both label and button together
	QVBoxLayout* w_lablandLayout1 = new QVBoxLayout;
	w_lablandLayout1->addWidget(w_barU1);
	w_lablandLayout1->addWidget(m_progressBarU1);
	w_vProgressBar->addStretch(2);
	w_vProgressBar->addLayout(w_lablandLayout1);
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

	m_uniteBox->setLayout(w_vProgressBar);
	// add ... to be completed
	m_splitWidget->addWidget(m_uniteBox);
}

QBoxLayout* TestGuiLayout::setBottomButtons()
{
	// buttons at the bottom of the dialog
	QHBoxLayout* w_horizontalLayout = new QHBoxLayout;
	w_horizontalLayout->addWidget(m_buttonBox);

	return w_horizontalLayout;
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
	QObject::connect(m_listWidget, SIGNAL(itemChanged(QListWidgetItem*)),
		this, SLOT(highlightChecked(QListWidgetItem*)));
	//	QObject::connect(m_listWidget, SIGNAL(itemSelectionChanged()),this,SLOT(selectedItem()));
	QObject::connect(m_listWidget, SIGNAL(itemClicked()), this, SLOT(clickedItem()));
	QObject::connect(m_saveButton, SIGNAL(clicked()), this, SLOT(save()));
	QObject::connect(m_closeButton, SIGNAL(clicked()), this, SLOT(close()));
}
} // End of namespace
