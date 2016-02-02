package com.example.jnitest2.app;

import android.app.Activity;
import android.os.Bundle;
import android.view.Menu;
import android.view.MenuItem;
import android.view.View;

import com.example.jnitest2.app.erdplayer.ErdAudioPlayer;
import com.example.jnitest2.app.erdplayer.audioplayer.AudioPlayer;

import java.io.IOException;

public class MainActivity extends Activity implements View.OnClickListener {
    private ErdAudioPlayer player;
    private String filePath = "/storage/sdcard0/erdmusic/download/songs/123.mp3";
    private AudioPlayer decoder;
    private String basePath = "/storage/sdcard0/erdmusic/download/songs/123.";

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        findViewById(R.id.play_mp3).setOnClickListener(this);
        findViewById(R.id.play_flac).setOnClickListener(this);
        findViewById(R.id.play_ape).setOnClickListener(this);
        findViewById(R.id.play_net_song).setOnClickListener(this);
        findViewById(R.id.pause).setOnClickListener(this);
        decoder = new AudioPlayer();
    }

    private void setDataSource(String path) {
        try {
            decoder.setDataSource(path);
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    @Override
    public boolean onCreateOptionsMenu(Menu menu) {
        // Inflate the menu; this adds items to the action bar if it is present.
        getMenuInflater().inflate(R.menu.menu_main, menu);
        return true;
    }

    @Override
    public boolean onOptionsItemSelected(MenuItem item) {
        // Handle action bar item clicks here. The action bar will
        // automatically handle clicks on the Home/Up button, so long
        // as you specify a parent activity in AndroidManifest.xml.
        int id = item.getItemId();
        //noinspection SimplifiableIfStatement
        if (id == R.id.action_settings) {
            return true;
        }

        return super.onOptionsItemSelected(item);
    }

    @Override
    public void onClick(View v) {
        switch (v.getId()) {
            case R.id.play_mp3:
//                if (player == null) {
//                    player = new ErdAudioPlayer(this);
//
//                }
//                player.play();
                if(decoder != null) {
                    decoder.stop();
                    decoder.prepare();
                    setDataSource(basePath + "mp3");
                    decoder.play();
                }
                break;
            case R.id.play_ape:
                if(decoder != null) {
                    decoder.stop();
                    decoder.prepare();
                    setDataSource(basePath + "ape");
                    decoder.play();
                }
                break;
            case R.id.play_flac:
                if(decoder != null) {
                    decoder.stop();
                    decoder.prepare();
                    setDataSource(basePath + "flac");
                    decoder.play();
                }
                break;
            case R.id.pause:
                if(decoder != null) {
                    decoder.stop();
                }
//                player.pause();
                break;
            case R.id.play_net_song:
                if (decoder != null) {
                    decoder.stop();
                    decoder.prepare();
                    setDataSource("http://m2.music.126.net/WXQDkKwErz3t2RWavP0FfA==/7880199837360434.mp3");
                    decoder.play();
                }
                break;
        }
    }
}
