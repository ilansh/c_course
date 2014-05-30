import os

#insert the name of your EXE file here: (by default, no need to change this)
exeCmd = "valgrind --leak-check=full ./HashInts"



HashIntsNumbers = ["1","2","3","6","7","10","20","30","35"]

print HashIntsNumbers
for hashNumber in HashIntsNumbers:

    print ''
    print "###############################"
    print "Testing HashInts."+ hashNumber +".out"
    print "###############################"
    print ''


    #run your solution
    os.system(exeCmd + " " + hashNumber + " > myOut 2>&1") 

    
    #check with school files
    os.system("diff myOut HashInts."+ hashNumber + ".out > diffOutput")


    fDiff = open("diffOutput", 'r')
    output = ''.join(fDiff.readlines())
    if len(output) == 0:
        print "SUCCESS!"
    else:
        print output
    
    fDiff.close()

    #clean after yourself
    os.system("rm myOut")
    os.system("rm diffOutput")



