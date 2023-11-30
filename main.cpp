#include "projectselector.h"

#include <QApplication>
#include <QLocale>
#include <QTranslator>

#include <QStyle>
#include <QStyleFactory>
#include <QFile>

#include <QMessageBox>

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    ProjectSelector w;

    QCoreApplication::setOrganizationName("guibuilder");
    QCoreApplication::setOrganizationDomain("no domain");
    QCoreApplication::setApplicationName("GUI Builder for Mbed");

    a.setStyle("Fusion");

    QFile theme(":/themes/dark-theme.css");
    if (theme.open(QFile::OpenModeFlag::ReadOnly)) {
        QString stylesheet = theme.readAll();
//        qDebug() << stylesheet;
        a.setStyleSheet(stylesheet);
        theme.close();
    } else {
        QMessageBox::critical(&w, "Error", "Error loading theme");
        a.exit(1);
        return 1;
    }

    QTranslator translator;
    const QStringList uiLanguages = QLocale::system().uiLanguages();
    for (const QString &locale : uiLanguages) {
        const QString baseName = "GUIBuilder_" + QLocale(locale).name();
        if (translator.load(":/i18n/" + baseName)) {
            a.installTranslator(&translator);
            break;
        }
    }
    w.show();
    return a.exec();
}
