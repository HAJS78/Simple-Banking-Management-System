#pragma once
#include <iostream>
#include<string>
#include<vector>
#include<fstream>
#include<iomanip>
using namespace std;


struct st_client_data
{
    string account_number = "";
    string pin_code;
    string name;
    string phone;
    double account_balance = 0;
    bool mark_for_delete = false;

};

const string file_name = "Bank_records_new.txt";

namespace show_clients_data
{


    vector<string>split_client_record(string client_record, string delimiter)
    {
        string data_element = "";
        short pos = 0;
        vector<string>record_data;

        while ((pos = client_record.find(delimiter)) != client_record.npos)
        {

            data_element = client_record.substr(0, pos);
            if (data_element != "")
            {
                record_data.push_back(data_element);
            }
            client_record.erase(0, pos + delimiter.length());


        }

        if (client_record != "")
        {

            record_data.push_back(client_record);

        }


        return record_data;

    }





    st_client_data convert_client_data_to_structure(string record, string delimiter)
    {
        st_client_data client;
        vector<string>v_record_data;

        v_record_data = split_client_record(record, delimiter);

        client.account_number = v_record_data[0];
        client.pin_code = v_record_data[1];
        client.name = v_record_data[2];
        client.phone = v_record_data[3];
        client.account_balance = stod(v_record_data[4]);


        return client;
    }


    vector<st_client_data> read_client_data_from_file(string file_name)
    {

        fstream my_file;
        string line;
        string delimiter = "#//#";
        vector<st_client_data>clients_records;
        st_client_data st_record_data;

        my_file.open(file_name, ios::in);

        if (my_file.is_open())
        {
            while (getline(my_file, line))
            {

                st_record_data = convert_client_data_to_structure(line, delimiter);
                clients_records.push_back(st_record_data);

            }


            my_file.close();
        }

        return clients_records;
    }


    void print_client_record(st_client_data client_record)
    {
        //becasue I have accout balance number in millions, unless i put the below statment it will be printed in
        // scientific notation  
        cout << fixed << showpoint;
        cout << left;
        cout << setw(16) << client_record.account_number << setw(12) << client_record.pin_code << setw(40) << client_record.name;
        cout << setw(17) << client_record.phone << setw(25) << client_record.account_balance << endl;



    }

    void print_clients_records(vector<st_client_data> clients_data)
    {

        cout << "\n\t\t\t\t\t\tClients' Data" << endl;   // \t=8 spaces
        cout << "\t\t\t";
        for (short j = 0; j <= 61; j++)cout << '.';
        cout << endl << endl;
        cout << left;
        cout << setw(16) << "Account Number" << setw(12) << "Pin Code" << setw(40) << "Client Name";
        cout << setw(17) << "Phone" << setw(25) << "Account Balance" << endl;

        for (st_client_data& client_record : clients_data)
        {
            print_client_record(client_record);
        }


        cout << "\n\nPress any key to go back to main menu" << endl << endl;
        system("pause>0");


    }



}

namespace add_clients_record
{

    bool account_existed(string account_number)
    {
        vector<st_client_data> v_clients_data = show_clients_data::read_client_data_from_file(file_name);
        for (st_client_data& record : v_clients_data)
        {
            if (record.account_number == account_number)
            {
                cout << "Account with this account number is already existed" << endl;
                return true;
            }

        }
        return false;

    }

    void read_client_data(st_client_data& client_record)
    {
        cout << endl;
        do
        {
            cout << "Enter account number ";
            cin >> client_record.account_number;
        } while (account_existed(client_record.account_number));
        cout << "Enter a pin code ";
        cin >> client_record.pin_code;
        cin.ignore();
        cout << "Enter client name ";
        getline(cin, client_record.name);
        cout << "Enter client phone number ";
        cin >> client_record.phone;
        cout << "Enter client account balance";
        cin >> client_record.account_balance;

    }


    string assemble_client_record_as_oneliner(st_client_data client_record)
    {
        string client_data = "";
        client_data += client_record.account_number + "#//#";
        client_data += client_record.pin_code + "#//#";
        client_data += client_record.name + "#//#";
        client_data += client_record.phone + "#//#";
        client_data += to_string(client_record.account_balance);

        return client_data;


    }



    void save_record_to_file(string record, string file_name)
    {

        fstream my_file;
        my_file.open(file_name, ios::app);

        if (my_file.is_open())
        {




            my_file << endl << record;

            my_file.close();
        }





    }



