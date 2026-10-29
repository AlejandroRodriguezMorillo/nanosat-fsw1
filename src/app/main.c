
#include <stdio.h>
#include "version.h"

int main(void) {

    printf("=== %s, v%s ===\n", MISSION_NAME, SW_VERSION);
    printf("FSM state: %s \n", "BOOT");

    return 0;
}