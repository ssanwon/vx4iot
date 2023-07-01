package com.example.app;

import android.annotation.SuppressLint;
import android.app.NotificationChannel;
import android.app.NotificationManager;
import android.app.Service;
import android.content.Intent;
import android.content.pm.PackageManager;
import android.os.Build;
import android.os.IBinder;
import android.widget.Toast;

import androidx.annotation.NonNull;
import androidx.core.app.ActivityCompat;
import androidx.core.app.NotificationCompat;
import androidx.core.app.NotificationManagerCompat;

import com.google.firebase.database.DataSnapshot;
import com.google.firebase.database.DatabaseError;
import com.google.firebase.database.DatabaseReference;
import com.google.firebase.database.FirebaseDatabase;
import com.google.firebase.database.ValueEventListener;

import java.text.SimpleDateFormat;
import java.util.Date;
import java.util.Objects;

public class MyService extends Service {

    private final DatabaseReference mData = FirebaseDatabase.getInstance().getReference();
    private static final String CHANNEL_ID = "simplified_coding";
    private SettingData settingData;
    private CurrentData currentData;
    private String timeOld = "";
    private String timeOld1 = "";

    public MyService() {

    }

    @Override
    public int onStartCommand(Intent intent, int flags, int startId) {

        if (Build.VERSION.SDK_INT >= Build.VERSION_CODES.O) {
            CharSequence name = "My Channel";
            String description = "My Channel Description";
            int importance = NotificationManager.IMPORTANCE_DEFAULT;
            NotificationChannel channel = new NotificationChannel(CHANNEL_ID, name, importance);
            channel.setDescription(description);

            NotificationManager notificationManager = getSystemService(NotificationManager.class);
            notificationManager.createNotificationChannel(channel);
        }

        realTimeData();

        return super.onStartCommand(intent, flags, startId);
    }

    private void realTimeData() {
        mData.child("Setting").addValueEventListener(new ValueEventListener() {
            @Override
            public void onDataChange(@NonNull DataSnapshot snapshot) {
                settingData = snapshot.getValue(SettingData.class);
                if (settingData != null) {
                    mData.child("Current").addValueEventListener(new ValueEventListener() {
                        @Override
                        public void onDataChange(@NonNull DataSnapshot snapshot) {
                            currentData = snapshot.getValue(CurrentData.class);
                            if (currentData != null) {
                                if (currentData.temp >= Integer.parseInt(settingData.tempAlarm))
                                    sendNotification_1();

                                @SuppressLint("SimpleDateFormat") SimpleDateFormat sdf = new SimpleDateFormat("dd-MM-yyyy");
                                String currentDateandTime = sdf.format(new Date());

                                if (!Objects.equals(currentData.time1, timeOld1)) {
                                    if(currentData.status == 1) {
                                        HistoryData historyData = new HistoryData("On", currentData.time1);
                                        mData.child("History/" + currentDateandTime).push().setValue(historyData);
                                        timeOld1 = currentData.time1;
                                    }
                                    else if (currentData.status == 0) {
                                        HistoryData historyData = new HistoryData("Off", currentData.time1);
                                        mData.child("History/" + currentDateandTime).push().setValue(historyData);
                                        timeOld1 = currentData.time1;
                                    }
                                }

                                if(!Objects.equals(currentData.time, timeOld)) {
                                    timeOld = currentData.time;

                                    int index = currentData.time.indexOf(" ");

                                    String time1 = currentData.time.substring(0, index);

                                    ChartData chartData = new ChartData(time1, currentData.temp);
                                    mData.child("Chart/" + currentDateandTime).push().setValue(chartData);
                                }

//                                if(Objects.equals(currentData.unit, "°C")) {
//
//                                }

                            }
                        }

                        @Override
                        public void onCancelled(@NonNull DatabaseError error) {

                        }
                    });
                }
            }

            @Override
            public void onCancelled(@NonNull DatabaseError error) {

            }
        });
    }

    private void sendNotification_1() {
        NotificationCompat.Builder builder = new NotificationCompat.Builder(this, CHANNEL_ID)
                .setSmallIcon(R.drawable.logo)
                .setContentTitle("Cảnh báo")
                .setContentText("Nhiệt độ cao quá mức cài đặt")
                .setPriority(NotificationCompat.PRIORITY_DEFAULT)
                .setAutoCancel(true);

        // Tùy chỉnh thông báo bằng cách thêm các thuộc tính khác

        NotificationManagerCompat notificationManager = NotificationManagerCompat.from(this);
        notificationManager.notify(1, builder.build());

    }

    private void sendNotification_2() {
        NotificationCompat.Builder builder = new NotificationCompat.Builder(this, CHANNEL_ID)
                .setSmallIcon(R.drawable.logo)
                .setContentTitle("Cảnh báo")
                .setContentText("Nhiệt độ cao quá mức cài đặt")
                .setPriority(NotificationCompat.PRIORITY_DEFAULT)
                .setAutoCancel(true);

        // Tùy chỉnh thông báo bằng cách thêm các thuộc tính khác

        NotificationManagerCompat notificationManager = NotificationManagerCompat.from(this);
        notificationManager.notify(2, builder.build());

    }

    @Override
    public void onDestroy() {
        super.onDestroy();
    }

    @Override
    public IBinder onBind(Intent intent) {
        // TODO: Return the communication channel to the service.
        throw new UnsupportedOperationException("Not yet implemented");
    }


}