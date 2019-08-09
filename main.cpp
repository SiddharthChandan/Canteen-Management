#include<ctime>
#include<bits/stdc++.h>
#include<iostream>
#include<windows.h>
#include<mysql.h>
#include<sstream>
#include<string>
#include<iomanip>

#define MAX_NO_OF_USERS 30
#define MAX_NO_OF_PRODUCTS 30

using namespace std;

//make the sql connection global

MYSQL* connection;
MYSQL_ROW row;
MYSQL_RES* res;



class Item{

protected:
    int id;
    string name;
    float price;
    int type;

public:
    Item();
    void setItemDetails(int,string,float,int);
    virtual void printDetails() = 0;

    //getters
    inline int getID();
    inline string getName();
    inline float getPrice();
    inline int getType();

    //setters

    void setPrice(float);

};


Item::Item(){
    id = 0;
    name = "";
    price = 0;
    type = 0;
}
void Item::setItemDetails(int x,string iname,float iprice,int itype){
    id = x;
    name = iname;
    price = iprice;
    type = itype;
}


inline int Item::getID(){
    return id;
}
inline string Item::getName(){
    return name;
}
inline float Item::getPrice(){
    return price;
}

inline int Item::getType(){
    return type;
}


    //setters

void Item::setPrice(float x){
    price = x;
}


class Product : public Item{

private:

    int quantityAvailable;
    int state;
    int startTime;
    int endTime;

public:
    Product();
    void setProductDetails(int,string,float,int,int,int,int,int);
    virtual void printDetails();
    //getters
    inline int getQuantityAvailable();
    inline int getStartTime();
    inline int getEndTime();
    inline int getState();

    //setters
    void setQuantityAvailable(int);
    void setStartTime(int);
    void setEndTime(int);
    void setState(int);

};

Product::Product(){
    quantityAvailable = 0;
    state = 0;
}
void Product::setProductDetails(int id,string name,float price,int type,int q,int st,int a,int b){
    Item::setItemDetails(id,name,price,type);

    quantityAvailable = q;
    state = st;
    startTime = a;
    endTime = b;
}

void Product::printDetails(){
    if(this->state == 1){
        cout<<setw(20)<<id<<setw(20)<<name<<setw(20)<<price<<setw(20)<<quantityAvailable<<"\n";
    }
}

    //getters
inline int Product::getQuantityAvailable(){
    return quantityAvailable;
}
inline int Product::getStartTime(){
    return startTime;
}
inline int Product::getEndTime(){
    return endTime;
}

inline int Product::getState(){
    return state;
}

    //setters
void Product::setQuantityAvailable(int x){
    quantityAvailable = x;
}
void Product::setStartTime(int a){
    startTime = a;
}
void Product::setEndTime(int a){
    endTime = a;
}

void Product::setState(int x){
    state = x;
}


class Order : public Item{

private:
    int quantityOrdered;
    int state;
    string date;
public:
    Order();
    virtual void printDetails();

    void setOrderDetails(int,string,float,int,int,int,string);
    //getters
    inline int getQuantityOrdered();
    inline int getState();

    //setters
    void setQuantityOrdered(int);
    void setState(int);


};

Order::Order(){
    quantityOrdered = 0;
    state = 0;
}

void Order::setOrderDetails(int id,string name,float price,int type,int q,int s,string dt){
    Item::setItemDetails(id,name,price,type);
    quantityOrdered = q;
    state = s;
    date = dt;
}

void Order::printDetails(){
    if(this->state == 1){
        cout<<setw(20)<<id<<setw(20)<<name<<setw(20)<<price<<setw(20)<<quantityOrdered<<"\n";
    }

}

inline int Order::getQuantityOrdered(){
    return quantityOrdered;
}

inline int Order::getState(){
    return this->state;
}
void Order::setQuantityOrdered(int n){
    quantityOrdered = n;
}

void Order::setState(int a){
    state = a;
}



class Person{

protected:
    int id;
    string firstName;
    string lastName;
    int age;
    string address;

public:
    Person();
    void takePersonDetails(int,string,string,int,string);
    virtual void printDetails() = 0;
    //getters
    inline string getFullName();
    inline int getAge();
    inline string getAddress();

    //setters

    void setFullName(string fName,string lName);
    void setAge(int x);
    void setAddress(string addr);

};


Person::Person(){
    id = 0;
    firstName = "";
    lastName = "";
    age = 0;
    address = "";
}

