#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <cassert>
#include <fstream>
#include <arpa/inet.h>

#define htonll(x) (((uint64_t)htonl((x) & 0xFFFFFFFF) << 32) | htonl((x) >> 32))
#define right_rotate(num, val) ((num >> val) | (num << (64 - val)))
#define append_word(word) (M[word_ptr++] = (ull)word)

typedef unsigned long long ull;

const unsigned long long h[8] = {0x6a09e667f3bcc908, 0xbb67ae8584caa73b, 0x3c6ef372fe94f82b, 0xa54ff53a5f1d36f1, 0x510e527fade682d1, 0x9b05688c2b3e6c1f, 0x1f83d9abfb41bd6b, 0x5be0cd19137e2179};

const unsigned long long k[80] = {0x428a2f98d728ae22, 0x7137449123ef65cd, 0xb5c0fbcfec4d3b2f, 0xe9b5dba58189dbbc, 0x3956c25bf348b538, 0x59f111f1b605d019, 0x923f82a4af194f9b, 0xab1c5ed5da6d8118, 0xd807aa98a3030242, 0x12835b0145706fbe, 0x243185be4ee4b28c, 0x550c7dc3d5ffb4e2, 0x72be5d74f27b896f, 0x80deb1fe3b1696b1, 0x9bdc06a725c71235, 0xc19bf174cf692694, 0xe49b69c19ef14ad2, 0xefbe4786384f25e3, 0x0fc19dc68b8cd5b5, 0x240ca1cc77ac9c65, 0x2de92c6f592b0275, 0x4a7484aa6ea6e483, 0x5cb0a9dcbd41fbd4, 0x76f988da831153b5, 0x983e5152ee66dfab, 0xa831c66d2db43210, 0xb00327c898fb213f, 0xbf597fc7beef0ee4, 0xc6e00bf33da88fc2, 0xd5a79147930aa725, 0x06ca6351e003826f, 0x142929670a0e6e70, 0x27b70a8546d22ffc, 0x2e1b21385c26c926, 0x4d2c6dfc5ac42aed, 0x53380d139d95b3df, 0x650a73548baf63de, 0x766a0abb3c77b2a8, 0x81c2c92e47edaee6, 0x92722c851482353b, 0xa2bfe8a14cf10364, 0xa81a664bbc423001, 0xc24b8b70d0f89791, 0xc76c51a30654be30, 0xd192e819d6ef5218, 0xd69906245565a910, 0xf40e35855771202a, 0x106aa07032bbd1b8, 0x19a4c116b8d2d0c8, 0x1e376c085141ab53, 0x2748774cdf8eeb99, 0x34b0bcb5e19b48a8, 0x391c0cb3c5c95a63, 0x4ed8aa4ae3418acb, 0x5b9cca4f7763e373, 0x682e6ff3d6b2b8a3, 0x748f82ee5defb2fc, 0x78a5636f43172f60, 0x84c87814a1f0ab72, 0x8cc702081a6439ec, 0x90befffa23631e28, 0xa4506cebde82bde9, 0xbef9a3f7b2c67915, 0xc67178f2e372532b, 0xca273eceea26619c, 0xd186b8c721c0c207, 0xeada7dd6cde0eb1e, 0xf57d4f7fee6ed178, 0x06f067aa72176fba, 0x0a637dc5a2c898a6, 0x113f9804bef90dae, 0x1b710b35131c471b, 0x28db77f523047d84, 0x32caab7b40c72493, 0x3c9ebe0a15c9bebc, 0x431d67c49c100d4c, 0x4cc5d4becb3e42b6, 0x597f299cfc657e2a, 0x5fcb6fab3ad6faec, 0x6c44198c4a475817};

ull *H;
ull *M;
int word_ptr, byte_ptr, bit_ptr;
void append_byte(unsigned char byte) {
	// assert(bit_ptr == 0);
	M[word_ptr] &= ~((ull)0xFF << ((8-1 - byte_ptr)*8) );
	M[word_ptr] |= ((ull)byte << ((8-1 - byte_ptr)*8) );
	byte_ptr = byte_ptr + 1;
	word_ptr += byte_ptr / 8;
	byte_ptr = byte_ptr % 8;
}

