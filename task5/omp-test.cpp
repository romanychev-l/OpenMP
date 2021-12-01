#include <bits/stdc++.h>

#include <iostream>
#include <omp.h>


using namespace std;


typedef vector<vector<int> > vv;
typedef vector<int> v;

void print_matrix(vv& matrix){
    int n = matrix.size();
    int m = matrix[0].size() - 2;

    for(int i = 0; i<n; i++){
        for(int j = 0; j<m; j++){
            cout << matrix[i][j] << ' ';
        }
        cout << "\n";
    }
}

void gen_matrix(vv& matrix, int mod){
	int n = matrix.size();
	for(int i = 0; i<n; i++){
		int m = matrix[i].size() - 2;

		int start = matrix[i][m];
		int end = matrix[i][m+1];

		for(int j = start; j<end; j++){
			matrix[i][j] = rand() % mod + 1;
		}
	}
}

void gen_triangle(vv& matrix, bool up=true, int mod=1000){
	int n = matrix.size();
	for(int i = 0; i<n; i++){
		int m = matrix[i].size() - 2;

		int start, end;
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

	gen_matrix(matrix, mod);
}

void gen_band(vv& matrix, int k1, int k2, bool up=true, int mod=1000){
	int n = matrix.size();
	for(int i = 0; i<n; i++){
		int m = matrix[i].size() - 2;

		int start, end;
		if(1){
			start = max(0, m - 1 - k1);
			end = min(m, i + k2 + 1);
		} else {
			start = max(0, i - k1);
			end = min(m, i + k2 + 1);
		}

		matrix[i][m] = start;
		matrix[i][m+1] = end;
	}

	gen_matrix(matrix, mod);
}

int get_min(vv& matrix, int ind, int parallel=false){
	if(parallel)
		omp_set_nested(true);

	int m = matrix[ind].size()-2;
	int start = matrix[ind][m];
	int end = matrix[ind][m+1];

	int min = matrix[ind][0];

	#pragma parallel for if(arallel)
	for (int i = start; i < end; i++)
	{
		if (matrix[ind][i] < min)
			min = matrix[ind][i];
	}

	return min;
}


int get_max(vv& matrix, int parallel){
	int n = matrix.size();

	int mx;
	v min_of_lines(n);
	omp_set_num_threads(parallel);

	#pragma omp parallel for
	for (int i = 0; i < n; i++)
		min_of_lines[i] = get_min(matrix, i);

	mx = min_of_lines[0];

	#pragma omp parallel for reduction(max:mx)
	for (int i = 1; i < n; i++)
		if (min_of_lines[i] > mx)
			mx = min_of_lines[i];

	return mx;
}



int main(){
	int n, m;
	cout << "Input n and m: ";
	cin >> n >> m;

	vv matrix(n, v (m + 2));

	gen_triangle(matrix);

    //print_matrix(matrix);

	for (int i = 1; i <= 16; i *= 2){
		double start_time = omp_get_wtime();
		int result = get_max(matrix, i);
		double time = omp_get_wtime() - start_time;

		cout << "Num threads: " << i << endl;
		cout << "Time: " << time << endl;
		cout << "Result: " << result << endl;
	}


	return 0;
}