void Person::takePersonDetails(int idFromDB,string fn,string ln,int pAge,string addr){
    id = idFromDB;
    firstName = fn;
    lastName = ln;
    age = pAge;
    address = addr;
}

    //getters
inline string Person::getFullName(){
    stringstream ss;
    ss << this->firstName<< " " << this->lastName <<" ";
    string result = ss.str();
    return result;
}
inline int Person::getAge(){
    return age;
}
inline string Person::getAddress(){
    return address;
}
void Person::setFullName(string fName,string laName){
    firstName = fName;
    lastName = laName;
}
void Person::setAge(int x){
    age = x;
}
void Person::setAddress(string addr){
    address = addr;
}



class User : public Person{

private:
    static int count; //to keep track of the no. of users
    string username;
    string password;
    int walletBalance;
    int state;

public:
    User();
    virtual void printDetails();

    void setUserDetails(int,string,string,int,string,string,string,int);
    void purchaseProducts(Product* products,int numberOfProducts);
    void getHistory();
    void addMoney(int amount);

    //add the products functions
    //getters

    inline int getUserID();
    inline string getUsername();
    inline string getPassword();
    inline int getWalletBalance();
    inline int getState();

    //setters
    void setUserName(string uName);
    void setWalletBalance(int balance);
    void setState(int s);


};

int User::count = 0;



User::User(){
    count++;
    username = "";
    password = "";
    walletBalance = 0;
}
void User::setUserDetails(int id,string fn,string ln,int page,string addr,string uname,string pword,int amt){

    Person::takePersonDetails(id,fn,ln,page,addr);
    username = uname;
    password = pword;
    walletBalance = amt;
    state = 1;
}

void changeQuantityOfProduct(int id,int q){

    stringstream ss;
    ss<<"UPDATE products SET product_quantity = '"<<q<<"' WHERE product_id = '"<<id<<"'";
    string query = ss.str();
    const char* qr = query.c_str();

    int qstate = mysql_query(connection,qr);
    if(qstate != 0){
        cout<<"Update products query failed !\n";
        exit(10);
    }
}

void updateOrderInDB(Order* orders,int orderIndex,int userID,float total,string date){
    int i;
    int qstate;
    string query;
    const char* q;
    for(i=0;i<orderIndex;i++){
        if(orders[i].getState() == 1){
            int id = orders[i].getID();
            int quantity = orders[i].getQuantityOrdered();
            float price = orders[i].getPrice();
            string name = orders[i].getName();
            stringstream ss;
            ss<<"INSERT INTO sales(product_id,product_name,customer_id,product_quantity,product_price,amount_paid,order_date) VALUES('"<<id<<"','"<<name<<"','"<<userID<<"','"<<quantity<<"','"<<price<<"','"<<total<<"','"<<date<<"')";
            query = ss.str();
            q = query.c_str();
            qstate = mysql_query(connection,q);
            if(qstate != 0){
                cout<<"Order detail updation in sales table failed !\n";
                exit(12);
            }
        }
    }
}

bool validateDate(int d,int m,int y){
    int daysOfMonth[13] = {0,31,28,31,30,31,30,31,31,30,31,30,31};
    if(y % 100 == 0 || y % 4 == 0){
        daysOfMonth[2]++;
    }

    if(m >= 0 && m <= 12 && d < daysOfMonth[m]){
        return true;
    }
    return false;

}

inline string User::getPassword(){
    return this->password;
}

