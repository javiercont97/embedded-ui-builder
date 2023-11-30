#ifndef PROJECT_H
#define PROJECT_H

#include <QObject>
#include <QDate>
#include <QSize>

#include <QPixmap>
#include <QImage>

class Project : public QObject {
    Q_OBJECT
public:
    explicit Project(QObject *parent = nullptr);


private:
    QString projectName;
    QDate lastModified;
    QString device;
    QSize resolution;
    QImage::Format screenFormat;
};

#endif // PROJECT_H
