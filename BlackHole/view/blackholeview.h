#ifndef BLACKHOLEVIEW_H
#define BLACKHOLEVIEW_H

#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QVector>
#include <QPushButton>
#include <QString>

class BlackHoleView : public QWidget
{
    Q_OBJECT

public:
    BlackHoleView(QWidget *parent = nullptr);
    ~BlackHoleView();

private:
    QVBoxLayout* m_mainLayout_;
    QGridLayout* m_tablePushButtonsLayout_;
    QVector<QVector<QPushButton*>> m_tablePushButtons_;
    QHBoxLayout* m_sizePushButtonsLayout_;
    QPushButton* m_sizePushButton5_;
    QPushButton* m_sizePushButton7_;
    QPushButton* m_sizePushButton9_;

    void newGame();
    void initTable();
    void refreshTable();
};
#endif // BLACKHOLEVIEW_H
