#include "TextEditor.h"

TextEditor::TextEditor(QWidget* parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	connect(ui.actionOpen, &QAction::triggered, this, &TextEditor::onOpen);
	connect(ui.actionSave_as, &QAction::triggered, this, &TextEditor::onSaveAs);
	connect(ui.actionExit, &QAction::triggered, this, &TextEditor::onExit);

	connect(ui.actionSearch, &QAction::triggered, this, &TextEditor::onFind);
	connect(&findDlg, &FindDialog::textFound,
		this, &TextEditor::onTextFound);
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
void TextEditor::onReplace() {}
void TextEditor::onSelectAll() {}
void TextEditor::onDateTime() {}
void TextEditor::onIncreaseFont() {}
void TextEditor::onDecreaseFont() {}
void TextEditor::onFont() {}
void TextEditor::onAbout() {}

void TextEditor::onTextFound(int index, int length)
{
	QTextCursor c = ui.plainTextEdit->textCursor();
	c.setPosition(index);
	c.setPosition(index + length, QTextCursor::KeepAnchor);
	ui.plainTextEdit->setTextCursor(c);
}
