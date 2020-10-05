#ifndef BLACKHOLEMODEL_H
#define BLACKHOLEMODEL_H

#include <QWidget>
#include <QVector>

class BlackHoleModel : public QWidget
{
    Q_OBJECT
public:
    BlackHoleModel(QWidget *parent = nullptr);
    ~BlackHoleModel();
    int getTableSize();
    int getTableValue(int, int);
    int getActualPlayer();

    void newGame(int);
private:
    bool m_isFirstPlayerMove_;

    int m_tableSize_;
    QVector<QVector<int>> m_table_;

    void initTable();
};

#endif // BLACKHOLEMODEL_H
