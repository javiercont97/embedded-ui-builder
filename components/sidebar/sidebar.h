#ifndef SIDEBAR_H
#define SIDEBAR_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui {
class Sidebar;
}
QT_END_NAMESPACE

class Sidebar : public QWidget {
	Q_OBJECT
   public:
	explicit Sidebar(QWidget *parent = nullptr);
	~Sidebar();
	
   private:
	Ui::Sidebar *ui;
};

#endif	// SIDEBAR_H
