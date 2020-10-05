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
        for (int j = 0; j < f_tableSize; ++j)
        {
            m_table_[i][j] = 0;
        }
    }
    int l_diagonalRow = 0;
    int l_diagonalCol = 0;
    for (int i = 0; i < f_tableSize; ++i)
    {
        bool l_isTopHalf = l_diagonalRow <= f_tableSize / 2;
        int l_player = l_isTopHalf ? 1 : 2;
        m_table_[l_diagonalRow][l_diagonalCol] = l_player;
        m_table_[l_diagonalRow][l_diagonalCol + f_tableSize - 1 - l_diagonalRow] = l_player;
    }
    m_table_[f_tableSize / 2][f_tableSize / 2] = 42;
}
