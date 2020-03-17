#include "AddSoldierDialog.h"
#include "./ui_AddSoldierDialog.h"

AddSoldierDialog::AddSoldierDialog(QWidget *parent) :QDialog(parent), ui(new Ui::AddSoldierDialog) {
    ui->setupUi(this);
    connect(ui->buttonBox, SIGNAL(accepted()), this, SLOT(passSoldierToParentWidget()));
}

AddSoldierDialog::~AddSoldierDialog() {
    delete ui;
}

void AddSoldierDialog::passSoldierToParentWidget() {
    QString firstName = ui->firstNameInput->text();
    QString lastName = ui->lastNameInput->text();

    Soldier soldier(firstName, lastName);

    emit sendAddedSoldier(soldier);
}

