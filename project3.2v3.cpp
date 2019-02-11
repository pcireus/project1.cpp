// -----------------------------------------------------
// Author: Pierre Cireus
// -----------------------------------------------------
   #include <iostream>
   #include <iomanip>
   #include <fstream>
   #include <sstream>
   #include <locale>					  // isdigit
   #include <ctime>
   #include <stdlib.h>
   using namespace std;
// -----------------------------------------------------
// Structure containg tree data
// -----------------------------------------------------
   struct Treeleaf{
       int acc_number;
       string last_name;
       string first_name;
       int month;
       int day;
       int year;
       float annual_salary;
       string dept_code;
       string phone_number;

       Treeleaf *right = NULL;
       Treeleaf *left = NULL;
   };
   //global root poiner
    Treeleaf *root = NULL;
// -----------------------------------------------------
// operation menu
// -----------------------------------------------------
    void Menu(char &choice);
// -----------------------------------------------------
// record modification operations
// -----------------------------------------------------
    void Rec_Menu(int &choice);
// -----------------------------------------------------
//  function for appending Node into tree
// -----------------------------------------------------
    void Append(Treeleaf *ptr);
// -----------------------------------------------------
// Inorder traversal
// -----------------------------------------------------
    void printInOrder( Treeleaf *nodePtr, ostream &cout);
// -----------------------------------------------------
// Preorder traversal
// -----------------------------------------------------
    void Print_pre (Treeleaf * nodePtr, ostream &cout);
// -----------------------------------------------------
// PostOrder traversal
// -----------------------------------------------------
    void Print_post( Treeleaf * nodePtr, ostream &cout);
// -----------------------------------------------------
// add leaf to tree function
// -----------------------------------------------------
    void AddLeaf(int acc, int &count);
// -----------------------------------------------------
// Modify leaf function
// -----------------------------------------------------
   void ModLeaf(int target);
// -----------------------------------------------------
// successor for min
// -----------------------------------------------------
    Treeleaf *successor(Treeleaf *ptr);
// -----------------------------------------------------
// Delete leaf function
// -----------------------------------------------------
   void Delleaf(int target, int &count);
// -----------------------------------------------------
// Ultimate validation function that calls every sub validation function
// -----------------------------------------------------
   bool Ultimate_val(string lname, string fname,string mn, string dy, string yr, string sal, string dept, string phone, int &err_count, int&pos, ostream &cout);
// -----------------------------------------------------
// search function for accounting duplicates
// -----------------------------------------------------
   bool Search(int target);
// -----------------------------------------------------
// birthday validation function
// -----------------------------------------------------
   bool valdate(string t_mn, string t_dy, string t_yr, int &err_count, int&pos, ostream &cout);
// -----------------------------------------------------
// name validation function
// -----------------------------------------------------
   bool valname(string lname, string fname, int &err_count, ostream &cout);
// -----------------------------------------------------
// Salary validation function
// -----------------------------------------------------
   bool valsal(string sal,  int &err_count, ostream &cout);
// -----------------------------------------------------
// department code validation
// -----------------------------------------------------
   bool valdept(string dept, int &err_count, ostream &cout);
// -----------------------------------------------------
// phone number validaiton
// -----------------------------------------------------
   bool valphone(string phone, int &err_count, ostream &cout);
// -----------------------------------------------------
// Function for retreiving age
// -----------------------------------------------------
   int GetAge(Treeleaf *ptr);

// -----------------------------------------------------
//                                      Main Program
// -----------------------------------------------------

