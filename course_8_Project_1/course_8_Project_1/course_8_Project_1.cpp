#include <iostream>
#include<string>
#include<vector>
#include<fstream>
#include<iomanip>
#include"bank_system_client.h"
#include"bank_system_user.h"
using namespace std;


enum en_main_screen { Show_clients_list = 1, Add_new_client = 2, Delete_client = 3, Update_client_info = 4, Find_client = 5, Transactions = 6,Manage_users=7, log_out = 8 };
enum en_transactions_screen { Deposit = 1, Withdraw = 2, Total_balances = 3, Exit_trans_screen = 4 };
enum en_manage_users{ Show_users_list = 1, Add_new_user = 2, Delete_user = 3, Update_user_info = 4, Find_user = 5, Main_menu= 6 };

en_main_screen software_main_screen();
void start_bank_mangement_system();
void transactions_screen();
void bank_mangement_system_login_Screen();
void manage_user_screen();

bool check_access(string permission_id,en_permission_id item_permission)
{
    short per_id = stoi(permission_id);
    if (per_id == inclusive_access)
        return true;

    if ((per_id & item_permission)  == item_permission)
        return true;
    else
        return false;   


}

void show_access_denied_message()
{

    cout <<"\nAccess Denied" << endl;
    cout << "Please call Admin for further assistance." << endl;
    cout << "\n\nPress any key to go back to the main menu" << endl;
    system("pause>0");

}

void go_back_to_main_menu()
{
    system("cls");
    start_bank_mangement_system();

}


void show_clinets_list()
{
    system("cls");
    if (!check_access(permission_id, show_client_list))
    {
        show_access_denied_message();
         go_back_to_main_menu();
    }
    vector<st_client_data>clients_records = show_clients_data::read_client_data_from_file(file_name);
    show_clients_data::print_clients_records(clients_records);
    go_back_to_main_menu();
}

void add_new_clients()
{
    system("cls");
    if (!check_access(permission_id, add_new_client))
    {
        show_access_denied_message();
        go_back_to_main_menu();
    }


    add_clients_record::add_client();
    go_back_to_main_menu();
}


void delete_clients_record()
{
    system("cls");
    
    if (!check_access(permission_id, delete_client))
    {
        show_access_denied_message();
        go_back_to_main_menu();
    }
    delete_client_record::delete_client();
    go_back_to_main_menu();
}

void update_clients_record()
{
    system("cls");
    if (!check_access(permission_id, update_client))
    {
        show_access_denied_message();
        go_back_to_main_menu();
    }
    update_clients_info::update_clients();
    go_back_to_main_menu();
}


void find_clients_record()
{
    system("cls");
    if (!check_access(permission_id, find_a_client))
    {
        show_access_denied_message();
        go_back_to_main_menu();
    }
    find_client::find_clients();
    go_back_to_main_menu();
}


void go_back_to_main_transactions_menu()
{
    system("cls");
    start_bank_mangement_system();

}


en_transactions_screen show_transctions_screen()
{
    system("cls");
    short user_choice;
    cout << "--------------------------------------------------------------------------------------------------------------" << endl;
    cout << "                                     Bank Mangement System-Transactions Screen                                      " << endl;
    cout << "--------------------------------------------------------------------------------------------------------------" << endl;
    cout << "\t[1]Deposit" << endl;
    cout << "\t[2]Withdraw" << endl;
    cout << "\t[3]Total Balances " << endl;
    cout << "\t[4]Exit" << endl;
    cout << "--------------------------------------------------------------------------------------------------------------" << endl;
    do
    {
        cout << "choose what you want to do [1-4]" << endl;
        cin >> user_choice;


    } while (user_choice < 1 || user_choice>4);
    return (en_transactions_screen)user_choice;


}

void processing_transactions(en_transactions_screen user_selected_transaction)
{
    system("cls");
    
    switch (user_selected_transaction)
    {

    case Deposit:

        depositions::processing_depositions();
        transactions_screen();
        break;

        break;
    case  Withdraw:
        withdrawals::processing_withdrawals();
        transactions_screen();
        break;
    case  Total_balances:
        total_balances::clients_balances_list();
        transactions_screen();
        break;
    case Exit_trans_screen:
        go_back_to_main_menu();

    }


}




void transactions_screen()
{
    system("cls");
    if (!check_access(permission_id, transactions))
    {
        show_access_denied_message();
        go_back_to_main_menu();
    }
    en_transactions_screen user_selected_transaction = show_transctions_screen();
    processing_transactions(user_selected_transaction);

}


