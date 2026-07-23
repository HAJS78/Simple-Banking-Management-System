#pragma once
#include <iostream>
#include<string>
#include<vector>
#include<fstream>
#include<iomanip>
using namespace std;
 
const string file_name_users = "bank_system_user_records.txt";
string permission_id ;

struct st_user_login_data
{

	string user_name;
	string password;
    string permission ;
    bool mark_for_delete = false;
};

enum en_permission_id { inclusive_access=-1, show_client_list = 1,add_new_client=2,delete_client=4,update_client=8,find_a_client=16,transactions=32,
manage_users=64};


namespace user_login_data
{
	
        vector<string>split_user_record(string user_record, string delimiter)
        {
            string data_element = "";
            short pos = 0;
            vector<string>record_data;

            while ((pos = user_record.find(delimiter)) != user_record.npos)
            {

                data_element = user_record.substr(0, pos);
                if (data_element != "")
                {
                    record_data.push_back(data_element);
                }
                user_record.erase(0, pos + delimiter.length());


            }

            if (user_record != "")
            {

                record_data.push_back(user_record);

            }


            return record_data;

        }





        st_user_login_data convert_user_data_to_structure(string record, string delimiter)
        {
            st_user_login_data user;
            vector<string>v_record_data;

            v_record_data = split_user_record(record, delimiter);

            user.user_name = v_record_data[0];
            user.password = v_record_data[1];
            user.permission = v_record_data[2];
            


            return user;
        }


        vector<st_user_login_data> read_user_data_from_file(string file_name_users)
        {

            fstream my_file;
            string line;
            string delimiter = "#//#";
            vector<st_user_login_data>user_records;
            st_user_login_data st_record_data;

            my_file.open(file_name_users, ios::in);

            if (my_file.is_open())
            {
                while (getline(my_file, line))
                {

                    st_record_data = convert_user_data_to_structure(line, delimiter);
                    user_records.push_back(st_record_data);

                }


                my_file.close();
            }

            return user_records;

        }

        bool is_user_found(string user_name,string password,string &permission)
        {
            vector<st_user_login_data>user_records = read_user_data_from_file(file_name_users);
           for(st_user_login_data &user:user_records)
           {
               if (user.user_name == user_name && user.password == password)
               {
                   permission=user.permission;
                   return true;
               }
           
           }
           
              return false;
        }


        

        

	 
	
	


}
namespace show_users_data
{

    vector<st_user_login_data>users_list = user_login_data::read_user_data_from_file(file_name_users);

    void print_user_record(st_user_login_data user_record)
    {
       
       
        cout << left;
        cout << setw(16) << user_record.user_name<< setw(12) << user_record.password << setw(40) << user_record.permission<<endl;
        


    }

    void print_users_records(vector<st_user_login_data> users_data)
    {

        cout << "\n\t\t\t\t\t\tUsers' Data" << endl;   // \t=8 spaces
        cout << "\t\t\t";
        for (short j = 0; j <= 61; j++)cout << '.';
        cout << endl << endl;
        cout << left;
        cout << setw(16) << "User Name" << setw(12) << "Password" << setw(40) << "Permission"<<endl;

        for (st_user_login_data& user_record : users_data)
        {
            print_user_record(user_record);
        }


        cout << "\n\nPress any key to go back to manage users screen" << endl << endl;
        system("pause>0");


    }





}
namespace add_login_credentials_for_new_user
{






    bool user_existed(string user_name)
    {
        vector<st_user_login_data> v_user_data = user_login_data::read_user_data_from_file(file_name_users);
        for (st_user_login_data& record : v_user_data)
        {
            if (record.user_name == user_name)
            {
                cout << "Account with this user name is already existed" << endl;
                return true;
            }

        }
        return false;

    }
    void find_total_permission_number(char ans, en_permission_id permission, short& total_permission_number)
    {
        if (ans == 'y' || ans == 'Y')
            total_permission_number = total_permission_number + permission;

    }


    short assign_user_permission()
    {
        short total_permission_number = 0;

        char ans = 'Y';
        cout << "\n\nDo you want to give full access to this user[y/n]? ";
        cin >> ans;
        if (ans == 'y' || ans == 'Y')
            return -1;
        cout << "Do you want to give access to :" << endl;
        cout << "\nShow client list [y/n]? ";
        cin >> ans;
        find_total_permission_number(ans, show_client_list, total_permission_number);

        cout << "\nAdd new client [y/n]? ";
        cin >> ans;
        find_total_permission_number(ans, add_new_client, total_permission_number);

        cout << "\nDelete client [y/n]? ";
        cin >> ans;
        find_total_permission_number(ans, delete_client, total_permission_number);

        cout << "\nUpdate client [y/n]? ";
        cin >> ans;
        find_total_permission_number(ans, update_client, total_permission_number);

        cout << "\nFind client [y/n]? ";
        cin >> ans;
        find_total_permission_number(ans, find_a_client, total_permission_number);


        cout << "\nTransactions [y/n]? ";
        cin >> ans;
        find_total_permission_number(ans, transactions, total_permission_number);


        cout << "\nManage_users [y/n]? ";
        cin >> ans;
        find_total_permission_number(ans, manage_users, total_permission_number);

        return total_permission_number;

    }




