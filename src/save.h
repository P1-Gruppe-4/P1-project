//
// Created by matei on 15/12/2025.
//

#ifndef P1_GRUPPE4_SAVE_H
#define P1_GRUPPE4_SAVE_H

void auto_save(lot **pointer, int length, int width);
lot **load_save(FILE *save_file, int *length, int *width);

#endif //P1_GRUPPE4_SAVE_H