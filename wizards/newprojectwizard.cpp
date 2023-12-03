#include "newprojectwizard.h"

#include <QDir>
#include <QFileDialog>
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
}

NewProjectWizard::~NewProjectWizard() { delete ui; }

void NewProjectWizard::setupEventConnections() {
	connect(this->ui->hasUI, &QCheckBox::stateChanged, this,
			&NewProjectWizard::onUICheckboxChanged);
	connect(this->ui->cancelBtn, &QPushButton::clicked, this,
			&NewProjectWizard::onCancelClicked);
	connect(this->ui->projectName, &QLineEdit::textChanged, this,
			&NewProjectWizard::onProjectNameChanged);
	connect(this->ui->projectLocation, &QLineEdit::textChanged, this,
			&NewProjectWizard::onPathChanged);
	connect(this->ui->browseBtn, &QPushButton::clicked, this,
			&NewProjectWizard::onBrowseClicked);
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

	this->ui->projectLocation->setText("");
	this->ui->projectLocation->setProperty("showerror", false);
	this->ui->projectLocation->style()->polish(this->ui->projectLocation);

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

void NewProjectWizard::onPathChanged(QString path) {
	int cursor = 0;

	QDir location(path);
	if (!location.exists()) {
		this->ui->projectLocation->setProperty("showerror", true);
	} else {
		this->ui->projectLocation->setProperty("showerror", false);
	}
	this->ui->projectLocation->style()->polish(this->ui->projectLocation);
}

void NewProjectWizard::onCancelClicked() {
	this->clearFields();
	this->reject();
}

void NewProjectWizard::onBrowseClicked() {
	QSettings settings;
	QString path = QFileDialog::getExistingDirectory(
		this, "Project location",
		settings.value("lastNewProjectPath").toString(),
		QFileDialog::Option::ShowDirsOnly);
	if (path.isEmpty()) return;

	ui->projectLocation->setText(path);
	settings.setValue("lastNewProjectPath", path);
}

void NewProjectWizard::onCreateClicked() {
	bool error = false;
	if (this->ui->projectName->text().isEmpty()) {
		this->ui->projectName->setProperty("showerror", true);
		this->ui->projectName->style()->polish(this->ui->projectName);
		error = true;
	}
	if (this->ui->projectLocation->text().isEmpty()) {
		this->ui->projectLocation->setProperty("showerror", true);
		this->ui->projectLocation->style()->polish(this->ui->projectLocation);
		error = true;
	}

	if (error) {
		QMessageBox::critical(this, "Input error",
							  "Please fill all the required fields");
		return;
	}
	
	CreateProjectDTO project(
		this->ui->projectName->text(), this->ui->projectLocation->text(),
		this->ui->device->currentText(), this->ui->hasUI->isChecked());
	emit this->projectCreated(project);
	this->clearFields();
	this->accept();
}