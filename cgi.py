#E:\Python\python.exe
# -*- coding: UTF-8 -*-

import os
import cgi
import cgitb
import urllib
import codecs
import time
import sys

reload(sys)
sys.setdefaultencoding('utf-8')
#print "Content-type:text/html"
#print                               
form = cgi.FieldStorage()
content = form["txt"].value
#print  content.encode('gbk')
os.chdir('E:\Apache2\htdocs')

file=codecs.open('temp1.in','w','utf-8')
#file=codecs.open('temp1.in','w') #1#可以写入文件
#file.write('helloworld')
#1#file.write(content.encode('gbk')) #可以写入.txt
#2#file.write(content.decode('gbk').encode('utf-8'))#尝试1
file.write(content.encode('utf-8'))#尝试2

#file.write('helloworld')
file.close()

time.sleep(0.4)
os.remove('temp1.in')

print "Location:../test.html\n\n"
#text = form.getvalue('txt')

#file.close()
#print text
