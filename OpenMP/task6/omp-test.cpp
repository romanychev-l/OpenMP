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

void gen_v(ll* array, ll n){
	for(ll i = 0; i < n; i++){
		array[i] = rand() % 1000 + 1;
    }
}

ld integral_reductions(ld a, ld b, ll N, ll num_threads=1, string red="red"){
	ld res;
	ld h = (b-a)/N;

    omp_set_num_threads(num_threads);

    res = 0.0;
    if(red == "red"){
        #pragma omp parallel for reduction(+:res)
        for(int i = 0; i < N; i++)
                res += f(a + i*h)*h;
    } else if(red == "critical"){
        #pragma omp parallel for shared(res)
        for(int i = 0; i < N; i++)
        {
            #pragma omp critical
                res += f(a + i*h)*h;
        }
    } else if(red == "atomic"){
        #pragma omp parallel for shared(res)
        for(int i = 0; i < N; i++)
        {
            #pragma omp atomic
                res += f(a + i*h)*h;
        }
    } else if(red == "lock"){
        omp_lock_t lock;
        omp_init_lock(&lock);
        #pragma omp parallel for shared(res)
        for(int i = 0; i < N; i++)
        {
            omp_set_lock(&lock);
                res += f(a + i*h)*h;
            omp_unset_lock(&lock);
        }
    }
    return res;
}

int main(){
    ll a = 15;
    ll b = 41;

    ll n = pow(10, 7);

    vector<ld> results;
    //cout << vec.size() << ' ' << vec[0]<< ' ' << vec[1] << "\n";


    for(ll i = 1; i <= 16; i *= 2){
        ld start_time = omp_get_wtime();
        //ld result = integral_reductions(a, b, n, i, "red");
        //ld result = integral_reductions(a, b, n, i, "critical");
        //ld result = integral_reductions(a, b, n, i, "atomic");
        ld result = integral_reductions(a, b, n, i, "lock");

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


	return 0;
}
