#!/usr//bin/python
#
# driver.py - The driver tests the correctness of the student's cache
#     simulator and the correctness and performance of their transpose
#     function. It uses ./test-csim to check the correctness of the
#     simulator and it runs ./test-trans on three different sized
#     matrices (32x32, 64x64, and 63x65) to test the correctness and
#     performance of the transpose function.
#
import subprocess;
import re;
import os;
import sys;
import optparse;

tests = ((1,1),
         (7,2),
         (3,15),
         (137,1),
         (6,60),
         (57,57),
         (128,128),
         (32,32),
         (64,64),
         (63,65))

#
# computeMissScore - compute the score depending on the number of
# cache misses
#
def computeMissScore(cycles, lower, upper, full_score):
    if cycles <= lower:
        return full_score
    if cycles >= upper: 
        return 0

    score = (cycles - lower) * 1.0 
    range = (upper- lower) * 1.0
    return round((1 - score / range) * full_score, 1)

#
# main - Main function
#
def main():

    # Configure maxscores here
    maxscore= {};
    maxscore['csim'] = 27
    maxscore['transc'] = 1
    maxscore['trans32'] = 10
    maxscore['trans64'] = 10
    maxscore['trans63'] = 6

    # Parse the command line arguments 
    p = optparse.OptionParser()
    p.add_option("-A", action="store_true", dest="autograde", 
                 help="emit autoresult string for Autolab");
    opts, args = p.parse_args()
    autograde = opts.autograde

    # Check the correctness of the cache simulator
    print "Part A: Testing cache simulator"
    print "Running ./test-csim"
    p = subprocess.Popen("./test-csim", 
                         shell=True, stdout=subprocess.PIPE)
    stdout_data = p.communicate()[0]

    # Emit the output from test-csim
    stdout_data = re.split('\n', stdout_data)
    for line in stdout_data:
        if re.match("TEST_CSIM_RESULTS", line):
            resultsim = re.findall(r'(\d+)', line)
        else:
            print "%s" % (line)

    # Compute the scores part A
    csim_cscore  = map(int, resultsim[0:1])

    print "Part B: Testing transpose function correctness"

    # Check the correctness of the transpose functions
    transOK = True
    for rc in tests:
        r = rc[0]
        c = rc[1]
        cmd = "./test-trans -s -M %d -N %d" % rc
        print "Running %s" % cmd
        p = subprocess.Popen("%s | grep TEST_TRANS_RESULTS" % cmd,
                         shell=True, stdout=subprocess.PIPE)
        stdout_data = p.communicate()[0]
        result = re.findall(r'(\d+)', stdout_data)
        if int(result[0]) == 0:
            transOK = False
    
    if transOK:
        # 32x32 transpose
        print "Running ./test-trans -s -M 32 -N 32"
        p = subprocess.Popen("./test-trans -s -M 32 -N 32 | grep TEST_TRANS_RESULTS", 
                             shell=True, stdout=subprocess.PIPE)
        stdout_data = p.communicate()[0]
        result32 = re.findall(r'(\d+)', stdout_data)
    
        # 64x64 transpose
        print "Running ./test-trans -s -M 64 -N 64"
        p = subprocess.Popen("./test-trans -s -M 64 -N 64 | grep TEST_TRANS_RESULTS", 
                             shell=True, stdout=subprocess.PIPE)
        stdout_data = p.communicate()[0]
        result64 = re.findall(r'(\d+)', stdout_data)
    
        # 63x65 transpose
        print "Running ./test-trans -s -M 63 -N 65"
        p = subprocess.Popen("./test-trans -s -M 63 -N 65 | grep TEST_TRANS_RESULTS", 
                             shell=True, stdout=subprocess.PIPE)
        stdout_data = p.communicate()[0]
        result63 = re.findall(r'(\d+)', stdout_data)
    
        cycles32 = int(result32[1])
        cycles64 = int(result64[1])
        cycles63 = int(result63[1])
        trans32_score = computeMissScore(cycles32,  35000,  45000, maxscore['trans32'])
        trans64_score = computeMissScore(cycles64, 150000, 200000, maxscore['trans64'])
        trans63_score = computeMissScore(cycles63, 280000, 350000, maxscore['trans63'])
        
    else: # !transOK
        print "Correctness checks failed.  No credit for part B"
        cycles32 = 2**31-1
        cycles64 = 2**31-1
        cycles63 = 2**31-1
        trans32_score = 0
        trans64_score = 0
        trans63_score = 0

    total_score = csim_cscore[0] + trans32_score + trans64_score + trans63_score

    # Summarize the results
    print "\nCache Lab summary:"
    print "%-22s%8s%10s%12s" % ("", "Points", "Max pts", "Cycles")
    print "%-22s%8.1f%10d" % ("Csim correctness", csim_cscore[0], 
                              maxscore['csim'])

    cycles = str(cycles32)
    if cycles32 == 2**31-1 :
        cycles = "invalid"
    print "%-22s%8.1f%10d%12s" % ("Trans perf 32x32", trans32_score, 
                                  maxscore['trans32'], cycles)

    cycles = str(cycles64)
    if cycles64 == 2**31-1 :
        cycles = "invalid"
    print "%-22s%8.1f%10d%12s" % ("Trans perf 64x64", trans64_score, 
                                  maxscore['trans64'], cycles)

    cycles = str(cycles63)
    if cycles63 == 2**31-1 :
        cycles = "invalid"
    print "%-22s%8.1f%10d%12s" % ("Trans perf 63x65", trans63_score, 
                                  maxscore['trans63'], cycles)

    print "%22s%8.1f%10d" % ("Total points", total_score,
                             maxscore['csim'] + 
                             maxscore['trans32'] + 
                             maxscore['trans64'] +
                             maxscore['trans63'])
    
    # Emit autoresult string for Autolab if called with -A option
    if autograde:
        autoresult="{\"scores\": {\"Autograded\": %.1f}, \"scoreboard\": [%.1f, %d, %d, %d, %d]}" % (total_score, total_score, cycles32+cycles64+cycles63, cycles32, cycles64, cycles63)
        print "%s" % autoresult
    
    
# execute main only if called as a script
if __name__ == "__main__":
    main()