int main()
    {
        // -----------------------------------------
    	// declare variables
    	// ------------------------------------
           ifstream inF ("words");      // set input stream for data
           ofstream out ("OutPut");     // output file for employee ravesalsalg duration
		   ofstream Err ("Efile");      // output file for errors
           int total_data_count = 0;    // total data count
           int Err_count = 0;           // toal error coun from file
           int Err_position = 0;        // accounts for the record position where error is found
           int spc = 10;                // formating space
           char choice;
           bool u_val = false;          // validation of birthday


           int temp2_num;                // validation purposes
           string temp2_lname;           // validation purposes
           string temp2_fname;           // validation purposes
           string temp2_mn;              // validation purposes
           string temp2_dy;              // validation purposes
           string temp2_yr;              // validation purposes
           string temp2_sal;             // validation purposes
           string temp2_dept;            // validation purposes
           string temp2_phone;           // validation purposes
        // -----------------------------------------
        // Retrieve data from input file and contrstuct tree
        // -----------------------------------------
            // print error report heading
            Err << "Error File"<<endl;
            Err <<"Record Number      reason for error"<<endl;
          while (!inF.eof())
                {
                    // input for validation
                      inF>>temp2_num >> temp2_lname>> temp2_fname >> temp2_mn >> temp2_dy>>temp2_yr>>temp2_sal>>temp2_dept>>temp2_phone;

                    // calling ultimate validation function
                       u_val =  Ultimate_val(temp2_lname, temp2_fname, temp2_mn, temp2_dy, temp2_yr, temp2_sal, temp2_dept, temp2_phone, Err_count, Err_position, Err);
                    // if valdate returns true
                            if (u_val == true)
                            {
                                // reconvert variables
                                int temp_mn = atoi(temp2_mn.c_str());
                                int temp_dy = atoi(temp2_dy.c_str());
                                int temp_yr = atoi(temp2_yr.c_str());
                                float temp_sal = atoi(temp2_sal.c_str());

                                // declare new node
                                  Treeleaf * x = new Treeleaf;
                                // input data inside node
                                    x->acc_number = temp2_num;
                                    x->last_name = temp2_lname;
                                    x->first_name = temp2_fname;
                                    x->month = temp_mn;
                                    x->day = temp_dy;
                                    x->year = temp_yr;
                                    x->annual_salary = temp_sal;
                                    x->dept_code = temp2_dept;
                                    x->phone_number = temp2_phone;
                                // call append function
                                   Append(x);
                                 // count total
                                   total_data_count++;
                            }
                        else
                            {
                                continue;
                            }
                }

    do
        {
            Menu(choice);
            switch(toupper(choice))
                {
                    case 'A':
                        {
                            bool is_acc_val = true;
                            string t_acc;
                            cout << "Enter account number: ";
                            cin >> t_acc;
                          // if account number is valid number
                          for(int i=0; i< t_acc.length(); i++)
                            {
                                if(isdigit(t_acc[i]))
                                    {

                                        is_acc_val == true;
                                    }
                                else
                                    {
                                        cout << "invalid account number"<<endl;
                                        is_acc_val = false;
                                        break;

                                    }
                            }

                        // change data type to int & search to see record exist
                            if(is_acc_val ==true)
                                {
                                    int acc = atoi(t_acc.c_str());
                                    if (Search(acc) == false)
                                        {
                                            // request and validate all other fields

                                            Treeleaf *ptr = new Treeleaf;
                                            AddLeaf(acc, total_data_count);
                                        }
                                    else
                                        {
                                            cout << "existing account number..."<<endl;

                                        }
                                }
                            break;
                        }

                    case 'D':
                        {
                             bool is_acc_val = true;
                            string t_acc;
                            cout << "Enter account number: ";
                            cin >> t_acc;
                          // if account number is valid number
                          for(int i=0; i< t_acc.length(); i++)
                            {
                                if(isdigit(t_acc[i]))
                                    {

                                        is_acc_val == true;
                                    }
                                else
                                    {
                                        cout << "invalid account number"<<endl;
                                        is_acc_val = false;
                                        break;

                                    }
                            }

                        // change data type to int & search to see record exist
                            if(is_acc_val ==true)
                                {
                                    int acc = atoi(t_acc.c_str());
                                    if (Search(acc) == true)
                                        {
                                                char ans;
                                                cout << "Please confirm deletion with (Y or N): ";
                                                cin >> ans;
                                                if (toupper(ans) == 'Y' )
                                                    {
                                                        // call delete function
                                                            Delleaf(acc, total_data_count);
                                                    }
                                                else if(toupper(ans) != 'N')
                                                    {
                                                        cout << "invalid selection"<<endl;
                                                        break;
                                                    }

                                        }
                                    else
                                        {
                                            cout << "unexisting account number..."<<endl;

                                        }
                                }
                            break;
                        }

                    case 'M':
                        {
                            bool is_acc_val = true;
                            string t_acc;
                            cout << "Enter account number: ";
                            cin >> t_acc;
                          // if account number is valid number
                          for(int i=0; i< t_acc.length(); i++)
                            {
                                if(isdigit(t_acc[i]))
                                    {

                                        is_acc_val == true;
                                    }
                                else
                                    {
                                        is_acc_val = false;
                                        break;

                                    }
                            }

                        // change data type to int & search to see record exist
                            if(is_acc_val ==true)
                                {
                                    int acc = atoi(t_acc.c_str());
                                    if (Search(acc) == true)
                                        {
                                            ModLeaf(acc);
                                        }
                                    else
                                        {
                                            cout << "unexisting account number..."<<endl;

                                        }
                                }



                            break;
                        }
                    case 'P':
                        {
                             // print heading
                                cout <<"                                    Inorder Traversal"<<endl;
                                cout << "                                   *****************"<<endl;

                                cout << right << setw(spc) << "Acct#" <<setw(spc ) << "Last" << right <<
                                setw(spc + 2)<< "First" <<right<<setw(spc + 3) << "date of" << right<<
                                setw(spc + 7 )<<"annual"<< setw(spc + 10)<< "department" << setw(spc)<<endl;
                                cout << right << setw(spc + spc) << "Name"<< right<<setw(spc + 2)
                                <<"Name" << right<<setw(spc + 3) << "birth"<<right<<setw(spc + 7)
                                << "salary" << setw(spc + 5) << "code" << setw(spc)<< "age"<<endl;
                            // call inorder
                               printInOrder(root, cout);
                            // print total records
                               cout << "Total records: "<< right << setw(spc)<< total_data_count - 1<<endl;

                            break;

                        }
                    case 'E':
                        {
                             // print total errors
                                Err << "Total errors: " << setw(spc + 3)<< Err_count<<endl;
                            // ------------------------------------
                            // Print every traversals to output file
                            // ------------------------------------
                            // print heading
                                out <<"                                    Inorder Traversal"<<endl;
                                out << "                                   *****************"<<endl;

                                out << right << setw(spc) << "Acct#" <<setw(spc ) << "Last" << right <<
                                setw(spc + 2)<< "First" <<right<<setw(spc + 3) << "date of" << right<<
                                setw(spc + 7 )<<"annual"<< setw(spc + 10)<< "department" << setw(spc)<<endl;
                                out << right << setw(spc + spc) << "Name"<< right<<setw(spc + 2)
                                <<"Name" << right<<setw(spc + 3) << "birth"<<right<<setw(spc + 7)
                                << "salary" << setw(spc + 5) << "code" << setw(spc)<< "age"<<endl;
                            // call inorder
                               printInOrder(root, out);
                            // print total records
                               out << "Total records: "<< right << setw(spc)<< total_data_count - 1<<endl;

                             // print heading
                                out <<"                                   Preorder Traversal"<<endl;
                                out << "                                   *****************"<<endl;


                                out << right << setw(spc) << "Acct#" <<setw(spc ) << "Last" << right <<
                                setw(spc + 2)<< "First" <<right<<setw(spc + 3) << "date of" << right<<
                                setw(spc + 7 )<<"annual"<< setw(spc + 10)<< "department" << setw(spc)<<endl;
                                out << right << setw(spc + spc) << "Name"<< right<<setw(spc + 2)
                                <<"Name" << right<<setw(spc + 3) << "birth"<<right<<setw(spc + 7)
                                << "salary" << setw(spc + 5) << "code" << setw(spc)<< "age"<<endl;

                            // call preorder
                               Print_pre(root, out);
                            // print total records
                               out << "Total records: "<< right << setw(spc)<< total_data_count - 1<<endl;

                             // print heading
                                out <<"                                   Postorder Traversal"<<endl;
                                out << "                                   *****************"<<endl;

                                out << right << setw(spc) << "Acct#" <<setw(spc ) << "Last" << right <<
                                setw(spc + 2)<< "First" <<right<<setw(spc + 3) << "date of" << right<<
                                setw(spc + 7 )<<"annual"<< setw(spc + 10)<< "department" << setw(spc)<<endl;
                                out << right << setw(spc + spc) << "Name"<< right<<setw(spc + 2)
                                <<"Name" << right<<setw(spc + 3) << "birth"<<right<<setw(spc + 7)
                                << "salary" << setw(spc + 5) << "code" << setw(spc)<< "age"<<endl;

                            // call postorder
                               Print_post(root, out);
                            // print total records
                               out << "Total records: "<< right << setw(spc)<< total_data_count - 1<<endl;
                            break;
                        }
                    default:
                        {
                            cout <<"Invalide selection..."<<endl;
                            break;
                        }
                }

        }while(toupper(choice) != 'E');

        return 0;
    }


