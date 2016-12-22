import re

finput=open('MainT_my.jack','r')
foutput=open('Main_my.xml','w')

words=[]

global count
count=0

global step
step=0

opset=set(['+','-','*', '/', '&amp;', '|','&lt;','&gt;','='])
statementset=set(['let','if','while','do','return'])
classVarDecset=set(['var','static','field'])
unaryOpset=set(['-','~'])

def print_current_line():
	global step
	global count
	printtab()
	#print(words[step])
	for i in range(3):
		foutput.write (words[step][i])
		foutput.write(' ')
		#print words[step][i],
		#print ' ',
	#print('\n')	
	foutput.write('\n')
	step+=1

def print_tri_line():
	global step
	global count
	for i in range(3):
		printtab()
	#	print(words[step])
		for j in range (3):
			foutput.write(words[step][j])
			foutput.write(' ')
			#print words[step][j],
			#print ' ',
		#print('\n')
		foutput.write('\n')
		step+=1

def isop(i):
	if words[i][1] in opset:
		return 1
	else:
		return 0

def isstatement(i):
	if words[i][1] in statementset:
		return 1
	else:
		return 0

def isclassVarDec(i):
	if words[i][1] in classVarDecset:
		return 1
	else:
		return 0

def isvarDec(i):
	if words[i][1] == 'var':
		return 1
	else :
		return 0

def isunaryOp(i):
	if words[i][1] in unaryOpset:
		return 1
	else:
		return 0

def statements():
	global step
	global count
	printtab()
	foutput.write('<statements>\n')
	count +=1
	#print(step)
	while (isstatement(step)):
		#print(step)
		if (words[step][1]=='let'): 
			letStatement() 
			#print('let')
		elif (words[step][1]=='if'): 
			ifStatement()
			#print('if')
		elif (words[step][1]=='do'): 
			doStatement()
			#print('do')
		elif (words[step][1]=='while'): 
			whileStatement()
			#print('while')
		elif (words[step][1]=='return'): 
			returnStatement()
			#print('return')
	count-=1
	printtab()
	foutput.write('</statements>\n')

def letStatement():
	global step
	global count
	printtab()
	foutput.write('<letStatement>\n')
	count+=1
	print_current_line()
	print_current_line()
	if (words[step][1]=='['):
		print_current_line()
		expression()
		print_current_line()
	print_current_line()
	expression()
	print_current_line()
	count-=1
	printtab()
	foutput.write('</letStatement>\n')

def ifStatement():
	global step
	global count
	printtab()
	foutput.write('<ifStatement>\n')
	count+=1
	print_current_line()
	print_current_line()
	expression()
	print_current_line()
	print_current_line()
	statements()
	print_current_line()
	if (words[step][1]=='else'):
		print_current_line()
		print_current_line()
		statements()
		print_current_line()
	count-=1
	printtab()
	foutput.write('</ifStatement>\n')

def whileStatement():
	global step
	global count
	printtab()
	foutput.write('<whileStatement>\n')
	count+=1
	print_current_line()
	print_current_line()
	expression()
	print_current_line()
	print_current_line()
	statements()
	print_current_line()
	count-=1
	printtab()
	foutput.write('</whileStatement>\n')

def doStatement():
	global step
	global count
	printtab()
	foutput.write('<doStatement>\n')
	count+=1
	print_current_line()
	subroutineCall()
	print_current_line()
	count-=1
	printtab()
	foutput.write('</doStatement>\n')

def returnStatement():
	global step
	global count
	printtab()
	foutput.write('<returnStatement>\n')
	count+=1
	print_current_line()
	if (words[step][1]!=';'):
		expression()
	print_current_line()
	count-=1
	printtab()
	foutput.write('</returnStatement>\n')

