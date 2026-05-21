#pragma once
#pragma region const
#define nameBuffer 128
#define maxPerApt 10
#define startCap 10
#pragma endregion const

#pragma region struct
struct Resident {
    int id;
    char fullName[nameBuffer];
};

struct Apartment {
    int number;
    int floor;
    int roomsCount;
    int residentIds[maxPerApt];
    int residentCount;
};

struct ResidentList {
    Resident* data;
    int count;
    int capacity;
};

struct ApartmentList {
    Apartment* data;
    int count;
    int capacity;
};
#pragma endregion struct