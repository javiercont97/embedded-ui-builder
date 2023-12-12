#ifndef SETTINGSMENU_H
#define SETTINGSMENU_H

#include <QDialog>

#include "../../services/projectservice.h"

enum class ACTIONS { REMOVE, UPDATE };

enum class SETTING_TYPES { RECENT_PROJECTS_LIST };

struct Task {
	ACTIONS action;
	SETTING_TYPES target;
};

QT_BEGIN_NAMESPACE
namespace Ui {
class SettingsMenu;
}
QT_END_NAMESPACE

class SettingsMenu : public QDialog {
	Q_OBJECT

   public:
	explicit SettingsMenu(QWidget *parent = nullptr);
	~SettingsMenu();

   signals:
	void settingsApplied();

   private:
	void setupEventConnections();
	void runTask(Task task);

   private slots:
	void onClearRecentProjectsClicked();
	void onApplyChanges();
	void onDiscardChanges();

   private:
	Ui::SettingsMenu *ui;
	QList<Task> tasksToPerform;

	ProjectService projectService;
};

#endif	// SETTINGSMENU_H