void User::purchaseProducts(Product* products,int numberOfProducts){
    time_t now = time(0);
    tm *ltm = localtime(&now);
    int curHour = ltm->tm_hour;
    string date;
    int d,m,y;
    int i;
    Order orders[10];
    int orderIndex = 0;
    int orderMainState = 0;

    int choice;
    int id;
    int quantity;
    float total = 0;
    while(1){
        cout<<"Enter the date (date,then month,then year): \n";
        cin>>d>>m>>y;
        if(validateDate(d,m,y)){
            stringstream datestream;
            datestream<<y<<"-"<<m<<"-"<<d;
            date = datestream.str();

            break;
        }
        else{
            cout<<"Invalid date entered !\n";
        }
    }


    while(orderMainState != 1){
        int index = -1;
        cout<<"\nThe available products are : \n";
        cout<<"\nRefrigerated items/stored items: \n";
        cout<<setw(20)<<"ID"<<setw(20)<<"Name"<<setw(20)<<"Price"<<setw(20)<<"Quantity"<<setw(20)<<"\n";
        for(i=0;i<numberOfProducts;i++){
            if(products[i].getType() == 0){
                    if(curHour >= products[i].getStartTime() && products[i].getEndTime() >= curHour){
                        products[i].printDetails();
                    }
            }
        }

        cout<<"\n For Immediate Consumption : \n";
        cout<<setw(20)<<"ID"<<setw(20)<<"Name"<<setw(20)<<"Price"<<setw(20)<<"Quantity"<<setw(20)<<"\n";
        for(i=0;i<numberOfProducts;i++){
            if(products[i].getType() == 1){
                    if(curHour >= products[i].getStartTime() && products[i].getEndTime() >= curHour){
                        products[i].printDetails();
                    }
            }
        }
        cout<<"1. Add an item to the cart\n2. Remove item from the cart\n3. Proceed to billing\nEnter your choice : \n";
        cin>>choice;
        index = -1;

        switch(choice){

        case 1:
            cout<<"Enter the id of the item you want to add to the cart : \n";
            cin>>id;
            index = -1;
            for(i=0;i<numberOfProducts;i++){
                if(products[i].getID() == id){
                    index = i;
                    cout<<"Item details : \n";
                    cout<<setw(20)<<"ID"<<setw(20)<<"Name"<<setw(20)<<"Price"<<setw(20)<<"Quantity"<<setw(20)<<"\n";
                    products[i].printDetails();
                    break;
                }
            }

            if(index == -1){
                cout<<"Invalid ID entered !\n";
                continue;
            }

            cout<<"\nEnter the quantity : \n";
            cin>>quantity;
            //important check

            if(quantity > products[index].getQuantityAvailable()){
                cout<<"Invalid quantity entered !\n";
                continue;
            }

            products[index].setQuantityAvailable(products[index].getQuantityAvailable() - quantity);
            //update database
            changeQuantityOfProduct(products[index].getID(),products[index].getQuantityAvailable());
            orders[orderIndex++].setOrderDetails(products[index].getID(),products[index].getName(),products[index].getPrice(),products[index].getType(),quantity,1,date);
            cout<<"\nItem successfully added !\n";

            break;

        case 2:
            cout<<"\nOrder details  :\n";
            cout<<setw(20)<<"ID"<<setw(20)<<"Name"<<setw(20)<<"Price"<<setw(20)<<"Quantity"<<setw(20)<<"\n";
            for(i=0;i<orderIndex;i++){
                if(orders[i].getState() == 1){
                    orders[i].printDetails();
                }
            }

            cout<<"\nEnter the ID of the item to be deleted : \n";
            cin>>id;
            index = -1;
            for(i=0;i<orderIndex;i++){
                if(orders[i].getState() == 1 && orders[i].getID() == id){
                    orders[i].setState(0);
                    for(i=0;i<numberOfProducts;i++){
                        if(products[i].getID() == orders[i].getID()){
                            products[i].setQuantityAvailable(products[i].getQuantityAvailable() + orders[i].getQuantityOrdered());
                            changeQuantityOfProduct(products[i].getID(),products[i].getQuantityAvailable());
                            break;
                        }
                    }
                    cout<<"\nSelected item deleted from the list\n";
                    index = i;
                    break;
                }
            }

            if(index == -1){
                cout<<"\nInvalid ID entered !\n";
                continue;
            }
            break;


        case 3:
            //calculate amount where state = 1, as quantity * price

            for(i=0;i<orderIndex;i++){
                if(orders[i].getState() == 1){
                    total += (orders[i].getQuantityOrdered() * orders[i].getPrice());
                }
            }


            //display bill, along with grand total
            cout<<"\nBill details : \n";
            cout<<setw(20)<<"ID"<<setw(20)<<"Name"<<setw(20)<<"Price"<<setw(20)<<"Quantity"<<setw(20)<<"\n";
            for(i=0;i<orderIndex;i++){
                if(orders[i].getState() == 1){
                    orders[i].printDetails();
                }
            }

            cout<<"\nTOTAL : "<<total<<"\n";

            int pchoice;
            cout<<"How do you wish to pay ?\n1. From wallet\n2. By cash\n";
            cin>>pchoice;

            switch(pchoice){
            case 1:
                int balance;
                balance = this->getWalletBalance();
                cout<<"Your balance is : "<<balance<<"\n";

                if(balance < total){
                    cout<<"You have insufficient balance !\nYou should pay by cash only!\n";
                }
                else{
                    this->setWalletBalance(balance -= total);
                    cout<<"Your new wallet balance is : "<<this->getWalletBalance()<<"\n";
                    break;
                }
            case 2:
                cout<<"\nO PAYING BY CASH O\n";
                cout<<"Amount settled!\n";
                break;
            }

            updateOrderInDB(orders,orderIndex,this->getUserID(),total,date);
            cout<<"Thank you for using this facility! :-) \n";
            orderMainState = 1;
            break;

        }

    }


}


