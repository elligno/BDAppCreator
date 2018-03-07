// C++ includes
#include <iostream>
// Qt includes
#include <QtWidgets/QWidget>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QHBoxLayout>

#include "BasicTest.h"


bdGui::BasicTest::BasicTest(QWidget *parent /*= Q_NULLPTR*/)
: m_testButton(Q_NULLPTR)
{
	//setupUi(this);
	createLayout();
	connect();
	setLayout(w_jean);
}

void bdGui::BasicTest::testButton()
{
	// do something
	int val = 0;
	float valf = 2.4;
}

void bdGui::BasicTest::connect()
{
	QObject::connect(m_testButton,SIGNAL(clicked()),this,SLOT(testButton()));
}

void bdGui::BasicTest::createLayout()
{
  w_jean = new QHBoxLayout;

	m_testButton = new QPushButton("Test123");
	m_testButton->setEnabled(true);
	w_jean->addWidget(m_testButton);
	/*setLayout(w_jean);*/
}
