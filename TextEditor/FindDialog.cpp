#include "FindDialog.h"

FindDialog::FindDialog(QWidget *parent)
    : QWidget(parent)
{
    ui.setupUi(this);
    setWindowFlags(Qt::Tool | Qt::WindowStaysOnTopHint | Qt::MSWindowsFixedSizeDialogHint);

    connect(ui.buttonFind, &QPushButton::clicked, this, &FindDialog::onFind);
    connect(ui.buttonCancel, &QPushButton::clicked, this, &FindDialog::onCancel);
}

void FindDialog::SetText(QString text)
{
    this->text = text;
}
void FindDialog::SetTextForFind(QString text)
{
    ui.editText->setText(text);
}

void FindDialog::onFind()
{
    bool useCase = ui.checkCaseSensitive->isChecked();
    int index = text.indexOf(ui.editText->text(), prevIndex, useCase ? Qt::CaseSensitive : Qt::CaseInsensitive);
    if (index != -1)
    {
        emit textFound(index, ui.editText->text().length());
        prevIndex = index + 1;
        if (prevIndex == text.length())
            prevIndex = 0;
    }
    else
    {
        prevIndex = 0;
    }
}
void FindDialog::onCancel()
{
    hide();
}
