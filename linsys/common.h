#ifndef COMMON_H_GUARD
#define COMMON_H_GUARD

#include "glbopts.h"
#include "cones.h"
#include "amatrix.h"

#define MIN_SCALE (1e-3)
#define MAX_SCALE (1e3)

/* underscore for blas / lapack, single or double precision */
#ifdef NOBLASUNDERSCORE
	#ifndef FLOAT
		#define BLAS(x) d ## x
	#else
		#define BLAS(x) s ## x
	#endif
#else
	#ifndef FLOAT
		#define BLAS(x) d ## x ## _
	#else
		#define BLAS(x) s ## x ## _
	#endif
#endif

#ifdef MATLAB_MEX_FILE
typedef ptrdiff_t blasint;
#elif defined BLAS64
#include <stdint.h>
typedef int64_t blasint;
#else
typedef int blasint;
#endif

void BLAS(scal)(blasint *n, scs_float *da, scs_float *dx, blasint *incx);
scs_float BLAS(nrm2)(blasint *n, scs_float *x, blasint *incx);
void BLAS(gemv)(char *trans, blasint *m, blasint *n, scs_float * alpha, scs_float *a, blasint *lda, const scs_float *x, blasint *incx,
		scs_float *beta, scs_float *y, blasint *incy);
void BLAS(axpy)(blasint *n, scs_float *da, scs_float *dx, blasint *incx, scs_float *dy, blasint *incy_);
void BLAS(syrk)(char *uplo, char *trans, blasint *n, blasint *k, scs_float *alpha, scs_float *a, blasint *lda, scs_float *beta, 
        scs_float *c, blasint *ldc);

/* void BLAS(gemm)(char *transa, char *transb, blasint *m, blasint * n, blasint *k, scs_float *alpha, scs_float *a, blasint *lda,
        scs_float *b, blasint *ldb, scs_float *beta, scs_float *c, blasint *ldc); */

scs_int validateLinSys(Data *d);
void normalizeA(Data * d, Work * w, Cone * k);
void unNormalizeA(Data *d, Work * w);
void accumByAtrans(Data * d, Priv * p, const scs_float * x, scs_float * y);
void freeAMatrix(AMatrix * A);
#endif
