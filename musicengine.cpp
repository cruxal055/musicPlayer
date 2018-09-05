#include "musicengine.h"
#include "ui_musicengine.h"


musicEngine::musicEngine(QWidget *parent) :
    QWidget(parent),
    balance(0),
    volume(50)
{
    deviceList = irrklang::createSoundDeviceList();
    int deviceCount = deviceList->getDeviceCount();
    qDebug()<<"Number of devices found: "<<deviceCount;
    for(int i = 0; i < deviceCount; ++i)
    {
        qDebug()<<deviceList->getDeviceDescription(i);
        //qDebug()<<deviceList->getDeviceDescription(i);
        listOfDevices.append(deviceList->getDeviceDescription(i));
        //listOfDevices << deviceList->getDeviceDescription(i);
    }
    setDevice(0);
    setBalance(balance);
    setVolume(volume);
    system("cd");

}



musicEngine::~musicEngine()
{
    qDebug() << "destructing itself\n";
    deviceList->drop();
    if (music)
        music->drop(); // release music stream.
    engine->drop(); // delete engine
}

musicEngine::musicEngine(string whatToPlay)
{
    currentPlay = whatToPlay;
}


void musicEngine::stopAllSounds()
{
    engine->stopAllSounds();
    qDebug() << "should not have moved";
}
float musicEngine::getBalance()
{
    return balance;
}

float musicEngine::getVolume()
{
    return volume;
}


QStringList& musicEngine::getDevices()
{
    return listOfDevices;
}
string musicEngine::whatIsPlaying()
{
    return currentPlay;
}
void musicEngine::loop(bool yes)
{
    if(yes)
        play();
}
bool musicEngine::currentState()
{
    return needNewSong;
}
/*
void musicEngine::requestNewSong()
{
    library temp;
    QFileInfo convert(QString::fromStdString(currentPlay));
    QString omfg =  convert.fileName();
    temp.setCurrent(omfg);
    bool isEnd;
    QString hold = QString::fromStdString(currentPlay);
    temp.LoadNewAmmo(hold,isEnd);
    if(isEnd)
    {
        qDebug() << "omfggggg";
        music->drop();
    }
    else
        currentPlay = hold.toStdString();
}*/
void musicEngine::play()
{
    qDebug() << "reached the play\n";
    qDebug() << "i should be playing this now: " << QString::fromStdString(currentPlay) << endl;
    engine->stopAllSounds();
    music = engine->play2D((currentPlay).c_str(),false, false, true);
    //f(engine->play2D("/Users/blank/Desktop/myMusic_for_Mac_with_irrklang 2/myMusic.app/Contents/MacOS/sample.mp3" ) != 0)
    if(music != 0)
        qDebug() << "wtf?";
    if(music)
    {
        setVolume(volume);
        setBalance(balance);
        music->setPan(balance);
       // volume = music->getVolume();
        timer = new QTimer(this);
        timer->setTimerType(Qt::TimerType::CoarseTimer);
        timer->start(500);
       // his ver connect(timer,SIGNAL(timeout()),this,SLOT(onSoundStopped()));
         connect(timer,SIGNAL(timeout()),this,SLOT(onSoundStopped()));
        emit songData(music->getVolume()*100,music->getPlayLength());
    }
}


void musicEngine::onSoundStopped()
{
    onTimeOut();
}

void musicEngine::setDevice(int deviceNumber)
{
    const char* deviceID = deviceList->getDeviceID(deviceNumber);
    if(engine)
        engine->drop();
    engine = createIrrKlangDevice();
    setBalance(0);

}

void musicEngine::pause()
{
    if(!music)
        return;
    else
        music->setIsPaused(music->getIsPaused() ? false : true);
}

void musicEngine::stop()
{
    music->stop();
    music->drop();
}

void musicEngine::fastForward()
{
   if(music)
   {
       float currPos = music->getPlayPosition()+5000;
       if(currPos >= music->getPlayLength())
            currPos = music->getPlayLength();
        music->setPlayPosition(currPos);
        emit currPositionInSong(music->getPlayPosition());
   }
   else
       onTimeOut();
   if(music->isFinished())
       music->stop();


//   if(music->getMaxDistance())
}

void musicEngine::rewind()
{
    float temp = 4.290e+08f;
    qDebug() << "the current play position is: " <<  music->getPlayPosition();
    float currPos = music->getPlayPosition() - 5000;
    double conv = currPos;
    qDebug() << "current position is: " << currPos;
    qDebug() << currPos;
    qDebug() << conv;
    if(currPos <= 0 || temp < currPos)
    {
      //  restart();
        emit requestPrevious();
      //  music->
        //  music->stop();
    }
    else
    {
        music->setPlayPosition(currPos);
    }
}

void musicEngine::restart()
{
    if(!music)
        return;
    else
    {
        setBalance(balance);
        setVolume(volume);
        music->setPlayPosition(0);
        emit currPositionInSong(0);
    }

}

void musicEngine::setVolume(int vol)
{
    qDebug() <<  volume;
    volume = vol;
    if(music)
        music->setVolume(volume/100.);
}

void musicEngine::setPlayingOffset(float timeOffset)
{
    float millisecs = timeOffset/100. * music->getPlayLength();
    music->setPlayPosition(millisecs);
}

void musicEngine::setBalance(int pan)
{
    balance = -pan/50.0;
    if(music)
        music->setPan(balance);
}

void musicEngine::setWhatToPlay(string whatToPlay)
{
   currentPlay = whatToPlay;
}

void musicEngine::onTimeOut()
{
    if(music->isFinished())
    {
        delete timer;
       // requestNewSong();
        //qDebug() <<
        //play();
        emit songFinished();
    }   // emit songFinished();
}