// -----------------------------------------------------
// operation menu
// -----------------------------------------------------
    void Menu(char &choice)
        {
            cout << endl;
            cout << "|------------|Menu Option|--------------|" << endl;
            cout << "| A) Add a record                       |" << endl;
            cout << "| M) Modify a record                    |" << endl;
            cout << "| D) Delete a record                    |" << endl;
            cout << "| P) Print report (in order)            |" << endl;
            cout << "| E) Exit System                        |" << endl;
            cout << "|------------|Menu Option|--------------|" << endl;
            cout << endl;
            cout << endl<< "Enter option: ";
            cin >> choice;
            cout << endl;
        }
// -----------------------------------------------------
// record modification operations
// -----------------------------------------------------
    void Rec_Menu(int &choice)
        {
            cout << endl;
            cout << "|------------|Menu Option|--------------|" << endl;
            cout << "| 1) First & Last name                  |" << endl;
            cout << "| 2) Birthdate                          |" << endl;
            cout << "| 3) Annual Salary                      |" << endl;
            cout << "| 4) Departement code                   |" << endl;
            cout << "| 5) Phone number                       |" << endl;
            cout << "| 6) Exit                               |" << endl;
            cout << "|------------|Menu Option|--------------|" << endl;
            cout << endl;
            cout << endl<< "Enter option: ";
            cin >> choice;
            cout << endl;
        }
