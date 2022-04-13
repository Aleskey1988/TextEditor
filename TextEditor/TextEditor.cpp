#include "TextEditor.h"

TextEditor::TextEditor(QWidget* parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	connect(ui.actionOpen, &QAction::triggered, this, &TextEditor::onOpen);
	connect(ui.actionSave_as, &QAction::triggered, this, &TextEditor::onSaveAs);
	connect(ui.actionExit, &QAction::triggered, this, &TextEditor::onExit);

	connect(ui.actionUndo, &QAction::triggered, this, &TextEditor::onUndo);
	connect(ui.actionRedo, &QAction::triggered, this, &TextEditor::onRedo);
	connect(ui.actionCut, &QAction::triggered, this, &TextEditor::onCut);
	connect(ui.actionCopy, &QAction::triggered, this, &TextEditor::onCopy);
	connect(ui.actionPaste, &QAction::triggered, this, &TextEditor::onPaste);
	connect(ui.actionDelete, &QAction::triggered, this, &TextEditor::onDelete);

	connect(ui.actionSearch, &QAction::triggered, this, &TextEditor::onFind);
	connect(&findDlg, &FindDialog::textFound,
		this, &TextEditor::onTextFound);

	connect(ui.actionReplace, &QAction::triggered,
		this, &TextEditor::onReplace);
	connect(&replaceDlg, &ReplaceDialog::textReplaced,
		this, &TextEditor::onTextReplaced);

	connect(ui.actionSelect_all, &QAction::triggered, this, &TextEditor::onSelectAll);
	connect(ui.actionDate_and_time, &QAction::triggered, this, &TextEditor::onDateTime);
	
	connect(ui.actionFont, &QAction::triggered, this, &TextEditor::onFont);
}

void TextEditor::onOpen()
{
	QString fileName = QFileDialog::getOpenFileName(this,
		"Open text file", "", "Text files (*.txt)");
	QFile file(fileName);
	file.open(QIODevice::ReadOnly);
	QByteArray ba = file.readAll();
	QString str = QString(ba);
	ui.plainTextEdit->setPlainText(str);
}
void TextEditor::onSave()
{
}
void TextEditor::onSaveAs()
{
	QString fileName = QFileDialog::getSaveFileName(this,
		"Save text file", "", "Text files (*.txt)");
	QFile file(fileName);
	file.open(QIODevice::WriteOnly);
	QTextStream ts(&file);
	ts.setCodec("UTF-8");
	ts << ui.plainTextEdit->toPlainText();
	file.close();
}
void TextEditor::onExit()
{
	close();
}
void TextEditor::onUndo()
{
	ui.plainTextEdit->undo();
}
void TextEditor::onRedo()
{
	ui.plainTextEdit->redo();
}
void TextEditor::onCut()
{
	ui.plainTextEdit->cut();
}
void TextEditor::onCopy()
{
	ui.plainTextEdit->copy();
}
void TextEditor::onPaste()
{
	ui.plainTextEdit->paste();
}
void TextEditor::onDelete()
{

}
void TextEditor::onFind()
{
	findDlg.SetText(ui.plainTextEdit->toPlainText());
	findDlg.show();
}
void TextEditor::onReplace()
{
	replaceDlg.show();
}
void TextEditor::onSelectAll()
{
	ui.plainTextEdit->selectAll();
}
void TextEditor::onDateTime()
{
	QDateTime dateTime;
	QString str = dateTime.currentDateTime().toString("dd.MM.yyyy hh:mm:ss:zzz");
	QTextCursor cursor = ui.plainTextEdit->textCursor();
	int pos = cursor.position();
	QString text = ui.plainTextEdit->toPlainText();
	text.insert(pos, str);
	ui.plainTextEdit->setPlainText(text);
}
void TextEditor::onIncreaseFont() {}
void TextEditor::onDecreaseFont() {}
void TextEditor::onFont()
{
	bool ok;
	QFont font = QFontDialog::getFont(
		&ok, QFont("MS Shell Dlg 2 [Serif]", 8), this);
	ui.plainTextEdit->setFont(font);
}
void TextEditor::onAbout() {}

void TextEditor::onTextFound(int index, int length)
{
	QTextCursor c = ui.plainTextEdit->textCursor();
	c.setPosition(index);
	c.setPosition(index + length, QTextCursor::KeepAnchor);
	ui.plainTextEdit->setTextCursor(c);
}
void TextEditor::onTextReplaced(QString what, QString two)
{
	QString text = ui.plainTextEdit->toPlainText();
	text.replace(what, two);
	ui.plainTextEdit->setPlainText(text);
}
