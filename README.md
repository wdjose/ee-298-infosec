# Machine Problem 1 - Hashing

This repository contains code in C++ which performs SHA-512 on any file. 

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

---

Machine Problem 1 for EE 298, University of the Philippines Diliman

Authors: 
- Williard Joshua Jose
- Rangel Daroya
- Jonric Mirando