// -----------------------------------------------------
// Ultimate validation function that calls every sub validation function
// -----------------------------------------------------
   bool Ultimate_val(string lname, string fname,string mn, string dy, string yr, string sal, string dept, string phone, int &err_count, int&pos, ostream &cout)
        {
                // formating space
                    int spc = 15;
                // position
                    pos++;
                // validation declarations
                  bool val1 = false;
                  bool val2 = false;
                  bool val3 = false;
                  bool val4 = false;
                  bool val5 = false;

                // call val1 first which containes outputs records number and position of error
                  val1 = valdate (mn, dy, yr, err_count, pos, cout);
                    // if val1 = false
                        if (val1 == false)
                            {
                                // call other validations
                                  val2 = valname (lname, fname, err_count, cout);
                                // validate salary
                                  val3 = valsal(sal, err_count, cout);
                                // validate departement code
                                  val4 = valdept(dept, err_count, cout);
                                // validate phone number
                                  val5 = valphone(phone, err_count, cout);
                                  cout <<endl;

                            }


                    //else
                      else
                            {

                              // cout position of file
                                  cout << left << setw(spc) << pos << setw(spc);
                              // call other validations
                                  val2 = valname(lname, fname, err_count, cout);
                                // validate salary
                                  val3 = valsal(sal, err_count, cout);
                                // validate departement code
                                  val4 = valdept(dept, err_count,cout);
                                // validate phone number
                                  val5 = valphone(phone, err_count, cout);
                                    cout << endl;

                            }
                        if (val1 == false || val2 == false || val3 == false || val4 == false || val5 == false)
                            {
                                return false;
                            }
                        else
                            {
                                return true;
                            }

        }
// -----------------------------------------------------
// Salary validation function
// -----------------------------------------------------
   bool valsal(string sal,  int &err_count, ostream &cout)
        {
            // vallide
                bool isval = false;
                if(sal =="0")
                    {
                        cout << "salary is zero  "<<endl;
                         err_count++;
                        return false;
                    }
             // read sal char by char making sure it is a float
                for(int i=0; i<sal.length(); i++)
                    {
                        if(!isdigit(sal[i]) && sal[i]!= '.' || sal[i] == '-' )
                            {
                                cout << "invalide Salary   ";
                                 err_count++;
                                return false;
                            }
                        else
                            {
                                isval = true;
                            }
                    }

            // if all chars vallide
                if(isval == true)
                    {
                        return true;
                    }
        }
// -----------------------------------------------------
// department code validation
// -----------------------------------------------------
   bool valdept(string dept, int &err_count, ostream &cout)
        {
            // char range
               string a = "a";
               string z = "z";
               string A = "A";
               string Z = "Z";
            // is dept a single char
                if(dept.length() != 1)
                    {
                        cout << "Invalid dept code   ";
                        err_count++;
                        return false;
                    }
                else if(!isdigit(dept[0]) )
                    {
                        if(dept>= a && dept <=z || dept >= A && dept <= Z)
                            {
                              return true;
                            }
                        else
                            {
                                cout << "Invalid dept code   ";
                                err_count++;
                                return false;
                            }
                    }
                else
                    {   cout << "Invalid dept code   ";
                        err_count++;
                        return false;
                    }

        }
// -----------------------------------------------------
// name validation function
// -----------------------------------------------------
   bool valname(string lname, string fname, int &err_count, ostream &cout)
        {
            bool lErr = false;
            bool fErr = false;
            char a = 'a';
            char A = 'A';
            char z = 'z';
            char Z = 'Z';
            //until at the end of name
                for (int i=0; i<lname.length(); i++)
                    {
                        // if isdigit or is not "-"
                           if (isdigit(lname[i]))
                                {
                                    cout << "Last name not alpha   ";
                                    err_count++;
                                    return false;
                                }
                            // else if inside of range
                            else if(lname[i] >=a && lname[i] <= z || lname[i] >= A && lname[i]<= Z || lname[i] =='-')
                                {
                                    //last name error is false
                                    lErr = false;
                                }
                            else
                                {
                                    // else last name error is true
                                    lErr = true;
                                }

                    }

                for (int k=0; k<fname.length(); k++)
                    {
                        // if isdigit or is not '-'
                           if (isdigit(fname[k]))
                                {
                                    cout << "first name not alpha   ";
                                    err_count++;
                                    return false;

                                }
                            else if((fname[k] >= 'a' && fname[k] <= 'z') || fname[k] >= 'A' && fname[k]<= 'Z' || fname[k] =='-')
                                {
                                    fErr = false;
                                }
                            else
                                {
                                    fErr = true;
                                }
                    }




            // if err found
                if(lErr == true || fErr == true)
                    {
                         err_count++;
                        return false;
                    }
                else
                    {
                        return true;
                    }


        }
// -----------------------------------------------------
// phone number validaiton
// -----------------------------------------------------
   bool valphone(string phone, int &err_count, ostream &cout)
        {
            // validation
               bool isval = false;
            // if not valid phone length
                if(phone.length()!= 12)
                    {
                        cout << "Invalid phone length  ";
                        err_count++;
                        return false;
                    }
                else
                    {
                    // if chars are digits seperated by '/'
                        for(int i=0; i<phone.length(); i++)
                            {
                                if(!isdigit(phone[i]) && phone[i]!= '-')
                                    {
                                        cout << "Invalid phone number";
                                        err_count++;
                                        return false;
                                    }
                                else
                                    {
                                        isval = true;
                                    }
                            }
                        if (isval == true)
                            {
                                return true;
                            }
                    }
        }
