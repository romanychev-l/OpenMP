#include <omp.h>
#include <stdio.h>
#include <iostream>
#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef long double ld;


void vprint(vector<ll>& a){
	for(ll i = 0; i<a.size(); i++){
		cout << a[i] << ' ';
	}
	cout << "\n";
}


int main () {
    omp_set_num_threads(8);

	ll n, ans = 0, s = 0;

	cin >> n;

	vector<ll> a(n), b(n);

	for(ll i = 0; i<n; i++){
		a[i] = rand() % 10000;
		b[i] = rand() % 10000;
	}

	//vprint(a);
	//vprint(b);

	ll start_time = clock();

	for(ll i = 0; i<n; i++){
		ans += a[i] * b[i];
	}

	ll end_time = clock();

	cout << "time: " << end_time - start_time << "\n";

	start_time =  clock();

#pragma omp parallel for reduction(+:s)
	for(ll i = 0; i<n; i++){
		s += a[i] * b[i];
	}

	end_time = clock();

	cout << "time: " << end_time - start_time << "\n";
	cout << "ans = " << ans << "\n";
	cout << "s = " << s << "\n";

	return 0;
}
