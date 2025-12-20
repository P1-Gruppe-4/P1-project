#include "menu.h"

// Function create_car with return type car, that prompts user to create a car
car create_car() {
    car newCar; // variable newCar of type car
    char handicap_input; // buffer to store "y" / "n"

    //Prompt user for how many hours they want to park
    printf("Enter stay duration hours: ");
    scanf("%lf", &newCar.duration_stay);

    //Prompt user for whether they need a handicap spot or not
    printf("Enter handicap, type y or n: ");
    scanf(" %c", &handicap_input);

    // Check if user wanted handicap spot or not, and set newCar.handicap to corresponding value
    if (tolower(handicap_input) == 'y') {
        newCar.handicap = 1;
    } else if (tolower(handicap_input) == 'n') {
        newCar.handicap = 0;
    } else {
        printf("Invalid input, defaulting handicap to no\n");
        newCar.handicap = 0;
    }

    //Prompt user whether they are guest, worker or VIP at the venue
    printf("Who is travelling in the car? 0 for Worker, 1 for VIP's, 2 for Guests ");
    //int temp to store users answer
    int temp;
    scanf("%d", &temp);

    //map user answer to corresponding value in role ENUM
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

    //Prompt user whether they have adults, family or elders in the car
    printf("If any, what passengers are in the car? 0 for Adult, 1 for Family, 2 for Elderly ");
    scanf("%d", &temp);
    //map answer to corresponding values in passenger ENUM
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

    //Prompt user whether they have a small, medium or big car
    printf("How big is your Car?: 0 for Small, 1 for Medium, 2 for Large\n");
    scanf("%d", &temp);

    //map user answer to corresponding value in size ENUM
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
        default:
            newCar.size = Small;
    }

    //prompt user for plate number
    printf("Enter the numberplate of your car like this: AC12842\n");
    scanf("%15s", newCar.number_plate);

    //return the users car
    return newCar;
}

//main_menu function that calls the other functions
void main_menu() {
    //variable for whether the app is done
    int done = 0;
    //variables for length and width of parkinglot
    int length_lot = 0, width_lot = 0;
    //while app is not done
    while (done == 0) {
        //prompt user about what to do in app
        printf(
            "Welcome to Lotimizer2D\n----------------------\nIf you want to create a new lot press 1\nIf you want to load from file press 2 \nIf you want to exit the program press 3\n  ");
        //save users answer in variabel input
        int input;
        scanf("%d", &input);

        //map input to functionality user chose
        switch (input) {
            //if user chose case 1, which is create new lot
            case 1: {
                //user is prompted for length and width of new lot, as long as the width and length he enters are not >=0
                int length, width;
                do {
                    printf("Enter length and width: ");
                    scanf("%d %d", &length, &width);
                } while (length <= 0 || width <= 0);

                //Parking lot is allocated dynamically using array_alloc function
                lot **parking_lot = array_alloc(length, width);
                // path_creator function is called, which creates path in the parking lot
                path_creator(parking_lot, length, width);
                // lot_assigner function is called, which assigns different spots ect. in parking lot
                parking_lot = lot_assigner(parking_lot, length, width);
                //lot_menu is called, which prompts user for further functionality
                lot_menu(parking_lot, length, width);
                //case breaks and user is returned to the start of while loop
                break;
            }
            //if user typed 2, user chose load parking lot
            case 2: {
                //user is prompted whether they want to load parkinglot from autosave, from a different file og go back to main menu
                printf(
                    "If you want to load from autosave press 1\nIf you want to load from a different file press 2, 3 to go back to main menu\n");
                //Users answer is stored in variabel load_choice, and string file_name is declared and auto_file is initialized
                int load_choice = 0;
                char auto_file[] = "autosave.txt";
                char file_name[100];
                scanf("%d", &load_choice);

                //maps user choice to corresponding logic
                switch (load_choice) {
                    //if user wants to load from autosave
                    case 1: {
                        //autosave file is opened and saved in file pointer auto_save_file
                        FILE *auto_save_file = fopen(auto_file, "r");

                        //if file pointer == NULL, function breaks and one is redirected to main menu again
                        if (auto_save_file == NULL) {
                            printf("ERROR! No auto saves found! Redirecting to the main menu.\n\n");
                            break;
                        }
                        //If it was not NULL, parking lot is loaded using load_save, and length and width are stored in length_lot and width_lot pointers
                        lot **parking_lot = load_save(auto_save_file, &length_lot, &width_lot);
                        //if parking_lot is not NULL, lot_menu is called, which prompts user for further functionality
                        if (parking_lot != NULL) {
                            lot_menu(parking_lot, length_lot, width_lot);
                        }
                        //case breaks and one is redirected back to menu
                        break;
                    }
                    case 2: {
                        //if user chose to load from a different file, user is prompted to enter filename
                        while (1) {
                            printf("Please enter file_name:\n");
                            //file name is stored in variable file_name
                            scanf("%99s", file_name);
                            //file is opened and stored in file pointer save_file
                            FILE *save_file = fopen(file_name, "r");

                            //if file pointeer is NULL, prompt user that it was invalid and that they should try again
                            if (save_file == NULL) {
                                printf("ERROR! Invalid input, try again:\n\n");
                                //else, load the parking lot and save in parking_lot variable
                            } else {
                                lot **parking_lot = load_save(save_file, &length_lot, &width_lot);
                                //if parking_lot is not NULL, lot_menu is called, which prompts user for further functionality
                                if (parking_lot != NULL) {
                                    lot_menu(parking_lot, length_lot, width_lot);
                                }
                                //break out of while
                                break;
                            }
                        }
                        //break case and redirect user back to main menu
                        break;
                    }
                    //if user typed 3 in this inner switch case, break and redirect user to main menu
                    case 3: {
                        break;
                    }
                    //Default case: input is invalid, and user is redirected
                    default: {
                        printf("ERROR! Invalid input, redirecting to the main menu.\n\n");
                    }
                }
                break;
            }
            //if case 3 in this outer switch case, variable done assigned 1, and program is done
            case 3: {
                done = 1;
                break;
            }
            //Default case: input is invalid, and user is redirected
            default: {
                printf("ERROR! Invalid input, redirecting to the main menu.\n\n");
            }
        }
    }
}