void User::printDetails(){
    if(this->state == 1 && this->username != "administrator"){
        cout<<setw(20)<<username<<setw(20)<<firstName<<setw(20)<<lastName<<setw(20)<<age<<setw(20)<<address<<setw(20)<<walletBalance<<setw(20)<<"\n";
    }

}
void User::getHistory(){
    cout<<"The history for the particular user  :\n";
    stringstream ss;
    ss<<"SELECT * FROM sales WHERE customer_id = '"<<this->getUserID()<<"'";
    string query = ss.str();
    const char* s = query.c_str();

    int qstate = mysql_query(connection,s);

    if(qstate != 0){
        cout<<"Get history in user query failed !\n";
        exit(13);
    }

    res = mysql_store_result(connection);
    while((row = mysql_fetch_row(res))){
        cout<<setw(20)<<"\n"<<setw(20)<<"Sale ID"<<setw(20)<<"Product Name"<<setw(20)<<"Quantity"<<setw(20)<<"Price"<<setw(20)<<"Amount"<<setw(20)<<"Date"<<setw(20)<<"\n";

        cout<<setw(20)<<row[0]<<setw(20)<<row[2]<<setw(20)<<row[4]<<setw(20)<<row[5]<<setw(20)<<row[6]<<setw(20)<<row[7]<<setw(20)<<"\n";
    }

}
void User::addMoney(int amount){
    this->walletBalance += amount;

}

inline int User::getUserID(){
    return id;
}
inline string User::getUsername(){
    return username;
}
inline int User::getWalletBalance(){
    return walletBalance;
}

inline int User::getState(){
    return state;
}
void User::setState(int s){
    this->state = s;
}

void User::setUserName(string uName){
    username = uName;
}
void User::setWalletBalance(int balance){
    walletBalance = balance;
}

//**********************
//ADMINISTRATOR CLASS
//**********************

class Administrator : public Person{

private:
    string username;
    string password;

public:
    virtual void printDetails();

    Administrator();
    void setAdministratorDetails(int,string,string,int,string,string,string);


    void printAllProductsDetails(Product* products,int& numberOfProducts); //should take arguments - a constant ref to an array of objects
    void addProduct(Product* products,int& numberOfProducts);
    void modifyProduct(Product* products,int& numberOfProducts); //takes in a product object
    void deleteProduct(Product* products,int& numberOfProducts); //
    void printReport();

    void addUser(User* users,int& numberOfUsers);
    void deleteUser(User* users,int& numberOfUsers);
    void printAllUsersDetails(User* users,int& numberOfUsers);

    string getUsername();
    string getPassword();

};

Administrator::Administrator(){

    username = "";
    password = "";

}
void Administrator::setAdministratorDetails(int idfromdb,string fname,string lname,int age,string addr,string uname,string pword){
    Person::takePersonDetails(idfromdb,fname,lname,age,addr);

    this->username = uname;
    this->password = pword;
}

string Administrator::getUsername(){
    return this->username;
}

string Administrator::getPassword(){
    return this->password;
}

void Administrator::printDetails(){
    cout<<setw(20)<<username<<setw(20)<<firstName<<setw(20)<<lastName<<setw(20)<<age<<setw(20)<<address<<setw(20)<<"\n";
}


