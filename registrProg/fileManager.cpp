#define _CRT_SECURE_NO_WARNINGS
#pragma region files
#include "includes.h"
#include "struct.h"
#include "prototypes.h"
#include "fileManager.h"
#pragma endregion files

typedef unsigned int unInt;

#pragma region saveAndLoadOper
void saveToFiles(const ResidentList& resList, const ApartmentList& aptList) {
    FILE* fRes = nullptr;
    if (fopen_s(&fRes, "residents.txt", "w") == 0 && fRes != nullptr) {
        fprintf_s(fRes, "%d\n", resList.count);
        for (int i = 0; i < resList.count; i++) {
            fprintf_s(fRes, "%d;%s\n", resList.data[i].id, resList.data[i].fullName);
        }
        fclose(fRes);
    }
    else {
        printf("[!] Ошибка: Не удалось сохранить жильцов!\n");
    }
    FILE* fApt = nullptr;
    if (fopen_s(&fApt, "apartments.txt", "w") == 0 && fApt != nullptr) {
        fprintf_s(fApt, "%d\n", aptList.count);
        for (int i = 0; i < aptList.count; i++) {
            fprintf_s(fApt, "%d %d %d\n", aptList.data[i].number, aptList.data[i].floor, aptList.data[i].roomsCount);
            for (int j = 0; j < aptList.data[i].residentCount; j++) {
                fprintf_s(fApt, "%d ", aptList.data[i].residentIds[j]);
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
    char buffer[512];
    FILE* fRes = nullptr;
    if (fopen_s(&fRes, "residents.txt", "r") == 0 && fRes != nullptr) {
        if (fgets(buffer, sizeof(buffer), fRes) != nullptr) {
            sscanf_s(buffer, "%d", &resList.count);
        }
        if (resList.count > resList.capacity) {
            delete[] resList.data;
            resList.data = new Resident[resList.count];
            resList.capacity = resList.count;
        }
        for (int i = 0; i < resList.count; i++) {
            if (fgets(buffer, sizeof(buffer), fRes) != nullptr) {
                sscanf_s(buffer, "%d; %[^\n]", &resList.data[i].id,
                    resList.data[i].fullName, (unInt)sizeof(resList.data[i].fullName));
            }
        }
        fclose(fRes);
    }
    FILE* fApt = nullptr;
    if (fopen_s(&fApt, "apartments.txt", "r") == 0 && fApt != nullptr) {
        if (fgets(buffer, sizeof(buffer), fApt) != nullptr) {
            sscanf_s(buffer, "%d", &aptList.count);
        }
        if (aptList.count > aptList.capacity) {
            delete[] aptList.data;
            aptList.data = new Apartment[aptList.count];
            aptList.capacity = aptList.count;
        }
        for (int i = 0; i < aptList.count; i++) {
            bool gotApt = false;
            while (fgets(buffer, sizeof(buffer), fApt) != nullptr) {
                if (buffer[0] != '\n' && buffer[0] != '\r') {
                    sscanf_s(buffer, "%d %d %d",
                        &aptList.data[i].number,
                        &aptList.data[i].floor,
                        &aptList.data[i].roomsCount);
                    gotApt = true;
                    break;
                }
            }
            if (!gotApt) {
                break;
            }
            aptList.data[i].residentCount = 0;
            if (fgets(buffer, sizeof(buffer), fApt) != nullptr) {
                char* token = nullptr;
                char* nextToken = nullptr;
                token = strtok_s(buffer, " \n\r", &nextToken);
                while (token != nullptr && aptList.data[i].residentCount < maxPerApt) {
                    int id = atoi(token);
                    if (id > 0) {
                        aptList.data[i].residentIds[aptList.data[i].residentCount] = id;
                        aptList.data[i].residentCount++;
                    }
                    token = strtok_s(nullptr, " \n\r", &nextToken);
                }
            }
        }
        fclose(fApt);
    }
}
#pragma endregion saveAndLoadOper