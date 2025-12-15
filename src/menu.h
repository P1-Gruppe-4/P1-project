//
// Created by matei on 15/12/2025.
//

#ifndef P1_GRUPPE4_MENU_H
#define P1_GRUPPE4_MENU_H

#include <stdio.h>
#include <ctype.h>
#include "types.h"
#include "save.h"
#include "arrays.h"
#include "parking_lot.h"
#include "map_to_lot.h"
#include "delete.h"
#include "find.h"

void main_menu();
void lot_menu(lot **parking_lot, int length, int width) ;
void add_cars(lot **parking_lot, int length, int width);

#endif //P1_GRUPPE4_MENU_H