void Administrator::printAllProductsDetails(Product* products,int& numberOfProducts){
    int i;
    cout<<setw(20)<<"ID"<<setw(20)<<"Name"<<setw(20)<<"Price"<<setw(20)<<"Quantity"<<setw(20)<<"\n";

    for(i=0;i<numberOfProducts;i++){
        products[i].printDetails();
    }
}
void Administrator::addProduct(Product* products,int& numberOfProducts){
    //get details
    string name;
    float price;
    int type;
    int quantity;
    int startTime,endTime;
    cout<<"Enter the name of the product : ";
    cin>>name;

    cout<<"Enter the price of the product : ";
    cin>>price;

    cout<<"Enter the type of the product (1 for packaged items, 0 for immediate consumption items) : ";
    cin>>type;

    cout<<"Enter the quantity available : ";
    cin>>quantity;

    cout<<"Enter the start time and end time in hours alone(24- hour format) : ";
    cin>>startTime>>endTime;


    stringstream ps;

    string query;
    int qstate;
    const char* q;

    ps<<"INSERT INTO products(product_name,product_price,product_quantity,product_type,product_state,product_start_time,product_end_time) VALUES('"<<name<<"','"<<price<<"','"<<quantity<<"','"<<type<<"','"<<1<<"','"<<startTime<<"','"<<endTime<<"') ";
    query = ps.str();
    q = query.c_str();
    qstate = mysql_query(connection,q);

    if(qstate != 0){
        cout<<"Insertion unsuccessful as query failed !\n";
        exit(2);
    }


    stringstream ss;
    ss<<"SELECT product_id FROM products WHERE product_name = '"<<name<<"'";
    query = ss.str();
    q = query.c_str();
    qstate = mysql_query(connection,q);

    if(qstate != 0){
        cout<<"Getting id unsuccessful as query failed !\n";
        exit(3);
    }

    cout<<"\nProduct successfully added !\n";


    res = mysql_store_result(connection);
    row = mysql_fetch_row(res);

    products[numberOfProducts++].setProductDetails(stoi(row[0]),name,price,type,quantity,1,startTime,endTime);

}
void Administrator::modifyProduct(Product* products,int& numberOfProducts){
    printAllProductsDetails(products,numberOfProducts);
    int id;
    cout<<"Which product do you want to modify ? Enter the ID of the product : ";
    cin>>id;
    int index = -1;
    int i = 0;
    while(i < numberOfProducts){
        if(products[i].getState() && products[i].getID() == id){
            index = i;
            break;
        }
        i++;
    }

    if(index == -1){
        cout<<"Invalid ID given!\n";
        return;
    }

    int choice;
    cout<<"What do you want to modify ?\n1.Price\n2.Quantity\n3.Start time\n4.End time\nEnter your choice : ";
    cin>>choice;

    switch(choice){
    case 1:
        {
            float price;
            cout<<"Enter the new price : ";
            cin>>price;

            products[index].setPrice(price);


            //simultaneously update in database
            stringstream ss1;
            ss1 << "UPDATE products SET product_price = '" << price << "' WHERE product_id = '" <<id<<"'";
            string query1 = ss1.str();
            const char* s1 = query1.c_str();
            int qstate1 = mysql_query(connection,s1);

            if(qstate1 != 0){
                cout<<"Updating unsuccessful as query failed !\n";
                exit(4);
            }
            break;
        }
    case 2:
        {
            int quantity;
            cout<<"Enter the new quantity : ";
            cin>>quantity;

            products[index].setQuantityAvailable(quantity);


            //simultaneously update in database
            stringstream ss2;
            ss2 << "UPDATE products SET product_quantity = '" << quantity << "' WHERE product_id = '" <<id<<"'";
            string query2 = ss2.str();
            const char* s2 = query2.c_str();
            int qstate2 = mysql_query(connection,s2);

            if(qstate2 != 0){
                cout<<"Updating unsuccessful as query failed !\n";
                exit(4);
            }

            break;
        }
    case 3:
        {
            int x1;
            cout<<"Enter the new start time : ";
            cin>>x1;

            products[index].setStartTime(x1);


            //simultaneously update in database
            stringstream ss3;
            ss3 << "UPDATE products SET product_start_time = '" << x1 << "' WHERE product_id = '" <<id<<"'";
            string query3 = ss3.str();
            const char* s3 = query3.c_str();
            int qstate3 = mysql_query(connection,s3);

            if(qstate3 != 0){
                cout<<"Updating unsuccessful as query failed !\n";
                exit(4);
            }

            break;

        }
    case 4:
        {

            int x2;
            cout<<"Enter the new end time : ";
            cin>>x2;

            products[index].setEndTime(x2);


            //simultaneously update in database
            stringstream ss4;
            ss4 << "UPDATE products SET product_end_time = '" << x2 << "' WHERE product_id = '" <<id<<"'";
            string query4 = ss4.str();
            const char* s4 = query4.c_str();
            int qstate4 = mysql_query(connection,s4);

            if(qstate4 != 0){
                cout<<"Updating unsuccessful as query failed !\n";
                exit(4);
            }

            break;

        }
    }
}
void Administrator::deleteProduct(Product* products,int& numberOfProducts){
    cout<<setw(20)<<"ID"<<setw(20)<<"Name"<<setw(20)<<"Price"<<setw(20)<<"Quantity"<<setw(20)<<"\n";
    printAllProductsDetails(products,numberOfProducts);
    int id;
    cout<<"Which product do you want to delete ? Enter the ID of the product : ";
    cin>>id;
    int index = -1;
    int i = 0;
    while(i < numberOfProducts){
        if(products[i].getState() && products[i].getID() == id){
            index = i;
            break;
        }
        i++;
    }

    if(index == -1){
        cout<<"Invalid ID given!\n";
        return;
    }

    cout<<"The selected item is :\n";
    products[index].printDetails();

    char choice;
    cout<<"Enter y/Y to confirm deletion, enter n/N to abort !\n";
    cin>>choice;

    choice = tolower(choice);
    if(choice != 'y'){
        cout<<"Operation aborted!\n";
        return;
    }
    else if(choice == 'y'){
        products[i].setState(0);
        //delete from DB
        stringstream ss;
        ss << "DELETE FROM products WHERE product_id = " <<id;
        string query = ss.str();
        const char* s = query.c_str();
        int qstate = mysql_query(connection,s);

        if(qstate != 0){
            cout<<"Deletion unsuccessful as query failed !\n";
            exit(5);
        }

        cout<<"\nProduct successfully deleted !\n";

    }

}
void Administrator::printReport(){
    string d1,d2;
    int d,m,y;
    cout<<"Enter the dates for the query : ";
    while(1){
        cout<<"Enter the start - date (date,then month,then year): \n";
        cin>>d>>m>>y;
        if(validateDate(d,m,y)){
            stringstream datestream;
            datestream<<y<<"-"<<m<<"-"<<d;
            d1 = datestream.str();
            break;
        }
        else{
            cout<<"Invalid date entered !\n";
        }
    }

    while(1){
        cout<<"Enter the end - date (date,then month,then year): \n";
        cin>>d>>m>>y;
        if(validateDate(d,m,y)){
            stringstream datestream;
            datestream<<y<<"-"<<m<<"-"<<d;
            d2 = datestream.str();
            break;
        }
        else{
            cout<<"Invalid date entered !\n";
        }
    }

    stringstream ss;
    ss<<"SELECT * FROM sales WHERE order_date BETWEEN '"<<d1<<"' AND '"<<d2<<"'";
    string query = ss.str();
    const char* s = query.c_str();

    int qstate = mysql_query(connection,s);

    if(qstate != 0){
        cout<<"Get history in admin query failed !\n";
        exit(15);
    }

    res = mysql_store_result(connection);
    cout<<setw(20)<<"Sale Id"<<setw(20)<<"Product Name"<<setw(20)<<"Customer ID"<<setw(20)<<"Quantity"<<setw(20)<<"Price"<<setw(20)<<"Amount"<<setw(20)<<"Date"<<setw(20)<<"\n";
    while((row = mysql_fetch_row(res))){
        cout<<setw(20)<<row[0]<<setw(20)<<row[2]<<setw(20)<<row[3]<<setw(20)<<row[4]<<setw(20)<<row[5]<<setw(20)<<row[6]<<setw(20)<<row[7]<<setw(20)<<"\n";
    }
}


