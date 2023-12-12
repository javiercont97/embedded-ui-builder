#include "editor.h"

#include <QApplication>
#include <QMessageBox>

#include "ui_editor.h"

Editor::Editor(QWidget *parent) : QMainWindow(parent), ui(new Ui::Editor) {
	ui->setupUi(this);

	this->setupEventConnections();
}

Editor::~Editor() { delete this->ui; }

void Editor::setupEventConnections() {
	// this->ui->actionClose_project
	connect(this->ui->actionClose_project, &QAction::triggered, this,
			&Editor::onCloseProject);
}

void Editor::closeEvent(QCloseEvent *event) {
		event->accept();
	QApplication::exit();

	QMainWindow::closeEvent(event);
}

void Editor::onCloseProject() {
	// this->hide();
	QApplication::exit();
}