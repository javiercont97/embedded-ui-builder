#ifndef PROJECTSSERVICE_H
#define PROJECTSSERVICE_H

#include <QList>
#include <QObject>
#include <QSettings>

#include "../dto/projectdto.h"

class ProjectsService : public QObject {
	Q_OBJECT
   public:
	explicit ProjectsService(QObject *parent = nullptr);

	ProjectDTO createNewProject();
	QList<ProjectDTO> getRecentProjectsList() const;

   private:
	void loadRecentProjects();
	void saveRecentProjects();
	void clearRecentProjects();

   private:
	ProjectDTO currentProject;
	QList<ProjectDTO> recentProjectsList;
};

#endif	// PROJECTSSERVICE_H
