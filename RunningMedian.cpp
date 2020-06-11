#include <vector>
#include <iostream>
#include <limits>
#include <algorithm>
#include <iomanip>
#include <sstream>

using namespace std;

/*
 * Complete the runningMedian function below.
 */

vector<double> runningMedian(vector<int> a) {
    /*
     * Write your code here.
     */
     std::vector<double> medians;
     for (int i = 1; i <= a.size(); ++i) {
       // Sort elements from begin and have i elements
       std::sort(a.begin(), a.begin() + i);
        if (i % 2 != 0) {
            medians.push_back(a[i/2]/ 1.0);
        } else {
            medians.push_back((a[i/2] + a[i/2 -1]) / 2.0);
        }
     }
     return medians;
}

int main()
{
//    ofstream fout(getenv("OUTPUT_PATH"));

    int a_count;
    cin >> a_count;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    vector<int> a(a_count);

    for (int a_itr = 0; a_itr < a_count; a_itr++) {
        int a_item;
        cin >> a_item;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        a[a_itr] = a_item;
    }

    vector<double> result = runningMedian(a);

    std::cout << "result" << std::endl;
    for (int result_itr = 0; result_itr < result.size(); result_itr++) {
        std::cout << std::fixed << std::setprecision(1) << result[result_itr] << std::endl;
    }

//    fout << "\n";
//
//    fout.close();

    return 0;
}
