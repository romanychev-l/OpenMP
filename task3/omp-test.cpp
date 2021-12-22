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

ld f(ld x){
    return sin(x)* cos(x);
}


ld integral(ld a, ld b, ll N, ll num_threads = 1){
    ld res = 0.0;
    ld h = (b-a)/N;
	omp_set_num_threads(num_threads);

    #pragma omp parallel for reduction(+:res)
	for(ll i = 0; i < N; i++)
	      res += f(a + i*h)*h;

    return res;
}

void gen_v(ll* array, ll n){
	for(ll i = 0; i < n; i++){
		array[i] = rand() % 1000 + 1;
    }
}

int main(){
    ll a = 15;
    ll b = 41;

    for(ll j = 3; j<=8; j++){
        ll n = pow(10, j);

        vector<ld> results;
        //cout << vec.size() << ' ' << vec[0]<< ' ' << vec[1] << "\n";


        for(ll i = 1; i <= 16; i *= 2){
            ld start_time = omp_get_wtime();
            ld result = integral(a, b, n, i);
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
