#define _CRT_SECURE_NO_WARNINGS
#include "includes.h"
#include "struct.h"
#include "prototypes.h"
#include "fileManager.h"

#pragma region fileFunctions
void saveToFiles(const ResidentList& resList, const ApartmentList& aptList) {
    FILE* fRes = nullptr;
    if (fopen_s(&fRes, "residents.txt", "w") == 0 && fRes != nullptr) {
        fprintf_s(fRes, "%llu\n", resList.count);
        for (size_t i = 0; i < resList.count; i++) {
            fprintf_s(fRes, "%llu;%s\n", resList.data[i].id, resList.data[i].fullName);
        }
        fclose(fRes);
    }
    else {
        printf("[!] Ошибка: Не удалось сохранить жильцов!\n");
    }
    FILE* fApt = nullptr;
    if (fopen_s(&fApt, "apartments.txt", "w") == 0 && fApt != nullptr) {
        fprintf_s(fApt, "%llu\n", aptList.count);
        for (size_t i = 0; i < aptList.count; i++) {
            fprintf_s(fApt, "%llu %llu %llu %llu\n",
                aptList.data[i].number,
                aptList.data[i].floor,
                aptList.data[i].roomsCount,
                aptList.data[i].residentCount);

            for (size_t j = 0; j < aptList.data[i].residentCount; j++) {
                fprintf_s(fApt, "%llu ", aptList.data[i].residentIds[j]);
            }
            fprintf_s(fApt, "\n");
        }
        fclose(fApt);
    }
    else {
        printf("[!] Ошибка: Не удалось сохранить квартиры!\n");
    }
}

void loadFromFiles(ResidentList& resList, ApartmentList& aptList) {
    FILE* fRes = nullptr;
    if (fopen_s(&fRes, "residents.txt", "r") == 0 && fRes != nullptr) {
        if (fscanf_s(fRes, "%llu\n", &resList.count) == 1) {
            if (resList.count > resList.capacity) {
                delete[] resList.data;
                resList.data = new Resident[resList.count];
                resList.capacity = resList.count;
            }
            for (size_t i = 0; i < resList.count; i++) {
                fscanf_s(fRes, "%llu;", &resList.data[i].id);
                size_t j = 0;
                char ch;
                while (fscanf_s(fRes, "%c", &ch, 1) == 1 && ch != '\n' && j < nameBuffer - 1) {
                    resList.data[i].fullName[j++] = ch;
                }
                resList.data[i].fullName[j] = '\0';
            }
        }
        fclose(fRes);
    }
    FILE* fApt = nullptr;
    if (fopen_s(&fApt, "apartments.txt", "r") == 0 && fApt != nullptr) {
        if (fscanf_s(fApt, "%llu\n", &aptList.count) == 1) {
            if (aptList.count > aptList.capacity) {
                delete[] aptList.data;
                aptList.data = new Apartment[aptList.count];
                aptList.capacity = aptList.count;
            }
            for (size_t i = 0; i < aptList.count; i++) {
                fscanf_s(fApt, "%llu %llu %llu %llu\n",
                    &aptList.data[i].number,
                    &aptList.data[i].floor,
                    &aptList.data[i].roomsCount,
                    &aptList.data[i].residentCount);

                for (size_t j = 0; j < aptList.data[i].residentCount; j++) {
                    fscanf_s(fApt, "%llu", &aptList.data[i].residentIds[j]);
                }
            }
        }
        fclose(fApt);
    }
}
#pragma endregion fileFunctions