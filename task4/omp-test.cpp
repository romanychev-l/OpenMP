#include <omp.h>
#include <stdio.h>
#include <iostream>
#include <bits/stdc++.h>
#include <iomanip>

using namespace std;

typedef long long ll;
typedef long double ld;

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

void gen_v(ll** array, ll n){
	for(ll i = 0; i < n; i++){
        for(ll j = 0; j<n; j++){
		    array[i][j] = rand() % 1000 + 1;
        }
    }
}

ll get_min(ll* row, int n, bool nested=false){
    omp_set_nested(nested);
    ll mn = row[0];

    #pragma omp parallel for reduction(min:mn)
    for (ll i = 0; i < n; i++){
        if (row[i] < mn)
            mn = row[i];
    }
    return mn;
}

ll get_max(ll** array, ll n, ll num_threads=1){
    ll mx;
    ll* min_row = new ll[n];
    omp_set_num_threads(num_threads);

    #pragma omp parallel for
    for (ll i = 0; i < n; i++)
        min_row[i] = get_min(array[i], n);

    mx = min_row[0];
    #pragma omp parallel for reduction(max:mx)
    for (ll i = 1; i < n; i++)
        if(min_row[i] > mx)
            mx = min_row[i];

    return mx;
}

int main(){
    for(ll j = 1000; j<25000; j+=4000){
        ll n = j;

        ll** array = new ll*[n];
        for(ll i = 0; i<n; i++){
            array[i] = new ll[n];
        }
        gen_v(array, n);

        vector<ld> results;
        //cout << vec.size() << ' ' << vec[0]<< ' ' << vec[1] << "\n";


        for(ll i = 1; i <= 16; i *= 2){
            ld start_time = omp_get_wtime();
            ld result = get_max(array, n, i);

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
