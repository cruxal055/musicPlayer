#ifndef LIBRARY_H
#define LIBRARY_H
#include <vector>
#include <string>
#include <QStringList>
#include <QDebug>
#include <QTimer>
#include <map>
#include <irrKlang.h>
#include <qfiledialog.h>
#include <qwidget.h>
#include <qmap>
#include <qxmlstream.h>
#include <QXmlStreamReader>
#include <QList>
#include <QMessageBox>

class library
{
    public:
        library();
        ~library();
        void grabSong();
        void set(QString key, QString data);
        void setCurrent(QString playing);
        void saveData();
        void loadData();
        void copyKeys(QStringList &same);
        void LoadNewAmmo();
        void setRepeat(bool value);
        QString getPath(const QString key);
        QString getNext();
        QString getPrevious();
        QString getCurrent();
        QString get(QString key);
        QString pathToName(QString toConvert);

        int displayCols();
        QList<QString> listTitles();
        QList<QString> listOfSongs(QList<QString> songs);

    signals:
        void lastElementReached();

    private:
        QMap<QString,QString> musica;
        QStringList songNames;
        QString current;
        bool toRepeat;


};

#endif // LIBRARY_H
