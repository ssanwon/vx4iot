package com.example.app;

public class CurrentData {
    public int status;
    public String time, time1;
    public int temp;
    public String unit;

    public CurrentData() {
    }

    public CurrentData(int status, String time,String time1, int temp, String unit) {
        this.status = status;
        this.time = time;
        this.time1 = time1;
        this.temp = temp;
        this.unit = unit;
    }
}