    void add_client()
    {
        cout << "--------------------------------------------------------------------------------------------------------------" << endl;
        cout << "                                     Bank Mangement System-Add Clients Screen                                        " << endl;
        cout << "--------------------------------------------------------------------------------------------------------------" << endl;
        cout << "Adding clients: " << endl;
        st_client_data client_record;
        char answer = 'Y';
        do
        {
            read_client_data(client_record);
            save_record_to_file(assemble_client_record_as_oneliner(client_record), file_name);
            cout << "\nClient was successfully added" << endl;
            cout << "\nDo you want to add another record?";
            cin >> answer;

        } while (answer == 'Y' || answer == 'y');


        cout << "\n\nPress any key to go back to the main menu" << endl;
        system("pause>0");




    }




}

namespace delete_client_record
{
    string input_account_number(string message)
    {
        string account_number;
        cout << "\n\n" << message;
        cin >> account_number;
        return account_number;


    }
    void print_client_data(st_client_data client_card)
    {

        cout << endl << endl;
        cout << "                        Client information                                " << endl;
        for (short j = 0; j <= 75; j++)cout << '*';
        cout << endl;
        cout << "Account number : " << client_card.account_number << endl;
        cout << "Pin code       : " << client_card.pin_code << endl;
        cout << "Name           : " << client_card.name << endl;
        cout << "Phone          : " << client_card.phone << endl;
        cout << "Account balance: " << client_card.account_balance << endl;


    }


    bool looking_up_client_record_by_account_number(vector<st_client_data> clients_data, string account_number, st_client_data& Client)
    {

        for (st_client_data& client_record : clients_data)
        {
            if (client_record.account_number == account_number)
            {
                Client = client_record;
                return true;
            }

        }
        return false;


    }

    bool mark_client_for_delete_by_account_number(vector<st_client_data>& clients, string account_number)
    {

        for (st_client_data& client : clients)
        {
            if (client.account_number == account_number)
            {
                client.mark_for_delete = true;
                return true;
            }

        }

        return false;



    }

    void save_updated_client_data_file_without_the_deleted_record(vector<st_client_data> client_record, string file_name)
    {

        fstream my_file;
        my_file.open(file_name, ios::out);

        if (my_file.is_open())
        {
            for (st_client_data& record : client_record)
            {
                if (record.mark_for_delete == false)
                {
                    my_file << add_clients_record::assemble_client_record_as_oneliner(record) << endl;
                }
            }

            my_file.close();
        }


    }


    bool delete_client_record_by_account_number(vector<st_client_data>& clients_data, string account_number)
    {
        st_client_data Client;
        bool marker = false;
        char answer = 'n';

        if (looking_up_client_record_by_account_number(clients_data, account_number, Client))
        {
            print_client_data(Client);
            cout << "\n\nAre you sure you want to delete this client record ?[Y/N]";
            cin >> answer;
            if (answer == 'Y' || answer == 'y')

            {
                marker = true;
                mark_client_for_delete_by_account_number(clients_data, account_number);
                save_updated_client_data_file_without_the_deleted_record(clients_data, file_name);
                return marker;
            }


        }
        else
        {

            cout << "\n\nAccount number " << account_number << " was not found" << endl;
            return marker;

        }


        return marker;

    }







    void delete_client()
    {
        cout << "--------------------------------------------------------------------------------------------------------------" << endl;
        cout << "                                     Bank Mangement System-Delete Clients' Recodrd Screen                                        " << endl;
        cout << "--------------------------------------------------------------------------------------------------------------" << endl;
        cout << "Deleting clients: " << endl;

        char answer = 'Y';
        do
        {

            vector<st_client_data>clients_records = show_clients_data::read_client_data_from_file(file_name);
            string message = "Enter account number you want to delete?";
            string account_number = input_account_number(message);
            if (delete_client_record_by_account_number(clients_records, account_number))
            {
                cout << "\nClient record was successfully deleted" << endl;
            }
            cout << "\nDo you want to delete another record?";
            cin >> answer;

        } while (answer == 'Y' || answer == 'y');


        cout << "\n\nPress any key to go back to the main menu" << endl;
        system("pause>0");


    }














}

namespace update_clients_info
{







    char confirm_update(vector<st_client_data>clients, string account_number)
    {
        char answer = 'Y';
        for (st_client_data& client : clients)
        {
            if (client.account_number == account_number)
            {
                delete_client_record::print_client_data(client);
                cout << "\n\nAre you sure you want to update this client record ?[Y/N]";
                cin >> answer;
                break;
            }

        }

        return answer;



    }

    st_client_data input_updated_data(st_client_data updated_data, string account_number)
    {
        updated_data.account_number = account_number;
        cout << "Enter a pin code ";
        cin >> updated_data.pin_code;
        cin.ignore();
        cout << "Enter client name ";
        getline(cin, updated_data.name);
        cout << "Enter client phone number ";
        cin >> updated_data.phone;
        cout << "Enter client account balance";
        cin >> updated_data.account_balance;

        return updated_data;

    }

