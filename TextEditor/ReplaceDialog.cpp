#include "ReplaceDialog.h"

ReplaceDialog::ReplaceDialog(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);

	connect(ui.buttonReplace, &QPushButton::clicked,
		this, &ReplaceDialog::onReplace);
	connect(ui.buttonCancel, &QPushButton::clicked,
		this, &ReplaceDialog::onCancel);
}
ReplaceDialog::~ReplaceDialog()
{
}

void ReplaceDialog::SetTextForFind(QString text)
{
	ui.editReplaceWhat->setText(text);
}

void ReplaceDialog::onReplace()
{
	emit textReplaced(ui.editReplaceWhat->text(), ui.editReplaceTo->text());
}
void ReplaceDialog::onCancel()
{
	hide();
}
