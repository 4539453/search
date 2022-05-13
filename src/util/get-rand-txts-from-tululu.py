import os
import random
from bs4 import BeautifulSoup
from urllib.request import Request, urlopen
import urllib.error
import shutil
import time

path="./resources/txts"
indexFile="index.txt"
BASEURL="https://tululu.org"

hdr = {'User-Agent': 'Mozilla/5.0 (X11; Linux x86_64) AppleWebKit/537.11 (KHTML, like Gecko) Chrome/23.0.1271.64 Safari/537.11',
       'Accept': 'text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8',
       'Accept-Charset': 'ISO-8859-1,utf-8;q=0.7,*;q=0.3',
       'Accept-Encoding': 'none',
       'Accept-Language': 'en-US,en;q=0.8',
       'Connection': 'keep-alive'}

def getUrl(path):
  print('path - {0}'.format(path))
  try:
    req = Request(path, headers=hdr)
    resource = urlopen(req, timeout=10)
  except urllib.error.HTTPError:
    return 404, None
  try:
    charset = resource.headers.get_content_charset()
    data = resource.read().decode(charset)
  except UnicodeDecodeError:
    return 404, None
  return 200, data

def getUrlFile(path, fileName):
  print('path - {0}'.format(path))
  try:
    req = Request(path, headers=hdr)
    with urlopen(req) as response, \
            open(fileName, 'wb') as outFile:
      shutil.copyfileobj(response, outFile)
  except urllib.error.HTTPError:
    return 404
  return 200

try:
  os.makedirs(path)
except OSError:
  if not os.path.isdir(path):
    raise

filecount = 0
while filecount < 5:

  random.seed()
  fileId = str(random.randint(1, 10000))

  if os.path.isfile(os.path.join(path, fileId + '.txt')) :
    continue 

  code, data = getUrl(BASEURL + "/b" + fileId)
  if not code == 200:
    continue
  
  soup = BeautifulSoup(data, 'html.parser')
  bookNameAuthor = soup.find(id="content").h1.get_text().split(' \xa0 :: \xa0 ')
  bookName = bookNameAuthor[0]
  author = bookNameAuthor[1]
  print('book - {0}, author - {1}'.format(bookName, author))
  

  code1 = getUrlFile(
    BASEURL + "/txt.php?id=" + fileId,
    path + '/' + fileId + '.txt'
  )
  if code1 != 200:
    continue

  with open(path + '/' + indexFile, 'a') as index_file:
    print('{0},{1},{2},{3}'.format(fileId, fileId+".txt", bookName, author
      ), file=index_file)

  filecount += 1
  time.sleep(1)

