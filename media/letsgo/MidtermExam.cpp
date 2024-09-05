#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
#include <cmath>

using namespace std;

struct CredentialsEntry
{
    string username;
    string password;
};

CredentialsEntry logged_in;

struct UserData
{
    string id;
    string website_name;
    string username;
    string password;
};

string CaesarCipherEncryption(string plain_text_input)
{
    string plain_text = " ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz1234567890-=!@#$%^&*()_+{}[]|;:'\"\\,.<>/?~`";
    int caesar_shift[] = {};
    int digit_caesar_shift = 1;

    int index;

    string cipher_text_output;

    for (int i = 0, n = plain_text_input.size(); i < n; i++)
    {
        for (int j = 0; j < 96; j++)
        {
            if (plain_text_input[i] == plain_text[j])
            {
                index = caesar_shift[digit_caesar_shift];
                if (j == 95)
                {
                    cipher_text_output += plain_text[1 + index];
                }
                else
                {
                    cipher_text_output += plain_text[(j + index) % 96];
                };
                digit_caesar_shift++;
                if (digit_caesar_shift % sizeof(caesar_shift) / sizeof(caesar_shift[0]) == 0)
                {
                    digit_caesar_shift = 1;
                };
                break;
            };
        };
    };

    return cipher_text_output;
};

string CaesarCipherDecryption(string cipher_text_input)
{
    string plain_text = " ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz1234567890-=!@#$%^&*()_+{}[]|;:'\"\\,.<>/?~`";
    int caesar_shift[] = {};
    int digit_caesar_shift = 1;

    int index;

    string plain_text_output;

    for (int i = 0, n = cipher_text_input.size(); i < n; i++)
    {
        for (int j = 0; j < 96; j++)
        {
            if (cipher_text_input[i] == plain_text[j])
            {
                index = caesar_shift[digit_caesar_shift];
                if (j - index < 0)
                {
                    plain_text_output += plain_text[96 + (j - index)];
                }
                else
                {
                    plain_text_output += plain_text[(j - index) % 96];
                };
                digit_caesar_shift++;
                if (digit_caesar_shift % sizeof(caesar_shift) / sizeof(caesar_shift[0]) == 0)
                {
                    digit_caesar_shift = 1;
                };
                break;
            };
        };
    };

    return plain_text_output;
};

string SubstitutionCipherEncryption(string plain_text_input)
{
    string plain_text = " ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz1234567890-=!@#$%^&*()_+{}[]|;:'\"\\,.<>/?~`";
    string cipher_text = " ~!@#$%^&*()_+`1234567890-=qwertyuiop[]\\QWERTYUIOP{}|asdfghjkl;'ASDFGHJKL:\"zxcvbnm,./ZXCVBNM<>?";

    plain_text_input = CaesarCipherEncryption(plain_text_input);

    string cipher_text_output;

    for (int i = 0, n = plain_text_input.size(); i < n; i++)
    {
        for (int j = 0; j < 96; j++)
        {
            if (plain_text_input[i] == plain_text[j])
            {
                cipher_text_output += cipher_text[j];
            };
        };
    };
    return cipher_text_output;
};

string SubstitutionCipherDecryption(string cipher_text_input)
{
    string plain_text = " ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz1234567890-=!@#$%^&*()_+{}[]|;:'\"\\,.<>/?~`";
    string cipher_text = " ~!@#$%^&*()_+`1234567890-=qwertyuiop[]\\QWERTYUIOP{}|asdfghjkl;'ASDFGHJKL:\"zxcvbnm,./ZXCVBNM<>?";

    string plain_text_output;

    for (int i = 0, n = cipher_text_input.size(); i < n; i++)
    {
        for (int j = 0; j < 96; j++)
        {
            if (cipher_text_input[i] == cipher_text[j])
            {
                plain_text_output += plain_text[j];
            };
        };
    };

    return CaesarCipherDecryption(plain_text_output);
};

// RSA Encryption Algorithm
int InverseOfE(int *phi, int *e)
{

    int table[2][2] =
        {
            {*phi, *phi},
            {*e, 1}};

    int temp00 = 0;
    int temp01 = 0;

    while (table[1][0] != 1)
    {
        temp00 = table[1][0];
        temp01 = table[1][1];

        table[1][1] = table[0][1] - ((table[0][0] / table[1][0]) * table[1][1]);
        if (table[1][1] < 0)
        {
            table[1][1] = *phi % table[1][1];
        };

        table[1][0] = table[0][0] - ((table[0][0] / table[1][0]) * table[1][0]);

        table[0][0] = temp00;
        table[0][1] = temp01;
    };
    return table[1][1];
};

