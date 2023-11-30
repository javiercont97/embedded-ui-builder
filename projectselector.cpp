#include "projectselector.h"
#include "./ui_projectselector.h"

#include <QDebug>
#include <QTableView>
#include <QLabel>
#include <QVBoxLayout>

ProjectSelector::ProjectSelector(QWidget *parent): QWidget(parent), ui(new Ui::ProjectSelector) {
    ui->setupUi(this);

    this->setupRecentProjectsList();
    this->setupEventConnections();
}

ProjectSelector::~ProjectSelector() {
    delete ui;
}

void ProjectSelector::setupRecentProjectsList() {
    this->projectsService = new ProjectsService(this);

    if(this->projectsService->getRecentProjectsList().isEmpty()) {
        QLabel *emptyMessage = new QLabel("<html><h2>It looks empty here</h2>Go ahead and create a new project</html>");
        emptyMessage->setAlignment(Qt::AlignCenter);
        ui->projectsList->setLayout(new QVBoxLayout(this));
        ui->projectsList->layout()->addWidget(emptyMessage);
    } else {
        QTableView *projectsList = new QTableView(this);
        ui->projectsList->setLayout(new QVBoxLayout(this));
        ui->projectsList->layout()->addWidget(projectsList);
    }

    //    ui->cloneBtn->setIcon(QApplication::style()->standardIcon(QStyle::StandardPixmap::SP_DialogSaveButton));
    //    ui->openBtn->setIcon(QApplication::style()->standardIcon(QStyle::SP_DirOpenIcon));
    //    ui->createBtn->setIcon(QApplication::style()->standardIcon(QStyle::SP_FileDialogNewFolder));
}

void ProjectSelector::setupEventConnections() {
    connect(this->ui->cloneBtn, &QPushButton::clicked, this, &ProjectSelector::onCloneRepository);
    connect(this->ui->openBtn, &QPushButton::clicked, this, &ProjectSelector::onOpenProject);
    connect(this->ui->createBtn, &QPushButton::clicked, this, &ProjectSelector::onCreateProject);
}

void ProjectSelector::onCloneRepository() {
    qDebug() << "Clone repository";
}

void ProjectSelector::onOpenProject() {
    qDebug() << "Open project";
}

void ProjectSelector::onCreateProject() {
    qDebug() << "Create project";
//    NewProjectWizard *newProjectWizard = new NewProjectWizard(this);
//    newProjectWizard->show();
}

