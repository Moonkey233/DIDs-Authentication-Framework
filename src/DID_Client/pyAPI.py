# from weidentityService import weidentityService
# from weidentityClient import weidentityClient
# import random
#
# URL = "https://did.moonkey.top:6001"
# # WeIdentity RestService URL

# weid = weidentityService(URL)
create_weid = weid.create_weidentity_did()
# print(create_weid)

# weid = weidentityClient(URL)
# privKey = "0xc4a116fb87ae9b8b87842b0f46e1bbf71c37fdae1104fd6d3fd2041e23c8c68e"
# nonce = str(random.randint(1, 999999999999999999999999999999))
# create_weid = weid.create_weidentity_did(privKey, nonce)
# print(create_weid)
