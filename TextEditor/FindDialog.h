#pragma once

#include <QWidget>
#include "ui_FindDialog.h"

class FindDialog : public QWidget
{
	Q_OBJECT

public:
	FindDialog(QWidget *parent = Q_NULLPTR);
	~FindDialog();

	void SetText(QString text);
	void SetTextForFind(QString text);

signals:
	void textFound(int index, int length);

private:
	void onFind();
	void onCancel();

	Ui::FindDialog ui;
	QString text;
	int prevIndex = 0;
};