//Function lot menu, that has all functionality which can be done once user has either created or loaded a parkinglot
void lot_menu(lot **parking_lot, int length, int width) {
    //int variable to store user choice
    int choice = 0;
    //while user does not choose 6
    while (choice != 6) {
        //prompt them to choose
        printf(
            "Press 1 to add car \nPress 2 to find car\nPress 3 to delete car\nPress 4 to print parkinglot\nPress 5 to view occupancy of lot\nPress 6 to save & go back to menu\n");
        //save their choice in choice variable
        scanf("%d", &choice);

        //if user chooses to add car and parking_lot is not NULL
        if (choice == 1 && parking_lot != NULL) {
            //call add_cars function
            add_cars(parking_lot, length, width);
            //if user chooses 2, which is to find car
        } else if (choice == 2) {
            //create variables r and c to save row and column of cars location
            int r, c;
            //declare plate_number string to store plate number of car
            char plate_number[16];
            //prompt user to enter cars platen number and save it in plate_number string
            printf("Enter the plate number of the car you wanna find\n");
            scanf("%15s", plate_number);
            //call function find_car_by_numberplate using the parkinglot, it's width and length, the plate_number and r,c variables
            int result = find_car_by_numberplate(parking_lot, length, width, plate_number, &r, &c);
            //if result of function is 1, which means it found the car
            if (result == 1) {
                //print the car location
                printf("The car with the numberplate %s is found at row %d and column %d\n", plate_number, r, c);
            } else {
                //if it did not find the car, print that the car is not in the parkinglot
                printf("The car with the numberplate %s is not in the parkinglot\n", plate_number);
            }
            //if user chooses 3, which is to delete a car
        } else if (choice == 3) {
            //declare plate_number string to store plate number of car
            char plate_number[16];
            //prompt user to enter cars platen number and save it in plate_number string
            printf("Enter the plate number of the car you wanna delete\n");
            scanf("%15s", plate_number);
            //call function delete_car using the parkinglot, it's width and length, the plate_number
            int result = delete_car(parking_lot, length, width, plate_number);
            //if result of function is 1, which means it deleted the car
            if (result == 1) {
                //print that the car has left the parkinglot
                printf("The car with the numberplate %s has left the parkinglot\n", plate_number);
            } else {
                //if not deleted, print that it was never in the parkinglot in the first place
                printf("The car with the numberplate %s was not in the parkinglot in the first place\n", plate_number);
            }
            // if user chooses 4, print the parkinglot via array_print function
        } else if (choice == 4) {
            array_print(parking_lot, length, width);
            //if user chooses 5, calculate occupancy score and write in console via occupancy_lot
        } else if (choice == 5) {
            printf("%.1lf%% of the lot is free\n", occupancy_lot(parking_lot, length, width));
        }
            //if user chooses 6, save the parkinglot via auto_save function and free the dynamically allocated parkinglot
         else if (choice == 6) {
            auto_save(parking_lot, length, width);
            array_free(parking_lot, length);
            //end function via return
            return;
        }
    }
}

// Helper function to add cars to the loaded array
void add_cars(lot **parking_lot, int length, int width) {
    //intitialize char c as 'y', meaning that user wants to set cars into the lot
    char c = 'y';
    //while c is not 'n', keep prompting user whether they want to set cars into the lot
    while (tolower(c) != 'n') {
        printf("Do you wish to set cars into the lot? (y/n): \n");
        // save their answer in c
        scanf(" %c", &c);
        // if c is 'y'
        if (tolower(c) == 'y') {
            //create new car via create_car function
            car new_car = create_car();
            //map the new car to a spot in the parkinglot via map_to_lot
            map_to_lot(new_car, parking_lot, length, width);
        }
    }
}
