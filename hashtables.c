#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "hashtables.h"
//Functions to check for wildcard values
bool wildcardOrMatch(const char *param, const char *value) {
    if (param == NULL || value == NULL) {
        return false;
    }
    if (strcmp(param, "*") == 0) {
        return true;
    }
    return strcmp(param, value) == 0;
}
bool intWildcardOrMatch(const char *param, int value) {
    if (param == NULL) {
        return false;
    }
    if (strcmp(param, "*") == 0) {
        return true;
    }
    return atoi(param) == value;
}
//SNAP
HashTable *SNAPTable;
char *createKeyForSNAP(int studentId) {
    char *key = malloc(20 * sizeof(char));
    sprintf(key, "%d", studentId);
    return key;
}
void insertSNAP(int StudentID, char *Name, char *Address, int Phone) {
    SNAP *newSNAP = malloc(sizeof(SNAP));
    if (newSNAP == NULL) {
        return;
    }
    newSNAP->StudentID = StudentID;
    newSNAP->Name = strdup(Name);
    newSNAP->Address = strdup(Address);
    newSNAP->Phone = Phone;
    char *key = createKeyForSNAP(StudentID);
    if (key == NULL) {
        free(newSNAP);
        return;
    }
    insertValue(SNAPTable, key, newSNAP);
    free(key);
}
void deleteSNAP(char *studentId, char *name, char *address, char *phone) {
    for (int i = 0; i < SNAPTable->size; i++) {
        Data *entry = SNAPTable->table[i];
        Data *prev = NULL;
        while (entry != NULL) {
            SNAP *snap = (SNAP *)entry->value;
            if (intWildcardOrMatch(studentId, snap->StudentID) &&
                wildcardOrMatch(name, snap->Name) &&
                wildcardOrMatch(address, snap->Address) &&
                intWildcardOrMatch(phone, snap->Phone)) {
                if (prev == NULL) {
                    SNAPTable->table[i] = entry->next;
                } else {
                    prev->next = entry->next;
                }
                free(snap->Name);
                free(snap->Address);
                free(snap);
            } else {
                prev = entry;
            }
            entry = entry->next;
        }
    }
}
void lookupSNAP(char *studentId, char *name, char *address, char *phone) {
    for (int i = 0; i < SNAPTable->size; i++) {
        Data *entry = SNAPTable->table[i];
        while (entry != NULL) {
            SNAP *snap = (SNAP *)entry->value;
            if (intWildcardOrMatch(studentId, snap->StudentID) &&
                wildcardOrMatch(name, snap->Name) &&
                wildcardOrMatch(address, snap->Address) &&
                intWildcardOrMatch(phone, snap->Phone)) {
                printf("Tuple found at key %s ", entry->key);
                printf("SNAP: Student ID: %d, Name: %s, Address: %s, Phone: %d\n", snap->StudentID, snap->Name, snap->Address, snap->Phone);
            }
            entry = entry->next;
        }
    }
}
void printSNAPTable(void) {
    printf("SNAP Table:\n");
    printf("%-15s%-15s%-20s%-15s\n", "StudentID", "Name", "Address", "Phone Number");
    for (int i = 0; i < SNAPTable->size; i++) {
        Data *entry = SNAPTable->table[i];
        while (entry != NULL) {
            SNAP *snap = (SNAP *)entry->value;
            printf("%-15d%-15s%-20s%-15d\n", snap->StudentID, snap->Name, snap->Address, snap->Phone);
            entry = entry->next;
        }
    }
}

