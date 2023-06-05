#include "profileeditor.h"
#include "ui_profileeditor.h"

ProfileEditor::ProfileEditor(user::Account* user, db::Database* db,
                             QWidget* parent) :
    QWidget(parent),
    ui(new Ui::ProfileEditor), user(user),
    pio(new profile::ProfileIO((db::ProfileDB*)db)) {
    ui->setupUi(this);

    // pull current profile
    pio->pull_profile_id(p, user->get_id());

    // populate fields with current info
    ui->dispnameField->setText(QString::fromStdString(p.get_display_name()));
    ui->username->setText(
        QString::fromStdString("@" + p.get_account()->get_username()));
    ui->bioField->setText(QString::fromStdString(p.get_bio()));
    ui->comboBox->setCurrentIndex(p.get_theme());

    // show current links
    std::vector<std::string> llabels = p.get_link_labels();
    std::vector<std::string> laddresses = p.get_link_addresses();
    for (int l = 0; l < (int)llabels.size(); l++) {
        ProfileEditorLink* pel =
            new ProfileEditorLink(llabels[l], laddresses[l]);
        ui->linkList->addWidget(pel);
        connect(pel, &ProfileEditorLink::remove_link, this,
                &ProfileEditor::remove_link);
    }

    // show current pals
    for (profile::Pal* pal : p.get_pals()) {
        ProfileEditorPal* pep = new ProfileEditorPal(pal);
        ui->palList->addWidget(pep);
        connect(pep, &ProfileEditorPal::remove_pal, this,
                &ProfileEditor::remove_pal);
    }

    // show current pfp
    ui->pfpSelect->setCurrentIndex(p.get_avatar_id());
    QImage image("../../images/" + QString::number(p.get_avatar_id()) + ".png");
    ui->pfp->setPixmap(QPixmap::fromImage(image));
}

ProfileEditor::~ProfileEditor() {
    QLayoutItem* child;
    while ((child = ui->linkList->takeAt(0)) != 0) delete child;
    while ((child = ui->palList->takeAt(0)) != 0) delete child;
    delete ui;
    delete pio;
}

void ProfileEditor::on_saveButton_clicked() {
    // save profile header changes
    pio->edit_bio(p, ui->bioField->toPlainText().toStdString());
    pio->edit_display_name(p, ui->dispnameField->text().toStdString());
    pio->edit_theme(p, ui->comboBox->currentIndex());
    pio->edit_avatar_image(p, ui->pfpSelect->currentIndex());
    emit update_profile();
    emit exit();
}

void ProfileEditor::on_linkAddButton_clicked() {
    // add link to database
    pio->add_link(p, ui->labelField->text().toStdString(),
                  ui->urlField->text().toStdString());

    // add link to ui
    ProfileEditorLink* pel =
        new ProfileEditorLink(ui->labelField->text().toStdString(),
                              ui->urlField->text().toStdString());
    ui->linkList->addWidget(pel);
    connect(pel, &ProfileEditorLink::remove_link, this,
            &ProfileEditor::remove_link);
    ui->labelField->clear();
    ui->urlField->clear();
}

void ProfileEditor::on_palAddButton_clicked() {
    // add pal to database
    pio->create_pal(p, ui->palImage->currentIndex(),
                    ui->palNameField->text().toStdString(),
                    ui->speciesField->text().toStdString(),
                    ui->palBdayField->text().toStdString(),
                    ui->palBioField->toPlainText().toStdString());

    // add pal to ui
    ProfileEditorPal* pep = new ProfileEditorPal(p.get_pals().back());
    ui->palList->addWidget(pep);
    connect(pep, &ProfileEditorPal::remove_pal, this,
            &ProfileEditor::remove_pal);
    ui->palNameField->clear();
    ui->speciesField->clear();
    ui->palBdayField->clear();
    ui->palBioField->clear();
}

void ProfileEditor::remove_link(QWidget* w, std::string la, std::string li) {
    pio->remove_link(p, la, li);
    ui->linkList->removeWidget(w);
    delete w;
}

void ProfileEditor::remove_pal(QWidget* w, profile::Pal* pal) {
    pio->remove_pal(p, pal);
    ui->linkList->removeWidget(w);
    delete w;
}

void ProfileEditor::on_pfpSelect_currentIndexChanged(int index) {
    Q_UNUSED(index);
    QImage image("../../images/"
                 + QString::number(ui->pfpSelect->currentIndex()) + ".png");
    ui->pfp->setPixmap(QPixmap::fromImage(image));
}
