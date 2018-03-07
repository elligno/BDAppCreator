#pragma once

#include <QtWidgets/QDialog>

// forward declaration
class QWidget;
class QPushButton;
class QHBoxLayout;

namespace bdGui {
	class BasicTest : public QDialog
	{
		Q_OBJECT
	public:
		BasicTest(QWidget *parent = Q_NULLPTR);
  public slots:
	void testButton();
	private:
		QPushButton* m_testButton;
		void connect();
		void createLayout();
		QHBoxLayout* w_jean;
	};
}//end of namespace
