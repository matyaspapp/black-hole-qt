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

    void newGame(int);
private:
    int m_tableSize_;
    QVector<QVector<int>> m_table_;

    void initTable(int);
};

#endif // BLACKHOLEMODEL_H
