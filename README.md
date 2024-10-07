Use Cmake to build the file. If you get the error "[ERROR]: Could not open file. Check file name/directory" you might have to change the path
in the FT.loadFile("$PATH") function.

The data files are public domain books that have been slightly edited to remove unnecessary characters and especially "\n". Custom data files can
be imported but you need to remove all the "\n" in the txt file for the program to work properly. This can be achieved by using any modern
text editor (like VSCode) and just doing a search and replace of "\n" with " ".

Using the larger txt files such as pg4200.txt may lead to long loading times. The file is over 1.2 million words in length and contains several ten 
thousand unique words. Thus it might take a while to do all the operations to get the text prediction ready.