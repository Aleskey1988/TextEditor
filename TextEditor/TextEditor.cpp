#include "TextEditor.h"

TextEditor::TextEditor(QWidget* parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);

    connect(ui.actionOpen, &QAction::triggered, this, &TextEditor::onOpen);
    connect(ui.actionSave_as, &QAction::triggered, this, &TextEditor::onSaveAs);
    connect(ui.actionExit, &QAction::triggered, this, &TextEditor::onExit);
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
void TextEditor::onUndo() {}
void TextEditor::onRedo() {}
void TextEditor::onCut() {}
void TextEditor::onCopy() {}
void TextEditor::onPaste() {}
void TextEditor::onDelete() {}
void TextEditor::onFind() {}
void TextEditor::onReplace() {}
void TextEditor::onSelectAll() {}
void TextEditor::onDateTime() {}
void TextEditor::onIncreaseFont() {}
void TextEditor::onDecreaseFont() {}
void TextEditor::onFont() {}
void TextEditor::onAbout() {}