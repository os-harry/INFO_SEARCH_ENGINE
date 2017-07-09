# coding=utf-8
import re
import urllib
import urllib2
import os
import thulac
count = int(1)
url_queue = []
url_hash =[]
url_hash_num =[]

thu = thulac.thulac(seg_only=True)

def lac_text():
	global thu
	thu.cut_f("titx.txt", "lac.txt")

def get_titx( html ):
	title_list=re.findall(r'<title>(.*)</title>', html, re.I)
	file = open('titx.txt','w')
	if len(title_list):
		tt=str(title_list[0])+'###'+'\n'
		file.write(tt)
	else :
		return

	if html.find('class="content">')==-1 and html.find('<div class="essay_body">')==-1:
		body = None
		return
	elif html.find('<div class="essay_body">') != -1 :
		st_p=html.find('<div class="essay_body">')
		en_p=html.find('/div',st_p) 
		body='\n'+html[st_p+len('<div class="essay_body">'):en_p-1]+'\n'
	elif html.find('class="content">') !=-1 :
		st_p = html.find('class="content">')
		en_p = html.find('<div id="footer">')
		body='\n'+html[st_p+len('class="content">'):en_p-1]+'\n'
	
	while not(body.find('<')==-1):
		st_p=body.find('<')
		en_p=body.find('>',st_p)
		body1 = body[st_p : en_p + 1]
		body = body.replace(body1, '')
	
	p=re.compile('\s+')
	body = re.sub(p,'',body)
	
	body = body +'\n'

	file.write(body)

	file.close();
	
	lac_text()


def get_html(url,url_count):
	global count
	global url_queue
	global url_hash
	print 'Getting>>>',url,url_count
	try : 	
		content = urllib2.urlopen(url).read()
	except urllib2.URLError as e :
		print 'DOWNLOAD ERROR' ,e.reason
		content = None
		return  
		 
	website_before = os.path.abspath('.') 
	website_filepath = website_before+'/'+str(url_count)
	if not (os.path.exists(website_filepath)) :
		os.mkdir(website_filepath)
	os.chdir(website_filepath)
	# 写一个 u_to_k // URL to key number
	u_to_k =open("u_to_k.txt",'w') 
	url_to_key = url + '     ' + str(url_count) + '\n'
	u_to_k.write(url_to_key)
	u_to_k.close()
	# 爬取 .html
	wfile = open('content.html','wb')
	url_to_key = url + '     ' + str(url_count) + '\n'
	wfile.write(url_to_key)
	wfile.write(content)
	wfile.close()
	#爬取 link.txt
	fp = open('link.txt','wb')
	urls = re.findall(r"<a.*?href=.*?<\/a>", content, re.I)
	for url in urls:
		fp.write(url+'\n')
	
	link_list = re.findall(r"(?<=href=\").+?(?=\")|(?<=href=\').+?(?=\')", content)
	for url in link_list:
		if url[:7]!='http://' :
			url = 'http://info.ruc.edu.cn/'+url 				
		fp.write(url+'\n')
		
		if  (not url in (url_hash))  and ( not url.find('info.ruc.edu.cn') == -1)  and ( url.find('.css')== -1 ) and ( url.find('.doc')== -1 ) and ( url.find('.xls')== -1 ) and ( url.find('/mailto')== -1 ) :
			count +=1
			url_hash.append(url)
			url_hash_num.append(count)
			url_queue.append([url,count])

			
	fp.close()

	get_titx(content)

	os.chdir(website_before)


def main()
	url = "http://info.ruc.edu.cn/"
	url_queue.append([url,count])
	url_hash.append([url,count])

	gfile =open('general.txt','w')

	while not( url_queue == [] ) :
		st = url_queue[0][0]+' '+str(url_queue[0][1])
		gfile.write(st+'\n')
		get_html( url_queue[0][0],url_queue[0][1] )
		url_queue.pop(0)

	gfile.close()

	print 'DONE'
main()

