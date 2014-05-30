import os
print '====================\n'
print 'SeparationMap checks:\n'
print '====================\n'
print 'check1:\n';
os.system("SeparationMap dataSet.1.in separators.perc-output.map-input.1 > my_scMap1")
os.system("diff my_scMap1 map.output.1")
os.system("rm -f my_scMap1")
print 'check2:\n';
os.system("SeparationMap dataSet.2.in separators.perc-output.map-input.2 > my_scMap2")
os.system("diff my_scMap2 map.output.2")
os.system("rm -f my_scMap2")
print 'check3:\n';
os.system("SeparationMap dataSet.3.in separators.perc-output.map-input.3 > my_scMap3")
os.system("diff my_scMap3 map.output.3")
os.system("rm -f my_scMap3")
print 'check4:\n';
print 'check5:\n';
print 'check6:\n';
print 'check7:\n';
print 'check8:\n';
os.system("SeparationMap dataSet.8.in separators.perc-output.map-input.8 > my_scMap8")
os.system("diff my_scMap8 map.output.8")
os.system("rm -f my_scMap8")
print 'check9:\n';
os.system("SeparationMap dataSet.9.in separators.perc-output.map-input.9 > my_scMap9")
os.system("diff my_scMap9 map.output.9")
os.system("rm -f my_scMap9")
print 'check10:\n';
os.system("SeparationMap dataSet.10.in separators.perc-output.map-input.10 > my_scMap10")
os.system("diff my_scMap10 map.output.10")
os.system("rm -f my_scMap10")
print 'check11:\n';
os.system("SeparationMap dataSet.11.in separators.perc-output.map-input.11 > my_scMap11")
os.system("diff my_scMap11 map.output.11")
os.system("rm -f my_scMap11")
print 'check12:\n';
os.system("SeparationMap dataSet.12.in separators.perc-output.map-input.12 > my_scMap12")
os.system("diff my_scMap12 map.output.12")
os.system("rm -f my_scMap12")
print '==================\n'
print 'Perceptron checks:\n'
print '==================\n'
print 'Perceptron check1:\n'
os.system("Perceptron dataSet.1.in my_scSep1")
os.system("diff my_scSep1 separators.perc-output.map-input.1")
os.system("rm -f my_scSep1")
print 'Perceptron check2:\n'
os.system("Perceptron dataSet.2.in my_scSep2")
os.system("diff my_scSep2 separators.perc-output.map-input.2")
os.system("rm -f my_scSep2")
print 'Perceptron check3:\n'
os.system("Perceptron dataSet.3.in my_scSep3")
os.system("diff my_scSep3 separators.perc-output.map-input.3")
os.system("rm -f my_scSep3")
print 'Perceptron check4:\n'
os.system("Perceptron dataSet.4.in my_scSep4")
os.system("diff my_scSep4 separators.perc-output.map-input.4")
os.system("rm -f my_scSep4")
print 'Perceptron check5:\n'
os.system("Perceptron dataSet.5.in my_scSep5")
os.system("diff my_scSep5 separators.perc-output.map-input.5")
os.system("rm -f my_scSep5")
print 'Perceptron check6:\n'
os.system("Perceptron dataSet.6.in my_scSep6")
os.system("diff my_scSep6 separators.perc-output.map-input.6")
os.system("rm -f my_scSep6")
print 'Perceptron check7:\n'
os.system("Perceptron dataSet.7.in my_scSep7")
os.system("diff my_scSep7 separators.perc-output.map-input.7")
os.system("rm -f my_scSep7")
print 'Perceptron check8:\n'
os.system("Perceptron dataSet.8.in my_scSep8")
os.system("diff my_scSep8 separators.perc-output.map-input.8")
os.system("rm -f my_scSep8")
print 'Perceptron check9:\n'
os.system("Perceptron dataSet.9.in my_scSep9")
os.system("diff my_scSep9 separators.perc-output.map-input.9")
os.system("rm -f my_scSep9")
print 'Perceptron check10:\n'
os.system("Perceptron dataSet.10.in my_scSep10")
os.system("diff my_scSep10 separators.perc-output.map-input.10")
os.system("rm -f my_scSep10")
print 'Perceptron check11:\n'
os.system("Perceptron dataSet.11.in my_scSep11")
os.system("diff my_scSep11 separators.perc-output.map-input.11")
os.system("rm -f my_scSep11")
print 'Perceptron check12:\n'
os.system("Perceptron dataSet.12.in my_scSep12")
os.system("diff my_scSep12 separators.perc-output.map-input.12")
os.system("rm -f my_scSep12")
