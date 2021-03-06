#ifndef SAVEGAME_H
#define SAVEGAME_H

#include <QDialog>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QListWidget>

#include <QDebug>

class SaveGame : public QDialog
{
    Q_OBJECT
public:
    SaveGame(QWidget *parent = 0);
    virtual ~SaveGame() {}
    void setGameList(QVector<QString> saveGameList);
    int getSelectedGame();

protected:
    QVBoxLayout* m_mainLayout_;
    QHBoxLayout* m_buttonsLayout_;
    QPushButton* m_okButton_;
    QPushButton* m_cancelButton_;
    QListWidget* m_listWidget_;
};

#endif // SAVEGAME_H
