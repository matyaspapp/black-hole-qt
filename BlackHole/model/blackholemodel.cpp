#include "blackholemodel.h"

BlackHoleModel::BlackHoleModel(QWidget *parent)
    : QWidget(parent)
{
    m_isFirstPlayerMove_ = true;
    m_tableSize_ = 5;
    newGame(m_tableSize_);
}

BlackHoleModel::~BlackHoleModel()
{
}

int BlackHoleModel::getTableSize()
{
    return m_tableSize_;
}

int BlackHoleModel::getTableValue(int f_xCoord, int f_yCoord)
{
    return m_table_[f_xCoord][f_yCoord];
}

int BlackHoleModel::getActualPlayerValue()
{
    return m_isFirstPlayerMove_ ? 1 : 2;
}

void BlackHoleModel::newGame(int f_tableSize)
{
    m_isFirstPlayerMove_ = true;
    m_tableSize_ = f_tableSize;
    m_playerOneShips_.resize(0);
    m_playerOneShips_.clear();
    m_playerTwoShips_.resize(0);
    m_playerTwoShips_.clear();
    initTable();
}

void BlackHoleModel::makeTurn(int f_xCoord, int f_yCoord, int f_dx, int f_dy)
{
    Ship* l_ship = getActualShip(f_xCoord, f_yCoord);
    if (nullptr == l_ship)
    {
        return;
    }

    int l_xMoveCoord = f_xCoord;
    int l_yMoveCoord = f_yCoord;
    while(true == isValidMove(l_xMoveCoord+f_dx, l_yMoveCoord+f_dy))
    {
        l_xMoveCoord += f_dx;
        l_yMoveCoord += f_dy;
    }

    m_table_[f_xCoord][f_yCoord] = 0;
    bool l_isNextToBlackHole = isValidField(l_xMoveCoord+f_dx, l_yMoveCoord+f_dy)
                               && 42 == m_table_[l_xMoveCoord+f_dx][l_yMoveCoord+f_dy];
    if (true == l_isNextToBlackHole)
    {
        l_ship->isAlive = false;
    }
    else
    {
        l_ship->xCoord = l_xMoveCoord;
        l_ship->yCoord = l_yMoveCoord;
        m_table_[l_xMoveCoord][l_yMoveCoord] = m_isFirstPlayerMove_
                                             ? 1
                                             : 2;
    }

    if (true == isGameOver())
    {
        int l_player = m_isFirstPlayerMove_
                     ? 1
                     : 2;
        Q_EMIT gameOver(l_player);
    }
    else
    {
        m_isFirstPlayerMove_ = !m_isFirstPlayerMove_;
    }
}

bool BlackHoleModel::loadGame(int f_gameIndex)
{
    QVector<int> l_savedGameData;
    if (!m_dataAccess_.loadGame(f_gameIndex, l_savedGameData))
    {
        return false;
    }

    m_isFirstPlayerMove_ = l_savedGameData[0];
    m_tableSize_ = l_savedGameData[1];
    m_playerOneShips_.resize(0);
    m_playerTwoShips_.resize(0);

    int l_savedDataIndex = 2;
    m_table_.resize(m_tableSize_);
    for (int i = 0; i < m_tableSize_; ++i)
    {
        m_table_[i].resize(m_tableSize_);
        for (int j = 0; j < m_tableSize_; ++j)
        {
            m_table_[i][j] = l_savedGameData[l_savedDataIndex];
            if (1 == m_table_[i][j])
            {
                m_playerOneShips_.push_back(new Ship(i, j));
            }
            else if (2 == m_table_[i][j])
            {
                m_playerTwoShips_.push_back(new Ship(i, j));
            }
            ++l_savedDataIndex;
        }
    }

    return true;
}

