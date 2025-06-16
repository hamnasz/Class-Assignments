#include <iostream>
using namespace std;

class TUFMAP {
public:
    void displayRoomSchedule(string roomNo) {
        string rooms[] = {"101", "102", "103", "104", "105", "106", "107", "108", "109", "110", "201", "202", "203", "204", "205", "206", "207", "208", "209", "210"};
        string times[] = {"8-9", "9-10", "10-11", "11-12", "12-1", "1-2", "2-3", "3-4", "4-5"};
        string teachers[][9] = {
           {"Mr Ahmed", "Ms Fatima", "Mr Ali", "Ms Aisha", "Mr Omar", "Mr Safiya", "Mr Zaid", "Ms Hadiya", "Ms Amirah"},
		   {"Mr Abdullah", "Ms Mariam", "Mr Zakariya", "Ms Sumaya", "Mr Ibrahim", "Ms Hafsah", "Mr Salman", "Ms Ayesha", "Mr Jibril"},
		   {"Mr Ahmad", "Ms Layla", "Mr Hamza", "Ms Ayesha", "Mr Talha", "Ms Khadija", "Mr Mustafa", "Ms Fatima", "Mr Zahid"},
		   {"Ms Samiya", "Mr Ahmad", "Ms Ayesha", "Mr Taha", "Ms Aliya", "Mr Rashid", "Ms Nadia", "Mr Saad", "Ms Ayesha"},
		   {"Ms Zahra", "Mr Khalid", "Ms Amina", "Mr Rizwan", "Ms Farah", "Mr Omar", "Ms Saba", "Mr Ahsan", "Ms Nadia"},
		   {"Mr Musa", "Ms Amna", "Mr Saeed", "Ms Zainab", "Mr Raza", "Ms Hina", "Mr Talha", "Ms Nadia", "Mr Usman"},
		   {"Mr Abdul Rahman", "Ms Sarah", "Mr Khalid", "Ms Ayesha", "Mr Asad", "Ms Maryam", "Mr Yasir", "Ms Zainab", "Mr Naveed"},
		   {"Mr Sajid", "Ms Fatima", "Mr Yousuf", "Ms Hira", "Mr Ismail", "Ms Kiran", "Mr Zubair", "Ms Saba", "Mr Ali"},
		   {"Ms Ayesha", "Mr Usman", "Ms Saima", "Mr Zain", "Mr Tariq", "Ms Nazia", "Mr Faisal", "Ms Bushra", "Mr Zafar"},
		   {"Mr Hassan", "Ms Maria", "Mr Asad", "Ms Ayesha", "Mr Iqbal", "Ms Samina", "Mr Rashid", "Ms Nida", "Mr Mujtaba"},
		   {"Mr Ibrahim", "Ms Sana", "Mr Waqas", "Ms Ayesha", "Mr Zahid", "Ms Naila", "Mr Zafar", "Ms Nazia", "Mr Arif"},
		   {"Mr Junaid", "Ms Sadia", "Mr Kamran", "Ms Ayesha", "Mr Hassan", "Ms Shabana", "Mr Rizwan", "Ms Sadia", "Mr Nasir"},
		   {"Mr Khalid", "Ms Bushra", "Mr Younus", "Ms Ayesha", "Mr Raheem", "Ms Seema", "Mr Asif", "Ms Saba", "Mr Waseem"},
		   {"Mr Naeem", "Ms Saba", "Mr Nadir", "Ms Ayesha", "Mr Yasin", "Ms Rukhsana", "Mr Adil", "Ms Samina", "Mr Aamir"},
		   {"Mr Imran", "Ms Farah", "Mr Mujahid", "Ms Ayesha", "Mr Ahsan", "Ms Najma", "Mr Nadeem", "Ms Saba", "Mr Adnan"},
		   {"Mr Saad", "Ms Zainab", "Mr Munawar", "Ms Ayesha", "Mr Zulfiqar", "Ms Aqsa", "Mr Javed", "Ms Saima", "Mr Fahad"},
		   {"Mr Sohail", "Ms Nazia", "Mr Sarwar", "Ms Ayesha", "Mr Usman", "Ms Rabia", "Mr Amin", "Ms Saba", "Mr Safdar"},
		   {"Mr Aamir", "Ms Hira", "Mr Anwar", "Ms Ayesha", "Mr Rashid", "Ms Sadia", "Mr Usman", "Ms Saba", "Mr Faisal"},
		   {"Mr Zubair", "Ms Saba", "Mr Mujahid", "Ms Ayesha", "Mr Jameel", "Ms Sadia", "Mr Imran", "Ms Nadia", "Mr Arshad"},
		   {"Mr Usman", "Ms Zara", "Mr Munir", "Ms Ayesha", "Mr Aslam", "Ms Sadia", "Mr Tariq", "Ms Saba", "Mr Noman"}
        };
        string classes[][9] = {
            {"OOP", "Db", "Calc", "Phy", "OOP", "Db", "Calc", "Phy", "OOP"},
			{"AI", "DS", "LA", "CN", "AI", "DS", "LA", "CN", "AI"},
			{"DS", "ML", "DSA", "SE", "DS", "ML", "DSA", "SE", "DS"},
			{"OS", "DM", "ToC", "WD", "OS", "DM", "ToC", "WD", "OS"},
			{"Db", "Algo", "LA", "DS", "Db", "Algo", "LA", "DS", "Db"},
			{"Phy", "Calc", "OOP", "Db", "Phy", "Calc", "OOP", "Db", "Phy"},
			{"Calc", "LA", "DS", "AI", "Calc", "LA", "DS", "AI", "Calc"},
			{"OOP", "Db", "Calc", "Phy", "OOP", "Db", "Calc", "Phy", "OOP"},
			{"DS", "ML", "Algo", "SE", "DS", "ML", "Algo", "SE", "DS"},
			{"AI", "DS", "LA", "CN", "AI", "DS", "LA", "CN", "AI"},
			{"Db", "Algo", "LA", "DS", "Db", "Algo", "LA", "DS", "Db"},
			{"Phy", "Calc", "OOP", "Db", "Phy", "Calc", "OOP", "Db", "Phy"},
			{"Calc", "LA", "DS", "AI", "Calc", "LA", "DS", "AI", "Calc"},
			{"OOP", "Db", "Calc", "Phy", "OOP", "Db", "Calc", "Phy", "OOP"},
			{"DS", "ML", "Algo", "SE", "DS", "ML", "Algo", "SE", "DS"},
			{"AI", "DS", "LA", "CN", "AI", "DS", "LA", "CN", "AI"},
			{"Db", "Algo", "LA", "DS", "Db", "Algo", "LA", "DS", "Db"},
			{"Phy", "Calc", "OOP", "Db", "Phy", "Calc", "OOP", "Db", "Phy"},
			{"Calc", "LA", "DS", "AI", "Calc", "LA", "DS", "AI", "Calc"},
			{"OOP", "Db", "Calc", "Phy", "OOP", "Db", "Calc", "Phy", "OOP"}
        };
        string departments[][9] = {
            {"BS-CS-A", "BS-IT-D", "BS-SE-A", "BS-EE-D", "BS-CS-B", "BS-IT-D", "BS-SE-B", "BS-EE-D", "BS-CS-C"},
			{"BS-AI-A", "BS-CY-A", "BS-DS-A", "BS-BME-A", "BS-AI-B", "BS-CY-B", "BS-DS-B", "BS-BME-D", "BS-AI-C"},
			{"BS-DS-C", "BS-IT-A", "BS-CS-A", "BS-SE-A", "BS-DS-B", "BS-IT-B", "BS-CS-B", "BS-SE-B", "BS-DS-C"},
			{"BS-CY-A", "BS-CS-A", "BS-AI-A", "BS-SE-A", "BS-CY-B", "BS-CS-B", "BS-AI-B", "BS-SE-B", "BS-CY-C"},
			{"BS-IT-A", "BS-CS-A", "BS-AI-A", "BS-DS-A", "BS-IT-B", "BS-CS-B", "BS-AI-B", "BS-DS-D", "BS-IT-C"},
			{"BS-SE-A", "BS-CS-E", "BS-IT-A", "BS-AI-A", "BS-SE-B", "BS-CS-B", "BS-IT-B", "BS-AI-B", "BS-SE-C"},
			{"BS-CS-A", "BS-IT-A", "BS-SE-F", "BS-AI-A", "BS-CS-D", "BS-IT-B", "BS-SE-C", "BS-AI-B", "BS-CS-C"},
			{"BS-EE-A", "BS-CS-A", "BS-IT-C", "BS-SE-A", "BS-EE-B", "BS-CS-B", "BS-IT-B", "BS-SE-B", "BS-EE-C"},
			{"BS-IT-A", "BS-CS-D", "BS-DS-A", "BS-AI-C", "BS-IT-B", "BS-CS-B", "BS-DS-B", "BS-AI-B", "BS-IT-C"},
			{"BS-SE-A", "BS-CS-A", "BS-IT-A", "BS-AI-A", "BS-SE-B", "BS-CS-B", "BS-IT-B", "BS-AI-B", "BS-SE-C"},
			{"BS-CS-A", "BS-IT-A", "BS-SE-A", "BS-DS-A", "BS-CS-B", "BS-IT-D", "BS-SE-B", "BS-DS-B", "BS-CS-C"},
			{"BS-EE-A", "BS-CS-A", "BS-IT-D", "BS-SE-A", "BS-EE-B", "BS-CS-B", "BS-IT-B", "BS-SE-B", "BS-EE-C"},
			{"BS-IT-A", "BS-CS-A", "BS-DS-A", "BS-AI-A", "BS-IT-B", "BS-CS-B", "BS-DS-B", "BS-AI-B", "BS-IT-C"},
			{"BS-SE-A", "BS-CS-A", "BS-IT-A", "BS-AI-A", "BS-SE-B", "BS-CS-B", "BS-IT-B", "BS-AI-B", "BS-SE-C"},
			{"BS-CS-A", "BS-IT-A", "BS-SE-A", "BS-DS-A", "BS-CS-B", "BS-IT-B", "BS-SE-B", "BS-DS-B", "BS-CS-C"},
			{"BS-EE-A", "BS-CS-A", "BS-IT-A", "BS-SE-A", "BS-EE-B", "BS-CS-B", "BS-IT-B", "BS-SE-B", "BS-EE-C"},
			{"BS-IT-A", "BS-CS-A", "BS-DS-A", "BS-AI-A", "BS-IT-B", "BS-CS-B", "BS-DS-B", "BS-AI-B", "BS-IT-C"},
			{"BS-SE-A", "BS-CS-A", "BS-IT-A", "BS-AI-A", "BS-SE-B", "BS-CS-B", "BS-IT-B", "BS-AI-B", "BS-SE-C"},
			{"BS-CS-A", "BS-IT-A", "BS-SE-A", "BS-DS-A", "BS-CS-B", "BS-IT-B", "BS-SE-B", "BS-DS-B", "BS-CS-C"},
			{"BS-EE-A", "BS-CS-A", "BS-IT-A", "BS-SE-A", "BS-EE-B", "BS-CS-B", "BS-IT-B", "BS-SE-B", "BS-EE-C"}
        };
		 string semesters[][9] = {
            {"1st", "2nd", "3rd", "4th", "5th", "6th", "7th", "8th", "1st"},
			{"2nd", "3rd", "4th", "5th", "6th", "7th", "8th", "1st", "2nd"},
			{"3rd", "4th", "5th", "6th", "7th", "8th", "1st", "2nd", "3rd"},
			{"4th", "5th", "6th", "7th", "8th", "1st", "2nd", "3rd", "4th"},
			{"5th", "6th", "7th", "8th", "1st", "2nd", "3rd", "4th", "5th"},
			{"6th", "7th", "8th", "1st", "2nd", "3rd", "4th", "5th", "6th"},
			{"7th", "8th", "1st", "2nd", "3rd", "4th", "5th", "6th", "7th"},
			{"8th", "1st", "2nd", "3rd", "4th", "5th", "6th", "7th", "8th"},
			{"1st", "2nd", "3rd", "4th", "5th", "6th", "7th", "8th", "1st"},
			{"2nd", "3rd", "4th", "5th", "6th", "7th", "8th", "1st", "2nd"},
			{"3rd", "4th", "5th", "6th", "7th", "8th", "1st", "2nd", "3rd"},
			{"4th", "5th", "6th", "7th", "8th", "1st", "2nd", "3rd", "4th"},
			{"5th", "6th", "7th", "8th", "1st", "2nd", "3rd", "4th", "5th"},
			{"6th", "7th", "8th", "1st", "2nd", "3rd", "4th", "5th", "6th"},
			{"7th", "8th", "1st", "2nd", "3rd", "4th", "5th", "6th", "7th"},
			{"8th", "1st", "2nd", "3rd", "4th", "5th", "6th", "7th", "8th"},
			{"1st", "2nd", "3rd", "4th", "5th", "6th", "7th", "8th", "1st"},
			{"2nd", "3rd", "4th", "5th", "6th", "7th", "8th", "1st", "2nd"},
			{"3rd", "4th", "5th", "6th", "7th", "8th", "1st", "2nd", "3rd"},
			{"4th", "5th", "6th", "7th", "8th", "1st", "2nd", "3rd", "4th"}
        };
        for (int i = 0; i < 20; i++) {
            if (rooms[i] == roomNo) {
                cout << "Schedule for Room " << roomNo << ":\n";
                cout<<"\n\tTime       Teacher       Subjects       Department       Semester"<<endl;
                for (int j = 0; j < 9; j++) {
                    cout <<"\t"<< times[j] <<"\t   "<< teachers[i][j]  <<"\t   " << classes[i][j]  <<"\t\t"<< departments[i][j] <<"\t\t  "<< semesters[i][j]<< endl;
                }
                return;
            }
        }
        cout << "Room not found." << endl;
    }

