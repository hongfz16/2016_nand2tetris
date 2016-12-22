import re
fkeyword=open('keyword','r')
keyword = set()
for line in fkeyword.readlines():
	keyword.add(line.rstrip('\n'))
fkeyword.close()
fsymbol=open('symbol','r')
symbol = set()
for line in fsymbol.readlines():
	symbol.add(line.rstrip('\n'))
fsymbol.close()
f=open('Maintemp.jack','r')
fout=open('MainT_my.jack','w')
for line in f.readlines():
	line=line.rstrip('\n')
	if line in keyword:
		fout.write('<keyword> ')
		fout.write(line.rstrip('\n'))
		fout.write(' </keyword>\n')
	elif line in symbol:
		if line=='<':
			linetemp='&lt;'
		elif line=='>':
			linetemp='&gt;'
		elif line=='&':
			linetemp='&amp;'
		else:
			linetemp=line
		fout.write('<symbol> ')
		fout.write(linetemp.rstrip('\n'))
		fout.write(' </symbol>\n')
	elif line.isdigit():
		fout.write('<integerConstant> ')
		fout.write(line.rstrip('\n'))
		fout.write(' </integerConstant>\n')
	elif re.match(r'\<\w+\>',line):
		fout.write(line)
		fout.write('\n')
	else:
		fout.write('<identifier> ')
		fout.write(line.rstrip('\n'))
		fout.write(' </identifier>\n')
f.close()
fout.close()
