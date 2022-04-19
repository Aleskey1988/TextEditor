#pragma once

#include <QWidget>
#include "ui_ReplaceDialog.h"

class ReplaceDialog : public QWidget
{
	Q_OBJECT

public:
	ReplaceDialog(QWidget *parent = Q_NULLPTR);

	void SetTextForFind(QString text);

signals:
	void textReplaced(QString what, QString two, bool useCase);

private:
	void onReplace();
	void onCancel();

	Ui::ReplaceDialog ui;
};