ull w[80];
void get_hash(ull *M, ull *H) {
	for (int i = 0; i < 16; i++)
		w[i] = M[i];
	for (int i = 16; i < 80; i++) {
		w[i] = w[i-16]
			+ (right_rotate(w[i-15], 1) ^ right_rotate(w[i-15], 8) ^ (w[i-15] >> 7))
			+ w[i-7]
			+ (right_rotate(w[i-2], 19) ^ right_rotate(w[i-2], 61) ^ (w[i-2] >> 6));
	}
	
	ull w_a=H[0], w_b=H[1], w_c=H[2], w_d=H[3], w_e=H[4], w_f=H[5], w_g=H[6], w_h=H[7];

	for (int i = 0; i < 80; i++) {
		ull S1 = right_rotate(w_e, 14) ^ right_rotate(w_e, 18) ^ right_rotate(w_e, 41);
		ull ch = (w_e & w_f) ^ (~w_e & w_g);
		ull temp1 = w_h + S1 + ch + k[i] + w[i];
		ull S0 = right_rotate(w_a, 28) ^ right_rotate(w_a, 34) ^ right_rotate(w_a, 39);
		ull maj = (w_a & w_b) ^ (w_a & w_c) ^ (w_b & w_c);
		ull temp2 = S0 + maj;

		w_h = w_g;
		w_g = w_f;
		w_f = w_e;
		w_e = w_d + temp1;
		w_d = w_c;
		w_c = w_b;
		w_b = w_a;
		w_a = temp1 + temp2;
	}
	H[0] += w_a;
	H[1] += w_b;
	H[2] += w_c;
	H[3] += w_d;
	H[4] += w_e;
	H[5] += w_f;
	H[6] += w_g;
	H[7] += w_h;
}

int main(int argc, char **argv) {
	if (argc != 2) {
		printf("Usage: ./file_sha512.out <filename>\n");
		return 1;
	}

	char filename[260] = {0};
	strncpy(filename, argv[1], 256);
	filename[256] = 0;

	std::ifstream infile(filename, std::ifstream::binary);
	if (!infile) {
		printf("Error opening \"%s\"\n", filename);
		return 1;
	}

	ull L, K, MLEN;
	L = K = MLEN = 0;

	//hashvals are stored in H[]; copy from default values at h[]
	H = (ull *)malloc(64);
	for (int i = 0; i < 8; i++)
		H[i] = h[i];

	//max buffer is 16MB + 2048 bits for K and L
	int max_buf_size = 1024 * 256;	//in bytes
	M = (ull *)malloc(max_buf_size + 2048/8);


	char *buf = (char *)malloc(max_buf_size);
	int buf_size, num_chunks;
	do {
		infile.read(buf, max_buf_size);
		buf_size = infile.gcount();

		L += buf_size * 8;

		//copy buffer bytes to M[]
		word_ptr = byte_ptr = bit_ptr = 0;
		int buf_words = buf_size / 8;
		for (int i = 0; i < buf_words; i++)
			append_word(htonll(*((ull *)buf + i)));
		for (int i = buf_size - buf_size % 8; i < buf_size; i++)
			append_byte(buf[i]);

		//if we reached EOF, we append 1 bit, K 0's, and 128-bit L
		if (buf_size < max_buf_size) {
			MLEN = L + 1 + 128;
			K = (-MLEN % 1024 + 1024) % 1024;
			MLEN += K;
			//append 1 bit and K 0's
			append_byte(0x80);
			for (int i = 0; i < K/8; i++)
				append_byte(0);
			//append 128-bit L
			append_word(0);
			append_word(L);
		}

		//iterate through all chunks
		for (int i = 0; i < word_ptr; i+=16)
			get_hash(M+i, H);
		
	} while (buf_size == max_buf_size);

	printf("SHA-512 of %s:\n", filename);
	for (int j = 0; j < 8; j++) {
		unsigned long long x = H[j];
		for (int i = 0; i < 64; i+=8) {
			printf("%02x", (unsigned int)(((*(((unsigned long long*)&x))) >> (64-8-i)) & 0xFFLLU) );
		}
	}
	printf("\n");

	free(M);
	free(H);
	free(buf);
	return 0;
}