// -----------------------------------------------------
// birthday validation function
// -----------------------------------------------------
   bool valdate(string t_mn, string t_dy, string t_yr, int &err_count, int&pos, ostream &cout)
        {
              // formating space
                 int spc = 15;
              // position
            // time retreived from system
                 time_t     rawtime;
                 struct tm* timeinfo;
                 time( &rawtime );
                 timeinfo = localtime( &rawtime );
             if (!isdigit(t_mn[0]) || !isdigit(t_dy[0]) ||!isdigit(t_yr[0]) )
                {
                     cout << left << setw(spc) << pos << setw(spc) << "Invalid birth day ("<<
                             t_dy<<")"<< right<<setw(spc)<<t_mn<<"-"<<t_dy<<"-"<<t_yr<<right<<setw(spc);
                             err_count++;
                             return false;
                }
            else
                {
                // convert all dates to integers
                    int mn = atoi(t_mn.c_str());
                    int dy = atoi(t_dy.c_str());
                    int yr = atoi(t_yr.c_str());
                    // if incomin day > 31 or <1

                  if(dy <1 || dy >31)
                        {
                            // increment error count
                              err_count ++;

                            // print account number and what is invalid if not the whole date
                              cout << left << setw(spc) << pos << setw(spc) << "Invalid birth day ("<<
                                      dy<<")"<< right<<setw(spc)<<mn<<"-"<<dy<<"-"<<yr << "  ";

                                      return false;

                        }


                // else if incomin not in range of 12 months
                  else if( mn < 1 || mn > 12)
                        {
                            // increment error count
                               err_count ++;

                            // print account number and what is invalid if not the whole date
                                 cout << left << setw(spc) << pos << setw(spc) << "Invalid birth month ("<<
                                 mn <<")"<< right<< setw(spc)<<mn<<"-"<<dy<<"-"<<yr<<"  ";


                                 return false;
                        }

                //else if incomin year > current year
                  else if(yr > (timeinfo->tm_year + 1900))
                        {
                         // increment error count
                              err_count ++;

                          // print account number and what is invalid if not the whole date
                                cout << left << setw(spc) << pos << setw(spc) << "Invalid birth year ("<<
                                        yr <<")"<< right<<setw(spc)<<mn<<"-"<<dy<<"-"<<yr<<"  ";

                                        return false;
                        }

                // else if incoming date greater than current date
                  else if (yr == (timeinfo->tm_year + 1900))

                            {
                                if(mn > (timeinfo->tm_mon + 1))
                                    {
                                     // increment error count
                                         err_count ++;
                                        cout << left << setw(spc) << pos << setw(spc) << "Invalid future birthday"<< right<< setw(spc)<<mn<<"-"<<dy<<"-"<<yr<<"  ";
                                        return false;
                                    }
                                else if(mn == (timeinfo->tm_mon + 1 ) && dy >timeinfo->tm_mday)
                                    {
                                         // increment error count
                                        err_count ++;
                                        cout << left << setw(spc) << pos << setw(spc) << "Invalid future birthday"<< right<< setw(spc)<<mn<<"-"<<dy<<"-"<<yr<<"  ";
                                     //increment err_count
                                        return false;
                                    }
                            }

                // else return true;
                  else
                        {
                            return true;
                        }

            }


      }

// -----------------------------------------------------
//  function for appending Node into tree
// -----------------------------------------------------
  void Append(Treeleaf *ptr)
        {
                ptr->left = NULL;
                ptr->right = NULL;

                // if tree is empty
                    if (root == 0)
                        {
                           // first pointer becomes head;
                             root = ptr;

                        }

                    else if((Search(ptr->acc_number)) == false)
                        {
                            //if head key < ptr key
                                if(root->acc_number < ptr->acc_number)
                                    {
                                        // traverse to the left pointer

                                            // declare curr pointer pointing head;
                                                Treeleaf *curr = root;
                                            // while curr->right !0
                                                while (curr->right !=0)
                                                    {
                                                      // continue
                                                         curr = curr->right;
                                                    }

                                            // add ptr to the tail
                                                if (curr->right == 0)
                                                    {
                                                        curr->right = ptr;

                                                    }
                                    }
                            // else if head key > ptr key
                                else if(root->acc_number > ptr->acc_number)
                                     {
                                        // traverse to the right pointer
                                            // delcare curr pointer pointing head
                                                Treeleaf *curr = root;
                                               while (curr->left !=0)
                                                    {
                                                      // continue
                                                        curr = curr->left;
                                                    }

                                            // add pointer to tail
                                               if (curr->left == 0)
                                                    {
                                                        curr->left = ptr;
                                                    }

                                     }



                                }


                }
