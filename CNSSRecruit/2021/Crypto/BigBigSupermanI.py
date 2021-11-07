from Crypto.Util.number import long_to_bytes

def fpow(a, b, n):
	r = 1
	while b != 0:
		if b & 1 == 1:
			r = r * a % n
		a = a * a % n
		b >>= 1
	return r

a = 10499958999037877045860819145654592139531258013786800315952660437695953206118177802362538707257147839843929607571065996701775308516344320494492623326535070933404552245238889019529867495706219558537483959855018656456767601472852530792072968424254995263689863458109858200434368660199825370006622972172615283000225895986795432100524830372657448639751748649746517567275491877758341825114165092719349624453145256163927226959292249202574111889453838454722039
n = 24482146465492008075985247474612414320648047425785643838292024343856484727961531014143038475016832753633643464040872815615028679515938203288641456487330618969964445990607887042678786725649115551121279019558561466028015891949399125083811735238746137986294864917479675168130071009961552443914582290960081092498541343026165888900247802180370535720495152921978143267961988522304615862013752399728187062523671938698800778472385717512452760615330027345844283
b = 13974352443151
i = b * fpow(a, n - 2, n) % n

flag = b'cnss{'+long_to_bytes(i)+b'}'
print(flag.decode())