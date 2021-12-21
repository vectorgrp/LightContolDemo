#ifndef VCAST_ORIGINAL_CODE
/* VectorCAST/Cover */
#ifndef VCAST_CONDITION_TYP
#define VCAST_CONDITION_TYP __int64
#endif

#ifndef VCAST_HAS_LONGLONG
#define VCAST_HAS_LONGLONG 1
#endif
#ifndef VCAST_MICROSOFT_LONG_LONG
#define VCAST_MICROSOFT_LONG_LONG 1
#endif

#ifdef __cplusplus
extern "C" {
#endif

#define VCAST_GLOBAL_BUFFER_OPTIMIZATIONS
/*
---------------------------------------------
-- Copyright 2020 Vector Informatik, GmbH. --
---------------------------------------------
*/

/* Defined variable usage for this file:

   Variable names that are indented apply only if the enclosing variable is set

   <<no defined variables set>>    : Output is written to the file TESTINSS.DAT

   VCAST_USE_STDOUT                : Output is written to stdout using puts
      VCAST_USE_PUTCHAR            : Output is written to stdout using putchar
      VCAST_USE_GH_SYSCALL         : Output is written to stdout using the GH syscall
                                     (For Green Hills INTEGRITY 178B)

   VCAST_CUSTOM_STD_OUTPUT         : custom user code required to write Output 
                                     to stdout or serial port interface
                                   : Need to also define VCAST_USE_STDOUT in order
                                     to set the stdout flag. 

   VCAST_CUSTOM_FILE_OUTPUT        : custom user file i/o code required to write 
                                     Output to TESTINSS.DAT 

   VCAST_USE_STD_STRING            : This define turns ON the use of memset from the
                                     system header string.h.

   VCAST_USE_STATIC_MEMORY         : No malloc is available, use alternate data.
      VCAST_MAX_MCDC_STATEMENTS    : The number of MCDC statement conditions 
                                     that can be reached when malloc is not 
                                     available. 
   VCAST_MAX_COVERED_SUBPROGRAMS   : The number of subprograms that may be
                                     covered. 
   VCAST_ENABLE_DATA_CLEAR_API     : Enable this macro to add the API
                                     VCAST_CLEAR_COVERAGE_DATA, which allows
                                     you to clear the currently collected
                                     coverage data during the execution of
                                     the instrumented executable.
   VCAST_ATTRIBUTE_CODE            : Allows the user to specify an attribute
                                     that will be placed before the ascii, 
                                     binary and subprogram coverage pool 
                                     global variables. This is useful for 
                                     putting this data in specific places
                                     in memory.
   VCAST_DUMP_CALLBACK             : If this is defined to a function name, 
                                     then when the user calls 
                                     VCAST_DUMP_COVERAGE_DATA, the function
                                     this was defined to will be called. The 
                                     purpose is to allow the users main loop
                                     to be given a chance to run within a 
                                     certain time frame.
   VCAST_FLUSH_DATA                : Use the flush system call after each
                                     string is written with fprintf in
                                     VCAST_WRITE_TO_INST_FILE_COVERAGE. The
                                     default is disabled. Define to any value
                                     to enable.
   VCAST_APPEND_WIN32_PID          : Append the process id to the TESTINSS.DAT
                                     file. This uses windows specific system
                                     calls to get the pid.
   VCAST_APPEND_POSIX_PID          : Append the process id to the TESTINSS.DAT
                                     file. This uses Posix specific system
                                     calls to get the pid.
   VCAST_APPEND_SECONDS_SINCE_EPOCH: Append the number of seconds since the
                                     epoch to the TESTINSS.DAT
                                     file. This uses the C library time() call.
*/

#ifndef __C_COVER_H__
#define __C_COVER_H__

#ifdef __cplusplus
extern "C" {
#endif

#ifndef VCAST_PRINTF_INTEGER 
#define VCAST_PRINTF_INTEGER "%d"
#endif
#ifndef VCAST_PRINTF_STRING
#define VCAST_PRINTF_STRING "%s"
#endif

#ifndef VCAST_MCDC_STORAGE_TYPE
#ifdef VCAST_UNSIGNED_LONG_MCDC_STORAGE
#define VCAST_MCDC_STORAGE_TYPE unsigned long
#else 
#ifdef VCAST_HAS_LONGLONG
#ifdef VCAST_MICROSOFT_LONG_LONG
#define VCAST_MCDC_STORAGE_TYPE unsigned __int64
#else 
#define VCAST_MCDC_STORAGE_TYPE unsigned long long
#endif /* VCAST_MICROSOFT_LONG_LONG */
#else 
#define VCAST_MCDC_STORAGE_TYPE unsigned long
#endif /* VCAST_HAS_LONGLONG */
#endif /* VCAST_UNSIGNED_LONG_MCDC_STORAGE */
#endif /* VCAST_MCDC_STORAGE_TYPE */

#ifdef __CUDACC__
/* Instrumentation for CUDA files replaces the "kernel launch"
 * syntax's triple-angle-brackets with a function-like 
 * VCAST_CUDA_KERNEL_LAUNCH() syntax for ease of parsing. 
 * This macro restores the original syntax so nvcc can 
 * process the file.
 */
#define VCAST_CUDA_KERNEL_LAUNCH(...) <<< __VA_ARGS__ >>>
#endif

/* CUDA-specific function decorators */
#ifdef __CUDA_ARCH__
#define VCAST_CUDA_HOST_DEVICE_FUNCTION __host__ __device__
#else
#define VCAST_CUDA_HOST_DEVICE_FUNCTION
#endif

/* AVL prototypes */
typedef struct vcast_mcdc_statement* VCAST_elementType;
struct VCAST_AVLNode;
typedef struct VCAST_AVLNode *VCAST_position;
typedef struct VCAST_AVLNode *VCAST_AVLTree;
VCAST_position vcast_find (VCAST_elementType VCAST_X, VCAST_AVLTree VCAST_T);
VCAST_AVLTree vcast_insert (VCAST_elementType VCAST_X, VCAST_AVLTree VCAST_T);

struct vcast_mcdc_statement
{
  VCAST_MCDC_STORAGE_TYPE mcdc_bits;
  VCAST_MCDC_STORAGE_TYPE mcdc_bits_used;
};
typedef struct vcast_mcdc_statement *vcast_mcdc_statement_ptr;

void VCAST_CLEAR_COVERAGE_DATA (void);
#ifndef VCAST_COVER_NO_STDIO
void VCAST_REGISTER_DUMP_AT_EXIT (void);
void VCAST_DUMP_COVERAGE_DATA (void);

int VCAST_WRITE_FN_CALL_ID(int unit, int id);
int VCAST_WRITE_STATEMENT_ID(int unit, int id);
int VCAST_WRITE_BRANCH_ID(int unit, int id, const char* TorF);
int VCAST_WRITE_OPTIMIZED_MCDC_ID(int unit, int id, char num_conditions,
                                  VCAST_MCDC_STORAGE_TYPE mcdc_bits, 
                                  VCAST_MCDC_STORAGE_TYPE mcdc_bits_used);
int VCAST_WRITE_FUNCTION_ID(int unit, int id);

int VCAST_WRITE_GLOBAL_FN_CALL_ID(int id);
int VCAST_WRITE_GLOBAL_STATEMENT_ID(int id);
int VCAST_WRITE_GLOBAL_BRANCH_ID(int id, const char* TorF);
int VCAST_WRITE_GLOBAL_OPTIMIZED_MCDC_ID(int id, char num_conditions,
                                         VCAST_MCDC_STORAGE_TYPE mcdc_bits, 
                                         VCAST_MCDC_STORAGE_TYPE mcdc_bits_used);
int VCAST_WRITE_GLOBAL_FUNCTION_ID(int id);
#endif /* VCAST_COVER_NO_STDIO */

#ifdef VCAST_COVERAGE_POINTS_AS_MACROS

/*
 * The instrumentation macros provide an alternative to the
 * instrumentation point functions, which are used by default. If you
 * need to add additional statements to the instrumentation points, we
 * suggest modifying the functions, and not the macros. First, ensure
 * the "Instrument using macros in c_cover.h" option is disabled and
 * then modify the functions of the same names in the c_cover_io.c file.
 *
 * The instrumentation point macros must be expressions or a
 * comma-separated list of expressions. To use them, enable the
 * "Instrument using macros in c_cover.h" option and reinstrument all
 * source files. Modification of the macros is allowed, but very
 * difficult.  You are strongly encouranged to verify coverage data when
 * using modified macros.
 */

#ifdef VCAST_GLOBAL_BUFFER_OPTIMIZATIONS
#ifdef VCAST_PACK_INSTRUMENTATION_STORAGE
#define VCAST_GLOBAL_FN_CALL_INSTRUMENTATION_POINT_REALTIME(id) (\
  ((vcast_coverage_bytes[id >> 3] & (((unsigned long)1) << id % 8)) == 0) ? \
  (vcast_coverage_bytes[id >> 3] |= (((unsigned long)1) << id % 8),         \
   VCAST_WRITE_GLOBAL_FN_CALL_ID(id)) : 1                       \
)
#else
#define VCAST_GLOBAL_FN_CALL_INSTRUMENTATION_POINT_REALTIME(id) (\
  (vcast_coverage_bytes[id] == 0) ? (vcast_coverage_bytes[id] = 1, VCAST_WRITE_GLOBAL_FN_CALL_ID(id)) : 1 \
)
#endif /* VCAST_PACK_INSTRUMENTATION_STORAGE */
#else
#ifdef VCAST_PACK_INSTRUMENTATION_STORAGE
#define VCAST_FN_CALL_INSTRUMENTATION_POINT_REALTIME(covdata, unit, id) (\
  ((covdata[id >> 3] & (((unsigned long)1) << id % 8)) == 0) ? \
  (covdata[id >> 3] |= (((unsigned long)1) << id % 8),         \
   VCAST_WRITE_FN_CALL_ID(unit, id)) : 1                       \
)
#else
#define VCAST_FN_CALL_INSTRUMENTATION_POINT_REALTIME(covdata, unit, id) (\
  (covdata[id] == 0) ? (covdata[id] = 1, VCAST_WRITE_FN_CALL_ID(unit, id)) : 1 \
)
#endif /* VCAST_PACK_INSTRUMENTATION_STORAGE */
#endif /* VCAST_GLOBAL_BUFFER_OPTIMIZATIONS */

/*************************************/
/* Use CUDA device-side code/buffer */
#ifdef __CUDA_ARCH__
#define VCAST_FN_CALL_INSTRUMENTATION_POINT_BUFFERED(covdata, id) (\
    atomicOr(&(((int*)(covdata ## _device))[id >> 5]),\
                (((unsigned long)1) << (id % 32)) ) )
/* Host-side code */
#else
#ifdef VCAST_GLOBAL_BUFFER_OPTIMIZATIONS
#ifdef VCAST_PACK_INSTRUMENTATION_STORAGE
#define VCAST_GLOBAL_FN_CALL_INSTRUMENTATION_POINT_BUFFERED(id) (  \
  vcast_coverage_bytes[id >> 3] |= (((unsigned long)1) << (id % 8)) \
)
#else
#define VCAST_GLOBAL_FN_CALL_INSTRUMENTATION_POINT_BUFFERED(id) (\
  vcast_coverage_bytes[id] = 1 \
)
#endif /* VCAST_PACK_INSTRUMENTATION_STORAGE */
#else
#if defined(VCAST_PACK_INSTRUMENTATION_STORAGE)
#define VCAST_FN_CALL_INSTRUMENTATION_POINT_BUFFERED(covdata, id) (\
  covdata[id >> 3] |= (((unsigned long)1) << (id % 8)) \
)
#else
#define VCAST_FN_CALL_INSTRUMENTATION_POINT_BUFFERED(covdata, id) (\
  covdata[id] = 1 \
)
#endif /* VCAST_PACK_INSTRUMENTATION_STORAGE */
#endif /* VCAST_GLOBAL_BUFFER_OPTIMIZATIONS */
#endif /* __CUDA_ARCH__ */
/*************************************/


#ifdef VCAST_GLOBAL_BUFFER_OPTIMIZATIONS
#define VCAST_GLOBAL_FN_CALL_INSTRUMENTATION_POINT_ANIMATION(id) (\
  VCAST_WRITE_GLOBAL_FN_CALL_ID(id) \
)
#else
#define VCAST_FN_CALL_INSTRUMENTATION_POINT_ANIMATION(unit, id) (\
  VCAST_WRITE_FN_CALL_ID(unit, id) \
)
#endif

#ifdef VCAST_GLOBAL_BUFFER_OPTIMIZATIONS
#if !defined(VCAST_PACK_INSTRUMENTATION_STORAGE)
#define VCAST_GLOBAL_STATEMENT_INSTRUMENTATION_POINT_REALTIME(id) ( \
  (vcast_coverage_bytes[id] == 0) ? (vcast_coverage_bytes[id] = 1, VCAST_WRITE_GLOBAL_STATEMENT_ID(id)) : 1 \
)
#else
#define VCAST_GLOBAL_STATEMENT_INSTRUMENTATION_POINT_REALTIME(id) ( \
  ((vcast_coverage_bytes[id >> 3] & (((unsigned long)1) << id % 8)) == 0) ? \
  (vcast_coverage_bytes[id >> 3] |= (((unsigned long)1) << id % 8), \
   VCAST_WRITE_GLOBAL_STATEMENT_ID(id)) : 1 \
)
#endif
#else
#if !defined(VCAST_PACK_INSTRUMENTATION_STORAGE)
#define VCAST_STATEMENT_INSTRUMENTATION_POINT_REALTIME(covdata, unit, id) (\
  (covdata[id] == 0) ? (covdata[id] = 1, VCAST_WRITE_STATEMENT_ID(unit, id)) : 1 \
)
#else
#define VCAST_STATEMENT_INSTRUMENTATION_POINT_REALTIME(covdata, unit, id) (\
  ((covdata[id >> 3] & (((unsigned long)1) << id % 8)) == 0) ? \
  (covdata[id >> 3] |= (((unsigned long)1) << id % 8), \
   VCAST_WRITE_STATEMENT_ID(unit, id)) : 1 \
)
#endif
#endif /* VCAST_GLOBAL_BUFFER_OPTIMIZATIONS */

