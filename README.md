# SHA-512 Implementation

This repository contains code in C++ which performs SHA-512 on any file. This source code is written from scratch, based on the pseudocode presented at https://en.wikipedia.org/wiki/SHA-2. Please see https://github.com/wdjose/sha-512/blob/master/profile_result.txt for runtime comparison with Python's hashlib library and Ubuntu's sha512sum utility. 

To compile: 

<code>make</code>

Usage: 

<code>./profile_sha512.out &lt;filename&gt;</code>

Example:

<code>./profile_sha512.out ubuntu-18.04.3-desktop-amd64.iso</code>

This repository also contains a bash script profiler comparing the C++ program performance with: 
- A python program utilizing the hashlib library
- The sha512sum command built in Ubuntu

Usage: 

<code>bash profile_sha512.sh &lt;filename1&gt; &lt;filename2&gt; &gt; profile_result.txt</code>

Example:

<code>bash profile_sha512.sh ubuntu-18.04.3-desktop-amd64.iso VirtualBox-6.1.4-136177-Win.exe &gt; profile_result.txt</code>
