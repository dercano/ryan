package com.example.squareapp2;

import android.app.Service;
import android.content.Intent;
import android.os.Handler;
import android.os.IBinder;
import android.os.Message;
import android.os.Messenger;
import android.os.RemoteException;

public class SquareService extends Service {

    public final static int MSG_SQUARE = 1;
    public final static int MSG_RESULT = 2;

    public final static int MSG_REGISTER_CLIENT = 3;
    public final static int MSG_UNREGISTER_CLIENT = 4;

    Messenger mActivityMessenger = null;

    final Messenger mServiceMessenger = new Messenger(new Handler() {
        @Override
        public void handleMessage(Message msg) {
            switch(msg.what) {
                case MSG_SQUARE:
                    if(mActivityMessenger == null) break;
                    int data = msg.arg1;
                    int result = data * data;
                    try {
                        mActivityMessenger.send(Message.obtain(null, MSG_RESULT, result, 0));
                    } catch (RemoteException e) {
                        e.printStackTrace();
                    }
                    break;
                case MSG_REGISTER_CLIENT:
                    mActivityMessenger = msg.replyTo;
                    break;
                case MSG_UNREGISTER_CLIENT:
                    mActivityMessenger = null;
                default:
                    super.handleMessage(msg);
            }
        }
    });

    @Override
    public IBinder onBind(Intent intent) {
        return mServiceMessenger.getBinder();
    }
}

