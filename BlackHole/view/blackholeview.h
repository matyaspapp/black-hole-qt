#ifndef BLACKHOLEVIEW_H
#define BLACKHOLEVIEW_H

#include "../model/blackholemodel.h"

#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QVector>
#include <QPushButton>
#include <QString>
#include <QLabel>
#include <QKeyEvent>

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

    void newGame(int);
    void initTable();
    void refreshTable();
    void refreshActualPlayer();

    void markTableButton(QPushButton*);

private slots:
    void sizeButtonClicked();
    void tableButtonClicked();
};
#endif // BLACKHOLEVIEW_H
