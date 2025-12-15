#include "save.h"

/*This function extracts the current parking-lot data and writes it into an autosave.txt file
 *Doing this ensure that there is always at least one fallback save for the user.
 *This function additionally creates an autosave-file if there is none yet. Do not, that the autosave file
 *ONLY contains the latest save, not multiple saves.
 */
void auto_save(lot **parking_lot, int length, int width) {
    //File pointer to autosave that opens autosave.txt in write mode
    FILE *auto_save = fopen("autosave.txt", "w");
    // Check if file auto_save opens
    if (!auto_save) {
        printf("ERROR: Could not open file autosave.txt for writing\n");
        return;
    }
    // Save length and width of the array
    fprintf(auto_save, "%d %d\n", length, width);
    //writes every individual array-cell into autosave.txt
    for (int i = 0; i < length; i++) {
        for (int j = 0; j < width; j++) {
            //Writes the status of the lot, whether it is handicapped and whether it has a car into autosave.txt
            fprintf(auto_save,
                    "%d %d %lf %d %d %d %lf %lf %d %d %d %d",
                    parking_lot[i][j].status,
                    parking_lot[i][j].is_handicap_spot,
                    parking_lot[i][j].max_duration,
                    parking_lot[i][j].max_size,
                    parking_lot[i][j].preferred_passenger,
                    parking_lot[i][j].allowed_role,
                    parking_lot[i][j].spot_width,
                    parking_lot[i][j].spot_length,
                    parking_lot[i][j].has_car,
                    parking_lot[i][j].distance,
                    parking_lot[i][j].row,
                    parking_lot[i][j].col
            );
            //If it has a car, the car is also saved
            if (parking_lot[i][j].has_car == 1) {
                fprintf(auto_save, " %lf %d %d %d %d %s", parking_lot[i][j].current_car.duration_stay,
                        parking_lot[i][j].current_car.handicap, parking_lot[i][j].current_car.passenger,
                        parking_lot[i][j].current_car.role, parking_lot[i][j].current_car.size, parking_lot[i][j].current_car.number_plate);
            }
            fprintf(auto_save, "\n");
        }
    }
    fclose(auto_save);
    printf("Save completed, saved to %s\n", "autosave.txt"); //debug
}

//This function extracts saved data in the correct format from the provided save_file
lot **load_save(FILE *save_file, int *length, int *width) {
    int length_arr, width_arr;
    fscanf(save_file, "%d %d", &length_arr, &width_arr);
    *length = length_arr;
    *width = width_arr;

    lot **parking_lot = array_alloc(length_arr, width_arr);
    for (int i = 0; i < length_arr; i++) {
        for (int j = 0; j < width_arr; j++) {
            fscanf(save_file,
                     "%d %d %lf %d %d %d %lf %lf %d %d %d %d",
                     &parking_lot[i][j].status,
                     &parking_lot[i][j].is_handicap_spot,
                     &parking_lot[i][j].max_duration,
                     &parking_lot[i][j].max_size,
                     &parking_lot[i][j].preferred_passenger,
                     &parking_lot[i][j].allowed_role,
                     &parking_lot[i][j].spot_width,
                     &parking_lot[i][j].spot_length,
                     &parking_lot[i][j].has_car,
                     &parking_lot[i][j].distance,
                     &parking_lot[i][j].row,
                     &parking_lot[i][j].col
             );
            if (parking_lot[i][j].has_car == 1) {
                fscanf(save_file, " %lf %d %d %d %d %s", &parking_lot[i][j].current_car.duration_stay,
                       &parking_lot[i][j].current_car.handicap, &parking_lot[i][j].current_car.passenger,
                       &parking_lot[i][j].current_car.role, &parking_lot[i][j].current_car.size, parking_lot[i][j].current_car.number_plate);
            }
        }
    }
    fclose(save_file);
    array_print(parking_lot, length_arr, width_arr);
    return parking_lot;
}