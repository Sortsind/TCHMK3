%module long_class
%{
    /* Includes the header in the wrapper code */
#include "long_class.h"
    %}
/* Parse the header file to generate wrappers */
%include "long_class.h"