    void read_user_credentials(st_user_login_data& user_credentials)
    {
        string password;

        cout << endl;
        do
        {
            cout << "Enter user number ";
            cin >> user_credentials.user_name;
        } while (user_existed(user_credentials.user_name));

        cout << "Enter user password?";
        cin >> user_credentials.password;
        user_credentials.permission = to_string(assign_user_permission());


    }

    string assemble_user_record_as_oneliner(st_user_login_data user_record)
    {
        string user_data = "";
        user_data += user_record.user_name + "#//#";
        user_data += user_record.password + "#//#";
        user_data += user_record.permission;


        return user_data;


    }


    void  save_user_credentials_to_file(string record, string file_name_users)
    {

        fstream my_file;
        my_file.open(file_name_users, ios::app);

        if (my_file.is_open())
        {




            my_file << endl << record;

            my_file.close();
        }





    }







    void add_user()
    {
        cout << "--------------------------------------------------------------------------------------------------------------" << endl;
        cout << "                                     Bank Mangement System-Add Users Screen                                        " << endl;
        cout << "--------------------------------------------------------------------------------------------------------------" << endl;
        cout << "Adding users: " << endl;
        st_user_login_data user_credentials;
        char answer = 'Y';
        do
        {
            read_user_credentials(user_credentials);
            string my_one_liner = assemble_user_record_as_oneliner(user_credentials);
            save_user_credentials_to_file(my_one_liner, file_name_users);
            cout << "\nuser was successfully added" << endl;
            cout << "\nDo you want to add another user?";
            cin >> answer;

        } while (answer == 'Y' || answer == 'y');


        cout << "\n\nPress any key to go back to manage users menu" << endl;
        system("pause>0");




    }







}
namespace delete_user_credentials
{
    
    string input_user_name(string message)
    {
        string user_name;
        cout << "\n\n" << message;
        cin >> user_name;
        return user_name;


    }

    void print_user_data(st_user_login_data user_credential)
    {

        cout << endl << endl;
        cout << "                        User information                                " << endl;
        for (short j = 0; j <= 75; j++)cout << '*';
        cout << endl;
        cout << "User name  : " << user_credential.user_name<< endl;
        cout << "Password   : " << user_credential.password << endl;
        cout << "Permission : " << user_credential.permission << endl;
        


    }


    bool looking_up_user_credentials_by_user_name(vector <st_user_login_data> user_credentials, string user_name, st_user_login_data & User)
    {

        for (st_user_login_data& user_credential : user_credentials)
        {
            if (user_credential.user_name == user_name)
            {
                User = user_credential;
                return true;
            }

        }
        return false;


    }

    bool mark_user_for_delete_by_user_name(vector<st_user_login_data>& users, string user_name)
    {

        for (st_user_login_data& user : users)
        {
            if (user.user_name == user_name)
            {
                user.mark_for_delete = true;
                return true;
            }

        }

        return false;



    }

    void save_updated_user_data_file_without_the_deleted_credentials(vector<st_user_login_data> user_credentials, string file_name_users)
    {

        fstream my_file;
        my_file.open(file_name_users, ios::out);

        if (my_file.is_open())
        {
            for (st_user_login_data& user_credential : user_credentials)
            {
                if (user_credential.mark_for_delete == false)
                {
                    my_file << add_login_credentials_for_new_user::assemble_user_record_as_oneliner(user_credential) << endl;
                }
            }

            my_file.close();
        }


    }
















    
    bool delete_user_credentials_by_user_name(vector <st_user_login_data> &user_credentials,string user_name)
    {
        st_user_login_data User;
        bool marker = false;
        char answer = 'n';

        if (looking_up_user_credentials_by_user_name(user_credentials, user_name, User))
        {
            print_user_data(User);
            cout << "\n\nAre you sure you want to delete this user ?[Y/N]";
            cin >> answer;
            if (answer == 'Y' || answer == 'y')

            {
                marker = true;
                mark_user_for_delete_by_user_name(user_credentials, user_name);
                save_updated_user_data_file_without_the_deleted_credentials(user_credentials, file_name_users);
                return marker;
            }


        }
        else
        {

            cout << "\n\nUser name " << user_name << " was not found" << endl;
            return marker;

        }


        return marker;

    }
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    
    void delete_user()
    {
        cout << "--------------------------------------------------------------------------------------------------------------" << endl;
        cout << "                                     Bank Mangement System-Delete User' Credentials Screen                                        " << endl;
        cout << "--------------------------------------------------------------------------------------------------------------" << endl;
        cout << "Deleting Users: " << endl;

        char answer = 'Y';
        do
        {

            vector<st_user_login_data>user_credentials = user_login_data::read_user_data_from_file(file_name_users);
            string message = "Enter the user name of the user you want to delete?";
            string user_name = input_user_name(message);
            if(user_name=="Admin")
            {
                cout << "\n\nAdmin credentials cannot be deleted" << endl;
                break;
            }
            if (delete_user_credentials_by_user_name(user_credentials, user_name))
            {
                cout << "\nUser credential was successfully deleted" << endl;
            }
            cout << "\nDo you want to delete another user?";
            cin >> answer;

        } while (answer == 'Y' || answer == 'y');


        cout << "\n\nPress any key to go back to manage users menu" << endl;
        system("pause>0");


    }



}
namespace find_user_login_credentials
{


