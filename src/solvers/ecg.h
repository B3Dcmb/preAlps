/******************************************************************************/
/* Author     : Olivier Tissot                                                */
/* Creation   : 2016/06/24                                                    */
/* Description: Enlarged Preconditioned C(onjugate) G(radient)                */
/******************************************************************************/

/******************************************************************************/
/*                                  INCLUDE                                   */
/******************************************************************************/
#ifndef BCG_H
#define BCG_H

/* STD */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
/* MPI */
#include <mpi.h>
/* CPaLAMeM */
#include <mat_csr.h>
#include <mat_dense.h>
#include <ivector.h>
#include <dvector.h>
#include <cholqr.h>
#include <matmult.h>
#include <kernels.h>
/* Preconditioner */
#include <precond.h>
/* CPaLAMeM */
#include <cpalamem_macro.h>
#include <cpalamem_instrumentation.h>
/* MKL */
#include<mkl.h>

/* A-orthonormalization algorithm */
typedef enum {
  ORTHOMIN,
  ORTHODIR
} Ortho_Alg_t;
/* Block size reduction */
typedef enum {
  ALPHA_RANK,
  NO_BS_RED
} Block_Size_Red_t;

typedef struct {
  /* Array type variables */
  double*           b;         /* Right hand side */
  Mat_Dense_t*      X;         /* Approximated solution */
  Mat_Dense_t*      R;         /* Residual */
  Mat_Dense_t*      P;         /* Descent direction */
  Mat_Dense_t*      AP;        /* A*P */
  Mat_Dense_t*      P_prev;    /* Previous descent direction */
  Mat_Dense_t*      AP_prev;   /* A*P_prev */
  Mat_Dense_t*      alpha;     /* Descent step */
  Mat_Dense_t*      beta;      /* Step to construt search directions */
  Mat_Dense_t*      gamma;     /* Step to construct odir search directions */
  Mat_Dense_t*      Z;         /* Extra memory */
  Mat_Dense_t*      H;         /* Descent directions needed to reduce block size */
  Mat_Dense_t*      AH;        /* A*H */
  double*           work;      /* working array */
  int*              iwork;     /* working array */

  /* Single value variables */
  double            normb;     /* norm_2(b) */
  double            res;       /* norm_2 of the residual */
  int               iter;      /* Iteration */

  /* Options and parameters */
  int               globPbSize;   /* Size of the global problem */
  int               locPbSize;    /* Size of the local problem */
  int               maxIter;      /* Maximum number of iterations */
  int               enlFac;       /* Enlarging factor */
  double            tol;          /* Tolerance */
  Ortho_Alg_t       ortho_alg;    /* A-orthonormalization algorithm */
  Block_Size_Red_t  bs_red;       /* Block size reduction */
  MPI_Comm          comm;         /* MPI communicator */
} ECG_t;

/******************************************************************************/

/******************************************************************************/
/*                                    CODE                                    */
/******************************************************************************/

int ECGMalloc(ECG_t* ecg);
int ECGInitialize(ECG_t* ecg, double* rhs, int* rci_request);
int ECGSplit(double* x, Mat_Dense_t* XSplit, int colIndex);
int ECGIterate(ECG_t* ecg, int* rci_request);
int ECGStoppingCriterion(ECG_t* ecg, int* stop);
void ECGFree(ECG_t* ecg);
int ECGFinalize(ECG_t* ecg, double* solution);
void ECGPrint(ECG_t* ecg);

/******************************************************************************/

#endif