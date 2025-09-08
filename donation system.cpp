#include<iostream>
#include<fstream>
#include<string>
#include<Windows.h>
using namespace std;
// Structure for storing user information
struct User 
{
    string username;
    string password;
};
// Base class for all donation pages
class DonationPage 
{
	public:
    	virtual void displayMenu() = 0; // Pure virtual function for displaying the menu
};
// Class for the introductory page
class IntroPage 
{
	private:
	    User* users;
	    int userCount;

    	void loadUsers() 
		{
        	ifstream infile("users.txt");
        	if (infile.is_open()) 
			{
            	while(infile>>users[userCount].username>>users[userCount].password) 
				{
                	userCount++;
            	}
            	infile.close();
        	}
    	}

    	void saveUsers() 
		{
        	ofstream outfile("users.txt");
        	if (outfile.is_open()) 
			{
            	for (int i=0; i<userCount; i++) 
				{
                	outfile<<users[i].username<<" "<<users[i].password<<"\n";
            	}
            	outfile.close();
        	}
    	}

		public:
    		IntroPage() : users(new User[100]), userCount(0) 
			{
        		loadUsers();
    		}

    		~IntroPage() 
			{
        		saveUsers();
        		delete[] users;
    		}

    		bool login() 
			{
        		string username, password;
		        cout<<"Enter username: ";
		        cin>>username;
		        cout<<"Enter password: ";
		        cin>>password;
		        for (int i=0; i<userCount; i++) 
				{
		            if (users[i].username==username && users[i].password==password) 
					{
		                cout<<"Login successful!\n";
		                showLoadingBar();
		                system("CLS");
		                return true;
		            }
        		}
		        cout << "Invalid credentials. Please try again.\n";
		        return false;
		    }

    		void signup() 
			{
		        string username, password;
		        cout<<"Enter new username: ";
		        cin>>username;
		        cout<<"Enter new password: ";
		        cin>>password;
		        users[userCount++] = { username, password };
		        cout<<"Signup successful!\n";
        		system("CLS");
    		}

    		void showLoadingBar() 
			{
	        	cout << "Loading";
	        	for (int i=0; i<10; ++i) 
				{
	            	cout << ".";
	            	Sleep(300); // sleep for 300 milliseconds
	        	}
        		cout<<"\n\n\t\t\t";
				char x=219;
				cout<<"\t\t\t";
				for (int i=0; i<=27; i++) 
				{
					cout<<x;
					for (int i=0; i<10000000; i++);
					}
				system("cls");
        		cout<<"\n";
    		}

    		void display() 
			{
			    int choice;
			    while (true) 
				{
			        cout<<"Welcome to the Donation System!\n";
			        cout<<"1. Login\n2. Signup\n";
			        cin>>choice;
			        system("CLS");
			        if (choice==1) 
					{
			            if (login()) break;
            		} 
					else if (choice==2) 
					{
                		signup();
            		} 
					else 
					{
                		cout << "Invalid choice. Please try again.\n";
            		}
        		}
    		}
};

// Class for Blood Donation page
class BloodDonationPage : public DonationPage 
{
	private:
    	struct Donor 
		{
	        string name;
	        int age;
	        string bloodType;
	    };

    	struct Recipient 
		{
	        string name;
	        int age;
	        string bloodType;
	    };

	    Donor* donors;
	    int donorCount;
	    Recipient* recipients;
	    int recipientCount;

    	void loadDonors() 
		{
		    ifstream infile("blood_donors.txt");
		    if (infile.is_open()) 
			{
		        while (infile>>donors[donorCount].name>>donors[donorCount].age>>donors[donorCount].bloodType) 
				{
                	donorCount++;
            	}
            	infile.close();
        	}
    	}

    	void saveDonors() 
		{
        	ofstream outfile("blood_donors.txt");
        	if (outfile.is_open()) 
			{
            	for (int i=0; i<donorCount; i++) 
				{
                	outfile << donors[i].name << " " << donors[i].age << " " << donors[i].bloodType << "\n";
            	}
            	outfile.close();
        	}
    	}

