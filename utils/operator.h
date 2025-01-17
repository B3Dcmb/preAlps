/******************************************************************************/
/* Author     : Olivier Tissot                                                */
/* Creation   : 2016/08/05                                                    */
/* Description: Definition of the linear operator                             */
/******************************************************************************/


/******************************************************************************/
/*                                  INCLUDE                                   */
/******************************************************************************/
#ifndef OPERATOR_H
#define OPERATOR_H

/* STD */
#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>
#include <string.h>
/* MPI */
#include <mpi.h>
/* CPaLAMeM */
//#include <cpalamem_macro.h>
//#include <cpalamem_instrumentation.h>
#include <cplm_matcsr.h>

#include <cplm_matdense.h>
#include <cplm_v0_ivector.h>

/*
#include <mat_load_mm.h>
#include <metis_interface.h>
#include <matmult.h>

*/
/* preAlps */
#include <preAlps_utils.h>
/******************************************************************************/

/******************************************************************************/
/*                                    CODE                                    */
/******************************************************************************/

/*
 * Read a sparse matrix from file (mtx or petsc binary) then partition it
 * using METIS K-Way algorithm into the number of processor in the communicator
 * comm and distribute it among those processors.
 * input: matrixFilename: MatrixMarket or PETSc binary file
 *        comm          : MPI communicator
 */
int  preAlps_OperatorBuild(const char* matrixFilename, MPI_Comm comm);

/*
 * Read a sparse matrix from file (mtx or petsc binary) and a corresponding RHS form txt fil
 * then partition them using METIS K-Way algorithm into the number of processor in the communicator
 * comm and distribute them among those processors.
 * input: matrixFilename: MatrixMarket or PETSc binary file
 *        rhsFilename   : txt file
 *        comm          : MPI communicator
 * output: rhs          : the corresponding rhs permuted and distributed
 */
int  preAlps_OperatorRHSBuild(const char* matrixFilename, const char* rhsFilename, double** rhs, MPI_Comm comm);


/* Setup a matrix vector product without permuting the matrix. Useful for the cases where the matrix has already been partitioned */
int preAlps_OperatorBuildNoPerm(CPLM_Mat_CSR_t *locA, int *idxRowBegin, int nbBlockPerProcs, MPI_Comm comm);

/*
 * Release memory allocated during preAlp_OperatorBuild.
 */
void preAlps_OperatorFree();

/*
 * Print informations about the operator.
 */
void preAlps_OperatorPrint(int rank);

/*
 * Apply the operator to a group of vector X and put the result into AX.
 * input : X : CPLM_Mat_Dense_t
 * output: AX: CPLM_Mat_Dense_t
 */
int  preAlps_OperatorGetSizes(int* M, int* m);

/*
 * Return the local part of the operator as a row panel CSR matrix.
 */
int  preAlps_BlockOperator(CPLM_Mat_Dense_t* X, CPLM_Mat_Dense_t* AX);

/*
 * Return the global size and local size of the operator A.
 */
int  preAlps_OperatorGetA(CPLM_Mat_CSR_t* A);

/*
 * Return a vector containing the global row index corresponding to the beginning
 * of each row panel.
 */
int  preAlps_OperatorGetRowPosPtr(int** rowPos, int* sizeRowPos);

/*
 * Return a vector containing the global col index corresponding to the beginning
 * of each local column block (column block i corresponds to values at the interface
 * between processor i and my_rank)
 */
int  preAlps_OperatorGetColPosPtr(int** colPos, int* sizeColPos);

/*
 * Return a vector containing the indexes of the neighbor processors.
 */
int  preAlps_OperatorGetDepPtr(int** dep, int* sizeDep);
/******************************************************************************/

#endif