void Administrator::printAllUsersDetails(User* users, int& numberOfUsers){
    cout<<setw(20)<<"\n"<<setw(20)<<"Username"<<setw(20)<<"First Name"<<setw(20)<<"Last Name"<<setw(20)<<"Age"<<setw(20)<<"Address"<<setw(20)<<"Wallet balance"<<setw(20)<<"\n";
    int i;
    for(i=0;i<numberOfUsers;i++){

        users[i].printDetails();
    }

}


void Administrator::addUser(User* users,int& numberOfUsers){
    string firstName,lastName,address;
    int age;
    string username,password;
    cout<<"Enter the details of the user : \nEnter the first Name : ";
    cin>>firstName;

    cout<<"Enter the last name : ";
    cin>>lastName;

    cout<<"Enter the age : ";
    cin>>age;

    cout<<"Enter the address : ";
    cin>>address;

    cout<<"Enter the username : ";
    cin>>username;

    cout<<"Enter the password : ";
    cin>>password;

    //first insert in db



    stringstream ps;

    string query;
    int qstate;
    const char* q;

    ps<<"INSERT INTO users(user_name,user_password,user_type,user_first_name,user_last_name,user_age,user_address,user_wallet_balance) VALUES('"<<username<<"','"<<password<<"','"<<1<<"','"<<firstName<<"','"<<lastName<<"','"<<age<<"','"<<address<<"','"<<100<<"')";
    query = ps.str();
    q = query.c_str();
    qstate = mysql_query(connection,q);

    if(qstate != 0){
        cout<<"Insertion unsuccessful as query failed !\n";
        exit(6);
    }


    stringstream ss;


    ss<<"SELECT user_id FROM users WHERE user_name = '"<<username<<"'";
    query = ss.str();
    q = query.c_str();
    qstate = mysql_query(connection,q);

    if(qstate != 0){
        cout<<"Getting id unsuccessful as query failed !\n";
        exit(7);
    }

    res = mysql_store_result(connection);
    row = mysql_fetch_row(res);

    users[numberOfUsers++].setUserDetails(stoi(row[0]),firstName,lastName,age,address,username,password,100);

    cout<<"\nUser successfully added !\n";
}
void Administrator::deleteUser(User* users,int& numberOfUsers){
    printAllUsersDetails(users,numberOfUsers);
    int id;
    cout<<"Enter the user_id of the user you want to delete : ";
    cin>>id;

    int i;
    int index = -1;
    for(i=0;i<numberOfUsers;i++){
        if(users[i].getUserID() == id){
            index = i;
            break;
        }
    }

    if(index == -1){
        cout<<"The given ID is invalid !\n";
        return;
    }

    cout<<"The selected user is :\n";
    cout<<setw(20)<<"\n"<<setw(20)<<"Username"<<setw(20)<<"First Name"<<setw(20)<<"Last Name"<<setw(20)<<"Age"<<setw(20)<<"Address"<<setw(20)<<"Wallet balance"<<setw(20)<<"\n";
    users[index].printDetails();

    int choice;
    cout<<"\nEnter y/Y to confirm deletion, n/N to abort operation !\n";
    cin>>choice;
    choice = tolower(choice);

    if(choice != 'y'){
        cout<<"Operation aborted !\n";
        return;
    }
    else if(choice == 'y'){
        users[index].setState(0);
        stringstream ss;
        ss << "DELETE FROM users WHERE user_id = " <<id;
        string query = ss.str();
        const char* s = query.c_str();
        int qstate = mysql_query(connection,s);

        if(qstate != 0){
            cout<<"Deletion unsuccessful as query failed !\n";
            exit(7);
        }

        cout<<"\nUser successfully deleted !\n";


    }
}