/*************************************/
/* Use CUDA device-side code/buffer */
#ifdef __CUDA_ARCH__
#define VCAST_STATEMENT_INSTRUMENTATION_POINT_BUFFERED(covdata, id) \
   ( atomicOr(&(((int*)(covdata ## _device))[id >> 5]), (((unsigned long)1) << (id % 32))) )
/* Host-side code */
#else
#if !defined(VCAST_PACK_INSTRUMENTATION_STORAGE)
#ifdef VCAST_GLOBAL_BUFFER_OPTIMIZATIONS
#define VCAST_GLOBAL_STATEMENT_INSTRUMENTATION_POINT_BUFFERED(id) (\
  vcast_coverage_bytes[id] = 1 \
)
#else
#define VCAST_STATEMENT_INSTRUMENTATION_POINT_BUFFERED(covdata, id) (\
  covdata[id] = 1 \
)
#endif /* VCAST_GLOBAL_BUFFER_OPTIMIZATIONS */
#else
#ifdef VCAST_GLOBAL_BUFFER_OPTIMIZATIONS
#define VCAST_GLOBAL_STATEMENT_INSTRUMENTATION_POINT_BUFFERED(id) (\
  vcast_coverage_bytes[id >> 3] |= (((unsigned long)1) << (id % 8)) \
)
#else
#define VCAST_STATEMENT_INSTRUMENTATION_POINT_BUFFERED(covdata, id) (\
  covdata[id >> 3] |= (((unsigned long)1) << (id % 8)) \
)
#endif /* VCAST_GLOBAL_BUFFER_OPTIMIZATIONS */
#endif
#endif /* __CUDA_ARCH__ */
/*************************************/

#ifdef VCAST_GLOBAL_BUFFER_OPTIMIZATIONS
#define VCAST_GLOBAL_STATEMENT_INSTRUMENTATION_POINT_ANIMATION(id) (\
  VCAST_WRITE_GLOBAL_STATEMENT_ID(id) \
)
#else
#define VCAST_STATEMENT_INSTRUMENTATION_POINT_ANIMATION(unit, id) (\
  VCAST_WRITE_STATEMENT_ID(unit, id) \
)
#endif

#ifdef VCAST_GLOBAL_BUFFER_OPTIMIZATIONS
#if !defined(VCAST_PACK_INSTRUMENTATION_STORAGE)
#define VCAST_GLOBAL_BRANCH_INSTRUMENTATION_POINT_REALTIME(id, condition) ( \
  condition ? \
  ((vcast_coverage_bytes[id * 2] == 0) ? (vcast_coverage_bytes[id * 2] = 1, VCAST_WRITE_GLOBAL_BRANCH_ID(id, "T"), 1) : 1) \
  : \
  ((vcast_coverage_bytes[id * 2 + 1] == 0) ? (vcast_coverage_bytes[id * 2 + 1] = 1, VCAST_WRITE_GLOBAL_BRANCH_ID(id, "F"), 0) : 0) \
)
#define VCAST_GLOBAL_SINGLE_BRANCH_INSTRUMENTATION_POINT_REALTIME(id, condition) ( \
  (vcast_coverage_bytes[id] == 0) ? (vcast_coverage_bytes[id] = 1, VCAST_WRITE_GLOBAL_BRANCH_ID(id, "S"), condition) : condition \
)
#else
#define VCAST_GLOBAL_BRANCH_INSTRUMENTATION_POINT_REALTIME(id, condition) ( \
  condition ? \
  (((vcast_coverage_bytes[id >> 2] & (((unsigned long)1) << (id % 4 << 1))) == 0) ?       \
   (vcast_coverage_bytes[id >> 2] |= (((unsigned long)1) << (id % 4 << 1)),               \
    VCAST_WRITE_GLOBAL_BRANCH_ID(id, "T"), 1) : 1)                       \
  : \
  (((vcast_coverage_bytes[id >> 2] & (((unsigned long)1) << ((id % 4 << 1) + 1))) == 0) ?   \
   (vcast_coverage_bytes[id >> 2] |= (((unsigned long)1) << ((id % 4 << 1) + 1)),       \
    VCAST_WRITE_GLOBAL_BRANCH_ID(id, "F"), 0) : 0)          \
)
#define VCAST_GLOBAL_SINGLE_BRANCH_INSTRUMENTATION_POINT_REALTIME(id, condition) ( \
  ((vcast_coverage_bytes[id >> 3] & (((unsigned long)1) << (id % 8))) == 0) ? \
  (vcast_coverage_bytes[id >> 3] |= (((unsigned long)1) << (id % 8)), (VCAST_WRITE_GLOBAL_BRANCH_ID(id, "S"), condition)) \
  : condition \
)
#endif
#else
#if !defined(VCAST_PACK_INSTRUMENTATION_STORAGE)
#define VCAST_BRANCH_INSTRUMENTATION_POINT_REALTIME(covdata, unit, id, condition) ( \
  condition ? \
  ((covdata[id * 2] == 0) ? (covdata[id * 2] = 1, VCAST_WRITE_BRANCH_ID(unit, id, "T"), 1) : 1) \
  : \
  ((covdata[id * 2 + 1] == 0) ? (covdata[id * 2 + 1] = 1, VCAST_WRITE_BRANCH_ID(unit, id, "F"), 0) : 0) \
)
#else
#define VCAST_BRANCH_INSTRUMENTATION_POINT_REALTIME(covdata, unit, id, condition) ( \
  condition ? \
  (((covdata[id >> 2] & (((unsigned long)1) << (id % 4 << 1))) == 0) ?       \
   (covdata[id >> 2] |= (((unsigned long)1) << (id % 4 << 1)),               \
    VCAST_WRITE_BRANCH_ID(unit, id, "T"), 1) : 1)                       \
  : \
  (((covdata[id >> 2] & (((unsigned long)1) << ((id % 4 << 1) + 1))) == 0) ?   \
   (covdata[id >> 2] |= (((unsigned long)1) << ((id % 4 << 1) + 1)),       \
    VCAST_WRITE_BRANCH_ID(unit, id, "F"), 0) : 0)          \
)
#endif
#endif /* VCAST_GLOBAL_BUFFER_OPTIMIZATIONS */

/*************************************/
/* Use CUDA device-side code/buffer */
#ifdef __CUDA_ARCH__
#define VCAST_BRANCH_INSTRUMENTATION_POINT_BUFFERED(covdata, id, condition) \
   ( condition ? \
      (atomicOr(&(((int*)(covdata ## _device))[id >> 4]), (((unsigned long)1) << (id % 16 << 1))), 1) \
      : \
      (atomicOr(&(((int*)(covdata ## _device))[id >> 4]), (((unsigned long)1) << ((id % 16 << 1) + 1))), 0) )
/* Host-side code */
#else
#ifdef VCAST_GLOBAL_BUFFER_OPTIMIZATIONS
#if !defined(VCAST_PACK_INSTRUMENTATION_STORAGE)
#define VCAST_GLOBAL_BRANCH_INSTRUMENTATION_POINT_BUFFERED(id, condition) ( \
  condition ? \
  ((vcast_coverage_bytes[id * 2] == 0) ? (vcast_coverage_bytes[id * 2] = 1, 1) : 1) \
  : \
  ((vcast_coverage_bytes[id * 2 + 1] == 0) ? (vcast_coverage_bytes[id * 2 + 1] = 1, 0) : 0) \
)
#define VCAST_GLOBAL_SINGLE_BRANCH_INSTRUMENTATION_POINT_BUFFERED(id, condition) (\
  (vcast_coverage_bytes[id] = 1, condition) \
)
#else
#define VCAST_GLOBAL_BRANCH_INSTRUMENTATION_POINT_BUFFERED(id, condition) (\
  condition ? \
  (vcast_coverage_bytes[id >> 2] |= (((unsigned long)1) << (id % 4 << 1)), 1)     \
  : \
  (vcast_coverage_bytes[id >> 2] |= (((unsigned long)1) << ((id % 4 << 1) + 1)), 0)     \
)
#define VCAST_GLOBAL_SINGLE_BRANCH_INSTRUMENTATION_POINT_BUFFERED(id, condition) (\
  (vcast_coverage_bytes[id >> 3] |= (((unsigned long)1) << (id % 8)), condition) \
)
#endif
#else
#if !defined(VCAST_PACK_INSTRUMENTATION_STORAGE)
#define VCAST_BRANCH_INSTRUMENTATION_POINT_BUFFERED(covdata, id, condition) ( \
  condition ? \
  ((covdata[id * 2] == 0) ? (covdata[id * 2] = 1, 1) : 1) \
  : \
  ((covdata[id * 2 + 1] == 0) ? (covdata[id * 2 + 1] = 1, 0) : 0) \
)
#define VCAST_SINGLE_BRANCH_INSTRUMENTATION_POINT_BUFFERED(covdata, id, condition) (\
  (covdata[id] = 1, condition) \
)
#else
#define VCAST_BRANCH_INSTRUMENTATION_POINT_BUFFERED(covdata, id, condition) (\
  condition ? \
  (covdata[id >> 2] |= (((unsigned long)1) << (id % 4 << 1)), 1)     \
  : \
  (covdata[id >> 2] |= (((unsigned long)1) << ((id % 4 << 1) + 1)), 0)     \
)
#define VCAST_SINGLE_BRANCH_INSTRUMENTATION_POINT_BUFFERED(covdata, id, condition) (\
  (covdata[id >> 3] |= (((unsigned long)1) << (id % 8)), condition) \
)
#endif
#endif /* VCAST_GLOBAL_BUFFER_OPTIMIZATIONS */
#endif
/*************************************/

#ifdef VCAST_GLOBAL_BUFFER_OPTIMIZATIONS
#define VCAST_GLOBAL_BRANCH_INSTRUMENTATION_POINT_ANIMATION(id, condition, onPath) ( \
  condition ? \
  (VCAST_WRITE_GLOBAL_BRANCH_ID(id, onPath ? "T" : "TX"), 1)      \
  : \
  (VCAST_WRITE_GLOBAL_BRANCH_ID(id, onPath ? "F" : "FX"), 0)      \
)

#define VCAST_GLOBAL_SINGLE_BRANCH_INSTRUMENTATION_POINT_ANIMATION(id, condition, onPath) ( \
  (VCAST_WRITE_GLOBAL_BRANCH_ID(id, "S"), condition)      \
)
#else /* VCAST_GLOBAL_BUFFER_OPTIMIZATIONS */
#define VCAST_BRANCH_INSTRUMENTATION_POINT_ANIMATION(unit, id, condition, onPath) ( \
  condition ? \
  (VCAST_WRITE_BRANCH_ID(unit, id, onPath ? "T" : "TX"), 1)      \
  : \
  (VCAST_WRITE_BRANCH_ID(unit, id, onPath ? "F" : "FX"), 0)      \
)
#endif /* VCAST_GLOBAL_BUFFER_OPTIMIZATIONS */

#ifdef VCAST_GLOBAL_BUFFER_OPTIMIZATIONS
#define VCAST_GLOBAL_OPTIMIZED_MCDC_CONDITION_INSTRUMENTATION_POINT_REALTIME_0(id, condition) (\
  condition ?                                                                                \
  (((vcast_coverage_bytes[id >> 2] & ((((unsigned long)0x3) << ((id << 1) % 8)))) == 0) ?     \
    (vcast_coverage_bytes[id >> 2] |= ((((unsigned long)0x3) << ((id << 1) % 8))),            \
     VCAST_WRITE_GLOBAL_OPTIMIZED_MCDC_ID(id, 'a', (VCAST_MCDC_STORAGE_TYPE)1,(VCAST_MCDC_STORAGE_TYPE)1), 1) : 1) \
      :                                                                                      \
      (((vcast_coverage_bytes[id >> 2] & ((((unsigned long)0x1) << ((id << 1) % 8)))) == 0) ? \
       (vcast_coverage_bytes[id >> 2] |= ((((unsigned long)0x1) << ((id << 1) % 8))),         \
        VCAST_WRITE_GLOBAL_OPTIMIZED_MCDC_ID(id, 'a', (VCAST_MCDC_STORAGE_TYPE)0, (VCAST_MCDC_STORAGE_TYPE)1), 0) : 0) \
)
#else /* VCAST_GLOBAL_BUFFER_OPTIMIZATIONS */
#define VCAST_OPTIMIZED_MCDC_CONDITION_INSTRUMENTATION_POINT_REALTIME_0(covdata, unit, id, condition) (\
  condition ?                                                                                \
  (((covdata[id >> 2] & ((((unsigned long)0x3) << ((id << 1) % 8)))) == 0) ?     \
    (covdata[id >> 2] |= ((((unsigned long)0x3) << ((id << 1) % 8))),            \
     VCAST_WRITE_OPTIMIZED_MCDC_ID(unit, id, 'a', (VCAST_MCDC_STORAGE_TYPE)1,(VCAST_MCDC_STORAGE_TYPE)1), 1) : 1) \
      :                                                                                      \
      (((covdata[id >> 2] & ((((unsigned long)0x1) << ((id << 1) % 8)))) == 0) ? \
       (covdata[id >> 2] |= ((((unsigned long)0x1) << ((id << 1) % 8))),         \
        VCAST_WRITE_OPTIMIZED_MCDC_ID(unit, id, 'a', (VCAST_MCDC_STORAGE_TYPE)0, (VCAST_MCDC_STORAGE_TYPE)1), 0) : 0) \
)
#endif /* VCAST_GLOBAL_BUFFER_OPTIMIZATIONS */

