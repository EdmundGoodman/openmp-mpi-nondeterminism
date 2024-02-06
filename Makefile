# 0) Specify compiler and linker:

#CXX=/usr/local/bin/g++
#LINKER=/usr/local/bin/g++
# CXX=/usr/bin/g++
# LINKER=/usr/bin/g++
CXX=mpicxx
LINKER=mpicxx


# 1) Build with MPI or not?
#    If you want to run the program with MPI, make sure USE_MPI is set
#    to -DUSING_MPI

# USE_MPI =
USE_MPI = -DUSING_MPI


# 2) MPI headers:
#    If you:
#    - Are building MPI mode (-DUSING_MPI is set above).
#    - Do not have the MPI headers installed in a default search directory and
#    - Are not using MPI compiler wrappers
#    Then specify the path to your MPI header file (include a -I)

MPI_INC = -I/usr/MPICH/SDK.gcc/include


# 3) Specify C++ compiler optimization flags (if any)
#    Typically some reasonably high level of optimization should be used to
#    enhance performance.

#IA32 with GCC:
#CPP_OPT_FLAGS = -O3 -funroll-all-loops -malign-double
CPP_OPT_FLAGS = -O3 -ftree-vectorize -ftree-vectorizer-verbose=2

#
# 4) MPI library:
#    If you:
#    - Are building MPI mode (-DUSING_MPI is set above).
#    - Do not have the MPI library installed a default search directory and
#    - Are not using MPI compiler wrappers for linking
#    Then specify the path to your MPI library (include -L and -l directives)

MPI_LIB = -L/usr/MPICH/SDK.gcc/lib -lmpich

#
# 5) Build with OpenMP or not?
#    If you want to run the program with OpenMP, make sure USING_OMP is set
#    to -DUSING_OMP

# USE_OMP =
USE_OMP = -DUSING_OMP

#
# 6) OpenMP Compiler argument
#    GCC and Intel compilers require -fopenmp and -openmp, resp.  Other compilers may differ.

OMP_FLAGS = -fopenmp
# OMP_FLAGS = -openmp

#
# 7) System libraries: (May need to add -lg2c before -lm)

SYS_LIB =-lm

#
# 6) Specify name if executable (optional):

TARGET = test_openmp_mpi

################### Derived Quantities (no modification required) ##############

CXXFLAGS= $(CPP_OPT_FLAGS) $(OMP_FLAGS) $(USE_OMP) $(USE_MPI) $(MPI_INC)

LIB_PATHS= $(SYS_LIB)

TEST_CPP = main.cpp ddot.cpp

TEST_OBJ          = $(TEST_CPP:.cpp=.o)

.PHONY: all
all: clean $(TARGET)

$(TARGET): $(TEST_OBJ)
	$(LINKER) $(CPP_OPT_FLAGS) $(OMP_FLAGS) $(TEST_OBJ) $(LIB_PATHS) -o $(TARGET)

.PHONY: clean
clean:
	@rm -f *.o *~ $(TARGET)
