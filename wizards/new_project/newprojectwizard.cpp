#include "newprojectwizard.h"

#include <QDir>
#include <QMessageBox>
#include <QRegularExpression>
#include <QRegularExpressionValidator>
#include <QSettings>

#include "ui_newprojectwizard.h"

NewProjectWizard::NewProjectWizard(QWidget *parent)
	: QDialog(parent), ui(new Ui::NewProjectWizard) {
	ui->setupUi(this);
	this->setupEventConnections();
	this->setupValidators();
	this->ui->projectLocation->setPlaceholderText("Project location");
	this->ui->projectLocation->setMode(BrowseMode::DIRECTORY);
}

NewProjectWizard::~NewProjectWizard() { delete ui; }

void NewProjectWizard::setupEventConnections() {
	connect(this->ui->hasUI, &QCheckBox::stateChanged, this,
			&NewProjectWizard::onUICheckboxChanged);
	connect(this->ui->cancelBtn, &QPushButton::clicked, this,
			&NewProjectWizard::onCancelClicked);
	connect(this->ui->projectName, &QLineEdit::textChanged, this,
			&NewProjectWizard::onProjectNameChanged);
	connect(this->ui->createProjectBtn, &QPushButton::clicked, this,
			&NewProjectWizard::onCreateClicked);
}

void NewProjectWizard::setupValidators() {
	this->ui->projectName->setValidator(new QRegularExpressionValidator(
		QRegularExpression("[a-z,A-Z][a-z,A-Z,_]*"), this->ui->projectName));
		
}

void NewProjectWizard::clearFields() {
	this->ui->projectName->setText("");
	this->ui->projectName->setProperty("showerror", false);
	this->ui->projectName->style()->polish(this->ui->projectName);
	this->ui->projectLocation->clearFields();
	this->ui->device->setCurrentIndex(0);
	this->ui->hasUI->setCheckState(Qt::CheckState::Unchecked);
}

void NewProjectWizard::onUICheckboxChanged(int state) {
	if (state) {
		this->ui->hasUI->setText("True");
		return;
	}
	this->ui->hasUI->setText("False");
}

void NewProjectWizard::onProjectNameChanged(QString text) {
	int cursor = 0;
	if (this->ui->projectName->validator()->validate(text, cursor) !=
		QValidator::Acceptable) {
		this->ui->projectName->setProperty("showerror", true);
	} else {
		this->ui->projectName->setProperty("showerror", false);
	}
	this->ui->projectName->style()->polish(this->ui->projectName);
}

void NewProjectWizard::onCancelClicked() {
	this->clearFields();
	this->reject();
}

void NewProjectWizard::onCreateClicked() {
	bool error = false;
	if (this->ui->projectName->text().isEmpty()) {
		this->ui->projectName->setProperty("showerror", true);
		this->ui->projectName->style()->polish(this->ui->projectName);
		error = true;
	}
	if (this->ui->projectLocation->getPath().isEmpty()) {
		this->ui->projectLocation->showError();
		error = true;
	}

	if (error) {
		QMessageBox::critical(this, "Input error",
							  "Please fill all the required fields");
		return;
	}
	QDir targetLocation(this->ui->projectLocation->getPath());
	if (targetLocation.exists("embedded-package.json")) {
		QMessageBox::StandardButton response = QMessageBox::question(this, "Override project", "Do you want to override existing project?");
		if (response == QMessageBox::StandardButton::No)return;
	}
	
	CreateProjectDTO project(
		this->ui->projectName->text(), this->ui->projectLocation->getPath(),
		this->ui->device->currentText(), this->ui->hasUI->isChecked());
	emit this->projectCreated(project);
	this->clearFields();
	this->accept();
}