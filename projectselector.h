#ifndef PROJECTSELECTOR_H
#define PROJECTSELECTOR_H

#include <QWidget>

#include "services/projectsservice.h"

QT_BEGIN_NAMESPACE
namespace Ui { class ProjectSelector; }
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
    void onCloneRepository();
    void onOpenProject();
    void onCreateProject();

private:
    Ui::ProjectSelector *ui;
    ProjectsService *projectsService;
};
#endif // PROJECTSELECTOR_H
