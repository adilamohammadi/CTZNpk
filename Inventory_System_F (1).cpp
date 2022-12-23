#include <iostream>
#include <fstream>
#include <string>
using namespace std;
int inv_item_count = 0;

struct inventory
{
    string Id = "-1", Name, Cat, Allocated_to[5] = {"0","0","0","0","0"};
    int Item_count = 0, Allocation_count = 0;
};

struct faculty
{
    string Id, Name, Department, Borrowed[100] = {"0"};
    int Borrow_count = 0;
};

// Faculty Data
void Read_Faculty(faculty teacher[])
{
    teacher[0].Id = "CSNC1";
    teacher[0].Name = "Nadeem Majeed";
    teacher[0].Department = "IT";
    teacher[1].Id = "CSNC2";
    teacher[1].Name = "Arifa Mirza";
    teacher[1].Department = "IT";
    teacher[2].Id = "CSNC3";
    teacher[2].Name = "Sunia Javed";
    teacher[2].Department = "IT";
    teacher[3].Id = "CSNC4";
    teacher[3].Name = "Asim Rasool";
    teacher[3].Department = "IT";
    teacher[4].Id = "CSNC5";
    teacher[4].Name = "Mariyam Tarrar";
    teacher[4].Department = "IT";
}

// Reading Data From File
void Read_items(inventory inv_item[])
{
    inv_item_count = 0;
    ifstream item_in("inventery_item_data.txt");
    for (int j = 0; j < 100; j++)
    {
        if (item_in.eof() == 0)
        {
            item_in >> inv_item[j].Id;
            item_in >> inv_item[j].Name;
            item_in >> inv_item[j].Cat;
            item_in >> inv_item[j].Item_count;
            inv_item_count += 1;
        }
        else
        {
            break;
        }
    }
    inv_item_count -= 1;
    item_in.close();
}

// Writing All Data to File
void Write_Items(inventory inv_item[])
{
    ofstream item_out("inventery_item_data.txt");
    for (int i = 0; i < inv_item_count; i++)
    {
        item_out << inv_item[i].Id << endl;
        item_out << inv_item[i].Name << endl;
        item_out << inv_item[i].Cat << endl;
        item_out << inv_item[i].Item_count << endl;
    }
    item_out.close();
}

// View Inventory Items
void View_Items(inventory inv_item[])
{
    cout << "Showing Item Details" << endl
         << endl;
    for (int i = 0; i < inv_item_count; i++)
    {
        if (inv_item[i].Id == "-1")
        {
            continue;
        }
        cout << "Item Number " << i + 1 << endl;
        cout << "Item ID : " << inv_item[i].Id << endl;
        cout << "Item Name : " << inv_item[i].Name << endl;
        cout << "Item Category : " << inv_item[i].Cat << endl;
        cout << "Item Quantity : " << inv_item[i].Item_count << endl;
    }
}

// Add Inventory Items
void Add_Items(inventory inv_item[])
{
    char ch;
    for (int i = 0; i < 100; i++)
    {
        if (inv_item[i].Id == "-1")
        {
            cout << "Add Details for Item Number " << inv_item_count + 1 << " at index " << i << endl;
            cout << "Item ID : ";
            cin >> inv_item[i].Id;
            cout << "Item Name : ";
            cin >> inv_item[i].Name;
            cout << "Item Category : ";
            cin >> inv_item[i].Cat;
            cout << "Item Quantity : ";
            cin >> inv_item[i].Item_count;
            inv_item_count += 1;
            cout << "Do You Want to Add More Items ? (Y/N) : ";
            cin >> ch;
            if (ch == 'n' || ch == 'N')
            {
                break;
            }
        }
    }
}


void Search_Items(inventory inv_item[], faculty teacher[])
{
    string Id;
    cout << "Enter Item ID: ";
    cin >> Id;
    for (int i = 0; i < inv_item_count; i++)
    {
        if (Id == inv_item[i].Id && Id != "-1")
        {
            cout << "Showing Details For ID " << inv_item[i].Id << endl;
            cout << "Item Name : " << inv_item[i].Name << endl;
            cout << "Item Category : " << inv_item[i].Cat << endl;
            cout << "Item Quantity : " << inv_item[i].Item_count << endl;
            cout << "Allocated To Following Teachers " << endl;
            for (int k = 0; k < inv_item[i].Allocation_count; k++)
            {
                for (int j = 0; j < 5; j++)
                {
                    if (inv_item[i].Allocated_to[k] == teacher[j].Id)
                    {
                        cout << "Name : " << teacher[j].Name << endl;
                        cout << "Name : " << teacher[j].Department << endl;
                    }
                }
            }
        }
    }
}

