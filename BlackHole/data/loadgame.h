#ifndef LOADGAME_H
#define LOADGAME_H

#include "savegame.h"

class LoadGame : public SaveGame
{
    Q_OBJECT
public:
    LoadGame(QWidget *parent = 0);
    virtual ~LoadGame() {}
protected slots:
    void okButtonClicked();
};

#endif // LOADGAME_H
