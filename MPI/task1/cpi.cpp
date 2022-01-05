#include <mpi.h>
#include <cstdlib>
#include <iostream>

typedef long long ll;

using namespace std;

int main(int argc, char* argv[]){
    int ProcNum, ProcRank;
    double eTime, sTime, Time;
    ll i, N=100000000, mn;
    ll* array = new ll[N];

    MPI_Init(&argc, &argv);
    MPI_Comm_rank(MPI_COMM_WORLD, &ProcNum);
    MPI_Comm_size(MPI_COMM_WORLD, &ProcRank);
    MPI_Barrier(MPI_COMM_WORLD);

    srand((unsigned)(time(0)));
    if (ProcNum == 0){
            for (i = 0; i < N; i++)
                    array[i] = rand()%1000 + 1;
    }
    sTime = MPI_Wtime();

    MPI_Bcast(&N, 1, MPI_LONG_LONG, 0, MPI_COMM_WORLD);
    ll lmn, lN = N/ProcRank;
    ll* buf = new ll[lN];
    MPI_Scatter(array, lN, MPI_LONG_LONG, buf, lN, MPI_LONG_LONG, 0, MPI_COMM_WORLD);

    lmn = buf[0];
    for (long long j = 1; j < lN; j++)
           if (buf[j] < lmn)
                    lmn = buf[j];

    MPI_Reduce(&lmn, &mn, 1, MPI_LONG_LONG, MPI_MIN, 0, MPI_COMM_WORLD);
    MPI_Barrier(MPI_COMM_WORLD);

    eTime = MPI_Wtime();
    Time = eTime - sTime;

    if(ProcNum == 0){
            cout << "Мин: " << mn << "\n";
            cout << "Время: " << Time << "\n";
    }
    MPI_Finalize();
    return 0;
}
