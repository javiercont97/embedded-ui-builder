#include "projectselector.h"

#include <QDebug>
#include <QLabel>
#include <QMessageBox>
#include <QTableView>
#include <QVBoxLayout>

#include "./ui_projectselector.h"

ProjectSelector::ProjectSelector(QWidget *parent)
	: QWidget(parent), ui(new Ui::ProjectSelector) {
	ui->setupUi(this);
	this->newProjectWizard = new NewProjectWizard(this);
	this->newProjectWizard->setModal(true);
	this->settingsMenu = new SettingsMenu(this);

	this->setupRecentProjectsList();
	this->setupEventConnections();
}

ProjectSelector::~ProjectSelector() { delete ui; }

void ProjectSelector::setupRecentProjectsList() {
	this->projectsService = new ProjectsService(this);

	if (this->projectsService->getRecentProjectsList().isEmpty()) {
		QLabel *emptyMessage = new QLabel(
			"<html><h2>It looks empty here</h2>Go ahead and create a new "
			"project</html>");
		emptyMessage->setAlignment(Qt::AlignCenter);
		ui->projectsList->layout()->addWidget(emptyMessage);
	} else {
		QTableView *projectsList = new QTableView(this);
		ui->projectsList->layout()->addWidget(projectsList);
	}
}

void ProjectSelector::setupEventConnections() {
	// Main menu Buttons
	connect(this->ui->cloneBtn, &QPushButton::clicked, this,
			&ProjectSelector::onCloneRepositoryClicked);
	connect(this->ui->openBtn, &QPushButton::clicked, this,
			&ProjectSelector::onOpenProjectClicked);
	connect(this->ui->createBtn, &QPushButton::clicked, this,
			&ProjectSelector::onCreateProjectClicked);

	// Open settings button
	connect(this->ui->settingsBtn, &QPushButton::clicked, this,
			&ProjectSelector::onSettingsClicked);

	// Create Project wizard
	connect(this->newProjectWizard, &NewProjectWizard::projectCreated, this,
			&ProjectSelector::onProjectCreated);
}

void ProjectSelector::onCloneRepositoryClicked() {
	qDebug() << "Clone repository";
}

void ProjectSelector::onOpenProjectClicked() { qDebug() << "Open project"; }

void ProjectSelector::onCreateProjectClicked() {
	qDebug() << "Create project";
	//    this->projectsService->
	newProjectWizard->show();
}

void ProjectSelector::onSettingsClicked() {
	qDebug() << "settings";
	this->settingsMenu->show();
}

void ProjectSelector::onProjectCreated(CreateProjectDTO project) {
	// QMessageBox::information(
	// 	this, "info",
	// 	QString::asprintf(
	// 		"%s in %s with %s and %s", project.projectName.toStdString().c_str(),
	// 		project.projectPath.toStdString().c_str(), project.device.toStdString().c_str(),
	// 		project.hasUI ? "has ui" : "does not have ui")
	// 		.toLatin1());
}