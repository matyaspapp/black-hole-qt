#ifndef BLACKHOLEVIEW_H
#define BLACKHOLEVIEW_H

#include "../model/blackholemodel.h"
#include "../data/savegame.h"

#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QVector>
#include <QPushButton>
#include <QString>
#include <QLabel>
#include <QKeyEvent>
#include <QMessageBox>
#include <QMovie>

class BlackHoleView : public QWidget
{
    Q_OBJECT

public:
    BlackHoleView(QWidget *parent = nullptr);
    ~BlackHoleView();

protected:
    void keyPressEvent(QKeyEvent*);

private:
    BlackHoleModel m_blackHoleGameModel_;
    SaveGame* m_saveGame_;

    QPushButton* m_markedTableButton_;

    QVBoxLayout* m_mainLayout_;
    QHBoxLayout* m_actualPlayerLayout_;
    QLabel* m_actualPlayerLabel_;
    QPushButton* m_actualPlayerButton_;
    QGridLayout* m_tablePushButtonsLayout_;
    QVector<QVector<QPushButton*>> m_tablePushButtons_;
    QHBoxLayout* m_sizePushButtonsLayout_;
    QPushButton* m_sizePushButton5_;
    QPushButton* m_sizePushButton7_;
    QPushButton* m_sizePushButton9_;

    QMovie* m_blackHoleButtonMovie_;

    void newGame(int);
    void initTable();
    void refreshTable();
    void refreshActualPlayer();

    void markTableButton(QPushButton*);

private slots:
    void setBlackHoleButtonIcon(int);
    void sizeButtonClicked();
    void tableButtonClicked();
    void gameOver(int);
};
#endif // BLACKHOLEVIEW_H
