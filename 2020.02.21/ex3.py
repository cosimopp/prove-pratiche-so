import os
import sys

#per ogni estensione
dict 

for walkingDirPath, subDirs, files in os.walk("."): #for name in files:, for name in subDirs: lista tutti i file/tutte le cartelle con loro path
	for fileName in files:
		fullPath = os.path.join(walkingDirPath, fileName) #path completa