#include "projectservice.h"

ProjectService::ProjectService(QObject *parent) : QObject{parent} {
	loadRecentProjects();
}

ProjectDTO *ProjectService::createNewProject(CreateProjectDTO project) {
	this->currentProject = new ProjectDTO(project.projectPath, this);
	recentProjectsList.append(this->currentProject);
	this->saveRecentProjects();
	return currentProject;
}

ProjectDTO *ProjectService::openProject(QString path) {
	this->currentProject = new ProjectDTO(path, this);
	recentProjectsList.append(this->currentProject);
	this->saveRecentProjects();
	return currentProject;
}

void ProjectService::loadRecentProjects() {
	QSettings settings;
	this->recentProjectsList.clear();
	if (!settings.contains("projectsList")) return;
	QStringList projectPaths = settings.value("projectsList").toStringList();
	foreach (QString path, projectPaths) {
		this->recentProjectsList.append(new ProjectDTO(path, this));
	}
}

void ProjectService::saveRecentProjects() {
	QSettings settings;
	QStringList paths;
	foreach (ProjectDTO *project, this->recentProjectsList) {
		if(!paths.contains(project->location))paths.append(project->location);
		if(paths.size() >= 10) break;
	}
	settings.setValue("projectsList", QVariant(paths));
}

void ProjectService::clearRecentProjects() {
	QSettings settings;
	settings.remove("projectsList");
}

QList<ProjectDTO *> ProjectService::getRecentProjectsList() const {
	return recentProjectsList;
}
