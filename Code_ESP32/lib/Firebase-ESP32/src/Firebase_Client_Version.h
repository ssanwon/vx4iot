#ifndef FIREBASE_CLIENT_VERSION
#define FIREBASE_CLIENT_VERSION "4.3.11"
#define FIREBASE_CLIENT_VERSION_NUM 40311

/* The inconsistent file version checking to prevent mixed versions compilation. */
#define FIREBASE_CLIENT_VERSION_CHECK(ver) (ver == FIREBASE_CLIENT_VERSION_NUM)
#endif