    void update_client_record_by_account_number(vector<st_client_data>& clients_data, string account_number)
    {



        for (st_client_data& client_record : clients_data)
        {
            if (client_record.account_number == account_number)
            {


                client_record = input_updated_data(client_record, account_number);
                break;

            }



        }



    }

    void save_client_data_file_with_updated_records(vector<st_client_data> client_record, string file_name)
    {

        fstream my_file;
        my_file.open(file_name, ios::out);

        if (my_file.is_open())
        {
            for (st_client_data& record : client_record)
            {

                my_file << add_clients_record::assemble_client_record_as_oneliner(record) << endl;

            }

            my_file.close();
        }


    }

    void update_client()
    {

        string message = "Enter account number you want to update?";
        string account_number = delete_client_record::input_account_number(message);
        vector<st_client_data>clients_records = show_clients_data::read_client_data_from_file(file_name);
        st_client_data Client;

        if (delete_client_record::looking_up_client_record_by_account_number(clients_records, account_number, Client))
        {
            char answer = confirm_update(clients_records, account_number);
            if (answer == 'Y' || answer == 'y')
            {
                update_client_record_by_account_number(clients_records, account_number);
                save_client_data_file_with_updated_records(clients_records, file_name);
                cout << "\nRecord and data file were updated" << endl;
            }
            else
            {

                cout << "\n\nUpdate was cancelled" << endl;

            }
        }
        else
        {
            cout << "\n\nAccount number " << account_number << " was not found" << endl;

        }




    }

    void update_clients()
    {

        cout << "--------------------------------------------------------------------------------------------------------------" << endl;
        cout << "                                     Bank Mangement System-Update Clients' Recodrd Screen                                        " << endl;
        cout << "--------------------------------------------------------------------------------------------------------------" << endl;
        cout << "Updating clients: " << endl;

        char answer = 'Y';
        do
        {

            update_client();
            cout << "\n\nDo you want to update another record?";
            cin >> answer;

        } while (answer == 'Y' || answer == 'y');


        cout << "\n\nPress any key to go back to the main menu" << endl;
        system("pause>0");










    }
}

namespace find_client
{
    void find_client()
    {
        char answer = 'Y';
        vector<st_client_data>clients_records = show_clients_data::read_client_data_from_file(file_name);
        st_client_data Client;

        do
        {

            string message = "Enter account number you want to look up?";
            string account_number = delete_client_record::input_account_number(message);


            if (delete_client_record::looking_up_client_record_by_account_number(clients_records, account_number, Client))
            {
                delete_client_record::print_client_data(Client);
            }
            else
            {
                cout << "\n Account number " << Client.account_number << " was not found." << endl;
            }
            cout << "\n\nDo you want to look up another client record?";
            cin >> answer;

        } while (answer == 'Y' || answer == 'y');


    }



    void find_clients()
    {

        cout << "--------------------------------------------------------------------------------------------------------------" << endl;
        cout << "                                     Bank Mangement System-Find Clients' Recodrd Screen                                        " << endl;
        cout << "--------------------------------------------------------------------------------------------------------------" << endl;
        cout << "Finding clients: " << endl;
        find_client();
        cout << "\n\nPress any key to go back to the main menu" << endl;
        system("pause>0");





    }





}
namespace depositions
{


    void update_client_balance(vector<st_client_data>& v_clients, string account_number, double new_balance)
    {
        for (st_client_data& record : v_clients)
        {
            if (record.account_number == account_number)
            {
                record.account_balance = new_balance;
                break;

            }


        }




    }

    void processing_client_deposition()
    {
        char answer = 'Y';
        double amount_deposited;
        double new_balance;
        st_client_data Client;
        vector<st_client_data> data_to_process = show_clients_data::read_client_data_from_file(file_name);
        string account_number = delete_client_record::input_account_number("enter account number?");
        if (delete_client_record::looking_up_client_record_by_account_number(data_to_process, account_number, Client))
        {
            delete_client_record::print_client_data(Client);
            cout << "\nEnter the amount you want to deposit?";
            cin >> amount_deposited;
            cout << "\n\nAre you sure we want to continue with this transaction[Y/N]?";
            cin >> answer;
            if (answer == 'Y' || answer == 'y')
            {
                new_balance = Client.account_balance + amount_deposited;
                cout << "\n\n" << amount_deposited << " $ was deposited in " << "account number " << account_number << endl;
                cout << "The new balance : " << new_balance << " $" << endl << endl;
                update_client_balance(data_to_process, account_number, new_balance);
                update_clients_info::save_client_data_file_with_updated_records(data_to_process, file_name);
            }
            else
            {
                cout << "\nTransaction was cancelled" << endl;
            }


        }

        else
        {
            cout << "\nAccount number " << account_number << " was not found" << endl << endl;

        }



    }


