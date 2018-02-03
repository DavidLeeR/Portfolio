Encryption program created for the course "Operating Systems" at Oregon State University

Description: This program includes an encryption daemon and client as well as a decryption daemon and client.
             The encryption client (otp_enc) asks the encryption daemon (otp_enc_d) to perform one time pad encryption
             using network calls. Similarly, The decryption client (otp_dec) asks the encryption daemon (otp_dec_d) to 
             perform one time pad decryption using network calls. Finally, the keygen program creates a decryption key 
             of the specified length. 
             

Instructions to compile and run programs:
Requires gcc (GNU) compiler 4.8.5
1)compile otp_enc.c with the command gcc otp_enc.c -o enc
2)compile otp_enc_d.c with the command gcc otp_enc_d.c -o enc_d
3)compile otp_dec.c with the command gcc otp_dec.c -o dec
4)compile otp_dec_d.c with the command gcc otp_dec.c -o dec_d
4)compile keygen.c with the command gcc keygen.c -o key
5)create a text file named "plaintext.txt" in the same directory
6)place the text you would like encrypted in plaintext.txt
7)to create a key, use the command keygen <length> > key
    -length is the length of the key and must be at least as long as plain text
    -this will create a key and place it in file "key"
8)to run the encryption daemon, use the command otp_enc_d <portnumber1> &
9)to run the decryption daemon, use the command otp_dec_d <portnumber2> &
10)to run the encryption client, use the command otp_enc plaintext.txt key <portnumber1> > ciphertext
    -this creates a encrypted text file named "ciphertext"
11)to run the decryption client, use the command otp_dec ciphertext key <portnumber1> > decryptedtext
    -this creates a decrypted text file named "decryptedtext"
12)The decryptedtext file should match the plaintext.txt file. 



Demonstrates: network calls, encryption algorithm, multiple processes


