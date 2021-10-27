import os

now_path = os.getcwd()

# get all files' and folders' names in the current directory
filenames= os.listdir (".")

folders_name = []
for filename in filenames:
    # check whether the current object is a folder or not
    if os.path.isdir(os.path.join(os.path.abspath("."), filename)):
        folders_name.append(filename)


for folder in folders_name:
    for i in range(0, 30, 1):
        path = now_path + "\\" + folder + "\\" + str(i) + "\\"
        try:
            os.remove(path + "population.txt")
        except:
            print("無此檔案")