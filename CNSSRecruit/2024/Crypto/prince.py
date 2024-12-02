from Crypto.Util.number import *

c = 94933879657019461326828225836780893807400776971235851915066913763683310991309173340557406241075423730347734496950200533575670368627940332981373490699790129749566410150515572724861054835984481560010703671000134856172771048226985683127931612726872883032424421652451138053080169329061035399029500996664744339122
p = 95855494001984957858370499068727677198914989191424438110665096413160144326163172754989614826773164540454657124564339977787908884977761972381683644262327181870316948741995100389232827854834171961842471759416662384703036141181130961351694018591639607368956764660290603455362026824834672239118472771981866952759
e = 65537

d = pow(e, -1, p - 1)
print(long_to_bytes(pow(c, d, p)).decode())