    void processing_depositions()
    {
        char more_depo = 'Y';
        cout << "------------------------------------------------------------------" << endl;
        cout << "          Bank Mangement System-Transactions/Deposite screen      " << endl;
        cout << "------------------------------------------------------------------" << endl << endl;
        do
        {
            processing_client_deposition();
            cout << "\nDo you want to make another desposition?";
            cin >> more_depo;



        } while (more_depo == 'Y' || more_depo == 'y');

        cout << "\n\nPress any key to go back to main transactions menu" << endl;
        system("Pause>0");
    }

}
namespace withdrawals
{



    void processing_client_withdrawal()
    {
        char answer = 'Y';
        double amount_withdrawn;
        double new_balance;
        st_client_data Client;
        vector<st_client_data> data_to_process = show_clients_data::read_client_data_from_file(file_name);
        string account_number = delete_client_record::input_account_number("enter account number?");
        if (delete_client_record::looking_up_client_record_by_account_number(data_to_process, account_number, Client))
        {
            delete_client_record::print_client_data(Client);
            cout << "\nEnter the amount you want to withdraw?";
            cin >> amount_withdrawn;
            while (amount_withdrawn > Client.account_balance)
            {
                cout << "The current balance is not sufficient to process this transaction.You can withdraw up to " << Client.account_balance << endl;
                cout << "\nEnter the amount you want to withdraw?";
                cin >> amount_withdrawn;

            }
            cout << "\n\nAre you sure we want to continue with this transaction[Y/N]?";
            cin >> answer;
            if (answer == 'Y' || answer == 'y')
            {
                new_balance = Client.account_balance - amount_withdrawn;
                cout << "\n\n" << amount_withdrawn << " $ was withdrawn from " << "account number " << account_number << endl;
                cout << "The new balance : " << new_balance << " $" << endl << endl;
                depositions::update_client_balance(data_to_process, account_number, new_balance);
                update_clients_info::save_client_data_file_with_updated_records(data_to_process, file_name);
            }
            else
            {
                cout << "\nTransaction was cancelled" << endl;
            }


        }

        else
        {
            cout << "\nAccount number " << account_number << " was not found" << endl << endl;

        }



    }


    void processing_withdrawals()
    {
        char more_depo = 'Y';
        cout << "------------------------------------------------------------------" << endl;
        cout << "          Bank Mangement System-Transactions/withdrawal screen    " << endl;
        cout << "------------------------------------------------------------------" << endl << endl;
        do
        {
            processing_client_withdrawal();
            cout << "\nDo you want to make another withdrawal?";
            cin >> more_depo;



        } while (more_depo == 'Y' || more_depo == 'y');

        cout << "\n\nPress any key to go back to main transactions menu" << endl;
        system("Pause>0");
    }




}
namespace total_balances
{
    double sum_of_balances(vector<st_client_data>data)
    {
        double sum = 0;
        for (st_client_data& record : data)
        {
            sum = sum + record.account_balance;


        }
        return sum;

    }

    void print_client_balance_record(st_client_data record)
    {
        cout << fixed << showpoint;
        cout << left;
        cout << setw(20) << record.account_number << setw(40) << record.name << setw(25) << record.account_balance << endl;

    }


    void print_balances_list(vector<st_client_data>data)
    {
        cout << "\n\t\t\t\t\t\tClients' Balances Data" << endl;
        cout << "\t\t\t";
        for (short j = 0; j <= 61; j++)cout << '.';
        cout << endl << endl << endl;
        cout << left;
        cout << setw(20) << "Account Number" << setw(40) << "Client Name" << setw(25) << "Account Balance" << endl;
        for (short j = 0; j <= 81; j++)cout << '*';
        cout << endl;
        for (st_client_data& client_record : data)
        {
            print_client_balance_record(client_record);
        }

        for (short j = 0; j <= 81; j++)cout << '*';
        cout << endl;
    }


    void clients_balances_list()
    {
        vector<st_client_data> data_to_process = show_clients_data::read_client_data_from_file(file_name);
        print_balances_list(data_to_process);
        cout << "\n\t\t\t\ The total of all clients balances: " << sum_of_balances(data_to_process) << endl;


        cout << "\n\nPress any key to go back to main transactions menu" << endl;
        system("Pause>0");
    }




}
