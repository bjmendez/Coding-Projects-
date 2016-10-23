import pandas as pd
import numpy as np
import matplotlib


matplotlib.use("Agg")
import matplotlib.pyplot as plt
import math
import random
import os
# path: the path/destination folder to check if it exists. If it does not exist, create it.
def make_sure_path_exists(path):
    try:
        os.makedirs(path)
    except OSError:
        if not os.path.isdir(path):
            raise
##########Used for time window of spectrogram###################
HOUR = 1.0
MINUTE = HOUR/60.0
SECOND = MINUTE/60.0
################################################################


##########Vars to allow for computer to see which columns have certain info##### EXCEL COLUMNS ARE 0 BASED##########
SKIP = [0, 1, 7, 3, 4, 5, 6,8,9,10,11,12,13,14] #used for determining unused columns (such as moods)

FOLDER = "Spectrograms"


train = ['training1004.csv', 'training1005.csv', 'training1007.csv', 'training1008.csv', 'training1019.csv','training1020.csv']
val = ['validation1004.csv','validation1005.csv','validation1007.csv','validation1008.csv','validation1019.csv','validation1020.csv']
test = ['test1004.csv','test1005.csv','test1007.csv','test1008.csv','test1019.csv','test1020.csv']

dataset = val + test + train


def createSpectrograms(DATASET, DATASETFILEPATH, NFFT=50, Fs = 0.2, NOVERLAP = 49,  WINDOWLEN = 15, GRAYSCALE = False, TIMECOL = 1, DATECOL = 0, DRINKCOL = 7, SKIP = SKIP, Folder = "Spectrograms"):
    namingVar = 0
    numDatapoints = 0
    spectrogramMade = 0
    df = pd.read_csv(DATASETFILEPATH + dataset[0] ) #turn excel/csv file into a dataframe (large pandas table)
    headers = list(df.columns.values) #list of headers
    for j in headers:

        if(df.columns.get_loc(j) not in SKIP):
            print j
            numSpecgrams = 0
            spectrogramMade = 0
            for i in DATASET:
                print i
                df = pd.read_csv("resample first/" + i)
                dfDrinkPts = df[df[headers[DRINKCOL]] == 1] #dataframe of all the instances of drinking
                for row in xrange(len(dfDrinkPts) -1, -1, -1):
                    tempdf = df[df[headers[DATECOL]] == dfDrinkPts.iloc[row][DATECOL]]
                    tempdf = tempdf[tempdf[headers[TIMECOL]] <= (dfDrinkPts.iloc[row][TIMECOL] + WINDOWLEN * MINUTE)]
                    tempdf = tempdf[tempdf[headers[TIMECOL]] >= (dfDrinkPts.iloc[row][TIMECOL] - WINDOWLEN * MINUTE)]
                    PAD_TO = int(pow(2, math.log(len(tempdf[j]), 2))) #calculate the Pad_to for NFFT
                    #PAD_TO = 256
                    if(numDatapoints < len(tempdf[j])):  # set numDatapoints, used later in finding non-drink spectrograms
                        numDatapoints = len(tempdf[j])
                    print numDatapoints
                    filename = (FOLDER + "/" + str(j)) + "/drink/" + str(spectrogramMade)    #cmap=plt.cm.binary,
                    plt.plot(tempdf["time"], tempdf[j])
                    make_sure_path_exists(FOLDER + "/" + str(j) + "/drink")
                    plt.xlabel("Time (6 Min)")
                    plt.ylabel("Heart Rate (BPM)")
                    plt.title("Drink Heart Rate")
                    plt.savefig(filename + "GRAPH.jpg")
                    plt.cla()
                    Pxx, freqs, bins, im = plt.specgram(tempdf[j], NFFT=NFFT, Fs=Fs, noverlap=NOVERLAP, pad_to=PAD_TO)
                    if GRAYSCALE:
                        plt.set_cmap("Greys_r")
                    plt.xlabel("Time (s)")
                    plt.colorbar().set_label("Intensity [dB]")
                    plt.ylabel("Frequency (Hz)")
                    plt.title("Drink Heart Rate Spectrogram")
                    plt.savefig(filename + ".jpg")
                    tempdf.to_csv(filename + ".txt", sep='\t')
                    plt.cla()
                    spectrogramMade = spectrogramMade + 1
                    index = dfDrinkPts[dfDrinkPts[headers[TIMECOL]] == dfDrinkPts.iloc[row][TIMECOL]].index
                    index = index[0]
                    df = df.drop(df.index[[range(int(index) - (numDatapoints - 1) / 2, int(index) + (numDatapoints - 1) / 2)]])


                random.seed()
                numIter = -1
                while spectrogramMade != numSpecgrams:
                    numIter = numIter + 1

                    randDate = df.drop_duplicates(subset=[df.columns.values[DATECOL]])
                    randomRow = randDate.sample(n=1)
                    randomDate = randomRow.iloc[0, 0]
                    time = df.sample(n=1).iloc[0, 1]

                    NoDrinkDf = df[df[headers[DATECOL]] == randomDate]
                    NoDrinkDf = NoDrinkDf[NoDrinkDf[headers[TIMECOL]] <= (time + WINDOWLEN*MINUTE)]
                    NoDrinkDf = NoDrinkDf[NoDrinkDf[headers[TIMECOL]] >= (time - WINDOWLEN*MINUTE)]
                    testfordrinkDF = NoDrinkDf[NoDrinkDf[headers[DRINKCOL]] == 1]
                    NoDrinkDf = NoDrinkDf[np.isfinite(NoDrinkDf[j])]

                    #print str(len(NoDrinkDf)) + ":" + str(numDatapoints) + "-" + str(numIter/5)
                    if len(testfordrinkDF) == 0 and len(NoDrinkDf) >= numDatapoints-numIter/5:
                        numIter = 0
                        PAD_TO = int(pow(2, math.log(len(NoDrinkDf[j]), 2)))  # calculate the Pad_to for NFFT
                        Pxx, freqs, bins, im = plt.specgram((NoDrinkDf[j]), NFFT=NFFT, pad_to=PAD_TO, noverlap=NOVERLAP, Fs=Fs)  # generate spectrogram
                        if GRAYSCALE:
                            plt.set_cmap("Greys_r")
                        plt.xlabel("Time (s)")
                        plt.ylabel("Frequency (Hz)")
                        plt.colorbar().set_label("Intensity [dB]")
                        plt.title("No-Drink Heart Rate Spectrogram")
                        filename = FOLDER + "/" + str(j) + "/no-drink/" + str(numSpecgrams)

                        make_sure_path_exists(FOLDER + "/" + str(j) + "/no-drink/")
                        plt.savefig(filename + ".jpg")
                        plt.cla()
                        plt.plot(NoDrinkDf["time"],NoDrinkDf[j])
                        plt.xlabel("Time (6 Min)")
                        plt.ylabel("Heart Rate (BPM)")
                        plt.title("No-Drink Heart Rate")
                        plt.savefig(filename + "GRAPH.jpg")
                        plt.cla()
                        NoDrinkDf.to_csv(filename + ".txt", sep='\t')
                        numSpecgrams = numSpecgrams + 1




    test = spectrogramMade / 5
    train = spectrogramMade - test
    for j in headers:
        if tempdf.columns.get_loc(j) not in SKIP:
            import os
            script_path = os.path.abspath(__file__)  # i.e. /path/to/dir/foobar.py
            script_dir = os.path.split(script_path)[0]  # i.e. /path/to/dir/
            rel_path = FOLDER + "/" + str(j) + "/train.txt"
            abs_file_path = os.path.join(script_dir, rel_path)
            drinktrainfile = open(abs_file_path, "w")
            rel_path = FOLDER + "/" + str(j) + "/val.txt"
            abs_file_path = os.path.join(script_dir, rel_path)

            drinktestfile = open(abs_file_path, "w")

            for i in range(0, test + train):
                 if i >= test:
                     drinktrainfile.write(FOLDER + "/" + str(j) + "/drink/" + str(i) + ".jpg 1\n")
                     drinktrainfile.write(FOLDER + "/" + str(j) + "/no-drink/" + str(i) + ".jpg 0\n" )

                 else:
                     drinktestfile.write(FOLDER + "/" + str(j) + "/drink/" + str(i) + ".jpg 1\n")
                     drinktestfile.write(FOLDER + "/" + str(j) + "/no-drink/" + str(i) + ".jpg 0\n")
            drinktrainfile.close()
            drinktestfile.close()

createSpectrograms(DATASET=dataset, DATASETFILEPATH="resample first/", GRAYSCALE = False, WINDOWLEN = 15)
print "DEEP LEARNING BEGIN"
execfile("CNNALEXNET.py")