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

int fib(int n) {
  int i, j;
  if (n<2)
    return n;
  else {
    i=fib(n-1);
    j=fib(n-2);
    return i+j;
  }
}


int fib_p(int n) {
  int i, j;
  if (n<2)
    return n;
  if (n < 30) {
    i = fib(n-1);
    j = fib(n-2);
    return i + j;
  } else {
    #pragma omp task shared(i)
    i=fib_p(n-1);
    #pragma omp task shared(j)
    j=fib_p(n-2);
    #pragma omp taskwait
    return i+j;
  }
}


int main () {
    //omp_set_num_threads(8);
    omp_set_nested(1);
    ll num = omp_get_max_threads();
    cout << num << "\n";

    ll n;

    cin >> n;

    ld start_time = omp_get_wtime();

    ll ans = fib(n);
    ld end_time = omp_get_wtime();

    cout << ans << "\n";
    cout << "time: " << end_time - start_time << "\n";

    start_time = omp_get_wtime();

    #pragma omp parallel
    {
    #pragma omp single
    {
        ans = fib_p(n);
    }
    }
    end_time = omp_get_wtime();

    cout << ans << "\n";
    cout << "time: " << end_time - start_time << "\n";

    /*
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
    */
	return 0;
}