// -----------------------------------------------------
// add leaf to tree function
// -----------------------------------------------------
    void AddLeaf(int acc, int &count)
        {
            // -----------------------------------------------------
            // declare vairables
            // -----------------------------------------------------
               string temp2_lname;          // validation purposes
               string temp2_fname;          // validation purposes
               string temp2_mn;             // validation purposes
               string temp2_dy;             // validation purposes
               string temp2_yr;             // validation purposes
               string temp2_sal;            // validation purposes
               string temp2_dept;           // validation purposes
               string temp2_phone;          // validation purposes
               int E_count = 0;
               bool val1 = false,
                    val2 = false,
                    val3 = false,
                    val4 = false,
                    val5 = false;

               Treeleaf *ptr = new Treeleaf;

            // request input from user and validate
                cout << "Enter first name: ";
                cin >>temp2_fname;
                cout << "Enter last name: ";
                cin >> temp2_lname;
            // validate input
                val1 =valname(temp2_lname, temp2_fname, E_count, cout);
              //if input validated

                if(val1 == true)
                    {
                        // ptr->acc_number = acc;
                        // ptr->last_name = temp2_lname;
                        // ptr->first_name = temp2_fname;

                        // request next field
                            cout << "Enter birth month (mm): ";
                            cin >>temp2_mn;

                            cout <<"Enter birth day (dd): ";
                            cin >>temp2_dy;

                            cout << "Enter birth year (yyyy): ";
                            cin >> temp2_yr;
                        // validate field
                            val2 = valdate(temp2_mn, temp2_dy, temp2_yr, E_count, E_count, cout);
                        // if input validated
                            if (val2 == true)
                                {
                                // convert to int all vairables
                                   int temp_mn = atoi(temp2_mn.c_str());
                                   int temp_dy = atoi(temp2_dy.c_str());
                                   int temp_yr = atoi(temp2_yr.c_str());

                                    // ptr->month = temp_mn;
                                    // ptr->day = temp_dy;
                                    // ptr->year = temp_yr;

                                    cout << "Enter salary (0.00): ";
                                    cin >> temp2_sal;
                                 // if input validated
                                    val3 = valsal(temp2_sal, E_count, cout);
                                    if (val3 == true)
                                        {
                                        // convert variable to float
                                            float temp_sal = atoi(temp2_sal.c_str());
                                            // ptr->annual_salary = temp_sal;

                                             cout << "Enter department code: ";
                                             cin >>temp2_dept;
                                        //validate field
                                        val4 = valdept(temp2_dept, E_count, cout);
                                        // if input validated
                                            if(val4 == true)
                                                {
                                                    // ptr->dept_code = temp2_dept;
                                                // input next field
                                                     cout << "Enter phone number (850-478-9637): ";
                                                     cin >> temp2_phone;
                                                // validate field
                                                    val5 = valphone(temp2_phone, E_count, cout);
                                                    if(val5 == true)
                                                        {
                                                            // ptr->phone_number = temp2_phone;

                                                             // if every field is validated
                                                            if (val1 == true && val2 == true && val3 == true && val4 == true && val5 ==true)
                                                                {
                                                                    ptr->acc_number = acc;
                                                                    ptr->last_name = temp2_lname;
                                                                    ptr->first_name = temp2_fname;
                                                                    ptr->month = temp_mn;
                                                                    ptr->day = temp_dy;
                                                                    ptr->year = temp_yr;
                                                                    ptr->annual_salary = temp_sal;
                                                                    ptr->dept_code = temp2_dept;
                                                                    ptr->phone_number = temp2_phone;

                                                                // count rec
                                                                    count++;
                                                                // insert into tree
                                                                    Append(ptr);

                                                                }
                                                        }
                                                }
                                        }
                                }
                    }
        }
// -----------------------------------------------------
// Modify leaf function
// -----------------------------------------------------
   void ModLeaf(int target)
        {
            // -----------------------------------------------------
            // delcare variables
            // -----------------------------------------------------
                int choice;
                bool found = false;
                int E_count = 0;
                string temp2_lname;          // validation purposes
                string temp2_fname;          // validation purposes
                string temp2_mn;             // validation purposes
                string temp2_dy;             // validation purposes
                string temp2_yr;             // validation purposes
                string temp2_sal;            // validation purposes
                string temp2_dept;           // validation purposes
                string temp2_phone;          // validation purposes
                // traverse the tree
                Treeleaf * curr = root;
                if (root->acc_number == target)
                    {
                        found = true;
                    }
                else if(root->acc_number < target)
                    {
                        //traverse right
                        while (curr !=0 && found == false)
                            {
                                if (curr->acc_number == target)
                                    {
                                        found = true;
                                    }
                                else
                                    {
                                        curr = curr->right;
                                    }
                            }

                    }

                else if (root->acc_number > target)
                    {
                        // traverse left
                        while (curr !=0 && found == false)
                            {
                                if (curr->acc_number == target)
                                    {
                                        found = true;
                                    }
                                else
                                    {
                                        curr = curr->left;
                                    }
                            }
                    }

                    if(found == true)
                        {
                            do
                                {

                                // display records menu
                                    Rec_Menu(choice);
                                    switch(choice)
                                        {
                                            case 1:
                                                {
                                                    cout << "Enter first name: ";
                                                    cin >>temp2_fname;
                                                    cout << "Enter last name: ";
                                                    cin >> temp2_lname;
                                                  //if input validated
                                                    if(valname(temp2_lname, temp2_fname, E_count, cout) == true)
                                                        {
                                                            curr->last_name = temp2_lname;
                                                            curr->first_name = temp2_fname;
                                                        }


                                                    break;
                                                }
                                            case 2:
                                                {
                                                    cout << "Enter birth month (mm): ";
                                                    cin >>temp2_mn;

                                                    cout <<"Enter birth day (dd): ";
                                                    cin >>temp2_dy;

                                                    cout << "Enter birth year (yyyy): ";
                                                    cin >> temp2_yr;

                                                // if input validated
                                                    if (valdate(temp2_mn, temp2_dy, temp2_yr, E_count, E_count, cout) == true)
                                                        {
                                                        // convert to int all vairables
                                                             int temp_mn = atoi(temp2_mn.c_str());
                                                             int temp_dy = atoi(temp2_dy.c_str());
                                                             int temp_yr = atoi(temp2_yr.c_str());

                                                            curr->month = temp_mn;
                                                            curr->day = temp_dy;
                                                            curr->year = temp_yr;
                                                        }
                                                    break;
                                                }
                                            case 3:
                                                {
                                                    cout << "Enter salary (0.00): ";
                                                    cin >> temp2_sal;

                                                 // if input validated
                                                    if (valsal(temp2_sal, E_count, cout) == true)
                                                        {
                                                        // convert variable to float
                                                            float temp_sal = atoi(temp2_sal.c_str());
                                                            curr->annual_salary = temp_sal;
                                                        }
                                                    break;
                                                }
                                            case 4:
                                                {
                                                    cout << "Enter department code: ";
                                                    cin >>temp2_dept;

                                                // if input validated
                                                    if(valdept(temp2_dept, E_count, cout) == true)
                                                        {
                                                            curr->dept_code = temp2_dept;
                                                        }
                                                    break;
                                                }
                                            case 5:
                                                {
                                                    cout << "Enter phone number (850-478-9637): ";
                                                    cin >> temp2_phone;

                                                    if(valphone(temp2_phone, E_count, cout) == true)
                                                        {
                                                            curr->phone_number = temp2_phone;
                                                        }
                                                    break;
                                                }
                                            case 6:
                                                {
                                                    break;
                                                }
                                            default:
                                                {
                                                    cout << "invalide selection choice..."<<endl;
                                                }
                                        }
                                }while (choice!= 6);


                        }

        }