bool IsPrime(int *num)
{
    for (int i = 2, n = *num / 2; i <= n; i++)
    {
        if (*num % i == 0)
        {
            return false;
        };
    };

    return true;
};

int PseudoRsaEncryption(string p_word, string q_word)
{

    int p = 0, q = 0;

    for (int i = 0, text_length = p_word.size(); i < text_length; i++)
    {
        p += int(p_word[i]);
    }

    for (int i = 0, text_length = q_word.size(); i < text_length; i++)
    {
        q += int(q_word[i]);
    }

    while (!IsPrime(&p))
    {
        p++;
    };

    while (!IsPrime(&q))
    {
        q++;
    };

    double n = p * q;

    int phi = (p - 1) * (q - 1);

    int e = 3;

    double part_ = pow(n, e);

    int cipher_text = int(part_) % int(n);

    return cipher_text;
};

int SearchProcess(string line, string query)
{
    for (int i = 0, n = line.size() - query.size() + 1; i < n; i++)
    {
        if (query == line.substr(i, query.size()))
        {
            return 1;
        };
    };
    return 0;
};

int Search(string *username, string *password)
{
    cout << endl
         << setfill('*') << setw(20) << '*' << " SEARCH ITEM " << setw(20) << '*' << endl
         << setfill(' ') << endl
         << setw(5) << ' ' << "Search with a minimum of 3 characters" << endl
         << setw(5) << ' ' << "E - Back to Home" << endl
         << endl;

    UserData data_chunk;

    ifstream data_text_file_search("data_text_file.txt");

    string query;

    do
    {
        cout << "-> ";
        cin >> query;
        if (query == "E")
        {
            return 1;
        }
    } while (query.size() < 3);

    cout << endl;

    if (data_text_file_search.good())
    {
        int counter = 0;
        while (!data_text_file_search.eof())
        {
            getline(data_text_file_search, data_chunk.id);
            if (data_chunk.id == to_string(PseudoRsaEncryption(*username, *password)) && !data_text_file_search.eof())
            {
                getline(data_text_file_search, data_chunk.website_name);
                getline(data_text_file_search, data_chunk.username);
                getline(data_text_file_search, data_chunk.password);
                if (SearchProcess(SubstitutionCipherDecryption(data_chunk.website_name), query) || SearchProcess(SubstitutionCipherDecryption(data_chunk.username), query))
                {
                    counter++;
                    cout << "Website name: " << SubstitutionCipherDecryption(data_chunk.website_name) << endl;

                    cout << "Username: " << SubstitutionCipherDecryption(data_chunk.username) << endl;

                    cout << "Password: " << SubstitutionCipherDecryption(data_chunk.password) << endl
                         << endl;
                }
            };
        };
        data_text_file_search.close();
        if (counter == 1)
        {
            cout << counter << " saved login found." << endl;
        }
        if (counter > 1)
        {
            cout << counter << " saved logins found." << endl;
        }
        else if (counter == 0)
        {
            cout << "No saved login found." << endl;
        };
    }
    else
    {
        cout << "No item recorded yet" << endl
             << endl;
    };

    return 0;
}

