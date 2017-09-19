/******************************************************************************/
/* Author     : Olivier Tissot, Simplice Donfack                              */
/* Creation   : 2016/09/05                                                    */
/* Description: Definition of the preconditioner                              */
/******************************************************************************/


/******************************************************************************/
/*                                  INCLUDE                                   */
/******************************************************************************/
#ifndef PRECONDITIONER_H
#define PRECONDITIONER_H

/* STD */
#include <stdio.h>
#include <stdlib.h>
/* MPI */
#include <mpi.h>
/* MatCSR */
#include <cpalamem_macro.h>
#include <cpalamem_instrumentation.h>
#include <mat_csr.h>
#include <mat_dense.h>

/* From which side the preconditioner needs to be applied: LEFT or SPLITTED */
typedef enum {
  LEFT_PREC,
  SPLIT_PREC
} Prec_Side_t;

/* Preconditioner type */
typedef enum {
  PREALPS_NOPREC,       /* No preconditioner*/
  PREALPS_BLOCKJACOBI,  /* Block Jacobi preconditioner*/
  PREALPS_LORASC,       /* Lorasc */
  PREALPS_PRESC         /* Preconditioner based on the Schur-Complement */
} Prec_Type_t;

/******************************************************************************/

/******************************************************************************/
/*                                    CODE                                    */
/******************************************************************************/
int  PrecondCreate(Prec_Type_t precond_type,
                   Mat_CSR_t* A,
                   int* rowPos,
                   int sizeRowPos,
                   int* colPos,
                   int sizeColPos,
                   int* dep,
                   int sizeDep);
int  PrecondApply(Prec_Type_t precond_type, Mat_Dense_t* A_in, Mat_Dense_t* B_out);
void PrecondFree(Prec_Type_t precond_type);
/* /\* Right preconditioner *\/o */
/* // User functions */
/* int RightPrecondCreate(); // TODO */
/* int RightPrecondApply();  // TODO */
/* int RightPrecondFree();   // TODO */
/* // ParBCG internals */
/* int RightPrecondInitialize(); // TODO */
/* int RightPrecondFinalize();   // TODO */
/* Left preconditioner */
// User functions
int LeftPrecondCreate(); // TODO
int LeftPrecondApply();  // TODO
int LeftPrecondFree();   // TODO
// ParBCG internals
int LeftPrecondInitialize(); // TODO
int LeftPrecondFinalize();   // TODO

/******************************************************************************/

#endif