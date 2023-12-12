#ifndef PROJECTDTO_H
#define PROJECTDTO_H

#include <QDate>
#include <QImage>
#include <QObject>
#include <QPixmap>
#include <QSize>

class ProjectDTO : public QObject {
	Q_OBJECT
   public:
	explicit ProjectDTO(QString path, QObject *parent = nullptr);

private:
	void saveProject();

   public:
	QString location;
	QString projectName;
	QDate lastModified;
	QString device;
	QSize resolution;
	QImage::Format screenFormat;
};

#endif	// PROJECTDTO_H
