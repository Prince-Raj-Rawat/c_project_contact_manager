#include  "contact.h""


void clear_buffer(){
    int c;
    while (c=(getchar()) != '\n' && c != EOF);
}

void stripNewline(char *str){

    str[strcspn(str, "\n")] = 0;

} 

void clear_screen() {
#ifdef _WIN32
    system("cls");  
#else
    printf("\033[H\033[J");  
#endif
}

void menu(){
        printf("\n__________________________________");
        printf("\n*********contact manager**********\n");
        printf("__________________________________\n");
        printf("1.add contact\n");
        printf("2.show all contact\n");
        printf("3.search contact\n");
        printf("4.delete contact\n");
        printf("5.save and quit\n");
        printf("__________________________________\n");


}


void add_contact(struct contact phone_info[],int *count){
    system("clear");

    if (*count >= max_contact){

        printf("---------contact list is full---------");
        return;

    }



    struct contact *new_contact=&phone_info[*count];
    printf("Enter first name: ");
    fgets(new_contact->first_name,sizeof(new_contact->first_name),stdin);
    stripNewline(new_contact->first_name);

    printf("Enter last name: ");
    fgets(new_contact->last_name,sizeof(new_contact->last_name),stdin);
    stripNewline(new_contact->last_name);

    printf("Enter phone no: ");
    fgets(new_contact->phone_no,sizeof(new_contact->phone_no),stdin );
    stripNewline(new_contact->phone_no);

    printf("Enter email: ");
    fgets(new_contact->email,sizeof(new_contact->email),stdin);
    stripNewline(new_contact->email);

    printf("-----new contact added successfully-----\n");

    (*count)++;

}

void show_contacts(struct contact phone_info[],int count){
    system("clear");
    printf("\n\n---------contact list---------\n");

    if(count == 0){
        printf("----------empty list----------\n");
        return;
    }

    for (int i = 0; i<count;i++){

        printf("contact : %d\n", i+1);
        printf("name : %s %s\n", phone_info[i].first_name,phone_info[i].last_name);
        printf("phone no : %s\n",phone_info[i].phone_no);
        printf("email address : %s\n\n",phone_info[i].email);


    }

}

void find_contact(struct contact phone_info[],int count){
    system("clear");

    char search_term[50];
    int found_contact=0;

    printf("--------search contact--------\n");
    printf("enter the search term: ");
    fgets(search_term,sizeof(search_term),stdin);
    stripNewline(search_term);

    if (strlen(search_term)==0){
        printf("search term can not be empty\n");
        return;
    }

    printf("search result...\n\n");

    for(int i=0;i< count; i++){
        if(strcasecmp(search_term,phone_info[i].email)==0||strcasecmp(search_term,phone_info[i].first_name)==0||strcasecmp(search_term,phone_info[i].last_name)==0||strcasecmp(search_term,phone_info[i].phone_no)==0)
            {
                printf("Name: %s %s\n",phone_info[i].first_name,phone_info[i].last_name);
                printf("phone_no. : %s\n",phone_info[i].phone_no);
                printf("email address : %s\n",phone_info[i].email);
                found_contact++;
            }
    }

    if(found_contact == 0){
        printf("no contact found containing %s \n",search_term);

    }
    else{
        printf("found %d contact containing %s \n",found_contact,search_term);
    }
    }



    void delete_contact(struct contact phone_info[],int *count){
        system("clear");
        int delete_index=0;

        printf("\n----------delete contact----------\n");

        if(*count == 0){
            printf("contact list is already empty\n");
            return;
        }
         
        printf("select a contact to delete.\n");
        for(int i=0;i< *count;i++){
            printf("%d. %s %s\n",i+1,phone_info[i].first_name,phone_info[i].last_name);
        }

        printf("press 0 to cancel.\n");
        printf("select index of the contact u want to delete : ");
        scanf("%d",&delete_index);
        


        if(delete_index == 0){
            printf("deletion cancelled\n");
            return;
        }

        if(delete_index<1 || delete_index>*count){
            printf("Invalid index selection,\n there is no contact on this index...\n");
            return;
        }

        int real_index = delete_index - 1;


        printf("are you sure you want to delete %s %s (y/n) ",phone_info[real_index].first_name,phone_info[real_index].last_name);
        clear_buffer();
        char confirm = getchar();
        clear_buffer();

        if (confirm == 'y'|| confirm == 'Y'){

            for (int i = real_index; i < *count-1; i++){
                phone_info[i]=phone_info[i+1];
            }
            (*count)--;

            printf("contact deleted successfully.\n");
        }
        else{
            printf("deletion cancelled.\n");
            return;

        }
    }



  void save_in_file(struct contact phone_info[],int count){
    FILE *file;
    file = fopen(filename,"wb");
    if (file == NULL){
        printf("Error: Could not open file '%s' for writing.\n", filename);
        return;
    }

    size_t item_written = fwrite(phone_info,sizeof(struct contact),count,file);

    if(item_written != count){
        printf("Error: write %zu items instead of %d\n",item_written,count);
        return;
    }

    else{
        printf("successfully saved %d contact to %s",count,filename);
    }
    fclose(file);

  }  



int upload_from_file(struct contact phone_info[]){

    FILE *file;
    file = fopen(filename,"rb");
    if(file == NULL){

         printf("No existing contact file ('%s') found. Starting fresh.\n", filename);
        return 0;
    }

   
    size_t itemsRead = fread(phone_info, sizeof(struct contact), max_contact, file);

    if (ferror(file)) {
        fprintf(stderr, "Error reading from file '%s'.\n", file);
    }
    
   
    fclose(file);

    
    return (int)itemsRead;
}

void sort_contacts(struct contact phone_info[], int count) {
    if (count < 2) {
        printf("Not enough contacts to sort.\n");
        return;
    }

    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - i - 1; j++) {
            int cmp = strcasecmp(phone_info[j].first_name, phone_info[j + 1].first_name);
            
            
            if (cmp == 0) {
                cmp = strcasecmp(phone_info[j].last_name, phone_info[j + 1].last_name);
            }
            
            
            if (cmp > 0) {
                struct contact temp = phone_info[j];
                phone_info[j] = phone_info[j + 1];
                phone_info[j + 1] = temp;
            }
        }
    }
    
    printf("Contacts sorted by name successfully.\n");
}