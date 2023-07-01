#include "myVX4.h"
#include <Arduino.h>

myVX4::myVX4()
{
    ;
}

// Cấu hình RS485
void myVX4::configVX4(int baudrate, int timeout)
{
    Serial2.begin(baudrate);
    Serial2.setTimeout(timeout);
}

// Tính toán giá trị CRC dựa trên dữ liệu
uint16_t myVX4::calculateCRC(uint8_t *data, uint8_t length)
{
    uint16_t crc = 0xFFFF; // Giá trị ban đầu của CRC

    for (uint8_t i = 0; i < length; i++)
    {
        crc ^= data[i]; // XOR byte dữ liệu với CRC hiện tại

        for (uint8_t j = 0; j < 8; j++)
        {
            if (crc & 0x0001)
            {
                crc >>= 1;
                crc ^= 0xA001; // Đa thức CRC-16
            }
            else
            {
                crc >>= 1;
            }
        }
    }
    return crc;
}

// Đọc nhiệt độ cài đặt (thanh ghi 103)
float myVX4::readSetPoint()
{
    // 02 03 00 67 00 01 35 E6
    uint8_t buf[] = {0x02, 0x03, 0x00, 0x67, 0x00, 0x01};
    int temp = 0;
    float temp_1 = 0;

    // Tính toán CRC
    uint16_t crc = calculateCRC(buf, 6);

    byte message[] = {0x02, 0x03, 0x00, 0x67, 0x00, 0x01, crc & 0xff, crc >> 8};
    Serial2.write(message, sizeof(message));

    int timeOut = 0;

    while (timeOut < 12)
    {
        delay(5);
        if (Serial2.available() > 0)
        {
            String rs485String = Serial2.readString();
            temp = (rs485String[3] * 256) + rs485String[4];

            if (temp > 1000)
            {
                temp = temp - 65536;
            }

            temp_1 = (float)temp / 10;
        }
        timeOut++;
    }
    return temp_1;
}

// Đọc độ lệch nhiệt độ cài đặt (thanh ghi 806)
float myVX4::readTempDelta1()
{
    // 02 03 03 26 00 01 65 B6
    uint8_t buf[] = {0x02, 0x03, 0x02, 0x26, 0x00, 0x01};
    int temp = 0;
    float temp_1 = 0;

    // Tính toán CRC
    uint16_t crc = calculateCRC(buf, 6);

    byte message[] = {0x02, 0x03, 0x02, 0x26, 0x00, 0x01, crc & 0xff, crc >> 8};
    Serial2.write(message, sizeof(message));

    int timeOut = 0;

    while (timeOut < 12)
    {
        delay(5);
        if (Serial2.available() > 0)
        {
            String rs485String = Serial2.readString();
            temp = (rs485String[3] * 256) + rs485String[4];

            if (temp > 1000)
            {
                temp = temp - 65536;
            }

            temp_1 = (float)temp / 10;
        }
        timeOut++;
    }
    return temp_1;
}

// Nhiệt độ cảnh báo (thanh ghi 301)
float myVX4::readTempAlarm()
{
    // 02 03 01 2D 00 01 15 CC
    uint8_t buf[] = {0x02, 0x03, 0x01, 0x2D, 0x00, 0x01};
    int temp = 0;
    float temp_1 = 0;

    // Tính toán CRC
    uint16_t crc = calculateCRC(buf, 6);

    byte message[] = {0x02, 0x03, 0x01, 0x2D, 0x00, 0x01, crc & 0xff, crc >> 8};
    Serial2.write(message, sizeof(message));

    int timeOut = 0;

    while (timeOut < 12)
    {
        delay(5);
        if (Serial2.available() > 0)
        {
            String rs485String = Serial2.readString();
            temp = (rs485String[3] * 256) + rs485String[4];

            if (temp > 1000)
            {
                temp = temp - 65536;
            }

            temp_1 = (float)temp / 10;
        }
        timeOut++;
    }
    return temp_1;
}

// Độ lệch nhiệt độ cảnh báo (thanh ghi 302)
float myVX4::readTempDelta2()
{
    // 02 03 01 2E 00 01 E5 FF
    uint8_t buf[] = {0x02, 0x03, 0x01, 0x2E, 0x00, 0x01};
    int temp = 0;
    float temp_1 = 0;

    // Tính toán CRC
    uint16_t crc = calculateCRC(buf, 6);

    byte message[] = {0x02, 0x03, 0x01, 0x2E, 0x00, 0x01, crc & 0xff, crc >> 8};
    Serial2.write(message, sizeof(message));

    int timeOut = 0;

    while (timeOut < 12)
    {
        delay(5);
        if (Serial2.available() > 0)
        {
            String rs485String = Serial2.readString();
            temp = (rs485String[3] * 256) + rs485String[4];

            if (temp > 1000)
            {
                temp = temp - 65536;
            }

            temp_1 = (float)temp / 10;
        }
        timeOut++;
    }
    return temp_1;
}

// Cài đặt nhiệt độ (thanh ghi 103)
void myVX4::controlSetPoint(int temp)
{
    // 02 06 00 67 00 00 38 26
    uint8_t buf[] = {0x02, 0x06, 0x00, 0x67, temp >> 8, temp & 0xff};
    uint16_t crc = calculateCRC(buf, 6);

    byte message[] = {0x02, 0x06, 0x00, 0x67, temp >> 8, temp & 0xff, crc & 0xff, crc >> 8};

    Serial2.write(message, sizeof(message));
    Serial.println("Cai dat thanh cong");
}

// Độ lệch nhiệt độ cài đặt (thanh ghi 806)
void myVX4::tempDelta1(int temp)
{
    // 02 06 03 26 00 00 68 76
    uint8_t buf[] = {0x02, 0x06, 0x03, 0x26, temp >> 8, temp & 0xff};
    uint16_t crc = calculateCRC(buf, 6);

    byte message[] = {0x02, 0x06, 0x03, 0x26, temp >> 8, temp & 0xff, crc & 0xff, crc >> 8};

    Serial2.write(message, sizeof(message));
    Serial.println("Cai dat thanh cong");
}

// Cài đặt nhiệt độ cảnh báo(thanh ghi 301)
void myVX4::tempAlarm(int temp)
{
    // 02 06 01 2D 00 00 18 0C
    uint8_t buf[] = {0x02, 0x06, 0x01, 0x2D, temp >> 8, temp & 0xff};
    uint16_t crc = calculateCRC(buf, 6);

    byte message[] = {0x02, 0x06, 0x01, 0x2D, temp >> 8, temp & 0xff, crc & 0xff, crc >> 8};

    Serial2.write(message, sizeof(message));
    Serial.println("Cai dat thanh cong");
}

// Độ lệch nhiệt độ cảnh báo (thanh ghi 302)
void myVX4::tempDelta2(int temp)
{
    // 02 06 01 2E 00 00 E8 0C
    uint8_t buf[] = {0x02, 0x06, 0x01, 0x2E, temp >> 8, temp & 0xff};
    uint16_t crc = calculateCRC(buf, 6);

    byte message[] = {0x02, 0x06, 0x01, 0x2E, temp >> 8, temp & 0xff, crc & 0xff, crc >> 8};

    Serial2.write(message, sizeof(message));
    Serial.println("Cai dat thanh cong");
}
