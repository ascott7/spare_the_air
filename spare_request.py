import urllib2

from HTMLParser import HTMLParser
class SpareHTMLParser(HTMLParser):
    def __init__(self):
        HTMLParser.__init__(self)
        self.done = False
    def handle_starttag(self, tag, attrs):
        #print "Encountered a start tag:", tag
        if not self.done:
            if tag == "div" and ('class', 'sta-day') in attrs:
                print "ALL CLEAR"
                self.done = True
            if tag == "div" and ('class', 'sta-day winteralert') in attrs:
                print "ALERT"
                self.done = True


response = urllib2.urlopen("http://www.sparetheair.org/").read()
parser = SpareHTMLParser()
parser.feed(response)
