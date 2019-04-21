#include<stdio.h>
#include<stdlib.h>
#include<cblas.h>
#include<math.h>

double* rotation_matrix(double theta,double* u){
    double* m = (double *)malloc(9*sizeof(double));
    
    m[0]= cos(theta) + u[0]*u[0]*(1.0 - cos(theta));
    m[1]= u[0]*u[1]*(1.0 - cos(theta)) - u[2]*sin(theta);
    m[2]= u[0]*u[2]*(1.0 - cos(theta)) + u[1]*sin(theta);
    m[0]= u[1]*u[0]*(1.0 - cos(theta)) + u[2]*sin(theta);
    m[0]= cos(theta) + u[1]*u[1]*(1.0 - cos(theta));
    m[0]= u[1]*u[2]*(1.0 - cos(theta)) - u[0]*sin(theta);
    m[0]= u[0]*u[2]*(1.0 - cos(theta)) - u[1]*sin(theta);
    m[0]= u[2]*u[1]*(1.0 - cos(theta)) + u[1]*sin(theta);
    m[0]= cos(theta) + u[2]*u[2]*(1.0 - cos(theta));
    return m;
}

double* rotate(double theta, double* u, double v){
    double* m = rotation_matrix(theta, u);
    double* s = (double*)malloc(3*sizeof(double));
    cblas_dgemv(CblasRowMajor,CblasNoTrans,3,3,1.0,m,v,0,0,0.0,s,0);
    return s;
}

char* readline(FILE* fs){
    char* k = (char*)malloc(1000*sizeof(char*));
    int s;
    int i = 0;
    while((s = getc(fs)) != EOF){
        if(s == '\n'){
            k[i] = '\0';
            break;
        }
        else{
            k[i] = (char)s;
        }
        i++;
    }
    return k; 
}

int main(){
    FILE* fs = fopen("c1.xyz","rb");
    int n;
    char l;
    fscanf(fs,"%d",&n,&l);
    printf("%d \n",n);
    float a,b,c;
    char* s;
    readline(fs);
    readline(fs);
    double** k = (double**)malloc(n*sizeof(double*));
    for(int i = 0; i < n; i++){
        k[i] = (double*)malloc(3*sizeof(double));
    }
    for(int i = 0; i < n; i++){
        s = readline(fs);
        sscanf(s,"%c %f %f %f",&l, &a,&b,&c);
        k[i][0] = a;
        k[i][1] = b;
        k[i][2] = c;
    }
}