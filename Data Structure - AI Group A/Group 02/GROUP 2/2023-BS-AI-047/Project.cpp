#include <iostream>
#include <fstream>
#include <queue>
#include <vector>
#include <string>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <chrono>
using namespace std;

class Patient 
{
public:
    string name;
    int age;
    string disease;
    string recentSymptoms;

    Patient(string name = "", int age = 0, string disease = "", string recentSymptoms = "") 
        : name(name), age(age), disease(disease), recentSymptoms(recentSymptoms) {}

    void inputPatientInfo() 
    {
        cout << "Enter patient's name: ";
        cin >> name;
        cout << "Enter patient's age: ";
        cin >> age;
        cout << "Enter patient's disease: ";
        cin >> disease;
        cout << "Enter patient's recent symptoms: ";
        cin >> recentSymptoms;
    }

    void displayPatientInfo() const 
    {
        cout << "Name: " << name << ", Age: " << age << ", Disease: " << disease 
             << ", Symptoms: " << recentSymptoms << endl;
    }
};

class Doctor 
{
public:
    string name;
    int id;

    Doctor(string name = "") 
{
        static int idCounter = 1;
        id = idCounter++;
        this->name = (name.empty()) ? "Doctor" + to_string(id) : name;
    }

    void displayDoctorInfo() const 
    {
        cout << "Doctor ID: " << id << ", Name: " << name << endl;
    }
};

class Hospital 
{
private:
    vector<Doctor> doctors;
    queue<Patient> patientQueue;
    vector<string> medicines;

public:
    Hospital() 
    {
        medicines = {"Paracetamol", "Ibuprofen", "Cough Syrup", "Antibiotics"};
    }

    void addDoctors(vector<string>& doctorNames) 
    {
        for (const string& doctorName : doctorNames) 
        {
            doctors.emplace_back(doctorName);
        }
    }

    void displayDoctors() const {
        cout << "\nAvailable Doctors:\n";
        for (const auto& doctor : doctors) 
        {
            doctor.displayDoctorInfo();
        }
    }

    void addPatientToQueue(const Patient& patient) 
    {
        patientQueue.push(patient);
        cout << "\nPatient " << patient.name << " added to the queue.\n";
    }

    void processPatient() {
        if (patientQueue.empty()) 
        {
            cout << "\nNo patients in the queue.\n";
            return;
        }

        Patient currentPatient = patientQueue.front();
        patientQueue.pop();

        // Assign a random doctor
        int doctorIndex = rand() % doctors.size();
        Doctor assignedDoctor = doctors[doctorIndex];

        // Recommend a random medicine
        string prescribedMedicine = medicines[rand() % medicines.size()];

        // Assign a random room number
        int roomNumber = rand() % 100 + 1;

        // Display patient details and consultation summary
        cout << "\nConsultation Summary:\n";
        currentPatient.displayPatientInfo();
        cout << "Assigned Doctor: " << assignedDoctor.name << endl;
        cout << "Prescribed Medicine: " << prescribedMedicine << endl;
        cout << "Room Number: " << roomNumber << endl;

        // Log the consultation details to a file
        logConsultation(currentPatient, assignedDoctor, prescribedMedicine, roomNumber);
    }

    void logConsultation(const Patient& patient, const Doctor& doctor, const string& medicine, int roomNumber) {
        ofstream file("hospital_log.txt", ios::app);
        if (file.is_open()) 
        {
            auto now = chrono::system_clock::to_time_t(chrono::system_clock::now());
            file << "Patient Name: " << patient.name 
                 << "\nAge: " << patient.age 
                 << "\nDisease: " << patient.disease 
                 << "\nSymptoms: " << patient.recentSymptoms 
                 << "\nAssigned Doctor: " << doctor.name 
                 << "\nPrescribed Medicine: " << medicine 
                 << "\nRoom Number: " << roomNumber 
                 << "\nDate and Time: " << put_time(localtime(&now), "%Y-%m-%d %X") 
                 << "\n---------------------------------\n";
            file.close();
        } else 
        {
            cout << "Unable to log consultation details.\n";
        }
    }

    bool isQueueEmpty() const 
    {
        return patientQueue.empty();
    }
};

int main() {
    srand(time(0));

    Hospital hospital;

    vector<string> doctorNames = 
    {
        "Dr. Sarah", "Dr. Asif", "Dr. Mariam", "Dr. Aria", "Dr. Arif",
        "Dr. Maham", "Dr. Fozia", "Dr. Harris", "Dr. Asim", "Dr. Mahad",
        "Dr. Fareed", "Dr. Ahmad", "Dr. Bilal", "Dr. Sajid", "Dr. Kaiser"
    };
    hospital.addDoctors(doctorNames);

    int choice;
    do {
        cout << "\nHospital Management System\n";
        cout << "1. Add a Patient to Queue\n";
        cout << "2. Process Next Patient\n";
        cout << "3. Display Available Doctors\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        switch (choice) 
        {
        case 1: 
        {
            Patient patient;
            patient.inputPatientInfo();
            hospital.addPatientToQueue(patient);
            break;
        }
        case 2:
            hospital.processPatient();
            break;
        case 3:
            hospital.displayDoctors();
            break;
        case 4:
            cout << "Exiting the system. Goodbye!\n";
            break;
        default:
            cout << "Invalid choice. Please try again.\n";
        }
    } 
    while (choice != 4);
    return 0;
}
