#ifndef CALL_H
#define CALL_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define max_contact 50
#define filename "contact_data.dat"

// Structure definition
struct contact {
    char first_name[50];
    char last_name[50];
    char phone_no[50];
    char email[50];
};

// Function prototypes
void menu();
void add_contact(struct contact phone_info[], int *count);
void show_contacts(struct contact phone_info[], int count);
void find_contact(struct contact phone_info[], int count);
void delete_contact(struct contact phone_info[], int *count);
void save_in_file(struct contact phone_info[], int count);
int upload_from_file(struct contact phone_info[]);
void clear_buffer();
void stripNewline(char *str);
void sort_contacts(struct contact phone_info[], int count);
void clear_screen();
#endif