package com.example.jnitest2.app.erdplayer;

import android.content.Context;

import com.example.jnitest2.app.erdplayer.audioplayer.AudioPlayer;

import java.io.IOException;

/**
 * Created by chenran on 2015/9/24.
 */
public class ErdAudioPlayer extends ErdPlayer {
    private AudioPlayer audioPlayer;

    public ErdAudioPlayer(Context context) {
        AudioLibUtils.loadAudioLib();
        audioPlayer = new AudioPlayer();
    }

    @Override
    public void prepare() throws IOException, IllegalStateException {

    }

    @Override
    public void prepareAsync() throws IllegalStateException {

    }

    @Override
    public void play() throws IllegalStateException {
        audioPlayer.play();
    }

    @Override
    public void pause() throws IllegalStateException {
        audioPlayer.pause();
    }

    @Override
    public void stop() throws IllegalStateException {
        audioPlayer.stop();
    }

    @Override
    public boolean isPlaying() {
        return audioPlayer.isPlaying();
    }

    @Override
    public void seekTo(int msec) throws IllegalStateException {
        audioPlayer.seekTo(msec);
    }

    @Override
    public long getCurrentTime() {
        return audioPlayer.getCurrentTime();
    }

    @Override
    public long getDuration() {
        return audioPlayer.getDuration();
    }

    @Override
    public double getBufferPercent() {
        return audioPlayer.getBufferPercent();
    }
}
