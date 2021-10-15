// An election system that uses cumulative voting
#include <iostream>
#include <iomanip>
#include <string>

using std::cout;
using std::cin;
using std::endl;
using std::string;
using std::stoi;
using std::istringstream;
using std::setw;
using std::right;
using std::left;


int main(int argc, char **argv) {
    int X = 0;
    bool default_X = true; // when set to true, X = # of candidates
    if (argc > 1) { // check for optional cmd arg value of X
        X = stoi(argv[1]);
        default_X = false;
    }

    // read in candidates from input and store their names in arr
    // stop reading in candidates when first char isn't alpha
    int i = 0;
    string candidates[11];
    while (getline(cin, candidates[i]) && candidates[i][0] >= 'A' && candidates[i][0] <= 'z') {        
        if (default_X) ++X;
        ++i;
    } // note that candidates[i] contains the first ballot

    int num_voters = 0;
    int num_valid = 0;
    int num_spoilt = 0;
    int vote_results[i]{0};

    string ballot_str;
    string vote;
    bool went_into_loop = false;
    while (getline(cin, ballot_str)) { // read rows of ballots
        went_into_loop = true;
        int ballot_arr[i]{0};
        int vote_count = 0;
        ++num_voters;

        if (ballot_str.empty() && i > 0) { // blank line when num candidates > 0 means spoilt
            ++num_spoilt;
            continue;
        }

        istringstream ballot_ss{ballot_str};
        while (getline(ballot_ss, vote, ' ')) { // store ballot specific vote counts temporarily in ballot_arr
            ballot_arr[vote_count] = stoi(vote);
            ++vote_count;
        }

        if (vote_count != i) { // not n columns 
            ++num_spoilt;
            continue;
        }

        int ballot_sum = 0;
        for (int j = 0; j < vote_count; ++j) { // get sum to check if its valid
            ballot_sum += ballot_arr[j];
        }

        if (ballot_sum > X) { // sum exceeds X
            ++num_spoilt;
            continue;
        }

        for (int j = 0; j < vote_count; ++j) { // update vote_results
            vote_results[j] += ballot_arr[j];
        }
        ++num_valid; // ballot is valid if got here
    }


    // cout << candidates[i] << endl;




    if (went_into_loop || !candidates[i].empty()) { // then candidates[i] wasn't just a end of file \n
        // Handle first ballot separtely (sorry this is super ugly but im desparate to just get this right)
        int first_ballot_arr[i]{0};
        int first_vote_count = 0;
        ++num_voters;

        if (candidates[i].empty() && i > 0) { // blank line when num candidates > 0 means spoilt
            ++num_spoilt;
        } else {
            istringstream ballot_ss{candidates[i]};
            while (getline(ballot_ss, vote, ' ')) { // store ballot specific vote counts temporarily in first_ballot_arr
                first_ballot_arr[first_vote_count] = stoi(vote);
                ++first_vote_count;
            }

            if (first_vote_count != i) { // not n columns 
                ++num_spoilt;
            } else {
                int first_ballot_sum = 0;
                for (int j = 0; j < first_vote_count; ++j) { // get sum to check if its valid
                    first_ballot_sum += first_ballot_arr[j];
                }

                if (first_ballot_sum > X) { // sum exceeds X
                    ++num_spoilt;
                } else {
                    for (int j = 0; j < first_vote_count; ++j) { // update vote_results
                        vote_results[j] += first_ballot_arr[j];
                    }
                    ++num_valid; // ballot is valid if got here
                }
            }
        }
    }

    // Printing results
    cout << "Number of voters: " << num_voters << endl;
    cout << "Number of valid ballots: " << num_valid << endl;
    cout << "Number of spoilt ballots: " << num_spoilt << endl;
    cout << endl;
    cout << "Candidate      Score" << endl;
    cout << endl;
    for (int j = 0; j < i; ++j) {
        cout << setw(15) << left << candidates[j];
        cout << setw(3) << right << vote_results[j] << endl;
    }
}