// -----------------------------------------------------
// Delete leaf function
// -----------------------------------------------------
   void Delleaf(int target, int &count)
        {
            bool found = false;
            Treeleaf * curr = root;
            Treeleaf * parent = NULL;
            if (root->acc_number == target)
                {
                    found = true;
                }
            else if(root->acc_number < target)
                {
                    //traverse right
                    while (curr !=0 && found == false)
                        {
                            if (curr->acc_number == target)
                                {
                                    found = true;
                                }
                            else
                                {
                                    parent = curr;
                                    curr = curr->right;
                                }
                        }

                }

            else if (root->acc_number > target)
                {
                    // traverse left
                    while (curr !=0 && found == false)
                        {
                            if (curr->acc_number == target)
                                {
                                    found = true;
                                }
                            else
                                {
                                    parent = curr;
                                    curr = curr->left;
                                }
                        }
                }

         // case where target is a leaf node
            if (found == true && curr->right == NULL && curr->left == NULL)
                {
                    if(parent->left == curr)
                        {
                            parent->left = NULL;
                        }
                    else
                        {
                            parent->right = NULL;
                        }

                    delete curr;
                    count--;

                }
        // case where target is a parent node with two children
            else if(curr->right != NULL && curr->left != NULL)
                {
                    Treeleaf * curr2 = curr->right;
                    //Treeleaf * parent = NULL;
                    while (curr2->left != NULL)
                        {
                            parent = curr2;
                            curr2=curr2->left;
                        }
                    curr = curr2;
                    parent->left = NULL;
                    delete curr2;
                    curr2 =NULL;
                    count--;
                }
        // case where target is a parent node with one child
            else if (curr->right == NULL || curr->left == NULL)
                {
                    if( curr->left != NULL)
                        {
                            parent->left = curr->left;
                        }
                    else
                        {
                            parent->right = curr->right;
                        }
                        delete curr;
                        curr = NULL;
                        count--;

                }


        }
// -----------------------------------------------------
// Inorder traversal
// -----------------------------------------------------
void printInOrder(Treeleaf * nodePtr, ostream &cout)
    {
         // function for current time calculation
            string date[12]= {"Jan.", "Feb.", "Mar.", "Apr.", "May.", "Jun.",
                            "Jul.", "Aug.", "Sep.", "Oct.", "Nov.", "Dec." };
        // function for current time calculation
            time_t     rawtime;
            struct tm* timeinfo;
            time( &rawtime );
            timeinfo = localtime( &rawtime );
            int spc = 10;


        if(nodePtr == NULL)
            return;

            printInOrder(nodePtr->left, cout);
              int age = GetAge(nodePtr);

            cout << right <<setw(spc)<< nodePtr->acc_number;
            cout << setw(spc) << nodePtr->last_name;
            cout << setw(spc) << nodePtr->first_name[0]<<".";
            cout << setw(spc) << date[nodePtr->month - 1];
            cout << nodePtr->day <<", ";
            cout <<nodePtr->year;
            cout << setw(spc) << "$" <<fixed<<setprecision(2)<<nodePtr->annual_salary;
            cout << setw(spc) << nodePtr->dept_code;
            cout << setw(spc) << age <<endl;

            printInOrder(nodePtr->right, cout);

    }

