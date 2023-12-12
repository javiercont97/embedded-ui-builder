#ifndef EDITOR_H
#define EDITOR_H

#include <QCloseEvent>
#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class Editor;
}
QT_END_NAMESPACE

class Editor : public QMainWindow {
	Q_OBJECT
   public:
	Editor(QWidget *parent= nullptr);
	~Editor();

   private:
	void setupEventConnections();

   protected:
	// Inherited from QMainWindow
	void closeEvent(QCloseEvent *event) override;

	void onCloseProject();

   private:
	Ui::Editor *ui;
};

#endif