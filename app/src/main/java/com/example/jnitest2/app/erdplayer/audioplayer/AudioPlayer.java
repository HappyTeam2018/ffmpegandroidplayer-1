package com.example.jnitest2.app.erdplayer.audioplayer;

import android.media.AudioFormat;
import android.media.AudioTrack;
import android.os.Handler;
import android.os.HandlerThread;
import android.os.Looper;
import android.os.Message;
import android.util.Log;

import com.example.jnitest2.app.erdplayer.AudioLibUtils;

import java.io.IOException;

/**
 * Created by chenran on 2015/10/16.
 */
public class AudioPlayer {
    private AudioTrack audioTrack;
    private HandlerThread handlerThread;
    private WorkHandler workHandler;
    private boolean isPlaying = false;

    private int samplerate,channeltype,minbufsize;

    public void setDataSource(String sourceFile) throws IOException {
        openFile(sourceFile);
        samplerate=getSampleRate();
        if (getChannel()==1)
            channeltype=AudioFormat.CHANNEL_OUT_MONO;
        else
            channeltype= AudioFormat.CHANNEL_OUT_STEREO;

        Log.i("TIMON", "samplerate--->" + samplerate);
        Log.i("TIMON", "channeltype--->" + channeltype);
        Log.i("TIMON", "channel--->" + getChannel());
        minbufsize= AudioTrack.getMinBufferSize(samplerate, channeltype, AudioFormat.ENCODING_PCM_16BIT);
        audioTrack = new AudioTrack(android.media.AudioManager.STREAM_MUSIC,samplerate,channeltype,
                AudioFormat.ENCODING_PCM_16BIT,
                minbufsize*2,
                AudioTrack.MODE_STREAM);
    }

    public void prepare() {
        JNIInit();
    }

    public void play() {
        if (!isPlaying) {
            isPlaying = true;
            audioTrack.play();
            workHandler.sendEmptyMessage(0);
        }
    }

    public void pause() {
        if (isPlaying) {
            workHandler.removeMessages(0);
            isPlaying = false;
            audioTrack.pause();
        }
    }

    public void stop() {
        if (isPlaying) {
            workHandler.removeMessages(0);
            isPlaying = false;
            audioTrack.stop();
            audioTrack.release();
            JNIExit();
        }
    }

    public void seekTo(int msec) {

    }

    public long getCurrentTime() {
        return 0;
    }

    public long getDuration() {
        return 0;
    }

    public double getBufferPercent() {
        return 0.0;
    }

    public boolean isPlaying() {
        return isPlaying;
    }

    public AudioPlayer() {
        handlerThread = new HandlerThread("workHandler");
        handlerThread.start();
        workHandler = new WorkHandler(handlerThread.getLooper());
        AudioLibUtils.loadAudioLib();
    }

    private class WorkHandler extends Handler {

        public WorkHandler(Looper looper) {
            super(looper);
        }

        @Override
        public void handleMessage(Message msg) {
            byte[] bytes=stream(minbufsize);
            int dsize=getDataSize();
            if(audioTrack.write(bytes, 0, dsize)<dsize) {
            }
            if (!isPlaying) {
                return;
            }
            Log.i("TIMON", "handleMessage--->");
            workHandler.sendEmptyMessageDelayed(0, 50);

        }
    }

    @Override
    protected void finalize() throws Throwable {
        JNIExit();
        workHandler.removeMessages(0);
        super.finalize();
    }


    public native byte[] stream(int minbufsize);
    public native int getDataSize();
    public native void openFile(String sourceFile) throws IOException;
    public native int getSampleRate();
    public native int getChannel();
    public native void JNIInit();
    public native void JNIExit();
}
