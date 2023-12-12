#include "projectdto.h"

#include <QDir>
#include <QFile>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonParseError>
#include <QJsonValue>
#include <QMessageBox>

ProjectDTO::ProjectDTO(QString path, QObject *parent)
	: QObject{parent}, location(path) {
	this->projectName = "project name";
	this->resolution = QSize(480, 360);

	this->saveProject();
}

void ProjectDTO::saveProject() {
	QJsonDocument document;
	QJsonObject root;

	root.insert("projectName", this->projectName);
	QJsonObject resolution;
	resolution.insert("height", this->resolution.height());
	resolution.insert("width", this->resolution.width());
	root.insert("displayResolution", resolution);

	document.setObject(root);

	QFile projectFile(QDir(this->location).filePath("embedded-package.json"));
	if (projectFile.open(QIODevice::OpenModeFlag::WriteOnly)) {
		projectFile.write(document.toJson());
		projectFile.close();

		return;
	}

	QMessageBox::critical(
		nullptr, "Failed to save project",
		"Unable to save project\n" + projectFile.errorString());
}