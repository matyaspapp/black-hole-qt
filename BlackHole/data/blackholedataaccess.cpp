#include <QFile>
#include <QFileInfo>
#include <QDateTime>
#include <QTextStream>

#include "blackholedataaccess.h"

QVector<QString> BlackHoleDataAccess::getSavedGameList() const
{
    QVector<QString> l_savedGames(5);
    for (int i = 0; i < 5; ++i)
    {
        if (QFile::exists("game" + QString::number(i) + ".sav"))
        {
            QFileInfo info("game" + QString::number(i) + ".sav");
            l_savedGames[i] = "[" + QString::number(i) + "]"
                            + info.lastModified().toString("yyyy.MM.dd HH:mm:ss");
        }
    }

    return l_savedGames;
}

bool BlackHoleDataAccess::saveGame(int f_gameIndex, const QVector<int>& f_saveGameData)
{
    QFile l_file("game"+ QString::number(f_gameIndex) + ".sav");
    if (!l_file.open(QFile::WriteOnly))
    {
        return false;
    }

    QTextStream l_fileStream(&l_file);
    int l_dataSize = f_saveGameData.length();
    for (int i = 0; i < l_dataSize; ++i)
    {
        l_fileStream << f_saveGameData[i] << endl;
    }
    l_file.close();

    return true;
}

bool BlackHoleDataAccess::loadGame(int f_gameIndex, QVector<int>& f_savedGameData)
{
    QFile l_file("game" + QString::number(f_gameIndex) + ".sav");
    if (!l_file.open(QFile::ReadOnly))
    {
        return false;
    }

    QTextStream l_fileStream(&l_file);
    bool l_isFirstPlayerMove = l_fileStream.readLine().toInt();
    int l_tableSize = l_fileStream.readLine().toInt();
    int l_dataSize = 2 + l_tableSize * l_tableSize;
    f_savedGameData.resize(l_dataSize);
    f_savedGameData[0] = l_isFirstPlayerMove;
    f_savedGameData[1] = l_tableSize;
    for (int i = 2; i < l_dataSize; ++i)
    {
        f_savedGameData[i] = l_fileStream.readLine().toInt();
    }
    l_file.close();

    return true;
}
