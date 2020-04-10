import hashlib
import argparse

parser = argparse.ArgumentParser()
parser.add_argument('filename')
args = parser.parse_args()

filename = args.filename
BLOCK_SIZE = 1024*1024*16

file_hash = hashlib.sha512()
with open(filename, 'rb') as f:
    fb = f.read(BLOCK_SIZE)
    while len(fb) > 0:
        file_hash.update(fb)
        fb = f.read(BLOCK_SIZE)

# print('SHA-512 of {}:'.format(filename))
print (file_hash.hexdigest())
