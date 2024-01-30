#ifndef hashtables_h
#define hashtables_h
#include "databasefunc.h"
typedef struct {
    int StudentID;
    char *Name;
    char *Address;
    int Phone;
} SNAP;
typedef struct {
    char *Course;
    int StudentID;
    char *Grade;
} CSG;
typedef struct {
    char *Course;
    char *Prereq;
} CP;
typedef struct {
    char *Course;
    char *Day;
    int Hour;
} CDH;
typedef struct {
    char *Course;
    char *Room;
} CR;
//Initialize
void initializeDatabase(void);
//SNAP
void insertSNAP(int studentId, char *name, char *address, int phone);
void deleteSNAP(char *studentId, char *name, char *address, char *phone);
void lookupSNAP(char *studentId, char *name, char *address, char *phone);
void printSNAPTable(void);
//CSG
void insertCSG(char *course, int studentId, char *grade);
void deleteCSG(char *course, char *studentId, char *grade);
void lookupCSG(char *course, char *studentId, char *grade);
void printCSGTable(void);
//CP
void insertCP(char *course, char *prerequisite);
void deleteCP(char *course, char *prerequisite);
void lookupCP(char *course, char *prerequisite);
void printCPTable(void);
//CDH
void insertCDH(char *course, char *day, int hour);
void deleteCDH(char *course, char *day, char *hour);
void lookupCDH(char *course, char *day, char *hour);
void printCDHTable(void);
//CR
void insertCR(char *course, char *room);
void deleteCR(char *course, char *room);
void lookupCR(char *course, char *room);
void printCRTable(void);
//Part 2
void findGradeForStudentInCourse(char *studentName, char *courseName);
void findStudentLocation(char *studentName, int hour, char *day);
//Free
void freeDatabase(void);
//Part 3
typedef struct {
    int studentId;
    char name[100];  // Assuming a fixed size for simplicity
    char address[100];
    int phone;
} SelectedSNAP;
typedef struct {
    char *course;
} ProjectedCourse;
typedef struct {
    int studentId;
    char *name;
    char *address;
    int phone;
    char *course;
    char *grade;
} SNAP_CSG_Join;
typedef struct {
    int studentId;
    char *course;
    char *grade;
} FinalResult;
void selectionSNAPByName(char *name, SelectedSNAP result[], int *resultSize);
void projectionCSGFromCourse(ProjectedCourse result[], int *resultSize);
void joinSNAPAndCSG(SNAP_CSG_Join result[], int *resultSize);
void projectionFinalHelper(SNAP_CSG_Join joinedEntries[], int joinedSize, FinalResult finalResults[], int *finalResultSize);
void findAllGradesFromStudent(void);
#endif
