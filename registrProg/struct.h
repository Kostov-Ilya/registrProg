#pragma once
#pragma region const
#define nameBuffer 128
#define maxPerApt 10
#define startCap 10
#pragma endregion const

#pragma region struct
struct Resident {
    size_t id;
    char fullName[nameBuffer];
};

struct Apartment {
    size_t number;
    size_t floor;
    size_t roomsCount;
    size_t residentIds[maxPerApt];
    size_t residentCount;
};

struct ResidentList {
    Resident* data;
    size_t count;
    size_t capacity;
};

struct ApartmentList {
    Apartment* data;
    size_t count;
    size_t capacity;
};
#pragma endregion struct