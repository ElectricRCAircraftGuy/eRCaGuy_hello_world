
GS  
\~ Aug. 2022?


## How to build gpg from source??? [I think that's what I was trying to figure out here]

https://gnupg.org/download/index.html


```bash
./configure
make
make install



# inside libgpg-error-1.45 dir
time ./configure
time make
time sudo make install




#######

# https://unix.stackexchange.com/a/175/114401
# https://gnupg.org/download/index.html

gpg --version

# 1. Build & install dependencies (needed libraries)

wget https://gnupg.org/ftp/gcrypt/libgpg-error/libgpg-error-1.45.tar.bz2
wget https://gnupg.org/ftp/gcrypt/libgcrypt/libgcrypt-1.10.1.tar.bz2
wget https://gnupg.org/ftp/gcrypt/libksba/libksba-1.6.0.tar.bz2
wget https://gnupg.org/ftp/gcrypt/libassuan/libassuan-2.5.5.tar.bz2
wget https://gnupg.org/ftp/gcrypt/ntbtls/ntbtls-0.3.1.tar.bz2
wget https://gnupg.org/ftp/gcrypt/npth/npth-1.6.tar.bz2
wget https://gnupg.org/ftp/gcrypt/pinentry/pinentry-1.2.0.tar.bz2

tar jxvf libgpg-error-*.bz2
tar jxvf libgcrypt-*.bz2
tar jxvf libksba-*.bz2
tar jxvf libassuan-*.bz2
tar jxvf ntbtls-*.bz2
tar jxvf npth-*.bz2
tar jxvf pinentry-*.bz2

cd libgpg-error-!(*.bz2)
./configure && make && sudo make install && cd ..

cd libgcrypt-!(*.bz2)
./configure && make && sudo make install && cd ..

cd libksba-!(*.bz2)
./configure && make && sudo make install && cd ..

cd libassuan-!(*.bz2)
./configure && make && sudo make install && cd ..

cd ntbtls-!(*.bz2)
./configure && make && sudo make install && cd ..

cd npth-!(*.bz2)
./configure && make && sudo make install && cd ..

cd pinentry-!(*.bz2)
./configure && make && sudo make install && cd ..

# 2. Build & install gpg

wget https://gnupg.org/ftp/gcrypt/gnupg/gnupg-2.3.7.tar.bz2
tar jxvf gnupg-*.bz2
cd gnupg-!(*.bz2)
./configure && make && sudo make install && cd ..



```


output while trying to run the above?
```
*** You need libgpg-error to build this program.
**  This library is for example available at
***   https://gnupg.org/ftp/gcrypt/gpgrt
*** (at least version 1.41 is required.)
***
configure:
***
*** You need libgcrypt to build this program.
**  This library is for example available at
***   https://gnupg.org/ftp/gcrypt/libgcrypt/
*** (at least version 1.9.1 (API 1) is required.)
***
configure:
***
*** You need libassuan to build this program.
*** This library is for example available at
***   https://gnupg.org/ftp/gcrypt/libassuan/
*** (at least version 2.5.0 (API 2) is required).
***
configure:
***
*** You need libksba to build this program.
*** This library is for example available at
***   https://gnupg.org/ftp/gcrypt/libksba/
*** (at least version 1.3.4 using API 1 is required).
***
configure:
***
*** It is now required to build with support for the
*** New Portable Threads Library (nPth). Please install this
*** library first.  The library is for example available at
***   https://gnupg.org/ftp/gcrypt/npth/
*** (at least version 1.2 (API 1) is required).
```


## and how do I check its pgp/gpg signature?

