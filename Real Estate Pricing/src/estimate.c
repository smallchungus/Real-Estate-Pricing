#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>

double **transpose(double **matrix, double **matrixb, int row, int col)
{
    // double temp = 0;
    for (int i = 0; i < col; i++)
    {
        for (int j = 0; j < row; j++)
        {
            matrixb[i][j] = matrix[j][i];
            // printf (" %lf ", matrixb[i][j]);
        }
        // printf("\n");
    }
    return matrixb;
}

double **divideRow(double **matrix, int row, int col, double dividor)
{
    // printf("this is the dividor function\n");
    // printf("this is row %i and this is col %i\n", row, col);
    for (int j = 0; j < col; j++)
    {
        matrix[row][j] = matrix[row][j] / dividor;
        /* printf("%lf ", matrix[row][j]); */
    }
    // printf("\n");
    return matrix;
}

double **multiplyRow(double **matrix, int inpRow, int col, double multiple)
{
    for (int j = 0; j < col; j++)
    {
        // matrix[inpRow][j] = printf ( "this is multiply row %lf ", matrix[inpRow][j]);
    }
    /*   printf("\n"); */
    return matrix;
}

double **subtractmult(double **matrix, int rowA, int rowB, int col, double multiple, int inpRow)
{

    // printf("subtract is called \n");
    // printf("this is row%i, this is col%i, and this is input row%i\n", rowA, col, inpRow);
    for (int j = 0; j < col; j++)
    {

        matrix[rowA][j] = matrix[rowA][j] - (matrix[inpRow][j] * multiple);
        // printf("this is subtract row %lf, this is row%i and this is col %i\n", matrix[rowA][j], rowA, j);
    }
    // printf("\n");
    return matrix;
}

double **multiplyMatrices(double **matrix, double **matrixb, double **resultMat, int resRow, int resCol, int rowb, int colb)
{

    double sum = 0;
    for (int x = 0; x < resRow; x++)
    {
        for (int y = 0; y < resCol; y++)
        {
            for (int z = 0; z < rowb; z++)
            {
                sum += (matrix[x][z] * matrixb[z][y]);
                //   printf("THISIS THE SUM %lf\n", matrix[x][y]);
            }
            resultMat[x][y] = sum;
            // printf("this is x %i and this is y %i and this is what's written %lf\n",x,y, resultMat[x][y]);
            sum = 0;
        }
    }
    return resultMat;
}
double **multiplyPrice(double **matrix, double **matrixb, double **resultMat, int rowA, int colB, int rowB)
{
    double sum = 0;

    for (int i = 0; i < colB; i++)
    {
        for (int j = 0; j < colB; j++)
        {
            sum += (matrix[i][j] * matrixb[j][0]);
            //printf("THISIS THE SUM %lf this is i %i and this is j %i, this is matrix[i][j]%lf and this is matrix[j][0]%lf \n", sum, i, j, matrix[i][j], matrixb[j][0]);
        }
        resultMat[i][0] = sum;
        //printf("this is x %i y is 0 and this is what's written %lf\n", i, resultMat[i][0]);
        sum = 0;
    }
    return resultMat;
}

