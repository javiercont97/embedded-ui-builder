#include "createprojectdto.h"

CreateProjectDTO::CreateProjectDTO(QString name, QString path, QString device,
								   bool hasUI)
	: projectName(name), projectPath(path), device(device), hasUI(hasUI) {}
