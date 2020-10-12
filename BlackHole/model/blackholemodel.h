#ifndef BLACKHOLEMODEL_H
#define BLACKHOLEMODEL_H

#include <QWidget>
#include <QVector>
#include <QDebug>

#include "../data/blackholedataaccess.h"

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

    bool saveGame(int);
    QVector<QString> getSavedGameList() const;
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
    Ship* getActualShip(int, int);
    bool isGameOver();

    BlackHoleDataAccess m_dataAccess_;

signals:
    void gameOver(int);
};

#endif // BLACKHOLEMODEL_H