void initializeArrays(User* users,int& numberOfUsers,Administrator& admin,Product* products,int& numberOfProducts){

    stringstream us,as,ps;

    string query;
    int qstate;
    const char* q;


    as<<"SELECT * FROM users WHERE user_type = '0' ";
    query = as.str();
    q = query.c_str();
    qstate = mysql_query(connection,q);

    if(qstate != 0){
        cout<<"Initialization unsuccessful as query failed !\n";
        exit(1);
    }
    res = mysql_store_result(connection);
    row = mysql_fetch_row(res);
    admin.setAdministratorDetails(stoi(row[0]),row[4],row[5],stoi(row[6]),row[7],row[1],row[2]);



    us<<"SELECT * FROM users WHERE user_type = '1' ";
    query = us.str();
    q = query.c_str();
    qstate = mysql_query(connection,q);

    if(qstate != 0){
        cout<<"Initialization unsuccessful as query failed !\n";
        exit(1);
    }

    res = mysql_store_result(connection);
    while((row = mysql_fetch_row(res))){
        users[numberOfUsers++].setUserDetails(stoi(row[0]),row[4],row[5],stoi(row[6]),row[7],row[1],row[2],stoi(row[8]));
    }



    ps<<"SELECT * FROM products";
    query = ps.str();
    q = query.c_str();
    qstate = mysql_query(connection,q);

    if(qstate != 0){
        cout<<"Initialization unsuccessful as query failed !\n";
        exit(1);
    }

    res = mysql_store_result(connection);
    while((row = mysql_fetch_row(res))){
        products[numberOfProducts++].setProductDetails(stoi(row[0]),row[1],stof(row[2]),stoi(row[4]),stoi(row[3]),stoi(row[5]),stoi(row[6]),stoi(row[7]));
    }




}



