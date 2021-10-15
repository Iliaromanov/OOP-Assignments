// Student and class average calculator
#include <iostream>
#include <sstream>
#include <string>

using namespace std;


struct Assesment {
    int max_mark;
    int weight;
};

struct Student {
    string name;
    int avg;
};


int main(int argc, char **argv) {
    string course_name = argv[1];
    int num_a = 5;
    if (argc > 2) {
        num_a = stoi(argv[2]);
    }

    cout << course_name << endl;

    Assesment grade_breakdown[12]{0}; // 12 because max 10 assignments + 1 mt + 1 exam
    string grade_s;
    for (int i = 0; i < num_a + 2; ++i) { // Read in grade breakdowns
        getline(cin, grade_s);
        istringstream grade_ss{grade_s};
        Assesment a;
        string val;
        grade_ss >> val;
        a.max_mark = stoi(val); 
        grade_ss >> val;
        a.weight = stoi(val);
        grade_breakdown[i] = a;
    }

    Student students[20]; // arr for storing valid students
    int student_i = 0;
    int valid_records = 0;
    string s;
    while (getline(cin, s)) { // read in student info
        if (s.empty()) { // blank lines ignored
            continue;
        }

        // Make a copy of grade breakdown to modify based on 
        //  students results if needed
        Assesment gr_bdwn_cp[num_a + 2]{0};
        for (int i = 0; i < num_a + 2; ++i) {
            gr_bdwn_cp[i] = grade_breakdown[i];
        }
        
        Student student;
        student.avg = 0;
        int num_grades = 0;
        istringstream student_ss{s};
        string val;
        int valid = true;
        while (getline(student_ss, val, ' ')) {
            if (num_grades == 0) { // reading students id
                student.name = val;
            } else {
                // For ACC just create a copy of and loop over grade_breakdown starting at num_grades ending at len - 3 and changing the weights as needed
                if (val == "ACC") { // if ACC
                    if (num_grades != num_a) {
                        int increase = gr_bdwn_cp[num_grades - 1].weight / (num_a - num_grades);
                        for (int i = num_grades; i < num_a; ++i) {
                            gr_bdwn_cp[i].weight += increase; 
                        }
                        gr_bdwn_cp[num_a-1].weight += gr_bdwn_cp[num_grades - 1].weight % (num_a - num_grades);
                    } else {
                        gr_bdwn_cp[num_a+1].weight += gr_bdwn_cp[num_a-1].weight; // if last assignment is adjusted its weight shifts to final
                    }
                    ++num_grades;
                    continue;
                }

                // for each grade check if its <= max for corresponding ass && if its >=0.
                int mark = stoi(val);
                if (num_grades > num_a + 3 || mark > gr_bdwn_cp[num_grades-1].max_mark || mark < 0) {
                    valid = false;
                    break;
                }
                // Calculate assignment grade and add to avg
                student.avg += (mark * gr_bdwn_cp[num_grades-1].weight) / 
                    gr_bdwn_cp[num_grades-1].max_mark;
            }
            ++num_grades;
        }
        --num_grades; // cus counted students id
        if (num_grades != num_a + 2 || !valid) {
            cout << student.name << " invalid" << endl;
            continue;
        }
        students[student_i] = student;
        ++student_i;
        ++valid_records;
    }

    // print result and calculate class avg
    int avg_sum = 0;
    cout << "Valid records: " << valid_records << endl;
    for (int i = 0; i < student_i; ++i) {
        avg_sum += students[i].avg;
        cout << students[i].name << " " << students[i].avg << endl;
    }
    cout << "Average: ";
    if (student_i == 0) {
        cout << 0 << endl;
    } else {
        cout << avg_sum / student_i << endl;
    }
}

