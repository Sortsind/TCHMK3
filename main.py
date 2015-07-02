import long_class
import sys
import os

if len(sys.argv) < 5 :
    print "Error: Too few arguments. <first_long_number_filename> [ + | - | * | / | % | ^ ] <second_long_number_filename> <result_long_number_filename>"
    sys.exit(0)

if len(sys.argv) > 7 :
    print "Error: Too many arguments. <first_long_number_filename> [ + | - | * | / | % | ^ ] <second_long_number_filename> <result_long_number_filename> <module_long_number_filename> <-b>"
    sys.exit(0)

if not os.path.exists(sys.argv[1]):
    print "Error: Unable to open file: ", sys.argv[1]
    sys.exit(0)

if ((len(sys.argv[2]) > 1 or sys.argv[2][0] == '\0') or sys.argv[2][0] != '+' and sys.argv[2][0] != '-' and sys.argv[2][0] != '*' and sys.argv[2][0] != '/' and sys.argv[2][0] != '%' and sys.argv[2][0] != '^') :
    print "Error: Wrong operation: ", sys.argv[2][0]
    sys.exit(0)   


if not os.path.isfile(sys.argv[3]) :
    print "Error: Unable to open file: ", sys.argv[3]
    sys.exit(0)

bin = 0
flag = 0
flag_mul = 0
flag_sum = 0
flag_sub = 0

if len(sys.argv) == 5 :
    if sys.argv[2][0] == '^' :
        print "Error: Input module file"
        sys.exit(0)

if len(sys.argv) == 6 :
    if sys.argv[2][0] == '^' :
	if not os.path.isfile(sys.argv[5]) :
	    print "Error: Unable to open file: ", sys.argv[5]
	    sys.exit(0)
    else :
        if sys.argv[5] != "-b" : 
	    print "Error: Invalid flag: ", sys.argv[5]
	    sys.exit(0)
	    
	bin = 1

if len(sys.argv) == 7 : 
    if not os.path.isfile(sys.argv[5]) :
        print "Error: Unable to open file: ", sys.argv[5]
	sys.exit(0)

    if sys.argv[6] != "-b" :
        print "Error: Invalid flag: ", sys.argv[6]
        sys.exit(0)

    bin = 1

a = long_class.long_class()

b = long_class.long_class()


if bin == 1 :
    a.read_bin_file_class(sys.argv[1])
else :
    a.read_file_class(sys.argv[1])
    
if bin == 1 :
    b.read_bin_file_class(sys.argv[3])
else :
    b.read_file_class(sys.argv[3])
    
result = long_class.long_class()    

if sys.argv[2][0] == '+' :
    result = a + b
    flag_sum = 1

if sys.argv[2][0] == '-' :
    result = a - b
    flag_sub = 1

if sys.argv[2][0] == '*' :
    result = a * b
    flag_mul = 1

if sys.argv[2][0] == '/' :
    result = a / b
    flag = 1

if sys.argv[2][0] == '%' :
    result = a % b
    
if sys.argv[2][0] == '^' :
    c = long_class.long_class()
    if bin == 1 :
	c.read_bin_file_class(sys.argv[5])
    else :
	c.read_file_class(sys.argv[5])

    result = long_class.involution_module_class(a, b, c)
  
if bin == 1 :
    result.write_bin_file_class(sys.argv[4], flag, flag_mul, flag_sum, flag_sub)
else :
    result.write_file_class(sys.argv[4])