en_manage_users  show_manage_user_screen()
{
    system("cls");
    short int user_choice;
    cout << "--------------------------------------------------------------------------------------------------------------" << endl;
    cout << "                                     Bank Mangement System-Manage Users Screen                                " << endl;
    cout << "--------------------------------------------------------------------------------------------------------------" << endl;
    cout << "\t[1]Show users list" << endl;
    cout << "\t[2]Add new user " << endl;
    cout << "\t[3]Delete user " << endl;
    cout << "\t[4]Update user information " << endl;
    cout << "\t[5]Find user " << endl;
    cout << "\t[6]Main menu" << endl;
    cout << "--------------------------------------------------------------------------------------------------------------" << endl;
    do
    {
        cout << "choose what you want to do [1-6]" << endl;
        cin >> user_choice;


    } while (user_choice < 1 || user_choice>6);
    return (en_manage_users)user_choice;


}

void show_users_list()
{
   
    vector<st_user_login_data>users_records = user_login_data::read_user_data_from_file(file_name_users);
    show_users_data::print_users_records(users_records);
    manage_user_screen();
}

void add_new_user()
{
    
    add_login_credentials_for_new_user::add_user();
    manage_user_screen();
}
void delete_users()
{
    delete_user_credentials::delete_user();
     manage_user_screen();

}
void look_up_users()
{
    find_user_login_credentials::find_users();
    manage_user_screen();

}

void update_users_credentials()
{
    update_user_login_credentials::update_users();
    manage_user_screen();

}




void processing_manage_user_screen_inquiry(en_manage_users user_inquiry)
{
    system("cls");
    switch (user_inquiry)
    {
    
    case Show_users_list:
        show_users_list();
        break;
    case  Add_new_user:
         add_new_user();            
         break;
    case  Delete_user:
        delete_users();
        break;
    case  Update_user_info:
        update_users_credentials();
        break;
    case  Find_user:
        look_up_users();
        break;
    case Main_menu:
        go_back_to_main_menu();
        break;
   
    }
    
}




void manage_user_screen()
{
    system("cls");
    if (!check_access(permission_id, manage_users))
    {
        show_access_denied_message();
        go_back_to_main_menu();
    }
    en_manage_users user_inquiry = show_manage_user_screen();
    processing_manage_user_screen_inquiry(user_inquiry);


}

en_main_screen software_main_screen()
{


    short int main_choice;
    cout << "--------------------------------------------------------------------------------------------------------------" << endl;
    cout << "                                     Bank Mangement System-Main Screen                                        " << endl;
    cout << "--------------------------------------------------------------------------------------------------------------" << endl;
    cout << "\t[1]Show clients list" << endl;
    cout << "\t[2]Add new client " << endl;
    cout << "\t[3]Delete client " << endl;
    cout << "\t[4]Update client information " << endl;
    cout << "\t[5]Find client " << endl;
    cout << "\t[6]Transactions" << endl;
    cout << "\t[7]Manage users" << endl;
    cout << "\t[8]Logout" << endl;
    cout << "--------------------------------------------------------------------------------------------------------------" << endl;
    do
    {
        cout << "choose what you want to do [1-8]" << endl;
        cin >> main_choice;


    } while (main_choice < 1 || main_choice>8);
    return (en_main_screen)main_choice;


}


void start_bank_mangement_system()
{

    system("cls");
    switch (software_main_screen())
    {

    case Show_clients_list:
        show_clinets_list();
        break;
    case  Add_new_client:
        add_new_clients();
        break;
    case  Delete_client:
        delete_clients_record();
        break;
    case  Update_client_info:
        update_clients_record();
        break;
    case  Find_client:
        find_clients_record();
        break;
    case Transactions:
        transactions_screen();
    case Manage_users: 
        manage_user_screen();
        break;
    case log_out:
        bank_mangement_system_login_Screen();
        break;

    }









}
void bank_mangement_system_login_Screen()
{
    system("cls");
    cout << "--------------------------------------------------------------------------------------------------------------" << endl;
    cout << "                                     Bank Mangement System-Log In Screen                                      " << endl;
    cout << "--------------------------------------------------------------------------------------------------------------" << endl;
    string user_name, password;
    cout << "Enter user name ";
    getline(cin>>ws, user_name);
    cout << "Enter password ";
    cin >> password;
   while (!(user_login_data::is_user_found(user_name, password,permission_id)))
    {
       cout << "UserName/Password is invalid,please enter different login credentials"<<endl;
       cout << "Enter user name ";
       getline(cin>>ws, user_name);
       cout << "Enter password ";
       cin>>password;
    }

   start_bank_mangement_system();



}


int main()
{

    bank_mangement_system_login_Screen();


}