/*************************************/
/* Use CUDA device-side code/buffer */
#ifdef __CUDA_ARCH__
#define VCAST_OPTIMIZED_MCDC_CONDITION_INSTRUMENTATION_POINT_BUFFERED_0(covdata, id, condition) \
   ( condition ? \
      (atomicOr(&(((int*)(covdata ## _device))[id >> 4]), (((unsigned long)0x3) << ((id << 1) % 32))), 1) \
      : \
      (atomicOr(&(((int*)(covdata ## _device))[id >> 4]), (((unsigned long)0x1) << ((id << 1) % 32))), 0) )
/* Host-side code */
#else
#ifdef VCAST_GLOBAL_BUFFER_OPTIMIZATIONS
#define VCAST_GLOBAL_OPTIMIZED_MCDC_CONDITION_INSTRUMENTATION_POINT_BUFFERED_0(id, condition) (\
  condition ?                                                                      \
  (vcast_coverage_bytes[id >> 2] |= ((((unsigned long)0x3) << ((id << 1) % 8))), 1) \
  :                                                                                \
  (vcast_coverage_bytes[id >> 2] |= ((((unsigned long)0x1) << ((id << 1) % 8))), 0) \
)
#else
#define VCAST_OPTIMIZED_MCDC_CONDITION_INSTRUMENTATION_POINT_BUFFERED_0(covdata, id, condition) (\
  condition ?                                                                      \
  (covdata[id >> 2] |= ((((unsigned long)0x3) << ((id << 1) % 8))), 1) \
  :                                                                                \
  (covdata[id >> 2] |= ((((unsigned long)0x1) << ((id << 1) % 8))), 0) \
)
#endif
#endif
/*************************************/

#ifdef VCAST_GLOBAL_BUFFER_OPTIMIZATIONS
#if !defined(VCAST_PACK_INSTRUMENTATION_STORAGE)
#define VCAST_GLOBAL_FUNCTION_INSTRUMENTATION_POINT_REALTIME(id) ( \
  (vcast_coverage_bytes[id] == 0) ? (vcast_coverage_bytes[id] = 1, VCAST_WRITE_GLOBAL_FUNCTION_ID(id)) : 1 \
)
#else
#define VCAST_GLOBAL_FUNCTION_INSTRUMENTATION_POINT_REALTIME(id) ( \
  ((vcast_coverage_bytes[id >> 3] & (((unsigned long)1) << id % 8)) == 0) ? \
  (vcast_coverage_bytes[id >> 3] |= (((unsigned long)1) << id % 8), \
   VCAST_WRITE_GLOBAL_FUNCTION_ID(id)) : 1 \
)
#endif
#else
#if !defined(VCAST_PACK_INSTRUMENTATION_STORAGE)
#define VCAST_FUNCTION_INSTRUMENTATION_POINT_REALTIME(covdata, unit, id) (\
  (covdata[id] == 0) ? (covdata[id] = 1, VCAST_WRITE_FUNCTION_ID(unit, id)) : 1 \
)
#else
#define VCAST_FUNCTION_INSTRUMENTATION_POINT_REALTIME(covdata, unit, id) (\
  ((covdata[id >> 3] & (((unsigned long)1) << id % 8)) == 0) ? \
  (covdata[id >> 3] |= (((unsigned long)1) << id % 8), \
   VCAST_WRITE_FUNCTION_ID(unit, id)) : 1 \
)
#endif
#endif /* VCAST_GLOBAL_BUFFER_OPTIMIZATIONS */

/*************************************/
/* Use CUDA device-side code/buffer */
#ifdef __CUDA_ARCH__
#define VCAST_FUNCTION_INSTRUMENTATION_POINT_BUFFERED(covdata, id) \
   ( atomicOr(&(((int*)(covdata ## _device))[id >> 5]), \
   (((unsigned long)1) << (id % 32))) )
/* Host-side code */
#else
#ifdef VCAST_GLOBAL_BUFFER_OPTIMIZATIONS
#ifdef VCAST_PACK_INSTRUMENTATION_STORAGE
#define VCAST_GLOBAL_FUNCTION_INSTRUMENTATION_POINT_BUFFERED(id) (\
  vcast_coverage_bytes[id >> 3] |= (((unsigned long)1) << (id % 8)) \
)
#else
#define VCAST_GLOBAL_FUNCTION_INSTRUMENTATION_POINT_BUFFERED(id) (\
  vcast_coverage_bytes[id] = 1 \
)
#endif /* VCAST_PACK_INSTRUMENTATION_STORAGE */
#else
#if defined(VCAST_PACK_INSTRUMENTATION_STORAGE)
#define VCAST_FUNCTION_INSTRUMENTATION_POINT_BUFFERED(covdata, id) (\
  covdata[id >> 3] |= (((unsigned long)1) << (id % 8)) \
)
#else
#define VCAST_FUNCTION_INSTRUMENTATION_POINT_BUFFERED(covdata, id) (\
  covdata[id] = 1 \
)
#endif /* VCAST_PACK_INSTRUMENTATION_STORAGE */
#endif /* VCAST_GLOBAL_BUFFER_OPTIMIZATIONS */
#endif /* __CUDA_ARCH__ */
/*************************************/

#ifdef VCAST_GLOBAL_BUFFER_OPTIMIZATIONS
#define VCAST_GLOBAL_FUNCTION_INSTRUMENTATION_POINT_ANIMATION(id) (\
  VCAST_WRITE_GLOBAL_FUNCTION_ID(id) \
)
#else
#define VCAST_FUNCTION_INSTRUMENTATION_POINT_ANIMATION(unit, id) (\
  VCAST_WRITE_FUNCTION_ID(unit, id) \
)
#endif

#else

int VCAST_FN_CALL_INSTRUMENTATION_POINT_REALTIME(char* covdata, int unit, int id);
int VCAST_GLOBAL_FN_CALL_INSTRUMENTATION_POINT_REALTIME(int id);
VCAST_CUDA_HOST_DEVICE_FUNCTION
int VCAST_FN_CALL_INSTRUMENTATION_POINT_BUFFERED(char* covdata, int id);
VCAST_CUDA_HOST_DEVICE_FUNCTION
int VCAST_GLOBAL_FN_CALL_INSTRUMENTATION_POINT_BUFFERED(int id);
int VCAST_FN_CALL_INSTRUMENTATION_POINT_ANIMATION(int unit, int id);
int VCAST_GLOBAL_FN_CALL_INSTRUMENTATION_POINT_ANIMATION(int id);
int VCAST_STATEMENT_INSTRUMENTATION_POINT_REALTIME(char* covdata, int unit, int id);
int VCAST_GLOBAL_STATEMENT_INSTRUMENTATION_POINT_REALTIME(int id);
VCAST_CUDA_HOST_DEVICE_FUNCTION
int VCAST_STATEMENT_INSTRUMENTATION_POINT_BUFFERED(char* covdata, int id);
VCAST_CUDA_HOST_DEVICE_FUNCTION
int VCAST_GLOBAL_STATEMENT_INSTRUMENTATION_POINT_BUFFERED(int id);
int VCAST_STATEMENT_INSTRUMENTATION_POINT_ANIMATION(int unit, int id);
int VCAST_GLOBAL_STATEMENT_INSTRUMENTATION_POINT_ANIMATION(int id);
int VCAST_BRANCH_INSTRUMENTATION_POINT_REALTIME(char* covdata, int unit, int id, VCAST_CONDITION_TYP condition);
int VCAST_SINGLE_BRANCH_INSTRUMENTATION_POINT_REALTIME(char* covdata, int unit, int id, VCAST_CONDITION_TYP condition);
int VCAST_GLOBAL_BRANCH_INSTRUMENTATION_POINT_REALTIME(int id, VCAST_CONDITION_TYP condition);
int VCAST_GLOBAL_SINGLE_BRANCH_INSTRUMENTATION_POINT_REALTIME(int id, VCAST_CONDITION_TYP condition);
VCAST_CUDA_HOST_DEVICE_FUNCTION
int VCAST_BRANCH_INSTRUMENTATION_POINT_BUFFERED(char* covdata, int id, VCAST_CONDITION_TYP condition);
int VCAST_GLOBAL_BRANCH_INSTRUMENTATION_POINT_BUFFERED(int id, VCAST_CONDITION_TYP condition);
int VCAST_SINGLE_BRANCH_INSTRUMENTATION_POINT_BUFFERED(char* covdata, int id, VCAST_CONDITION_TYP condition);
int VCAST_GLOBAL_SINGLE_BRANCH_INSTRUMENTATION_POINT_BUFFERED(int id, VCAST_CONDITION_TYP condition);
int VCAST_BRANCH_INSTRUMENTATION_POINT_ANIMATION(int unit, int id, VCAST_CONDITION_TYP condition, int onPath);
int VCAST_GLOBAL_BRANCH_INSTRUMENTATION_POINT_ANIMATION(int id, VCAST_CONDITION_TYP condition, int onPath);
int VCAST_GLOBAL_SINGLE_BRANCH_INSTRUMENTATION_POINT_ANIMATION(int id, VCAST_CONDITION_TYP condition, int onPath);
VCAST_CONDITION_TYP 
VCAST_OPTIMIZED_MCDC_CONDITION_INSTRUMENTATION_POINT_REALTIME_0(char* covdata,
                                                                int unit, int id,
                                                                VCAST_CONDITION_TYP condition);
VCAST_CONDITION_TYP 
VCAST_GLOBAL_OPTIMIZED_MCDC_CONDITION_INSTRUMENTATION_POINT_REALTIME_0(int id,
                                                                       VCAST_CONDITION_TYP condition);
VCAST_CUDA_HOST_DEVICE_FUNCTION
VCAST_CONDITION_TYP 
VCAST_OPTIMIZED_MCDC_CONDITION_INSTRUMENTATION_POINT_BUFFERED_0(char* covdata,
                                                                int id,
                                                                VCAST_CONDITION_TYP condition);
VCAST_CONDITION_TYP 
VCAST_GLOBAL_OPTIMIZED_MCDC_CONDITION_INSTRUMENTATION_POINT_BUFFERED_0(int id,
                                                                       VCAST_CONDITION_TYP condition);
int VCAST_FUNCTION_INSTRUMENTATION_POINT_REALTIME(char* covdata, int unit, int id);
int VCAST_GLOBAL_FUNCTION_INSTRUMENTATION_POINT_REALTIME(int id);
VCAST_CUDA_HOST_DEVICE_FUNCTION
int VCAST_FUNCTION_INSTRUMENTATION_POINT_BUFFERED(char* covdata, int id);
int VCAST_GLOBAL_FUNCTION_INSTRUMENTATION_POINT_BUFFERED(int id);
int VCAST_FUNCTION_INSTRUMENTATION_POINT_ANIMATION(int unit, int id);
int VCAST_GLOBAL_FUNCTION_INSTRUMENTATION_POINT_ANIMATION(int id);

/***************************************************************************/
/* For CUDA, remap calls on device side to use device-specific buffer name */
/* See corresponding #undefs in c_cover_io.c */ 
#ifdef __CUDA_ARCH__
/* Depending on the setting of "use macros for coverage" option, these will
 * either be macros above (which don't need remapping) or functions, which 
 * do. If functions, remap arguments. */
#define VCAST_FN_CALL_INSTRUMENTATION_POINT_BUFFERED(covdata, id) VCAST_FN_CALL_INSTRUMENTATION_POINT_BUFFERED(covdata ## _device, id)
#define VCAST_STATEMENT_INSTRUMENTATION_POINT_BUFFERED(covdata, id) VCAST_STATEMENT_INSTRUMENTATION_POINT_BUFFERED(covdata ## _device, id)
#define VCAST_BRANCH_INSTRUMENTATION_POINT_BUFFERED(covdata, id, condition) VCAST_BRANCH_INSTRUMENTATION_POINT_BUFFERED(covdata ## _device, id, condition)
#define VCAST_OPTIMIZED_MCDC_CONDITION_INSTRUMENTATION_POINT_BUFFERED_0(covdata, id, condition) VCAST_OPTIMIZED_MCDC_CONDITION_INSTRUMENTATION_POINT_BUFFERED_0(covdata ## _device, id, condition)
#define VCAST_FUNCTION_INSTRUMENTATION_POINT_BUFFERED(covdata, id) VCAST_FUNCTION_INSTRUMENTATION_POINT_BUFFERED(covdata ## _device, id)
#endif
/***************************************************************************/

#endif /* VCAST_COVERAGE_POINTS_AS_MACROS */

VCAST_CUDA_HOST_DEVICE_FUNCTION
VCAST_CONDITION_TYP
VCAST_SAVE_MCDC_SUBCONDITION (struct vcast_mcdc_statement *mcdc_statement,
                              int bit_index, VCAST_CONDITION_TYP condition);

VCAST_CONDITION_TYP 
VCAST_MCDC_CONDITION_INSTRUMENTATION_POINT_REALTIME(VCAST_AVLTree *vcast_mcdc_array,
                                                    struct vcast_mcdc_statement *mcdc_statement,
                                                    int unit, int id,
                                                    VCAST_CONDITION_TYP condition);
VCAST_CONDITION_TYP 
VCAST_GLOBAL_MCDC_CONDITION_INSTRUMENTATION_POINT_REALTIME(struct vcast_mcdc_statement *mcdc_statement,
                                                           int id,
                                                           VCAST_CONDITION_TYP condition);

VCAST_CONDITION_TYP 
VCAST_MCDC_CONDITION_INSTRUMENTATION_POINT_ANIMATION(struct vcast_mcdc_statement *mcdc_statement,
                                                     int unit, int id, VCAST_CONDITION_TYP condition);

VCAST_CONDITION_TYP 
VCAST_GLOBAL_MCDC_CONDITION_INSTRUMENTATION_POINT_ANIMATION(struct vcast_mcdc_statement *mcdc_statement,
                                                            int id, VCAST_CONDITION_TYP condition);

VCAST_CUDA_HOST_DEVICE_FUNCTION
VCAST_CONDITION_TYP 
VCAST_MCDC_CONDITION_INSTRUMENTATION_POINT_BUFFERED(VCAST_AVLTree *vcast_mcdc_array,
                                                    struct vcast_mcdc_statement *mcdc_statement,
                                                    int id,
                                                    VCAST_CONDITION_TYP condition);
VCAST_CONDITION_TYP 
VCAST_GLOBAL_MCDC_CONDITION_INSTRUMENTATION_POINT_BUFFERED(struct vcast_mcdc_statement *coverage,
                                                           int id,
                                                           VCAST_CONDITION_TYP condition);

VCAST_CONDITION_TYP 
VCAST_OPTIMIZED_MCDC_CONDITION_INSTRUMENTATION_POINT_REALTIME_1(char* covdata,
                                                                struct vcast_mcdc_statement *mcdc_statement,
                                                                int unit, int id,
                                                                VCAST_CONDITION_TYP condition);
VCAST_CONDITION_TYP 
VCAST_GLOBAL_OPTIMIZED_MCDC_CONDITION_INSTRUMENTATION_POINT_REALTIME_1(struct vcast_mcdc_statement *mcdc_statement,
                                                                       int id,
                                                                       VCAST_CONDITION_TYP condition);
VCAST_CONDITION_TYP 
VCAST_OPTIMIZED_MCDC_CONDITION_INSTRUMENTATION_POINT_REALTIME(char* covdata,
                                                          struct vcast_mcdc_statement *mcdc_statement,
                                                          int unit, int id,
                                                          int num_conditions,
                                                          VCAST_CONDITION_TYP condition);
VCAST_CONDITION_TYP 
VCAST_GLOBAL_OPTIMIZED_MCDC_CONDITION_INSTRUMENTATION_POINT_REALTIME(char* covdata,
                                                                     struct vcast_mcdc_statement *mcdc_statement,
                                                                     int id,
                                                                     int num_conditions,
                                                                     VCAST_CONDITION_TYP condition);

VCAST_CUDA_HOST_DEVICE_FUNCTION
VCAST_CONDITION_TYP 
VCAST_OPTIMIZED_MCDC_CONDITION_INSTRUMENTATION_POINT_BUFFERED_1(char* covdata,
                                                                struct vcast_mcdc_statement *mcdc_statement,
                                                                int id,
                                                                VCAST_CONDITION_TYP condition);
VCAST_CONDITION_TYP 
VCAST_GLOBAL_OPTIMIZED_MCDC_CONDITION_INSTRUMENTATION_POINT_BUFFERED_1(struct vcast_mcdc_statement *mcdc_statement,
                                                                       int id,
                                                                       VCAST_CONDITION_TYP condition);
VCAST_CUDA_HOST_DEVICE_FUNCTION
VCAST_CONDITION_TYP 
VCAST_OPTIMIZED_MCDC_CONDITION_INSTRUMENTATION_POINT_BUFFERED_2(char* covdata,
                                                                struct vcast_mcdc_statement *mcdc_statement,
                                                                int id,
                                                                VCAST_CONDITION_TYP condition);

VCAST_CUDA_HOST_DEVICE_FUNCTION
VCAST_CONDITION_TYP 
VCAST_OPTIMIZED_MCDC_CONDITION_INSTRUMENTATION_POINT_BUFFERED(char* covdata,
                                                              struct vcast_mcdc_statement *mcdc_statement,
                                                              int id,
                                                              int num_conditions,
                                                              VCAST_CONDITION_TYP condition);
VCAST_CONDITION_TYP 
VCAST_GLOBAL_OPTIMIZED_MCDC_CONDITION_INSTRUMENTATION_POINT_BUFFERED(char* covdata,
                                                                     struct vcast_mcdc_statement *mcdc_statement,
                                                                     int id,
                                                                     int num_conditions,
                                                                     VCAST_CONDITION_TYP condition);

VCAST_CONDITION_TYP 
VCAST_OPTIMIZED_MCDC_CONDITION_INSTRUMENTATION_POINT_ANIMATION(struct vcast_mcdc_statement *mcdc_statement,
                                                           int unit, int id,
                                                           int num_conditions,
                                                           VCAST_CONDITION_TYP condition);
                                                           
VCAST_CONDITION_TYP 
VCAST_GLOBAL_OPTIMIZED_MCDC_CONDITION_INSTRUMENTATION_POINT_ANIMATION(struct vcast_mcdc_statement *mcdc_statement,
                                                                      int id,
                                                                      int num_conditions,
                                                                      VCAST_CONDITION_TYP condition);
                                                           
/***************************************************************************/
/* For CUDA, remap calls on device side to use device-specific buffer name */
/* See corresponding #undefs in c_cover_io.c */ 
#ifdef __CUDA_ARCH__
/* These will always be functions regardless of the "use macros for coverage" 
 * option, so do the redefine globally. */
#define VCAST_OPTIMIZED_MCDC_CONDITION_INSTRUMENTATION_POINT_BUFFERED(covdata, statement, id, num_conditions, condition) VCAST_OPTIMIZED_MCDC_CONDITION_INSTRUMENTATION_POINT_BUFFERED(covdata ## _device, statement, id, num_conditions, condition)
#define VCAST_OPTIMIZED_MCDC_CONDITION_INSTRUMENTATION_POINT_BUFFERED_1(covdata, statement, id, condition) VCAST_OPTIMIZED_MCDC_CONDITION_INSTRUMENTATION_POINT_BUFFERED_1(covdata ## _device, statement, id, condition)
#define VCAST_OPTIMIZED_MCDC_CONDITION_INSTRUMENTATION_POINT_BUFFERED_2(covdata, statement, id, condition) VCAST_OPTIMIZED_MCDC_CONDITION_INSTRUMENTATION_POINT_BUFFERED_2(covdata ## _device, statement, id, condition)
#endif
/***************************************************************************/

int VCAST_COUPLING_INSTRUMENTATION_POINT (int vc_probeIndex);
void vcastDumpCouplingData (void);
void vcastCouplingDataInit (void);
int vcastControlCoupleTargetCall (int vc_probeIndex);
int vcastControlCoupleFptrCall (int probeIndex, void *fnCall, void *fnTarget);
int vcastControlCoupleVrtlCall (int vc_probeIndex);
                                                           
#ifndef VCAST_COVER_NO_STDIO
int vcast_strlen(const char *VC_S);
char * vcast_strcat (char *VC_S, const char *VC_T);
char * vcast_int_to_string (char *buf, VCAST_MCDC_STORAGE_TYPE vc_x);
void VCAST_WRITE_TO_INST_FILE_COVERAGE (const char *S, int flush);
#endif /* VCAST_COVER_NO_STDIO */
                                                           

#ifndef VCAST_UNIT_TEST_TOOL

#ifdef VCAST_HAS_LONGLONG
  #ifdef VCAST_MICROSOFT_LONG_LONG
  #define VCAST_LONGEST_INT __int64
  #else
  #define VCAST_LONGEST_INT long long
  #endif
#else
  #define VCAST_LONGEST_INT long
#endif

#ifndef VCAST_UNSIGNED_CONVERSION_TYPE
#define VCAST_UNSIGNED_CONVERSION_TYPE unsigned VCAST_LONGEST_INT
#endif
#ifndef VCAST_SIGNED_CONVERSION_TYPE
#define VCAST_SIGNED_CONVERSION_TYPE VCAST_LONGEST_INT
#endif

/* types */
/* ifdef VCAST_NO_FLOAT */
#ifdef VCAST_NO_FLOAT
typedef long vCAST_double;
typedef long vCAST_long_double;
/* else */
#else
typedef double vCAST_double;
/* ifdef VCAST_ALLOW_LONG_DOUBLE */
#if defined(VCAST_ALLOW_LONG_DOUBLE) || !defined(VCAST_NO_LONG_DOUBLE)
typedef long double vCAST_long_double;
#else
typedef double vCAST_long_double;
#endif
/* endif VCAST_ALLOW_LONG_DOUBLE */
#endif
/* endif VCAST_NO_FLOAT */

#ifndef VCAST_COVER_NO_STDIO
VCAST_LONGEST_INT vcast_abs ( VCAST_LONGEST_INT vcNum );
void vectorcast_signed_to_string ( char vcDest[], VCAST_LONGEST_INT vcSrc );
int VCAST_special_compare ( char *vcDouble1, char *vcDouble2, int vcLen );
void vectorcast_strcpy ( char *VC_S, const char *VC_T );
void vectorcast_float_to_string( char *mixed_str, vCAST_long_double f );
#endif /* VCAST_COVER_NO_STDIO */

/* This macro is always defined, because, it "tells" the c_cover_io.c 
   file that the prototypes are available to it. */
#define VCAST_PROBE_PRINT_AVAILABLE

void vcast_probe_print (const char *S);
void vcast_probe_print_int (VCAST_SIGNED_CONVERSION_TYPE i);
void vcast_probe_print_unsigned (VCAST_UNSIGNED_CONVERSION_TYPE i);
void vcast_probe_print_float (vCAST_long_double f);

#endif /* VCAST_UNIT_TEST_TOOL */

#ifdef __cplusplus
}
#endif

#endif

#ifdef __cplusplus
}
#endif
#ifdef __cplusplus
extern "C" {
#endif
extern char vcast_coverage_bytes[];
#define VCAST_STATEMENT_INST_POINT_0 120
#define VCAST_STATEMENT_INST_POINT_1 121
#define VCAST_STATEMENT_INST_POINT_2 122
#define VCAST_STATEMENT_INST_POINT_3 123
#define VCAST_STATEMENT_INST_POINT_4 124
#define VCAST_STATEMENT_INST_POINT_5 125
#define VCAST_STATEMENT_INST_POINT_6 126
#define VCAST_STATEMENT_INST_POINT_7 127
#define VCAST_STATEMENT_INST_POINT_8 128
#define VCAST_STATEMENT_INST_POINT_9 129
#define VCAST_STATEMENT_INST_POINT_10 130
#define VCAST_STATEMENT_INST_POINT_11 131
#define VCAST_STATEMENT_INST_POINT_12 132
#define VCAST_STATEMENT_INST_POINT_13 133
#define VCAST_STATEMENT_INST_POINT_14 134
#define VCAST_STATEMENT_INST_POINT_15 135
#define VCAST_STATEMENT_INST_POINT_16 136
#define VCAST_STATEMENT_INST_POINT_17 137
#define VCAST_STATEMENT_INST_POINT_18 138
#define VCAST_STATEMENT_INST_POINT_19 139
#define VCAST_STATEMENT_INST_POINT_20 140
#define VCAST_STATEMENT_INST_POINT_21 141
#define VCAST_STATEMENT_INST_POINT_22 142
#define VCAST_STATEMENT_INST_POINT_23 143
#define VCAST_STATEMENT_INST_POINT_24 144
#define VCAST_STATEMENT_INST_POINT_25 145
#define VCAST_STATEMENT_INST_POINT_26 146
#define VCAST_STATEMENT_INST_POINT_27 147
#define VCAST_STATEMENT_INST_POINT_28 148
#define VCAST_STATEMENT_INST_POINT_29 149
#define VCAST_STATEMENT_INST_POINT_30 150
#define VCAST_STATEMENT_INST_POINT_31 151
#define VCAST_STATEMENT_INST_POINT_32 152
#define VCAST_STATEMENT_INST_POINT_33 153
#define VCAST_STATEMENT_INST_POINT_34 154
#define VCAST_STATEMENT_INST_POINT_35 155
#define VCAST_STATEMENT_INST_POINT_36 156
#define VCAST_STATEMENT_INST_POINT_37 157
#define VCAST_STATEMENT_INST_POINT_38 158
#define VCAST_STATEMENT_INST_POINT_39 159
#define VCAST_STATEMENT_INST_POINT_40 160
#define VCAST_STATEMENT_INST_POINT_41 161
#define VCAST_STATEMENT_INST_POINT_42 162
#define VCAST_STATEMENT_INST_POINT_43 163
#define VCAST_STATEMENT_INST_POINT_44 164
#define VCAST_STATEMENT_INST_POINT_45 165
#define VCAST_STATEMENT_INST_POINT_46 166
#define VCAST_STATEMENT_INST_POINT_47 167
#define VCAST_STATEMENT_INST_POINT_48 168
#define VCAST_STATEMENT_INST_POINT_49 169
#define VCAST_STATEMENT_INST_POINT_50 170
#define VCAST_STATEMENT_INST_POINT_51 171
#define VCAST_STATEMENT_INST_POINT_52 172
#define VCAST_STATEMENT_INST_POINT_53 173
#define VCAST_STATEMENT_INST_POINT_54 174
#define VCAST_STATEMENT_INST_POINT_55 175
#define VCAST_STATEMENT_INST_POINT_56 176
#define VCAST_STATEMENT_INST_POINT_57 177
#define VCAST_STATEMENT_INST_POINT_58 178
#define VCAST_STATEMENT_INST_POINT_59 179
#define VCAST_STATEMENT_INST_POINT_60 180
#define VCAST_STATEMENT_INST_POINT_61 181
#define VCAST_STATEMENT_INST_POINT_62 182
#define VCAST_STATEMENT_INST_POINT_63 183
#define VCAST_STATEMENT_INST_POINT_64 184
#define VCAST_STATEMENT_INST_POINT_65 185
#define VCAST_STATEMENT_INST_POINT_66 186
#define VCAST_STATEMENT_INST_POINT_67 187
#define VCAST_STATEMENT_INST_POINT_68 188
extern VCAST_AVLTree vcast_mcdc_bytes[];
#define VCAST_OPTIMIZED_MCDC_INST_POINT_0_0 28
#define VCAST_OPTIMIZED_MCDC_INST_POINT_0_1 29
#define VCAST_OPTIMIZED_MCDC_INST_POINT_0_2 30
#define VCAST_OPTIMIZED_MCDC_INST_POINT_0_3 31
#define VCAST_OPTIMIZED_MCDC_INST_POINT_0_4 32
#define VCAST_OPTIMIZED_MCDC_INST_POINT_0_5 33
#define VCAST_OPTIMIZED_MCDC_INST_POINT_0_6 34
#define VCAST_OPTIMIZED_MCDC_INST_POINT_0_7 35
#define VCAST_OPTIMIZED_MCDC_INST_POINT_0_8 36
#define VCAST_OPTIMIZED_MCDC_INST_POINT_0_9 37
#define VCAST_OPTIMIZED_MCDC_INST_POINT_0_10 38
#define VCAST_OPTIMIZED_MCDC_INST_POINT_0_11 39
#define VCAST_OPTIMIZED_MCDC_INST_POINT_0_12 40
#define VCAST_OPTIMIZED_MCDC_INST_POINT_0_13 41
#define VCAST_OPTIMIZED_MCDC_INST_POINT_0_14 42
#define VCAST_OPTIMIZED_MCDC_INST_POINT_0_15 43
#define VCAST_OPTIMIZED_MCDC_INST_POINT_0_16 44
#define VCAST_OPTIMIZED_MCDC_INST_POINT_0_17 45
#define VCAST_OPTIMIZED_MCDC_INST_POINT_0_18 46
#define VCAST_OPTIMIZED_MCDC_INST_POINT_0_19 47
#define VCAST_OPTIMIZED_MCDC_INST_POINT_0_20 48
#define VCAST_OPTIMIZED_MCDC_INST_POINT_0_21 49
#define VCAST_OPTIMIZED_MCDC_INST_POINT_0_22 50
#define VCAST_OPTIMIZED_MCDC_INST_POINT_0_23 51
#define VCAST_OPTIMIZED_MCDC_INST_POINT_0_24 52
#define VCAST_OPTIMIZED_MCDC_INST_POINT_0_25 53
#define VCAST_OPTIMIZED_MCDC_INST_POINT_0_26 54
#define VCAST_OPTIMIZED_MCDC_INST_POINT_0_27 55
#define VCAST_OPTIMIZED_MCDC_INST_POINT_0_28 56
#define VCAST_OPTIMIZED_MCDC_INST_POINT_0_29 57
#define VCAST_OPTIMIZED_MCDC_INST_POINT_0_30 58
#define VCAST_OPTIMIZED_MCDC_INST_POINT_0_31 59
#define VCAST_OPTIMIZED_MCDC_INST_POINT_1_0 0
#define VCAST_OPTIMIZED_MCDC_INST_POINT_1_1 1
#define VCAST_OPTIMIZED_MCDC_INST_POINT_1_2 2
#define VCAST_OPTIMIZED_MCDC_INST_POINT_1_3 3
#define VCAST_OPTIMIZED_MCDC_INST_POINT_1_4 4
#define VCAST_OPTIMIZED_MCDC_INST_POINT_1_5 5
#define VCAST_OPTIMIZED_MCDC_INST_POINT_1_6 6
#define VCAST_OPTIMIZED_MCDC_INST_POINT_1_7 7
#define VCAST_OPTIMIZED_MCDC_INST_POINT_1_8 8
#define VCAST_OPTIMIZED_MCDC_INST_POINT_1_9 9
#define VCAST_OPTIMIZED_MCDC_INST_POINT_1_10 10
#define VCAST_OPTIMIZED_MCDC_INST_POINT_1_11 11
#define VCAST_OPTIMIZED_MCDC_INST_POINT_1_12 12
#define VCAST_OPTIMIZED_MCDC_INST_POINT_1_13 13
#ifdef __cplusplus
} /* end extern */
#endif
/*
 * This file contains generated ccde for a model 'LightCtrl_SWC'.
 * It is an implementation of the light control ECU we want to test.
 */
