#ifndef AUDIOENGINE_H
#define AUDIOENGINE_H

#include <gst/gst.h>
#include <glib.h>
#include <QObject>

class AudioEngine : public QObject {
    Q_OBJECT
public:
    AudioEngine(QObject *parent = 0);
    ~AudioEngine();

    int Init();

    void MusicPlay();
    void MusicPaused();
    void MusicStop();
    void AddFile(char *file);
    void SetVolume(gdouble val);
    gint64 GetMusicPosition();
    gint64 GetMusicDuration();
    void SetMusicPosition(gint64 pos);

private:
    GstElement *pipeline;
    GstElement *source;
    GstElement *volume;
    gint64 pos;

    static void OnPadAdded(GstElement *element, GstPad *pad, gpointer data);

private slots:
};

#endif // AUDIOENGINE_H
