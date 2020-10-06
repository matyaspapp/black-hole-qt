#ifndef SAVEGAME_H
#define SAVEGAME_H

#include <QDialog>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QListWidget>

class SaveGame : public QDialog
{
    Q_OBJECT
public:
    SaveGame(QWidget *parent = 0);
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