int DeleteItemVault(string *username, string *password)
{
    cout << endl
         << setfill('*') << setw(20) << '*' << " DELETE ITEM " << setw(20) << '*' << endl
         << setfill(' ') << endl
         << setw(5) << ' ' << "Select item number to delete" << endl
         << setw(5) << ' ' << "E - Back to Home" << endl
         << endl;

    ifstream data_text_file_read("data_text_file.txt");
    UserData data_chunk;

    int counter = 0;

    if (data_text_file_read.good())
    {
        while (!data_text_file_read.eof())
        {
            getline(data_text_file_read, data_chunk.id);
            if (data_chunk.id == to_string(PseudoRsaEncryption(*username, *password)) && !data_text_file_read.eof())
            {
                cout << counter << "." << endl;
                counter++;
                getline(data_text_file_read, data_chunk.website_name);
                cout << "Website name: " << SubstitutionCipherDecryption(data_chunk.website_name) << endl;

                getline(data_text_file_read, data_chunk.username);
                cout << "Username: " << SubstitutionCipherDecryption(data_chunk.username) << endl;

                getline(data_text_file_read, data_chunk.password);
                cout << "Password: " << SubstitutionCipherDecryption(data_chunk.password) << endl
                     << endl;
            };
        };
        data_text_file_read.close();
    };

    string index_to_delete_str;

    do
    {
        cout << "-> ";
        cin >> index_to_delete_str;
        cin.clear();
        if (index_to_delete_str == "E")
        {
            return 1;
        };
    } while (cin.fail());

    int index_to_delete = stoi(index_to_delete_str);

    ifstream data_text_file_read_1("data_text_file.txt");
    ofstream data_text_file_write("temp_data_text_file.txt");

    bool entry_deleted = false;

    if (data_text_file_read_1.good())
    {
        counter = 0;
        while (!data_text_file_read_1.eof())
        {
            getline(data_text_file_read_1, data_chunk.id);
            if (!data_text_file_read_1.eof())
            {
                getline(data_text_file_read_1, data_chunk.website_name);
                getline(data_text_file_read_1, data_chunk.username);
                getline(data_text_file_read_1, data_chunk.password);

                // Saves usernames and passwords of other users
                if (data_chunk.id != to_string(PseudoRsaEncryption(*username, *password)))
                {
                    data_text_file_write << data_chunk.id << endl;
                    data_text_file_write << data_chunk.website_name << endl;
                    data_text_file_write << data_chunk.username << endl;
                    data_text_file_write << data_chunk.password << endl;
                }
                // Saves usernames and passwords of the user
                else if (data_chunk.id == to_string(PseudoRsaEncryption(*username, *password)) && counter != index_to_delete)
                {
                    data_text_file_write << data_chunk.id << endl;
                    data_text_file_write << data_chunk.website_name << endl;
                    data_text_file_write << data_chunk.username << endl;
                    data_text_file_write << data_chunk.password << endl;
                    counter++;
                }
                // Deletes the username and password that user wants to delete
                else
                {
                    entry_deleted = true;
                    counter++;
                };
            };
        };
        data_text_file_read_1.close();
        data_text_file_write.close();

        remove("data_text_file.txt");
        rename("temp_data_text_file.txt", "data_text_file.txt");
    };

    if (entry_deleted)
    {
        cout << endl
             << "Item deleted successfully." << endl;
        return 0;
    }
    else
    {
        cout << endl
             << "Item not found, try again." << endl;
        return 1;
    };

    return 1;
};

int AddItemVault(string *username, string *password)
{
    cout << endl
         << setfill('*') << setw(20) << '*' << " ADD ITEM " << setw(20) << '*' << endl
         << setfill(' ') << endl
         << setw(5) << ' ' << "E - Back to Vault" << endl
         << endl;

    UserData add_item_vault;

    // add_item_vault.id = ;

    cout << "Website name: ";
    cin.ignore();
    getline(cin, add_item_vault.website_name);
    cin.clear();
    if (add_item_vault.website_name == "E")
    {
        return 1;
    };

    cout << "Username: ";
    cin >> add_item_vault.username;
    cin.clear();
    if (add_item_vault.username == "E")
    {
        return 1;
    };

    cout << "Password: ";
    cin >> add_item_vault.password;
    cin.clear();
    if (add_item_vault.password == "E")
    {
        return 1;
    };

    ofstream data_text_file("data_text_file.txt", ios_base::app);

    // ID
    data_text_file << PseudoRsaEncryption(*username, *password) << endl;
    data_text_file << SubstitutionCipherEncryption(add_item_vault.website_name) << endl;
    data_text_file << SubstitutionCipherEncryption(add_item_vault.username) << endl;
    data_text_file << SubstitutionCipherEncryption(add_item_vault.password) << endl;

    data_text_file.close();

    return 0;
}