bool BlackHoleModel::saveGame(int f_gameIndex)
{
    QVector<int> l_actualGameData;
    l_actualGameData.push_back(m_isFirstPlayerMove_);
    l_actualGameData.push_back(m_tableSize_);
    for (int i = 0; i < m_tableSize_; ++i)
    {
        for (int j = 0; j < m_tableSize_; ++j)
        {
            l_actualGameData.push_back(m_table_[i][j]);
        }
    }

    return m_dataAccess_.saveGame(f_gameIndex, l_actualGameData);
}

QVector<QString> BlackHoleModel::getSavedGameList() const
{
    return m_dataAccess_.getSavedGameList();
}

// private
void BlackHoleModel::initTable()
{
    m_table_.resize(m_tableSize_);
    for (int i = 0; i < m_tableSize_; ++i)
    {
        m_table_[i].resize(m_tableSize_);
        for (int j = 0; j < m_tableSize_; ++j)
        {
            m_table_[i][j] = 0;
        }
    }
    for (int l_diagonalIdx = 0; l_diagonalIdx < m_tableSize_; ++l_diagonalIdx)
    {
        if (l_diagonalIdx == m_tableSize_ / 2)
        {
            continue;
        }
        bool l_isTopHalf = l_diagonalIdx <= m_tableSize_ / 2;
        int l_player = l_isTopHalf ? 1 : 2;
        m_table_[l_diagonalIdx][l_diagonalIdx] = l_player;
        m_table_[l_diagonalIdx][m_tableSize_ - 1 - l_diagonalIdx] = l_player;
        if (1 == l_player)
        {
            m_playerOneShips_.push_back(new Ship(l_diagonalIdx, l_diagonalIdx));
            m_playerOneShips_.push_back(new Ship(l_diagonalIdx, m_tableSize_-1-l_diagonalIdx));
        }
        else if (2 == l_player)
        {
            m_playerTwoShips_.push_back(new Ship(l_diagonalIdx, l_diagonalIdx));
            m_playerTwoShips_.push_back(new Ship(l_diagonalIdx, m_tableSize_-1-l_diagonalIdx));
        }
    }
    m_table_[m_tableSize_ / 2][m_tableSize_ / 2] = 42;
}

int BlackHoleModel::getAliveShipsNum()
{
    int l_shipCounter = 0;
    if (true == m_isFirstPlayerMove_)
    {
        for (Ship* l_ship : m_playerOneShips_)
        {
            if (true == l_ship->isAlive)
            {
                ++l_shipCounter;
            }
        }
    }
    else
    {
        for (Ship* l_ship : m_playerTwoShips_)
        {
            if (true == l_ship->isAlive)
            {
                ++l_shipCounter;
            }
        }
    }

    return l_shipCounter;
}

bool BlackHoleModel::isValidField(int f_xCoord, int f_yCoord)
{
    return 0 <= f_xCoord && f_xCoord < m_tableSize_
        && 0 <= f_yCoord && f_yCoord < m_tableSize_;
}

bool BlackHoleModel::isValidMove(int f_xNeighbour, int f_yNeighbour)
{
    return isValidField(f_xNeighbour, f_yNeighbour)
        && m_table_[f_xNeighbour][f_yNeighbour] == 0;
}

BlackHoleModel::Ship* BlackHoleModel::getActualShip(int f_xCoord, int f_yCoord)
{
    Ship* l_ship = nullptr;
    if (true == m_isFirstPlayerMove_)
    {
        for (Ship* l_actualShip : m_playerOneShips_)
        {
            if (l_actualShip->xCoord == f_xCoord && l_actualShip->yCoord == f_yCoord)
            {
                l_ship = l_actualShip;
            }
        }
    }
    else
    {
        for (Ship* l_actualShip : m_playerTwoShips_)
        {
            if (l_actualShip->xCoord == f_xCoord && l_actualShip->yCoord == f_yCoord)
            {
                l_ship = l_actualShip;
            }
        }
    }

    return l_ship;
}

bool BlackHoleModel::isGameOver()
{
    int l_playerShipsNum = getAliveShipsNum();
    return l_playerShipsNum == m_tableSize_ / 2;
}
