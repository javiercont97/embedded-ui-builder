#ifndef PROJECTSSERVICE_H
#define PROJECTSSERVICE_H

#include <QList>
#include <QObject>
#include <QSettings>
#include <QFile>
#include <QDir>

#include "../dto/projectdto.h"
#include "../dto/createprojectdto.h"

class ProjectService : public QObject {
	Q_OBJECT
   public:
	explicit ProjectService(QObject *parent = nullptr);

	ProjectDTO* createNewProject(CreateProjectDTO project);
	ProjectDTO* openProject(QString path);
	QList<ProjectDTO *> getRecentProjectsList() const;

	void loadRecentProjects();
	void clearRecentProjects();

	
   private:
	void saveRecentProjects();

   private:
	ProjectDTO* currentProject;
	QList<ProjectDTO *> recentProjectsList;
};

#endif	// PROJECTSSERVICE_H
