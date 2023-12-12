#include "projectselector.h"

#include <QDebug>
#include <QMessageBox>
#include <QTableWidget>
#include <QVBoxLayout>

#include "./ui_projectselector.h"

ProjectSelector::ProjectSelector(QWidget *parent)
	: QWidget(parent), ui(new Ui::ProjectSelector) {
	ui->setupUi(this);
	this->projectsService = new ProjectService(this);
	this->newProjectWizard = new NewProjectWizard(this);
	this->newProjectWizard->setModal(true);
	this->settingsMenu = new SettingsMenu(this);
	this->editor = new Editor(this);

	this->setupRecentProjectsList();
	this->setupEventConnections();
}

ProjectSelector::~ProjectSelector() {
	delete ui;
	delete this->editor;
}

void ProjectSelector::setupRecentProjectsList() {
	if (this->emptyMessage) {
		this->ui->projectsList->layout()->removeWidget(this->emptyMessage);
		delete this->emptyMessage;
		this->emptyMessage = nullptr;
	}
	if (this->list) {
		this->ui->projectsList->layout()->removeWidget(this->list);
		delete this->list;
		this->list = nullptr;
	}

	QList<ProjectDTO *> recentProjects =
		this->projectsService->getRecentProjectsList();
	if (recentProjects.isEmpty()) {
		this->emptyMessage = new QLabel(
			"<html><h2>It looks empty here</h2>Go ahead and create a new "
			"project</html>",
			this);
		this->emptyMessage->setAlignment(Qt::AlignCenter);
		this->ui->projectsList->layout()->addWidget(emptyMessage);
	} else {
		this->list = new QListWidget(this);
		foreach (ProjectDTO *project, recentProjects) {
			this->list->insertItem(this->list->count(), project->location);
			this->ui->projectsList->layout()->addWidget(this->list);
		}
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

	// Settings menu
	connect(this->settingsMenu, &SettingsMenu::settingsApplied, this,
			&ProjectSelector::onSettingsApplied);

	// List
	connect(this->list, &QListWidget::itemDoubleClicked, this,
			&ProjectSelector::onProjectSelectedFromList);
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

void ProjectSelector::onSettingsApplied() {
	this->projectsService->loadRecentProjects();
	this->setupRecentProjectsList();
}

void ProjectSelector::onProjectCreated(CreateProjectDTO project) {
	this->projectsService->createNewProject(project);
	this->setupRecentProjectsList();

	this->editor->show();
	this->hide();
}

void ProjectSelector::onProjectSelectedFromList(QListWidgetItem *item) {
	this->projectsService->openProject(item->text());
	this->hide();
	this->editor->show();
}
