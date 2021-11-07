from sage.all import *
from hashlib import md5

num = 42884020547169390364057708512857160494285905714049130207174574321294001570717794624065180823944268300615872241601579039570417514768021539120794827687319577302185669966605784385135475359835440522138098740956869698753641542827169807498060060203204623056652296548672193678604201527271552258183411014527366217548194668469156210293296924920396661175084847772705813725399053734267798263155285086152337660486536186646844672457165552673635686438518233777750910982014487846162409685706645584022613739678475494110418588076015804320630926293482802728176941310074063709832881421592093809601385355979927053037564815022569532301725889642648753691270079271760325794402609541247330395378653665694056501747438163292250560881807911461231726101015329450977148586716650828721964825603783645451441758913032780302842678209454303821607654073090650401139540242325808963472494771631432989047762098809264580664019379523293624441137658106554812934798531301113822034790852090529061101693937747989599304386879458074169786212163676139153571980665024887827190167719665028793495590181448050849517686984259984456749798664352548534304800162670309538117876068852938462001997080070145586746296815514664296506732662997084432462415745714170644890474456380187175650685331337577272850596655499330349676234958852437039128355237654047269

flag = md5(str(euler_phi(num)).encode()).hexdigest()
print('Flag is cnss{' + flag + '}')

'''
726469 5
14429917 10
3488777 6
1248059 6
7324349 9
13943177 6
117077309 5
40264613 10
4003333 7
1291513693 10
925020799 9
416211353 9
6945055903 8
42273263297 5
4297172359 7
14980192757 6
34448261957 9
31896490931 8
334972370143 6
409576292549 8
'''