int Vault(string *username, string *password)
{
start_Vault:
    cout << endl
         << setfill('*') << setw(20) << '*' << " VAULT " << setw(20) << '*' << endl
         << setfill(' ');

    ifstream data_text_file("data_text_file.txt");

    cout << endl;

    if (data_text_file.good())
    {
        UserData data_chunk;
        while (!data_text_file.eof())
        {
            // Identifier
            getline(data_text_file, data_chunk.id);
            if (data_text_file.eof())
            {
                data_text_file.close();
                break;
            }
            getline(data_text_file, data_chunk.website_name);
            getline(data_text_file, data_chunk.username);
            getline(data_text_file, data_chunk.password);

            if (to_string(PseudoRsaEncryption(*username, *password)) == data_chunk.id)
            {
                cout << "Website name: " << SubstitutionCipherDecryption(data_chunk.website_name) << endl;
                cout << "Username: " << SubstitutionCipherDecryption(data_chunk.username) << endl;
                cout << "Password: " << SubstitutionCipherDecryption(data_chunk.password) << endl
                     << endl;
            }
        };
    }
    else
    {
        cout << "No item recorded yet" << endl
             << endl;
    };

    cout << setw(5) << ' ' << "A - Add item" << endl
         << setw(5) << ' ' << "D - Delete item" << endl
         << setw(5) << ' ' << "E - Back to Home" << endl
         << endl;

    cout << "-> ";
    char vault_option;
    cin >> vault_option;
    cin.clear();

    switch (vault_option)
    {
    case 'A':
        switch (AddItemVault(username, password))
        {
        case 1:
            goto start_Vault;
            break;
        case 0:
            cout << endl
                 << "Item saved successfully." << endl;
            goto start_Vault;
            break;
        };
        break;
    case 'D':
        switch (DeleteItemVault(username, password))
        {
        case 1:
            goto start_Vault;
            break;
        case 0:
            goto start_Vault;
            break;
        };
        break;
    case 'E':
        return 1;
    default:
        cout << setfill('*') << setw(3) << '*' << "Invalid selection. Try again." << setw(3) << '*' << endl
             << endl
             << setfill(' ');
        goto start_Vault;
    }
    return 0;
};

void Home(string *username, string *password)
{
start_Home:
    cout << endl
         << setfill('*') << setw(20) << '*' << " HOME " << setw(20) << '*' << endl
         << setfill(' ') << setw(2) << ' ' << "Press a letter to enter a page." << endl
         << endl
         << setw(5) << ' ' << "V - Vault Page" << endl
         << setw(5) << ' ' << "S - Search Page" << endl
         << setw(5) << ' ' << "E - Log Out" << endl
         << endl;
};

// User Interfaces
void MainMenu()
{
    cout << endl
         << setfill('*') << setw(20) << '*' << " SECURUS PASSWORD MANAGER " << setw(20) << '*' << endl
         << setfill(' ') << setw(2) << ' ' << "Press a letter to enter a page." << endl
         << endl
         << setw(5) << ' ' << "L - Log In Page" << endl
         << setw(5) << ' ' << "S - Sign Up Page" << endl
         << setw(5) << ' ' << "E - Exit Program" << endl
         << endl;
};

// LogInMenu returns 1 when user wants to go back to Main Menu
int LogInMenu()
{
    cout << endl
         << setfill('*') << setw(20) << '*' << " LOG IN MENU " << setw(20) << '*' << endl
         << setfill(' ') << setw(2) << ' ' << "If you haven't signed up then type E to get into main menu." << endl
         << endl;

    CredentialsEntry log_in_entry;

    cout << "Username: ";
    cin >> log_in_entry.username;
    cin.clear();
    // Checks if the user wants to go back to Main Menu
    if (log_in_entry.username == "E")
    {
        return 1;
    };
    cout << "Password: ";
    cin >> log_in_entry.password;
    cin.clear();
    // Checks if the user wants to go back to Main Menu
    if (log_in_entry.password == "E")
    {
        return 1;
    };

    int login_status = 0;
    // Define and Initialize Sign up txt file to find email and password
    ifstream sign_up_file("sign_up.txt");
    string sign_up_file_line_log_in;

    if (!sign_up_file.good())
    {
        cout << endl
             << endl
             << setfill('*') << setw(3) << '*' << "The username or password you entered isn't a valid one." << setw(3) << '*' << endl
             << endl;
        return 1;
    }
    while (!sign_up_file.eof())
    {

        getline(sign_up_file, sign_up_file_line_log_in);

        if (sign_up_file.eof())
        {
            break;
        };

        if (!(sign_up_file_line_log_in == ""))
        {
            if (stoi(sign_up_file_line_log_in) == PseudoRsaEncryption(log_in_entry.username, log_in_entry.password))
            {
                cout << endl
                     << "Successfully Logged In" << endl;
                login_status = 1;
                logged_in.username = log_in_entry.username;
                logged_in.password = log_in_entry.password;
                return 0;
            };
        };
    };

    if (login_status == 0)
    {
        cout << endl
             << endl
             << setfill('*') << setw(3) << '*' << "The username or password you entered isn't a valid one." << setw(3) << '*' << endl
             << endl;
        return 1;
    }

    return 1;
};

