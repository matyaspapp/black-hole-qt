#include "savegame.h"

SaveGame::SaveGame(QWidget *parent)
    : QDialog(parent)
{
    setFixedSize(300, 200);
    setWindowTitle("Save Game");

    m_buttonsLayout_ = new QHBoxLayout();
    m_okButton_ = new QPushButton("Ok");
    m_cancelButton_ = new QPushButton("Cancel");
    m_buttonsLayout_->addWidget(m_okButton_);
    m_buttonsLayout_->addWidget(m_cancelButton_);

    m_mainLayout_ = new QVBoxLayout();
    m_listWidget_ = new QListWidget();
    m_mainLayout_->addWidget(m_listWidget_);
    m_mainLayout_->addLayout(m_buttonsLayout_);

    setLayout(m_mainLayout_);

    connect(m_okButton_, SIGNAL(clicked()), this, SLOT(accept()));
    connect(m_cancelButton_, SIGNAL(clicked()), this, SLOT(reject()));
}

void SaveGame::setGameList(QVector<QString> f_saveGameList)
{
    m_listWidget_->clear();
    for (int i = 0; i < 5; i++)
    {
        if (i < f_saveGameList.size() && !f_saveGameList[i].isEmpty())
            m_listWidget_->addItem(f_saveGameList[i]);
        else
            m_listWidget_->addItem("empty");
    }
}

int SaveGame::getSelectedGame()
{
    return m_listWidget_->currentRow();
}
