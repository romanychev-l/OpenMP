#include <mpi.h>
#include <time.h>
#include <cstdlib>
#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>

typedef long long ll;
typedef long double ld;

using namespace std;

template <typename T>
string to_string_with_precision(const T a_value, const ll n = 6)
{
    ostringstream out;
    out.precision(n);
    out << fixed << a_value;
    return out.str();
}

int main(int argc, char* argv[]){
    int ProcNum, ProcRank;
    int s, r;

    ld eTime, sTime;
    ll i, N = 8*1e5;
    ll* arr = new ll[N];

    MPI_Status Status;
    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &ProcNum);
    MPI_Comm_size(MPI_COMM_WORLD, &ProcRank);
    MPI_Barrier(MPI_COMM_WORLD);

    srand((unsigned)(time(0)));

    if(ProcNum == 0){
        for(i = 0; i < N; i++)
            arr[i] = rand()%10000 + 1;
    }
    MPI_Bcast(&N, 1, MPI_DOUBLE, 0, MPI_COMM_WORLD);

    //if(ProcNum == 1)
        ll* larr = new ll[N];

    sTime = MPI_Wtime();

    for(ll j = 0; j < 100; j++){
        if(j % 2 == 0){
            s = 0;
            r = 1;
            if(ProcNum == 0)
                MPI_Send(arr, N, MPI_LONG_LONG, r, 0, MPI_COMM_WORLD);
            else if(ProcNum == 1)
                MPI_Recv(larr, N, MPI_LONG_LONG, s, MPI_ANY_TAG, MPI_COMM_WORLD, &Status);
        } else {
            s = 1;
            r = 0;
            if(ProcNum == 1)
                MPI_Send(larr, N, MPI_LONG_LONG, r, 0, MPI_COMM_WORLD);
            else if(ProcNum == 0)
                MPI_Recv(arr, N, MPI_LONG_LONG, s, MPI_ANY_TAG, MPI_COMM_WORLD, &Status);
        }
    }

    MPI_Barrier(MPI_COMM_WORLD);
    eTime = MPI_Wtime();

    string Time = to_string_with_precision(eTime - sTime);
    Time[1] = ',';

    if(ProcNum == 0)
            cout << "Длительность: " << Time << endl;

    MPI_Finalize();

    return 0;
}