// Edit Inventory Items
void Edit_Items(inventory inv_item[])
{
    string Id;
    cout << "Enter Item ID you want to Edit : ";
    cin >> Id;
    for (int i = 0; i < inv_item_count; i++)
    {
        if (Id == inv_item[i].Id)
        {
        cout << "Item Name : ";
        cin >> inv_item[i].Name;
        cout << "Item Category : ";
        cin >> inv_item[i].Cat;
        cout << "Item Quantity : ";
        cin >> inv_item[i].Item_count;    
        }
        
    }
}

// Retrieve Inventory Items
void Retrieve_Items(inventory inv_item[], faculty teacher[])
{
    string Tid, Id;
    char ch;
    cout << "Enter Teacher Id : ";
    cin >> Tid;
    for (int i = 0; i < 5; i++)
    {
        if (Tid == teacher[i].Id)
        {
            cout << "Mr. " << teacher[i].Name << " have Borrowed these Items " << endl;
            for (int j = 0; j < teacher[i].Borrow_count; j++)
            {
                if (teacher[i].Borrowed[j] == "-1")
                {
                    continue;
                }
                else
                {
                    cout << "Item ID : " << teacher[i].Borrowed[j] << endl;
                    cout << "You want to Retrieve this Item (Y/N): ";
                    cin >> ch;
                    if (ch != 'n' || ch != 'N')
                    {
                        for (int n = 0; n < inv_item_count; n++)
                        {
                            if (teacher[i].Borrowed[j] == inv_item[n].Id)
                            {
                                inv_item[n].Item_count += 1;
                                for (int m = 0; m < inv_item[n].Allocation_count; m++)
                                {
                                    if (inv_item[n].Allocated_to[m] == teacher[i].Id)
                                    {
                                        inv_item[n].Allocated_to[m] = "-1";
                                    }
                                }
                            }
                        }
                        teacher[i].Borrowed[j] = "-1";
                    }
                }
            }
        }
    }
}

// Delete Inventory Item
void Delete_Items(inventory inv_item[])
{
    string Id;
    cout << "Enter Item ID you Want to Delete : ";
    cin >> Id;
    for (int i = 0; i < inv_item_count; i++)
    {
        if (Id == inv_item[i].Id)
        {
            inv_item[i].Id = "-1";
        }
    }
}

