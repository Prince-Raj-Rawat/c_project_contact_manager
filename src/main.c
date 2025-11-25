#include "contact.h"


int main(){

    struct contact phone_info[max_contact];
    int count=0;
    int opt=0;

    printf("starting contact manager..\n");

    count = upload_from_file(phone_info);
    printf("Loaded %d contacts from file.\n", count);



    while(opt != 5)
    {
        menu();

        printf("\nenter :");
        scanf("%d",&opt);
        clear_buffer();

        switch(opt){

            case 1 :
                {clear_screen();
                add_contact(phone_info, &count);
                sort_contacts(phone_info, count);
                break;}
            case 2 :
                {clear_screen();
                show_contacts(phone_info, count);
                break;}
             case 3 :
                {clear_screen();
                find_contact(phone_info, count);
                break;}
            case 4 :
                {clear_screen();
                delete_contact(phone_info, &count);
                break;}
            case 5 :
                {save_in_file(phone_info, count);
                break;}
            default:
                {printf("invalid choice please choose no. from 1-5.\n");}
        }



    }
        
    

    return 0;

}












