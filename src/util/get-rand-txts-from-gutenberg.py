import os
import random
import urllib.request
import urllib.error

path="./txts"
indexFile="index.txt"
GUTENBERG="http://www.gutenberg.org"
fileExt1 = ".txt.utf-8" 
fileExt2 = "-0.txt"

def getUrl(path):
    print('path - {0}'.format(path))
    try:
        res=urllib.request.urlopen(path)
    except urllib.error.HTTPError:
        return 404, None
    try:
        data = res.read().decode('utf-8')
    except UnicodeDecodeError:
        return 404, None
    return 200, data

try:
    os.makedirs(path)
except OSError:
    if not os.path.isdir(path):
        raise

filecount = 0
while filecount < 100:

    random.seed()
    fileId = str(random.randint(1, 10000))

    if os.path.isfile(os.path.join(path, fileId + '.txt')) :
        continue 

    code3, data3 = getUrl(GUTENBERG + "/ebooks/" + fileId)
    if not code3 == 200:
        continue
    bookAndAuthor = data3.split('<h1 itemprop=\"name\">',1)[1].split("</h1",1)[0]
    bookName = bookAndAuthor.split(" by ", 1)[0]
    author = bookAndAuthor.split(" by ", 1)[1]
    print('book - {0}, author - {1}'.format(bookName, author))
    
    code1, data1 = getUrl(GUTENBERG + "/ebooks/" + fileId + fileExt1)
    if code1 != 200:
        code2, data2 = getUrl(GUTENBERG + "/files/" + fileId + "/" + fileId + fileExt2)
        if code2 != 200:
            continue
        else:
            with open(path + '/' + fileId + '.txt', 'w') as text_file:
                print(data2, file=text_file)
    else:
        with open(path + '/' + fileId + '.txt', 'w') as text_file:
            print(data1, file=text_file)

    with open(path + '/' + indexFile, 'a') as index_file:
        print('{0},{1},{2},{3}'.format(fileId, fileId+".txt", bookName, author
            ), file=index_file)

    filecount += 1