    void displayRoomTimeSchedule(string roomNo, string timeSlot) {
        string rooms[] = {"101", "102", "103", "104", "105", "106", "107", "108", "109", "110", "201", "202", "203", "204", "205", "206", "207", "208", "209", "210"};
        string times[] = {"8-9", "9-10", "10-11", "11-12", "12-1", "1-2", "2-3", "3-4", "4-5"};
        string teachers[][9] = {
           {"Mr Ahmed", "Ms Fatima", "Mr Ali", "Ms Aisha", "Mr Omar", "Mr Safiya", "Mr Zaid", "Ms Hadiya", "Ms Amirah"},
		   {"Mr Abdullah", "Ms Mariam", "Mr Zakariya", "Ms Sumaya", "Mr Ibrahim", "Ms Hafsah", "Mr Salman", "Ms Ayesha", "Mr Jibril"},
		   {"Mr Ahmad", "Ms Layla", "Mr Hamza", "Ms Ayesha", "Mr Talha", "Ms Khadija", "Mr Mustafa", "Ms Fatima", "Mr Zahid"},
		   {"Ms Samiya", "Mr Ahmad", "Ms Ayesha", "Mr Taha", "Ms Aliya", "Mr Rashid", "Ms Nadia", "Mr Saad", "Ms Ayesha"},
		   {"Ms Zahra", "Mr Khalid", "Ms Amina", "Mr Rizwan", "Ms Farah", "Mr Omar", "Ms Saba", "Mr Ahsan", "Ms Nadia"},
		   {"Mr Musa", "Ms Amna", "Mr Saeed", "Ms Zainab", "Mr Raza", "Ms Hina", "Mr Talha", "Ms Nadia", "Mr Usman"},
		   {"Mr Abdul Rahman", "Ms Sarah", "Mr Khalid", "Ms Ayesha", "Mr Asad", "Ms Maryam", "Mr Yasir", "Ms Zainab", "Mr Naveed"},
		   {"Mr Sajid", "Ms Fatima", "Mr Yousuf", "Ms Hira", "Mr Ismail", "Ms Kiran", "Mr Zubair", "Ms Saba", "Mr Ali"},
		   {"Ms Ayesha", "Mr Usman", "Ms Saima", "Mr Zain", "Mr Tariq", "Ms Nazia", "Mr Faisal", "Ms Bushra", "Mr Zafar"},
		   {"Mr Hassan", "Ms Maria", "Mr Asad", "Ms Ayesha", "Mr Iqbal", "Ms Samina", "Mr Rashid", "Ms Nida", "Mr Mujtaba"},
		   {"Mr Ibrahim", "Ms Sana", "Mr Waqas", "Ms Ayesha", "Mr Zahid", "Ms Naila", "Mr Zafar", "Ms Nazia", "Mr Arif"},
		   {"Mr Junaid", "Ms Sadia", "Mr Kamran", "Ms Ayesha", "Mr Hassan", "Ms Shabana", "Mr Rizwan", "Ms Sadia", "Mr Nasir"},
		   {"Mr Khalid", "Ms Bushra", "Mr Younus", "Ms Ayesha", "Mr Raheem", "Ms Seema", "Mr Asif", "Ms Saba", "Mr Waseem"},
		   {"Mr Naeem", "Ms Saba", "Mr Nadir", "Ms Ayesha", "Mr Yasin", "Ms Rukhsana", "Mr Adil", "Ms Samina", "Mr Aamir"},
		   {"Mr Imran", "Ms Farah", "Mr Mujahid", "Ms Ayesha", "Mr Ahsan", "Ms Najma", "Mr Nadeem", "Ms Saba", "Mr Adnan"},
		   {"Mr Saad", "Ms Zainab", "Mr Munawar", "Ms Ayesha", "Mr Zulfiqar", "Ms Aqsa", "Mr Javed", "Ms Saima", "Mr Fahad"},
		   {"Mr Sohail", "Ms Nazia", "Mr Sarwar", "Ms Ayesha", "Mr Usman", "Ms Rabia", "Mr Amin", "Ms Saba", "Mr Safdar"},
		   {"Mr Aamir", "Ms Hira", "Mr Anwar", "Ms Ayesha", "Mr Rashid", "Ms Sadia", "Mr Usman", "Ms Saba", "Mr Faisal"},
		   {"Mr Zubair", "Ms Saba", "Mr Mujahid", "Ms Ayesha", "Mr Jameel", "Ms Sadia", "Mr Imran", "Ms Nadia", "Mr Arshad"},
		   {"Mr Usman", "Ms Zara", "Mr Munir", "Ms Ayesha", "Mr Aslam", "Ms Sadia", "Mr Tariq", "Ms Saba", "Mr Noman"}
        };
        string classes[][9] = {
           {"OOP", "Db", "Calc", "Phy", "OOP", "Db", "Calc", "Phy", "OOP"},
			{"AI", "DS", "LA", "CN", "AI", "DS", "LA", "CN", "AI"},
			{"DS", "ML", "DSA", "SE", "DS", "ML", "DSA", "SE", "DS"},
			{"OS", "DM", "ToC", "WD", "OS", "DM", "ToC", "WD", "OS"},
			{"Db", "Algo", "LA", "DS", "Db", "Algo", "LA", "DS", "Db"},
			{"Phy", "Calc", "OOP", "Db", "Phy", "Calc", "OOP", "Db", "Phy"},
			{"Calc", "LA", "DS", "AI", "Calc", "LA", "DS", "AI", "Calc"},
			{"OOP", "Db", "Calc", "Phy", "OOP", "Db", "Calc", "Phy", "OOP"},
			{"DS", "ML", "Algo", "SE", "DS", "ML", "Algo", "SE", "DS"},
			{"AI", "DS", "LA", "CN", "AI", "DS", "LA", "CN", "AI"},
			{"Db", "Algo", "LA", "DS", "Db", "Algo", "LA", "DS", "Db"},
			{"Phy", "Calc", "OOP", "Db", "Phy", "Calc", "OOP", "Db", "Phy"},
			{"Calc", "LA", "DS", "AI", "Calc", "LA", "DS", "AI", "Calc"},
			{"OOP", "Db", "Calc", "Phy", "OOP", "Db", "Calc", "Phy", "OOP"},
			{"DS", "ML", "Algo", "SE", "DS", "ML", "Algo", "SE", "DS"},
			{"AI", "DS", "LA", "CN", "AI", "DS", "LA", "CN", "AI"},
			{"Db", "Algo", "LA", "DS", "Db", "Algo", "LA", "DS", "Db"},
			{"Phy", "Calc", "OOP", "Db", "Phy", "Calc", "OOP", "Db", "Phy"},
			{"Calc", "LA", "DS", "AI", "Calc", "LA", "DS", "AI", "Calc"},
			{"OOP", "Db", "Calc", "Phy", "OOP", "Db", "Calc", "Phy", "OOP"}
        };
        string departments[][9] = {
             {"BS-CS-A", "BS-IT-D", "BS-SE-A", "BS-EE-D", "BS-CS-B", "BS-IT-D", "BS-SE-B", "BS-EE-D", "BS-CS-C"},
			{"BS-AI-A", "BS-CY-A", "BS-DS-A", "BS-BME-A", "BS-AI-B", "BS-CY-B", "BS-DS-B", "BS-BME-D", "BS-AI-C"},
			{"BS-DS-C", "BS-IT-A", "BS-CS-A", "BS-SE-A", "BS-DS-B", "BS-IT-B", "BS-CS-B", "BS-SE-B", "BS-DS-C"},
			{"BS-CY-A", "BS-CS-A", "BS-AI-A", "BS-SE-A", "BS-CY-B", "BS-CS-B", "BS-AI-B", "BS-SE-B", "BS-CY-C"},
			{"BS-IT-A", "BS-CS-A", "BS-AI-A", "BS-DS-A", "BS-IT-B", "BS-CS-B", "BS-AI-B", "BS-DS-D", "BS-IT-C"},
			{"BS-SE-A", "BS-CS-E", "BS-IT-A", "BS-AI-A", "BS-SE-B", "BS-CS-B", "BS-IT-B", "BS-AI-B", "BS-SE-C"},
			{"BS-CS-A", "BS-IT-A", "BS-SE-F", "BS-AI-A", "BS-CS-D", "BS-IT-B", "BS-SE-C", "BS-AI-B", "BS-CS-C"},
			{"BS-EE-A", "BS-CS-A", "BS-IT-C", "BS-SE-A", "BS-EE-B", "BS-CS-B", "BS-IT-B", "BS-SE-B", "BS-EE-C"},
			{"BS-IT-A", "BS-CS-D", "BS-DS-A", "BS-AI-C", "BS-IT-B", "BS-CS-B", "BS-DS-B", "BS-AI-B", "BS-IT-C"},
			{"BS-SE-A", "BS-CS-A", "BS-IT-A", "BS-AI-A", "BS-SE-B", "BS-CS-B", "BS-IT-B", "BS-AI-B", "BS-SE-C"},
			{"BS-CS-A", "BS-IT-A", "BS-SE-A", "BS-DS-A", "BS-CS-B", "BS-IT-D", "BS-SE-B", "BS-DS-B", "BS-CS-C"},
			{"BS-EE-A", "BS-CS-A", "BS-IT-D", "BS-SE-A", "BS-EE-B", "BS-CS-B", "BS-IT-B", "BS-SE-B", "BS-EE-C"},
			{"BS-IT-A", "BS-CS-A", "BS-DS-A", "BS-AI-A", "BS-IT-B", "BS-CS-B", "BS-DS-B", "BS-AI-B", "BS-IT-C"},
			{"BS-SE-A", "BS-CS-A", "BS-IT-A", "BS-AI-A", "BS-SE-B", "BS-CS-B", "BS-IT-B", "BS-AI-B", "BS-SE-C"},
			{"BS-CS-A", "BS-IT-A", "BS-SE-A", "BS-DS-A", "BS-CS-B", "BS-IT-B", "BS-SE-B", "BS-DS-B", "BS-CS-C"},
			{"BS-EE-A", "BS-CS-A", "BS-IT-A", "BS-SE-A", "BS-EE-B", "BS-CS-B", "BS-IT-B", "BS-SE-B", "BS-EE-C"},
			{"BS-IT-A", "BS-CS-A", "BS-DS-A", "BS-AI-A", "BS-IT-B", "BS-CS-B", "BS-DS-B", "BS-AI-B", "BS-IT-C"},
			{"BS-SE-A", "BS-CS-A", "BS-IT-A", "BS-AI-A", "BS-SE-B", "BS-CS-B", "BS-IT-B", "BS-AI-B", "BS-SE-C"},
			{"BS-CS-A", "BS-IT-A", "BS-SE-A", "BS-DS-A", "BS-CS-B", "BS-IT-B", "BS-SE-B", "BS-DS-B", "BS-CS-C"},
			{"BS-EE-A", "BS-CS-A", "BS-IT-A", "BS-SE-A", "BS-EE-B", "BS-CS-B", "BS-IT-B", "BS-SE-B", "BS-EE-C"}
        };
		string semesters[][9] = {
            {"1st", "2nd", "3rd", "4th", "5th", "6th", "7th", "8th", "1st"},
			{"2nd", "3rd", "4th", "5th", "6th", "7th", "8th", "1st", "2nd"},
			{"3rd", "4th", "5th", "6th", "7th", "8th", "1st", "2nd", "3rd"},
			{"4th", "5th", "6th", "7th", "8th", "1st", "2nd", "3rd", "4th"},
			{"5th", "6th", "7th", "8th", "1st", "2nd", "3rd", "4th", "5th"},
			{"6th", "7th", "8th", "1st", "2nd", "3rd", "4th", "5th", "6th"},
			{"7th", "8th", "1st", "2nd", "3rd", "4th", "5th", "6th", "7th"},
			{"8th", "1st", "2nd", "3rd", "4th", "5th", "6th", "7th", "8th"},
			{"1st", "2nd", "3rd", "4th", "5th", "6th", "7th", "8th", "1st"},
			{"2nd", "3rd", "4th", "5th", "6th", "7th", "8th", "1st", "2nd"},
			{"3rd", "4th", "5th", "6th", "7th", "8th", "1st", "2nd", "3rd"},
			{"4th", "5th", "6th", "7th", "8th", "1st", "2nd", "3rd", "4th"},
			{"5th", "6th", "7th", "8th", "1st", "2nd", "3rd", "4th", "5th"},
			{"6th", "7th", "8th", "1st", "2nd", "3rd", "4th", "5th", "6th"},
			{"7th", "8th", "1st", "2nd", "3rd", "4th", "5th", "6th", "7th"},
			{"8th", "1st", "2nd", "3rd", "4th", "5th", "6th", "7th", "8th"},
			{"1st", "2nd", "3rd", "4th", "5th", "6th", "7th", "8th", "1st"},
			{"2nd", "3rd", "4th", "5th", "6th", "7th", "8th", "1st", "2nd"},
			{"3rd", "4th", "5th", "6th", "7th", "8th", "1st", "2nd", "3rd"},
			{"4th", "5th", "6th", "7th", "8th", "1st", "2nd", "3rd", "4th"}
        };
        for (int i = 0; i < 20; i++) {
            if (rooms[i] == roomNo) {
                for (int j = 0; j < 9; j++) {
                    if (times[j] == timeSlot) {
                        cout << "\nSchedule for Room " << roomNo << " at " << timeSlot << "\n\n";
                        cout << "\tTeacher       Subjects       Department        Semester  \n" <<"\t"<< teachers[i][j] <<"\t" << classes[i][j] <<"\t      "<< departments[i][j] <<"\t\t "<< semesters[i][j] << endl;
                        return;
                    }
                }
                cout << "Time slot not found." << endl;
                return;
            }
        }
        cout << "Room not found." << endl;
    }
};

