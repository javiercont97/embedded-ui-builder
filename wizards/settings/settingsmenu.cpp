#include "settingsmenu.h"

#include <QSettings>

#include "../../components/browse/browsecomponent.h"
#include "ui_settingsmenu.h"

SettingsMenu::SettingsMenu(QWidget *parent)
	: QDialog(parent), ui(new Ui::SettingsMenu) {
	ui->setupUi(this);
	this->setupEventConnections();
}

SettingsMenu::~SettingsMenu() { delete ui; }

void SettingsMenu::setupEventConnections() {
	// First config tab - General
	connect(this->ui->clearRecentProjectBtn, &QPushButton::clicked, this,
			&SettingsMenu::onClearRecentProjectsClicked);

	// Apply or discard
	connect(this->ui->applyChangesBtn, &QPushButton::clicked, this,
			&SettingsMenu::onApplyChanges);

	connect(this->ui->discardChangesBtn, &QPushButton::clicked, this,
			&SettingsMenu::onDiscardChanges);
}

void SettingsMenu::runTask(Task task) {
	// QSettings settings;
	if (task.action == ACTIONS::REMOVE) {
		switch (task.target) {
			case SETTING_TYPES::RECENT_PROJECTS_LIST:
				projectService.clearRecentProjects();
				break;

			default:
				break;
		}
	} else if (task.action == ACTIONS::UPDATE) {
		switch (task.target) {
			case SETTING_TYPES::RECENT_PROJECTS_LIST:
				break;

			default:
				break;
		}
	}
}

void SettingsMenu::onClearRecentProjectsClicked() {
	this->tasksToPerform.push_back({
		action : ACTIONS::REMOVE,
		target : SETTING_TYPES::RECENT_PROJECTS_LIST
	});
}

void SettingsMenu::onApplyChanges() {
	for (Task task : this->tasksToPerform) {
		this->runTask(task);
	}

	this->tasksToPerform.clear();
	emit this->settingsApplied();
	this->accept();
}

void SettingsMenu::onDiscardChanges() {
	this->tasksToPerform.clear();
	this->reject();
}