#include "AddSoldierDialog.h"
#include "./ui_AddSoldierDialog.h"

AddSoldierDialog::AddSoldierDialog(QWidget *parent) :QDialog(parent), ui(new Ui::AddSoldierDialog) {
    ui->setupUi(this);
    connect(ui->buttonBox, SIGNAL(accepted()), this, SLOT(sendSoldierToMainWindow()));
}

AddSoldierDialog::~AddSoldierDialog() {
    delete ui;
}

void AddSoldierDialog::sendSoldierToMainWindow() {
    QString firstName = ui->firstNameInput->text();
    QString lastName = ui->lastNameInput->text();
    
    QComboBox *comboBox = ui->rankComboBox;
    int currentIndex = comboBox->currentIndex();
    const QVariant &variant = comboBox->itemData(currentIndex);
    Rank rank = variant.value<Rank>();
    Soldier soldier(firstName, lastName, rank);

    emit sendAddedSoldier(soldier);
}


void AddSoldierDialog::setAvailableRanks(const std::list<Rank> &ranks) {
    foreach (Rank rank, ranks) {
        ui->rankComboBox->addItem(rank.name, QVariant::fromValue<Rank>(rank));
    }
}
