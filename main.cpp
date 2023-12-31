#include <QApplication>
#include <QFile>
#include <QLocale>
#include <QMessageBox>
#include <QStyle>
#include <QStyleFactory>
#include <QTranslator>

#include "editor/editor.h"

int main(int argc, char *argv[]) {
	QApplication a(argc, argv);
	QCoreApplication::setOrganizationName("guibuilder");
	QCoreApplication::setOrganizationDomain("no domain");
	QCoreApplication::setApplicationName("GUI Builder for Mbed");

	Editor w;

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
