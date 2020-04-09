# ITPower Project

#Weather Band

#subject: data conversion


Since we are using LoRa to transfer data from the weather station to database, we wanted to reduce the size of the data.


This repo specifically deal with reducing size of rain data, but retaining the resolution down to half a second.


The idea is to convert the frequency of rain data being measured(every 0.01") into binary, so the resolution of the data is retained with minimum size required.


To achieve this, the time stamp when rain is measured is converted into binary every 0.5 second. This resulted 30 bits of data every 15 second, since there are 32 bits in int, i throw in 2 bit of time stamp.


With this method, very minute will resulted 4*32 bit(16 byte) of data.


Time stamp of date and hours are not included since the rain data will be send with other data in the weather station.
