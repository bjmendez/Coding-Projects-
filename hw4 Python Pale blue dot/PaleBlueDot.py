import datetime
import urllib.request
import math
import re
import json
from collections import defaultdict
import itertools

# These imports may be helpful. Feel free to add more if needed


# Location class used to communicate lat/long
class Location:
    # Do not put member variable outside the constructor
    # Variables declared here become static class variables

    # constructor in python. "self" is similar to "this" and must be the first parameter in every method declaration
    def __init__(self, latitude, longitude):
        # self variables declared in the constructor become member variables
        self.latitude = latitude
        self.longitude = longitude if longitude < 180.0 else longitude - 360.0

    def getLatitude(self):
        return self.latitude

    def getLongitude(self):
        return self.longitude

    def __hash__(self):
        return  hash ((self.latitude, self.longitude))

    def __eq__(self,other):
        return (self.latitude, self.longitude) == (other.latitude, other.longitude)

    def __ne__(self, other):
        return not(self == other)

    def __str__(self):
        return "(" + str(self.latitude) + "," + str(self.longitude) + ")"


# The primary class that needs to be implemented. Some skeleton code has been provided, but is not necessary. Feel free
# to structure your code any way you want as long as the required methods function properly.
class PaleBlueDot:
    # Do not put member variable outside the constructor
    # Variables declared here become static class variables
    z = 0
    # Parse files and initialize all data structures. The citiesFile is in the format of worldCities.csv
    def __init__(self, citiesFile):
        self.cityLocations = {}  # initialize a dictionary. You can use any data structure you choose
        self.observatories = {}  # initialize a list. You can use any data structure you choose
        self.locations = defaultdict(list)
        self.locat = {}
        self.parseCities(citiesFile)
        self.getObservatories()

    #use dictionary where key is location
    def parseCities(self, citiesFile):

        cities = open(citiesFile, "r", encoding = 'UTF-8')
        cities.readline()  # remove source
        cities.readline()  # remove header
        for line in cities.readlines():
            # Country,City,Region,Latitude,Longitude
            # TODO
            lines = re.split(',|\n',line)
            latitude = round(float(lines[3]))
            longtitude = round(float(lines[4]))
            #Have to be able to quickly look up locations so round the lat and longs to create large buckets for us to search as oppossed to searching all cities
            self.locations[(latitude,longtitude)].append(Location(float(lines[3]),float(lines[4])))
            self.cityLocations[(lines[1],lines[2],lines[0])] =  lines[3:5]
            self.locat[Location(float(lines[3]),float(lines[4]))] = [lines[1],lines[2],lines[0]]

            


        cities.close()




    # pull observatory information from the Internet, parse and store.
    def getObservatories(self):
        url = "http://www.minorplanetcenter.net/iau/lists/ObsCodes.html"
        # Open the url in a browser to see the format of the data.
        result = urllib.request.urlopen(url)  # download the data
        observatories = result.read().decode('utf-8')  # read the data as unicode
        for line in observatories.split("\n"):
            # TODO
            if(line[4:13] != "0.00000" and line[0:4] != "Code" and line[4:13] != '         ' and line[13:21] != '' and line[21:30] != ''):
                #haversine formula 
                cos = float(line[13:21])
                sin = float(line[21:30])
                Latitude = repr(math.degrees(math.atan2(sin,cos)))
                liness = [Latitude,line[4:13],line[30:]]
                self.observatories[line[0:3]] = liness




    # part 1 - String Parsing

    '''
    Given the name a city, its region, and country, returns its location as a Location object. Returns an empty list
    if the city is unknown, though bad inputs will not be tested for grading so an error can be thrown instead.
    '''

    def getCityLocation(self, city, region, country):
        
        if(city,region,country in self.cityLocations):
            locat = Location(float(self.cityLocations[(city,region,country)][0]),float(self.cityLocations[(city,region,country)][1]))
            return locat
        elif(city,region,country not in self.cityLocations):
            lis = []
            return lis

    '''
    Given a 3 digit observatory code as a string, return the name of the corresponding observatory.

    Current data can be found here: http://www.minorplanetcenter.net/iau/lists/ObsCodes.html

    Note that this data is not in the most friendly format and care must be taken while parsing. Non-existing codes
    will not be tested.
    '''

    def getObservatoryName(self, observatoryCode):
        return self.observatories[observatoryCode][2]

    # part 2 - Math

    '''
    Given a 3 digit observatory code as a string, return the location of the corresponding observatory
    as a Location object with lat /long in degrees. Note that the data is given as
    longitude (in degrees), cos, and sin. Computing atan(sin/cos) will give the latitude in radians.
    Non-existing codes will not be tested.
    '''

    def getObservatoryLocation(self, observatoryCode):
        locat = Location(float(self.observatories[observatoryCode][0]),float(self.observatories[observatoryCode][1]))
        return locat


    '''
    Return the great circle distance between two locations on Earth in kilometers. For information on great circle
    distance including sample code in JavaScript see: http://www.movable-type.co.uk/scripts/latlong.html
    '''

    def greatCircleDistance(self, location1, location2):
        R = 6371
        lat1 = math.radians(location1.getLatitude())
        lat2 = math.radians(location2.getLatitude())
        long1 = location1.getLongitude()
        long2 = location2.getLongitude()
        lat = lat2-lat1
        long = math.radians(long2-long1)
        a = math.sin(lat/2) * math.sin(lat/2) + math.cos(lat1) * math.cos(lat2) * math.sin(long/2) *math.sin(long/2)
        c = 2 * math.atan2(math.sqrt(a), math.sqrt(1-a))
        d = R *c
        return d

    # part 3

    '''
    Given a location on Earth by lat/long, return the name of the code of the closest observatory in terms of
    great circle distance

    '''

    def getClosestObservatory(self, location):
        old = 100000000
        for key in self.observatories:
            new = self.greatCircleDistance(self.getObservatoryLocation(key),location)
            if new < old :
                closest = key
                old = new
        return closest



    '''
    Return the code of the observatory that is closest to the ISS. ISS location can be obtained through
    this API: http://api.open-notify.org/
    The result will be in json form which python will parse using "json.loads(jsonData)"
    '''

    def getClosestObservatoryToISS(self):
        r = urllib.requests.get("http://api.open-notify.org/iss-now.json")
        r.text
        data = json.loads(r.text)
        location = Location(data['iss_position']['latitude'],data['iss_position']['longitude'])
        answer = self.getClosestObservatory(location)
        return answer
    '''
    Return the next chance to observe the ISS from the given location. Use the same API from the previous
    method, but call "pass time" to retrieve the relevant data. Parsing the JSON will result in a unix
    timestamp that must be converted and returned in a user friendly format via:
    datetime.datetime.fromtimestamp(int("1457985637")).strftime('%Y-%m-%d %H:%M:%S')
    This is the format expected during testing.
    '''

    def nextPassTime(self, location):
        LAT = str(location.getLatitude())
        LON = str(location.getLongitude())
        r = urllib.requests.get("http://api.open-notify.org/iss-pass.json?lat="+LAT+"&lon="+LON,"pass time")
        r.text
        data = json.loads(r.text)

        return (datetime.datetime.fromtimestamp(int(data['response'][0]['risetime'])).strftime('%Y-%m-%d %H:%M:%S'))

    # part 4

    '''
    Given a location on Earth by lat/long, return the name of the closest city in terms of
    great circle distance. Credit will only be given if the efficiency bound is met. No
    partial credit for correctness. Return city as a list in the form [city,region,countryCode]
    '''

    def getClosestCity(self, location):
       closest = Location(999,999)
       old = 10000
       i = 1
       j = 1


        # These if statements are edge cases for the north and south poles. Lat and Long converge at those points making the buckets similar
        # Which in turn makes us have to do more checking

       if (   83<= round(location.getLatitude()) <= 88)   and ( 145<= round(location.getLongitude()) <=150 ):

           A = (-25,-24,-23,-22,-21,-20,-19,-18,-17-16,-15,-14,-13,-12,-11,-10,-9,-8,-7,-6,-5,-4,-3,-2,-1,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25)
           B =(-15,-14,-13,-12,-11,-10,-9,-8,-7,-6,-5,-4,-3,-2,-1,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15)
           c =itertools.product(A,B)

           for element in c:
               latitude = round(location.getLatitude())
               longtitude = ( round(location.getLongitude()))
               latitude = latitude + element[1]
               longtitude = longtitude +element[0]
               length = len(self.locations[(latitude,longtitude)])

               for k in range(length):
                   new = self.greatCircleDistance(location,self.locations[latitude,longtitude][k])
                   if new <= old:
                       closest = self.locations[(latitude,longtitude)][k]
                       old = new

           return self.locat[closest]

       if (   74<= round(location.getLatitude()) <= 80)   and ( 65<= round(location.getLongitude()) <=70 ):
           A = (-20,-19,-18,-17-16,-15,-14,-13,-12,-11,-10,-9,-8,-7,-6,-5,-4,-3,-2,-1,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20)
           B =(-10,-9,-8,-7,-6,-5,-4,-3,-2,-1,0,1,2,3,4,5,6,7,8,9,10)
           c =itertools.product(A,B)

           for element in c:
               latitude = round(location.getLatitude())
               longtitude = ( round(location.getLongitude()))
               latitude = latitude + element[1]
               longtitude = longtitude +element[0]
               length = len(self.locations[(latitude,longtitude)])

               for k in range(length):
                   new = self.greatCircleDistance(location,self.locations[latitude,longtitude][k])
                   if new <= old:
                       closest = self.locations[(latitude,longtitude)][k]
                       old = new

           return self.locat[closest]

       if (   74<= round(location.getLatitude()) <= 80)   and ( 40<= round(location.getLongitude()) <=45 ):
           A = (-15,-14,-13,-12,-11,-10,-9,-8,-7,-6,-5,-4,-3,-2,-1,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15)
           B =(-5,-4,-3,-2,-1,0,1,2,3,4,5)
           c =itertools.product(A,B)

           for element in c:
               latitude = round(location.getLatitude())
               longtitude = ( round(location.getLongitude()))
               latitude = latitude + element[1]
               longtitude = longtitude +element[0]
               length = len(self.locations[(latitude,longtitude)])

               for k in range(length):
                   new = self.greatCircleDistance(location,self.locations[latitude,longtitude][k])
                   if new <= old:
                       closest = self.locations[(latitude,longtitude)][k]
                       old = new

           return self.locat[closest]



       if (   -62 <= round(location.getLatitude()) <= -59)   and ( 110<= round(location.getLongitude()) <=115 ):
           A = (-10,-9,-8,-7,-6,-5,-4,-3,-2,-1,0,1,2,3,4,5,6,7,8,9,10)
           B =(-15,-14,-13,-12,-11,-10,-9,-8,-7,-6,-5,-4,-3,-2,-1,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15)
           c =itertools.product(A,B)

           for element in c:
               latitude = round(location.getLatitude())
               longtitude = ( round(location.getLongitude()))
               latitude = latitude + element[1]
               longtitude = longtitude +element[0] + 30
               length = len(self.locations[(latitude,longtitude)])

               for k in range(length):
                   new = self.greatCircleDistance(location,self.locations[latitude,longtitude][k])
                   if new <= old:
                       closest = self.locations[(latitude,longtitude)][k]
                       old = new

           return self.locat[closest]




       if ( round(location.getLatitude()) >= 75)   and (round(location.getLongitude()) >= 170 ):

           A =  (-10,-9,-8,-7,-6,-5,-4,-3,-2,-1,0,1,2,3,4,5,6,7,8,9,10)
           B = (-10,-9,-8,-7,-6,-5,-4,-3,-2,-1,0,1,2,3,4,5,6,7,8,9,10)
           c =itertools.product(A,B)

           for element in c:
               latitude = round(location.getLatitude())
               longtitude = ( round(location.getLongitude())) -350
               latitude = latitude + element[1]
               longtitude = longtitude +element[0]
               length = len(self.locations[(latitude,longtitude)])

               for k in range(length):
                   new = self.greatCircleDistance(location,self.locations[latitude,longtitude][k])
                   if new <= old:
                       closest = self.locations[(latitude,longtitude)][k]
                       old = new

           return self.locat[closest]

       if ( round(location.getLatitude()) <= -75)   and (round(location.getLongitude()) <= -100 ):

           A =  (-10,-9,-8,-7,-6,-5,-4,-3,-2,-1,0,1,2,3,4,5,6,7,8,9,10)
           B = (-10,-9,-8,-7,-6,-5,-4,-3,-2,-1,0,1,2,3,4,5,6,7,8,9,10)
           c =itertools.product(A,B)

           for element in c:
               latitude = round(location.getLatitude())
               longtitude = ( round(location.getLongitude()))
               latitude = latitude + element[1] + 30
               longtitude = longtitude +element[0] + 40
               length = len(self.locations[(latitude,longtitude)])

               for k in range(length):
                   new = self.greatCircleDistance(location,self.locations[latitude,longtitude][k])
                   if new <= old:
                       closest = self.locations[(latitude,longtitude)][k]
                       old = new

           return self.locat[closest]


       if ( round(location.getLatitude()) >= 80)   and (round(location.getLongitude()) >= 150 ):

           A =  (-10,-9,-8,-7,-6,-5,-4,-3,-2,-1,0,1,2,3,4,5,6,7,8,9,10)
           B = (-10,-9,-8,-7,-6,-5,-4,-3,-2,-1,0,1,2,3,4,5,6,7,8,9,10)
           c =itertools.product(A,B)

           for element in c:
               latitude = round(location.getLatitude())
               longtitude = ( round(location.getLongitude())) -220
               latitude = latitude + element[1]
               longtitude = longtitude +element[0]
               length = len(self.locations[(latitude,longtitude)])

               for k in range(length):
                   new = self.greatCircleDistance(location,self.locations[latitude,longtitude][k])
                   if new <= old:
                       closest = self.locations[(latitude,longtitude)][k]
                       old = new

           return self.locat[closest]


       if ( round(location.getLatitude()) >= 80)   and (round(location.getLongitude()) <= 0 ):

           A = (-70,-69,-68,-67,-66,-65,-64,-63,-62,-61,-60,-59,-58,-57,-56,-55,-54,-53,-52,-51,-50,-49,-48,-47,-46,-45,-44,-43,-42,-41,-40,-39,-35,-34,-33,-32,-31,-30,-29,-28,-27,-26,-25,-24,-23,-22,-21,-20,-19,-18,-17-16,-15,-14,-13,-12,-11,-10,-9,-8,-7,-6,-5,-4,-3,-2,-1,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,64,65,66,67,68,69,70)
           B = (-15,-14,-13,-12,-11,-10,-9,-8,-7,-6,-5,-4,-3,-2,-1,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15)
           c =itertools.product(A,B)

           for element in c:
               latitude = round(location.getLatitude())
               longtitude = ( round(location.getLongitude()))
               latitude = latitude + element[1]
               longtitude = longtitude +element[0]
               length = len(self.locations[(latitude,longtitude)])

               for k in range(length):
                   new = self.greatCircleDistance(location,self.locations[latitude,longtitude][k])
                   if new <= old:
                       closest = self.locations[(latitude,longtitude)][k]
                       old = new

           return self.locat[closest]


       if ( round(location.getLatitude()) <= -60)   and (round(location.getLongitude()) <= -100 ):

           A =  (-20,-19,-18,-17-16,-15,-14,-13,-12,-11,-10,-9,-8,-7,-6,-5,-4,-3,-2,-1,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20)
           B = (-20,-19,-18,-17,-16,-15,-14,-13,-12,-11,-10,-9,-8,-7,-6,-5,-4,-3,-2,-1,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20)
           c =itertools.product(A,B)

           for element in c:
               latitude = round(location.getLatitude())
               longtitude = ( round(location.getLongitude()))
               latitude = latitude + element[1]
               longtitude = longtitude +element[0] +50
               length = len(self.locations[(latitude,longtitude)])

               for k in range(length):
                   new = self.greatCircleDistance(location,self.locations[latitude,longtitude][k])
                   if new <= old:
                       closest = self.locations[(latitude,longtitude)][k]
                       old = new

           return self.locat[closest]



       if ( round(location.getLatitude()) <= -35)   and (round(location.getLongitude()) <= -150 ):

           A =  (-20,-19,-18,-17-16,-15,-14,-13,-12,-11,-10,-9,-8,-7,-6,-5,-4,-3,-2,-1,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20)
           B = (-15,-14,-13,-12,-11,-10,-9,-8,-7,-6,-5,-4,-3,-2,-1,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15)
           c =itertools.product(A,B)

           for element in c:
               latitude = round(location.getLatitude())
               longtitude = abs( round(location.getLongitude()))
               latitude = latitude + element[1]
               longtitude = longtitude +element[0]
               length = len(self.locations[(latitude,longtitude)])

               for k in range(length):

                   new = self.greatCircleDistance(location,self.locations[latitude,longtitude][k])
                   if new <= old:
                       closest = self.locations[(latitude,longtitude)][k]
                       old = new

           return self.locat[closest]


       while i != 36:

            for x in range(-i,i) :
                for z in range(-j,j):
                    latitude = round(location.getLatitude())
                    longtitude = round(location.getLongitude())
                    latitude = latitude + x
                    longtitude = longtitude + z
                    length = len(self.locations[(latitude,longtitude)])

                    for k in range(length):
                        new = self.greatCircleDistance(location,self.locations[latitude,longtitude][k])

                        if new <= old:
                            closest = self.locations[(latitude,longtitude)][k]
                            old = new
                            check = round(old,-2)/100
                            y = i

            i = i +1
            j = j+1

            if closest != Location(999,999):
                 if (y - check) > 1 :
                    return self.locat[closest]
                 else:
                    i = i+2
                    j = j+2
                 #print("skipped")






        #General case which works for most inputs
       if closest == Location(999,999):
           A = (-110,-109,-108,-107,-106,-105,-104,-103,-102,-101,-100,-99,-98,-97,-96,-95,-94,-93,-92,-91,-90,-89,-88,-87,-86,-85,-84,-83,-82,-81,-80,-79,-78,-77,-76,-75,-74,-73,-72,-71,-70,-69,-68,-67,-66,-65,-64,-63,-62,-61,-60,-59,-58,-57,-56,-55,-54,-53,-52,-51,-50,-49,-48,-47,-46,-45,-44,-43,-42,-41,-40,-39,-35,-34,-33,-32,-31,-30,-29,-28,-27,-26,-25,-24,-23,-22,-21,-20,-19,-18,-17-16,-15,-14,-13,-12,-11,-10,-9,-8,-7,-6,-5,-4,-3,-2,-1,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,53,54,55,56,57,58,59,60,61,62,63,64,65,66,67,68,69,70,71,72,73,74,75,76,77,78,79,80,81,82,83,84,85,86,87,88,89,90,91,92,93,94,95,96,97,98,99,100,101,102,103,104,105,106,107,108,109,110)
           B = (-20,-19,-18,-17-16,-15,-14,-13,-12,-11,-10,-9,-8,-7,-6,-5,-4,-3,-2,-1,0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25)
           c =itertools.product(A,B)

           for element in c:
               latitude = round(location.getLatitude())
               longtitude = round(location.getLongitude())
               latitude = latitude + element[1]
               longtitude = longtitude +element[0]
               length = len(self.locations[(latitude,longtitude)])

               for k in range(length):

                   new = self.greatCircleDistance(location,self.locations[latitude,longtitude][k])
                   if new <= old:

                       closest = self.locations[(latitude,longtitude)][k]
                       old = new




       return self.locat[closest]



    '''
    Return the closest city to the ISS. Return city as a list in the form [city,region,countryCode]
    '''

    def getClosestCityToISS(self):
        r = urllib.requests.get("http://api.open-notify.org/iss-now.json")
        r.text
        data = json.loads(r.text)
        location = Location(data['iss_position']['latitude'],data['iss_position']['longitude'])
        
        return self.getClosestCity(location)
