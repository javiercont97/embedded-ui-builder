#ifndef PROJECTSSERVICE_H
#define PROJECTSSERVICE_H

#include <QObject>
#include <QList>
#include <QSettings>

#include "../dto/project.h"

class ProjectsService : public QObject {
    Q_OBJECT
public:
    explicit ProjectsService(QObject *parent = nullptr);

    QList<Project> getRecentProjectsList() const;

private:
    void loadRecentProjects();
    void saveRecentProjects();
    void clearRecentProjects();

private:
    Project currentProject;
    QList<Project> recentProjectsList;
};

#endif // PROJECTSSERVICE_H
