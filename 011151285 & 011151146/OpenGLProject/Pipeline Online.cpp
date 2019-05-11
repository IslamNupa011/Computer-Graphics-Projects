#include <bits/stdc++.h>
using namespace std;

struct Matrix
{
    double dim[4][4];

    Matrix()
    {
          for(int i=0;i<4;i++){

            for(int j=0;j<4;j++){

                if(i==j){
                dim[i][j]=1;
                }

                else{

                    dim[i][j]=0;
                }
            }
        }
    }
};

    void PrintMatrix(FILE* output)
    {
        /// Print the Matrix in output text file


        output = fopen ("output.txt", "a+");
        for(int i=0;i<4;i++){
        for(int j=0;j<4;j++){
        fprintf(output, "%lf ",dim[i][j]);
        }
         fprintf(output,"%s","\n");
        }
        fclose(output);

    }
};
void CopyMatrix(Matrix& dst, Matrix& src)
{
  for (int i=0; i<4; ++i)
   for (int j=0; j<4; ++j)
     dst[i][j] = src[i][j];
}


void MultMatrix(Matrix& product,Matrix& matrix1, Matrix& matrix2, Matrix& matrix3)
{
  for (int x=0; x<4; ++x)
    for (int y=0; y<4; ++y)
    {
      double sum = 0;
      for (int z=0; z<4; ++z)
        sum += matrix1[x][z] * matrix2[z][y];
      product[x][y] = sum;
    }
}

int main()
{
    stack <Matrix> S;
    S.push(Matrix());
    FILE* input;
    FILE* output;
    Matrix n;

    n.PrintMatrix(output);


    /// Take input from the text file scene.txt and show output in stage.txt file

    char command[10]; /// string for command inputs
    input=fopen("scene.txt","r");

    while(1)
    {
        fscanf(input, "%s", &command);
        cout<<command<<"\n";
        /// Input command from file

        if(strcmp(command, "triangle") == 0)
        {
           /// Do by yourself
           Matrix m1, m2, m3;

           m1[0][0] = 1.0; m1[0][1] = 0.0; m1[0][2] = 0.0;
           m1[1][0] = 0.0; m1[1][1] = 1.0; m1[1][2] = 0.0;
           m1[2][0] = 0.0; m1[2][1] = 0.0; m1[2][2] = 1.0;

           m2[0][0] = 0.0; m2[0][1] = 0.0; m2[0][2] = 0.0;
           m2[1][0] = 5.0; m2[1][1] = 0.0; m2[1][2] = 0.0;
           m2[2][0] = 0.0; m2[2][1] = 0.0; m2[2][2] = 0.0;

           MultMatrix(m3, m1, m2);


        else if(strcmp(command, "scale") == 0)
        {
            double xScale,yScale,zScale,m1[][],m2[][];
            /// Do by yourself
             m1[0][0]=xScale; m1[0][1]=0;   m1[0][2]=0;
             m1[1][0]=0;   m1[1][1]=yScale; m1[1][2]=0;
              m1[2][0]=0;   m1[2][1]=0;   m1[2][2]=1;

             MultMatrix(m2, m1, m);
             CopyMatrix(m, m2);
        }

        else if(strcmp(command, "translate") == 0)
        {
            /// Bonus
            /// Do by yourself
            int xTrans, int yTrans, int zTrans;
            double m1[][], m2[][];

            m1[0][0]=2.0;    m1[0][1]=0;    m1[0][2]=0;
            m1[1][0]=0;    m1[1][1]=2.0;    m1[1][2]=0;
            m1[2][0]=xTrans; m1[2][1]=yTrans; m1[2][2]=2.0;

            MultMatrix(m2, m1, m);
            CopyMatrix(m, m2);
        }

        else if (strcmp(command, "end") == 0)
        {
            /// Do by yourself
        }

    }

    /// Close both the input and output files

    return 0;
}