int main(int argc, char *argv[])
{

    FILE *train;
    train = fopen(argv[1], "r");

    char isThisTrain[10];
    int row, col;
    double num;
    fscanf(train, "%s\n", isThisTrain);
    if (strcmp(isThisTrain, "train") != 0)
    {
        //  printf("error");
        return EXIT_FAILURE;
    }

    fscanf(train, "%d\n", &col);
    fscanf(train, "%d\n", &row);
    // int rowA, colB, rowB;
    // int colB;

    double **inputMat = (double **)malloc(row * sizeof(double *));
    double **inputMatb = (double **)malloc(row * sizeof(double *));
    double **transposeMat = (double **)malloc((col + 1) * sizeof(double *));
    // double **transposeRes = (double **)malloc((col+1) * sizeof(double *));
    double **inverse = (double **)malloc(row * sizeof(double *));
    // double **resultMat = (double **)malloc(row * sizeof(double *));
    double **priceMat = (double **)malloc(row * sizeof(double *));
    double **priceMatOver = (double **)malloc(row * sizeof(double *));
    //  double ** dataInput = (double **) malloc (row * sizeof(double*));
    //  priceMat[0] = (double *)malloc( col * sizeof(double*));
    //  double **tempInp = (double **)malloc (row * sizeof(double*));
    //  double **tempInv = (double **)malloc (row * sizeof(double*));

    col = col + 1;

    for (int h = 0; h < row; h++)
    {
        inputMat[h] = (double *)malloc(col * sizeof(double *));

        inputMatb[h] = (double *)malloc(col * sizeof(double *));
        inverse[h] = (double *)malloc(row * sizeof(double *));
        // resultMat[h] = (double *)malloc(col * sizeof(double *));
        priceMat[h] = (double *)malloc(col * sizeof(double *));
        // priceMatOver[h] = (double *)malloc(col * sizeof(double *));
        //    dataInput[h] = (double *) malloc (col * sizeof(double*));
        //     tempInp[h] = (double *)malloc (col * sizeof(double*));
        //    tempInv[h] = (double *)malloc (col * sizeof(double*));
    }
    for (int i = 0; i < row; i++)
    {
        priceMatOver[i] = (double *)malloc(row * sizeof(double *));
    }
    for (int h = 0; h < col; h++)
    {
        transposeMat[h] = (double *)malloc(row * sizeof(double *));
        // transposeRes[h] = (double *)malloc(row * sizeof(double *));
    }

    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            fscanf(train, "%lf/t", &num);
            inputMat[i][j] = num;
            // printf ("%lf ", inputMat[i][j]);
        }
        // printf("\n");
        fscanf(train, "\n");
    }
    // printf ("done with input");

    // initialize the last column which is the prices
    for (int i = 0; i < row; i++)
    {
        priceMat[i][0] = inputMat[i][col - 1];
        //printf("the price mat %lf the row is %i, the col is %i \n", priceMat[i][0], row, col);
    }

    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            if (j == 0)
                inputMatb[i][j] = 1;
            else
                inputMatb[i][j] = inputMat[i][j - 1];
            // printf ("inputMatb before transpose %lf ", inputMatb[i][j] );
        }
        //    printf ("\n");
    }
    fclose(train);
    // we create matrix x because the matrix given isn't matrix x
    // so we kind of have to do it over again.
    for (int i = 0; i < row; i++)
    {
        for (int j = 0; j < col; j++)
        {
            inputMat[i][j] = inputMatb[i][j];
            //          printf ("inputMat  %lf ", inputMatb[i][j] );
        }
        //    printf("\n");
    }
    // we define stuff here.

    // double **transposeMat = (double **)malloc(row * sizeof(double *));
    // double **inverse = (double **)malloc(row * sizeof(double *));
    double **resultMat = (double **)malloc(col * sizeof(double *));
    // double **priceMatOver = (double **)malloc(row * sizeof(double *));

    for (int h = 0; h < col; h++)
    {
        //    transposeMat[h] = (double *)malloc(col * sizeof(double *));
        //    inverse[h] = (double *)malloc(col * sizeof(double *));
        resultMat[h] = (double *)malloc(col * sizeof(double *));
        // priceMatOver[h] = (double *)malloc(col * sizeof(double *));
    }

    // transpose the matrix
    // so now inputMat contains the ranspose of the matrix
    // inputMatb contains the original matrix
    transposeMat = transpose(inputMatb, transposeMat, row, col);
    resultMat = multiplyMatrices(transposeMat, inputMatb, resultMat, col, col, row, col);

    //printf("this is input mat after multplying\n");
    for (int i = 0; i < col; i++)
    {
        for (int j = 0; j < col; j++)
        {
            //printf("%lf ", resultMat[i][j]);
        }
        //printf("\n");
    }

    for (int i = 0; i < col; i++)
    {
        for (int j = 0; j < col; j++)
        {
            if (i == j)
                inverse[i][j] = 1;
            else
            {
                inverse[i][j] = 0;
            }
            //printf("%lf ", inverse[i][j]);
        }
        //printf("\n");
    }
    for (int p = 0; p < col; p++)
    {
        double dividor = resultMat[p][p];
        resultMat = divideRow(resultMat, p, col, dividor);
        inverse = divideRow(inverse, p, row, dividor);
        for (int i = p + 1; i < col; i++)
        {
            double multiple = resultMat[i][p];
            // printf("this is multiple %lf\n", multiple);
            // printf ("this is the multiple %lf\n", multiple);
            resultMat = subtractmult(resultMat, i, p, col, multiple, p);
            inverse = subtractmult(inverse, i, p, row, multiple, p);
        }
    }
    // printf("FINISHED LOWER TRIANGULAR \n");
    for (int p = col - 1; p > 0; p--)
    {
        for (int i = p - 1; i >= 0; i--)
        {
            double multiple = resultMat[i][p];
            // printf("THIS IS SECOND MULTIPLE %lf", multiple);
            resultMat = subtractmult(resultMat, i, p, col, multiple, p);
            inverse = subtractmult(inverse, i, p, row, multiple, p);
        }
    }
    // colB = 1;
    double **transposeRes = (double **)malloc((col) * sizeof(double *));

    for (int h = 0; h < col; h++)
    {
        // transposeMat[h] = (double *)malloc(row * sizeof(double *));
        transposeRes[h] = (double *)malloc((row + 1) * sizeof(double *));
    }
    transposeRes = multiplyMatrices(inverse, transposeMat, transposeRes, col, row, col, row);

    // we are on the last home streth multiplying price mat by the inverse have to figure this out
    priceMatOver = multiplyMatrices(transposeRes, priceMat, priceMatOver, col, 1, row, col);

    //  printf("this is input mat after dividing\n");
    for (int i = 0; i < col; i++)
    {
        for (int j = 0; j < col; j++)
        {
          //  printf("%lf ", inverse[i][j]);
        }
     //   printf("\n");
    }
    //  printf("this is inverse mat after dividing\n");
    for (int i = 0; i < col; i++)
    {
        for (int j = 0; j < row; j++)
        {
           // printf("%lf ", transposeRes[i][j]);
        }
       //printf("\n");
    }
    //printf("this is priceMat after multiplying\n");
    //for (int i = 0; i < col; i++)
    //{
        // for (int j = 0; j < row; j++)
       //printf("%lf\n", priceMatOver[i][0]);
    //}
    // FILE *data;
    train = fopen(argv[2], "r");
    int dataRow, dataCol;
    double dataNum;
    char isThisData[10];
    fscanf(train, "%s\n", isThisData);

    if (strcmp(isThisData, "data") != 0)
    {
        // printf("error");
        return EXIT_FAILURE;
    }
    fscanf(train, "%d\n", &dataCol);
    fscanf(train, "%d\n", &dataRow);
    // printf("%i", dataCol);

    double **dataInputTHIS = (double **)malloc(dataRow * sizeof(double *));
    // double newArray [dataRow][dataCol+1];
    double **dataInputb = (double **)malloc(dataRow * sizeof(double *));
    double **res = (double **)malloc(dataRow * sizeof(double *));

    for (int i = 0; i < dataRow; i++)
    {
        dataInputTHIS[i] = (double *)malloc(dataCol * sizeof(double *));
        dataInputb[i] = (double *)malloc((dataCol + 1) * sizeof(double *));
        res[i] = (double *)malloc(dataCol * sizeof(double *));
    }

    for (int i = 0; i < dataRow; i++)
    {
        for (int j = 0; j < dataCol; j++)
        {
            fscanf(train, "%lf/t", &dataNum);
            dataInputTHIS[i][j] = dataNum;
            // printf("%lf this is row%i and this is col %i ", dataInputTHIS[i][j], i, j);
        }
        // printf("\n");
        fscanf(train, "\n");
    }

    fclose(train);
     for (int i = 0; i < dataRow; i++)
    {
        for (int j = dataCol; j >= 0; j--)
        {
            if (j == 0)
                dataInputb[i][j] = 1;
            else
            {
                dataInputb[i][j] = dataInputTHIS[i][j - 1];
            }
            //printf("this is dataInput %lf", dataInputb[i][j]);
        }
        //printf("\n");
    }
     res = multiplyMatrices(dataInputb, priceMatOver, res, dataRow, 1, col, 1);
 
    for ( int i =0; i < dataRow; i ++){
        double num = (res[i][0]);
        int b = (int)(num < 0 ? (num - 0.5) : (num + 0.5));
        printf("%i", b);
        printf("\n");
    }



    for (int a = 0; a < row; a++)
    {
        free(inputMat[a]);
        free(inputMatb[a]);
        free(inverse[a]);
        free(priceMat[a]);
        free(priceMatOver[a]);
    }
    for (int a = 0; a < col; a++)
    {
        free(transposeMat[a]);
        free(transposeRes[a]);
        free(resultMat[a]);
    }
    free(transposeMat);
    free(transposeRes);
    free(priceMatOver);
    free(inputMat);
    free(inverse);
    free(inputMatb);
    free(resultMat);
    free(priceMat);

    for (int i = 0; i < dataRow; i++)
    {
        free(dataInputTHIS[i]);
        free(dataInputb[i]);
        free(res[i]);
    }

    free(dataInputTHIS);
    free(dataInputb);
    free(res);

    // free ( resultMat);
    return EXIT_SUCCESS;
}
