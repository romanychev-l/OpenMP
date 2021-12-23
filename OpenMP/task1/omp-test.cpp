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

ll get_max(ll* array, ll n, ll num_threads=1){
	ll mx = array[0];
    //cout << "mx " << mx << '\n';
    //cout << "n " << n << '\n';

    omp_set_num_threads(num_threads);
    #pragma omp parallel for reduction(max:mx)
    for (ll i = 0; i < n; i++)
        if (array[i] > mx)
            mx = array[i];

	return mx;
}

void gen_v(ll* array, ll n){
	for(ll i = 0; i < n; i++){
		array[i] = rand() % 1000 + 1;
    }
}

int main(){
    /*
	ll n;

	cout << "Введите n: ";
	cin >> n;

    v vec(n);
    */

    /*
	ld start_time = omp_get_wtime();
	ll result1 = get_max(vec, n, 0);
	ld time1 = omp_get_wtime() - start_time;


	ll result2, result3;
	ld time2, time3;
    */

    for(ll j = 4; j<10; j++){
        ll n = pow(10, j);

        ll* array = new long long[n];
        v results;
        gen_v(array, n);
        //cout << vec.size() << ' ' << vec[0]<< ' ' << vec[1] << "\n";


        for(ll i = 1; i <= 16; i *= 2){
            ld start_time = omp_get_wtime();
            ll result = get_max(array, n, i);
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
