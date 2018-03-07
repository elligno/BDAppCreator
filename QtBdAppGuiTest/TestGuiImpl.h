#ifndef TESTGUIIMPL_H
#define TESTGUIIMPL_H

#include <QtWidgets/QDialog>

// forward declaration
class QWidget;
class QGroupBox;
class QPushButton;
class QListWidget;
class QProgressBar;
class QTableWidget;
class QListWidgetItem;
class QDialogButtonBox;

namespace bdGui  
{
	// check if it is supported by VS15 (C++11)
	// Answer is YES!!!
	template<typename T, typename S>
	auto multiply(T lhs, S rhs) -> decltype(lhs*rhs)
	{
		return lhs*rhs;
	}

class TestGuiImpl : public QDialog
{
    Q_OBJECT

public:
    TestGuiImpl(QWidget *parent = Q_NULLPTR);
public slots:
    void highlightChecked(QListWidgetItem* item);
    void save();
		void selectedItem();
		void clickedItem();
private:
    int m_currCount;
    int m_prevCount;
    QListWidget* m_listWidget;
		QTableWidget* m_tblWidget;
    QDialogButtonBox* m_buttonBox;
    QGroupBox* m_cmdBox;
    QPushButton* m_saveButton;   // when user push this button, report is saved
    QPushButton* m_closeButton;
    QProgressBar* m_progressBar; // adding a progress for testing purpose

    // some helper functions
    void createListWidget();
    void createOtherWidgets();
    void createLayout();
    void createConnections();
};
} // End of namespace
#endif // TESTGUIIMPL_H