def term():
	global step
	global count
	printtab()
	foutput.write('<term>\n')
	count+=1
	#print(step)
	if (isunaryOp(step)):
		print_current_line()
		term()
	elif (words[step][1]=='('):
		print_current_line()
		expression()
		print_current_line()
	else:
		if(words[step+1][1]=='['):
			print_current_line()
			print_current_line()
			expression()
			print_current_line()
		elif(words[step+1][1]=='.' or words[step+1][1]=='('):
			#print('yeah')
			subroutineCall()
			
		else:
			print_current_line()
	count-=1
	printtab()
	foutput.write('</term>\n')

def expression():
	global step
	global count
	printtab()
	foutput.write('<expression>\n')
	count+=1
	term()
	while(isop(step)):
		print_current_line()
		term()
	count-=1
	printtab()
	foutput.write('</expression>\n')

def expressionList():
	global count
	global step
	printtab()
	foutput.write('<expressionList>\n')
	count+=1
	if(words[step][1]!=')'):
		expression()
		while(words[step][1]==','):
			print_current_line()
			expression()
	count-=1
	printtab()
	foutput.write('</expressionList>\n')

def subroutineBody():
	global step
	global count
	printtab()
	foutput.write('<subroutineBody>\n')
	count+=1
	print_current_line()
	while(words[step][1]!='}'):
		if isvarDec(step):
			varDec()
		else: statements()
	print_current_line()
	count-=1
	printtab()
	foutput.write('</subroutineBody>\n')

def varDec():
	global step
	global count
	printtab()
	foutput.write('<varDec>\n')
	count+=1
	print_tri_line()
	while (words[step][1]==','):
		print_current_line()
		print_current_line()
	print_current_line()
	count-=1
	printtab()
	foutput.write('</varDec>\n')

def parameterList():
	global step
	global count
	printtab()
	foutput.write('<parameterList>\n')
	count+=1
	if words[step][1]!=')':
		print_current_line()
		print_current_line()
		while (words[step][1]==','):
			print_tri_line()
	count-=1
	printtab()
	foutput.write('</parameterList>\n')

def classVarDec():
	global step
	global count
	printtab()
	foutput.write('<classVarDec>\n')
	count+=1
	print_tri_line()
	while (words[step][1]==','):
		print_current_line()
		print_current_line()
	print_current_line()
	count-=1
	printtab()
	foutput.write('</classVarDec>\n')

def subroutineDec():
	global step
	global count
	printtab()
	foutput.write('<subroutineDec>\n')
	count+=1
	print_tri_line()
	print_current_line()
	parameterList()
	print_current_line()
	subroutineBody()
	count-=1
	printtab()
	foutput.write('</subroutineDec>\n')

def subroutineCall():
	global step
	global count
	print_current_line()
	print_current_line()
	if(words[step+1][1]=='('):
		print_current_line()
		print_current_line()
		expressionList()
		print_current_line()
	else:
		print_current_line()
		print_current_line()
		expressionList()
		print_current_line()

def printtab():
	global step
	global count
	for i in range (count):
		foutput.write('  ')
		#print '  ',

def classdec():
	global count
	global step
	printtab()
	foutput.write('<class>\n')
	count=count+1
	for i in range(3):
		printtab()
		#print(words[step])
		for j in range (3):
			foutput.write(words[step][j])
			foutput.write(' ')
			#print words[step][j],
			#print ' ',
		#print('\n')
		foutput.write('\n')
		step=step+1
	while (words[step][1]!='}'):
		if isclassVarDec(step):
			classVarDec()
		else : subroutineDec()
	#count-=1
	printtab()
	#print(words[step])
	for i in range (3):
		foutput.write(words[step][i])
		foutput.write(' ')
		#print words[step][i],
		#print ' ',
	#print('\n')	
	foutput.write('\n')
	count-=1
	printtab()
	foutput.write('</class>\n')


for line in finput.readlines():
	word=re.split(r'\s+',line)
	words.append([word[0],word[1],word[2]])

classdec()
finput.close()
foutput.close()