//CSG
HashTable *CSGTable;
char *createKeyForCSG(char *course, int studentId) {
    char *key = malloc(50 * sizeof(char));
    sprintf(key, "%s_%d", course, studentId);
    return key;
}
void insertCSG(char *Course, int StudentID, char *Grade) {
    CSG *newCSG = malloc(sizeof(CSG));
    if (newCSG == NULL) {
        return;
    }
    newCSG->Course = strdup(Course);
    newCSG->StudentID = StudentID;
    newCSG->Grade = strdup(Grade);
    char *key = createKeyForCSG(Course, StudentID);
    if (key == NULL) {
        free(newCSG);
        return;
    }
    insertValue(CSGTable, key, newCSG);
    free(key);
}
void deleteCSG(char *course, char *studentId, char *grade) {
    for (int i = 0; i < CSGTable->size; i++) {
        Data *entry = CSGTable->table[i];
        Data *prev = NULL;
        while (entry != NULL) {
            CSG *csg = (CSG *)entry->value;
            if (wildcardOrMatch(course, csg->Course) &&
                intWildcardOrMatch(studentId, csg->StudentID) &&
                wildcardOrMatch(grade, csg->Grade)) {
                if (prev == NULL) {
                    CSGTable->table[i] = entry->next;
                } else {
                    prev->next = entry->next;
                }
                free(csg->Course);
                free(csg->Grade);
                free(csg);
                free(entry);
                entry = (prev == NULL) ? CSGTable->table[i] : prev->next;
            } else {
                prev = entry;
                entry = entry->next;
            }
        }
    }
}
void lookupCSG(char *course, char *studentId, char *grade) {
    for (int i = 0; i < CSGTable->size; i++) {
        Data *entry = CSGTable->table[i];
        while (entry != NULL) {
            CSG *csg = (CSG *)entry->value;
            if (wildcardOrMatch(course, csg->Course) &&
                intWildcardOrMatch(studentId, csg->StudentID) &&
                wildcardOrMatch(grade, csg->Grade)) {
                printf("Tuple found at key %s ", entry->key);
                printf("CSG: Course: %s, Student ID: %d, Grade: %s\n", csg->Course, csg->StudentID, csg->Grade);
            }
            entry = entry->next;
        }
    }
}
void printCSGTable(void) {
    printf("CSG Table:\n");
    printf("%-10s%-10s%-10s\n", "Course", "StudentID", "Grade");
    for (int i = 0; i < CSGTable->size; i++) {
        Data *entry = CSGTable->table[i];
        while (entry != NULL) {
            CSG *csg = (CSG *)entry->value;
            printf("%-10s%-10d%-10s\n", csg->Course, csg->StudentID, csg->Grade);
            entry = entry->next;
        }
    }
}
//CP
HashTable *CPTable;
char *createKeyForCP(char *course) {
    char *key = strdup(course);
    return key;
}
void insertCP(char *Course, char *Prereq) {
    CP *newCP = malloc(sizeof(CP));
    if (newCP == NULL) {
        return;
    }
    newCP->Course = strdup(Course);
    newCP->Prereq = strdup(Prereq);
    char *key = createKeyForCP(Course);
    if (key == NULL) {
        free(newCP);
        return;
    }
    insertValue(CPTable, key, newCP);
    free(key);
}
void deleteCP(char *course, char *prerequisite) {
    for (int i = 0; i < CPTable->size; i++) {
        Data *entry = CPTable->table[i];
        Data *prev = NULL;
        while (entry != NULL) {
            CP *cp = (CP *)entry->value;
            if (wildcardOrMatch(course, cp->Course) &&
                wildcardOrMatch(prerequisite, cp->Prereq)) {
                if (prev == NULL) {
                    CPTable->table[i] = entry->next;
                } else {
                    prev->next = entry->next;
                }
                free(cp->Course);
                free(cp->Prereq);
                free(cp);
                free(entry);
                entry = (prev == NULL) ? CPTable->table[i] : prev->next;
            } else {
                prev = entry;
                entry = entry->next;
            }
        }
    }
}
void lookupCP(char *course, char *prerequisite) {
    for (int i = 0; i < CPTable->size; i++) {
        Data *entry = CPTable->table[i];
        while (entry != NULL) {
            CP *cp = (CP *)entry->value;
            if (wildcardOrMatch(course, cp->Course) &&
                wildcardOrMatch(prerequisite, cp->Prereq)) {
                printf("Tuple found at key %s ", entry->key);
                printf("CP: Course: %s, Prerequisite: %s\n", cp->Course, cp->Prereq);
            }
            entry = entry->next;
        }
    }
}
void printCPTable(void) {
    printf("CP Table:\n");
    printf("%-10s%-10s\n", "Course", "Prerequisite");
    for (int i = 0; i < CPTable->size; i++) {
        Data *entry = CPTable->table[i];
        while (entry != NULL) {
            CP *cp = (CP *)entry->value;
            printf("%-10s%-10s\n", cp->Course, cp->Prereq);
            entry = entry->next;
        }
    }
}
//CDH
HashTable *CDHTable;
char *createKeyForCDH(char *course, char *day, int hour) {
    char *key = malloc(50 * sizeof(char));
    sprintf(key, "%s_%s_%d", course, day, hour);
    return key;
}
void insertCDH(char *Course, char *Day, int Hour) {
    CDH *newCDH = malloc(sizeof(CDH));
    if (newCDH == NULL) {
        return;
    }
    newCDH->Course = strdup(Course);
    newCDH->Day = strdup(Day);
    newCDH->Hour = Hour;
    char *key = createKeyForCDH(Course, Day, Hour);
    if (key == NULL) {
        free(newCDH);
        return;
    }
    insertValue(CDHTable, key, newCDH);
    free(key);
}
void deleteCDH(char *course, char *day, char *hour) {
    for (int i = 0; i < CDHTable->size; i++) {
        Data *entry = CDHTable->table[i];
        Data *prev = NULL;
        while (entry != NULL) {
            CDH *cdh = (CDH *)entry->value;
            if (wildcardOrMatch(course, cdh->Course) &&
                wildcardOrMatch(day, cdh->Day) &&
                intWildcardOrMatch(hour, cdh->Hour)) {
                if (prev == NULL) {
                   CDHTable->table[i] = entry->next;
                } else {
                    prev->next = entry->next;
                }
                free(cdh->Course);
                free(cdh->Day);
                free(cdh);
                free(entry);
                entry = (prev == NULL) ? CDHTable->table[i] : prev->next;
            } else {
                prev = entry;
                entry = entry->next;
            }
        }
    }
}
void lookupCDH(char *course, char *day, char *hour) {
    for (int i = 0; i < CDHTable->size; i++) {
        Data *entry = CDHTable->table[i];
        while (entry != NULL) {
            CDH *cdh = (CDH *)entry->value;
            if (wildcardOrMatch(course, cdh->Course) &&
                wildcardOrMatch(day, cdh->Day) &&
                intWildcardOrMatch(hour, cdh->Hour)) {
                printf("Tuple found at key %s ", entry->key);
                printf("CDH: Course: %s, Day: %s, Hour: %d\n", cdh->Course, cdh->Day, cdh->Hour);
            }
            entry = entry->next;
        }
    }
}
void printCDHTable(void) {
    printf("CDH Table:\n");
    printf("%-10s%-10s%-10s\n", "Course", "Day", "Hour");
    for (int i = 0; i < CDHTable->size; i++) {
        Data *entry = CDHTable->table[i];
        while (entry != NULL) {
            CDH *cdh = (CDH *)entry->value;
            printf("%-10s%-10s%-10d\n", cdh->Course, cdh->Day, cdh->Hour);
            entry = entry->next;
        }
    }
}
//CR
HashTable *CRTable;
char *createKeyForCR(char *course) {
    char *key = strdup(course);
    return key;
}
void insertCR(char *Course, char *Room) {
    CR *newCR = malloc(sizeof(CR));
    if (newCR == NULL) {
        return;
    }
    newCR->Course = strdup(Course);
    newCR->Room = strdup(Room);
    char *key = createKeyForCR(Course);
    if (key == NULL) {
        free(newCR);
        return;
    }
    insertValue(CRTable, key, newCR);
    free(key);
}
void deleteCR(char *course, char *room) {
    for (int i = 0; i < CRTable->size; i++) {
        Data *entry = CRTable->table[i];
        Data *prev = NULL;
        while (entry != NULL) {
            CR *cr = (CR *)entry->value;
            if (wildcardOrMatch(course, cr->Course) &&
                wildcardOrMatch(room, cr->Room)) {
                if (prev == NULL) {
                    CRTable->table[i] = entry->next;
                } else {
                    prev->next = entry->next;
                }
                free(cr->Course);
                free(cr->Room);
                free(cr);
                free(entry);
                entry = (prev == NULL) ? CRTable->table[i] : prev->next;
            } else {
                prev = entry;
                entry = entry->next;
            }
        }
    }
}
void lookupCR(char *course, char *room) {
    for (int i = 0; i < CPTable->size; i++) {
        Data *entry = CRTable->table[i];
        while (entry != NULL) {
            CR *cr = (CR *)entry->value;
            if (wildcardOrMatch(course, cr->Course) &&
                wildcardOrMatch(room, cr->Room)) {
                printf("Tuple found at key %s ", entry->key);
                printf("CR: Course: %s, Room: %s\n", cr->Course, cr->Room);
            }
            entry = entry->next;
        }
    }
}
void printCRTable(void) {
    printf("CR Table:\n");
    printf("%-10s%-10s\n", "Course", "Room");
    for (int i = 0; i < CRTable->size; i++) {
        Data *entry = CRTable->table[i];
        while (entry != NULL) {
            CR *cr = (CR *)entry->value;
            printf("%-10s%-10s\n", cr->Course, cr->Room);
            entry = entry->next;
        }
    }
}
//Part 2 Functions
//Name Grade Course
// Function to find the student ID for a given name in SNAPTable (1)
int findStudentID(char *studentName) {
    for (int i = 0; i < SNAPTable->size; i++) {
        Data *entry = SNAPTable->table[i];
        while (entry != NULL) {
            SNAP *snapData = (SNAP *)entry->value;
            if (strcmp(snapData->Name, studentName) == 0) {
                return snapData->StudentID;
            }
            entry = entry->next;
        }
    }
    return -1; // Return -1 if not found
}
// Function to find the grade for a given student ID and course in CSGTable (2)
char *findGrade(int studentID, char *courseName) {
    char key[100];
    sprintf(key, "%s_%d", courseName, studentID);
    CSG *csgData = (CSG *)lookupValue(CSGTable, key);
    return (csgData ? csgData->Grade : NULL);
}
// Function to print the grade for a given student and course (3)
void printGrade(char *studentName, char *courseName) {
    int studentID = findStudentID(studentName);
    if (studentID != -1) {
        char *grade = findGrade(studentID, courseName);
        printf("%s has a grade of %s in %s\n", studentName, (grade ? grade : "Not found"), courseName);
    } else {
        printf("Student %s not found\n", studentName);
    }
}
// Main function
void findGradeForStudentInCourse(char *studentName, char *courseName) {
    printGrade(studentName, courseName);
}
//StudentID Day Hour Room
void findStudentLocation(char *studentName, int hour, char *day) {
    for (int i = 0; i < SNAPTable->size; i++) {
        Data *entry = SNAPTable->table[i];
        while (entry != NULL) {
            SNAP *snapData = (SNAP *)entry->value;
            if (strcmp(snapData->Name, studentName) == 0) {
                for (int j = 0; j < CSGTable->size; j++) {
                    Data *csgEntry = CSGTable->table[j];
                    while (csgEntry != NULL) {
                        CSG *csgData = (CSG *)csgEntry->value;
                        if (csgData->StudentID == snapData->StudentID) {
                            char cdhKey[100];
                            sprintf(cdhKey, "%s_%s_%d", csgData->Course, day, hour);
                            CDH *cdhData = (CDH *)lookupValue(CDHTable, cdhKey);
                            CR *crData = (CR *)lookupValue(CRTable, csgData->Course);
                            if (cdhData && cdhData->Course && crData && crData->Room) {
                                printf("%s is in room %s at %d on %s\n", studentName, crData->Room, hour, day);
                                return;
                            }
                        }
                        csgEntry = csgEntry->next;
                    }
                }
            }
            entry = entry->next;
        }
    }
    printf("No location found for %s at %d on %s\n", studentName, hour, day);
}
//Part 3 Functions
//Selection by Name
void selectionSNAPByName(char *name, SelectedSNAP result[], int *resultSize) {
    int maxResultSize = 100;
    *resultSize = 0;
    for (int i = 0; i < SNAPTable->size; i++) {
        Data *entry = SNAPTable->table[i];
        while (entry != NULL && *resultSize < maxResultSize) {
            SNAP *snap = (SNAP *)entry->value;
            if (strcmp(snap->Name, name) == 0) {
                result[*resultSize] = (SelectedSNAP){
                        .studentId = snap->StudentID,
                        .phone = snap->Phone,
                };
                strcpy(result[*resultSize].name, snap->Name);
                strcpy(result[*resultSize].address, snap->Address);
                (*resultSize)++;
            }
            entry = entry->next;
        }
    }
}
//Projection from Course
void projectionCSGFromCourse(ProjectedCourse result[], int *resultSize) {
    int maxResultSize = 100;
    *resultSize = 0;
    for (int i = 0; i < CSGTable->size && *resultSize < maxResultSize; i++) {
        Data *entry = CSGTable->table[i];
        while (entry != NULL) {
            CSG *csg = (CSG *)entry->value;
            result[(*resultSize)++] = (ProjectedCourse){.course = csg->Course};
            entry = entry->next;
        }
    }
}
//Join SNAP and CSG
void joinSNAPAndCSG(SNAP_CSG_Join result[], int* resultSize) {
    int maxResultSize = 100;
    *resultSize = 0;
    for (int i = 0; i < SNAPTable->size && *resultSize < maxResultSize; i++) {
        Data *snapEntry = SNAPTable->table[i];
        while (snapEntry != NULL && *resultSize < maxResultSize) {
            SNAP *snap = (SNAP *)snapEntry->value;
            for (int j = 0; j < CSGTable->size && *resultSize < maxResultSize; j++) {
                Data *csgEntry = CSGTable->table[j];
                while (csgEntry != NULL && *resultSize < maxResultSize) {
                    CSG *csg = (CSG *)csgEntry->value;
                    if (snap->StudentID == csg->StudentID) {
                        SNAP_CSG_Join joinEntry = {
                                .studentId = snap->StudentID,
                                .name = strdup(snap->Name),
                                .address = strdup(snap->Address),
                                .phone = snap->Phone,
                                .course = strdup(csg->Course),
                                .grade = strdup(csg->Grade)
                        };
                        result[*resultSize] = joinEntry;
                        (*resultSize)++;
                    }
                    csgEntry = csgEntry->next;
                }
            }
            snapEntry = snapEntry->next;
        }
    }
}
void projectionFinalHelper(SNAP_CSG_Join joinedEntries[], int joinedSize, FinalResult finalResults[], int *finalResultSize) {
    *finalResultSize = 0;
    for (int i = 0; i < joinedSize; i++) {
        finalResults[*finalResultSize].studentId = joinedEntries[i].studentId;
        finalResults[*finalResultSize].course = strdup(joinedEntries[i].course);
        finalResults[*finalResultSize].grade = strdup(joinedEntries[i].grade);
        (*finalResultSize)++;
    }
}
void findAllGradesFromStudent(void) {
    //SNAP ▷◁ CSG
    SNAP_CSG_Join joinedEntries[100];
    int joinedSize = 0;
    joinSNAPAndCSG(joinedEntries, &joinedSize);
    //σName=“O. Gonzalez”(SNAP)
    SelectedSNAP selectedSNAPEntries[100];
    int selectedSNAPSize = 0;
    selectionSNAPByName("O. Gonzalez", selectedSNAPEntries, &selectedSNAPSize);
    //πStudentId,Course,Grade
    FinalResult finalResults[100];
    int finalResultSize = 0;
    projectionFinalHelper(joinedEntries, joinedSize, finalResults, &finalResultSize);
    //πStudentId,Course,Grade(σName=“O. Gonzalez”(SNAP ▷◁ CSG))
    for (int i = 0; i < finalResultSize; i++) {
        for (int j = 0; j < selectedSNAPSize; j++) {
            if (finalResults[i].studentId == selectedSNAPEntries[j].studentId) {
                printf("%-15d%-15s%-15s\n",
                       finalResults[i].studentId, finalResults[i].course, finalResults[i].grade);
            }
        }
    }
    // Free dynamically allocated memory
    for (int i = 0; i < finalResultSize; i++) {
        free(finalResults[i].course);
        free(finalResults[i].grade);
    }
    for (int i = 0; i < joinedSize; i++) {
        free(joinedEntries[i].name);
        free(joinedEntries[i].address);
        free(joinedEntries[i].course);
        free(joinedEntries[i].grade);
    }
}
//Free
void freeDatabase(void) {
    freeHashTable(SNAPTable);
    freeHashTable(CSGTable);
    freeHashTable(CPTable);
    freeHashTable(CDHTable);
    freeHashTable(CRTable);
}
//Initialize
void initializeDatabase(void) {
    SNAPTable = createNewHashTable(100);
    CSGTable = createNewHashTable(100);
    CPTable = createNewHashTable(100);
    CDHTable = createNewHashTable(100);
    CRTable = createNewHashTable(100);
}
