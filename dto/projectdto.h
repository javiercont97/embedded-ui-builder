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
	explicit ProjectDTO(QObject *parent = nullptr);

   private:
	QString projectName;
	QDate lastModified;
	QString device;
	QSize resolution;
	QImage::Format screenFormat;
};

#endif	// PROJECTDTO_H