int main() {
    TUFMAP sms;
    int choice;
    string roomNo, timeSlot;
    cout << "\t\t\tTUF Map and Room Schedule System\n\n";
    cout<<"                      1st floor                                            2nd floor\n";
    cout << "\t _______________________________________             _______________________________________\n";
    cout << "\t|  101  |  102  |  103  |  104  | 105  |            |  201  |  202  |  203  |  204  | 205  |\n";
    cout << "\t|_______|_______|_______|_______|______|            |_______|_______|_______|_______|______|\n";
    cout << "\t|                                      |            |                                      |\n";
    cout << "\t|                                      |            |                                      |\n";
    cout << "\t|                                      |            |                                      |\n";
    cout << "\t|                                      |            |                                      |\n";
    cout << "\t|______________________________________|            |______________________________________|\n";
    cout << "\t|  106  |  107  |  108  |  109  | 110  |            |  206  |  207  |  208  |  209  | 210  |\n";
    cout << "\t|_______|_______|_______|_______|______|            |_______|_______|_______|_______|______|\n";
    cout << "\n1. Display Room Schedule\n";
    cout << "2. Display Room Schedule at a specific time\n";
    cout << "\nEnter your choice: ";
    cin >> choice;
    switch (choice) {
        case 1:
            cout << "\nEnter room number: ";
            cin >> roomNo;
            cout<<endl;
            sms.displayRoomSchedule(roomNo);
            break;
        case 2:
            cout << "Enter room number: ";
            cin >> roomNo;
            cout << "Enter time slot (e.g., 8-9): ";
            cin >> timeSlot;
            sms.displayRoomTimeSchedule(roomNo, timeSlot);
            break;
        default:
            cout << "Invalid choice." << endl;
    }
    return 0;
}
