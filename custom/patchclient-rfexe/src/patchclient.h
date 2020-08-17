#pragma once
#include "resource.h"

// Default patcher settings
#define PN_WEBADDRESS "webpatch.xenophase.net"
#define PN_LISTFILE "patch/patch6.txt"
#define PN_NOTICEFILE "patch/notice_patch.txt"
#define PN_ALLOWFILE "patch/patch_allow.txt"
#define PN_PATCHLEVELFILE_OLD "apatch.inf"
#define PN_PATCHLEVELFILE "apatch.ini"
#define PN_NOTICECLOSEFILE "patch/notice_close.txt"
#define PN_DATAFILE "adata.grf"
#define PN_FILEWEBADDR "ftp.xenophase.net"
#define PN_FILEWEBDIR "rf/patch/"
#define PN_FILEWEBPORT 443
#define PN_WEBPORT 443

// Settings of the patchwindow itself
#define PMC_TITLE "Ragnarok Frontier - Patch client"
#define PMC_HEADLINE "Ragnarok Patch Notice"
#define PMC_NOTICE_BLANK "Loading Patch Notice, please wait."
#define PMC_BUILDON_STR "Build Date: "__DATE__" "__TIME__""
#define PMC_EXITBUTTON "Exit"
#define PMC_SGBUTTON "Start Game"
#define PMC_STATUS_BLANK "..."
#define PMC_GAMEEXE "rfexe.exe 1sak1"
#define PMC_GAMETITLE "Ragnarok Frontier"
#define PMC_GAMEWNDCLASS "Ragnarok"

// Optional features
#define PMC_SHOWHEADURL FALSE
#define PMC_HEADURLTEXT ""
#define PMC_HEADURL ""

#define PMC_SHOWVOTELINK FALSE
#define PMC_VOTELINKTEXT "Please Vote for us!"
#define PMC_VOTELINK ""

#define PMC_ADDABOUTWINDOW FALSE

// public key for patchlist signature verification
#define PN_PUBLICKEY \
"-----BEGIN PUBLIC KEY-----"                                      "\n" \
"MIIBIjANBgkqhkiG9w0BAQEFAAOCAQ8AMIIBCgKCAQEAv4KD2k97vQq4aQiebva2""\n" \
"Z3VKLj7ydQjgg3adySk/BBJ1seNqeBoU/5Btp0UrrXz2VVjG4fW8zdQT45pz2otu""\n" \
"iF1gU+rk+bYO3JgQ0S086XBP+KnOjmMIwLRkotDNRATnbhSgIgKP1SA9+MxFEhoH""\n" \
"7KtFU7Vd2AhLo7Clkl6wa+8d22cb8EM6nId6psxyygQK064TYOLPkCe3hX0F/bqK""\n" \
"XlvvU+fQHlDnMNrVamhlqTX3owJ2J1puiJk7GZZJTx3Bo+cADb/fjKOkOWQMqA/Z""\n" \
"unszH0xjIDEcHa/8Ng/MJamnMjcNqoKeHMo+ybdNhEjRYI50Pd7lXeBj2DG9rmVZ""\n" \
"mQIDAQAB"                                                        "\n" \
"-----END PUBLIC KEY-----"                                        "\n"
