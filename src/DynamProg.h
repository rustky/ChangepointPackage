#define ERROR_TOO_MANY_SEGMENTS 1

int DynamProg(
    const double *data_ptr,
    const int Kmax,
    const int N_data,
    double *changepoint_ptr
);
