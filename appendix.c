#include "hashtables.h"
//SNAP
void populateSNAP(void) {
    insertSNAP(66252, "L. Adams", "55 Pear Ave.", 4559284);
    insertSNAP(1376, "R. Johnson", "88 Apple Dr.", 7175542);
    insertSNAP(39391, "O. Gonzalez", "62 Durian Blvd.", 6876203);
    insertSNAP(74533, "C. Johnson", "5 Raisin Ln.", 9924616);
    insertSNAP(58429, "O. Gonzalez", "78 Rhubarb Ave.", 1718839);
    insertSNAP(99730, "R. Johnson", "56 Kiwi Blvd.", 9039855);
}
//CSG
void populateCSG(void) {
    // Insert data into CSG table
    insertCSG("CSC171", 66252, "A");
    insertCSG("CSC171", 58429, "B");
    insertCSG("MATH150", 39391, "A");
    insertCSG("DSCC201", 66252, "C");
    insertCSG("DSCC201", 1376, "B+");
    insertCSG("CSC172", 99730, "A");
    insertCSG("MATH150", 58429, "C+");
    insertCSG("CSC173", 74533, "B+");
    insertCSG("CSC173", 99730, "A");
    insertCSG("DSCC201", 99730, "C");
}
//CP
void populateCP(void) {
    // Insert data into CP table
    insertCP("CSC172", "CSC171");
    insertCP("CSC172", "MATH150");
    insertCP("CSC173", "CSC172");
    insertCP("CSC252", "CSC172");
    insertCP("CSC254", "CSC252");
    insertCP("DSCC201", "CSC171");
    insertCP("DSCC202", "DSCC201");
    insertCP("DSCC265", "CSC262");
    insertCP("DSCC265", "CSC171");
}
//CDH
void populateCDH(void) {
    // Insert data into CDH table
    insertCDH("CSC171", "M", 1400);
    insertCDH("CSC171", "W", 1400);
    insertCDH("CSC172", "M", 1525);
    insertCDH("CSC172", "W", 1640);
    insertCDH("CSC173", "M", 1400);
    insertCDH("CSC173", "W", 1400);
    insertCDH("CSC252", "M", 1230);
    insertCDH("CSC252", "W", 1230);
    insertCDH("DSCC201", "T", 900);
    insertCDH("DSCC201", "R", 900);
    insertCDH("DSCC202", "T", 1650);
    insertCDH("DSCC202", "R", 1650);
    insertCDH("DSCC265", "T", 1400);
    insertCDH("DSCC265", "R", 1400);
}
//CR
void populateCR(void) {
    // Insert data into CR table
    insertCR("CSC171", "Hutchison Hall 141");
    insertCR("CSC172", "Hutchison Hall 141");
    insertCR("CSC173", "Wegmans 1400");
    insertCR("CSC252", "Wegmans 1400");
    insertCR("CSC254", "Wegmans 1400");
    insertCR("DSCC201", "Bausch & Lomb 109");
    insertCR("DSCC202", "Dewey 2162");
    insertCR("DSCC265", "Wegmans 1400");
    insertCR("MATH150", "Harkness 115");
}
