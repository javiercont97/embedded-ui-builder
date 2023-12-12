#include "browsecomponent.h"

#include <QDir>
#include <QFileDialog>
#include <QMessageBox>
#include <QSettings>
#include <QStyle>

#include "ui_browsecomponent.h"

BrowseComponent::BrowseComponent(QWidget *parent)
	: QWidget(parent), ui(new Ui::BrowseComponent) {
	ui->setupUi(this);
	this->setupEventConnections();
	this->setFocusProxy(this->ui->targetLocation);
	// Set default mode
	this->mode = BrowseMode::DIRECTORY;
}

BrowseComponent::~BrowseComponent() { delete ui; }

void BrowseComponent::setMode(BrowseMode mode) { this->mode = mode; }

BrowseMode BrowseComponent::getMode() { return this->mode; }

void BrowseComponent::setPlaceholderText(QString text) {
	this->ui->targetLocation->setPlaceholderText(text);
}

void BrowseComponent::clearFields() {
	this->ui->targetLocation->setText("");
	this->clearError();
}

QString BrowseComponent::getPath() {
	return this->ui->targetLocation->text();
}

void BrowseComponent::showError() {
	this->ui->targetLocation->setProperty("showerror", true);
	this->ui->targetLocation->style()->polish(this->ui->targetLocation);
}

void BrowseComponent::clearError() {
	this->ui->targetLocation->setProperty("showerror", false);
	this->ui->targetLocation->style()->polish(this->ui->targetLocation);
}

void BrowseComponent::setupEventConnections() {
	connect(this->ui->browseBtn, &QPushButton::clicked, this,
			&BrowseComponent::onBrowseClicked);
	connect(this->ui->targetLocation, &QLineEdit::textEdited, this,
			&BrowseComponent::onPathChanged);
}

void BrowseComponent::onBrowseClicked() {
	QSettings settings;
	QString path;

	if (this->mode == BrowseMode::DIRECTORY) {
		path = QFileDialog::getExistingDirectory(
		this, "Project location",
		settings.value("defaultProjectLocation").toString(),
		QFileDialog::Option::ShowDirsOnly);
	} else {
		path = QFileDialog::getOpenFileName(
		this, "Project location",
		settings.value("defaultProjectLocation").toString());
	}
	if (path.isEmpty()) return;

	ui->targetLocation->setText(path);
	emit this->pathChanged(path);
}

void BrowseComponent::onPathChanged(QString path) {
	switch (this->mode) {
		case BrowseMode::FILE:
			if (!QFile(path).exists()) {
				this->showError();
				return;
			}
			break;
		case BrowseMode::DIRECTORY:
			if (!QDir(path).exists()) {
				this->showError();
				return;
			}
			break;
	}

	this->clearError();
}