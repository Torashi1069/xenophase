#pragma once


unsigned long* crypton_set_key(const unsigned long in_key[], const unsigned long key_len);
void crypton_encrypt(const unsigned long in_blk[4], unsigned long out_blk[4]);
void crypton_decrypt(const unsigned long in_blk[4], unsigned long out_blk[4]);
