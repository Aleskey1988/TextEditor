#include "ReplaceDialog.h"

ReplaceDialog::ReplaceDialog(QWidget *parent)
    : QWidget(parent)
{
    ui.setupUi(this);
    setWindowFlags(Qt::Tool | Qt::WindowStaysOnTopHint | Qt::MSWindowsFixedSizeDialogHint);

    connect(ui.buttonReplace, &QPushButton::clicked, this, &ReplaceDialog::onReplace);
    connect(ui.buttonCancel, &QPushButton::clicked, this, &ReplaceDialog::onCancel);
}

void ReplaceDialog::SetTextForFind(QString text)
{
    ui.editReplaceWhat->setText(text);
}

void ReplaceDialog::onReplace()
{
    bool useCase = ui.checkCaseSensitive->isChecked();
    emit textReplaced(ui.editReplaceWhat->text(), ui.editReplaceTo->text(), useCase);
}
void ReplaceDialog::onCancel()
{
    hide();
}
