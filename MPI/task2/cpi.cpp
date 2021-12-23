#include <mpi.h>
#include <cstdlib>
#include <iostream>

typedef long long ll;

using namespace std;

int main(int argc, char* argv[]){
        int ProcNum, ProcRank;
        double eTime,sTime, Time;
        ll i, N=10000, sm;
        ll* array1 = new ll[N];
        ll* array2 = new ll[N];

        MPI_Init(&argc, &argv);
        MPI_Comm_rank(MPI_COMM_WORLD, &ProcNum);
        MPI_Comm_size(MPI_COMM_WORLD, &ProcRank);
        MPI_Barrier(MPI_COMM_WORLD);

        srand((unsigned)(time(0)));
        if(ProcNum == 0){
                for (i = 0; i < N; i++)
                        array1[i] = rand()%1000 + 1;
                for (i = 0; i < N; i++)
                        array2[i] = rand()%1000 + 1;
        }
        MPI_Bcast(&N, 1, MPI_LONG_LONG, 0, MPI_COMM_WORLD);

        ll* buf1 = new ll[N/ProcRank];
        ll* buf2 = new ll[N/ProcRank];
        ll lsm = 0;
        sTime = MPI_Wtime();

        MPI_Scatter(array1, N/ProcRank, MPI_LONG_LONG, buf1, N/ProcRank, MPI_LONG_LONG, 0, MPI_COMM_WORLD);
        MPI_Scatter(array2, N/ProcRank, MPI_LONG_LONG, buf2, N/ProcRank, MPI_LONG_LONG, 0, MPI_COMM_WORLD);

        for(ll j = 0; j < N/ProcRank; j++)
                lsm += buf1[j]*buf2[j];

        MPI_Reduce(&lsm, &sm, 1, MPI_LONG_LONG, MPI_SUM, 0, MPI_COMM_WORLD);
        MPI_Barrier(MPI_COMM_WORLD);
        eTime = MPI_Wtime();
        Time =eTime - sTime;

        if(ProcNum == 0){
                cout << "Скалярное произведения: " << sm << "\n";
                cout << "Время: " << Time << "\n";;
        }
        MPI_Finalize();
        return 0;
}
