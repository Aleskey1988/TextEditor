#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_TextEditor.h"

class TextEditor : public QMainWindow
{
	Q_OBJECT

public:
	TextEditor(QWidget *parent = Q_NULLPTR);

private:
	Ui::TextEditorClass ui;
};
