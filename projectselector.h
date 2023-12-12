#ifndef PROJECTSELECTOR_H
#define PROJECTSELECTOR_H

#include <QLabel>
#include <QListWidget>
#include <QWidget>

#include "dto/createprojectdto.h"
#include "editor/editor.h"
#include "services/projectservice.h"
#include "wizards/new_project/newprojectwizard.h"
#include "wizards/settings/settingsmenu.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class ProjectSelector;
}
QT_END_NAMESPACE

class ProjectSelector : public QWidget {
	Q_OBJECT

   public:
	ProjectSelector(QWidget *parent = nullptr);
	~ProjectSelector();

   private:
	void setupRecentProjectsList();
	void setupEventConnections();

   private slots:
	void onCloneRepositoryClicked();
	void onOpenProjectClicked();
	void onCreateProjectClicked();
	void onSettingsClicked();

	void onSettingsApplied();

	// Project wizard
	void onProjectCreated(CreateProjectDTO project);
	void onProjectSelectedFromList(QListWidgetItem *item);

   private:
	Ui::ProjectSelector *ui;
	// Services
	ProjectService *projectsService;

	// Wizards
	NewProjectWizard *newProjectWizard;
	SettingsMenu *settingsMenu;

	// Main windows
	Editor *editor;

	// Widgets
	QLabel *emptyMessage = nullptr;
	QListWidget *list = nullptr;
};
#endif	// PROJECTSELECTOR_H