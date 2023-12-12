#ifndef BROWSECOMPONENT_H
#define BROWSECOMPONENT_H

#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui {
class BrowseComponent;
}
QT_END_NAMESPACE

enum class BrowseMode { FILE, DIRECTORY };

class BrowseComponent : public QWidget {
	Q_OBJECT

   public:
	explicit BrowseComponent(QWidget *parent = nullptr);
	~BrowseComponent();

	void setMode(BrowseMode mode);
	BrowseMode getMode();
	void setPlaceholderText(QString text);
	void clearFields();
	QString getPath();
	void showError();
	void clearError();

   private:
	void setupEventConnections();

   signals:
	pathChanged(QString path);

   private slots:
	void onBrowseClicked();
	void onPathChanged(QString path);

   private:
	Ui::BrowseComponent *ui;
	BrowseMode mode;
};

#endif	// BROWSECOMPONENT_H
