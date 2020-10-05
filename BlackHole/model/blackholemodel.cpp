#include "blackholemodel.h"

BlackHoleModel::BlackHoleModel(QWidget *parent)
    : QWidget(parent)
{
    m_tableSize_ = 5;
    initTable(m_tableSize_);
}

BlackHoleModel::~BlackHoleModel()
{
}

void BlackHoleModel::initTable(int f_tableSize)
{
    m_table_.resize(f_tableSize);
    for (int i = 0; i < f_tableSize; ++i)
    {
        m_table_[i].resize(f_tableSize);
        for (int j = 0; j < f_tableSize; ++j)
        {
            m_table_[i][j] = 0;
        }
    }
    for (int l_diagonalIdx = 0; l_diagonalIdx < f_tableSize; ++l_diagonalIdx)
    {
        bool l_isTopHalf = l_diagonalIdx <= f_tableSize / 2;
        int l_player = l_isTopHalf ? 1 : 2;
        m_table_[l_diagonalIdx][l_diagonalIdx] = l_player;
        m_table_[l_diagonalIdx][f_tableSize - 1 - l_diagonalIdx] = l_player;
    }
    m_table_[f_tableSize / 2][f_tableSize / 2] = 42;
}

int BlackHoleModel::getTableSize()
{
    return m_tableSize_;
}

int BlackHoleModel::getTableValue(int f_xCoord, int f_yCoord)
{
    return m_table_[f_xCoord][f_yCoord];
}

void BlackHoleModel::newGame(int f_tableSize)
{
    m_tableSize_ = f_tableSize;
    initTable(f_tableSize);
}