    	void loadRecipients() 
		{
        	ifstream infile("blood_recipients.txt");
        	if (infile.is_open()) 
			{
            	while (infile>>recipients[recipientCount].name>>recipients[recipientCount].age>>recipients[recipientCount].bloodType) 
				{
                	recipientCount++;
            	}
            	infile.close();
        	}
    	}

    	void saveRecipients() 
		{
        	ofstream outfile("blood_recipients.txt");
        	if (outfile.is_open()) 
			{
            	for (int i=0; i<recipientCount; i++) 
				{
                	outfile<<recipients[i].name<<" "<<recipients[i].age<<" "<< recipients[i].bloodType<<"\n";
            	}
            	outfile.close();
        	}
    	}

		public:
    		BloodDonationPage() : donors(new Donor[100]), donorCount(0), recipients(new Recipient[100]), recipientCount(0) 
			{
        		loadDonors();
        		loadRecipients();
    		}

    		~BloodDonationPage() 
			{
		        saveDonors();
		        saveRecipients();
		        delete[] donors;
		        delete[] recipients;
		    }

    		void donateBlood() 
			{
		        Donor newDonor;
		        cout<<"Enter your name: ";
		        cin>>newDonor.name;
		        cout<<"Enter your age: ";
		        cin>>newDonor.age;
		        cout<<"Enter your blood type: ";
		        cin>>newDonor.bloodType;
		        donors[donorCount++]=newDonor;
		        cout<<"Thank you for your blood donation!\n";
		    }

		    void getBlood() 
			{
		        Recipient newRecipient;
		        cout<<"Enter your name: ";
		        cin>>newRecipient.name;
		        cout<<"Enter your age: ";
		        cin>>newRecipient.age;
		        cout<<"Enter your blood type: ";
		        cin>>newRecipient.bloodType;
		        recipients[recipientCount++] = newRecipient;
		        cout<<"Your blood request has been recorded!\n";
		    }

		    void displayMenu() override 
			{
		        int choice;
		        cout<<"Blood Donation Menu:\n";
		        cout<<"1. Donate Blood\n2. Get Blood\n";
		        cin>>choice;
		        system("CLS");
		        if (choice == 1) 
				{
		            donateBlood();
		        } 
				else if (choice == 2) 
				{
		            getBlood();
		        } 
				else 
				{
            		cout<<"Invalid choice.\n";
        		}
    		}
};

// Class for Cloth Donation page
class ClothDonationPage : public DonationPage 
{
	private:
    	struct Donor 
		{
	        string name;
	        string clothType;
	        int quantity;
	    };

    	struct Recipient 
		{
	        string name;
	        string clothType;
	        int quantity;
	    };

		Donor* donors;
		int donorCount;
		Recipient* recipients;
		int recipientCount;

    	void loadDonors() 
		{
        	ifstream infile("cloth_donors.txt");
        	if (infile.is_open()) 
			{
            	while (infile>>donors[donorCount].name>>donors[donorCount].clothType>>donors[donorCount].quantity) 
				{
                	donorCount++;
            	}
            	infile.close();
        	}
    	}

    	void saveDonors() 
		{
        	ofstream outfile("cloth_donors.txt");
        	if (outfile.is_open()) 
			{
            	for (int i=0; i<donorCount; i++) 
				{
                	outfile<<donors[i].name<<" "<<donors[i].clothType<<" "<<donors[i].quantity<<"\n";
            	}
            	outfile.close();
        	}
    	}

    	void loadRecipients() 
		{
        	ifstream infile("cloth_recipients.txt");
        	if (infile.is_open()) 
			{
            	while (infile>>recipients[recipientCount].name>>recipients[recipientCount].clothType>>recipients[recipientCount].quantity) 
				{
                	recipientCount++;            
				}
            	infile.close();
        	}
    	}

