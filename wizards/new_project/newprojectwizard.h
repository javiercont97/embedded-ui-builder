#ifndef NEWPROJECTWIZARD_H
#define NEWPROJECTWIZARD_H

#include <QDialog>
#include "../../dto/createprojectdto.h"

namespace Ui {
class NewProjectWizard;
}

class NewProjectWizard : public QDialog {
	Q_OBJECT

   public:
	explicit NewProjectWizard(QWidget *parent = nullptr);
	~NewProjectWizard();

   private:
	void setupEventConnections();
	void setupValidators();
	void clearFields();

   signals:
   void projectCreated(CreateProjectDTO &project);

   private slots:
	void onUICheckboxChanged(int state);
	void onProjectNameChanged(QString text);
	void onCancelClicked();
	void onCreateClicked();

   private:
	Ui::NewProjectWizard *ui;
};

#endif	// NEWPROJECTWIZARD_H
