#ifndef BLACKHOLEDATAACCESS_H
#define BLACKHOLEDATAACCESS_H

#include <QVector>
#include <QDebug>

class BlackHoleDataAccess
{
public:
    QVector<QString> getSavedGameList() const;

    bool saveGame(int, const QVector<int>&);
};

#endif // BLACKHOLEDATAACCESS_H
