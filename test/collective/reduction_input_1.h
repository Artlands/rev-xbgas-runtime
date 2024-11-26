
#define NELEMS 32
#define NPES 4 

const int input_data_0[NELEMS] = 
{
    0,   1,   3,   1,   2,   0,   0,   3,   3,   1,   1,   2,   0,   0,   3,   0,   2,   0,   3,   0, 
    2,   0,   0,   2,   3,   1,   3,   2,   1,   3,   2,   0
};

const int input_data_1[NELEMS] = 
{
    3,   0,   0,   3,   0,   3,   1,   2,   1,   2,   1,   1,   2,   2,   3,   3,   1,   3,   2,   0, 
    3,   2,   1,   2,   1,   1,   3,   1,   2,   2,   2,   2
};

const int input_data_2[NELEMS] = 
{
    0,   0,   1,   2,   3,   2,   2,   1,   2,   2,   2,   3,   0,   2,   0,   2,   1,   3,   0,   3, 
    1,   2,   3,   2,   3,   1,   0,   1,   3,   1,   3,   1
};

const int input_data_3[NELEMS] = 
{
    3,   2,   3,   1,   0,   2,   3,   2,   2,   3,   1,   3,   2,   3,   2,   0,   0,   0,   0,   3, 
    3,   2,   0,   3,   1,   2,   1,   3,   0,   1,   3,   2
};

const int* input_data[NPES] = {
  input_data_0,
  input_data_1,
  input_data_2,
  input_data_3
};

