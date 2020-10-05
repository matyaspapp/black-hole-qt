#include "blackholeview.h"

BlackHoleView::BlackHoleView(QWidget *parent)
    : QWidget(parent)
{
    setWindowTitle("Black Hole");
    setFixedSize(sizeHint());

    m_tablePushButtonsLayout_ = new QGridLayout();
    m_tablePushButtonsLayout_->setContentsMargins(0, 0, 0, 0);
    m_tablePushButtonsLayout_->setSpacing(0);

    m_sizePushButtonsLayout_ = new QHBoxLayout();
    m_sizePushButton5_ = new QPushButton("5x5");
    m_sizePushButton7_ = new QPushButton("7x7");
    m_sizePushButton9_ = new QPushButton("9x9");
    m_sizePushButtonsLayout_->addWidget(m_sizePushButton5_);
    m_sizePushButtonsLayout_->addWidget(m_sizePushButton7_);
    m_sizePushButtonsLayout_->addWidget(m_sizePushButton9_);

    m_mainLayout_ = new QVBoxLayout();
    m_mainLayout_->addLayout(m_tablePushButtonsLayout_);
    m_mainLayout_->addLayout(m_sizePushButtonsLayout_);

    setLayout(m_mainLayout_);
    newGame();
}

BlackHoleView::~BlackHoleView()
{
}

void BlackHoleView::newGame()
{
    initTable();
    refreshTable();
}

void BlackHoleView::initTable()
{
    for (QVector<QPushButton*> l_row : m_tablePushButtons_)
    {
        for (QPushButton* l_actTableButton : l_row)
        {
            m_tablePushButtonsLayout_->removeWidget(l_actTableButton);
            delete l_actTableButton;
        }
        l_row.clear();
    }

    int l_tableSize = 5;
    m_tablePushButtons_.resize(l_tableSize);
    for (int i = 0; i < l_tableSize; ++i)
    {
        m_tablePushButtons_[i].resize(l_tableSize);
        for (int j = 0; j < l_tableSize; ++j)
        {
            m_tablePushButtons_[i][j] = new QPushButton();
            m_tablePushButtons_[i][j]->setFixedSize(50, 50);
            m_tablePushButtons_[i][j]->setEnabled(false);
            m_tablePushButtonsLayout_->addWidget(m_tablePushButtons_[i][j], i, j);
        }
    }
}

void BlackHoleView::refreshTable()
{
    int l_tableSize = 5;
    for (int i = 0; i < l_tableSize; ++i)
    {
        for (int j = 0; j < l_tableSize; ++j)
        {
            int l_actTableValue = 0;
            QString l_color = "";
            switch(l_actTableValue)
            {
            case 1:
                l_color = "red";
                break;
            case 2:
                l_color = "blue";
                break;
            case 42:
                l_color = "black";
                break;
            }
            m_tablePushButtons_[i][j]->setStyleSheet("background-color: " + l_color);
        }
    }
}
