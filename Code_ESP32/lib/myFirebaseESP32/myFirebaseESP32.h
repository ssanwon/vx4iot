#ifndef myFirebaseESP32_h
#define myFirebaseESP32_h

#include <Arduino.h>
#include <FirebaseESP32.h>

class myFirebaseESP32
{
public:
    myFirebaseESP32();

    void init();
    void putInt(String path, int data);
    void putFloat(String path, float data);
    void putString(String path, String data);
    int readInt(String path);
    float readFloat(String path);
    String readString(String path);

private:
#define FIREBASE_HOST "https://dieu-khien-nhiet-do-dixell-default-rtdb.firebaseio.com/"
#define FIREBASE_AUTH "9xBA2JsMxk8yUzlBkHF39q2n0qmynDykaERBBWKq"
};
#endif