    void find_user()
    {
        char answer = 'Y';
        vector<st_user_login_data>user_credentials = user_login_data::read_user_data_from_file(file_name_users);
        st_user_login_data Users;

        do
        {

            string message = "Enter user name for the user you want to look up?";
            string user_name = delete_user_credentials::input_user_name(message);


            if (delete_user_credentials::looking_up_user_credentials_by_user_name(user_credentials, user_name,Users))
            {
                delete_user_credentials::print_user_data(Users);
            }
            else
            {
                cout << "\n User name " << Users.user_name << " was not found." << endl;
            }
            cout << "\n\nDo you want to look up another user?";
            cin >> answer;

        } while (answer == 'Y' || answer == 'y');


    }















    void find_users()
    {

        cout << "--------------------------------------------------------------------------------------------------------------" << endl;
        cout << "                                     Bank Mangement System-Find Users' Credentials Screen                                        " << endl;
        cout << "--------------------------------------------------------------------------------------------------------------" << endl;
        cout << "Finding users: " << endl;
        find_user();
        cout << "\n\nPress any key to go back to manage users menu" << endl;
        system("pause>0");





    }



}
namespace update_user_login_credentials 
{

    char confirm_user_update(vector<st_user_login_data>users, string user_name)
    {
        char answer = 'Y';
        for (st_user_login_data&user : users)
        {
            if (user.user_name == user_name)
            {
                delete_user_credentials::print_user_data(user);
                cout << "\n\nAre you sure you want to update this user credentials ?[Y/N]";
                cin >> answer;
                break;
            }

        }

        return answer;



    }

    st_user_login_data input_updated_user_data(st_user_login_data updated_data, string user_name)
    {
        char ans = 'Y';
        updated_data.user_name =user_name;
        cout << "Enter user password?";
        cin >> updated_data.password;
        cout << "\nDo you want to change the authorization given to this user?[Y/N]?";
        cin >> ans;
        if (ans == 'Y' || ans == 'y')
        {
            updated_data.permission = to_string(add_login_credentials_for_new_user::assign_user_permission());
        }

        return updated_data;

    }






    void update_user_credentials_by_user_name(vector<st_user_login_data>& users_data, string user_name)
    {



        for (st_user_login_data& user_credential : users_data)
        {
            if (user_credential.user_name == user_name)
            {


                user_credential = input_updated_user_data(user_credential, user_name);
                break;

            }



        }



    }




    void save_user_data_file_with_updated_credentials(vector<st_user_login_data> user_credentials, string file_name_users)
    {

        fstream my_file;
        my_file.open(file_name_users, ios::out);

        if (my_file.is_open())
        {
            for (st_user_login_data& user_credential : user_credentials)
            {

                my_file << add_login_credentials_for_new_user::assemble_user_record_as_oneliner(user_credential) << endl;

            }

            my_file.close();
        }


    }













    void update_user()
    {

        string message = "Enter user name of the user you want to update?";
        string user_name = delete_user_credentials::input_user_name(message);
        vector<st_user_login_data>user_credentials = user_login_data::read_user_data_from_file(file_name_users);
        st_user_login_data Users;

        if (delete_user_credentials::looking_up_user_credentials_by_user_name(user_credentials, user_name, Users))
        {
            char answer = confirm_user_update(user_credentials, user_name);
            if (answer == 'Y' || answer == 'y')
            {
                update_user_credentials_by_user_name(user_credentials, user_name);
                save_user_data_file_with_updated_credentials(user_credentials, file_name_users);
                cout << "\nUser credentials and data file were updated" << endl;
            }
            else
            {

                cout << "\n\nUpdate was cancelled" << endl;

            }
        }
        else
        {
            cout << "\n\nUser name " << Users.user_name<< " was not found" << endl;

        }




    }










    void update_users()
    {

        cout << "--------------------------------------------------------------------------------------------------------------" << endl;
        cout << "                                     Bank Mangement System-Update Users' Credentials Screen                                        " << endl;
        cout << "--------------------------------------------------------------------------------------------------------------" << endl;
        cout << "Updating users: " << endl;

        char answer = 'Y';
        do
        {

            update_user();
            cout << "\n\nDo you want to update another user login credentials?";
            cin >> answer;

        } while (answer == 'Y' || answer == 'y');


        cout << "\n\nPress any key to go back to manage users menu" << endl;
        system("pause>0");










    }







}