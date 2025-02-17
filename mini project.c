#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct {
    char username[50], password[50];
    int bookedBus; 
} User;

typedef struct {
    char name[50], source[50], destination[50];
    int availableSeats;
    float fare;
} Bus;

User users[100];
Bus buses[] = {
    {"Volvo Express", "City A", "City B", 40, 50.0},
    {"Luxury Coach", "City A", "City C", 35, 65.0},
    {"Economy Ride", "City B", "City C", 50, 35.0},
};
int userCount = 0, busCount = 3;

void displayBuses() {
    for (int i = 0; i < busCount; i++) {
        printf("%d. %s | From: %s | To: %s | Seats: %d | Fare: %.2f\n", 
               i + 1, buses[i].name, buses[i].source, buses[i].destination, 
               buses[i].availableSeats, buses[i].fare);
    }
}

void bookTicket(User *user) {
    if (user->bookedBus != -1) {
        printf("You already booked a ticket for '%s'.\n", buses[user->bookedBus].name);
        return;
    }
    displayBuses();
    printf("Select a bus (1-%d): ", busCount);
    int choice; scanf("%d", &choice); choice--;
    if (choice >= 0 && choice < busCount && buses[choice].availableSeats > 0) {
        buses[choice].availableSeats--; user->bookedBus = choice;
        printf("Ticket booked for '%s'.\n", buses[choice].name);
    } else printf("Invalid choice or no seats available.\n");
}

void cancelTicket(User *user) {
    if (user->bookedBus == -1) {
        printf("No ticket to cancel.\n"); return;
    }
    printf("Cancel ticket for '%s'? (y/n): ", buses[user->bookedBus].name);
    char confirm; scanf(" %c", &confirm);
    if (confirm == 'y' || confirm == 'Y') {
        buses[user->bookedBus].availableSeats++;
        user->bookedBus = -1;
        printf("Ticket canceled.\n");
    } else printf("Cancellation aborted.\n");
}

void userMenu(User *user) {
    while (1) {
        printf("\n~USER MENU~\n1. Book Ticket\n2. Cancel Ticket\n3. Check Bus Status\n4. Logout\nChoice: ");
        int choice; 
        scanf("%d", &choice);
        if (choice == 1) bookTicket(user);
        else if (choice == 2) cancelTicket(user);
        else if (choice == 3) displayBuses();
        else if (choice == 4) break;
        else printf("Invalid choice.\n");
    }
}

void login() {
    char username[50], password[50];
    printf("Username: "); scanf("%s", username);
    printf("Password: "); scanf("%s", password);
    for (int i = 0; i < userCount; i++) {
        if (strcmp(users[i].username, username) == 0 && strcmp(users[i].password, password) == 0) {
            printf("Welcome, %s.\n", username);
            userMenu(&users[i]);
            return;
        }
    }
    printf("Invalid credentials.\n");
}

void addUser() {
    if (userCount >= 100) { printf("User limit reached.\n"); return; }
    printf("New username: "); scanf("%s", users[userCount].username);
    printf("New password: "); scanf("%s", users[userCount].password);
    users[userCount++].bookedBus = -1;
    printf("User added.\n");
}

void deleteUser() {
    char username[50]; printf("Enter username to delete: "); scanf("%s", username);
    for (int i = 0; i < userCount; i++) {
        if (strcmp(users[i].username, username) == 0) {
            for (int j = i; j < userCount - 1; j++) users[j] = users[j + 1];
            userCount--; printf("User deleted.\n"); return;
        }
    }
    printf("User not found.\n");
}

int main() {
    while (1) {
        printf("\n~BOOK YOUR BUS TICKET ~\n1. Login\n2. Add User\n3. Delete User\n4. Exit\nChoice: ");
        int choice; scanf("%d", &choice);
        if (choice == 1) login();
        else if (choice == 2) addUser();
        else if (choice == 3) deleteUser();
        else if (choice == 4) break;
        else printf("Invalid choice.\n");
    }
    return 0;
}