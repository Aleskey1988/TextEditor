#pragma once

#include <QtWidgets>
#include "ui_TextEditor.h"
#include "FindDialog.h"
#include "ReplaceDialog.h"

class TextEditor : public QMainWindow
{
	Q_OBJECT

public:
	TextEditor(QWidget *parent = Q_NULLPTR);

private:
	void onOpen();
	void onSave();
	void onSaveAs();
	void onExit();
	void onUndo();
	void onRedo();
	void onCut();
	void onCopy();
	void onPaste();
	void onDelete();
	void onFind();
	void onReplace();
	void onSelectAll();
	void onDateTime();
	void onIncreaseFont();
	void onDecreaseFont();
	void onFont();
	void onAbout();

	void onTextFound(int index, int length);
	void onTextReplaced(QString what, QString two);

	Ui::TextEditorClass ui;
	FindDialog findDlg;
	ReplaceDialog replaceDlg;
};
