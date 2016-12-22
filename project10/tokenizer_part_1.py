#by hongfz
f= open ('Main.jack','r')
f1=open ('Maintemp.jack','w')
import re
def not_empty(s):
	if s==' ': return False
	if s=='': return False
	if s=='\t': return False
	if s=='\n': return False
	return True
a=f.read()
z=re.compile(r'\"')
b=z.split(a)
i=0
while i<=len(b)-1:
	p = re.compile(r'([\.\(\)\;\,\[\]\s])')
	c = p.split(b[i])
	d=list(filter(not_empty,c))
	for j in range(len(d)):
		#d[j]=d[j].rstrip('\n')
		f1.write (d[j])
		f1.write ('\n')
	if i<len(b)-1:
		f1.write('<stringConstant> ')
		f1.write (b[i+1])
		f1.write ('</stringConstant>')
		f1.write ('\n')
	i=i+2
f.close()
f1.close()