/*vcast_header_collapse_start:C:\\Program Files (x86)\\Microsoft Visual Studio\\2019\\Pinned\\VC\\Tools\\MSVC\\14.28.29910\\include\\stdbool.h*/
//
// stdbool.h
//
//      Copyright (c) Microsoft Corporation. All rights reserved.
//
// The C Standard Library <stdbool.h> header.
//
/*vcast_header_collapse_end*/
/*vcast_header_expansion_start:D:\\dev\\TCR\\Libraries\\tds-vectorcast-data\\LightControl_Basic_CAN_CBT\\BFC\\Application\\IO.h*/
typedef unsigned char uint8_T;
typedef unsigned short uint16_T;
typedef double real_T;
typedef struct tag_DW_LightCtrl_SWC_T
{
  real_T HysteresisTimer;
  uint8_T is_active_c1_LightCtrl_SWC;
  uint8_T is_c1_LightCtrl_SWC;
  uint8_T is_AutoMode;
} DW_LightCtrl_SWC_T;
struct P_LightCtrl_SWC_T_ 
{
  real_T LightIntensityToOff_Value;
  real_T LightIntensityToOn_Value;
  real_T HysteresisTimeToOff_Value;
  real_T HysteresisTimeToOn_Value;
  real_T CycleTime_Value;
};
typedef struct P_LightCtrl_SWC_T_ P_LightCtrl_SWC_T;
extern P_LightCtrl_SWC_T LightCtrl_SWC_P;
extern DW_LightCtrl_SWC_T LightCtrl_SWC_DW;
extern void LightCtrl(void);
extern void LightCtrl_Init(void);
void Output_HeadLight(uint8_T headLightValue);
void Input_LightSwitch(uint8_T *value);
void Input_LightIntensity(uint16_T * lightIntesityValue);
/*vcast_header_expansion_end*/
const uint8_T C_LightCtrl_SWC_IN_AutoMode = ((uint8_T)1U);
const uint8_T C_LightCtrl_SWC_IN_EnterAutoMode = ((uint8_T)1U);
const uint8_T C_LightCtrl_SWC_IN_LightOff = ((uint8_T)2U);
const uint8_T C_LightCtrl_SWC_IN_LightOn = ((uint8_T)3U);
const uint8_T C_LightCtrl_SWC_IN_LightToOff = ((uint8_T)4U);
const uint8_T C_LightCtrl_SWC_IN_LightToOn = ((uint8_T)5U);
const uint8_T C_LightCtrl_SWC_IN_OffMode = ((uint8_T)2U);
const uint8_T C_LightCtrl_SWC_IN_OnMode = ((uint8_T)3U);
const uint8_T C_LightCtrl_SW_IN_NO_ACTIVE_CHILD = ((uint8_T)0U);
DW_LightCtrl_SWC_T LightCtrl_SWC_DW;
P_LightCtrl_SWC_T LightCtrl_SWC_P = 
{
  70.0,        // LightIntensityToOff
  60.0,        // LightIntensityToOn
  3.0,         // HysteresisTimeToOff
  2.0,         // HysteresisTimeToOn
  0.01         // CycleTime
};
void Transition_S2_37(void)
{
  VCAST_GLOBAL_OPTIMIZED_MCDC_CONDITION_INSTRUMENTATION_POINT_BUFFERED_0(VCAST_OPTIMIZED_MCDC_INST_POINT_0_0, 1);
VCAST_GLOBAL_STATEMENT_INSTRUMENTATION_POINT_BUFFERED(VCAST_STATEMENT_INST_POINT_0);
LightCtrl_SWC_DW.is_c1_LightCtrl_SWC = C_LightCtrl_SWC_IN_OffMode;
}
void Transition_S2_39(void)
{
  VCAST_GLOBAL_OPTIMIZED_MCDC_CONDITION_INSTRUMENTATION_POINT_BUFFERED_0(VCAST_OPTIMIZED_MCDC_INST_POINT_0_1, 1);
VCAST_GLOBAL_STATEMENT_INSTRUMENTATION_POINT_BUFFERED(VCAST_STATEMENT_INST_POINT_1);
LightCtrl_SWC_DW.is_AutoMode = C_LightCtrl_SW_IN_NO_ACTIVE_CHILD;
  VCAST_GLOBAL_STATEMENT_INSTRUMENTATION_POINT_BUFFERED(VCAST_STATEMENT_INST_POINT_2);
LightCtrl_SWC_DW.is_c1_LightCtrl_SWC = C_LightCtrl_SWC_IN_OnMode;
}
void Transition_S2_41(void)
{
	VCAST_GLOBAL_OPTIMIZED_MCDC_CONDITION_INSTRUMENTATION_POINT_BUFFERED_0(VCAST_OPTIMIZED_MCDC_INST_POINT_0_2, 1);
VCAST_GLOBAL_STATEMENT_INSTRUMENTATION_POINT_BUFFERED(VCAST_STATEMENT_INST_POINT_3);
LightCtrl_SWC_DW.is_AutoMode = C_LightCtrl_SW_IN_NO_ACTIVE_CHILD;
	VCAST_GLOBAL_STATEMENT_INSTRUMENTATION_POINT_BUFFERED(VCAST_STATEMENT_INST_POINT_4);
LightCtrl_SWC_DW.is_c1_LightCtrl_SWC = C_LightCtrl_SWC_IN_OffMode;
}
void Transition_S2_32(void)
{
  VCAST_GLOBAL_OPTIMIZED_MCDC_CONDITION_INSTRUMENTATION_POINT_BUFFERED_0(VCAST_OPTIMIZED_MCDC_INST_POINT_0_3, 1);
VCAST_GLOBAL_STATEMENT_INSTRUMENTATION_POINT_BUFFERED(VCAST_STATEMENT_INST_POINT_5);
LightCtrl_SWC_DW.is_AutoMode = C_LightCtrl_SWC_IN_LightOff;
}
void Transition_S2_33(void)
{
  VCAST_GLOBAL_OPTIMIZED_MCDC_CONDITION_INSTRUMENTATION_POINT_BUFFERED_0(VCAST_OPTIMIZED_MCDC_INST_POINT_0_4, 1);
VCAST_GLOBAL_STATEMENT_INSTRUMENTATION_POINT_BUFFERED(VCAST_STATEMENT_INST_POINT_6);
LightCtrl_SWC_DW.is_AutoMode = C_LightCtrl_SWC_IN_LightOff;
}
void Transition_S2_19(void)
{
  VCAST_GLOBAL_OPTIMIZED_MCDC_CONDITION_INSTRUMENTATION_POINT_BUFFERED_0(VCAST_OPTIMIZED_MCDC_INST_POINT_0_5, 1);
VCAST_GLOBAL_STATEMENT_INSTRUMENTATION_POINT_BUFFERED(VCAST_STATEMENT_INST_POINT_7);
LightCtrl_SWC_DW.is_AutoMode = C_LightCtrl_SWC_IN_LightToOn;
}
void Transition_S2_29(void)
{
  VCAST_GLOBAL_OPTIMIZED_MCDC_CONDITION_INSTRUMENTATION_POINT_BUFFERED_0(VCAST_OPTIMIZED_MCDC_INST_POINT_0_6, 1);
VCAST_GLOBAL_STATEMENT_INSTRUMENTATION_POINT_BUFFERED(VCAST_STATEMENT_INST_POINT_8);
Output_HeadLight(0);
  VCAST_GLOBAL_STATEMENT_INSTRUMENTATION_POINT_BUFFERED(VCAST_STATEMENT_INST_POINT_9);
LightCtrl_SWC_DW.HysteresisTimer = 0.0;
  VCAST_GLOBAL_STATEMENT_INSTRUMENTATION_POINT_BUFFERED(VCAST_STATEMENT_INST_POINT_10);
LightCtrl_SWC_DW.is_AutoMode = C_LightCtrl_SWC_IN_LightOff;
}
void Transition_S2_20(void)
{
		VCAST_GLOBAL_OPTIMIZED_MCDC_CONDITION_INSTRUMENTATION_POINT_BUFFERED_0(VCAST_OPTIMIZED_MCDC_INST_POINT_0_7, 1);
VCAST_GLOBAL_STATEMENT_INSTRUMENTATION_POINT_BUFFERED(VCAST_STATEMENT_INST_POINT_11);
LightCtrl_SWC_DW.is_AutoMode = C_LightCtrl_SWC_IN_LightToOff;
}
void Transition_S2_28(void)
{
  VCAST_GLOBAL_OPTIMIZED_MCDC_CONDITION_INSTRUMENTATION_POINT_BUFFERED_0(VCAST_OPTIMIZED_MCDC_INST_POINT_0_8, 1);
VCAST_GLOBAL_STATEMENT_INSTRUMENTATION_POINT_BUFFERED(VCAST_STATEMENT_INST_POINT_12);
Output_HeadLight(1);
  VCAST_GLOBAL_STATEMENT_INSTRUMENTATION_POINT_BUFFERED(VCAST_STATEMENT_INST_POINT_13);
LightCtrl_SWC_DW.is_AutoMode = C_LightCtrl_SWC_IN_LightOn;
  // We create a fault injection here. This function has now an "implementation error".
  // With this error in the code, 1 test case fails.
  // To see how VectorCAST's Change Based Testing feature works, "fix" the error in this function (see below).
  // Then, run the test cases in VectorCAST Manage again.
  // You will notice that multiple test cases will be executed: not only the failed one but also all those this function affects.
  // However, the unaffected test cases will not be executed at all.
  // Replace the value '3.0' in this line with '0.0' to fix the "implementation error".
  VCAST_GLOBAL_STATEMENT_INSTRUMENTATION_POINT_BUFFERED(VCAST_STATEMENT_INST_POINT_14);
LightCtrl_SWC_DW.HysteresisTimer = 3.0;
}
void Transition_S2_23(void)
{
	 VCAST_GLOBAL_OPTIMIZED_MCDC_CONDITION_INSTRUMENTATION_POINT_BUFFERED_0(VCAST_OPTIMIZED_MCDC_INST_POINT_0_9, 1);
VCAST_GLOBAL_STATEMENT_INSTRUMENTATION_POINT_BUFFERED(VCAST_STATEMENT_INST_POINT_15);
LightCtrl_SWC_DW.is_AutoMode = C_LightCtrl_SWC_IN_LightOn;
}
void Transition_S2_6(void)
{
  VCAST_GLOBAL_OPTIMIZED_MCDC_CONDITION_INSTRUMENTATION_POINT_BUFFERED_0(VCAST_OPTIMIZED_MCDC_INST_POINT_0_10, 1);
VCAST_GLOBAL_STATEMENT_INSTRUMENTATION_POINT_BUFFERED(VCAST_STATEMENT_INST_POINT_16);
LightCtrl_SWC_DW.is_AutoMode = C_LightCtrl_SWC_IN_LightOff;
}
void Transition_S2_25(void)
{
  VCAST_GLOBAL_OPTIMIZED_MCDC_CONDITION_INSTRUMENTATION_POINT_BUFFERED_0(VCAST_OPTIMIZED_MCDC_INST_POINT_0_11, 1);
VCAST_GLOBAL_STATEMENT_INSTRUMENTATION_POINT_BUFFERED(VCAST_STATEMENT_INST_POINT_17);
LightCtrl_SWC_DW.HysteresisTimer += LightCtrl_SWC_P.CycleTime_Value;
  VCAST_GLOBAL_STATEMENT_INSTRUMENTATION_POINT_BUFFERED(VCAST_STATEMENT_INST_POINT_18);
LightCtrl_SWC_DW.is_AutoMode = C_LightCtrl_SWC_IN_LightToOff;
}
void Transition_S2_22(void)
{
  VCAST_GLOBAL_OPTIMIZED_MCDC_CONDITION_INSTRUMENTATION_POINT_BUFFERED_0(VCAST_OPTIMIZED_MCDC_INST_POINT_0_12, 1);
VCAST_GLOBAL_STATEMENT_INSTRUMENTATION_POINT_BUFFERED(VCAST_STATEMENT_INST_POINT_19);
LightCtrl_SWC_DW.is_AutoMode = C_LightCtrl_SWC_IN_LightOff;
}
void Transition_S2_18(void)
{
  VCAST_GLOBAL_OPTIMIZED_MCDC_CONDITION_INSTRUMENTATION_POINT_BUFFERED_0(VCAST_OPTIMIZED_MCDC_INST_POINT_0_13, 1);
VCAST_GLOBAL_STATEMENT_INSTRUMENTATION_POINT_BUFFERED(VCAST_STATEMENT_INST_POINT_20);
LightCtrl_SWC_DW.is_AutoMode = C_LightCtrl_SWC_IN_LightOn;
}
void Transition_S2_24(void)
{
  VCAST_GLOBAL_OPTIMIZED_MCDC_CONDITION_INSTRUMENTATION_POINT_BUFFERED_0(VCAST_OPTIMIZED_MCDC_INST_POINT_0_14, 1);
VCAST_GLOBAL_STATEMENT_INSTRUMENTATION_POINT_BUFFERED(VCAST_STATEMENT_INST_POINT_21);
LightCtrl_SWC_DW.HysteresisTimer += LightCtrl_SWC_P.CycleTime_Value;
  VCAST_GLOBAL_STATEMENT_INSTRUMENTATION_POINT_BUFFERED(VCAST_STATEMENT_INST_POINT_22);
LightCtrl_SWC_DW.is_AutoMode = C_LightCtrl_SWC_IN_LightToOn;
}
void Transition_S2_38(void)
{
  VCAST_GLOBAL_OPTIMIZED_MCDC_CONDITION_INSTRUMENTATION_POINT_BUFFERED_0(VCAST_OPTIMIZED_MCDC_INST_POINT_0_15, 1);
VCAST_GLOBAL_STATEMENT_INSTRUMENTATION_POINT_BUFFERED(VCAST_STATEMENT_INST_POINT_23);
LightCtrl_SWC_DW.is_c1_LightCtrl_SWC = C_LightCtrl_SWC_IN_AutoMode;
}
void Transition_S2_31(void)
{
  VCAST_GLOBAL_OPTIMIZED_MCDC_CONDITION_INSTRUMENTATION_POINT_BUFFERED_0(VCAST_OPTIMIZED_MCDC_INST_POINT_0_16, 1);
VCAST_GLOBAL_STATEMENT_INSTRUMENTATION_POINT_BUFFERED(VCAST_STATEMENT_INST_POINT_24);
LightCtrl_SWC_DW.is_AutoMode = C_LightCtrl_SWC_IN_EnterAutoMode;
}
void Transition_S2_45(void)
{
  VCAST_GLOBAL_OPTIMIZED_MCDC_CONDITION_INSTRUMENTATION_POINT_BUFFERED_0(VCAST_OPTIMIZED_MCDC_INST_POINT_0_17, 1);
VCAST_GLOBAL_STATEMENT_INSTRUMENTATION_POINT_BUFFERED(VCAST_STATEMENT_INST_POINT_25);
LightCtrl_SWC_DW.is_c1_LightCtrl_SWC = C_LightCtrl_SWC_IN_OnMode;
}
void Transition_S2_43(void)
{
  VCAST_GLOBAL_OPTIMIZED_MCDC_CONDITION_INSTRUMENTATION_POINT_BUFFERED_0(VCAST_OPTIMIZED_MCDC_INST_POINT_0_18, 1);
VCAST_GLOBAL_STATEMENT_INSTRUMENTATION_POINT_BUFFERED(VCAST_STATEMENT_INST_POINT_26);
Output_HeadLight(0);
  VCAST_GLOBAL_STATEMENT_INSTRUMENTATION_POINT_BUFFERED(VCAST_STATEMENT_INST_POINT_27);
LightCtrl_SWC_DW.is_c1_LightCtrl_SWC = C_LightCtrl_SWC_IN_OffMode;
}
void Transition_S2_40(void)
{
  VCAST_GLOBAL_OPTIMIZED_MCDC_CONDITION_INSTRUMENTATION_POINT_BUFFERED_0(VCAST_OPTIMIZED_MCDC_INST_POINT_0_19, 1);
VCAST_GLOBAL_STATEMENT_INSTRUMENTATION_POINT_BUFFERED(VCAST_STATEMENT_INST_POINT_28);
LightCtrl_SWC_DW.is_c1_LightCtrl_SWC = C_LightCtrl_SWC_IN_OffMode;
}
void Transition_S2_42(void)
{
  VCAST_GLOBAL_OPTIMIZED_MCDC_CONDITION_INSTRUMENTATION_POINT_BUFFERED_0(VCAST_OPTIMIZED_MCDC_INST_POINT_0_20, 1);
VCAST_GLOBAL_STATEMENT_INSTRUMENTATION_POINT_BUFFERED(VCAST_STATEMENT_INST_POINT_29);
LightCtrl_SWC_DW.is_c1_LightCtrl_SWC = C_LightCtrl_SWC_IN_AutoMode;
}
void Transition_S2_44(void)
{
  VCAST_GLOBAL_OPTIMIZED_MCDC_CONDITION_INSTRUMENTATION_POINT_BUFFERED_0(VCAST_OPTIMIZED_MCDC_INST_POINT_0_21, 1);
VCAST_GLOBAL_STATEMENT_INSTRUMENTATION_POINT_BUFFERED(VCAST_STATEMENT_INST_POINT_30);
Output_HeadLight(1);
  VCAST_GLOBAL_STATEMENT_INSTRUMENTATION_POINT_BUFFERED(VCAST_STATEMENT_INST_POINT_31);
LightCtrl_SWC_DW.is_c1_LightCtrl_SWC = C_LightCtrl_SWC_IN_OnMode;
}
/* Model step function */
void LightCtrl(void)
{
  int vcast_switch_taken_1 = 0;
int vcast_switch_taken_2 = 0;
  struct vcast_mcdc_statement vcast_mcdc_statement = {0, 0};
uint8_T Input_LightSwitch_local_storage;
  uint16_T rtb_LightIntensity_LightIntensi;
  VCAST_GLOBAL_OPTIMIZED_MCDC_CONDITION_INSTRUMENTATION_POINT_BUFFERED_0(VCAST_OPTIMIZED_MCDC_INST_POINT_0_22, 1);
VCAST_GLOBAL_STATEMENT_INSTRUMENTATION_POINT_BUFFERED(VCAST_STATEMENT_INST_POINT_32);
Input_LightSwitch(&Input_LightSwitch_local_storage);
  VCAST_GLOBAL_STATEMENT_INSTRUMENTATION_POINT_BUFFERED(VCAST_STATEMENT_INST_POINT_33);
Input_LightIntensity(&rtb_LightIntensity_LightIntensi);
  if ( VCAST_GLOBAL_OPTIMIZED_MCDC_CONDITION_INSTRUMENTATION_POINT_BUFFERED_1(&vcast_mcdc_statement, VCAST_OPTIMIZED_MCDC_INST_POINT_1_0, (VCAST_CONDITION_TYP)(VCAST_SAVE_MCDC_SUBCONDITION(&vcast_mcdc_statement, 1, (VCAST_CONDITION_TYP)(LightCtrl_SWC_DW.is_active_c1_LightCtrl_SWC == 0U))
)))
  {
    VCAST_GLOBAL_STATEMENT_INSTRUMENTATION_POINT_BUFFERED(VCAST_STATEMENT_INST_POINT_34);
LightCtrl_SWC_DW.is_active_c1_LightCtrl_SWC = 1U;
    VCAST_GLOBAL_STATEMENT_INSTRUMENTATION_POINT_BUFFERED(VCAST_STATEMENT_INST_POINT_35);
Transition_S2_37();
  }
  else
  {
    VCAST_GLOBAL_STATEMENT_INSTRUMENTATION_POINT_BUFFERED(VCAST_STATEMENT_INST_POINT_36);
vcast_switch_taken_1 = 0;
switch (LightCtrl_SWC_DW.is_c1_LightCtrl_SWC)
    {
      case ((uint8_T)1U):VCAST_GLOBAL_OPTIMIZED_MCDC_CONDITION_INSTRUMENTATION_POINT_BUFFERED_0(VCAST_OPTIMIZED_MCDC_INST_POINT_0_23, 1);vcast_switch_taken_1 = 1;
        if ( VCAST_GLOBAL_OPTIMIZED_MCDC_CONDITION_INSTRUMENTATION_POINT_BUFFERED_1(&vcast_mcdc_statement, VCAST_OPTIMIZED_MCDC_INST_POINT_1_1, (VCAST_CONDITION_TYP)(VCAST_SAVE_MCDC_SUBCONDITION(&vcast_mcdc_statement, 1, (VCAST_CONDITION_TYP)(Input_LightSwitch_local_storage == 1))
)))
        {
          VCAST_GLOBAL_STATEMENT_INSTRUMENTATION_POINT_BUFFERED(VCAST_STATEMENT_INST_POINT_37);
Transition_S2_39();
        }
        else if ( VCAST_GLOBAL_OPTIMIZED_MCDC_CONDITION_INSTRUMENTATION_POINT_BUFFERED_1(&vcast_mcdc_statement, VCAST_OPTIMIZED_MCDC_INST_POINT_1_2, (VCAST_CONDITION_TYP)(VCAST_SAVE_MCDC_SUBCONDITION(&vcast_mcdc_statement, 1, (VCAST_CONDITION_TYP)(Input_LightSwitch_local_storage == 0))
)))
        {
          VCAST_GLOBAL_STATEMENT_INSTRUMENTATION_POINT_BUFFERED(VCAST_STATEMENT_INST_POINT_38);
Transition_S2_41();
        }
        else
        {
          VCAST_GLOBAL_STATEMENT_INSTRUMENTATION_POINT_BUFFERED(VCAST_STATEMENT_INST_POINT_39);
vcast_switch_taken_2 = 0;
switch (LightCtrl_SWC_DW.is_AutoMode)
          {
            case ((uint8_T)1U):VCAST_GLOBAL_OPTIMIZED_MCDC_CONDITION_INSTRUMENTATION_POINT_BUFFERED_0(VCAST_OPTIMIZED_MCDC_INST_POINT_0_24, 1);vcast_switch_taken_2 = 1;
              if ( VCAST_GLOBAL_OPTIMIZED_MCDC_CONDITION_INSTRUMENTATION_POINT_BUFFERED_1(&vcast_mcdc_statement, VCAST_OPTIMIZED_MCDC_INST_POINT_1_3, (VCAST_CONDITION_TYP)(VCAST_SAVE_MCDC_SUBCONDITION(&vcast_mcdc_statement, 1, (VCAST_CONDITION_TYP)(rtb_LightIntensity_LightIntensi > LightCtrl_SWC_P.LightIntensityToOff_Value))
)))
              {
                VCAST_GLOBAL_STATEMENT_INSTRUMENTATION_POINT_BUFFERED(VCAST_STATEMENT_INST_POINT_40);
Transition_S2_32();
              }
              else
              {
                VCAST_GLOBAL_STATEMENT_INSTRUMENTATION_POINT_BUFFERED(VCAST_STATEMENT_INST_POINT_41);
Transition_S2_33();
              }
              VCAST_GLOBAL_STATEMENT_INSTRUMENTATION_POINT_BUFFERED(VCAST_STATEMENT_INST_POINT_42);
break;
            case ((uint8_T)2U):if (!vcast_switch_taken_2) VCAST_GLOBAL_OPTIMIZED_MCDC_CONDITION_INSTRUMENTATION_POINT_BUFFERED_0(VCAST_OPTIMIZED_MCDC_INST_POINT_0_25, 1);vcast_switch_taken_2 = 1;
              if ( VCAST_GLOBAL_OPTIMIZED_MCDC_CONDITION_INSTRUMENTATION_POINT_BUFFERED_1(&vcast_mcdc_statement, VCAST_OPTIMIZED_MCDC_INST_POINT_1_4, (VCAST_CONDITION_TYP)(VCAST_SAVE_MCDC_SUBCONDITION(&vcast_mcdc_statement, 1, (VCAST_CONDITION_TYP)(rtb_LightIntensity_LightIntensi < LightCtrl_SWC_P.LightIntensityToOn_Value))
)))
              {
                VCAST_GLOBAL_STATEMENT_INSTRUMENTATION_POINT_BUFFERED(VCAST_STATEMENT_INST_POINT_43);
Transition_S2_19();
              }
              else
              {
                VCAST_GLOBAL_STATEMENT_INSTRUMENTATION_POINT_BUFFERED(VCAST_STATEMENT_INST_POINT_44);
Transition_S2_29();
              }
              VCAST_GLOBAL_STATEMENT_INSTRUMENTATION_POINT_BUFFERED(VCAST_STATEMENT_INST_POINT_45);
break;
            case ((uint8_T)3U):if (!vcast_switch_taken_2) VCAST_GLOBAL_OPTIMIZED_MCDC_CONDITION_INSTRUMENTATION_POINT_BUFFERED_0(VCAST_OPTIMIZED_MCDC_INST_POINT_0_26, 1);vcast_switch_taken_2 = 1;
              if ( VCAST_GLOBAL_OPTIMIZED_MCDC_CONDITION_INSTRUMENTATION_POINT_BUFFERED_1(&vcast_mcdc_statement, VCAST_OPTIMIZED_MCDC_INST_POINT_1_5, (VCAST_CONDITION_TYP)(VCAST_SAVE_MCDC_SUBCONDITION(&vcast_mcdc_statement, 1, (VCAST_CONDITION_TYP)(rtb_LightIntensity_LightIntensi > LightCtrl_SWC_P.LightIntensityToOff_Value))
)))
              {
                VCAST_GLOBAL_STATEMENT_INSTRUMENTATION_POINT_BUFFERED(VCAST_STATEMENT_INST_POINT_46);
Transition_S2_20();
              }
              else
              {
                VCAST_GLOBAL_STATEMENT_INSTRUMENTATION_POINT_BUFFERED(VCAST_STATEMENT_INST_POINT_47);
Transition_S2_28();
              }
              VCAST_GLOBAL_STATEMENT_INSTRUMENTATION_POINT_BUFFERED(VCAST_STATEMENT_INST_POINT_48);
break;
            case ((uint8_T)4U):if (!vcast_switch_taken_2) VCAST_GLOBAL_OPTIMIZED_MCDC_CONDITION_INSTRUMENTATION_POINT_BUFFERED_0(VCAST_OPTIMIZED_MCDC_INST_POINT_0_27, 1);vcast_switch_taken_2 = 1;
              if ( VCAST_GLOBAL_OPTIMIZED_MCDC_CONDITION_INSTRUMENTATION_POINT_BUFFERED_1(&vcast_mcdc_statement, VCAST_OPTIMIZED_MCDC_INST_POINT_1_6, (VCAST_CONDITION_TYP)(VCAST_SAVE_MCDC_SUBCONDITION(&vcast_mcdc_statement, 1, (VCAST_CONDITION_TYP)(rtb_LightIntensity_LightIntensi <= LightCtrl_SWC_P.LightIntensityToOff_Value))
)))
              {
                VCAST_GLOBAL_STATEMENT_INSTRUMENTATION_POINT_BUFFERED(VCAST_STATEMENT_INST_POINT_49);
Transition_S2_23();
              }
              else if ( VCAST_GLOBAL_OPTIMIZED_MCDC_CONDITION_INSTRUMENTATION_POINT_BUFFERED_1(&vcast_mcdc_statement, VCAST_OPTIMIZED_MCDC_INST_POINT_1_7, (VCAST_CONDITION_TYP)(VCAST_SAVE_MCDC_SUBCONDITION(&vcast_mcdc_statement, 1, (VCAST_CONDITION_TYP)(LightCtrl_SWC_DW.HysteresisTimer >= LightCtrl_SWC_P.HysteresisTimeToOff_Value))
)))
              {
                VCAST_GLOBAL_STATEMENT_INSTRUMENTATION_POINT_BUFFERED(VCAST_STATEMENT_INST_POINT_50);
Transition_S2_6();
              }
              else
              {
                VCAST_GLOBAL_STATEMENT_INSTRUMENTATION_POINT_BUFFERED(VCAST_STATEMENT_INST_POINT_51);
Transition_S2_25();
              }
              VCAST_GLOBAL_STATEMENT_INSTRUMENTATION_POINT_BUFFERED(VCAST_STATEMENT_INST_POINT_52);
break;
            default:if (!vcast_switch_taken_2) VCAST_GLOBAL_OPTIMIZED_MCDC_CONDITION_INSTRUMENTATION_POINT_BUFFERED_0(VCAST_OPTIMIZED_MCDC_INST_POINT_0_28, 1);vcast_switch_taken_2 = 1;
              if ( VCAST_GLOBAL_OPTIMIZED_MCDC_CONDITION_INSTRUMENTATION_POINT_BUFFERED_1(&vcast_mcdc_statement, VCAST_OPTIMIZED_MCDC_INST_POINT_1_8, (VCAST_CONDITION_TYP)(VCAST_SAVE_MCDC_SUBCONDITION(&vcast_mcdc_statement, 1, (VCAST_CONDITION_TYP)(rtb_LightIntensity_LightIntensi >= LightCtrl_SWC_P.LightIntensityToOn_Value))
)))
              {
                VCAST_GLOBAL_STATEMENT_INSTRUMENTATION_POINT_BUFFERED(VCAST_STATEMENT_INST_POINT_53);
Transition_S2_22();
              }
              else if ( VCAST_GLOBAL_OPTIMIZED_MCDC_CONDITION_INSTRUMENTATION_POINT_BUFFERED_1(&vcast_mcdc_statement, VCAST_OPTIMIZED_MCDC_INST_POINT_1_9, (VCAST_CONDITION_TYP)(VCAST_SAVE_MCDC_SUBCONDITION(&vcast_mcdc_statement, 1, (VCAST_CONDITION_TYP)(LightCtrl_SWC_DW.HysteresisTimer >= LightCtrl_SWC_P.HysteresisTimeToOn_Value))
)))
              {
                VCAST_GLOBAL_STATEMENT_INSTRUMENTATION_POINT_BUFFERED(VCAST_STATEMENT_INST_POINT_54);
Transition_S2_18();
              }
              else
              {
                VCAST_GLOBAL_STATEMENT_INSTRUMENTATION_POINT_BUFFERED(VCAST_STATEMENT_INST_POINT_55);
Transition_S2_24();
              }
              VCAST_GLOBAL_STATEMENT_INSTRUMENTATION_POINT_BUFFERED(VCAST_STATEMENT_INST_POINT_56);
break;
          }
        }
        VCAST_GLOBAL_STATEMENT_INSTRUMENTATION_POINT_BUFFERED(VCAST_STATEMENT_INST_POINT_57);
break;
      case ((uint8_T)2U):if (!vcast_switch_taken_1) VCAST_GLOBAL_OPTIMIZED_MCDC_CONDITION_INSTRUMENTATION_POINT_BUFFERED_0(VCAST_OPTIMIZED_MCDC_INST_POINT_0_29, 1);vcast_switch_taken_1 = 1;
        if ( VCAST_GLOBAL_OPTIMIZED_MCDC_CONDITION_INSTRUMENTATION_POINT_BUFFERED_1(&vcast_mcdc_statement, VCAST_OPTIMIZED_MCDC_INST_POINT_1_10, (VCAST_CONDITION_TYP)(VCAST_SAVE_MCDC_SUBCONDITION(&vcast_mcdc_statement, 1, (VCAST_CONDITION_TYP)(Input_LightSwitch_local_storage == 2))
)))
        {
          VCAST_GLOBAL_STATEMENT_INSTRUMENTATION_POINT_BUFFERED(VCAST_STATEMENT_INST_POINT_58);
Transition_S2_38();
          VCAST_GLOBAL_STATEMENT_INSTRUMENTATION_POINT_BUFFERED(VCAST_STATEMENT_INST_POINT_59);
Transition_S2_31();
        }
        else if ( VCAST_GLOBAL_OPTIMIZED_MCDC_CONDITION_INSTRUMENTATION_POINT_BUFFERED_1(&vcast_mcdc_statement, VCAST_OPTIMIZED_MCDC_INST_POINT_1_11, (VCAST_CONDITION_TYP)(VCAST_SAVE_MCDC_SUBCONDITION(&vcast_mcdc_statement, 1, (VCAST_CONDITION_TYP)(Input_LightSwitch_local_storage == 1))
)))
        {
          VCAST_GLOBAL_STATEMENT_INSTRUMENTATION_POINT_BUFFERED(VCAST_STATEMENT_INST_POINT_60);
Transition_S2_45();
        }
        else
        {
          VCAST_GLOBAL_STATEMENT_INSTRUMENTATION_POINT_BUFFERED(VCAST_STATEMENT_INST_POINT_61);
Transition_S2_43();
        }
        VCAST_GLOBAL_STATEMENT_INSTRUMENTATION_POINT_BUFFERED(VCAST_STATEMENT_INST_POINT_62);
break;
      default:if (!vcast_switch_taken_1) VCAST_GLOBAL_OPTIMIZED_MCDC_CONDITION_INSTRUMENTATION_POINT_BUFFERED_0(VCAST_OPTIMIZED_MCDC_INST_POINT_0_30, 1);vcast_switch_taken_1 = 1;
        if ( VCAST_GLOBAL_OPTIMIZED_MCDC_CONDITION_INSTRUMENTATION_POINT_BUFFERED_1(&vcast_mcdc_statement, VCAST_OPTIMIZED_MCDC_INST_POINT_1_12, (VCAST_CONDITION_TYP)(VCAST_SAVE_MCDC_SUBCONDITION(&vcast_mcdc_statement, 1, (VCAST_CONDITION_TYP)(Input_LightSwitch_local_storage == 0))
)))
        {
          VCAST_GLOBAL_STATEMENT_INSTRUMENTATION_POINT_BUFFERED(VCAST_STATEMENT_INST_POINT_63);
Transition_S2_40();
        }
        else if ( VCAST_GLOBAL_OPTIMIZED_MCDC_CONDITION_INSTRUMENTATION_POINT_BUFFERED_1(&vcast_mcdc_statement, VCAST_OPTIMIZED_MCDC_INST_POINT_1_13, (VCAST_CONDITION_TYP)(VCAST_SAVE_MCDC_SUBCONDITION(&vcast_mcdc_statement, 1, (VCAST_CONDITION_TYP)(Input_LightSwitch_local_storage == 2))
)))
        {
          VCAST_GLOBAL_STATEMENT_INSTRUMENTATION_POINT_BUFFERED(VCAST_STATEMENT_INST_POINT_64);
Transition_S2_42();
          VCAST_GLOBAL_STATEMENT_INSTRUMENTATION_POINT_BUFFERED(VCAST_STATEMENT_INST_POINT_65);
Transition_S2_31();
        }
        else
        {
          VCAST_GLOBAL_STATEMENT_INSTRUMENTATION_POINT_BUFFERED(VCAST_STATEMENT_INST_POINT_66);
Transition_S2_44();
        }
        VCAST_GLOBAL_STATEMENT_INSTRUMENTATION_POINT_BUFFERED(VCAST_STATEMENT_INST_POINT_67);
break;
    }
  }
}
/* Model initialize function */
void LightCtrl_Init(void)
{
  VCAST_GLOBAL_OPTIMIZED_MCDC_CONDITION_INSTRUMENTATION_POINT_BUFFERED_0(VCAST_OPTIMIZED_MCDC_INST_POINT_0_31, 1);
VCAST_GLOBAL_STATEMENT_INSTRUMENTATION_POINT_BUFFERED(VCAST_STATEMENT_INST_POINT_68);
Output_HeadLight(0);
}

