#include <CmsmRfid.h>
#include <CmsmVisitor.h>
/*
 * RFID constants and objects
 */
const int MAX_VISITORS = 2;

extern CmsmRfid Rfid;
extern CmsmVisitor* Visitors;

bool checkVisitor(String RfidTag);

void showNextPosition();
