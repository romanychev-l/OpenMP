#include <bits/stdc++.h>

#include <iostream>
#include <omp.h>


using namespace std;

typedef long long ll;
typedef long double ld;

template <typename T>
string to_string_with_precision(const T a_value, const ll n = 6){
    ostringstream out;
    out.precision(n);
    out << fixed << a_value;
    return out.str();
}

void print_matrix(auto matrix, ll n){
    for(ll i = 0; i<n; i++){
        for(ll j = 0; j<n; j++){
            cout << matrix[i][j] << '\t';
        }
        cout << "\n";
    }
}

void gen_matrix(auto matrix, ll n, ll mod=1000){
	for(ll i = 0; i<n; i++){
        //cout << "gen matrix " << i << "\n";
		ll m = n;

		ll start = matrix[i][m];
		ll end = matrix[i][m+1];

		for(ll j = start; j<end; j++){
			matrix[i][j] = rand() % mod + 1;
		}
	}
}

void gen_triangle(auto matrix, ll n, bool up=true, ll mod=1000){
	for(ll i = 0; i<n; i++){
        //cout << "triangle " << i << "\n";
		ll m = n;

		ll start, end;
		if(up){
			start = i;
			end = m;
		} else {
			start = 0;
			end = i + 1;
		}

		matrix[i][m] = start;
		matrix[i][m+1] = end;
	}

	gen_matrix(matrix, n, mod);
}

void gen_band(auto matrix, ll n, ll k1, ll k2, bool up=true, ll mod=1000){
	for(ll i = 0; i<n; i++){
		ll m = n + 1;

		ll start, end;
		if(1){
			start = max(ll(0), m - 1 - k1);
			end = min(m, i + k2 + 1);
		} else {
			start = max(ll(0), i - k1);
			end = min(m, i + k2 + 1);
		}

		matrix[i][m] = start;
		matrix[i][m+1] = end;
	}

	gen_matrix(matrix, n, mod);
}

ll get_min(auto matrix, ll n, ll ind, string sheld="static", ll nested=false){
	omp_set_nested(nested);

	ll m = n;
	ll start = matrix[ind][m];
	ll end = matrix[ind][m+1];

	ll min = matrix[ind][0];

    if(sheld == "static"){
        #pragma omp parallel for
        for(ll i = start; i < end; i++){
            if (matrix[ind][i] < min)
                min = matrix[ind][i];
        }
    } else if(sheld == "dynamic"){
        #pragma omp parallel for schedule(dynamic)
        for(ll i = start; i < end; i++){
            if (matrix[ind][i] < min)
                min = matrix[ind][i];
        }
    } else if(sheld == "guided"){
        #pragma omp parallel for schedule(guided)
        for(ll i = start; i < end; i++){
            if (matrix[ind][i] < min)
                min = matrix[ind][i];
        }

    }

	return min;
}


ll get_max(auto matrix, ll n, ll num_threads=1, string sheld="static"){
    ll mx;
	ll* min_row = new ll[n];
	omp_set_num_threads(num_threads);

    if(sheld == "static"){
        #pragma omp parallel for
        for(ll i = 0; i < n; i++)
            min_row[i] = get_min(matrix, n, i, sheld, true);

        mx = min_row[0];

        #pragma omp parallel for reduction(max:mx)
        for(ll i = 1; i < n; i++)
            if(min_row[i] > mx)
                mx = min_row[i];

    } else if(sheld == "dynamic"){
        #pragma omp parallel for schedule(dynamic)
        for(ll i = 0; i < n; i++)
            min_row[i] = get_min(matrix, n, i, sheld);

        mx = min_row[0];

        #pragma omp parallel for reduction(max:mx) schedule(dynamic)
        for(ll i = 1; i < n; i++)
            if(min_row[i] > mx)
                mx = min_row[i];

    } else if(sheld == "guided"){
        #pragma omp parallel for schedule(guided)
        for(ll i = 0; i < n; i++)
            min_row[i] = get_min(matrix, n, i, sheld, true);

        mx = min_row[0];

        #pragma omp parallel for reduction(max:mx) schedule(guided)
        for(ll i = 1; i < n; i++)
            if(min_row[i] > mx)
                mx = min_row[i];

    }

	return mx;
}

void delete_matrix(auto matrix, ll n){
    for(ll i = 0; i<n; i++){
        delete [] matrix[0];
    }
    delete [] matrix;
}

int main(){
    for(ll j = 1000; j<25000; j+=4000){
        cout << "size " << j << "\n";
        ll** matrix = new ll*[j];
        for(ll i = 0; i<j; i++){
            //cout << i << "\n";
            matrix[i] = new ll[j+2];
        }

        gen_triangle(matrix, j);
        //cout << "ok";

        vector<ll> results;

        //print_matrix(matrix, j);

        for (ll i = 1; i <= 16; i *= 2){
            //cout << "num thread " << i << "\n";
            ld start_time = omp_get_wtime();

            ll result = get_max(matrix, j, i, "guided");

            ld time = omp_get_wtime() - start_time;

            results.push_back(result);
            string t = to_string_with_precision(time, 8);
            t[1] = ',';
            cout << t << '\n';
        }
        for(ll i = 0; i<results.size(); i++){
            cout << results[i] << ' ';
        }
        cout << "\n";

        //delete_matrix(matrix, j);
    }


	return 0;
}
