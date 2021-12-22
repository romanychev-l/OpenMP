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

ll scalar(ll n, ll m, ll num_threads=1){
    freopen("in.txt", "r", stdin);

    ll result = 0;
	omp_set_num_threads(num_threads);

    ll** array = new ll*[n];
    for (int i = 0; i < n; i++)
        array[i] = new ll[m];

    ll start = 0, end = 0;
    ll f = 0;

    #pragma omp parallel sections
    {
        #pragma omp section
        {
            for(ll i = 0; i<n; i++){
                for(ll j = 0; j<m; j++){
                    cin >> array[i][j];
                }
                #pragma omp critical
                {
                    end++;
                }
            }
            #pragma omp critical
            {
                f = 1;
            }
        }
        #pragma omp section
        {
            while(!f || start != end){
                ll ind = -1;
                ll res = 0;
                #pragma omp critical
                {
                    if(end - start >= 2){
                        ind = start;
                        start += 2;
                    }
                }
                if(ind != -1){
                    res = 0;
                    #pragma omp parallel for reduction(+:res)
                    for(ll i = 0; i<m; i++){
                        res += array[ind][i] * array[ind+1][i];
                    }
                    //cout << res << ' ';
                }
            }
        }
    }
    //cout << "\n";
    return 0;
/*

#pragma omp parallel for reduction(+:result)
	for (int i = 0; i < n; ++i)
        	result += (array1[i] * array2[i]);

    return result;
    */
}

void gen_v(ll* array, ll n){
	for(ll i = 0; i < n; i++){
		array[i] = rand() % 1000 + 1;
    }
}

int main () {
    ll n = 10000;
    ll m = 1000;
    /*
    freopen("in.txt", "w", stdout);

    for(ll i = 0; i<n; i++){
        for(ll j = 0; j<m; j++){
            cout << rand() % 1000 + 1 << ' ';
        }
        cout << "\n";
    }

    fclose (stdout);
    */
    //freopen("in.txt", "r", stdin);

    v results;
    //gen_v(array1, n);
    //gen_v(array2, n);

    //cout << "Количество потоков: " << j << "\n";
    for(ll i = 1; i <= 16; i *= 2){
        cout << "Количество потоков: " << i << "\n";

        ld start_time = omp_get_wtime();

        ll result = scalar(n, m, i);

        ld time = omp_get_wtime() - start_time;

        results.push_back(result);
        string t = to_string_with_precision(time, 8);
        t[1] = ',';
        cout << t << '\n';
    }
    for(ll i = 0; i<results.size(); i++){
        cout << results[i] << ' ';
    }


    return 0;
}
