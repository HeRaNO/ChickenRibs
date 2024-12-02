from Crypto.Util.number import *

n = 0x45307be9cab8f66dc8d9ef1d8ec145428157bc613a4fb954a3f5b3077697a1fee4b5a8de7a8aa20529c5a84f37583c374d8141efa7875f273932c7182eb2dd5645c77745f88af4e622b1bdc1526047a375d90aa7436148a0eb5f66463964bc0f4df1fca814e443ce6e880d9d36b0110ddf974b8c252108bdbabfb0dd6d149631
m = b"Please keep away from me, I had to study hard"
e = 65537
print(hex(pow(bytes_to_long(m), e, n)))
