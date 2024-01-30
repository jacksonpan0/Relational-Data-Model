#include <stdio.h>
#include <stdlib.h>
#include "hashtables.h"
#include "appendix.h"
#include "repl.h"
int main(void) {
    //Part 1
    //Allot space for databases
    printf("Part 1\n");
    initializeDatabase();
    //Populate them
    populateSNAP();
    populateCSG();
    populateCP();
    populateCDH();
    populateCR();
    //Print all
    printSNAPTable();
    printf("\n");
    printCSGTable();
    printf("\n");
    printCPTable();
    printf("\n");
    printCDHTable();
    printf("\n");
    printCRTable();
    printf("\n");
    //Part 1 Example Operations
    //Perform operations as per the assignment
    printf("\nOperations Performed:\n");
    //(a)
    printf("Operation: Lookup(CSG - (DSCC201, 01376, B+))\n");
    lookupCSG("DSCC201", "01376", "B+");
    printf("\n");
    //(b)
    printf("Operation: Lookup(SNAP - (*, R. Johnson, *, *))\n");
    lookupSNAP("*", "R. Johnson", "*", "*");
    printSNAPTable();
    deleteSNAP("*", "R. Johnson", "*", "*");
    printSNAPTable();
    printf("\n");
    //(c)
    printf("Operation: Lookup(CP - (CSC252, CSC173))\n");
    lookupCP("CSC252", "CSC173");
    printf("\n");
    //(d)
    printf("Operation: Delete(CDH - (DSCC201, T, 900))\n");
    deleteCDH("DSCC201", "T", "900");
    printCDHTable();
    printf("\n");
    //(e)
    printf("Operation: Delete(CDH - (CSC171, T, *))\n");
    deleteCDH("CSC171", "T", "*");
    printCDHTable();
    printf("\n");
    //(f)
    printf("Operation: Delete(CDH - (CSC173, *, *))\n");
    deleteCDH("CSC173", "*", "*");
    printCDHTable();
    printf("\n");
    //(g)
    printf("Operation: Insert(CSG - (CSC252, 74533, A-))\n");
    insertCSG("CSC252", 74533, "A-");
    printCSGTable();
    printf("\n");
    //(h)
    printf("Operation: Insert(CSG - (DSCC201, 66252, C))\n");
    insertCSG("DSCC201", 66252, "C");
    printCSGTable();
    printf("\n");
    freeDatabase();
    //End of Part 1
    //
    //Part 2
    printf("Part 2");
    initializeDatabase();
    //Populate them
    populateSNAP();
    populateCSG();
    populateCP();
    populateCDH();
    populateCR();
    //Query Searching
    repl();
    // Part 3
    printf("\nPart 3\n");
    // 1. σName=“O. Gonzalez”(SNAP)
    SelectedSNAP selectionTuples[100];
    int selectionTuplesSize = 0;
    selectionSNAPByName("O. Gonzalez", selectionTuples, &selectionTuplesSize);
    printf("1. σName=“O. Gonzalez”(SNAP)\n");
    printf("Selection Results: \n");
    printf("SNAP Table: \n");
    printf("%-15s%-15s%-20s%-15s\n", "StudentID", "Name", "Address", "Phone Number");
    for (int i = 0; i < selectionTuplesSize; i++) {
        printf("%-15d%-15s%-20s%-15d\n", selectionTuples[i].studentId, selectionTuples[i].name, selectionTuples[i].address, selectionTuples[i].phone);
    }
    printf("\n");
    // 2. πCourse(CSG)
    ProjectedCourse projectionTuples[100];
    int projectionTuplesSize = 0;
    projectionCSGFromCourse(projectionTuples, &projectionTuplesSize);
    printf("2. πCourse(CSG)\n");
    printf("Projection Results: \n");
    printf("CSG Table: \n");
    for (int i = 0; i < projectionTuplesSize; i++) {
        printf("%-15s\n", projectionTuples[i].course);
    }
    printf("\n");
    // 3. SNAP ▷◁ CSG
    SNAP_CSG_Join joinResults[100];
    int joinResultsSize = 0;
    joinSNAPAndCSG(joinResults, &joinResultsSize);
    printf("3. SNAP ▷◁ CSG\n");
    printf("Join Results: \n");
    printf("SNAP ⨝ CSG Table: \n");
    printf("%-15s%-15s%-20s%-15s%-15s%-15s\n", "StudentID", "Name", "Address", "Phone Number", "Course", "Grade");
    for (int i = 0; i < joinResultsSize; i++) {
        printf("%-15d%-15s%-20s%-15d%-15s%-15s\n",
               joinResults[i].studentId, joinResults[i].name, joinResults[i].address,
               joinResults[i].phone, joinResults[i].course, joinResults[i].grade);
        // Free the duplicated strings
        free(joinResults[i].name);
        free(joinResults[i].address);
        free(joinResults[i].course);
        free(joinResults[i].grade);
    }
    printf("\n");
    // 4. πStudentId,Course,Grade(σName=“O. Gonzalez”(SNAP ▷◁ CSG))
    printf("4.\n");
    printf("Projection Selection Join Results: \n");
    printf("Table: \n");
    printf("%-15s%-15s%-15s\n", "StudentID", "Course", "Grade");
    findAllGradesFromStudent();
    freeDatabase();
    return 0;
}
