#include <iostream>
#include <string>
#include <cstdlib>
#include <limits>
#include <stdexcept>

using namespace std;

const int MAX_ITEMS = 100;

// Inventory variables
int itemIds[MAX_ITEMS];
string itemNames[MAX_ITEMS];
int itemQuantities[MAX_ITEMS];
double itemPrices[MAX_ITEMS];
int itemCount = 0;

// User cart variables
int userCartIds[MAX_ITEMS];
string userCartNames[MAX_ITEMS];
int userCartQuantities[MAX_ITEMS];
double userCartPrices[MAX_ITEMS];
int userCartCount = 0;

double totalBill = 0;

void getInput(int &value, const string &prompt) {    //to handle int
    while (true) {
        cout << prompt;
        cin >> value;

        if (cin) {
            break;
        }

        cout << "Invalid input! Please enter a valid integer.\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

void getInput(double &value, const string &prompt) {   //to handle double
    while (true) {
        cout << prompt;
        cin >> value;

        if (cin) {
            break;
        }

        cout << "Invalid input! Please enter a valid number.\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

void getInput(string &value, const string &prompt) {   //to handle string
    while (true) {
        cout << prompt;
        cin >> value;

        if (cin) {
            break;
        }

        cout << "Invalid input! Please enter a valid string.\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}


// Function declarations
void displayAdminMenu();
void displayUserMenu();

void displayAllDetails();
void insertItem();
void editItem();
void deleteItem();
void deleteAllItems();

void displayItemsMenu();
void selectItems();
void displayBill();
void lastRecord();
void helpCenter();
void ratings();

int main() {
    int choice;

    while (true) {
        try {
            system("cls");
            cout << "\n--- Honda Bike Workshop and Inventory System ---\n";
            cout << "1. Admin\n";
            cout << "2. User\n";
            cout << "3. Exit\n";

            getInput(choice, "Enter your choice: ");

            switch (choice) {
                case 1:
                    displayAdminMenu();
                    break;
                case 2:
                    displayUserMenu();
                    break;
                case 3:
                    cout << "Exiting the system. Goodbye!\n";
                    return 0;
                default:
                    cout << "Invalid choice! Please try again.\n";
                    system("pause");
            }
        } catch (const exception &e) {
            cout << "An error occurred: " << e.what() << "\n";
            system("pause");
        }
    }
}

void displayAdminMenu() {
    int choice;

    while (true) {
        try {
            system("cls");
            cout << "\n--- Admin Menu ---\n";
            cout << "1. Display All Details\n";
            cout << "2. Insert Item\n";
            cout << "3. Edit Item\n";
            cout << "4. Delete Item\n";
            cout << "5. Delete All Items\n";
            cout << "6. Back to Main Menu\n";

            getInput(choice, "Enter your choice: ");

            switch (choice) {
                case 1:
                    displayAllDetails();
                    system("pause");
                    break;
                case 2:
                    insertItem();
                    system("pause");
                    break;
                case 3:
                    editItem();
                    system("pause");
                    break;
                case 4:
                    displayAllDetails();
                    deleteItem();
                    system("pause");
                    break;
                case 5:
                    deleteAllItems();
                    system("pause");
                    break;
                case 6:
                    return;
                default:
                    cout << "Invalid choice! Please try again.\n";
                    system("pause");
            }
        } catch (const exception &e) {
            cout << "An error occurred: " << e.what() << "\n";
            system("pause");
        }
    }
}

void displayAllDetails() {
    try {
        if (itemCount == 0) {
            cout << "No items in the inventory.\n";
            return;
        }

        cout << "\n--- Inventory Details ---\n";
        for (int i = 0; i < itemCount; i++) {
            cout << "ID: " << itemIds[i]
                 << ", Name: " << itemNames[i]
                 << ", Quantity: " << itemQuantities[i]
                 << ", Price: " << itemPrices[i] << "\n";
        }
    } catch (const exception &e) {
        cout << "An error occurred: " << e.what() << "\n";
    }
}

void insertItem() {
    try {
        if (itemCount >= MAX_ITEMS) {
            cout << "Inventory is full!\n";
            return;
        }

        getInput(itemIds[itemCount], "Enter Item ID: ");

        // Check for duplicate ID
        for (int i = 0; i < itemCount; i++) {
            if (itemIds[i] == itemIds[itemCount]) {
                throw invalid_argument("Duplicate ID detected! IDs must be unique.");
            }
        }

        cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear buffer before reading name
        cout << "Enter Item Name: ";
        getline(cin, itemNames[itemCount]);  // Use getline to read names with spaces

        getInput(itemQuantities[itemCount], "Enter Item Quantity: ");
        getInput(itemPrices[itemCount], "Enter Item Price: ");

        itemCount++;
        cout << "Item inserted successfully!\n";
    } catch (const invalid_argument &e) {
        cout << "Error: " << e.what() << "\n";
    }
}


void editItem() {
    int id;
    getInput(id, "Enter the ID of the item to edit: ");

    for (int i = 0; i < itemCount; i++) {
        if (itemIds[i] == id) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear buffer
            cout << "Enter new name: ";
            getline(cin, itemNames[i]);  // Use getline to read names with spaces
            getInput(itemQuantities[i], "Enter new quantity: ");
            getInput(itemPrices[i], "Enter new price: ");
            cout << "Item updated successfully!\n";
            return;
        }
    }
    cout << "Item not found!\n";
}

void deleteItem() {
    try {
        int id;
        getInput(id, "Enter the ID of the item to delete: ");

        for (int i = 0; i < itemCount; i++) {
            if (itemIds[i] == id) {
                for (int j = i; j < itemCount - 1; j++) {
                    itemIds[j] = itemIds[j + 1];
                    itemNames[j] = itemNames[j + 1];
                    itemQuantities[j] = itemQuantities[j + 1];
                    itemPrices[j] = itemPrices[j + 1];
                }
                itemCount--;
                cout << "Item deleted successfully!\n";
                return;
            }
        }
        throw runtime_error("Item not found!");
    } catch (const exception &e) {
        cout << "Error: " << e.what() << "\n";
    }
}

void deleteAllItems() {
    try {
        itemCount = 0;
        cout << "All items deleted successfully!\n";
    } catch (const exception &e) {
        cout << "An error occurred: " << e.what() << "\n";
    }
}

void displayUserMenu() {
    int choice;

    while (true) {
        try {
            system("cls");
            cout << "\n--- User Menu ---\n";
            cout << "1. Items Menu\n";
            cout << "2. Select Items\n";
            cout << "3. My Bill\n";
            cout << "4. Last Record\n";
            cout << "5. Help Center\n";
            cout << "6. Ratings\n";
            cout << "7. Back to Main Menu\n";

            getInput(choice, "Enter your choice: ");

            switch (choice) {
                case 1:
                    displayAllDetails();
                    system("pause");
                    break;
                case 2:
                    displayAllDetails();
                    selectItems();
                    system("pause");
                    break;
                case 3:
                    displayBill();
                    system("pause");
                    break;
                case 4:
                    lastRecord();
                    system("pause");
                    break;
                case 5:
                    helpCenter();
                    system("pause");
                    break;
                case 6:
                    ratings();
                    system("pause");
                    break;
                case 7:
                    return;
                default:
                    cout << "Invalid choice! Please try again.\n";
                    system("pause");
            }
        } catch (const exception &e) {
            cout << "An error occurred: " << e.what() << "\n";
            system("pause");
        }
    }
}

void displayItemsMenu() {
    try {
        displayAllDetails();
    } catch (const exception &e) {
        cout << "An error occurred: " << e.what() << "\n";
    }
}

void selectItems() {
    try {
        int id, quantity;
        getInput(id, "Enter the ID of the item to select: ");

        for (int i = 0; i < itemCount; i++) {
            if (itemIds[i] == id) {
                getInput(quantity, "Enter quantity: ");

                if (quantity <= itemQuantities[i]) {
                    itemQuantities[i] -= quantity;
                    userCartIds[userCartCount] = id;
                    userCartNames[userCartCount] = itemNames[i];
                    userCartQuantities[userCartCount] = quantity;
                    userCartPrices[userCartCount] = itemPrices[i] * quantity;
                    userCartCount++;
                    totalBill += itemPrices[i] * quantity;
                    cout << "Item added to cart!\n";
                } else {
                    cout << "Not enough stock available!\n";
                }
                return;
            }
        }
        throw runtime_error("Item not found!");
    } catch (const exception &e) {
        cout << "Error: " << e.what() << "\n";
    }
}

void displayBill() {
    try {
        if (userCartCount == 0) {
            cout << "Your cart is empty.\n";
            return;
        }

        cout << "\n--- Your Bill ---\n";
        for (int i = 0; i < userCartCount; i++) {
            cout << "ID: " << userCartIds[i]
                 << ", Name: " << userCartNames[i]
                 << ", Quantity: " << userCartQuantities[i]
                 << ", Total Price: " << userCartPrices[i] << "\n";
        }
        cout << "Total Amount: " << totalBill << "\n";
    } catch (const exception &e) {
        cout << "An error occurred: " << e.what() << "\n";
    }
}

void lastRecord() {
    try {
        if (userCartCount == 0) {
            cout << "No last record available.\n";
            return;
        }

        cout << "\n--- Last Record ---\n";
        cout << "ID: " << userCartIds[userCartCount - 1]
             << ", Name: " << userCartNames[userCartCount - 1]
             << ", Quantity: " << userCartQuantities[userCartCount - 1]
             << ", Total Price: " << userCartPrices[userCartCount - 1] << "\n";
    } catch (const exception &e) {
        cout << "An error occurred: " << e.what() << "\n";
    }
}

void helpCenter() {
    try {
        cout << "\n--- Help Center ---\n";
        cout << "For assistance, contact us at: help@hondaworkshop.com\n";
    } catch (const exception &e) {
        cout << "An error occurred: " << e.what() << "\n";
    }
}

void ratings() {
    try {
        int rating;
        getInput(rating, "Rate our system (1-5): ");
        if (rating >= 1 && rating <= 5) {
            cout << "Thank you for your feedback!\n";
        } else {
            throw out_of_range("Invalid rating! Please provide a rating between 1 and 5.");
        }
    } catch (const exception &e) {
        cout << "Error: " << e.what() << "\n";
    }
}
