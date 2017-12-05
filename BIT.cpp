#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

class BIT {

public:


    BIT(vector<int> list) {


        //Initialize BIT with list in O(n*log(n))
//		m_array = std::vector<int>(list.size() + 1, 0);
//		for (int idx = 0; idx < list.size(); idx++) {
//			update(idx, list[idx]);
//		}

        arr = vector<int>(list.size() + 1, 0);
        for ( int idx = 0; idx < list.size(); ++idx) {
            //arr[idx + 1] = list[idx];
            update(idx, list[idx]);
        }

//        for (int idx = 1; idx < arr.size(); ++idx) {
//            int idx2 = idx + (idx & -idx);
//            if (idx2 < arr.size()) {
//                arr[idx2] += arr[idx];
//            }
//        }
    }


    void update(int idx, int add) {
		// Add a value to the idx-th element
		for (++idx; idx < arr.size(); idx += idx & -idx) {
			arr[idx] += add;
		}
//		for (idx += idx & -idx; idx < arr.size(); ++idx) {
//			arr[idx] += add;
//		}
	}

	int prefix_query(int idx) {
		// Computes prefix sum of up to including the idx-th element
		int result = 0;

		//------//
		idx++;
		while(idx > 0)
        {
            result += arr[idx];
            idx -= idx & -idx;
        }
        //------//


		//for (++idx; idx > 0; idx -= idx & -idx) {
		//	result += arr[idx];
		//}


		return result;
	}


	int range_query(int from_idx, int to_idx) {
		// Computes the range sum between two indices (both inclusive)
		return prefix_query(to_idx) - prefix_query(from_idx - 1);
	}




private:
    vector<int> arr;
};

int main()
{
    fstream inFile("data.txt", ios::in);

	vector<int> arr;
	int n;

    if (!inFile)
    {
        cout << "file not found" << endl;
    }

    while (inFile >> n)
    {
        arr.push_back(n);

    }inFile.close();


    int length = arr.size();

    BIT bit(arr);

    for (int i = 0; i < length; ++i)
    {
        cout << arr[i] << " ";
    }cout << endl;

    int C;
    cout << "\n\n     1. Update \n     2. Prefix query\n     3. Insert\n     0. Exit\n";

    while (C == 0)
    {

        cin >> C;
        if (C==1)
        {
            int Pos;
            int F;
            cout << "Enter the location: ";   cin >> Pos;
            cout << "Enter the value: ";  cin >> F;
            cout << "Add " << F << " to element at pos " << Pos << endl;
            bit.update(Pos, F);
            vector<int> new_arr;
            for (int idx = 0; idx < arr.size(); idx++) {
                new_arr.push_back(bit.range_query(idx, idx));

            }cout << endl;
            for (int i=0; i<length; ++i) {
                cout << new_arr[i] << " ";
            }
            cout << endl << endl;

        }

        if (C==2)
        {
            int F;
            cout << "Enter the value: ";  cin >> F;
            cout << "Prefix sum of first " << F << " elements: " << bit.prefix_query(F) << endl;
        }

        if (C==3)
        {
            vector<int>::iterator it = arr.end();
            int F;


            cout << "Enter the value: ";  cin >> F;
            arr.insert(it , F);

            length++;
            for (int i=0; i<length; ++i) {
                cout << arr[i] << " ";
            }
            cout << endl << endl;

        }
        else {

        }




    }















    return 0;

}














