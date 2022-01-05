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
        ld eTime, sTime, gres;
        ll i, N = 1e8;

        MPI_Init(&argc, &argv);
        MPI_Comm_rank(MPI_COMM_WORLD, &ProcNum);
        MPI_Comm_size(MPI_COMM_WORLD, &ProcRank);
        MPI_Barrier(MPI_COMM_WORLD);

        sTime = MPI_Wtime();

        ll lN = N/ProcRank;
        ll a = 10;
        ll b = 20;
        ld h = ld(b-a)/ld(N);
        ld buf, res;
        for(ll i = 1+ProcNum; i < lN; i+=ProcNum+1){
                buf = a + i*h;
                res += buf*buf - 2*buf;
        }

        res *= h;

        MPI_Reduce(&res, &gres, 1, MPI_DOUBLE, MPI_SUM, 0, MPI_COMM_WORLD);
        MPI_Barrier(MPI_COMM_WORLD);

        eTime = MPI_Wtime();
        string pTime = to_string_with_precision(eTime - sTime);

        pTime[1] = ',';

        if(ProcNum == 0){
                cout << "Данные: " << N << "\n";
                cout << "Длительность: " << pTime << "\n";
        }
        MPI_Finalize();

    return 0;
}
