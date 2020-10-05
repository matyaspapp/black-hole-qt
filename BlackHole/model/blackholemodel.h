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
private:
    int m_tableSize_;
    QVector<QVector<int>> m_table_;

    void initTable(int);
};

#endif // BLACKHOLEMODEL_H