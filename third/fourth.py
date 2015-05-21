import sys
import third
def Error ():
	print "Incorrect input"
	print "Input format: Filename1 Operation(+,-,/,%,m) Filename2 Result"
	print "or"
	print "Filename1 ^ Filename2 Modul Result"
	print "Add -b if files are binary"
	exit()

if len(sys.argv) < 5 or len(sys.argv)>7:
	Error()


a = third.BIGNUMBER()
b = third.BIGNUMBER()


name_a = sys.argv[1]

operation = sys.argv[2]
name_b = sys.argv[3]


if operation=="^":
	mod = third.BIGNUMBER()
	name_mod = sys.argv[4]
	if len(sys.argv) > 5 and sys.argv[5]!="-b":
		name_res = sys.argv[5]
		
	else:
		Error()
else:
	name_mod = 0
	name_res = sys.argv[4]

if sys.argv[-1] == "-b":
	a.ReadBin(name_a)
	b.ReadBin(name_b)
	if name_mod!=0:
		mod.ReadBin(name_mod)
else:

	a.ReadText(name_a)
	b.ReadText(name_b)
	if name_mod!=0:
		mod.ReadText(name_mod)	
	
if operation == "+":
	res = a + b
if operation == "-":
	res = a - b
if operation == "m":
	res = a * b
if operation == "/":
	res = a / b
if operation == "%":
	res = a % b
if operation == "^":
	res = a.PowMod(b,mod)

if sys.argv[-1] == "-b":
	res.WriteBin(name_res)
else:
	res.WriteText(name_res)


