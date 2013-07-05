import sys
import json
File = open(sys.argv[1],'r')
FileData = File.read()
obj = json.loads(FileData)
FileData = json.dumps(obj,separators=(',',':'))
File.close()

FileData =FileData.replace("\\","\\\\")
FileData = FileData.replace("\n","\\n")
FileData = FileData.replace('"','\\"')
FileData= FileData.replace("\t",r"\t") 
f = open(sys.argv[1] + ".h" ,"w")
f.write(FileData)
f.close