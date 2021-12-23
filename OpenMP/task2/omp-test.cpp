#include <omp.h>
#include <stdio.h>
#include <iostream>
#include <bits/stdc++.h>
#include <iomanip>

using namespace std;

typedef long long ll;
typedef long double ld;
typedef vector<vector<int> > vv;
typedef vector<int> v;

template <typename T>
string to_string_with_precision(const T a_value, const ll n = 6)
{
    ostringstream out;
    out.precision(n);
    out << fixed << a_value;
    return out.str();
}

void vprint(ll* array, ll n){
	for(ll i = 0; i<n; i++){
		cout << array[i] << ' ';
	}
	cout << "\n";
}

ll scalar(ll* array1, ll* array2, ll n, ll num_threads=1){
    ll result = 0;
	omp_set_num_threads(num_threads);
	#pragma omp parallel for reduction(+:result)
	for (int i = 0; i < n; ++i)
        	result += (array1[i] * array2[i]);

    return result;
}

void gen_v(ll* array, ll n){
	for(ll i = 0; i < n; i++){
		array[i] = rand() % 1000 + 1;
    }
}

int main () {
    for(ll j = 4; j<9; j++){
        ll n = pow(10, j);

        ll* array1 = new ll[n];
        ll* array2 = new ll[n];
        v results;
        gen_v(array1, n);
        gen_v(array2, n);

        cout << "Количество потоков: " << j << "\n";
        for(ll i = 1; i <= 16; i *= 2){
            ld start_time = omp_get_wtime();
            ll result = scalar(array1, array2, n, i);
            ld time = omp_get_wtime() - start_time;

            results.push_back(result);
            string t = to_string_with_precision(time, 8);
            t[1] = ',';
            cout << t << '\n';
            //cout << fixed << setprecision(8) << t << "\n";
            //cout << time << '\n';
        }
        for(ll i = 0; i<results.size(); i++){
            cout << results[i] << ' ';
        }
        cout << "\n";
    }


    return 0;
}
