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
    RankDescription rank = variant.value<RankDescription>();
    Soldier soldier(firstName, lastName, rank);

    clearFields();
    emit sendAddedSoldier(soldier);
}


void AddSoldierDialog::setAvailableRanks(const std::list<RankDescription> &ranks) {
    foreach (RankDescription rank, ranks) {
        ui->rankComboBox->addItem(rank.name, QVariant::fromValue<RankDescription>(rank));
    }
}

void AddSoldierDialog::clearFields() {
    ui->firstNameInput->clear();
    ui->lastNameInput->clear();
}
