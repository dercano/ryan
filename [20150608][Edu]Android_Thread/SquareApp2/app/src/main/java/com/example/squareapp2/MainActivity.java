package com.example.squareapp2;

import android.app.Activity;
import android.content.ComponentName;
import android.content.Context;
import android.content.Intent;
import android.content.ServiceConnection;
import android.os.Bundle;
import android.os.Handler;
import android.os.IBinder;
import android.os.Message;
import android.os.Messenger;
import android.os.RemoteException;
import android.view.Menu;
import android.view.MenuItem;
import android.view.View;
import android.widget.EditText;
import android.widget.Toast;

public class MainActivity extends Activity {

    EditText mEdit;

    Messenger mServiceMessenger = null;
    Messenger mActivityMessenger = new Messenger(new Handler() {
        @Override
        public void handleMessage(Message msg) {
            switch(msg.what) {
                case SquareService.MSG_RESULT:
                    int result = msg.arg1;
                    Toast.makeText(getApplicationContext(), result + "", Toast.LENGTH_LONG).show();
                    break;
                default:
                    super.handleMessage(msg);
            }
        }
    });

    ServiceConnection mConnection  = new ServiceConnection() {
        @Override
        public void onServiceConnected(ComponentName name, IBinder service) {
            mServiceMessenger = new Messenger(service);

            Message msg = Message.obtain(null, SquareService.MSG_REGISTER_CLIENT);
            msg.replyTo = mActivityMessenger;

            try {
                mServiceMessenger.send(msg);
            } catch (RemoteException e) {
                e.printStackTrace();
            }
        }

        @Override
        public void onServiceDisconnected(ComponentName name) {
            mServiceMessenger = null;
        }
    };

    boolean mBound = false;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_main);

        mEdit = (EditText)findViewById(R.id.edit_input);

        Intent intent = new Intent(MainActivity.this, SquareService.class);
        mBound = bindService(intent, mConnection, Context.BIND_AUTO_CREATE);
    }

    public void onClick(View view) {
        if(mBound) {
            int data = Integer.parseInt(mEdit.getText().toString());

            try {
                mServiceMessenger.send(Message.obtain(null, SquareService.MSG_SQUARE, data, 0));
            } catch (RemoteException e) {
                e.printStackTrace();
            }
        }
    }

    @Override
    protected void onStop() {
        super.onStop();

        if(mBound) {
            Message msg = Message.obtain(null, SquareService.MSG_UNREGISTER_CLIENT);

            try {
                mServiceMessenger.send(msg);
            } catch (RemoteException e) {
                e.printStackTrace();
            }

            unbindService(mConnection);
            mBound = false;
        }
    }
}