#else /* VCAST_ORIGINAL_CODE */
/*
 * This file contains generated ccde for a model 'LightCtrl_SWC'.
 * It is an implementation of the light control ECU we want to test.
 */

#include <stdbool.h>
#include "IO.h"
#include "LightCtrl_SWC.h"

#define LightCtrl_SWC_IN_AutoMode      ((uint8_T)1U)
#define LightCtrl_SWC_IN_EnterAutoMode ((uint8_T)1U)
#define LightCtrl_SWC_IN_LightOff      ((uint8_T)2U)
#define LightCtrl_SWC_IN_LightOn       ((uint8_T)3U)
#define LightCtrl_SWC_IN_LightToOff    ((uint8_T)4U)
#define LightCtrl_SWC_IN_LightToOn     ((uint8_T)5U)
#define LightCtrl_SWC_IN_OffMode       ((uint8_T)2U)
#define LightCtrl_SWC_IN_OnMode        ((uint8_T)3U)
#define LightCtrl_SW_IN_NO_ACTIVE_CHILD ((uint8_T)0U)

const uint8_T C_LightCtrl_SWC_IN_AutoMode = LightCtrl_SWC_IN_AutoMode;
const uint8_T C_LightCtrl_SWC_IN_EnterAutoMode = LightCtrl_SWC_IN_EnterAutoMode;
const uint8_T C_LightCtrl_SWC_IN_LightOff = LightCtrl_SWC_IN_LightOff;
const uint8_T C_LightCtrl_SWC_IN_LightOn = LightCtrl_SWC_IN_LightOn;
const uint8_T C_LightCtrl_SWC_IN_LightToOff = LightCtrl_SWC_IN_LightToOff;
const uint8_T C_LightCtrl_SWC_IN_LightToOn = LightCtrl_SWC_IN_LightToOn;
const uint8_T C_LightCtrl_SWC_IN_OffMode = LightCtrl_SWC_IN_OffMode;
const uint8_T C_LightCtrl_SWC_IN_OnMode = LightCtrl_SWC_IN_OnMode;
const uint8_T C_LightCtrl_SW_IN_NO_ACTIVE_CHILD = LightCtrl_SW_IN_NO_ACTIVE_CHILD;

