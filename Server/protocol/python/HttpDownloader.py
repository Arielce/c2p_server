import urllib
import io
from sgmllib import SGMLParser
from urllib2 import Request

count = 0

class UrlList(SGMLParser):
    def reset(self):
        SGMLParser.reset(self)
        self.urls = []
        self.images = []

    def start_a(self, attrs):
        #print "start_a " + str(attrs)
        href = [v for k, v in attrs if k == 'href']
        #print href
        if href:
            self.urls.extend(href)
        self.getimages(attrs)

    def unknown_starttag(self, tag, attrs):
        if tag == 'img':
            self.getimages(attrs)

    def printUrls(self):
        for url in self.urls:
            print url

    def getUrls(self):
        return self.urls

    def getimages(self, attrs):
        #print str(attrs)
        img = [v for k, v in attrs if k=='src']
        if img:
            self.images.extend(img)

    def printImages(self):
        for img in self.images:
            print img

    def saveImages(self):
        global count
        try:
            for img in self.images:
                #print img
                self.sock = urllib.urlopen(img)
                jpg = self.sock.read()
                name = "%d.jpg" %count
                File = open('D:\\image\\' + name, "wb")
                File.write(jpg)
                File.close()
                count = count + 1
        except:
            print "except"

class UrlSet():
    def __init__(self):
        self.urlset = set([])

    def addUrl(self, url):
        self.urlset.add(url)

    def IsUrlExist(self, url):
        ret = url in self.urlset
        return ret


class ParseUrl():
    def __init__(self, indexUrl):
        self.indexUrl = indexUrl
        self.urlset = UrlSet()

    def GetUrls(self, url, layerlen=0):
        if layerlen > 3:
            return
        if self.urlset.IsUrlExist(url) == True:
            return
        else:
            self.urlset.addUrl(url)
        
        sock = urllib.urlopen(url)
        parser = UrlList()
        parser.feed(sock.read())
        sock.close()
        urls = parser.getUrls()
        for u in urls:
            preindex = './'
            if u.find(preindex) != -1:
                print "DELETE:" + u
                continue
            if u == "./" or u == "../" or u == ".":
                continue
            u = self.indexUrl + "/" + u
            if self.urlset.IsUrlExist(u) == False:
                print u
                parser.saveImages()
                self.GetUrls(u, layerlen+1)
                self.urlset.addUrl(u)

def test():
    indexUrl = "http://cl.man.lv"
    parser = ParseUrl(indexUrl)
    parser.GetUrls("http://cl.man.lv/thread0806.php?fid=2")
    
test()
