#ifndef PROJECTSELECTOR_H
#define PROJECTSELECTOR_H

#include <QWidget>

#include "services/projectsservice.h"
#include "wizards/newprojectwizard.h"
#include "wizards/settings/settingsmenu.h"
#include "dto/createprojectdto.h"

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

	// Project wizard
	void onProjectCreated(CreateProjectDTO project);

   private:
	Ui::ProjectSelector *ui;
	ProjectsService *projectsService;
	NewProjectWizard *newProjectWizard;
	SettingsMenu *settingsMenu;
};
#endif	// PROJECTSELECTOR_H
