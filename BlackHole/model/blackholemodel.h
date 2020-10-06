#ifndef BLACKHOLEMODEL_H
#define BLACKHOLEMODEL_H

#include <QWidget>
#include <QVector>

class BlackHoleModel : public QWidget
{
    Q_OBJECT
public:
    struct Ship
    {
        int xCoord;
        int yCoord;
        bool isAlive;
        Ship(int x, int y)
            : xCoord(x), yCoord(y), isAlive(true)
        {
        }
    };

    BlackHoleModel(QWidget *parent = nullptr);
    ~BlackHoleModel();
    int getTableSize();
    int getTableValue(int, int);
    int getActualPlayerValue();

    void newGame(int);
    void makeTurn(int, int, int, int);
private:
    bool m_isFirstPlayerMove_;

    int m_tableSize_;
    QVector<QVector<int>> m_table_;

    QVector<Ship*> m_playerOneShips_;
    QVector<Ship*> m_playerTwoShips_;

    void initTable();
    int getAliveShipsNum();
    bool isValidField(int, int);
    bool isValidMove(int, int);
};

#endif // BLACKHOLEMODEL_H