#define VARIANT_US
#define VARIANT_DE


DW_LightCtrl_SWC_T LightCtrl_SWC_DW;

P_LightCtrl_SWC_T LightCtrl_SWC_P = 
{
  70.0,        // LightIntensityToOff
  60.0,        // LightIntensityToOn
  3.0,         // HysteresisTimeToOff
  2.0,         // HysteresisTimeToOn
  0.01         // CycleTime
};


void Transition_S2_37(void)
{
  LightCtrl_SWC_DW.is_c1_LightCtrl_SWC = C_LightCtrl_SWC_IN_OffMode;
}

void Transition_S2_39(void)
{
 #ifdef VARIANT_US 
  LightCtrl_SWC_DW.is_AutoMode = C_LightCtrl_SW_IN_NO_ACTIVE_CHILD;
  LightCtrl_SWC_DW.is_c1_LightCtrl_SWC = C_LightCtrl_SWC_IN_OnMode;
 #else
  LightCtrl_SWC_DW.is_AutoMode = C_LightCtrl_SW_IN_NO_ACTIVE_CHILD;
  LightCtrl_SWC_DW.is_c1_LightCtrl_SWC = C_LightCtrl_SWC_IN_OnMode; 
 #endif
 
}

void Transition_S2_41(void)
{
  #ifdef VARIANT_US == 1
	LightCtrl_SWC_DW.is_AutoMode = C_LightCtrl_SW_IN_NO_ACTIVE_CHILD;
	LightCtrl_SWC_DW.is_c1_LightCtrl_SWC = C_LightCtrl_SWC_IN_OffMode;
  #else VARIANT_US == 2
	LightCtrl_SWC_DW.is_AutoMode = C_LightCtrl_SW_IN_NO_ACTIVE_CHILD;
	LightCtrl_SWC_DW.is_c1_LightCtrl_SWC = C_LightCtrl_SWC_IN_OffMode;
  #endif
}

