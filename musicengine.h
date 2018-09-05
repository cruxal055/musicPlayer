#ifndef MUSICENGINE_H
#define MUSICENGINE_H
#include <string>
#include <QStringList>
#include <QDebug>
#include <QTimer>
#include <library.h>

using namespace std;

#include <QWidget>
#include <irrKlang.h>
#include <ik_ISoundDeviceList.h>

using namespace irrklang;

enum musicEngineErrors {NO_MUSIC_TO_PLAY,
                        ERROR_STARTING_ENGINE,
                        FILE_NOT_FOUND,
                        FILE_NOT_LOADED,
                        BAD_VOLUME,
                        BAD_PITCH};

namespace Ui {
class musicEngine;
}

class musicEngine : public QWidget
{
    Q_OBJECT

    public:
        explicit musicEngine(QWidget *parent = 0);
        ~musicEngine();
        musicEngine(string whatToPlay);
        QStringList& getDevices();
        float getVolume();
        float getBalance();
        void requestNewSong();
        float getCurrTime();
        void stopAllSounds();
        bool currentState();
        void changeCurrSong(std::string neo);
        string whatIsPlaying();

    signals:

       void currVolume(float volume);
       void songData(size_t volume, size_t time);
       void songFinished();
       void currPositionInSong(float time);
       void requestPrevious();

    public slots:
        void play();
        void loop(bool yes);
        void pause ();
        void stop ();
        void fastForward();
        void rewind();
        void restart();
        void setDevice(int deviceNumber);
        void setVolume (int vol);
        void setPlayingOffset(float timeOffset);
        void setWhatToPlay(string whatToPlay);
        void setBalance(int pan);
        void onTimeOut();
        void onSoundStopped();

    private:
        bool needNewSong;
        string currentPlay;
        irrklang::ISoundEngine* engine;
        irrklang::ISound* music;
        irrklang::ISoundDeviceList* deviceList;
        ik_f32 balance, volume;
        QStringList listOfDevices;
        QTimer *timer;
};

#endif