// List of Faculty Members who Borrowed specific item
void Teacher_List(inventory inv_item[], faculty teacher[])
{
    string Id;
    cout << "Enter Item ID : ";
    cin >> Id;
    for (int i = 0; i < inv_item_count; i++)
    {
        if (Id == inv_item[i].Id && Id != "-1")
        {
            cout << "List of Teachers" << endl;
            for (int k = 0; k < inv_item[i].Allocation_count; k++)
            {
                for (int n = 0; n < 5; n++)
                {
                    if (inv_item[i].Allocated_to[k] == teacher[n].Id)
                    {
                        cout << "ID : " << teacher[n].Id << endl;
                        cout << "Name : " << teacher[n].Name << endl;
                        cout << "Department : " << teacher[n].Department << endl;
                    }
                }
            }
        }
    }
}
// Assign Inventory Items
void Assign_Items(inventory inv_item[], faculty teacher[])
{
    char ch;
    string Tid, Id;
    bool t_found, i_found;
    do
    {
        cout << "Enter Teacher ID : ";
        cin >> Tid;
        for (int i = 0; i < 5; i++)
        {
            if (Tid == teacher[i].Id)
            {
                t_found = true;
                cout << "Teacher Name : " << teacher[i].Name << endl;
                cout << "Department : " << teacher[i].Department << endl;
                cout << "Enter Item ID you want to Assign : ";
                do
                {
                    cin >> Id;
                    for (int j = 0; j < inv_item_count; j++)
                    {
                        if (Id == inv_item[j].Id && Id != "-1")
                        {
                            i_found = true;
                            if (inv_item[j].Item_count > 0)
                            {
                                cout << "in Stock : " << inv_item[j].Item_count << endl;
                                inv_item[j].Item_count -= 1;
                                cout << "remaining : " << inv_item[j].Item_count << endl;
                                bool flag = false;
                                for (int z = 0; z < inv_item[j].Allocation_count; z++)
                                {
                                    if (inv_item[j].Allocated_to[z] == "-1")
                                    {
                                        inv_item[j].Allocated_to[z] = teacher[i].Id;
                                        flag = true;
                                        break;
                                    }
                                    else{
                                        flag = false;
                                    }
                                }
                                if (flag = false)
                                {
                                    inv_item[j].Allocated_to[inv_item[j].Allocation_count] = teacher[i].Id;
                                    inv_item[j].Allocation_count += 1; 
                                }
                                bool flag1 = false;
                                for (int x = 0; x < teacher[i].Borrow_count; x++)
                                {
                                    if (teacher[i].Borrowed[x] == "-1")
                                    {
                                        teacher[i].Borrowed[x] = inv_item[j].Id;
                                        flag1 = true;
                                        break;
                                    }
                                    else{
                                        flag1 = false;
                                    }    
                                }
                                if (flag1 == false)
                                {
                                teacher[i].Borrowed[teacher[i].Borrow_count] = inv_item[j].Id;
                                teacher[i].Borrow_count += 1;    
                                }
                            }
                            else
                            {
                                cout << "Out of Stock" << endl;
                            }
                            break;
                        }
                        else
                        {
                            i_found = false;
                        }
                    }
                    if (i_found == false)
                    {
                        cout << "No Item Found Against This Item. Enter ID Again" << endl;
                    }
                } while (i_found == false);
                break;
            }
            else
            {
                t_found = false;
            }
        }
        if (t_found == false)
        {
            cout << "No Teacher Found against this ID" << endl;
        }
        cout << "Do You Want to Assign Any Item to Any Teacher Again? (Y/N) : ";
        cin >> ch;
        if (ch == 'n' || ch == 'N')
        {
            t_found = true;
        }
        else{
            t_found = false;
        }
    } while (t_found == false);
}

int main()
{
    int choice;
    bool flag = true;
    inventory inv_item[100];
    faculty teacher[5];
    Read_Faculty(teacher);

    cout << "---Inventory Management System---" << endl;
    cout << "------- Menue -------" << endl;
    do
    {
        cout << "Press" << endl
             << "1: Add Inventory Item" << endl
             << "2: View All Inventory Item" << endl
             << "3: Search Inventory Item" << endl
             << "4: Edit Inventory Item" << endl
             << "5: Delete Inventory Item" << endl
             << "6: Assign Inventory Item" << endl
             << "7: Retrieve Inventory Item" << endl
             << "8: List of Faculty Members who Borrowed specific item" << endl
             << "------------------------------------------------------" << endl;
        cin >> choice;
        switch (choice)
        {
        case 1:
            Read_items(inv_item);
            Add_Items(inv_item);
            Write_Items(inv_item);
            break;
        case 2:
            Read_items(inv_item);
            View_Items(inv_item);
            break;
        case 3:
            Read_items(inv_item);
            Search_Items(inv_item, teacher);
            break;
        case 4:
            Read_items(inv_item);
            Edit_Items(inv_item);
            Write_Items(inv_item);
            break;
        case 5:
            Read_items(inv_item);
            Delete_Items(inv_item);
            Write_Items(inv_item);
            break;
        case 6:
            Read_items(inv_item);
            Assign_Items(inv_item, teacher);
            Write_Items(inv_item);
            break;
        case 7:
            Read_items(inv_item);
            Retrieve_Items(inv_item, teacher);
            Write_Items(inv_item);
            break;
        case 8:
            Read_items(inv_item);
            Teacher_List(inv_item, teacher);
            break;
        default:
            break;
        }
        cout << "Do You Want To Exist ? (1/0) : ";
        cin >> choice;
        if (choice == 0)
        {
            flag = true;
        }
        else
        {
            flag = false;
        }

    } while (flag == true);
    return 0;
}
