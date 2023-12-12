#ifndef CREATEPROJECTDTO_H
#define CREATEPROJECTDTO_H

#include <QString>

class CreateProjectDTO {
   public:
	CreateProjectDTO(QString name, QString path, QString device, bool hasUI);

   public:
	const QString projectName;
	const QString projectPath;
	const QString device;
	const bool hasUI;
};

#endif	// CREATEPROJECTDTO_H
