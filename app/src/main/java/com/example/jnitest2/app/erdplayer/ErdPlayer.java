package com.example.jnitest2.app.erdplayer;

import java.io.IOException;

/**
 * Created by chenran on 2015/9/24.
 */
public abstract class ErdPlayer {

    public abstract void prepare() throws IOException, IllegalStateException;

    public abstract void prepareAsync() throws IllegalStateException;

    public abstract void play() throws IllegalStateException;

    public abstract void pause() throws IllegalStateException;

    public abstract void stop() throws IllegalStateException;

    public abstract boolean isPlaying();

    public abstract void seekTo(int msec) throws IllegalStateException;

    public abstract long getCurrentTime();

    public abstract long getDuration();

    public abstract double getBufferPercent();
}
