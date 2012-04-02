/*
 * Copyright (c) 2011      The University of Tennessee and The University
 *                         of Tennessee Research Foundation.  All rights
 *                         reserved.
 *
 *
 *     @author Azzam Haidar
 *     @author Stan Tomov
 *
 *     @precisions normal d -> s
 *
 */

#include "common_magma.h"
#include "magma_dbulgeinc.h"
// === Define what BLAS to use ============================================

// === End defining what BLAS to use ======================================
 

//////////////////////////////////////////////////////////////
//          DSTEDC          Divide and Conquer for tridiag
//////////////////////////////////////////////////////////////
extern "C" void  magma_dstedc_withZ(char JOBZ, magma_int_t N, double *D, double * E, double *Z, magma_int_t LDZ) {
  double *WORK;
  magma_int_t *IWORK;
  magma_int_t LWORK, LIWORK;
  magma_int_t INFO;
  magma_int_t NxN=N*N;
   
  if(JOBZ=='V'){
        LWORK  = 1 + 3*N + 3*N*((magma_int_t)log2(N)+1) + 4*N*N+ 256*N; 
        LIWORK =  6 + 6*N + 6*N*((magma_int_t)log2(N)+1) + 256*N;
  }else if(JOBZ=='I'){
        LWORK  = 2*N*N+256*N+1; 
          LIWORK = 256*N;
  }else if(JOBZ=='N'){
        LWORK  = 256*N+1; 
          LIWORK = 256*N;  
  }else{
          printf("ERROR JOBZ %c\n",JOBZ);
          exit(-1);
  }

  WORK = (double*) malloc( LWORK*sizeof( double) );
  IWORK = (magma_int_t*) malloc( LIWORK*sizeof( magma_int_t) );

  lapackf77_dstedc(&JOBZ, &N, D, E, Z, &LDZ, WORK,&LWORK,IWORK,&LIWORK,&INFO);

  if(INFO!=0){
        printf("=================================================\n");
        printf("DSTEDC ERROR OCCURED. HERE IS INFO %d \n ",INFO);
        printf("=================================================\n");
          //assert(INFO==0);
  }


  free( IWORK );
  free( WORK );
}
//////////////////////////////////////////////////////////////

