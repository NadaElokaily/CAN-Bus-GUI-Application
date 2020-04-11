import xml.etree.ElementTree as ET
import os.path

errorFileFlag = True
ecuName="none"
ecuProperties={}

#get the right file path and check if it has .xml in the end, if not add it
while(errorFileFlag):
    
    fileName = input("XML File Name is: ")
    if fileName[-4:] != ".xml":
        fileName = fileName +".xml"
    if os.path.isfile(fileName):        
        errorFileFlag = False
    else:
        errorFileFlag = True
        print("File not accessible") 

#parse the XML File and return a tree
ecuTree = ET.parse(fileName)
#loop over the ECU Nodes
for fatherNode in ecuTree.iter():
    if fatherNode.tag == "ECU":
        ecuName = "none"
        ecuProperties={}
        #loop over the Properties Nodes and store them in a dictionary
        for childNode in fatherNode:       
            if childNode.tag == "Name" :
                ecuName = childNode.text
            ecuProperties[childNode.tag] =childNode.text
        #check that the Name Node exists
        if ecuName != "none":
            outputFile = open(ecuName+".txt","w+")
            #write the properties pairs in the output file and cmd Line
            for prop in ecuProperties:
                print(prop+" : " +ecuProperties[prop])
                outputFile.write(prop+" : " +ecuProperties[prop]+",\n")
            outputFile.close()
        
'''
###########if the name node wasn't the first in the tags this wouldn't work#####################3
    for childNode in fatherNode:
        
        print("child",fatherNode.text)
        if fatherNode.tag == "ECU":
            for childNode in fatherNode:
                if childNode.tag == "Name" :
                    outputFile = open(childNode.text+".txt","w+")
                outputFile.write(childNode.tag +" : " +childNode.text+"\n")
            outputFile.close()
           
'''
