#include "projectsservice.h"

ProjectsService::ProjectsService(QObject *parent) : QObject{parent} {
	loadRecentProjects();
}

ProjectDTO ProjectsService::createNewProject() {}

void ProjectsService::loadRecentProjects() {
	QSettings settings;

	if (!settings.contains("projectsList")) {
		qDebug() << "Does not exist";
		return;
	}

	qDebug() << "Exists";

	QStringList projectPaths = settings.value("projectsList").toStringList();
	foreach (QString path, projectPaths) {
		qDebug() << path;
	}
}

void ProjectsService::saveRecentProjects() {}

void ProjectsService::clearRecentProjects() {
	QSettings settings;

	settings.remove("projectsList");
}

QList<ProjectDTO> ProjectsService::getRecentProjectsList() const {
	return recentProjectsList;
}