int main(){

    connection = mysql_init(0);
    connection = mysql_real_connect(connection,"192.168.43.68","admin","admin","canteen",0,NULL,0);
    if(connection){
        cout<<"Connected to the database!\n";
    }
    else{
        cout<<"Not connected to the database!\n";
        exit(404);
    }
    User users[MAX_NO_OF_USERS];
    Administrator admin;
    Product products[MAX_NO_OF_PRODUCTS];

    int numberOfUsers = 0,numberOfProducts = 0;

    initializeArrays(users,numberOfUsers,admin,products,numberOfProducts);

    //CONSOLE FOR USER/ADMINISTRATOR

    //we have the arrays with all users, admin and products

    int choice;

    while(1){
        cout<<"LOGIN\n\n1.USER\n\n2.ADMINISTRATOR\nEnter your choice : ";
        cin>>choice;

        if(choice == 1){
            string username;
            cout<<"Enter the user's user name : ";
            cin>>username;

            string password;

            int i;
            int index = -1;
            for(i=0;i<numberOfUsers;i++){
                if(users[i].getUsername() == username){
                    index = i;
                    break;
                }
            }

            if(index == -1){
                cout<<"User not found!\nTry again!\n";
                continue;
            }

            cout<<"Enter the password : ";
            cin>>password;

            if(users[index].getPassword() != password){
                cout<<"Wrong password !\nTry again\n";
                continue;
            }

            //users[index] is the required user.
            cout<<"\nYour details : \n";
            cout<<setw(20)<<"\n"<<setw(20)<<"Username"<<setw(20)<<"First Name"<<setw(20)<<"Last Name"<<setw(20)<<"Age"<<setw(20)<<"Address"<<setw(20)<<"Wallet balance"<<setw(20)<<"\n";

            users[index].printDetails();
            int userChoice;

            while(1){
                cout<<"\n1. Purchase an item\n2. Add money to the wallet\n3. Get history\n4. Exit \nEnter your choice : ";

                cin>>userChoice;

                switch(userChoice){
                case 1:
                    users[index].purchaseProducts(products,numberOfProducts);
                    break;

                case 2:
                    int amount;
                    cout<<"Enter the amount you want to add : \n";
                    cin>>amount;

                    users[index].addMoney(amount);
                    break;

                case 3:
                    users[index].getHistory();
                    break;

                case 4:
                    cout<<"Thank you!\n";
                    exit(406);

                }

            }
        }

        //ADMINISTRATOR LOGIN

        else if(choice == 2){
            //admin

            string username;
            cout<<"Enter the administrator's user name : ";
            cin>>username;

            string password;
            cout<<"Enter the password : ";
            cin>>password;

            if(admin.getUsername() != username || admin.getPassword() != password){
                cout<<"Credentials don't match !\n";
                continue;
            }

            while(1){
                cout<<"Enter the operation you want to perform :\n";


                int adminChoice;
                cout<<"1. Add a product\n2. Modify a particular product\n3. Delete a product\n4. View all products\n5. Add a user\n6. Delete a user\n7. Print all users' details\n8. Print sales report for particular time period\n9. Exit\n";
                cin>>adminChoice;
                switch(adminChoice){

                case 1:
                    admin.addProduct(products,numberOfProducts);
                    break;

                case 2:
                    admin.modifyProduct(products,numberOfProducts);
                    break;

                case 3:
                    admin.deleteProduct(products,numberOfProducts);
                    break;

                case 4:
                    admin.printAllProductsDetails(products,numberOfProducts);
                    break;

                case 5:
                    admin.addUser(users,numberOfUsers);
                    break;

                case 6:
                    admin.deleteUser(users,numberOfUsers);
                    break;

                case 7:
                    admin.printAllUsersDetails(users,numberOfUsers);
                    break;
                case 8:
                    admin.printReport();
                    break;

                case 9:
                    cout<<"Thank you !\n";
                    exit(405);

                default:
                    cout<<"Invalid choice !\nTry again!\n";
                    break;
                }
            }

        }
        else{
        cout<<"Invalid choice !\n";
        continue;
        }
    }


    return 0;

}