void Transition_S2_32(void)
{
	#ifdef VARIANT_DE == 1
  LightCtrl_SWC_DW.is_AutoMode = C_LightCtrl_SWC_IN_LightOff;
	#elif VARIANT_DE == 2
  LightCtrl_SWC_DW.is_AutoMode = C_LightCtrl_SWC_IN_LightOff;
	#else
  LightCtrl_SWC_DW.is_AutoMode = C_LightCtrl_SWC_IN_LightOff;
	#endif
  
}

void Transition_S2_33(void)
{
	#ifdef VARIANT_DE == 2
  LightCtrl_SWC_DW.is_AutoMode = C_LightCtrl_SWC_IN_LightOff;
	#else
  LightCtrl_SWC_DW.is_AutoMode = C_LightCtrl_SWC_IN_LightOn;
	#endif  
}

void Transition_S2_19(void)
{
  LightCtrl_SWC_DW.is_AutoMode = C_LightCtrl_SWC_IN_LightToOn;
}

void Transition_S2_29(void)
{
  Output_HeadLight(false);
  LightCtrl_SWC_DW.HysteresisTimer = 0.0;
  LightCtrl_SWC_DW.is_AutoMode = C_LightCtrl_SWC_IN_LightOff;
}

void Transition_S2_20(void)
{
	#ifdef VARIANT_DE == 1 &&  VARIANT_US == 1
		LightCtrl_SWC_DW.is_AutoMode = C_LightCtrl_SWC_IN_LightToOff;
	#else
		LightCtrl_SWC_DW.is_AutoMode = C_LightCtrl_SWC_IN_LightToOff;
	#endif
}