// SignUpMenu returns 1 when user wants to go back to Main Menu
int SignUpMenu()
{
start_SignUpMenu:
    cout << setfill('*') << setw(20) << '*' << " SIGN UP MENU " << setw(20) << '*' << endl
         << setfill(' ') << setw(2) << ' ' << "If you already signed up then type E to get into main menu." << endl
         << endl
         << setw(5) << ' ' << "No whitespaces between..." << endl
         << setw(5) << ' ' << "eg. lawlawrencee, rencezz, hahaha12" << endl
         << endl;

    CredentialsEntry sign_up_entry;

    cout << "Username: ";
    cin >> sign_up_entry.username;
    cin.clear();
    // Checks if the user wants to go back to Main Menu
    if (sign_up_entry.username == "E")
    {
        return 1;
    };
    cout << "Password: ";
    cin >> sign_up_entry.password;
    cin.clear();
    // Checks if the user wants to go back to Main Menu
    if (sign_up_entry.password == "E")
    {
        return 1;
    };

    // Check for conflicts
    ofstream check_file("sign_up.txt", ios_base::app);
    check_file.close();

    ifstream sign_up_file_conflict_check("sign_up.txt");
    string sign_up_file_conflict_check_line;

    while (!sign_up_file_conflict_check.eof())
    {

        getline(sign_up_file_conflict_check, sign_up_file_conflict_check_line);
        if (sign_up_file_conflict_check.eof())
        {
            break;
        };
        if (!(sign_up_file_conflict_check_line == ""))
        {
            if (stoi(sign_up_file_conflict_check_line) == PseudoRsaEncryption(sign_up_entry.username, sign_up_entry.password))
            {
                cout << endl
                     << "login credentials already exist. Try again." << endl
                     << endl;
                goto start_SignUpMenu;
            };
        };
    };

    // Define and Initialize Sign Up txt file
    ofstream sign_up_file("sign_up.txt", ios_base::app);

    // Add Log In Credentials and Encrypt it using RSA
    sign_up_file << PseudoRsaEncryption(sign_up_entry.username, sign_up_entry.password) << endl;
    sign_up_file.close();

    logged_in.username = sign_up_entry.username;
    logged_in.password = sign_up_entry.password;
    return 0;
};

int main()
{
start:
    MainMenu();

    cout << "-> ";
    char menu_option;

    cin >> menu_option;
    cin.clear();

    switch (menu_option)
    {
    case 'L':
        cin.clear();
        switch (LogInMenu())
        {
        case 1:
            goto start;
            break;
        case 0:
            goto start_Home;
            break;
        };
        break;

    case 'S':
        cin.clear();
        switch (SignUpMenu())
        {
        case 1:
            goto start;
            break;
        case 0:
            goto start_Home;
            break;
        };
        break;

    case 'E':
        goto exit;

    default:
        cout << setfill('*') << setw(3) << '*' << "Invalid selection. Try again." << setw(3) << '*' << endl
             << endl
             << setfill(' ');
        goto start;
    };

    goto start;

start_Home:
    Home(&logged_in.username, &logged_in.username);

    cout << "-> ";
    char home_option;

    cin >> home_option;
    cin.clear();

    switch (home_option)
    {
    case 'V':
        if (Vault(&logged_in.username, &logged_in.password) == 1)
        {
            goto start_Home;
        };
        break;
    start_Search:
    case 'S':
        if (Search(&logged_in.username, &logged_in.password) == 1)
        {
            goto start_Home;
        }
        else
        {
            goto start_Search;
        }
        break;
    case 'E':
        goto start;
    default:
        cout << setfill('*') << setw(3) << '*' << "Invalid selection. Try again." << setw(3) << '*' << endl
             << endl
             << setfill(' ');
        goto start_Home;
    };

exit:
    return 0;
}