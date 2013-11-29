#include "audioengine.h"
#include <QDebug>
#include <gst/audio/streamvolume.h>
#include <gst/controller/gstinterpolationcontrolsource.h>
#include <gst/controller/gstdirectcontrolbinding.h>
#include <string>

AudioEngine::AudioEngine(QObject *parent) : QObject(parent) {
    pipeline = new GstElement();
    source = new GstElement();
    volume = new GstElement();
}

AudioEngine::~AudioEngine() {
    gst_object_unref (GST_OBJECT (pipeline));
}

void AudioEngine::OnPadAdded(GstElement *element, GstPad *pad, gpointer data) {
  GstPad *sinkpad;
  GstElement *decoder = (GstElement *) data;

  sinkpad = gst_element_get_static_pad(decoder, "sink");

  gst_pad_link(pad, sinkpad);

  gst_object_unref(sinkpad);
}



int AudioEngine::Init() {
  GstElement *demuxer, *decoder, *conv, *sink;

  gst_init(0, 0);

  pipeline = gst_pipeline_new("audio-player");
  source = gst_element_factory_make("filesrc", NULL);
  demuxer = gst_element_factory_make("decodebin", NULL);
  decoder = gst_element_factory_make("audioconvert", NULL);
  volume = gst_element_factory_make("volume", NULL);
  conv = gst_element_factory_make("audioconvert",  NULL);
  sink = gst_element_factory_make("autoaudiosink", NULL);

  if (!pipeline || !source || !demuxer || !decoder || !volume || !conv || !sink) {
    return -1;
  }

  gst_bin_add_many(GST_BIN (pipeline),
                    source, demuxer, decoder, volume, conv, sink, NULL);

  gst_element_link(source, demuxer);

  gst_element_link_many(decoder, volume, conv, sink, NULL);

  g_signal_connect(demuxer, "pad-added", G_CALLBACK(OnPadAdded), decoder);

  return 0;
}

void AudioEngine::AddFile(char *file) {
    g_object_set(G_OBJECT(source), "location", file, NULL);
}

void AudioEngine::MusicPlay() {
    gst_element_set_state(pipeline, GST_STATE_PLAYING);
}

void AudioEngine::MusicPaused() {
    gst_element_set_state(pipeline, GST_STATE_PAUSED);
}

void AudioEngine::MusicStop() {
    gst_element_set_state(pipeline, GST_STATE_READY);
}

void AudioEngine::SetVolume(gdouble val) {
    g_object_set(G_OBJECT(volume), "volume", val, NULL);
}

gint64 AudioEngine::GetMusicDuration() {
    gint64 len;
    gst_element_query_duration(pipeline, GST_FORMAT_TIME, &len);
    return len;
}

gint64 AudioEngine::GetMusicPosition() {
    gint64 pos;
    gst_element_query_position(pipeline, GST_FORMAT_TIME, &pos);
    return pos;
}

void AudioEngine::SetMusicPosition(gint64 pos) {
    gst_element_set_state(pipeline, GST_STATE_PAUSED);
    gst_element_seek_simple(pipeline, GST_FORMAT_TIME, GST_SEEK_FLAG_FLUSH, pos);
    gst_element_set_state(pipeline, GST_STATE_PLAYING);
}
