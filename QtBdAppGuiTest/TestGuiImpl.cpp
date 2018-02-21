#include <iostream>
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
#include <QtCore/QTextStream>
#include <QtCore/QFile>
//
#include "TestGuiImpl.h"

namespace bdGui {

TestGuiImpl::TestGuiImpl(QWidget *parent)
: QDialog(parent),
  m_currCount(0),
  m_prevCount(0)
{
    setWindowTitle("BdApp Bon De Livraison (creator)");

    // create all components for the GUI
    createListWidget();
    createOtherWidgets();
    createLayout();
    createConnections();

    // set initial
    m_progressBar->setValue(0);

    // just configuring the progress bar to display
    if(!m_progressBar->isEnabled())
    {
        m_progressBar->setEnabled(true);
    }
    if(m_progressBar->minimum()!=0)
    {
        m_progressBar->setMinimum(0);
    }
    if(m_progressBar->maximum()!=10)
    {
        m_progressBar->setMaximum(10);
    }
}

void TestGuiImpl::createListWidget(){
    m_listWidget = new QListWidget;
    QStringList w_strList;
    w_strList << "Commande_1" << "Commande_2" << "Commande_3" << "Commande_4"
              << "Commande_5" << "Commande_6" << "Commande_7" << "Commande_8";

    // add list widget item to the list widget
    m_listWidget->addItems(w_strList);

    // retrieve list widget item to configure
    QListWidgetItem* w_item = Q_NULLPTR;
    for(int i = 0; i < m_listWidget->count(); ++i){
        w_item = m_listWidget->item(i);
        w_item->setFlags(w_item->flags() | Qt::ItemIsUserCheckable);
        w_item->setCheckState(Qt::Unchecked);
    }

    // shall have no item selected
    QList<QListWidgetItem*> w_check = m_listWidget->selectedItems();
    if(w_check.size()!=0)
    {
        QMessageBox::information(this, tr("BdApp Bon De Livraison"),
                                 tr("Initial item list not empty."),
                                 QMessageBox::Ok);;
    }
}

void TestGuiImpl::createOtherWidgets(){
    m_cmdBox = new QGroupBox(tr("Liste de Commandes"));
    m_buttonBox = new QDialogButtonBox;
    m_saveButton = m_buttonBox->addButton(QDialogButtonBox::Save);
    m_closeButton = m_buttonBox->addButton(QDialogButtonBox::Close);
    // testing purpose, add a progress bar
    m_progressBar = new QProgressBar;
}

void TestGuiImpl::createLayout(){
    QVBoxLayout* w_viewLayout = new QVBoxLayout;
    w_viewLayout->addWidget(m_listWidget);
    m_cmdBox->setLayout(w_viewLayout); // add it to whole layout

    QHBoxLayout* w_horizontalLayout = new QHBoxLayout;
    w_horizontalLayout->addWidget(m_buttonBox);

    QVBoxLayout* w_mainLayout = new QVBoxLayout;
    w_mainLayout->addWidget(m_cmdBox);
    w_mainLayout->addLayout(w_horizontalLayout);
    w_mainLayout->addWidget(m_progressBar);

    setLayout(w_mainLayout);
}

void TestGuiImpl::createConnections(){
    QObject::connect(m_listWidget, SIGNAL(itemChanged(QListWidgetItem*)),
                     this, SLOT(highlightChecked(QListWidgetItem*)));

	//	QObject::connect(m_listWidget, SIGNAL(itemSelectionChanged()),this,SLOT(selectedItem()));
		QObject::connect(m_listWidget, SIGNAL(itemClicked()), this, SLOT(clickedItem()));
		QObject::connect(m_saveButton, SIGNAL(clicked()), this, SLOT(save()));
    QObject::connect(m_closeButton, SIGNAL(clicked()), this, SLOT(close()));
}

void TestGuiImpl::highlightChecked(QListWidgetItem *aItem){
    if(aItem->checkState() == Qt::Checked)
        aItem->setBackgroundColor(QColor("#ffffb2"));
    else
        aItem->setBackgroundColor(QColor("#ffffff"));
}

void TestGuiImpl::save()
{ // create bon de livraison
	short w_row = {};
	const int w_numItem = m_listWidget->count();
	for( auto i = 0; i < w_numItem; ++i)
	{
		QListWidgetItem* w_checked = m_listWidget->item(i);
		if (w_checked->checkState() == Qt::CheckState::Checked)
		{
			++w_row;
			std::cout << "Just checking basic stuff\n";
		}
	}//for-loop

	std::cout << "Number of selected item is: " << w_row << "\n";
	// return the value of the progress bar
	int w_currValue = m_progressBar->value();
	// set it to the new value
	m_progressBar->setValue(w_currValue + w_row);

#if 0
	// check for selected cmd (current)
    // shall have no item selected
    QList<QListWidgetItem*> w_checkList = m_listWidget->selectedItems();
    int w_selectedItems = w_checkList.size(); // include all
 
		// since first time we have on;y one element
		if (w_checkList.front()->checkState() == Qt::CheckState::Checked)
		{
			std::cout << "Just checking basic stuff\n";
		}

    // ...
    if(m_prevCount == 0) // first time
    {
        m_prevCount = w_selectedItems;
        m_currCount = m_prevCount;

        // return the value of the progress bar
        int w_currValue = m_progressBar->value();
        // set it to the new value
        m_progressBar->setValue(w_currValue+m_currCount);
    }
    else { // new selection has been done
     m_currCount = w_selectedItems - m_prevCount;
     m_prevCount = w_selectedItems;
     // return the value of the progress bar
     int w_currValue = m_progressBar->value();
     // set it to the new value
     m_progressBar->setValue(w_currValue+m_currCount);
    }

    // return the value of the progress bar
 //   int w_currValue = m_progressBar->value();
    // set it to the new value
 //   m_progressBar->setValue(w_currValue+m_currCount);
#endif

    QFile w_file("Bon_de_livraison.txt");
    if( !w_file.open(QIODevice::WriteOnly | QIODevice::Text))
        return;

    QTextStream w_out(&w_file);
    w_out << "Bon de commandes:" << "\n";

    QListWidgetItem* w_item = Q_NULLPTR;
    for( int i = 0; i < m_listWidget->count(); ++i) {
        w_item = m_listWidget->item(i);
        if( w_item->checkState() == Qt::Checked)
            w_out << w_item->text() << "\n";
    }

    QMessageBox::information(this, tr("BdApp Bon De Livraison"),
                                   tr("Bon de livraison were saved."),
                                   QMessageBox::Ok);
}

void TestGuiImpl::selectedItem()
{
// 	QList<QListWidgetItem*> w_listCount = m_listWidget->selectedItems();
// 	QListWidgetItem* w_checked = w_listCount.front();
// 	if( w_checked->isSelected())
// 	{
// 		std::cout << "Just checking basic stuff\n";
// 	}
	short w_row = {};
	const int w_numItem = m_listWidget->count();
	for( auto i=0;i<w_numItem;++i)
	{
		QListWidgetItem* w_checked = m_listWidget->item(i);
		if( w_checked->checkState() == Qt::CheckState::Checked)
		{
			++w_row;
			std::cout << "Just checking basic stuff\n";
		}
		std::cout << "Number of selected item is: " << w_row << "\n";
	}
//	int w_count = w_listCount.size();
}

void TestGuiImpl::clickedItem()
{
	// checking state of the clicked item
	QListWidgetItem* w_test123 = m_listWidget->currentItem();
  if( w_test123->checkState()==Qt::CheckState::Checked)
	{
		std::cout << "We have a checked state";
	}
}
}// End of namespace
