/*
 * BalanceBracket.cpp
 *
 *  Created on: Jan 15, 2020
 *      Author: fading
 */

#include <bits/stdc++.h>
#include <map>

using namespace std;

// Complete the isBalanced function below.
string isBalanced(string s) {
    if (s.size() % 2 != 0) {
        return "NO";
    } else {
        std::map<char, char> bracket_map = {
            {'}', '{'},
            {']', '['},
            {')', '('},
        };
        std::string first_part = s.substr(0, s.size() / 2);
        std::string second_part = s.substr(s.size() / 2);
        std::string reverse_second_part;
        for (int i = second_part.size() -1; i >= 0; --i) {
            auto it = bracket_map.find(second_part[i]);
            if (it != bracket_map.end()) {
                reverse_second_part.push_back(it->second);
            } else {
                return "NO";
            }
        }
        if (first_part == reverse_second_part) {
            return "YES";
        } else {
            return "NO";
        }
    }
}

int main()
{
    ofstream fout(getenv("OUTPUT_PATH"));

    int t;
    cin >> t;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    for (int t_itr = 0; t_itr < t; t_itr++) {
        string s;
        getline(cin, s);

        string result = isBalanced(s);
        std::cout << result << std::endl;

        fout << result << "\n";
    }

    fout.close();

    return 0;
}



