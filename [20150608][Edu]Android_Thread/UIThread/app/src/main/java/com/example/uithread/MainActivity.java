package com.example.uithread;

import android.app.Activity;
import android.os.Bundle;
import android.os.Handler;
import android.os.Message;
import android.view.Menu;
import android.view.MenuItem;
import android.view.View;
import android.widget.TextView;

public class MainActivity extends Activity {
    TextView mText;
    int mSec = 0;

//    Thread thread = new Thread(new Runnable() {
//        @Override
//        public void run() {
//            while(true) {
//                ++mSec;
//                mText.setText(mSec + "");
//                try { Thread.sleep(1000);} catch (InterruptedException e) { e.printStackTrace(); }
//            }
//        }
//    });

        Thread thread = new Thread(new Runnable() {
        @Override
        public void run() {
            while(true) {
                ++mSec;

                Message msg = Message.obtain();
                msg.arg1 = mSec;
                msg.what = 0;

                mHandler.sendMessage(msg);


                try { Thread.sleep(1000);} catch (InterruptedException e) { e.printStackTrace(); }
            }
        }
    });


    // 1. create handler
    Handler mHandler = new Handler() {
        @Override
        public void handleMessage(Message msg) {

            switch(msg.what)
            {
                case 0:
                    int data = msg.arg1;
                    mText.setText(data +"");
                    break;
                default:
                    super.handleMessage(msg);
            }
        }
    };

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        mText = (TextView)findViewById(R.id.txt_view);
    }

    public void onClick(View view) {


        thread.start();
    }
}
