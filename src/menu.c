#include <menu.h>


car create_car() {
    car newCar;
    char handicap_input; // buffer to store "y" / "n"

    printf("Enter stay duration hours: ");
    scanf("%lf", &newCar.duration_stay);

    printf("Enter handicap, type y or n: ");
    scanf(" %c", &handicap_input); // read string

    // Convert string to handicap value
    if (tolower(handicap_input) == 'y') {
        newCar.handicap = 1;
    } else if (tolower(handicap_input) == 'n') {
        newCar.handicap = 0;
    } else {
        printf("Invalid input, defaulting handicap to no\n");
        newCar.handicap = 0;
    }

    printf("Who is travelling in the car? 0 for Worker, 1 for VIP's, 2 for Guests ");
    int temp;
    scanf("%d", &temp);
    switch (temp) {
        case 0:
            newCar.role = Worker;
            break;
        case 1:
            newCar.role = VIP;
            break;
        case 2:
            newCar.role = Guest;
            break;
        default:
            newCar.role = Guest;
    }

    printf("If any, what passengers are in the car? 0 for Adult, 1 for Family, 2 for Elderly ");
    scanf("%d", &temp);
    switch (temp) {
        case 0:
            newCar.passenger = Adult;
            break;
        case 1:
            newCar.passenger = Family;
            break;
        case 2:
            newCar.passenger = Elderly;
            break;
        default:
            newCar.passenger = Adult;
    }

    printf("How big is your Car?: 0 for Small, 1 for Medium, 2 for Large, 3 for special\n");
    scanf("%d", &temp);
    switch (temp) {
        case 0:
            newCar.size = Small;
            break;
        case 1:
            newCar.size = Medium;
            break;
        case 2:
            newCar.size = Large;
            break;
        case 3:
            newCar.size = Special;
            break;
        default:
            newCar.size = Small;
    }
    printf("Enter the numberplate of your car like this: AC12842\n");
    scanf("%15s", newCar.number_plate);

    return newCar;
}

void main_menu() {
    int done = 0;
    int length_lot = 0, width_lot = 0;
    while (done == 0) {
        printf(
            "Welcome to Lotimizer2D\n----------------------\nIf you want to create a new lot press 1\nIf you want to load from file press 2 \nIf you want to exit the program press 3\n  ");
        int input;
        scanf("%d", &input);

        switch (input) {
            case 1: {
                int length, width;
                do {
                    printf("Enter length and width: ");
                    scanf("%d %d", &length, &width);
                } while (length <= 0 || width <= 0);

                lot **parking_lot = array_alloc(length, width);
                path_creator(parking_lot, length, width);
                parking_lot = lot_assigner(parking_lot, length, width);
                lot_menu(parking_lot, length, width);
                break;
            }

            case 2: {
                printf(
                    "If you want to load from autosave press 1\nIf you want to load from a different file press 2, 0 to go back to main menu\n");
                int load_choice = 0;
                char auto_file[] = "autosave.txt";
                char file_name[100];
                scanf("%d", &load_choice);

                switch (load_choice) {
                    case 1: {
                        FILE *auto_save_file = fopen(auto_file, "r");

                        if (auto_save_file == NULL) {
                            printf("ERROR! No auto saves found! Redirecting to the main menu.\n\n");
                            break;
                        }
                        lot **parking_lot = load_save(auto_save_file, &length_lot, &width_lot);
                        if (parking_lot != NULL) {
                            lot_menu(parking_lot, length_lot, width_lot);
                        }

                        break;
                    }
                    case 2: {
                        while (1) {
                            printf("Please enter file_name:\n");
                            scanf("%99s", file_name);
                            FILE *save_file = fopen(file_name, "r");

                            if (save_file == NULL) {
                                printf("ERROR! Invalid input, try again:\n\n");
                            } else {
                                lot **parking_lot = load_save(save_file, &length_lot, &width_lot);
                                if (parking_lot != NULL) {
                                    lot_menu(parking_lot, length_lot, width_lot);
                                }

                                break;
                            }
                        }
                        break;
                    }
                    case 0: {
                        break;
                    }
                    default: {
                        printf("ERROR! Invalid input, redirecting to the main menu.\n\n");
                    }
                }
                break;
            }
            case 3: {
                done = 1;
                break;
            }
            default: {
                printf("ERROR! Invalid input, redirecting to the main menu.\n\n");
            }
        }
    }
}

void lot_menu(lot **parking_lot, int length, int width) {
    int choice = 0;
    while (choice != 5) {
        printf(
            "Press 1 to add car \nPress 2 to find car\nPress 3 to delete car\nPress 4 to print parkinglot\nPress 5 to save & go back to menu\n");
        scanf("%d", &choice);

        if (choice == 1 && parking_lot != NULL) {
            add_cars(parking_lot, length, width);
        } else if (choice == 2) {
            int r, c;
            char plate_number[16];
            printf("Enter the plate number of the car you wanna find\n");
            scanf("%15s", plate_number);
            int result = find_car_by_numberplate(parking_lot, length, width, plate_number, &r, &c);
            if (result == 1) {
                printf("The car with the numberplate %s is found at row %d and column %d\n", plate_number, r, c);
            } else {
                printf("The car with the numberplate %s is not in the parkinglot\n", plate_number);
            }
        } else if (choice == 3) {
            char plate_number[16];
            printf("Enter the plate number of the car you wanna delete\n");
            scanf("%15s", plate_number);
            int result = delete_car(parking_lot, length, width, plate_number);
            if (result == 1) {
                printf("The car with the numberplate %s has left the parkinglot\n", plate_number);
            } else {
                printf("The car with the numberplate %s was not in the parkinglot in the first place\n", plate_number);
            }
        } else if (choice == 4) {
            array_print(parking_lot, length, width);
        } else if (choice == 5) {
            auto_save(parking_lot, length, width);
            array_free(parking_lot, length);
            return;
        }
    }
}

// Helper function to add cars to the loaded array
void add_cars(lot **parking_lot, int length, int width) {
    char c = 'y';
    while (tolower(c) != 'n') {
        printf("Do you wish to set cars into the lot? (y/n): \n");
        scanf(" %c", &c);
        if (tolower(c) == 'y') {
            car new_car = create_car();
            map_to_lot(new_car, parking_lot, length, width);
        }
    }
}
