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
        bool l_isTopHalf = l_diagonalIdx <= m_tableSize_ / 2;
        int l_player = l_isTopHalf ? 1 : 2;
        m_table_[l_diagonalIdx][l_diagonalIdx] = l_player;
        m_table_[l_diagonalIdx][m_tableSize_ - 1 - l_diagonalIdx] = l_player;
    }
    m_table_[m_tableSize_ / 2][m_tableSize_ / 2] = 42;
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
    m_tableSize_ = f_tableSize;
    initTable();
}
