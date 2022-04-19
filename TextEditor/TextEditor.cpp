#include "TextEditor.h"

TextEditor::TextEditor(QWidget* parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);

    connect(ui.actionOpen, &QAction::triggered, this, &TextEditor::onOpen);
    connect(ui.actionSave, &QAction::triggered, this, &TextEditor::onSave);
    connect(ui.actionSaveAs, &QAction::triggered, this, &TextEditor::onSaveAs);
    connect(ui.actionExit, &QAction::triggered, this, &TextEditor::onExit);

    connect(ui.actionUndo, &QAction::triggered, this, &TextEditor::onUndo);
    connect(ui.actionRedo, &QAction::triggered, this, &TextEditor::onRedo);
    connect(ui.actionCut, &QAction::triggered, this, &TextEditor::onCut);
    connect(ui.actionCopy, &QAction::triggered, this, &TextEditor::onCopy);
    connect(ui.actionPaste, &QAction::triggered, this, &TextEditor::onPaste);

    connect(ui.actionSearch, &QAction::triggered, this, &TextEditor::onFind);
    connect(&findDlg, &FindDialog::textFound, this, &TextEditor::onTextFound);

    connect(ui.actionReplace, &QAction::triggered, this, &TextEditor::onReplace);
    connect(&replaceDlg, &ReplaceDialog::textReplaced, this, &TextEditor::onTextReplaced);

    connect(ui.actionSelectAll, &QAction::triggered, this, &TextEditor::onSelectAll);
    connect(ui.actionDateTime, &QAction::triggered, this, &TextEditor::onDateTime);

    connect(ui.actionIncreaseFontSize, &QAction::triggered, this, &TextEditor::onIncreaseFont);
    connect(ui.actionDecreaseFontSize, &QAction::triggered, this, &TextEditor::onDecreaseFont);
    connect(ui.actionFont, &QAction::triggered, this, &TextEditor::onFont);

    connect(ui.actionAbout, &QAction::triggered, this, &TextEditor::onAbout);

    loadSettings();
}
TextEditor::~TextEditor()
{
    saveSettings();
}

void TextEditor::onOpen()
{
    fileName = QFileDialog::getOpenFileName(this, "Open text file", "", "Text files (*.txt)");
    QFile file(fileName);
    file.open(QIODevice::ReadOnly);
    QByteArray ba = file.readAll();
    QString str = QString(ba);
    ui.plainTextEdit->setPlainText(str);
}
void TextEditor::onSave()
{
    if (fileName.isEmpty())
        onSaveAs();
    else
        saveToFile();
}
void TextEditor::onSaveAs()
{
    fileName = QFileDialog::getSaveFileName(this, "Save text file", "", "Text files (*.txt)");
    saveToFile();
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
void TextEditor::onIncreaseFont()
{
    QFont font = ui.plainTextEdit->font();
    double fontSize = font.pointSizeF();
    fontSize *= 1.1;
    font.setPointSizeF(fontSize);
    ui.plainTextEdit->setFont(font);
}
void TextEditor::onDecreaseFont()
{
    QFont font = ui.plainTextEdit->font();
    double fontSize = font.pointSizeF();
    fontSize /= 1.1;
    font.setPointSizeF(fontSize);
    ui.plainTextEdit->setFont(font);
}
void TextEditor::onFont()
{
    bool ok;
    QFont editorFont = ui.plainTextEdit->font();
    QFont font = QFontDialog::getFont(&ok, editorFont, this);
    ui.plainTextEdit->setFont(font);
}
void TextEditor::onAbout()
{
    QMessageBox::information(nullptr, "Text editor", "The best text editor you've ever seen!!1");
}

void TextEditor::onTextFound(int index, int length)
{
    QTextCursor c = ui.plainTextEdit->textCursor();
    c.setPosition(index);
    c.setPosition(index + length, QTextCursor::KeepAnchor);
    ui.plainTextEdit->setTextCursor(c);
}
void TextEditor::onTextReplaced(QString what, QString two, bool useCase)
{
    QString text = ui.plainTextEdit->toPlainText();
    text.replace(what, two, useCase ? Qt::CaseSensitive : Qt::CaseInsensitive);
    ui.plainTextEdit->setPlainText(text);
}

void TextEditor::saveSettings()
{
    QByteArray mainWindowGeometry = saveGeometry();
    QByteArray findDialogGeometry = findDlg.saveGeometry();
    QByteArray replaceDialogGeometry = replaceDlg.saveGeometry();
    QString fontFamily = ui.plainTextEdit->font().family();
    double fontSize = ui.plainTextEdit->font().pointSizeF();

    QSettings settings("settings.ini", QSettings::Format::IniFormat);
    settings.beginGroup("Main");
    settings.setValue("mainWindowGeometry", mainWindowGeometry);
    settings.setValue("findDialogGeometry", findDialogGeometry);
    settings.setValue("replaceDialogGeometry", replaceDialogGeometry);
    settings.setValue("fontFamily", fontFamily);
    settings.setValue("fontSize", fontSize);
}
void TextEditor::loadSettings()
{
    QSettings settings("settings.ini", QSettings::Format::IniFormat);
    settings.beginGroup("Main");

    QByteArray mainWindowGeometry = settings.value("mainWindowGeometry").toByteArray();
    QByteArray findDialogGeometry = settings.value("findDialogGeometry").toByteArray();
    QByteArray replaceDialogGeometry = settings.value("replaceDialogGeometry").toByteArray();
    QString fontFamily = settings.value("fontFamily", "Times").toString();
    double fontSize = settings.value("fontSize", 8).toDouble();

    restoreGeometry(mainWindowGeometry);
    findDlg.restoreGeometry(findDialogGeometry);
    replaceDlg.restoreGeometry(replaceDialogGeometry);
    QFont font(fontFamily, fontSize);
    ui.plainTextEdit->setFont(font);
}
void TextEditor::saveToFile()
{
    if (!fileName.isEmpty())
    {
        QFile file(fileName);
        file.open(QIODevice::WriteOnly);
        QTextStream ts(&file);
        ts.setCodec("UTF-8");
        ts << ui.plainTextEdit->toPlainText();
        file.close();
    }
}