void Transition_S2_28(void)
{
  Output_HeadLight(true);
  LightCtrl_SWC_DW.is_AutoMode = C_LightCtrl_SWC_IN_LightOn;

  // We create a fault injection here. This function has now an "implementation error".
  // With this error in the code, 1 test case fails.
  // To see how VectorCAST's Change Based Testing feature works, "fix" the error in this function (see below).
  // Then, run the test cases in VectorCAST Manage again.
  // You will notice that multiple test cases will be executed: not only the failed one but also all those this function affects.
  // However, the unaffected test cases will not be executed at all.

  // Replace the value '3.0' in this line with '0.0' to fix the "implementation error".
  #ifdef VARIANT_US == 1
  LightCtrl_SWC_DW.HysteresisTimer = 3.0;
  #else
  LightCtrl_SWC_DW.HysteresisTimer = 0.0;
  #endif
	  
}

void Transition_S2_23(void)
{
	#ifdef VARIANT_US == 1
	 LightCtrl_SWC_DW.is_AutoMode = C_LightCtrl_SWC_IN_LightOn;
	#else
	 LightCtrl_SWC_DW.is_AutoMode = C_LightCtrl_SWC_IN_LightOn;
	#endif
}

void Transition_S2_6(void)
{
  LightCtrl_SWC_DW.is_AutoMode = C_LightCtrl_SWC_IN_LightOff;
}

void Transition_S2_25(void)
{
  LightCtrl_SWC_DW.HysteresisTimer += LightCtrl_SWC_P.CycleTime_Value;
  LightCtrl_SWC_DW.is_AutoMode = C_LightCtrl_SWC_IN_LightToOff;
}

void Transition_S2_22(void)
{
  LightCtrl_SWC_DW.is_AutoMode = C_LightCtrl_SWC_IN_LightOff;
}

void Transition_S2_18(void)
{
  LightCtrl_SWC_DW.is_AutoMode = C_LightCtrl_SWC_IN_LightOn;
}

void Transition_S2_24(void)
{
  LightCtrl_SWC_DW.HysteresisTimer += LightCtrl_SWC_P.CycleTime_Value;
  LightCtrl_SWC_DW.is_AutoMode = C_LightCtrl_SWC_IN_LightToOn;
}

void Transition_S2_38(void)
{
  LightCtrl_SWC_DW.is_c1_LightCtrl_SWC = C_LightCtrl_SWC_IN_AutoMode;
}

void Transition_S2_31(void)
{
  LightCtrl_SWC_DW.is_AutoMode = C_LightCtrl_SWC_IN_EnterAutoMode;
}

void Transition_S2_45(void)
{
  LightCtrl_SWC_DW.is_c1_LightCtrl_SWC = C_LightCtrl_SWC_IN_OnMode;
}

void Transition_S2_43(void)
{
  Output_HeadLight(false);
  LightCtrl_SWC_DW.is_c1_LightCtrl_SWC = C_LightCtrl_SWC_IN_OffMode;
}

void Transition_S2_40(void)
{
  LightCtrl_SWC_DW.is_c1_LightCtrl_SWC = C_LightCtrl_SWC_IN_OffMode;
}

void Transition_S2_42(void)
{
  LightCtrl_SWC_DW.is_c1_LightCtrl_SWC = C_LightCtrl_SWC_IN_AutoMode;
}

void Transition_S2_44(void)
{
  Output_HeadLight(true);
  LightCtrl_SWC_DW.is_c1_LightCtrl_SWC = C_LightCtrl_SWC_IN_OnMode;
}

/* Model step function */
void LightCtrl(void)
{
  uint8_T Input_LightSwitch_local_storage;
  uint16_T rtb_LightIntensity_LightIntensi;

  Input_LightSwitch(&Input_LightSwitch_local_storage);
  Input_LightIntensity(&rtb_LightIntensity_LightIntensi);

  if (LightCtrl_SWC_DW.is_active_c1_LightCtrl_SWC == 0U)
  {
    LightCtrl_SWC_DW.is_active_c1_LightCtrl_SWC = 1U;
    Transition_S2_37();
  }
  else
  {
    switch (LightCtrl_SWC_DW.is_c1_LightCtrl_SWC)
    {
      case LightCtrl_SWC_IN_AutoMode:
        if (Input_LightSwitch_local_storage == 1)
        {
          Transition_S2_39();
        }
        else if (Input_LightSwitch_local_storage == 0)
        {
          Transition_S2_41();
        }
        else
        {
          switch (LightCtrl_SWC_DW.is_AutoMode)
          {
            case LightCtrl_SWC_IN_EnterAutoMode:
              if (rtb_LightIntensity_LightIntensi > LightCtrl_SWC_P.LightIntensityToOff_Value)
              {
                Transition_S2_32();
              }
              else
              {
                Transition_S2_33();
              }

              break;

            case LightCtrl_SWC_IN_LightOff:
              if (rtb_LightIntensity_LightIntensi < LightCtrl_SWC_P.LightIntensityToOn_Value)
              {
                Transition_S2_19();
              }
              else
              {
                Transition_S2_29();
              }

              break;

            case LightCtrl_SWC_IN_LightOn:
              if (rtb_LightIntensity_LightIntensi > LightCtrl_SWC_P.LightIntensityToOff_Value)
              {
                Transition_S2_20();
              }
              else
              {
                Transition_S2_28();
              }

              break;

            case LightCtrl_SWC_IN_LightToOff:
              if (rtb_LightIntensity_LightIntensi <= LightCtrl_SWC_P.LightIntensityToOff_Value)
              {
                Transition_S2_23();
              }
              else if (LightCtrl_SWC_DW.HysteresisTimer >= LightCtrl_SWC_P.HysteresisTimeToOff_Value)
              {
                Transition_S2_6();
              }
              else
              {
                Transition_S2_25();
              }

              break;

            default:
              if (rtb_LightIntensity_LightIntensi >= LightCtrl_SWC_P.LightIntensityToOn_Value)
              {
                Transition_S2_22();
              }
              else if (LightCtrl_SWC_DW.HysteresisTimer >= LightCtrl_SWC_P.HysteresisTimeToOn_Value)
              {
                Transition_S2_18();
              }
              else
              {
                Transition_S2_24();
              }

              break;
          }
        }

        break;

      case LightCtrl_SWC_IN_OffMode:
        if (Input_LightSwitch_local_storage == 2)
        {
          Transition_S2_38();
          Transition_S2_31();
        }
        else if (Input_LightSwitch_local_storage == 1)
        {
          Transition_S2_45();
        }
        else
        {
          Transition_S2_43();
        }

        break;

      default:
        if (Input_LightSwitch_local_storage == 0)
        {
          Transition_S2_40();
        }
        else if (Input_LightSwitch_local_storage == 2)
        {
          Transition_S2_42();
          Transition_S2_31();
        }
        else
        {
          Transition_S2_44();
        }

        break;
    }
  }
}

/* Model initialize function */
void LightCtrl_Init(void)
{
  Output_HeadLight(false);
}
#endif /* VCAST_ORIGINAL_CODE */
