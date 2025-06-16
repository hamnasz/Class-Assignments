#include <iostream>
#include <list>
#include <string>
#include <algorithm>

using namespace std;

struct Job {
    string title;
    string level;

    Job(string t, string l) : title(t), level(l) {}
};

bool compareJobs(const Job &a, const Job &b) {
    string levels[] = {"high", "medium", "low"};
    int levelA = find(begin(levels), end(levels), a.level) - begin(levels);
    int levelB = find(begin(levels), end(levels), b.level) - begin(levels);
    return levelA < levelB; 
}

int main() {
    list<Job> jobList; 
    string option, jobTitle, level;

    while (true) {
        cout << "\nChoose an option (add/remove/show/quit): ";
        cin >> option;

        if (option == "add") {
            cout << "Enter job title: ";
            cin.ignore(); 
            getline(cin, jobTitle);

            cout << "Enter job priority (high/medium/low): ";
            cin >> level;

            if (level == "high" || level == "medium" || level == "low") {
                jobList.push_back(Job(jobTitle, level));
                cout << "Job added." << endl;
            } else {
                cout << "Invalid priority. Please use high, medium, or low." << endl;
            }
        } 
        else if (option == "remove") {
            cout << "Enter job title to remove: ";
            cin.ignore();
            getline(cin, jobTitle);

            auto it = find_if(jobList.begin(), jobList.end(), [&](const Job &j) {
                return j.title == jobTitle;
            });

            if (it != jobList.end()) {
                jobList.erase(it);
                cout << "Job removed." << endl;
            } else {
                cout << "Job not found." << endl;
            }
        } 
        else if (option == "show") {
            if (!jobList.empty()) {
                jobList.sort(compareJobs);
                cout << "Jobs sorted by Priority: " << endl;
                for (const auto &job : jobList) {
                    cout << "Job: " << job.title << ", Priority: " << job.level << endl;
                }
            } else {
                cout << "No jobs available to display." << endl;
            }
        } 
        else if (option == "quit") {
            break;
        } 
        else {
            cout << "Invalid option. Please try again." << endl;
        }
    }

    return 0;
}