// -----------------------------------------------------
// post order traversal
// -----------------------------------------------------
void Print_post(Treeleaf *nodePtr, ostream &cout)
    {
          // function for current time calculation
            string date[12]= {"Jan.", "Feb.", "Mar.", "Apr.", "May.", "Jun.",
                            "Jul.", "Aug.", "Sep.", "Oct.", "Nov.", "Dec." };
        // function for current time calculation
            time_t     rawtime;
            struct tm* timeinfo;
            time( &rawtime );
            timeinfo = localtime( &rawtime );
            int spc = 10;
            if(nodePtr == NULL)
                return;

               // recurssion left subtree
                  Print_post(nodePtr->left, cout);
               // recurssion on right subtree
                  Print_post(nodePtr->right, cout);

                    int age = GetAge(nodePtr);

                  cout << right <<setw(spc)<< nodePtr->acc_number;
                  cout << setw(spc) << nodePtr->last_name;
                  cout << setw(spc) << nodePtr->first_name[0]<<".";
                  cout << setw(spc) << date[nodePtr->month - 1];
                  cout << nodePtr->day <<", ";
                  cout <<nodePtr->year;
                  cout << setw(spc) << "$" <<fixed<<setprecision(2)<<nodePtr->annual_salary;
                  cout << setw(spc) << nodePtr->dept_code;
                  cout << setw(spc) << age <<endl;
}

// -----------------------------------------------------
// preorder traversal
// -----------------------------------------------------

void Print_pre (Treeleaf * nodePtr, ostream &cout)
    {
        // function for current time calculation
            string date[12]= {"Jan.", "Feb.", "Mar.", "Apr.", "May.", "Jun.",
                              "Jul.", "Aug.", "Sep.", "Oct.", "Nov.", "Dec." };
        // function for current time calculation
            time_t     rawtime;
            struct tm* timeinfo;
            time( &rawtime );
            timeinfo = localtime( &rawtime );
            int spc = 10;

            if(nodePtr == NULL)
                return;

                  int age = GetAge(nodePtr);

                cout << right <<setw(spc)<< nodePtr->acc_number;
                cout << setw(spc) << nodePtr->last_name;
                cout << setw(spc) << nodePtr->first_name[0]<<".";
                cout << setw(spc) << date[nodePtr->month - 1];
                cout << nodePtr->day <<", ";
                cout <<nodePtr->year;
                cout << setw(spc) << "$" <<fixed<<setprecision(2)<<nodePtr->annual_salary;
                cout << setw(spc) << nodePtr->dept_code;
                cout << setw(spc) << age <<endl;

               // recurssion on left
                  Print_pre(nodePtr->left, cout);
               // recurssion on right
                  Print_pre(nodePtr->right, cout);

    }
// -----------------------------------------------------
// successor for min
// -----------------------------------------------------
    Treeleaf * successor(Treeleaf * ptr)
        {
            Treeleaf *curr = ptr;
            while (curr->left != NULL)
                {
                    curr = curr->left;
                }
            return curr;

        }
// -----------------------------------------------------
// search function for target in tree
// -----------------------------------------------------
bool Search(int target)
    {
        bool found = false;
        Treeleaf * curr = root;
        if (root->acc_number == target)
            {
                found = true;
            }
        else if(root->acc_number < target)
            {
                //traverse right
                while (curr !=0 && found == false)
                    {
                        if (curr->acc_number == target)
                            {
                                found = true;
                            }
                        else
                            {
                                curr = curr->right;
                            }
                    }

            }

        else if (root->acc_number > target)
            {
                // traverse left
                while (curr !=0 && found == false)
                    {
                        if (curr->acc_number == target)
                            {
                                found = true;
                            }
                        else
                            {
                                curr = curr->left;
                            }
                    }
            }

        if (found == true)
            {
                return true;
            }
        else
            {
                return false;
            }

    }
// -----------------------------------------------------
// Function for retreiving emplyee age
// -----------------------------------------------------
int GetAge(Treeleaf *ptr)
    {
        // Date from system
           time_t     rawtime;
           struct tm* timeinfo;
           time( &rawtime );
           timeinfo = localtime(&rawtime);

        //delcare age, the difference between current year and birth year
          int Age = (timeinfo->tm_year + 1900) - (ptr->year);
        //take difference of birth month to current month
          if ((timeinfo->tm_mon + 1 ) > ptr->month)
            {
             // taking difference of months
                int Diffm = (timeinfo->tm_mon + 1 ) - ptr->month;
             // round down if not inthe range of 6 months
                 if(Diffm >6)
                    {
                        Age--;
                    }

            }
          else if ((timeinfo->tm_mon + 1 ) < ptr->month)
            {
             // taking difference of months
                int Diffm = ptr->month - (timeinfo->tm_mon + 1);
             // round down if not inthe range of 6 months
                 if(Diffm >6)
                    {
                        Age--;
                    }

            }
            if(Age == 0)
                {
                    Age++;
                }


        return Age;
    }