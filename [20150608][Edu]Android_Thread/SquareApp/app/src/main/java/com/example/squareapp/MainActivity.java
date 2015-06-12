package com.example.squareapp;

import android.app.Activity;
import android.os.Bundle;
import android.os.Handler;
import android.os.Looper;
import android.os.Message;
import android.view.Menu;
import android.view.MenuItem;
import android.view.View;
import android.widget.EditText;
import android.widget.Toast;

public class MainActivity extends Activity {

    public static final int DO_SQUARE = 1;

    EditText mEdit;

    Handler mHandler = new Handler() {
        @Override
        public void handleMessage(Message msg) {
            switch(msg.what) {
                case SquareThread.RESULT_SQUARE:
                    int result = msg.arg1;
                    Toast.makeText(getApplicationContext(), result + "", Toast.LENGTH_LONG).show();
                    break;
                default:
                    super.handleMessage(msg);
            }
        }
    };

    public static class SquareThread extends Thread {

        public static final int RESULT_SQUARE = 1;

        private Handler mAcitivtyHandler;
        public Handler mThreadHandler;

        public SquareThread(Handler h) { mAcitivtyHandler = h; }

        @Override
        public void run()
        {
            Looper.prepare();

            mThreadHandler = new Handler(){
                @Override
                public void handleMessage(Message msg) {
                    switch(msg.what) {
                        case MainActivity.DO_SQUARE: {
                            int data = msg.arg1;
                            int result = data * data;

                            Message message = Message.obtain();
                            message.arg1 = result;
                            message.what = SquareThread.RESULT_SQUARE;

                            mAcitivtyHandler.sendMessage(message);
                        }
                        break;
                        default:
                            super.handleMessage(msg);
                    }
                }
            };

            Looper.loop();
        }

    }

    SquareThread squareThread;


    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);
        mEdit = (EditText)findViewById(R.id.edit_input);

        squareThread = new SquareThread(mHandler);
        squareThread.start();
    }

    public void onClick(View view) {
        int data = Integer.parseInt(mEdit.getText().toString());

        Message msg = Message.obtain();
        msg.what = MainActivity.DO_SQUARE;
        msg.arg1 = data;

        squareThread.mThreadHandler.sendMessage(msg);
    }

}
