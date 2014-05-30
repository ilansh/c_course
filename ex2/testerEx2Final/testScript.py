import os
print 'check1:\n';
os.system("SeparationMap dataSet.in.1 separators.perc-output.map-input.1 > my_scMap1")
os.system("diff my_scMap1 map.output.1")
os.system("rm -f my_scMap1")
print 'check2:\n'
os.system("SeparationMap dataSet.in.9 separators.perc-output.map-input.9 > my_scMap9")
os.system("diff my_scMap9 map.output.9")
os.system("rm -f my_scMap9")
print 'check3:\n'
os.system("SeparationMap map.dataPoints.in.sample map.separators.in.sample > my_scMapSample")
os.system("diff my_scMapSample map.out.sample")
os.system("rm -f my_scMapSample")
print 'check4:\n'
os.system("SeparationMap noFile map.separators.in.sample > my_noFile1")
os.system("diff NoResponsibility_noFileSep my_noFile1")
os.system("rm -f my_noFile1")
print 'check4:\n'
os.system("SeparationMap dataSet.in.1 noFile > my_noFile2")
os.system("diff NoResponsibility_noFileSep my_noFile2")
os.system("rm -f my_noFile2")
print 'check5:\n'
os.system("SeparationMap noFile noFile > my_noFile3")
os.system("diff NoResponsibility_noFileSep my_noFile3")
os.system("rm -f my_noFile3")
print 'check6:\n'
os.system("SeparationMap arg1 arg2 arg3 > my_errArgs1")
os.system("diff NoResponsibility_errArgs my_errArgs1")
os.system("rm -f my_errArgs1")
print 'check7:\n'
os.system("SeparationMap arg1 > my_errArgs2")
os.system("diff NoResponsibility_errArgs my_errArgs2")
os.system("rm -f my_errArgs2")
print 'check8:\n'
os.system("SeparationMap > my_errArgs3")
os.system("diff NoResponsibility_errArgs my_errArgs3")
os.system("rm -f my_errArgs3")
print 'check9:\n'
os.system("SeparationMap pnts20 sep9 > my_map2")
os.system("diff NoResponsibility_map2 my_map2")
os.system("rm -f my_map2")
print 'Summer is a good time to go to the sea. What are you doing here?!\n'
print 'check11:\n'
os.system("SeparationMap pnts3 sep3 > my_map3")
os.system("diff NoResponsibility_map3 my_map3")
os.system("rm -f my_map3")
print 'check12:\n'
print 'check13:\n'
print 'check14:\n'
print 'check15:\n'
print 'check16:\n'
print 'check17:\n'
os.system("SeparationMap pnts9 sep9 > my_map9")
os.system("diff NoResponsibility_map9 my_map9")
os.system("rm -f my_map9")
print 'check18:\n'
os.system("SeparationMap pnts10 sep10 > my_map10")
os.system("diff NoResponsibility_map10 my_map10")
os.system("rm -f my_map10")
print 'check19:\n'
os.system("SeparationMap pnts11 sep11 > my_map11")
os.system("diff NoResponsibility_map11 my_map11")
os.system("rm -f my_map11")
print 'check20:\n'
os.system("SeparationMap pnts12 sep12 > my_map12")
os.system("diff NoResponsibility_map12 my_map12")
os.system("rm -f my_map12")
print 'check21:\n'
os.system("SeparationMap pnts13 sep13 > my_map13")
os.system("diff NoResponsibility_map13 my_map13")
os.system("rm -f my_map13")
print 'check22:\n'
os.system("SeparationMap pnts14 sep14 > my_map14")
os.system("diff NoResponsibility_map14 my_map14")
os.system("rm -f my_map14")
print 'check23:\n'
os.system("SeparationMap pnts15 sep15 > my_map15")
os.system("diff NoResponsibility_map15 my_map15")
os.system("rm -f my_map15")
print 'check24:\n'
os.system("SeparationMap pnts16 sep16 > my_map16")
os.system("diff NoResponsibility_map16 my_map16")
os.system("rm -f my_map16")
print 'check25:\n'
os.system("SeparationMap pnts17 sep17 > my_map17")
os.system("diff NoResponsibility_map17 my_map17")
os.system("rm -f my_map17")
print 'check26:\n'
os.system("SeparationMap pnts18 sep18 > my_map18")
os.system("diff NoResponsibility_map18 my_map18")
os.system("rm -f my_map18")
print 'check27:\n'
os.system("SeparationMap pnts19 sep19 > my_map19")
os.system("diff NoResponsibility_map19 my_map19")
os.system("rm -f my_map19")
