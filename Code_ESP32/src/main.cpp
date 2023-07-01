#include <Arduino.h>
#include <myVX4.h>
#include <myNTP.h>
#include <myFirebaseESP32.h>
#include <string.h>

myVX4 mVX4;
myNTP mNTP;
myFirebaseESP32 mFirebaseESP32;

unsigned long previousMillis1 = 0; // Biến lưu trữ thời gian trước đó cho hàm 1
unsigned long previousMillis2 = 0; // Biến lưu trữ thời gian trước đó cho hàm 2
unsigned long previousMillis3 = 0; // Biến lưu trữ thời gian trước đó cho hàm 3
unsigned long interval1 = 1000;    // Thời gian giữa hai lần gọi hàm 1 (1 giây)
unsigned long interval2 = 5000;    // Thời gian giữa hai lần gọi hàm 2 (0.5 giây)
unsigned long interval3 = 1000;    // Thời gian giữa hai lần gọi hàm 3 (3 giây)

void setup()
{
    // Khởi tạo các thiết lập và cấu hình
    Serial.begin(9600);

    mVX4.configVX4(9600, 35);
    mNTP.initNTP();
    mFirebaseESP32.init();

    Serial.println("Cau hinh thanh cong");
}

void loop()
{
    // Đọc nhiệt độ và cập nhật theo chu kì cài đặt
    if (millis() - previousMillis1 >= interval1)
    {
        previousMillis1 = millis(); // Cập nhật thời gian trước đó

        Serial.println("Task 1 is running");
        mFirebaseESP32.putFloat("Current/temp", mVX4.readSetPoint());
        delay(500);
        mFirebaseESP32.putString("Current/time", mNTP.getTime());
    }

    // Gửi các giá trị cài đặt của đồng hồ lên firebase
    if (millis() - previousMillis2 >= interval2)
    {
        previousMillis2 = millis(); // Cập nhật thời gian trước đó

        // Thực hiện các hoạt động cho hàm 2 ở đây
        Serial.println("Task 2 is running");
        mFirebaseESP32.putString("Setiing/temp", (String)mVX4.readSetPoint());
        mFirebaseESP32.putString("Setiing/tempDelta1", (String)mVX4.readTempDelta1());
        mFirebaseESP32.putString("Setiing/tempAlarm", (String)mVX4.readTempAlarm());
        mFirebaseESP32.putString("Setiing/tempDelta2", (String)mVX4.readTempDelta2());
    }

    // Đọc các giá trị từ firebase về và cài đặt đồng hồ
    if (millis() - previousMillis3 >= interval3)
    {
        previousMillis3 = millis(); // Cập nhật thời gian trước đó

        Serial.println("Task 3 is running");
        mVX4.controlSetPoint((int)mFirebaseESP32.readString("Setting/temp").toInt());
        mVX4.tempDelta1((int)mFirebaseESP32.readString("Setting/tempDelta1").toInt());
        mVX4.tempAlarm((int)mFirebaseESP32.readString("Setting/tempAlarm").toInt());
        mVX4.tempDelta2((int)mFirebaseESP32.readString("Setting/tempDelta2").toInt());

        interval1 = (mFirebaseESP32.readString("Setting/time").toInt()) * 60000;
    }
}