    	void saveRecipients() 
		{
        	ofstream outfile("cloth_recipients.txt");
       		if (outfile.is_open()) 
			   {
            for (int i = 0; i < recipientCount; i++) {
                outfile << recipients[i].name << " " << recipients[i].clothType << " " << recipients[i].quantity << "\n";
            }
            outfile.close();
        }
    }

public:
    ClothDonationPage() : donors(new Donor[100]), donorCount(0), recipients(new Recipient[100]), recipientCount(0) {
        loadDonors();
        loadRecipients();
    }

    ~ClothDonationPage() {
        saveDonors();
        saveRecipients();
        delete[] donors;
        delete[] recipients;
    }

    void donateCloth() {
        Donor newDonor;
        cout << "Enter your name: ";
        cin >> newDonor.name;
        cout << "Enter type of cloth: ";
        cin >> newDonor.clothType;
        cout << "Enter quantity: ";
        cin >> newDonor.quantity;
        donors[donorCount++] = newDonor;
        cout << "Thank you for your cloth donation!\n";
    }

    void getCloth() {
        Recipient newRecipient;
        cout << "Enter your name: ";
        cin >> newRecipient.name;
        cout << "Enter type of cloth: ";
        cin >> newRecipient.clothType;
        cout << "Enter quantity: ";
        cin >> newRecipient.quantity;
        recipients[recipientCount++] = newRecipient;
        cout << "Your cloth request has been recorded!\n";
    }

    void displayMenu() override {
        int choice;
        cout << "Cloth Donation Menu:\n";
        cout << "1. Donate Clothes\n2. Get Clothes\n";
        cin >> choice;
        system("CLS");
        if (choice == 1) {
            donateCloth();
        } else if (choice == 2) {
            getCloth();
        } else {
            cout << "Invalid choice.\n";
        }
    }
};

// Class for Money Donation page
class MoneyDonationPage : public DonationPage {
private:
    struct Donor {
        string name;
        double amount;
    };

    Donor* donors;
    int donorCount;

    void loadDonors() {
        ifstream infile("money_donors.txt");
        if (infile.is_open()) {
            while (infile >> donors[donorCount].name >> donors[donorCount].amount) {
                donorCount++;
            }
            infile.close();
        }
    }

    void saveDonors() {
        ofstream outfile("money_donors.txt");
        if (outfile.is_open()) {
            for (int i = 0; i < donorCount; i++) {
                outfile << donors[i].name << " " << donors[i].amount << "\n";
            }
            outfile.close();
        }
    }

public:
    MoneyDonationPage() : donors(new Donor[100]), donorCount(0) {
        loadDonors();
    }

    ~MoneyDonationPage() {
        saveDonors();
        delete[] donors;
    }

    void donateMoney() {
        Donor newDonor;
        cout << "Enter your name: ";
        cin >> newDonor.name;
        cout << "Enter amount: ";
        cin >> newDonor.amount;
        donors[donorCount++] = newDonor;
        cout << "Thank you for your donation!\n";
    }

    void displayMenu() override {
        donateMoney();
    }
};

// Class for Thank You page
class ThankYouPage {
public:
    void display() {
        cout << "Thank you for your contribution!\n";
        cout << "Your generosity is greatly appreciated.\n";
    }
};

// Class for main Donation System
class DonationSystem {
private:
    IntroPage introPage;
    BloodDonationPage bloodDonationPage;
    ClothDonationPage clothDonationPage;
    MoneyDonationPage moneyDonationPage;
    ThankYouPage thankYouPage;

public:
    void start() {
        introPage.display();
        int choice;
        while (true) {
            cout << "Donation Menu:\n";
            cout << "1. Blood Donation\n2. Cloth Donation\n3. Charity\n";
            cin >> choice;
            system("CLS");
            switch (choice) {
                case 1:
                    bloodDonationPage.displayMenu();
                    break;
                case 2:
                    clothDonationPage.displayMenu();
                    break;
                case 3:
                    moneyDonationPage.displayMenu();
                    break;
                default:
                    cout << "Invalid choice. Please try again.\n";
                    continue;
            }
            break;
        }
        thankYouPage.display();
    }
};

int main() {
    DonationSystem system;
    system.start();
    return 0;
}
