package com.example.app;

public class SettingData {
    public String temp, tempDelta1, time, tempAlarm, tempDelta2;

    public SettingData() {
    }

    public SettingData(String temp, String tempDelta1, String time, String tempAlarm, String tempDelta2) {
        this.temp = temp;
        this.tempDelta1 = tempDelta1;
        this.time = time;
        this.tempAlarm = tempAlarm;
        this.tempDelta2 = tempDelta2;
    }
}
