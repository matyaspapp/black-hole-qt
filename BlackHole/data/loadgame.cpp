#include "loadgame.h"
#include <QMessageBox>

LoadGame::LoadGame(QWidget *parent)
    : SaveGame(parent)
{
    setWindowTitle("Load Game");
    disconnect(m_okButton_, SIGNAL(clciked()),
               this, SLOT(okButtonClicked()));
    connect(m_okButton_, SIGNAL(clicked()),
            this, SLOT(okButtonClicked()));
}

void LoadGame::okButtonClicked()
{
    if ("empty" == m_listWidget_->currentItem()->text())
    {
        QMessageBox::warning(this, "BlackHole", "There is no selected game!");
        return;
    }

    Q_EMIT accept();
}
