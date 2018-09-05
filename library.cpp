#include "library.h"

library::library()
{
    loadData();
}
library::~library()
{

}

QList<QString> library::listTitles()
{
    QList<QString> titles;
    titles<<"Name"<<"Artist"<<"Album"<<"Year";
    return titles;
}
int library::displayCols()
{
    int cols = 4;
    return cols;
}

QList<QString> library::listOfSongs(QList<QString> songs)
{
    songs = songNames;
    return songs;
}

void library::set(QString key, QString data)
{
    musica[key] = data;
    songNames << key;
    saveData();
}

QString library::get(QString key)
{
    return musica[key];
}

void library::setRepeat(bool value)
{
    toRepeat = value;
}

QString library::pathToName(QString toConvert)
{
    QFileInfo converter(toConvert);
    return converter.fileName();
}

void library::saveData()
{
    if(musica.empty())
        return;
    QXmlStreamWriter writer;
  //  QFile out("your own directory");
    out.open(QFile::WriteOnly);
    writer.setDevice(&out);
    writer.setAutoFormatting(true);
    writer.writeStartDocument();
    writer.writeStartElement("library");
    for(int i = 0; i < songNames.size(); ++i)
    {
      writer.writeStartElement("song");
      writer.writeStartElement("name");
      writer.writeCharacters(songNames[i]);
      writer.writeEndElement();
      writer.writeStartElement("path");
      writer.writeCharacters(musica[songNames[i]]);
      writer.writeEndElement();
      writer.writeEndElement();
    }
    writer.writeEndElement();
    writer.writeEndDocument();
    out.close();
}

void library::LoadNewAmmo()
{
    bool beg = false;
    if(current == songNames.last())
    {
        if(toRepeat)
        {
            qDebug() << "toRepeat is selected";
            current = songNames[0];
            beg = true;
        }
        else
        {
            qDebug() << "toRepeat is not selected\n";
            current.clear();
            return;
        }
    }
        int pos = songNames.indexOf(current);
        qDebug() << "the current is: " << current;
        if(!beg)
        {
            ++pos;
        }
        current = songNames[pos];
        setCurrent(songNames[pos]);
}

void library::loadData()
{
   //QFile input("your own ");

    QXmlStreamReader reader;
    input.open(QFile::ReadOnly | QFile::Text);
    reader.setDevice(&input);
    QStringList unpacker;
    while(!reader.atEnd() && !reader.hasError())
    {
        while(!reader.atEnd() && !reader.hasError())
        {
            reader.readNext();
            if(reader.isStartElement())
                continue;
            if(reader.isCharacters() && !reader.isWhitespace())
                unpacker << reader.text().toString();
        }
    }
    for(size_t i=0; i<unpacker.size(); ++i)
    {
        QString temp = unpacker[i];
        songNames << unpacker[i];
        ++i;
        musica[temp] = unpacker[i];
    }

    input.close();
}

void library::copyKeys(QStringList &same)
{
    same = songNames;
}
QString library::getPath(const QString key)
{
    return musica[key];
}
QString library::getPrevious()
{
    QString toPlay;
    if(songNames.size() == 0)
        toPlay = " ";
    if(songNames.size() == 1)
        toPlay = musica[songNames[0]];
    else
    {
        int pos = songNames.indexOf(current);
        --pos;
        toPlay = musica[songNames[pos]];
        setCurrent(songNames[pos]);
    }
    return toPlay;
}
QString library::getNext()
{
    QString toPlay;
 //   if(songNames.size() == 0)
   //     toPlay = " ";
     int error = 7;
     QChar hide = error;
     if(songNames.size() == 1)
         toPlay = musica[songNames[0]];
    if(current == songNames.last())
        toPlay = hide;
    else
    {
        int pos = songNames.indexOf(current);
        ++pos;
        toPlay = musica[songNames[pos]];
        setCurrent(songNames[pos]);
    }

    return toPlay;
}
void library::setCurrent(QString playing)
{
    current = playing;
}
QString library::getCurrent()
{
    return current;

}
